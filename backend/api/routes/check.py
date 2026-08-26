from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from config import settings
from db import get_db
from models.exercise import Exercise
from models.attempt import Attempt
from models.user import User
from api.deps import get_current_user
from core.oef.engine import load_and_render, find_def_path
from core.oef.evaluator import OEFEvaluator
from core.answer.schemas import AnswerResult
from core.answer.strategies.standard import run_standard
from core.answer.strategies.condition import run_condition
from core.answer.strategies.analyze import run_analyze, run_feedback
from core.chrono import module_scoredelay, read_started_at, score_factor

router = APIRouter(prefix="/api/check", tags=["check"])

# Types dont la bonne réponse est **une seule valeur numérique**, et dont le
# corrigé peut donc s'écrire dans la convention décimale de la langue
# (cf. `PAX_LOCALIZE_FEEDBACK`). C'est le périmètre de `NUMERIC_REPLY_TYPES`
# (`strategies/_locale.py`, côté saisie), plus `range` — dont la réponse est
# elle aussi une valeur unique, ses bornes ne servant qu'à la comparer.
#
# Les types à **plusieurs composantes** en sont exclus, et c'est le point à ne
# pas rater : leur virgule sépare déjà les composantes. Localiser les points
# d'un `coord` attendu `2.5,3.5` donnerait `2,5,3,5`, illisible. Ceux-là
# s'écrivent `2,5;3,5`, ce que `_pixels_to_repere` fait déjà pour `coord`.
# Exclus aussi les types textuels : un `atext` répond « 3.5 pouces », un `raw`
# compare au caractère près, un `correspond` transporte du HTML.
_LOCALIZED_FEEDBACK_TYPES = frozenset({
    "numeric", "numexp", "range", "units", "unit", "sigunits",
})


def _localize_feedback(results, answers, lang: str, enabled: bool) -> None:
    """Écrit les corrigés numériques dans la convention décimale de `lang`.

    Confort d'affichage, coupé par `PAX_LOCALIZE_FEEDBACK=0` : le moteur sort
    des points, la langue de l'exercice en veut peut-être des virgules
    (`core/oef/i18n.py`). **Aucun verdict n'en dépend** — la notation accepte
    les deux écritures, et seule la bonne réponse est réécrite : `reply` est ce
    que l'élève a tapé, on le lui rend tel quel.

    Modifie `results` sur place.
    """
    from core.oef.i18n import localize_decimals, uses_comma_decimal  # noqa: PLC0415

    if not enabled or not uses_comma_decimal(lang):
        return
    names = {
        a.input_name for a in answers
        if (a.answer_type or "").lower() in _LOCALIZED_FEEDBACK_TYPES
    }
    if not names:
        return
    for r in results:
        if r.input_name in names and r.expected:
            r.expected = localize_decimals(r.expected, lang)


# ── Modèles HTTP ──────────────────────────────────────────────────────────────

class ReplyItem(BaseModel):
    input_name: str
    value: str


class CheckRequest(BaseModel):
    seed: int
    replies: list[ReplyItem]
    sheet_id: int | None = None
    m_step: int | None = None


class CheckResponse(BaseModel):
    exercise_id: str
    global_score: float
    results: list[AnswerResult]
    attempt_id: str
    has_invalid_format: bool = False
    noanalyzeprint: bool = False
    feedback_html: str | None = None
    solution_html: str | None = None
    # Chrono telemetry — informational for the frontend so the score breakdown
    # can read "vous avez gagné 0.6 pts (1.0 × 60% chrono)". Server already
    # applied the factor to ``global_score``; these fields are *not* used to
    # recompute anything client-side.
    chrono_elapsed: float | None = None
    chrono_factor: float | None = None


def _pixels_to_repere(s: str | None, transform: str, comma_decimal: bool) -> str | None:
    """Render a coord click-zone (pixels) in repère units for the feedback.

    ``transform`` is ``"x0,y0,ex,ey"`` (origin pixel + pixels-per-unit, from
    slib/draw/repere). ``s`` is e.g. ``"(177,317)"`` or ``"point,170,320"`` —
    the first numeric pair is the point/centre. The reply click rarely lands
    on an exact grid node, so we round to 1 decimal (honest: shows a near-miss
    as ``(-0,8;-3,9)``, not a misleading ``(-1;-4)``).
    """
    import re as _re  # noqa: PLC0415

    try:
        x0, y0, ex, ey = (float(v) for v in transform.split(","))
    except (ValueError, TypeError):
        return s
    if not ex or not ey:
        return s
    nums = _re.findall(r"-?\d+(?:\.\d+)?", s or "")
    if len(nums) < 2:
        return s
    mx = (float(nums[0]) - x0) / ex
    my = (float(nums[1]) - y0) / ey
    dec, sep = (",", ";") if comma_decimal else (".", ",")

    def _fmt(v: float) -> str:
        v = round(v, 1)
        out = str(int(v)) if v == int(v) else str(v)
        return out.replace(".", dec)

    return f"({_fmt(mx)}{sep}{_fmt(my)})"


# ── Route ─────────────────────────────────────────────────────────────────────

@router.post("/{exercise_id}", response_model=CheckResponse)
async def check_exercise(
    exercise_id: str,
    body: CheckRequest,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    try:
        rendered = load_and_render(exercise.oef_path, seed=body.seed, m_step=body.m_step)
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Erreur de rendu : {e}")

    # ── Normalisation des réponses ────────────────────────────────────────────
    import re as _re
    replies_by_name: dict[str, str] = {}
    for r in body.replies:
        name = r.input_name.replace(" ", "")
        replies_by_name[name] = r.value
    for name, value in list(replies_by_name.items()):
        if m := _re.match(r"^r(\d+)$", name):
            replies_by_name[f"reply{m.group(1)}"] = value
        if m := _re.match(r"^reply(\d+)$", name):
            replies_by_name[f"r{m.group(1)}"] = value

    # ── Filtrage des réponses actives ─────────────────────────────────────────
    visible_input_names: set[str] | None = None
    if rendered.is_dynsteps:
        visible_input_names = {
            s["name"]
            for s in rendered.statement_segments
            if s.get("type") in ("input", "slot", "menu")
        }
        # For dynsteps/course, answers are already filtered by the engine to
        # the current step's replies; include them all (covers radio/menu
        # answers that don't emit a widget span in the statement).
        for a in rendered.answers:
            visible_input_names.add(a.input_name)

    active_ans_defs = [
        a for a in rendered.answers
        if not a.options.get("ungraded")
        and (visible_input_names is None or a.input_name in visible_input_names)
    ]

    # ── Dispatch vers la bonne stratégie ─────────────────────────────────────
    feedback_html: str | None = None

    # `analyze_var` covers widget answers (clickfill/radio/menu) that DISPLAY a
    # widget but are CHECKED via the :test section — e.g. deve7's clickfill
    # slots feed `?analyze 49…52` and grading is `simplify(reply1²+2·reply2·
    # reply3+reply4²−enonce)=0`. Without this they fell through to run_standard
    # (empty expected → always wrong).
    if rendered.check_sections and any(
        a.answer_type == "analyze" or "analyze_var" in a.options
        for a in active_ans_defs
    ):
        global_score, results = run_analyze(rendered, active_ans_defs, replies_by_name, body.seed)
        feedback_html = run_feedback(rendered, active_ans_defs, replies_by_name, results, body.seed)

    elif rendered.condition:
        evaluator = OEFEvaluator(seed=body.seed)
        evaluator.ctx.update(rendered.ev_ctx)
        global_score, results = run_condition(
            rendered.condition["expr"], active_ans_defs, replies_by_name, evaluator,
            rendered.lang,
        )

    else:
        global_score, results = run_standard(active_ans_defs, replies_by_name, rendered.lang)
        feedback_html = run_feedback(rendered, active_ans_defs, replies_by_name, results, body.seed)

    # ── coord : feedback en coordonnées du repère (pas en pixels) ────────────
    from core.oef.i18n import uses_comma_decimal  # noqa: PLC0415
    _coord_xform = {
        a.input_name: a.options["transform"]
        for a in rendered.answers
        if a.answer_type == "coord" and a.options.get("transform")
    }
    if _coord_xform:
        comma = uses_comma_decimal(rendered.lang)
        for r in results:
            xform = _coord_xform.get(r.input_name)
            if xform:
                r.reply = _pixels_to_repere(r.reply, xform, comma)
                r.expected = _pixels_to_repere(r.expected, xform, comma)

    # ── atext : le corrigé montre `replyGood`, pas `replygood` ───────────────
    # WIMS affiche la première alternative de la première ligne ; le reste du
    # `replygood` est un jeu de `badwords` interne. `oefcountries` y range les
    # deux cents pays du monde, que le corrigé déroulait en entier.
    _atext_names = {a.input_name for a in rendered.answers if a.answer_type == "atext"}
    if _atext_names:
        from core.answer.checkers import atext_display_answer  # noqa: PLC0415
        for r in results:
            if r.input_name in _atext_names and r.expected:
                r.expected = atext_display_answer(r.expected)

    # ── range : le corrigé montre une valeur, pas les bornes ─────────────────
    # `anstype/range` affiche le milieu du premier intervalle (ou ses deux
    # bornes s'il est ouvert) : « 0,5 » plutôt que le « 0.6,0.4 » stocké, que
    # l'élève lirait comme deux réponses.
    _range_names = {a.input_name for a in rendered.answers if a.answer_type == "range"}
    if _range_names:
        from core.answer.checkers import range_display_answer  # noqa: PLC0415
        comma = uses_comma_decimal(rendered.lang)
        for r in results:
            if r.input_name in _range_names and r.expected:
                r.expected = range_display_answer(r.expected, comma)

    # ── sigunits : le corrigé montre la valeur arrondie, pas la consigne ──────
    # L'attendu est stocké `"<valeur> <unité> #N"`, où `#N` dit combien de
    # chiffres significatifs on exige. Affiché tel quel, `astron2` rendait
    # « 74753832.77 km^2 #4 » : la valeur que l'élève devait justement
    # arrondir, suivie d'un marqueur qui ne lui parle pas.
    _sig_names = {a.input_name for a in rendered.answers if a.answer_type == "sigunits"}
    if _sig_names:
        from core.answer.checkers import sigunits_display_answer  # noqa: PLC0415
        comma = uses_comma_decimal(rendered.lang)
        for r in results:
            if r.input_name in _sig_names and r.expected:
                r.expected = sigunits_display_answer(r.expected, comma)

    # ── Corrigé : la convention décimale de la langue (cf. _localize_feedback)
    _localize_feedback(
        results, rendered.answers, rendered.lang, settings.pax_localize_feedback
    )

    # ── Métadonnées de réponse ────────────────────────────────────────────────
    has_invalid = any(r.status == "invalid_format" for r in results)

    noanalyzeprint = any(
        "noanalyzeprint" in str(a.options.get("option", "")).lower()
        for a in rendered.answers
    )

    # ── Chrono : facteur de score en fonction du temps écoulé ────────────────
    # Si le module a un scoredelay et qu'on retrouve un started_at en Redis,
    # on multiplie le score brut par le facteur calculé côté serveur. Pas de
    # started_at (Redis perdu, /check sans /render préalable) → on n'applique
    # rien (score plein) plutôt que d'infliger un zéro arbitraire.
    chrono_elapsed: float | None = None
    chrono_factor: float | None = None
    if not has_invalid:
        sd = module_scoredelay(find_def_path(exercise.oef_path))
        if sd is not None:
            started_at = read_started_at(str(current_user.id), exercise_id, body.seed)
            if started_at is not None:
                from datetime import datetime, timezone
                elapsed = (datetime.now(timezone.utc) - started_at).total_seconds()
                factor = score_factor(elapsed, sd)
                chrono_elapsed = elapsed
                chrono_factor = factor
                global_score *= factor

    # ── Enregistrement de la tentative ───────────────────────────────────────
    attempt_id = "00000000-0000-0000-0000-000000000000"
    if not has_invalid:
        attempt = Attempt(
            student_id=current_user.id,
            exercise_id=exercise_id,
            sheet_id=body.sheet_id,
            score=global_score,
            answers={r.input_name: r.value for r in body.replies},
            seed=body.seed,
            is_graded=body.sheet_id is not None,
        )
        db.add(attempt)
        await db.commit()
        await db.refresh(attempt)
        attempt_id = str(attempt.id)

    solution_html = rendered.solution_html.strip() or None

    return CheckResponse(
        exercise_id=exercise_id,
        global_score=global_score,
        results=results,
        attempt_id=attempt_id,
        has_invalid_format=has_invalid,
        noanalyzeprint=noanalyzeprint,
        feedback_html=feedback_html,
        solution_html=solution_html,
        chrono_elapsed=chrono_elapsed,
        chrono_factor=chrono_factor,
    )
