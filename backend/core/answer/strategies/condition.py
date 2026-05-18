"""Stratégie \\condition OEF : évaluation via OEFEvaluator."""

from __future__ import annotations

from core.answer.schemas import AnswerResult
from core.oef.evaluator import OEFEvaluator


def run_condition(
    condition_expr: str,
    active_ans_defs: list,
    replies_by_name: dict[str, str],
    ev: OEFEvaluator,
) -> tuple[float, list[AnswerResult]]:
    """Évalue la \\condition OEF avec les réponses élève.

    Injecte les valeurs de réponse dans le contexte de l'évaluateur, évalue
    l'expression booléenne globale, et retourne (global_score, results).
    """
    for ans in active_ans_defs:
        val = replies_by_name.get(ans.input_name, "").strip()
        ev.ctx[ans.input_name] = val
        alias = ans.input_name.replace("reply", "r")
        ev.ctx[alias] = val
        if ans.logical_name:
            ev.ctx[ans.logical_name] = val

    correct = bool(ev._eval_expr(condition_expr, kind="logic"))
    score = 1.0 if correct else 0.0

    results: list[AnswerResult] = []
    for ans in active_ans_defs:
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
