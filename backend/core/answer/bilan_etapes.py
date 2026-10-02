"""La note d'un exercice à étapes — le bilan de `oef/var.proc`, non une moyenne.

WIMS ne note pas un exercice à étapes étape par étape. Chaque envoi
intermédiaire passe par `oef/step.proc`, qui juge l'étape pour décider de la
suite et **range** les réponses (`saverep$i`) ; la note n'est calculée qu'une
fois, quand l'exercice se termine — dernière étape franchie, ou réponse fausse
sans `nonstop` qui l'arrête (`step.proc:66`). `var.proc` (`:ana`) reprend alors
**toutes** les réponses :

    freetot = creplycnt + conditioncnt − conditionned + weightadjust
    freegot = condgot + Σ notes des réponses atteintes (× leur poids)
    note    = (freegot / freetot) ^ freepower

- ``creplycnt`` compte les réponses des étapes **annoncées** (`oefsteps`) :
  toutes celles d'un `course` dont les étapes sont écrites d'avance, celles des
  étapes déjà ouvertes d'un exercice à `\\nextstep` (`nextstep.proc:24`). Une
  réponse d'étape annoncée mais jamais atteinte y pèse de tout son poids, et
  rapporte zéro (`var.proc:307`).
- Un champ ``?analyze`` sort du compte (``conditionned``, `var.proc:302`) :
  ce sont les conditions qui le jugent, et elles comptent toutes, qu'elles
  portent sur une étape atteinte ou non.

PAX faisait la moyenne des étapes, chacune au prorata de ses champs justes, et
comptait juste un champ ``?analyze`` jamais jugé. Les deux mesures de
`oefdevfact/deve7` (6/10, 4/10) ne départagent pas les deux modèles — 3/5 et
2/5 ici, (1 + 2/3)/3 et (1 + 1/3)/3 là ; `histocap`, arrêté à l'étape 5 avec
1,4/10 chez WIMS, dément la moyenne. Reste un écart ouvert : ces mesures de
`deve7` supposent `freepower` = 1, quand le niveau 3 le met à 2 (TODO).

Ce que chaque étape a montré — ses champs, les réponses, leurs verdicts — est
gardé côté serveur, comme WIMS garde `saverep$i` : le bilan ne dépend pas de
ce que le navigateur voudra bien renvoyer.
"""

from __future__ import annotations

import json
import logging
import re

logger = logging.getLogger(__name__)

# Un exercice laissé en plan ne doit pas encombrer Redis ; une séance, si.
_TTL = 6 * 3600


def _cle(user_id: str, exercise_id: str, seed: int) -> str:
    return f"pax:etapes:{user_id}:{exercise_id}:{seed}"


def _redis():
    from core.oef.render_cache import _redis_client  # noqa: PLC0415
    return _redis_client()


def nom_canonique(token: str) -> str:
    """`r5`, `reply5`, `R 5` → `reply5` ; `c2` reste `c2`."""
    t = re.sub(r"\s+", "", token)
    if m := re.fullmatch(r"r(?:eply)?(\d+)", t, re.I):
        return f"reply{m.group(1)}"
    if m := re.fullmatch(r"c(?:hoice)?(\d+)", t, re.I):
        return f"c{m.group(1)}"
    return t


def lire_parcours(user_id: str, exercise_id: str, seed: int) -> dict:
    """Ce que les étapes déjà envoyées ont laissé : `{etapes, notes, reponses}`."""
    vide = {"etapes": {}, "notes": {}, "reponses": {}}
    r = _redis()
    if r is None:
        return vide
    try:
        data = r.get(_cle(user_id, exercise_id, seed))
        if data:
            return json.loads(data)
    except Exception as exc:  # noqa: BLE001
        logger.debug("parcours : lecture impossible (%s)", exc)
    return vide


def memoriser_etape(
    user_id: str,
    exercise_id: str,
    seed: int,
    etape: int,
    noms: list[str],
    notes: dict[str, float],
    reponses: dict[str, str],
) -> dict:
    """Ajoute l'étape ``etape`` au parcours, et le renvoie.

    L'étape 1 ouvre un parcours neuf : recommencer le même tirage ne doit pas
    hériter des réponses de l'essai précédent.
    """
    parcours = (
        {"etapes": {}, "notes": {}, "reponses": {}}
        if etape <= 1
        else lire_parcours(user_id, exercise_id, seed)
    )
    # Une étape rejouée (réponse refusée pour son format, puis corrigée)
    # remplace la précédente ; les étapes au-delà n'existent pas encore.
    parcours["etapes"] = {
        k: v for k, v in parcours["etapes"].items() if int(k) < etape
    }
    parcours["etapes"][str(etape)] = list(noms)
    parcours["notes"].update(notes)
    parcours["reponses"].update(reponses)
    r = _redis()
    if r is not None:
        try:
            r.setex(_cle(user_id, exercise_id, seed), _TTL, json.dumps(parcours))
        except Exception as exc:  # noqa: BLE001
            logger.debug("parcours : écriture impossible (%s)", exc)
    return parcours


def etapes_ecrites(rendered) -> list[list[str]] | None:
    """Les étapes que `oefsteps` écrit d'avance, ou ``None``.

    Un `course` les énumère toutes, une par ligne ; un exercice à `\\nextstep`
    n'en connaît que la première, les suivantes naissant de ses réponses. On
    ne tient la liste pour complète que si elle compte autant de lignes que
    d'étapes annoncées.
    """
    brut = str((rendered.ev_ctx or {}).get("oefsteps", "")).strip()
    lignes = [l for l in re.split(r"[\n\r]+", brut) if l.strip()]
    if len(lignes) <= 1 or len(lignes) != (rendered.total_steps or 0):
        return None
    return [
        [nom_canonique(t) for t in re.split(r"[,;\t]+", l) if t.strip()]
        for l in lignes
    ]


def _est_analyse(ans_def) -> bool:
    return ans_def.answer_type == "analyze" or "analyze_var" in (ans_def.options or {})


def bilan(rendered, parcours: dict, etape: int, seed: int,
          m_step_final: int | None = None) -> float:
    """La note de `var.proc` sur tout le parcours, avant `freepower`.

    `m_step_final` : la valeur de `$m_step` sous laquelle WIMS joue le dernier
    `:postdef` et le `:test`. Pour un exercice `\\nextstep` mené à son terme,
    `step.proc` a déjà avancé l'étape (`!advance oefstep`) quand
    `nextstep.proc` joue `:postdef` : c'est N+1, et le modèle QCM de
    `uniteadn` y lit le verdict de la dernière question (`val69[$m_step-1;…]`).
    """
    from core.answer.strategies.analyze import (  # noqa: PLC0415
        _analyze_replies,
        _cases_en_textes,
        _forme_brute,
    )

    par_nom = {a.input_name: a for a in (getattr(rendered, "toutes_reponses", None) or rendered.answers)}
    atteintes: list[str] = []
    for k in sorted(parcours.get("etapes", {}), key=int):
        if int(k) <= etape:
            atteintes += parcours["etapes"][k]
    annoncees = atteintes
    ecrites = etapes_ecrites(rendered)
    if ecrites is not None:
        annoncees = [n for ligne in ecrites for n in ligne]

    notes = parcours.get("notes", {})
    got = tot = 0.0
    for nom in dict.fromkeys(annoncees):
        a = par_nom.get(nom)
        if a is None or _est_analyse(a):
            continue
        poids = a.weight if a.weight is not None else 1.0
        tot += poids
        if nom in atteintes:
            got += float(notes.get(nom, 0.0)) * poids

    # Les conditions, jouées sur les réponses des étapes atteintes. Celles qui
    # portent sur un champ jamais atteint échouent, et comptent quand même.
    sections = rendered.check_sections
    if sections and sections.get("test"):
        from core.oef.def_engine import check_analyze  # noqa: PLC0415

        # Un champ jamais atteint est **vide** : WIMS ne l'a pas reçu. Le laisser
        # hors du contexte, c'était lui laisser la valeur que le rendu y avait
        # posée — `histocap` passait 45 conditions sur 49, dont celles d'une
        # étape 6 jamais ouverte, que WIMS marque toutes « NON ».
        memo = parcours.get("reponses", {})
        reponses = {n: (memo.get(n, "") if n in atteintes else "") for n in par_nom}
        reponses = _cases_en_textes(rendered, list(par_nom.values()), reponses)
        ctx = sections["ctx"]
        if m_step_final is not None:
            ctx = dict(ctx, m_step=str(m_step_final), step=str(m_step_final))
        par_numero: dict[int, str] = {}
        for n, v in reponses.items():
            if m := re.fullmatch(r"reply(\d+)", n):
                par_numero[int(m.group(1))] = _forme_brute(v.strip(), par_nom.get(n))
        retenues: list[int] = []
        condtest, poids_cond = check_analyze(
            ev_ctx=ctx,
            postdef_instructions=sections["postdef"],
            test_instructions=sections["test"],
            analyze_replies=_analyze_replies(list(par_nom.values()), reponses, rendered.lang),
            seed=seed,
            replies_by_number=par_numero,
            def_path=sections.get("def_path"),
            condlist_out=retenues,
        )
        try:
            declarees = int(str((rendered.meta or {}).get("conditioncnt", 0)).strip() or 0)
        except ValueError:
            declarees = 0
        # `condlist=all` : toutes les conditions déclarées comptent, même
        # celles que `:test` n'aurait pas posées. Une `condlist` explicite,
        # elle, borne le compte à ses conditions — vide (`[0]`), à aucune.
        numeros = [int(k[len("condtest"):]) for k in condtest if k[len("condtest"):].isdigit()]
        if retenues == [0]:
            retenues = []
        elif not retenues:
            retenues = list(range(1, max([declarees, *numeros]) + 1))
        for k in retenues:
            nom = f"condtest{k}"
            w = poids_cond.get(nom, 1.0)
            tot += w
            got += condtest.get(nom, 0) * w

    return got / tot if tot > 0 else 0.0
