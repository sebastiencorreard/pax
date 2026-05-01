import uuid
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
from core.answer.checkers import check_answer, _normalize_expr

router = APIRouter(prefix="/api/check", tags=["check"])


def _pretty_expected(expected: str, answer_type: str) -> str:
    """Retourne la correction sous forme lisible (développée pour algexp)."""
    if answer_type.lower() in ("algexp", "litexp", "formal"):
        try:
            import sympy
            from sympy.parsing.sympy_parser import (
                parse_expr, standard_transformations, implicit_multiplication_application
            )
            transformations = standard_transformations + (implicit_multiplication_application,)
            local_dict = {"expand": sympy.expand, "factor": sympy.factor}
            expr = parse_expr(_normalize_expr(expected), transformations=transformations,
                              local_dict=local_dict)
            return str(sympy.expand(expr))
        except Exception:
            pass
    return expected


class ReplyItem(BaseModel):
    input_name: str   # reply1, reply2, ...
    value: str        # ce que l'élève a tapé


class CheckRequest(BaseModel):
    seed: int
    replies: list[ReplyItem]
    sheet_id: int | None = None


class AnswerResult(BaseModel):
    input_name: str
    correct: bool
    score: float
    method: str
    reply: str | None = None      # réponse de l'élève
    expected: str | None = None   # correction


class CheckResponse(BaseModel):
    exercise_id: str
    global_score: float           # moyenne pondérée
    results: list[AnswerResult]
    attempt_id: str


def _check_condition(
    condition_expr: str,
    ans_defs,
    replies_by_name: dict,
    ev: OEFEvaluator,
) -> tuple[float, list[AnswerResult]]:
    """
    Évalue la \condition OEF avec les réponses élève via l'OEFEvaluator (Lark).
    Retourne (global_score, results).
    """
    # 1. Injecter les réponses élève dans le contexte de l'évaluateur
    # On supporte replyN, rN et les noms logiques si présents
    for ans in ans_defs:
        val = replies_by_name.get(ans.input_name, "").strip()
        # WIMS standard: \reply1, \reply2...
        ev.ctx[ans.input_name] = val
        # Alias court: \r1, \r2...
        alias = ans.input_name.replace("reply", "r")
        ev.ctx[alias] = val
        # Nom logique
        if ans.logical_name:
            ev.ctx[ans.logical_name] = val

    # 2. Évaluer l'expression via le parseur Lark
    # On force le type 'logic' pour avoir un booléen
    correct = bool(ev._eval_expr(condition_expr, kind="logic"))

    score = 1.0 if correct else 0.0
    results = []
    for ans in ans_defs:
        reply_val = replies_by_name.get(ans.input_name, "").strip()
        results.append(AnswerResult(
            input_name=ans.input_name,
            correct=correct,
            score=score,
            method="condition",
            reply=reply_val,
            expected=ev.ctx.get(
                ans.logical_name if ans.logical_name else ans.input_name,
                ans.expected
            ),
        ))
    return score, results


@router.post("/{exercise_id}", response_model=CheckResponse)
async def check_exercise(
    exercise_id: str,
    body: CheckRequest,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    # Charge l'exercice
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    # Re-rend l'exercice avec le même seed → mêmes valeurs attendues
    try:
        rendered = load_and_render(exercise.oef_path, seed=body.seed)
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Erreur de rendu : {e}")

    # Construit un index des réponses attendues par input_name
    expected_by_name = {a.input_name: a for a in rendered.answers}

    # Vérifie chaque réponse
    results: list[AnswerResult] = []
    total_weight = 0.0
    weighted_score = 0.0

    # Normalise les noms : "reply 1" → "reply1", et ajoute l'alias r1 ↔ reply1
    replies_by_name: dict[str, str] = {}
    for r in body.replies:
        name = r.input_name.replace(" ", "")
        replies_by_name[name] = r.value
        # r1 est l'alias court de reply1 (convention WIMS \embed{r1,...})
        import re as _re2
        m = _re2.match(r'^r(\d+)$', name)
        if m:
            replies_by_name[f"reply{m.group(1)}"] = r.value
        m2 = _re2.match(r'^reply(\d+)$', name)
        if m2:
            replies_by_name[f"r{m2.group(1)}"] = r.value

    # Si l'exercice a une \condition globale, l'évaluer
    if rendered.condition:
        global_score, results = _check_condition(
            rendered.condition["expr"], rendered.answers, replies_by_name, evaluator
        )
    else:
        for ans_def in rendered.answers:
            reply_value = replies_by_name.get(ans_def.input_name, "").strip()
            check = check_answer(
                answer_type=ans_def.answer_type,
                reply=reply_value,
                expected=ans_def.expected,
                options=ans_def.options,
            )
            results.append(AnswerResult(
                input_name=ans_def.input_name,
                correct=check.correct,
                score=check.score,
                method=check.method,
                reply=reply_value,
                expected=_pretty_expected(ans_def.expected, ans_def.answer_type),
            ))
            weighted_score += check.score * ans_def.weight
            total_weight += ans_def.weight

        global_score = weighted_score / total_weight if total_weight > 0 else 0.0

    # Sauvegarde la tentative
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

    return CheckResponse(
        exercise_id=exercise_id,
        global_score=global_score,
        results=results,
        attempt_id=str(attempt.id),
    )
