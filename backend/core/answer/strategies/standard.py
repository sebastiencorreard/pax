"""Stratégie standard : vérification réponse par réponse via checkers.py."""

from __future__ import annotations

from core.answer.checkers import check_answer, is_polexpand, _normalize_expr
from core.answer.schemas import AnswerResult


def pretty_expected(expected: str, answer_type: str) -> str:
    """Retourne la correction sous forme lisible, en préservant la forme
    voulue par l'auteur : développée si l'expected était développé,
    factorisée sinon."""
    if answer_type.lower() in ("algexp", "litexp", "formal"):
        try:
            import sympy
            from sympy.parsing.sympy_parser import (
                parse_expr,
                standard_transformations,
                implicit_multiplication_application,
            )
            transformations = standard_transformations + (implicit_multiplication_application,)
            expr = parse_expr(
                _normalize_expr(expected),
                transformations=transformations,
                local_dict={"expand": sympy.expand, "factor": sympy.factor},
            )
            # Only expand if the stored expected was itself developed.
            # Otherwise (factored form expected), keep it as-is so the
            # debug "Réponse auto" fills a form that passes polfactor.
            if is_polexpand(expected):
                return str(sympy.expand(expr))
            return str(expr)
        except Exception:
            pass
    return expected


def run_standard(
    active_ans_defs: list,
    replies_by_name: dict[str, str],
) -> tuple[float, list[AnswerResult]]:
    """Vérifie chaque réponse indépendamment, retourne (global_score, results)."""
    results: list[AnswerResult] = []
    weighted_score = 0.0
    total_weight = 0.0

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
                expected=pretty_expected(ans_def.expected, ans_def.answer_type),
                status=check.status,
                detail=check.detail,
            )
        )
        weighted_score += check.score * ans_def.weight
        total_weight += ans_def.weight

    global_score = weighted_score / total_weight if total_weight > 0 else 0.0
    return global_score, results
