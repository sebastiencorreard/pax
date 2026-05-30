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
    """True iff `reply` and `expected` are mathematically equal but list their
    top-level terms in a different order.

    Used only for *plain* litexp (no `polexpand` option) — the "réduire et
    ordonner suivant les puissances décroissantes" family, where WIMS compares
    the rawmath strings literally (`$dd isitemof $good`) so the student's order
    must match the stored canonical (decreasing-power) order. Exercises that
    set `polexpand` (the "développer" family) accept any equivalent ordering and
    must NOT call this.
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
        # Canonicalise each arg via sympify(str()) so `-3*x` (stored as
        # `Mul(-1,3,x)` under evaluate=False) compares against `Mul(-3,x)`.
        r_terms = [str(sympy.sympify(str(t))) for t in reply_parsed.args]
        e_terms = [str(sympy.sympify(str(t))) for t in expected_parsed.args]
        # Same multiset, different sequence → order issue. Different multisets
        # (e.g. `2x+3x` vs `5x`) are a reduction issue (handled by polexpand).
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
        for canon in canon_args:
            _coef, rest = canon.as_coeff_Mul()
            groups.setdefault(rest, []).append(canon)
        def _fmt(term) -> str:
            # Render the *canonical* term (sympify collapses the unevaluated
            # parse, so `-1*4` shows as `-4`). `**` → `^` and drop the explicit
            # `*` of a monomial so it reads like maths: `7*a` → `7a`, `3*x**2`
            # → `3x^2`.
            return str(term).replace("**", "^").replace("*", "")

        for terms in groups.values():
            if len(terms) > 1:
                t1, t2 = _fmt(terms[0]), _fmt(terms[1])
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


def check_numeric(
    reply: str, expected: str, precision: float = 1e-4, comma_is_decimal: bool = True
) -> CheckResult:
    """
    Compare deux nombres avec tolérance relative + absolue.
    Accepte les fractions (1/2), les expressions simples (2*3).
    ``comma_is_decimal`` : voir :func:`_parse_number`.
    """
    try:
        r = _parse_number(reply.strip(), comma_is_decimal)
        e = _parse_number(expected.strip(), comma_is_decimal)
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


def check_jsxgraph(reply: str, expected: str, options: dict | None = None) -> CheckResult:
    """Compare les coordonnées du/des point(s) déplacé(s) à la position attendue.

    `reply` et `expected` suivent le format WIMS jsxgraph : des lignes séparées
    par ``;``, chaque ligne étant les coordonnées d'un point séparées par ``,``
    (ex. ``"7;"`` ou ``"3,5;"``). Chaque coordonnée est comparée numériquement
    avec une tolérance ``1/precision`` (précision WIMS par défaut 10 → 0,1).
    Le score est la fraction de coordonnées dans la tolérance.
    """
    options = options or {}
    m = re.search(r"precision\s*=\s*([\d.]+)", str(options.get("option", "")))
    precision = float(m.group(1)) if m else 10.0
    tol = 1.0 / precision if precision else 0.1

    def _rows(s: str) -> list[str]:
        return [r.strip() for r in s.split(";") if r.strip()]

    exp_rows, rep_rows = _rows(expected), _rows(reply)
    total = ok = 0
    for i, exp_row in enumerate(exp_rows):
        exp_coords = [c.strip() for c in exp_row.split(",") if c.strip()]
        rep_coords = rep_rows[i].split(",") if i < len(rep_rows) else []
        for j, ec in enumerate(exp_coords):
            total += 1
            try:
                if j < len(rep_coords) and abs(float(ec) - float(rep_coords[j].strip())) < tol:
                    ok += 1
            except (ValueError, TypeError):
                pass
    if total == 0:
        return CheckResult(correct=False, score=0.0, method="jsxgraph")
    score = ok / total
    return CheckResult(correct=score == 1.0, score=score, method="jsxgraph")


def _parse_number(s: str, comma_is_decimal: bool = True) -> float:
    """Parse un nombre : entier, décimal, fraction, expression simple.

    ``comma_is_decimal`` (vrai par défaut, locales à virgule) traite la virgule
    comme séparateur décimal — on accepte alors aussi le point (``3,5`` et
    ``3.5`` valent 3,5). En locale à point, la virgule n'est PAS décimale : un
    ``3,5`` n'est pas reconnu comme un nombre (il échoue au parsing).
    """
    s = s.strip()
    if comma_is_decimal:
        s = s.replace(",", ".")
    s = s.replace("^", "**")
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


def check_algexp(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
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
            _normalize_expr(reply, comma_is_decimal),
            transformations=transformations,
            local_dict=local_dict,
        )
        e_expr = parse_expr(
            _normalize_expr(expected, comma_is_decimal),
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
        return _check_algexp_numeric(reply, expected, comma_is_decimal)


def _normalize_expr(expr: str, comma_is_decimal: bool = True) -> str:
    """Normalise une expression OEF/élève pour SymPy.

    ``comma_is_decimal`` (locales à virgule) : une virgule entre deux chiffres
    est un séparateur décimal → convertie en point avant sympify, qui sinon
    lirait ``0,113`` comme un tuple ``(0, 113)``.
    """
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
    # Virgule décimale (locale à virgule) : ``0,113`` → ``0.113``.
    if comma_is_decimal:
        expr = re.sub(r"(?<=\d),(?=\d)", ".", expr)
    return expr


def _check_algexp_numeric(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
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
        r_expr = sympy.sympify(_normalize_expr(reply, comma_is_decimal), locals=_loc)
        e_expr = sympy.sympify(_normalize_expr(expected, comma_is_decimal), locals=_loc)

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


def check_numexp(
    reply: str, expected: str, precision: float = 1e-4, comma_is_decimal: bool = True
) -> CheckResult:
    """
    Évalue les deux expressions numériquement et compare.
    Ex: reply="2+3", expected="5"
    """
    try:
        import sympy

        _loc = _safe_locals()
        # En locale à virgule, ``2,5`` est un décimal : on le convertit avant
        # sympify (qui lirait sinon un tuple). Le point reste accepté.
        r_in = reply.replace(",", ".") if comma_is_decimal else reply
        e_in = expected.replace(",", ".") if comma_is_decimal else expected
        r_val = float(sympy.sympify(_normalize_expr(r_in), locals=_loc))
        e_val = float(sympy.sympify(_normalize_expr(e_in), locals=_loc))
        correct = (
            abs(r_val - e_val) <= precision
            or abs(r_val - e_val) / (abs(e_val) + 1e-12) <= precision
        )
        return CheckResult(
            correct=correct, score=1.0 if correct else 0.0, method="numexp"
        )
    except Exception:
        return check_numeric(reply, expected, precision, comma_is_decimal)


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


def check_fset(
    reply: str, expected: str, precision: float = 1e-4, comma_is_decimal: bool = True
) -> CheckResult:
    """
    Ensemble fini WIMS : ordre non significatif, équivalence numérique
    ou symbolique sur chaque élément (donc -4 == -8/2 == -4.0).

    Désambiguïsation de la virgule (``comma_is_decimal``) : en locale à virgule,
    ``,`` est le séparateur décimal et ``;`` sépare les éléments. La réponse est
    lue de façon **tolérante** : sans ``;``, on essaie à la fois « un seul
    décimal » (``2,5`` → 2,5) et « liste séparée par des virgules » (``2,5`` →
    {2;5}), et on retient l'interprétation qui colle le mieux à l'attendu. En
    locale à point, la virgule n'est qu'un séparateur de liste.
    """

    def equiv(a: str, b: str) -> bool:
        try:
            av = _parse_number(a, comma_is_decimal)
            bv = _parse_number(b, comma_is_decimal)
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

    def count_matches(r_items: list[str], e_items: list[str]) -> int:
        matched = [False] * len(r_items)
        n = 0
        for e in e_items:
            for i, r in enumerate(r_items):
                if matched[i]:
                    continue
                if equiv(r, e):
                    matched[i] = True
                    n += 1
                    break
        return n

    def split_on(s: str, sep: str) -> list[str]:
        return [x.strip() for x in s.split(sep) if x.strip()]

    # Expected is author-written: prefer its ';' if present, else ','.
    e_items = split_on(expected, ";" if ";" in expected else ",")

    # Candidate readings of the reply (see docstring).
    if ";" in reply:
        candidates = [split_on(reply, ";")]
    else:
        candidates = []
        if comma_is_decimal and reply.strip():
            candidates.append([reply.strip()])          # comma = decimal → one element
        candidates.append(split_on(reply, ","))         # comma = list separator

    best_score = -1.0
    mismatch_len = None
    for r_items in candidates:
        if len(r_items) != len(e_items):
            if mismatch_len is None:
                mismatch_len = len(r_items)
            continue
        n = count_matches(r_items, e_items)
        if n == len(e_items):
            return CheckResult(correct=True, score=1.0, method="fset")
        score = n / len(e_items) if e_items else 0.0
        best_score = max(best_score, score)

    if best_score < 0:
        # Every candidate had the wrong cardinality.
        return CheckResult(
            correct=False,
            score=0.0,
            method="fset",
            detail=f"{mismatch_len or 0} valeur(s), {len(e_items)} attendue(s)",
        )
    return CheckResult(correct=False, score=best_score, method="fset")


# ------------------------------------------------------------------ #
# Choix (radio, checkbox, clickfill)                                   #
# ------------------------------------------------------------------ #


def check_radio(reply: str, expected: str) -> CheckResult:
    """Comparaison exacte insensible à la casse et aux espaces."""
    correct = reply.strip().lower() == expected.strip().lower()
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="exact")


def check_clickfill(reply: str, expected: str) -> CheckResult:
    """Compare two drag-compose sequences (comma-joined slot values).

    Order matters; empty slots are ignored. Works for a single-slot clickfill
    too (one item each side).
    """
    def seq(s: str) -> list[str]:
        return [x.strip() for x in s.split(",") if x.strip()]

    correct = seq(reply) == seq(expected)
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="clickfill")


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

    Commas *inside parentheses* are not separators — a right item may itself
    be a coordinate like ``(-1,-2)``. Split with the same paren-aware regex
    the def-engine uses for WIMS lists (`_split_list_items`); a plain
    ``a,b,c`` list (no parens) splits identically to ``str.split(",")``.

    With `partial=True` (WIMS option ``split`` / ``partialscore``), the
    score is the fraction of correctly-placed items. Otherwise it's
    all-or-nothing.
    """
    def _norm(s: str) -> str:
        return re.sub(r"\s+", " ", s).strip()
    r_items = [_norm(x) for x in re.split(r",(?![^(]*\))", reply)]
    e_items = [_norm(x) for x in re.split(r",(?![^(]*\))", expected)]
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


def _split_top_level(s: str, sep: str) -> list[str]:
    """Split `s` on single-char `sep`, only at bracket depth 0."""
    parts: list[str] = []
    depth = 0
    cur: list[str] = []
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth = max(0, depth - 1)
        if ch == sep and depth == 0:
            parts.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    parts.append("".join(cur))
    return parts


def _product_multiset(s: str) -> tuple[str, ...]:
    """Factors of a product ``a*b*c`` as an order-independent sorted multiset,
    spaces stripped (``*`` or ``×`` accepted as the operator)."""
    factors = re.split(r"[*×]", s)
    return tuple(sorted(f.replace(" ", "").lower() for f in factors if f.strip()))


def _find_bracket_blocks(s: str) -> list[str]:
    """Top-level ``[...]`` blocks in `s` (the Apick blocks inside ``Alt:``)."""
    blocks: list[str] = []
    depth = 0
    start: int | None = None
    for i, ch in enumerate(s):
        if ch == "[":
            if depth == 0:
                start = i
            depth += 1
        elif ch == "]":
            depth -= 1
            if depth == 0 and start is not None:
                blocks.append(s[start : i + 1])
                start = None
    return blocks


def _apick_multiset(block: str) -> tuple[str, ...] | None:
    """Parse a WIMS ``[Apick:N,[*],…,op1,…,opN]`` block into its N operands as
    a sorted multiset. ``Apick:N`` and the ``[*]`` separator slots are dropped;
    the rest are the factors the student may give in any order."""
    inner = block.strip()
    if inner.startswith("[") and inner.endswith("]"):
        inner = inner[1:-1]
    items = [it.strip() for it in _split_top_level(inner, ",")]
    if not items or not items[0].lower().startswith("apick:"):
        return None
    ops = [
        it.replace(" ", "").lower()
        for it in items[1:]
        if it.strip() and it.strip() != "[*]"
    ]
    return tuple(sorted(ops)) if ops else None


def check_case(reply: str, expected: str) -> CheckResult:
    """WIMS `case` type: ``expected`` lists alternatives separated by ``|``.
    The reply matches an alternative literally (case/space-insensitive), or —
    for WIMS' ``[Alt:[Apick:N,…]]`` construct (prime factorisation, 1024) — as
    a product whose factor multiset equals an accepted one (order-free). E.g.
    ``5^2*2*7|[Alt:[Apick:3,[*],[*],5^2,2,7],[Apick:4,[*],[*],[*],5,5,2,7]]``
    accepts ``2*5*5*7`` as well as ``5^2*2*7`` in any factor order."""
    reply_norm = reply.strip().lower()
    reply_ms = _product_multiset(reply)

    literal_alts: set[str] = set()
    accepted_ms: list[tuple[str, ...]] = []
    for part in _split_top_level(expected, "|"):
        part = part.strip()
        if not part:
            continue
        m = re.match(r"\[alt:(.*)\]$", part, re.I | re.DOTALL)
        if m:
            for block in _find_bracket_blocks(m.group(1)):
                ms = _apick_multiset(block)
                if ms is not None:
                    accepted_ms.append(ms)
        else:
            literal_alts.add(part.lower())

    correct = reply_norm in literal_alts or (bool(reply_ms) and reply_ms in accepted_ms)
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="case")


def check_default(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
    """OEF `default`: algebraic comparison, fallback to plain text.

    WIMS `anstype/default` runs through Maxima for symbolic equivalence; if
    that fails (or expected is a non-math string), accept exact text match.
    """
    algexp = check_algexp(reply, expected, comma_is_decimal)
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
    lang: str | None = None,
) -> CheckResult:
    """
    Point d'entrée unique. Dispatch vers le bon checker selon le type.

    ``lang`` (langue de l'exercice) décide du séparateur décimal : la virgule
    n'est traitée comme décimale que dans les locales concernées (voir
    ``core/oef/i18n.py``). Défaut : français (virgule décimale).
    """
    from core.oef.i18n import uses_comma_decimal  # noqa: PLC0415

    options = options or {}
    precision = float(options.get("precision", 1e-4))
    comma_is_decimal = uses_comma_decimal(lang)

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
                r = check_answer(answer_type, reply, alt, options, lang)
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
        # Term order: enforced for *plain* litexp only — the "réduire et
        # ordonner suivant les puissances décroissantes" family (reduire1p…),
        # where WIMS compares the rawmath strings literally so the student must
        # match the stored decreasing-power order (`8+11v` rejected for
        # `11v+8`). The `polexpand`/`expand` "développer" family (developperA4…)
        # accepts any equivalent ordering, so it is exempt.
        explicit_expand = "polexpand" in opt_str or "expand" in opt_str
        if (
            answer_type.lower() == "litexp"
            and not explicit_expand
            and _is_term_order_mismatch(reply, expected)
        ):
            return CheckResult(
                correct=False,
                score=0.0,
                method="term_order",
                status="invalid_format",
                detail=_REWRITE_MSG,
            )

    match answer_type.lower():
        case "numeric":
            return check_numeric(reply, expected, precision, comma_is_decimal)
        case "numexp":
            return check_numexp(reply, expected, precision, comma_is_decimal)
        case "algexp" | "litexp" | "formal":
            return check_algexp(reply, expected, comma_is_decimal)
        case "function":
            return check_algexp(reply, expected, comma_is_decimal)
        case "fset":
            return check_fset(reply, expected, precision, comma_is_decimal)
        case "set" | "checkbox":
            return check_set(reply, expected)
        case "radio" | "menu" | "mark":
            return check_radio(reply, expected)
        case "clickfill":
            return check_clickfill(reply, expected)
        case "correspond":
            return check_correspond(reply, expected, partial=bool(options.get("partial")))
        case "jsxgraph":
            return check_jsxgraph(reply, expected, options)
        case "case":
            return check_case(reply, expected)
        case "default" | "auto":
            return check_default(reply, expected, comma_is_decimal)
        case "text":
            return check_text(reply, expected)
        case _:
            _log_unhandled_answer_type(answer_type)
            return check_text(reply, expected)
