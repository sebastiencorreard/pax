"""Stratégie ?analyze : vérification via :postdef + :test + feedback."""

from __future__ import annotations

from core.answer.schemas import AnswerResult
from core.answer.strategies.standard import pretty_expected


def run_analyze(
    rendered,
    active_ans_defs: list,
    replies_by_name: dict[str, str],
    seed: int,
) -> tuple[float, list[AnswerResult]]:
    """Exécute :postdef + :test avec les réponses élève, retourne (global_score, results).

    Les réponses sont injectées comme valN dans le contexte avant :postdef.
    """
    from core.oef.def_engine import check_analyze

    analyze_replies = {
        int(a.options["analyze_var"][3:]): replies_by_name.get(a.input_name, "").strip()
        for a in active_ans_defs
        if a.answer_type == "analyze" and "analyze_var" in a.options
    }
    condtest, weights = check_analyze(
        ev_ctx=rendered.check_sections["ctx"],
        postdef_instructions=rendered.check_sections["postdef"],
        test_instructions=rendered.check_sections["test"],
        analyze_replies=analyze_replies,
        seed=seed,
    )
    # Weighted score (condweightN); falls back to a plain average when all
    # weights are 1. Correct on every condition → 1.0.
    total_w = sum(weights.values())
    if total_w > 0:
        global_score = sum(condtest[k] * weights[k] for k in condtest) / total_w
    else:
        global_score = 0.0

    results: list[AnswerResult] = []
    for ans_def in active_ans_defs:
        reply_value = replies_by_name.get(ans_def.input_name, "").strip()
        results.append(
            AnswerResult(
                input_name=ans_def.input_name,
                correct=(global_score == 1.0),
                score=global_score,
                method="analyze",
                reply=reply_value,
                expected=pretty_expected(ans_def.expected, ans_def.answer_type),
            )
        )
    return global_score, results


def run_feedback(
    rendered,
    active_ans_defs: list,
    replies_by_name: dict[str, str],
    results: list[AnswerResult],
    seed: int,
) -> str | None:
    """Exécute :feedback et retourne le HTML, ou None si absent."""
    if not (rendered.check_sections and "feedback" in rendered.check_sections):
        return None

    from core.oef.def_engine import render_feedback

    analyze_replies = {
        int(a.options["analyze_var"][3:]): replies_by_name.get(a.input_name, "").strip()
        for a in active_ans_defs
        if a.answer_type == "analyze" and "analyze_var" in a.options
    } or None

    return render_feedback(
        ev_ctx=rendered.check_sections["ctx"],
        postdef_instructions=rendered.check_sections["postdef"],
        test_instructions=rendered.check_sections["test"],
        feedback_instructions=rendered.check_sections["feedback"],
        replies_by_name=replies_by_name,
        results=results,
        seed=seed,
        analyze_replies=analyze_replies,
    )
