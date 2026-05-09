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
                parse_expr,
                standard_transformations,
                implicit_multiplication_application,
            )

            transformations = standard_transformations + (
                implicit_multiplication_application,
            )
            local_dict = {"expand": sympy.expand, "factor": sympy.factor}
            expr = parse_expr(
                _normalize_expr(expected),
                transformations=transformations,
                local_dict=local_dict,
            )
            return str(sympy.expand(expr))
        except Exception:
            pass
    return expected


class ReplyItem(BaseModel):
    input_name: str  # reply1, reply2, ...
    value: str  # ce que l'élève a tapé


class CheckRequest(BaseModel):
    seed: int
    replies: list[ReplyItem]
    sheet_id: int | None = None
    m_step: int | None = None


class AnswerResult(BaseModel):
    input_name: str
    correct: bool
    score: float
    method: str
    reply: str | None = None  # réponse de l'élève
    expected: str | None = None  # correction
    status: str = "ok"
    detail: str | None = None


class CheckResponse(BaseModel):
    exercise_id: str
    global_score: float  # moyenne pondérée
    results: list[AnswerResult]
    attempt_id: str
    has_invalid_format: bool = False
    noanalyzeprint: bool = False
    feedback_html: str | None = None


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
    for ans in ans_defs:
        val = replies_by_name.get(ans.input_name, "").strip()
        ev.ctx[ans.input_name] = val
        alias = ans.input_name.replace("reply", "r")
        ev.ctx[alias] = val
        if ans.logical_name:
            ev.ctx[ans.logical_name] = val

    correct = bool(ev._eval_expr(condition_expr, kind="logic"))

    score = 1.0 if correct else 0.0
    results = []
    for ans in ans_defs:
        reply_val = replies_by_name.get(ans.input_name, "").strip()
        results.append(
            AnswerResult(
                input_name=ans.input_name,
                correct=correct,
                score=score,
                method="condition",
                reply=reply_val,
                expected=ev.ctx.get(
                    ans.logical_name if ans.logical_name else ans.input_name,
                    ans.expected,
                ),
            )
        )
    return score, results


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

    results: list[AnswerResult] = []
    total_weight = 0.0
    weighted_score = 0.0

    replies_by_name: dict[str, str] = {}
    for r in body.replies:
        name = r.input_name.replace(" ", "")
        replies_by_name[name] = r.value

    import re as _re2
    for name, value in list(replies_by_name.items()):
        m = _re2.match(r"^r(\d+)$", name)
        if m:
            replies_by_name[f"reply{m.group(1)}"] = value
        m2 = _re2.match(r"^reply(\d+)$", name)
        if m2:
            replies_by_name[f"r{m2.group(1)}"] = value

    # Filter out fields that should be completely ignored (default=vide)
    active_ans_defs = [
        a for a in rendered.answers 
        if "default=vide" not in str(a.options.get("option", "")).lower()
    ]

    # Exercices avec réponses ?analyze (vérification via :postdef + :test)
    if rendered.check_sections and any(a.answer_type == "analyze" for a in active_ans_defs):
        from core.oef.def_engine import check_analyze
        from core.answer.checkers import _normalize_expr

        analyze_replies = {
            a.options["analyze_var"]: f"({_normalize_expr(replies_by_name.get(a.input_name, '').strip())})"
            for a in active_ans_defs
            if a.answer_type == "analyze" and "analyze_var" in a.options
        }
        condtest = check_analyze(
            ev_ctx=rendered.check_sections["ctx"],
            postdef_instructions=rendered.check_sections["postdef"],
            test_instructions=rendered.check_sections["test"],
            analyze_replies=analyze_replies,
            seed=body.seed,
        )
        n_tests = len(condtest)
        global_score = sum(condtest.values()) / n_tests if n_tests > 0 else 0.0
        for ans_def in active_ans_defs:
            reply_value = replies_by_name.get(ans_def.input_name, "").strip()
            results.append(
                AnswerResult(
                    input_name=ans_def.input_name,
                    correct=bool(global_score == 1.0),
                    score=global_score,
                    method="analyze",
                    reply=reply_value,
                    expected=_pretty_expected(ans_def.expected, ans_def.answer_type),
                )
            )

    elif rendered.condition:
        evaluator = OEFEvaluator(seed=body.seed)
        evaluator.ctx.update(rendered.ev_ctx)
        
        global_score, results = _check_condition(
            rendered.condition["expr"], active_ans_defs, replies_by_name, evaluator
        )
    else:
        for ans_def in active_ans_defs:
            reply_value = replies_by_name.get(ans_def.input_name, "").strip()
            check = check_answer(
                answer_type=ans_def.answer_type,
                reply=reply_value,
                expected=ans_def.expected,
                options=ans_def.options,
            )
            results.append(
                AnswerResult(
                    input_name=ans_def.input_name,
                    correct=check.correct,
                    score=check.score,
                    method=check.method,
                    reply=reply_value,
                    expected=_pretty_expected(ans_def.expected, ans_def.answer_type),
                    status=check.status,
                    detail=check.detail,
                )
            )
            weighted_score += check.score * ans_def.weight
            total_weight += ans_def.weight

        global_score = weighted_score / total_weight if total_weight > 0 else 0.0

    has_invalid = any(r.status == "invalid_format" for r in results)

    noanalyzeprint = False
    for a in rendered.answers:
        if "noanalyzeprint" in str(a.options.get("option", "")).lower():
            noanalyzeprint = True
            break

    feedback_html = None
    if rendered.check_sections and "feedback" in rendered.check_sections:
        from core.oef.def_engine import render_feedback
        feedback_html = render_feedback(
            ev_ctx=rendered.check_sections["ctx"],
            postdef_instructions=rendered.check_sections["postdef"],
            test_instructions=rendered.check_sections["test"],
            feedback_instructions=rendered.check_sections["feedback"],
            replies_by_name=replies_by_name,
            results=results,
            seed=body.seed,
        )

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
