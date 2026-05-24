"""
Vérificateurs de réponses par type OEF.
Chaque checker reçoit la réponse de l'élève et la valeur attendue,
et retourne un CheckResult.
"""

from __future__ import annotations
from dataclasses import dataclass
from fractions import Fraction
import logging
import re
import sys

_log = logging.getLogger("pax.answer")
_logged_unhandled_types: set[str] = set()


# Single-letter names that sympy's namespace pre-binds to non-Symbol objects
# (N = numerical-eval function, E = exp(1), I = imaginary unit, O = Order
# class, S = singleton registry, Q = assumption keys, C = legacy). In school
# exercises these are always variables (`N` for un nombre, `E` pour un
# événement, …), so force them to Symbols whenever we hand a string off to
# sympify / parse_expr. Without this, parse_expr('N+16') raises
# `TypeError: unsupported operand type(s) for +: 'function' and 'Integer'`.
def _safe_locals() -> dict:
    import sympy  # noqa: PLC0415
    return {name: sympy.Symbol(name) for name in ("N", "O", "I", "E", "S", "Q", "C")}


def _free_symbols(expr_str: str) -> set[str]:
    """Return the set of free variable names in a math expression string.

    Used to detect when a reply introduces variables the expected answer
    doesn't mention — typically a case mismatch like `z+15` vs `Z+15`.
    Returns an empty set on parse failure (the caller treats "no info"
    as "no problem").
    """
    try:
        import sympy  # noqa: PLC0415
        from sympy.parsing.sympy_parser import (
            implicit_multiplication_application,
            parse_expr,
            standard_transformations,
        )
        transformations = standard_transformations + (
            implicit_multiplication_application,
        )
        expr = parse_expr(
            expr_str.replace("^", "**"),
            transformations=transformations,
            local_dict=_safe_locals(),
        )
        return {str(s) for s in expr.free_symbols}
    except Exception:
        return set()


def _unknown_variables(reply: str, expected: str) -> set[str]:
    """Variables present in `reply` but not in any alternative of `expected`."""
    expected_vars: set[str] = set()
    for alt in _split_top_level_alternatives(expected):
        expected_vars |= _free_symbols(alt)
    reply_vars = _free_symbols(reply)
    return reply_vars - expected_vars


def _is_case_mismatch_only(reply: str, expected: str) -> bool:
    """True iff every variable in `reply` that's absent from `expected`
    has a case-equivalent (lowercase match) variable in `expected`.

    `z+15` against `Z+15` → True  (just a case slip, prompt for retry)
    `X+15` against `Z+15` → False (genuinely wrong variable → wrong answer)
    `z+y` against `Z`     → False (`y` has no case-equivalent in expected)
    """
    expected_vars: set[str] = set()
    for alt in _split_top_level_alternatives(expected):
        expected_vars |= _free_symbols(alt)
    reply_vars = _free_symbols(reply)
    unknown = reply_vars - expected_vars
    if not unknown:
        return False
    expected_lower = {v.lower() for v in expected_vars}
    return all(u.lower() in expected_lower for u in unknown)


# Generic "rewrite please" message reused for all form-mismatch warnings
# (polexpand, polfactor, bad_variable). Mirrors WIMS' single `badform`
# message rather than spelling out the specific failure mode.
_REWRITE_MSG = (
    "La réponse que vous avez donnée n'est pas écrite comme il faut. "
    "Veuillez la réécrire correctement."
)


def _is_term_order_mismatch(reply: str, expected: str) -> bool:
    """True iff `reply` and `expected` are mathematically equal but have
    different top-level term orderings.

    WIMS' `litexp` script compares the rawmath'd strings directly
    (`$dd isitemof $good`), not the canonicalised forms (`algexp` does
    that), so the student's typed order must match the stored
    canonical order. Mirror that for litexp only.
    """
    try:
        import sympy  # noqa: PLC0415
        from sympy.parsing.sympy_parser import (
            implicit_multiplication_application,
            parse_expr,
            standard_transformations,
        )
        T = standard_transformations + (implicit_multiplication_application,)
        loc = _safe_locals()
        reply_parsed = parse_expr(
            reply.replace("^", "**"), transformations=T,
            local_dict=loc, evaluate=False,
        )
        expected_parsed = parse_expr(
            expected.replace("^", "**"), transformations=T,
            local_dict=loc, evaluate=False,
        )
        # Non-equal expressions are normal wrong answers, not an order issue.
        if sympy.expand(reply_parsed - expected_parsed) != 0:
            return False
        # Single-term expressions can't have an order issue.
        if not (reply_parsed.is_Add and expected_parsed.is_Add):
            return False
        # Canonicalise each arg via sympify(str()) so `-3*x` (which
        # parse_expr stores as `Mul(-1,3,x)` with evaluate=False) is
        # compared against `Mul(-3,x)` symmetrically.
        r_terms = [str(sympy.sympify(str(t))) for t in reply_parsed.args]
        e_terms = [str(sympy.sympify(str(t))) for t in expected_parsed.args]
        # Same multiset of terms but different sequence → order issue.
        # Different multisets (e.g. `2x + 3x` vs `5x`) → reduction issue
        # already handled by polexpand, not order.
        if sorted(r_terms) != sorted(e_terms):
            return False
        return r_terms != e_terms
    except Exception:
        return False


def _polexpand_diagnostic(s: str) -> str | None:
    """Returns a French explanation of *why* `s` fails the polexpand
    check, or None when no specific diagnosis is available. Mirrors
    WIMS' `oef/analyse/expandpolynome` output style — currently covers
    only the "termes à combiner" case (its most common warning).
    """
    try:
        import sympy  # noqa: PLC0415
        from sympy.parsing.sympy_parser import (
            implicit_multiplication_application,
            parse_expr,
            standard_transformations,
        )
        T = standard_transformations + (
            implicit_multiplication_application,
        )
        expr = parse_expr(
            s.replace("^", "**"),
            transformations=T,
            local_dict=_safe_locals(),
            evaluate=False,
        )
        if not expr.is_Add:
            return None
        # Canonicalise each top-level term so positives and negatives
        # have the same shape (see is_polexpand for why sympify(str())
        # is needed here too).
        canon_args = [sympy.sympify(str(a)) for a in expr.args]
        # Group terms by their symbolic part (coefficient stripped).
        # Two terms in the same group are combinable → not reduced.
        groups: dict = {}
        for orig, canon in zip(expr.args, canon_args):
            _coef, rest = canon.as_coeff_Mul()
            groups.setdefault(rest, []).append(orig)
        for terms in groups.values():
            if len(terms) > 1:
                # Render the first two as plain text — sympy's str() uses
                # `*` like WIMS does in this very message.
                t1, t2 = str(terms[0]).replace("**", "^"), str(terms[1]).replace("**", "^")
                return (
                    f"Votre expression n'est pas réduite. "
                    f"Les termes {t1} et {t2} se simplifient."
                )
        return None
    except Exception:
        return None


def _log_unhandled_answer_type(answer_type: str) -> None:
    """Log an answer type that falls through to text-match (likely unsupported).
    Deduped by name across the process lifetime so the log stays readable."""
    key = answer_type.lower()
    if key in _logged_unhandled_types:
        return
    _logged_unhandled_types.add(key)
    msg = f"[ANSWER-FALLBACK] type={answer_type!r} → check_text"
    _log.warning(msg)
    print(msg, file=sys.stderr, flush=True)


@dataclass
class CheckResult:
    correct: bool
    score: float  # 0.0 à 1.0
    method: str  # "numeric", "sympy", "exact", ...
    detail: str = ""  # message optionnel pour le feedback
    status: str = "ok"  # "ok", "invalid_format"


def is_polexpand(s: str) -> bool:
    """Vérifie si une expression est sous forme développée ET réduite
    (somme de monômes distincts par degré/symbole)."""
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
        expr = parse_expr(
            s.replace("^", "**"),
            transformations=transformations,
            evaluate=False,
            local_dict=_safe_locals(),
        )

        def is_monomial(e):
            if e.is_Number or e.is_Symbol:
                return True
            if e.is_Pow:
                return e.base.is_Symbol and e.exp.is_Number
            if e.is_Mul:
                return all(is_monomial(arg) for arg in e.args)
            return False

        # 1. Structurellement développé : somme de monômes
        if expr.is_Add:
            if not all(is_monomial(arg) for arg in expr.args):
                return False
        elif not is_monomial(expr):
            return False

        # 2. Réduit : combiner les termes similaires (sans factoriser
        # ni appliquer d'autres simplifications) et vérifier que le
        # nombre de termes top-level n'a pas changé.
        # Pourquoi `sympify(str(expr))` plutôt que :
        #   - `sympy.simplify` : factorise (`40u² + 30u` → `10u(4u+3)`,
        #     2→1 terme, faux positif sur les expressions réduites).
        #   - `expr.func(*expr.args)` : ne re-canonicalise pas les Mul
        #     internes, donc `-63x - 6x` (= `Mul(-1,63,x) + Mul(-1,6,x)`)
        #     n'est pas combiné — alors que `+63x + 6x` l'est. Asymétrie
        #     entre termes positifs et négatifs construits avec
        #     evaluate=False.
        #   - `sympy.expand` : étrangement ne combine pas non plus les
        #     like terms d'un Add evaluate=False.
        # sympify(str) re-parse depuis zéro avec evaluate=True : combine
        # les like terms (positifs OU négatifs) sans factoriser.
        def term_count(e):
            return len(e.args) if e.is_Add else 1

        return term_count(expr) == term_count(sympy.sympify(str(expr)))
    except Exception:
        return True  # En cas d'erreur de parsing, on laisse passer au checker normal


# ------------------------------------------------------------------ #
# Numérique                                                            #
# ------------------------------------------------------------------ #


def check_numeric(reply: str, expected: str, precision: float = 1e-4) -> CheckResult:
    """
    Compare deux nombres avec tolérance relative + absolue.
    Accepte les fractions (1/2), les expressions simples (2*3).
    """
    try:
        r = _parse_number(reply.strip())
        e = _parse_number(expected.strip())
    except (ValueError, ZeroDivisionError, SyntaxError):
        return CheckResult(
            correct=False,
            score=0.0,
            method="numeric",
            detail="Réponse non reconnue comme un nombre",
        )

    abs_err = abs(r - e)
    rel_err = abs_err / (abs(e) + 1e-12)
    correct = abs_err <= precision or rel_err <= precision

    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="numeric")


def _parse_number(s: str) -> float:
    """Parse un nombre : entier, décimal, fraction, expression simple."""
    s = s.replace(",", ".").replace("^", "**").strip()
    # Fraction explicite ex: 3/4
    if re.fullmatch(r"-?\d+\s*/\s*-?\d+", s):
        return float(Fraction(s.replace(" ", "")))
    # Expression arithmétique simple (pas d'appel de fonction)
    if re.fullmatch(r"[\d\s\+\-\*\/\.\(\)\^]+", s):
        return float(eval(s, {"__builtins__": {}}))
    raise ValueError(f"Impossible de parser: {s!r}")


# ------------------------------------------------------------------ #
# Expression algébrique — SymPy                                        #
# ------------------------------------------------------------------ #


def check_algexp(reply: str, expected: str) -> CheckResult:
    """
    Compare deux expressions algébriques via SymPy.
    Correct si la différence se simplifie à 0.
    """
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

        local_dict = {
            **_safe_locals(),
            "expand": sympy.expand,
            "factor": sympy.factor,
            "simplify": sympy.simplify,
        }
        r_expr = parse_expr(
            _normalize_expr(reply),
            transformations=transformations,
            local_dict=local_dict,
        )
        e_expr = parse_expr(
            _normalize_expr(expected),
            transformations=transformations,
            local_dict=local_dict,
        )

        diff = sympy.simplify(sympy.expand(r_expr) - sympy.expand(e_expr))
        correct = diff == 0

        return CheckResult(
            correct=correct, score=1.0 if correct else 0.0, method="sympy"
        )

    except Exception:
        # Fallback : comparaison numérique en plusieurs points
        return _check_algexp_numeric(reply, expected)


def _normalize_expr(expr: str) -> str:
    """Normalise une expression OEF/élève pour SymPy."""
    expr = expr.strip()
    # Exposants LaTeX ^{n} -> ^n
    expr = re.sub(r"\^\{(.*?)\}", r"^\1", expr)
    # Exposants Unicode → notation ^
    superscripts = {
        "⁰": "0",
        "¹": "1",
        "²": "2",
        "³": "3",
        "⁴": "4",
        "⁵": "5",
        "⁶": "6",
        "⁷": "7",
        "⁸": "8",
        "⁹": "9",
    }
    for sup, digit in superscripts.items():
        expr = expr.replace(sup, f"^{digit}")
    expr = expr.replace("^", "**")
    expr = expr.replace("\\times", "*")
    expr = expr.replace("\\cdot", "*")
    # Supprime les espaces autour des opérateurs
    expr = re.sub(r"\s+", "", expr)
    return expr


def _check_algexp_numeric(reply: str, expected: str) -> CheckResult:
    """
    Fallback : évalue les deux expressions en plusieurs points et compare.
    Fonctionne pour des polynômes en x, y.
    """
    try:
        import sympy

        x, y, z = sympy.symbols("x y z")
        test_points = [
            {x: 1, y: 2, z: 3},
            {x: -1, y: 3, z: -2},
            {x: 2, y: -1, z: 1},
            {x: 0.5, y: 1.5, z: -0.5},
        ]
        _loc = _safe_locals()
        r_expr = sympy.sympify(_normalize_expr(reply), locals=_loc)
        e_expr = sympy.sympify(_normalize_expr(expected), locals=_loc)

        for pt in test_points:
            r_val = complex(r_expr.subs(pt))
            e_val = complex(e_expr.subs(pt))
            if abs(r_val - e_val) > 1e-6:
                return CheckResult(correct=False, score=0.0, method="numeric_fallback")

        return CheckResult(correct=True, score=1.0, method="numeric_fallback")
    except Exception:
        return CheckResult(
            correct=False,
            score=0.0,
            method="error",
            detail="Impossible de vérifier l'expression",
        )


# ------------------------------------------------------------------ #
# Expression numérique (numexp)                                        #
# ------------------------------------------------------------------ #


def check_numexp(reply: str, expected: str, precision: float = 1e-4) -> CheckResult:
    """
    Évalue les deux expressions numériquement et compare.
    Ex: reply="2+3", expected="5"
    """
    try:
        import sympy

        _loc = _safe_locals()
        r_val = float(sympy.sympify(_normalize_expr(reply), locals=_loc))
        e_val = float(sympy.sympify(_normalize_expr(expected), locals=_loc))
        correct = (
            abs(r_val - e_val) <= precision
            or abs(r_val - e_val) / (abs(e_val) + 1e-12) <= precision
        )
        return CheckResult(
            correct=correct, score=1.0 if correct else 0.0, method="numexp"
        )
    except Exception:
        return check_numeric(reply, expected, precision)


# ------------------------------------------------------------------ #
# Ensemble (set)                                                       #
# ------------------------------------------------------------------ #


def check_set(reply: str, expected: str) -> CheckResult:
    """
    Compare deux ensembles de valeurs (séparées par des virgules ou des ;).
    Ordre non significatif.
    """

    def parse_set(s: str) -> set:
        sep = ";" if ";" in s else ","
        return {x.strip().lower() for x in s.split(sep) if x.strip()}

    r_set = parse_set(reply)
    e_set = parse_set(expected)

    if r_set == e_set:
        return CheckResult(correct=True, score=1.0, method="set")

    # Score partiel : proportion d'éléments corrects
    intersection = r_set & e_set
    score = len(intersection) / max(len(e_set), 1) if e_set else 0.0
    return CheckResult(correct=False, score=score, method="set")


def check_fset(reply: str, expected: str, precision: float = 1e-4) -> CheckResult:
    """
    Ensemble fini WIMS : ordre non significatif, équivalence numérique
    ou symbolique sur chaque élément (donc -4 == -8/2 == -4.0).
    """

    def split_items(s: str) -> list[str]:
        sep = ";" if ";" in s else ","
        return [x.strip() for x in s.split(sep) if x.strip()]

    r_items = split_items(reply)
    e_items = split_items(expected)

    if len(r_items) != len(e_items):
        return CheckResult(
            correct=False,
            score=0.0,
            method="fset",
            detail=f"{len(r_items)} valeur(s), {len(e_items)} attendue(s)",
        )

    def equiv(a: str, b: str) -> bool:
        try:
            av = _parse_number(a)
            bv = _parse_number(b)
            return (
                abs(av - bv) <= precision
                or abs(av - bv) / (abs(bv) + 1e-12) <= precision
            )
        except (ValueError, ZeroDivisionError, SyntaxError):
            pass
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
            _loc = _safe_locals()
            ra = parse_expr(_normalize_expr(a), transformations=transformations, local_dict=_loc)
            rb = parse_expr(_normalize_expr(b), transformations=transformations, local_dict=_loc)
            return sympy.simplify(ra - rb) == 0
        except Exception:
            return a.strip().lower() == b.strip().lower()

    matched = [False] * len(r_items)
    n_correct = 0
    for e in e_items:
        for i, r in enumerate(r_items):
            if matched[i]:
                continue
            if equiv(r, e):
                matched[i] = True
                n_correct += 1
                break

    if n_correct == len(e_items):
        return CheckResult(correct=True, score=1.0, method="fset")
    return CheckResult(correct=False, score=n_correct / len(e_items), method="fset")


# ------------------------------------------------------------------ #
# Choix (radio, checkbox, clickfill)                                   #
# ------------------------------------------------------------------ #


def check_radio(reply: str, expected: str) -> CheckResult:
    """Comparaison exacte insensible à la casse et aux espaces."""
    correct = reply.strip().lower() == expected.strip().lower()
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="exact")


def check_text(reply: str, expected: str) -> CheckResult:
    """Comparaison de texte insensible à la casse."""
    correct = reply.strip().lower() == expected.strip().lower()
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="text")


def check_correspond(reply: str, expected: str, partial: bool = False) -> CheckResult:
    """Correspondance bijective.

    `reply` and `expected` are both ``,``-separated lists of right-column
    items in the user-chosen / correct order. The j-th reply item is
    compared to the j-th expected item by whitespace-normalised text
    equality (matches WIMS' `$g_ notsametext $r_`).

    With `partial=True` (WIMS option ``split`` / ``partialscore``), the
    score is the fraction of correctly-placed items. Otherwise it's
    all-or-nothing.
    """
    def _norm(s: str) -> str:
        return re.sub(r"\s+", " ", s).strip()
    r_items = [_norm(x) for x in reply.split(",")]
    e_items = [_norm(x) for x in expected.split(",")]
    if len(r_items) != len(e_items) or not e_items:
        return CheckResult(correct=False, score=0.0, method="correspond")
    n_correct = sum(1 for r, e in zip(r_items, e_items) if r == e)
    if n_correct == len(e_items):
        return CheckResult(correct=True, score=1.0, method="correspond")
    if partial:
        return CheckResult(
            correct=False,
            score=n_correct / len(e_items),
            method="correspond_partial",
        )
    return CheckResult(correct=False, score=0.0, method="correspond")


def check_case(reply: str, expected: str) -> CheckResult:
    """WIMS `case` type: ``expected`` lists alternatives separated by ``|``;
    the reply matches if it equals any alternative (case- and space-insensitive)."""
    reply_norm = reply.strip().lower()
    alternatives = [alt.strip().lower() for alt in expected.split("|") if alt.strip()]
    correct = reply_norm in alternatives
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="case")


def check_default(reply: str, expected: str) -> CheckResult:
    """OEF `default`: algebraic comparison, fallback to plain text.

    WIMS `anstype/default` runs through Maxima for symbolic equivalence; if
    that fails (or expected is a non-math string), accept exact text match.
    """
    algexp = check_algexp(reply, expected)
    if algexp.correct:
        return CheckResult(correct=True, score=1.0, method="default_algexp")
    text = check_text(reply, expected)
    if text.correct:
        return CheckResult(correct=True, score=1.0, method="default_text")
    return CheckResult(correct=False, score=0.0, method="default")


# ------------------------------------------------------------------ #
# Dispatcher principal                                                  #
# ------------------------------------------------------------------ #


def _split_top_level_alternatives(expected: str) -> list[str]:
    """Split `expected` at top-level commas only.

    WIMS' litexp/algexp scripts iterate over `replygood` items split by
    comma (`!itemcnt $good`), so an expected like ``Z+15,15+Z`` means
    either form is accepted. We must keep commas inside parentheses
    intact (e.g. function arguments like ``f(x,y)``).
    """
    parts: list[str] = []
    depth = 0
    current: list[str] = []
    for ch in expected:
        if ch in "([{":
            depth += 1
            current.append(ch)
        elif ch in ")]}":
            depth -= 1
            current.append(ch)
        elif ch == "," and depth == 0:
            parts.append("".join(current).strip())
            current = []
        else:
            current.append(ch)
    if current:
        parts.append("".join(current).strip())
    return [p for p in parts if p]


def check_answer(
    answer_type: str,
    reply: str,
    expected: str,
    options: dict | None = None,
) -> CheckResult:
    """
    Point d'entrée unique. Dispatch vers le bon checker selon le type.
    """
    options = options or {}
    precision = float(options.get("precision", 1e-4))

    # Handle default value if reply is empty
    if not reply.strip():
        opt_str = str(options.get("option", "")).lower()
        if "default=vide" in opt_str:
            return CheckResult(correct=True, score=1.0, method="default_vide")

    # Multi-good: if expected lists several acceptable answers, treat as
    # alternatives and accept the reply if it matches any of them. Skip for
    # types where comma is part of the answer syntax (sets, radio/case lists).
    if answer_type.lower() in ("algexp", "litexp", "formal", "function", "default", "auto", "numeric", "numexp"):
        alternatives = _split_top_level_alternatives(expected)
        if len(alternatives) > 1:
            last: CheckResult | None = None
            for alt in alternatives:
                r = check_answer(answer_type, reply, alt, options)
                if r.correct:
                    return r
                last = r
            return last or CheckResult(correct=False, score=0.0, method="default")

    opt_str = str(options.get("option", "")).lower()
    
    # Auto-detect whether the expected answer constrains the form (developed
    # vs factored). Mirrors WIMS' litexp/algexp checkers, which reject a
    # mathematically-equal reply that doesn't match the form the author stored.
    requires_expand = "polexpand" in opt_str or "expand" in opt_str
    requires_factor = "polfactor" in opt_str
    if (
        not requires_expand
        and not requires_factor
        and answer_type.lower() in ("algexp", "default", "auto", "litexp", "formal")
        and any(c.isalpha() for c in expected)
    ):
        if is_polexpand(expected):
            requires_expand = True
        else:
            requires_factor = True

    # Pre-check polexpand if requested
    if requires_expand:
        if reply.strip() and not is_polexpand(reply):
            return CheckResult(
                correct=False,
                score=0.0,
                method="polexpand",
                status="invalid_format",
                detail=_polexpand_diagnostic(reply) or _REWRITE_MSG,
            )

    # Pre-check polfactor if requested
    if requires_factor:
        if reply.strip() and is_polexpand(reply):
            return CheckResult(
                correct=False,
                score=0.0,
                method="polfactor",
                status="invalid_format",
                detail=_REWRITE_MSG,
            )

    # Form-mismatch pre-checks for algebraic types.
    if reply.strip() and answer_type.lower() in (
        "algexp", "default", "auto", "litexp", "formal", "function"
    ):
        # Case-slip: `z+15` vs `Z+15` warns. Genuinely wrong variables
        # (`X+15` vs `Z+15`) fall through to the normal check.
        if _is_case_mismatch_only(reply, expected):
            return CheckResult(
                correct=False,
                score=0.0,
                method="bad_variable",
                status="invalid_format",
                detail=_REWRITE_MSG,
            )
        # Term-order: `litexp` only. WIMS' algexp pipes both sides
        # through `print(maxima ...)` (`$t2 isitemof $t1`) which
        # canonicalises the order; litexp compares the rawmath strings
        # directly (`$dd isitemof $good`), so the student's typed order
        # must match the stored canonical order. develop.fr/bin3 (algexp)
        # accepts any equivalent ordering; reduire1..5 (litexp) doesn't.
        if answer_type.lower() == "litexp" and _is_term_order_mismatch(reply, expected):
            return CheckResult(
                correct=False,
                score=0.0,
                method="term_order",
                status="invalid_format",
                detail=_REWRITE_MSG,
            )

    match answer_type.lower():
        case "numeric":
            return check_numeric(reply, expected, precision)
        case "numexp":
            return check_numexp(reply, expected, precision)
        case "algexp" | "litexp" | "formal":
            return check_algexp(reply, expected)
        case "function":
            return check_algexp(reply, expected)
        case "fset":
            return check_fset(reply, expected, precision)
        case "set":
            return check_set(reply, expected)
        case "radio" | "menu" | "clickfill" | "mark":
            return check_radio(reply, expected)
        case "correspond":
            return check_correspond(reply, expected, partial=bool(options.get("partial")))
        case "case":
            return check_case(reply, expected)
        case "default" | "auto":
            return check_default(reply, expected)
        case "text":
            return check_text(reply, expected)
        case _:
            _log_unhandled_answer_type(answer_type)
            return check_text(reply, expected)
