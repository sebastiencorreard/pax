from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.exercise import Exercise
from models.attempt import Attempt
from models.user import User
from api.deps import get_current_user
from core.oef.engine import load_and_render
from core.oef.evaluator import OEFEvaluator
from core.answer.schemas import AnswerResult
from core.answer.strategies.standard import run_standard
from core.answer.strategies.condition import run_condition
from core.answer.strategies.analyze import run_analyze, run_feedback

router = APIRouter(prefix="/api/check", tags=["check"])


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

    active_ans_defs = [
        a for a in rendered.answers
        if "default=vide" not in str(a.options.get("option", "")).lower()
        and (visible_input_names is None or a.input_name in visible_input_names)
    ]

    # ── Dispatch vers la bonne stratégie ─────────────────────────────────────
    feedback_html: str | None = None

    if rendered.check_sections and any(a.answer_type == "analyze" for a in active_ans_defs):
        global_score, results = run_analyze(rendered, active_ans_defs, replies_by_name, body.seed)
        feedback_html = run_feedback(rendered, active_ans_defs, replies_by_name, results, body.seed)

    elif rendered.condition:
        evaluator = OEFEvaluator(seed=body.seed)
        evaluator.ctx.update(rendered.ev_ctx)
        global_score, results = run_condition(
            rendered.condition["expr"], active_ans_defs, replies_by_name, evaluator
        )

    else:
        global_score, results = run_standard(active_ans_defs, replies_by_name)
        feedback_html = run_feedback(rendered, active_ans_defs, replies_by_name, results, body.seed)

    # ── Métadonnées de réponse ────────────────────────────────────────────────
    has_invalid = any(r.status == "invalid_format" for r in results)

    noanalyzeprint = any(
        "noanalyzeprint" in str(a.options.get("option", "")).lower()
        for a in rendered.answers
    )

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

    return CheckResponse(
        exercise_id=exercise_id,
        global_score=global_score,
        results=results,
        attempt_id=attempt_id,
        has_invalid_format=has_invalid,
        noanalyzeprint=noanalyzeprint,
        feedback_html=feedback_html,
    )
