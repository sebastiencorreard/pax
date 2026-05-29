"""Stratégie standard : vérification réponse par réponse via checkers.py."""

from __future__ import annotations

from core.answer.checkers import check_answer, is_polexpand, _normalize_expr, _safe_locals
from core.answer.schemas import AnswerResult


def pretty_expected(expected: str, answer_type: str) -> str:
    """Retourne la correction sous forme lisible, en préservant la forme
    voulue par l'auteur : développée si l'expected était développé,
    factorisée sinon."""
    if answer_type.lower() in ("algexp", "litexp", "formal") and is_polexpand(expected):
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
                local_dict={**_safe_locals(), "expand": sympy.expand, "factor": sympy.factor},
            )
            return str(sympy.expand(expr))
        except Exception:
            pass
    # Non-developed (factored, etc.) or non-polynomial: keep the stored form.
    # parse_expr's auto-evaluation would distribute Mul (5*(6v-5) → 30v-25)
    # and defeat the polfactor intent.
    return expected


def run_standard(
    active_ans_defs: list,
    replies_by_name: dict[str, str],
    lang: str | None = None,
) -> tuple[float, list[AnswerResult]]:
    """Vérifie chaque réponse indépendamment, retourne (global_score, results).

    ``lang`` (langue de l'exercice) est transmis aux checkers pour le séparateur
    décimal locale-aware (voir ``core/oef/i18n.py``).
    """
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
            lang=lang,
        )
        # `mark` replies are 1-based positions; the feedback should show the
        # choice *labels*, not the numbers. Map both the student's reply and the
        # expected position through the choice list.
        display_reply = reply_value
        display_expected = pretty_expected(ans_def.expected, ans_def.answer_type)
        if ans_def.answer_type.lower() == "mark":
            choices = ans_def.options.get("choices") or []

            def _label(pos: str) -> str:
                try:
                    i = int(pos)
                except (ValueError, TypeError):
                    return pos
                return choices[i - 1] if 1 <= i <= len(choices) else pos

            display_reply = _label(reply_value)
            display_expected = _label(ans_def.expected)
        results.append(
            AnswerResult(
                input_name=ans_def.input_name,
                correct=check.correct,
                score=check.score,
                method=check.method,
                reply=display_reply,
                expected=display_expected,
                status=check.status,
                detail=check.detail,
            )
        )
        weighted_score += check.score * ans_def.weight
        total_weight += ans_def.weight

    global_score = weighted_score / total_weight if total_weight > 0 else 0.0
    return global_score, results
