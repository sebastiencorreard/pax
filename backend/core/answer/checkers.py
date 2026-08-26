"""
Vérificateurs de réponses par type OEF.
Chaque checker reçoit la réponse de l'élève et la valeur attendue,
et retourne un CheckResult.
"""

from __future__ import annotations
from dataclasses import dataclass
from fractions import Fraction
import logging
import math
import re
import sys
import unicodedata

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

# Réponse juste « à la précision près » : proche de la bonne valeur mais pas
# assez précise (deuxième passage WIMS à sqrt(precision) → crédit partiel).
_POOR_PRECISION_MSG = (
    "Votre réponse est presque juste, mais pas assez précise."
)

# `\computeanswer{no}` : l'élève doit fournir la valeur numérique calculée, pas
# une expression à évaluer (`5*5` refusé pour `25`).
_COMPUTE_MSG = (
    "Donnez le résultat sous forme d'un nombre, pas d'un calcul à effectuer."
)

# equation : `eqsign=yes` (défaut) exige une vraie équation, signe « = » compris
# — WIMS rend `NaN badform` avant même de comparer.
_EQSIGN_MSG = (
    "Donnez une équation complète, avec le signe « = »."
)

# numexp : la fraction doit être irréductible (WIMS `noreduced`).
_NUMEXP_REDUCE_MSG = "Écrivez la fraction sous sa forme irréductible."
# numexp : mélange fraction + décimal interdit (WIMS `badform`).
_NUMEXP_BADFORM_MSG = (
    "N'utilisez pas à la fois une barre de fraction et une virgule décimale."
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


# Alias historiques de `oef/replytype.proc` (`rt_names` → `rt_types`). WIMS les
# traduit avant tout dispatch : un exercice qui déclare `number` veut `numeric`.
# Noter `text` → `case`, et non une comparaison de texte : `case` sait lire les
# écritures alternatives séparées par `|`.
_RT_ALIASES = {
    "auto": "default",
    "coordinate": "coord",
    "coordinates": "coord",
    "corresp": "correspond",
    "correspondance": "correspond",
    "expalg": "algexp",
    "link": "click",
    "number": "numeric",
    "ranges": "range",
    "select": "menu",
    "sigunit": "sigunits",
    "text": "case",
    "unit": "units",
    "wordcomp": "textcomp",
}

# Les types de réponse qui existent réellement chez WIMS — `rt_all` de
# `replytype.proc`, complété des « new types » que le même fichier dit ne plus
# avoir à déclarer (« just put a line `!set anstype=yes` in the input file »),
# soit un fichier par type dans `wims/public_html/scripts/anstype/`. Régénérer
# par : `ls wims/public_html/scripts/anstype/ | grep -vE '\.(input|inc|after|css|md)$'`.
#
# Cette liste ne dit pas ce que PAX sait faire, mais ce que WIMS connaît : elle
# sépare le type *inventé par un auteur* (que WIMS ramène à `default`) du type
# *réel non encore porté* (dette identifiée, tracée par `[ANSWER-FALLBACK]`).
_WIMS_KNOWN_TYPES = frozenset({
    "algexp", "aset", "atext", "case", "checkbox", "chembrut", "chemclick",
    "chemdraw", "chemeq", "chemformula", "chemformula_analysis", "chessgame",
    "chset", "click", "clickfill", "clicktile", "clock", "code", "complex",
    "compose", "coord", "correspond", "crossword", "default", "dragfill",
    "draw", "equation", "flashcard", "formal", "fset", "function", "geogebra",
    "geogebra_translation", "imgcomp", "javacurve", "jmolclick", "jsxgraph",
    "jsxgraphcurve", "keyboard", "litexp", "mark", "matrix", "menu",
    "multidraw", "multipleclick", "nocase", "numeric", "numexp", "puzzle",
    "radio", "range", "raw", "reorder", "set", "sigunits", "symtext",
    "textcomp", "time", "units", "vector", "wlist",
})

# Un module peut définir ses propres types, et `replytype.proc` les cherche
# avant de conclure : `!readproc anstype/<type>.input` résout d'abord dans le
# module. Ceux du corpus, relevés par
#
#   find ressources -path '*/anstype/*' -type f ! -name '*.input'
#
# et retenus seulement s'ils portent bien `!set anstype=yes` — sans quoi le C
# les ramènerait à `default`. Ce ne sont donc pas des noms inventés : leur
# checker existe, il n'est simplement pas encore porté. `oefforpython` redéfinit
# même `vector` pour son propre compte, nuance que PAX ne gère pas encore : le
# checker du cœur s'applique à tous.
_MODULE_ANSTYPES = frozenset({
    "runcode", "js2wims1", "draft", "autoeval", "vector", "reaction",
    "numexp2", "jsxgraphobjet",
})


def normalize_replytype(answer_type: str) -> str:
    """Nom de type canonique, façon ``oef/replytype.proc``.

    Le C procède dans cet ordre, et l'ordre compte :

        rt_1=!positionof item $(replytype$i) in $rt_names
        !if $rt_1 != $empty and $rt_1 > 0
          replytype$i=!item $rt_1 of $rt_types
        !default replytype$i=default
        replytype$i=!word 1 of $(replytype$i)

    D'où : l'alias d'abord, puis le **type vide qui devient `default`** — c'est
    la réponse au type vide de 4 exercices du corpus —, puis le **premier mot
    seulement**, si bien qu'un `default nonstop` reste un `default`.

    Le nettoyage alphanumérique du C (`!text select abcdef… in`) n'est appliqué
    qu'aux noms qu'il ne reconnaît pas, comme lui, et sert surtout à écarter les
    restes de variables non substituées (`$(val11[])menu`).
    """
    t = (answer_type or "").strip().lower()
    t = _RT_ALIASES.get(t, t)
    if not t:
        return "default"
    t = t.split()[0] if t.split() else "default"
    if t in _WIMS_KNOWN_TYPES or t in _MODULE_ANSTYPES:
        return t
    cleaned = re.sub(r"[^a-z0-9]", "", t)
    return cleaned or "default"


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

# Précision WIMS par défaut pour les comparaisons numériques. WIMS stocke
# `wims_compare_precision` = `\precision{M}` de l'OEF (var.prep : borné entre
# 20 et 1e8, défaut 10000). Contrairement à une tolérance, M est *grand* : plus
# M est grand, plus la comparaison est stricte (tolérance relative ≈ 2/M).
WIMS_DEFAULT_PRECISION = 10000.0


def _wims_has_compound_arith(reply: str, comma_is_decimal: bool = True) -> bool:
    """True si ``reply`` est une expression arithmétique composée, à rejeter
    quand ``\\computeanswer{no}`` (l'élève doit donner la valeur calculée).

    Reproduit ``anstype/numeric`` : on retire le signe de tête puis on rejette
    si l'un de ``+ - * ^ (`` apparaît, ou à la fois ``.`` et ``/`` (fraction de
    décimaux). Une fraction simple d'entiers (``3/4``) et un décimal (``2.5``)
    restent acceptés. En locale à virgule, ``,`` est d'abord normalisé en ``.``
    comme le fait WIMS avant le test."""
    s = reply.strip()
    if not s:
        return False
    if comma_is_decimal:
        s = s.replace(",", ".")
    # Notation scientifique (`3.34e-26`) : un nombre, pas un calcul — le `-` de
    # l'exposant ne doit pas la faire passer pour une expression composée.
    if re.fullmatch(r"[+-]?\d+(?:\.\d+)?[eE][+-]?\d+", s):
        return False
    if s[0] in "+-":
        s = s[1:]
    if any(op in s for op in ("+", "-", "*", "^", "(")):
        return True
    return "." in s and "/" in s


def _wims_num_equal(d1: float, d2: float, prec: float) -> bool:
    """Égalité numérique WIMS (``compare.c``) : deux réels sont égaux ssi
    ``|d1-d2|*prec <= |d1+d2| + 1/prec``. ``prec`` est la précision WIMS
    (grand entier, ≈ inverse de la tolérance relative)."""
    diff = abs(d1 - d2) * prec
    s = abs(d1 + d2)
    if 0 < prec < 1e10:
        s += 1.0 / prec
    return s >= diff


def check_numeric(
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
    absolute: bool = False,
) -> CheckResult:
    """
    Compare deux nombres avec la sémantique de précision WIMS (``anstype/numeric``).
    Accepte les fractions (1/2), les expressions simples (2*3).
    ``comma_is_decimal`` : voir :func:`_parse_number`.

    ``precision`` est la précision WIMS (grand entier, défaut 10000), *pas* une
    tolérance. Deux passages, comme WIMS :

    - à ``precision`` : réponse exacte → correct, score 1.0 ;
    - sinon à ``sqrt(precision)`` (comparaison relâchée) → « bonne à la précision
      près » : score partiel 0.5, ``correct=False`` (``precgood`` de WIMS).

    Avec l'option ``absolute``, WIMS compare la différence absolue :
    ``precision*|test-good| < 1`` (correct) ou ``< 10`` (partiel).
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

    if absolute:
        diff = abs(r - e)
        if precision * diff < 1:
            return CheckResult(correct=True, score=1.0, method="numeric")
        if precision * diff < 10:
            return CheckResult(correct=False, score=0.5, method="numeric",
                               detail=_POOR_PRECISION_MSG)
        return CheckResult(correct=False, score=0.0, method="numeric")

    if _wims_num_equal(r, e, precision):
        return CheckResult(correct=True, score=1.0, method="numeric")
    if _wims_num_equal(r, e, math.sqrt(precision)):
        return CheckResult(correct=False, score=0.5, method="numeric",
                           detail=_POOR_PRECISION_MSG)
    return CheckResult(correct=False, score=0.0, method="numeric")


def _split_value_unit(s: str) -> tuple[str | None, str]:
    """Split ``"7.7 m/s"`` / ``"7.7m/s"`` into ``("7.7", "m/s")``.

    The value is a leading signed decimal or integer fraction; everything after
    is the unit. Returns ``(None, "")`` when no leading number is found.
    """
    # Valeur : décimal avec exposant scientifique optionnel (`3.34e-26`), ou
    # fraction d'entiers. L'exposant fait partie de la VALEUR, pas de l'unité.
    m = re.match(
        r"^\s*([+-]?\d+(?:[.,]\d+)?(?:[eE][+-]?\d+)?|[+-]?\d+\s*/\s*\d+)\s*(.*)$",
        s.strip(), re.DOTALL,
    )
    if not m:
        return None, ""
    return m.group(1).strip(), m.group(2).strip()


def _normalize_unit(u: str) -> str:
    """Normalise a unit string for comparison: drop whitespace, unify the
    multiplication dot. (``"m / s"`` → ``"m/s"``; case is significant — m≠M.)"""
    u = re.sub(r"\s+", "", u)
    return u.replace("·", "*").replace("⋅", "*").replace("×", "*")


# Symboles d'unités → nom sympy.physics.units. `L`/`l` = litre.
_UNIT_BASE = {
    "m": "meter", "g": "gram", "s": "second", "L": "liter", "l": "liter",
    "mol": "mole", "N": "newton", "J": "joule", "Pa": "pascal", "W": "watt",
    "V": "volt", "A": "ampere", "K": "kelvin", "Hz": "hertz", "C": "coulomb",
    "F": "farad", "Ohm": "ohm", "Ω": "ohm", "h": "hour", "min": "minute",
    "mn": "minute", "°": "degree", "deg": "degree", "rad": "radian",
    "bar": "bar", "eV": "electronvolt",
}
# Préfixes → clé sympy.physics.units.prefixes.PREFIXES. `µ`/`u` = micro (`mu`).
_UNIT_PREFIX = {
    "da": "da", "h": "h", "k": "k", "M": "M", "G": "G", "T": "T", "P": "P",
    "E": "E", "d": "d", "c": "c", "m": "m", "µ": "mu", "u": "mu", "n": "n",
    "p": "p", "f": "f", "a": "a",
}


def _unit_atom(tok: str):
    """`dm^2` → expression sympy `(deci·meter)**2` ; `kOhm` → `kilo·ohm`.
    Renvoie l'expression sympy (unité) ou None si non reconnue. Le préfixe est
    appliqué AVANT la puissance."""
    import sympy.physics.units as _u  # noqa: PLC0415
    from sympy.physics.units.prefixes import PREFIXES  # noqa: PLC0415

    m = re.fullmatch(r"([A-Za-zµΩ°]+)\^?(-?\d+)?", tok)
    if not m:
        return None
    name, pw = m.group(1), m.group(2)
    power = int(pw) if pw else 1
    if name in _UNIT_BASE:  # base exacte (min, mol, bar… avant tout préfixe)
        return getattr(_u, _UNIT_BASE[name]) ** power
    # Préfixe (2 lettres d'abord) + base.
    for p in ("da",) + tuple("EGMPTkhdcmµunpfa"):
        rest = name[len(p):]
        if name.startswith(p) and rest in _UNIT_BASE and p in _UNIT_PREFIX:
            return (PREFIXES[_UNIT_PREFIX[p]] * getattr(_u, _UNIT_BASE[rest])) ** power
    return None


def _unit_to_si(unit: str) -> tuple[str, float] | None:
    """Réduit une unité composée (`km/h`, `mol/L`, `dm^2`) à
    (dimension canonique, facteur vers les unités de base SI) via
    ``sympy.physics.units`` — gère préfixes, puissances, unités dérivées
    (N, J, Ω…) et non-métriques (h, min, °). None si non reconnue."""
    unit = _normalize_unit(unit)
    if not unit:
        return None
    expr = None
    op = "*"
    for tok in re.findall(r"[*/]|[^*/]+", unit):
        if tok in ("*", "/"):
            op = tok
            continue
        atom = _unit_atom(tok)
        if atom is None:
            return None
        expr = atom if expr is None else (expr * atom if op == "*" else expr / atom)
    if expr is None:
        return None
    try:
        from sympy.physics.units.systems.si import SI  # noqa: PLC0415
        factor, _dim = SI._collect_factor_and_dimension(expr)
        dim = str(SI.get_dimensional_expr(expr))
        return dim, float(factor)
    except Exception:
        return None


def check_unit(
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
) -> CheckResult:
    """Type ``units`` (WIMS): a numeric value followed by a unit (``"7.7 m/s"``).

    The number is compared numerically (``check_numeric``) and the unit string
    textually after normalising whitespace/separators — so ``"7.7m/s"`` matches
    the expected ``"7.7 m/s"``. WIMS' ``units-filter`` additionally *converts*
    between compatible units; we don't (these exercises ask for a specific
    unit), so the unit must match after normalisation. A missing unit (when one
    is expected) fails — the statement asks to "préciser l'unité".
    """
    rn, ru = _split_value_unit(reply)
    en, eu = _split_value_unit(expected)
    if rn is None or en is None:
        return CheckResult(correct=False, score=0.0, method="unit")
    # 1) Même unité (texte) : comparaison numérique directe.
    if _normalize_unit(ru) == _normalize_unit(eu):
        num = check_numeric(rn, en, precision, comma_is_decimal)
        return CheckResult(correct=num.correct, score=num.score, method="unit")
    # 2) Unités différentes mais compatibles : conversion vers la base SI (WIMS
    #    `units-filter` accepte `400 dm^2` pour `4 m^2`). On ramène les deux
    #    valeurs à la même dimension avant de comparer.
    r_si = _unit_to_si(ru)
    e_si = _unit_to_si(eu)
    if r_si is not None and e_si is not None and r_si[0] == e_si[0]:
        try:
            rv = _parse_number(rn, comma_is_decimal) * r_si[1]
            ev = _parse_number(en, comma_is_decimal) * e_si[1]
        except (ValueError, ZeroDivisionError, SyntaxError):
            return CheckResult(correct=False, score=0.0, method="unit")
        correct = _wims_num_equal(rv, ev, precision)
        return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="unit")
    return CheckResult(correct=False, score=0.0, method="unit")


# Scientific notation written as ``×10^n`` / ``*10^n`` / ``·10^n`` / `` 10^n``
# (with or without the ``^``) → ``e`` notation, so `float()` can read it.
_SCI_OP_RE = re.compile(r"\s*[*x×·⋅]\s*10\s*\^?\s*([+-]?\d+)")
_SCI_SP_RE = re.compile(r"(?<=\d)\s*10\s*\^\s*([+-]?\d+)")


def _normalize_sci(s: str) -> str:
    s = _SCI_OP_RE.sub(lambda m: "e" + m.group(1), s)
    s = _SCI_SP_RE.sub(lambda m: "e" + m.group(1), s)
    return s


def _split_sci_value_unit(s: str) -> tuple[str | None, str]:
    """Split ``"1.64e11 km^3"`` / ``"1,64 × 10^11 km^3"`` / ``"164200792894 km^3"``
    into ``(value, unit)``, the value possibly in scientific notation."""
    s = _normalize_sci(s.strip())
    m = re.match(r"^\s*([+-]?\d+(?:[.,]\d+)?(?:[eE][+-]?\d+)?)\s*(.*)$", s, re.DOTALL)
    if not m:
        return None, ""
    return m.group(1).strip(), m.group(2).strip()


def _round_sig(x: float, n: int) -> float:
    """Round ``x`` to ``n`` significant figures."""
    if x == 0 or n < 1:
        return 0.0
    return round(x, -int(math.floor(math.log10(abs(x)))) + (n - 1))


def _sci_to_float(s: str, comma_is_decimal: bool) -> float:
    s = s.strip()
    if comma_is_decimal:
        s = s.replace(",", ".")
    return float(_normalize_sci(s))


def format_sigunits_expected(expected: str) -> str:
    """Render a ``sigunits`` expected (``"164200792894 km^3 #3"``) as the answer
    the student should give: scientific notation rounded to N significant
    figures, plus the unit (``"1.64e11 km^3"``) — the ``#N`` directive dropped."""
    m = re.match(r"^(.*?)\s*#\s*(\d+)\s*$", expected.strip(), re.DOTALL)
    if not m:
        return expected
    n = int(m.group(2))
    val, unit = _split_sci_value_unit(m.group(1))
    if val is None:
        return m.group(1).strip()
    try:
        x = _sci_to_float(val, comma_is_decimal=True)
    except (ValueError, OverflowError):
        return m.group(1).strip()
    if x == 0:
        mant_exp = "0"
    else:
        exp = int(math.floor(math.log10(abs(x))))
        mant = round(x / 10 ** exp, n - 1)
        if abs(mant) >= 10:  # rounding pushed e.g. 9.99→10.0
            mant /= 10
            exp += 1
        mant_exp = f"{mant:.{max(n - 1, 0)}f}e{exp}"
    return f"{mant_exp} {unit}".strip()


def range_display_answer(expected: str, comma_is_decimal: bool = True) -> str:
    """La valeur affichée en corrigé pour un `range` — le `replyGood` de WIMS.

    `anstype/range` la pose sur la **première** paire de bornes : le milieu de
    l'intervalle quand il est borné, les deux bornes telles quelles s'il y a un
    `inf`. Un `replygood` de longueur **impaire** l'emporte : son dernier item
    est alors la réponse à afficher.

        !if $t=1
          !if inf notin $g1$g2
            replyGood$i=$[($G1+($G2))/2]
          !else
            replyGood$i=$g1,$g2
          !endif
        !endif
        …
        !if $[$gcnt%2]=1
          replyGood$i=$(replygood$i[-1])
        !endif

    `comma_is_decimal` ne décide ici que du **séparateur de liste** — `;` quand
    la virgule est décimale, pour que les deux rôles ne se confondent pas
    (`core/oef/i18n.py`) —, et seul cet appelant sait qu'il s'agit d'une paire
    de bornes. La virgule décimale, elle, est posée en une passe transverse sur
    tous les corrigés numériques (`check.py`, `PAX_LOCALIZE_FEEDBACK`).
    """
    from core.oef.def_engine.wims_lists import cutitems  # noqa: PLC0415
    from core.oef.numfmt import format_wims_float  # noqa: PLC0415

    items = [x.strip() for x in cutitems(expected or "") if x.strip()]

    # `,` décimal ⇒ `;` de liste : les deux rôles ne se confondent jamais dans
    # une même locale (`i18n.list_separator`), ce qui distingue le décimal
    # `2,5` de la paire `2;5`.
    sep = ";" if comma_is_decimal else ","

    if len(items) % 2 == 1:
        return items[-1]
    if len(items) < 2:
        return ""
    g1, g2 = items[0], items[1]
    if "inf" in g1.lower() or "inf" in g2.lower():
        return f"{g1}{sep}{g2}"
    try:
        a = _parse_number(g1, comma_is_decimal)
        b = _parse_number(g2, comma_is_decimal)
    except (ValueError, ZeroDivisionError, SyntaxError, TypeError):
        return f"{g1}{sep}{g2}"
    return format_wims_float((a + b) / 2)


def check_range(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
    """Type WIMS `range` : la réponse doit tomber **dans** un intervalle.

    `replygood` est une liste d'items de longueur paire, lue par paires de
    bornes (`anstype/range`) :

        gcnt=!itemcnt $(replygood$i)
        !if $gcnt<2 … Text=bad …
        gcnt2=$[floor($gcnt/2)]
        !for t=1 to $gcnt2
          g1=$(replygood$i[2*$t-1]) ; g2=$(replygood$i[2*$t])
          !if inf notin $g1$g2 and $G1>$G2 … !exchange G1,G2
          !if (inf isin $G1 or $G1<=$test) and (inf isin $G2 or $G2>=$test)
            diag=yes

    Les bornes sont donc **rangées dans l'ordre où elles viennent** — un
    `0.6,0.4` est l'intervalle [0.4 ; 0.6] —, plusieurs paires forment une
    union, et `inf` ouvre le côté correspondant. Un item surnuméraire (compte
    impair) n'est pas une borne : il ne sert qu'à l'affichage du corrigé.

    PAX repliait sur une comparaison de texte : `0.5` face à `0.6,0.4` était
    refusé, et `3` face à `3,3` aussi.
    """
    from core.oef.def_engine.wims_lists import cutitems  # noqa: PLC0415
    from core.oef.numfmt import format_wims_float  # noqa: PLC0415

    def _wims_double(x: float) -> float:
        """La valeur telle que WIMS la manipule : 12 chiffres significatifs.

        Une borne est un `$[…]` — donc évaluée **puis imprimée** avant d'être
        comparée. Sans ce passage, `2.59+0.01` reste `2.5999999999999996` et
        rejette la borne haute `2.6` de `descriptives/ecarttype2`.
        """
        try:
            return float(format_wims_float(x))
        except (ValueError, OverflowError):
            return x

    try:
        test = _wims_double(_parse_number(reply.strip(), comma_is_decimal))
    except (ValueError, ZeroDivisionError, SyntaxError, TypeError):
        return CheckResult(correct=False, score=0.0, method="range")
    if test != test or test in (float("inf"), float("-inf")):  # NaN / Inf
        return CheckResult(correct=False, score=0.0, method="range")

    items = [x.strip() for x in cutitems(expected or "") if x.strip()]
    if len(items) < 2:
        # `!if $gcnt<2 … Text=bad` — un `replygood` inexploitable.
        return CheckResult(correct=False, score=0.0, method="range")

    for i in range(len(items) // 2):
        g1, g2 = items[2 * i], items[2 * i + 1]
        lo_inf, hi_inf = "inf" in g1.lower(), "inf" in g2.lower()
        try:
            lo = None if lo_inf else _wims_double(_parse_number(g1, comma_is_decimal))
            hi = None if hi_inf else _wims_double(_parse_number(g2, comma_is_decimal))
        except (ValueError, ZeroDivisionError, SyntaxError, TypeError):
            continue  # borne non évaluable : `!goto badgood` côté WIMS
        if lo is not None and hi is not None and lo > hi:
            lo, hi = hi, lo
        if (lo is None or lo <= test) and (hi is None or hi >= test):
            return CheckResult(correct=True, score=1.0, method="range")
    return CheckResult(correct=False, score=0.0, method="range")


def check_sigunits(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
    """Type ``sigunits`` (WIMS): a value in scientific notation rounded to N
    significant figures, plus a unit — expected stored as ``"<value> <unit> #N"``.

    Checks: the reply rounded to N sig figs equals the expected rounded to N sig
    figs, the unit matches, and the reply isn't given with *more* than N sig
    figs (so the student must actually round, e.g. ``1.64e11`` not the raw
    ``164200792894``). Unlike WIMS' ``units-filter`` we don't convert between
    units (the statement asks for a specific one).
    """
    m = re.match(r"^(.*?)\s*#\s*(\d+)\s*$", expected.strip(), re.DOTALL)
    if not m:
        return check_unit(reply, expected, comma_is_decimal=comma_is_decimal)
    n_sig = int(m.group(2))
    ev, eu = _split_sci_value_unit(m.group(1))
    rv, ru = _split_sci_value_unit(reply)
    if ev is None or rv is None:
        return CheckResult(correct=False, score=0.0, method="sigunits")
    try:
        en = _sci_to_float(ev, comma_is_decimal)
        rn = _sci_to_float(rv, comma_is_decimal)
    except (ValueError, OverflowError):
        return CheckResult(correct=False, score=0.0, method="sigunits")

    target = _round_sig(en, n_sig)
    rr = _round_sig(rn, n_sig)

    def _close(a: float, b: float) -> bool:
        return abs(a - b) <= 1e-9 * max(abs(a), abs(b), 1.0)

    # value rounds to the target AND the reply was itself given to ≤ N sig figs
    num_ok = _close(rr, target) and _close(rr, rn)
    unit_ok = _normalize_unit(ru) == _normalize_unit(eu)
    correct = num_ok and unit_ok
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="sigunits")


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


def check_coord(reply: str, expected: str) -> CheckResult:
    """Type ``coord`` : clic sur une image-repère (``<input type=image>``).

    ``reply`` = les pixels cliqués ``(x,y)`` (ou ``x,y``). ``expected`` = la
    *click-zone* WIMS, p.ex. ``point,Ax,Ay`` / ``circle,cx,cy,d`` /
    ``rectangle,x1,y1,x2,y2`` — coordonnées en pixels-image. Portage fidèle de
    ``wims/src/Misc/clickzone.c`` : pour ``point`` le clic est bon si la distance
    au point cible est ≤ 4 px (exact) ou ≤ 7 px (toléré). L'origine du repère et
    l'échelle sont déjà encodées dans ces pixels par le tracé, donc la
    comparaison se fait entièrement en espace-image.
    """
    nums = re.findall(r"-?\d+(?:\.\d+)?", reply or "")
    if len(nums) < 2:
        return CheckResult(correct=False, score=0.0, method="coord")
    cx, cy = float(nums[0]), float(nums[1])

    parts = [p.strip() for p in (expected or "").split(",")]
    if not parts:
        return CheckResult(correct=False, score=0.0, method="coord")
    shape = parts[0].lower()
    vals = [float(v) for v in parts[1:] if re.fullmatch(r"-?\d+(?:\.\d+)?", v)]

    def _hit() -> bool:
        if shape.startswith("point") or shape == "p":
            # One or more target points; any within tolerance counts.
            for i in range(0, len(vals) - 1, 2):
                if math.hypot(vals[i] - cx, vals[i + 1] - cy) <= 7:
                    return True
            return False
        if shape.startswith("circle") and len(vals) >= 3:
            return math.hypot(vals[0] - cx, vals[1] - cy) <= vals[2] / 2
        if shape.startswith("rectangle") and len(vals) >= 4:
            x1, x2 = sorted((vals[0], vals[2]))
            y1, y2 = sorted((vals[1], vals[3]))
            return x1 <= cx <= x2 and y1 <= cy <= y2
        if shape.startswith("ellipse") and len(vals) >= 4 and vals[2] > 0 and vals[3] > 0:
            return math.hypot(2 * (vals[0] - cx) / vals[2], 2 * (vals[1] - cy) / vals[3]) <= 1
        return False

    ok = _hit()
    return CheckResult(correct=ok, score=1.0 if ok else 0.0, method="coord")


# ------------------------------------------------------------------ #
# Vecteur — comparaison composante par composante                      #
# ------------------------------------------------------------------ #


def _declosing(s: str) -> str:
    """``!declosing`` : retire UNE paire de délimiteurs englobants.

    Même règle que le `_cmd_declosing` du moteur : la paire ne tombe que si le
    premier ouvrant s'apparie au tout dernier caractère, sinon `(1,2),(3,4)`
    verrait ses deux couples fusionnés en un seul.
    """
    s = s.strip()
    for open_, close_ in (("(", ")"), ("[", "]"), ("{", "}")):
        if s.startswith(open_) and s.endswith(close_):
            depth = 0
            for j, ch in enumerate(s):
                if ch == open_:
                    depth += 1
                elif ch == close_:
                    depth -= 1
                    if depth == 0:
                        if j != len(s) - 1:
                            return s
                        break
            return s[1:-1].strip()
    return s


def _vector_items(s: str, semicolon_separates: bool = False) -> list[str]:
    """Composantes d'un vecteur, façon ``anstype/vector``.

    La virgule sépare ; **à défaut de virgule** l'espace prend le relais
    (`!words2items`), donc `3 -3` vaut `3,-3`. Le découpage passe par
    `wims_lists.cutitems`, seul endroit du projet qui découpe une liste WIMS.

    ``semicolon_separates`` sort de WIMS : en locale à virgule décimale, c'est
    le `;` qui sépare et la virgule appartient au nombre (`-2,75;-4,75`). Il
    prime alors sur la virgule, sans quoi `-2,75` se lirait en deux items.
    """
    from core.oef.def_engine import wims_lists as wl  # noqa: PLC0415

    if semicolon_separates:
        return [x.strip() for x in s.split(";")]
    if "," in s:
        return [x.strip() for x in wl.cutitems(s)]
    return s.split()


def _eval_scalar(s: str, comma_is_decimal: bool = True) -> float:
    """Valeur numérique d'une composante, comme le `$[...]` de WIMS.

    `_parse_number` couvre l'entier, le décimal, la fraction et l'arithmétique
    simple ; sympy prend la suite pour ce qui appelle une fonction (`sqrt(2)/2`
    en géométrie). Lève `ValueError` si rien n'y parvient.
    """
    try:
        return _parse_number(s, comma_is_decimal)
    except (ValueError, SyntaxError, ZeroDivisionError, NameError, TypeError):
        pass
    try:
        import sympy  # noqa: PLC0415

        val = complex(
            sympy.sympify(
                _normalize_expr(s, comma_is_decimal), locals=_safe_locals()
            ).evalf()
        )
    except Exception as exc:  # noqa: BLE001
        raise ValueError(f"Impossible d'évaluer: {s!r}") from exc
    if abs(val.imag) > 1e-12:
        raise ValueError(f"Valeur complexe: {s!r}")
    return val.real


def check_vector(
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
    absolute: bool = False,
) -> CheckResult:
    """Type ``vector`` : un vecteur donné par ses composantes.

    Portage de ``anstype/vector``. Les délimiteurs englobants sont facultatifs
    (`!declosing`) et l'espace vaut séparateur quand aucune virgule n'est
    présente (`!words2items`) : `(3,-3)`, `3,-3` et `3 -3` sont la même
    réponse.

    **Un écart assumé au C** : WIMS refuse le point-virgule net (`!if ; isin
    $dd → NaN`), n'ayant jamais eu à écrire `-2,75`. La convention i18n du
    projet en fait au contraire le séparateur de liste des langues à virgule
    décimale (`core/oef/i18n.py`), si bien qu'un élève francophone saisissant
    `-2,75;-4,75` — la forme la plus naturelle pour lui — était recalé avec la
    bonne réponse. On accepte donc le `;` **là où la virgule est décimale**, et
    nulle part ailleurs : en locale à point, le refus du C tient tel quel.
    L'ambiguïté ne se pose pas, un `;` présent tranchant la lecture de la
    virgule (séparateur sans lui, décimale avec).

    Chaque composante est comparée **en valeur**, pas littéralement : le
    `-5.5/2` de `translation5` vaut la décimale `-2.75`, que le repli
    texte refusait. Deux passages comme WIMS — à `precision` (juste), puis à
    sa racine (« presque juste » : non crédité, mais signalé plutôt que
    compté faux sec). L'option `absolute` compare en écart absolu et relâche
    à `precision/10`, exactement comme `check_numeric`.

    Un attendu illisible est une erreur d'auteur (`Test=bad` chez WIMS) ; une
    réponse illisible est une erreur d'élève (`test=NaN`). Les deux valent 0
    ici, mais seule la seconde porte un message de forme.
    """
    dd = _declosing(reply or "")
    good = _declosing(expected or "")

    # `!if ; isin $dd` — antérieur à tout découpage, donc même un `;` niché
    # dans une composante condamne la réponse entière. Sauf en locale à virgule
    # décimale, où il est le séparateur attendu (cf. docstring).
    if ";" in dd and not comma_is_decimal:
        return CheckResult(correct=False, score=0.0, method="vector",
                           status="invalid_format", detail=_REWRITE_MSG)

    # L'attendu sort du moteur en notation à point (`3,-3`), mais on lui
    # applique la même règle : un `;` y séparerait aussi, plutôt que de rendre
    # la composante illisible.
    e_items = _vector_items(good, comma_is_decimal and ";" in good)
    r_items = _vector_items(dd, comma_is_decimal and ";" in dd)
    if not e_items:
        return CheckResult(correct=False, score=0.0, method="vector")
    # `badsize` : un vecteur de la mauvaise taille est faux, sans second
    # passage de précision (WIMS exclut explicitement `badsize` du precgood).
    if len(r_items) != len(e_items):
        return CheckResult(correct=False, score=0.0, method="vector")

    prec_loose = precision / 10 if absolute else math.sqrt(precision)
    verdicts: list[str] = []
    for x_s, y_s in zip(e_items, r_items):
        try:
            x = _eval_scalar(x_s, comma_is_decimal)
        except ValueError:
            return CheckResult(correct=False, score=0.0, method="vector")
        try:
            y = _eval_scalar(y_s, comma_is_decimal)
        except ValueError:
            return CheckResult(correct=False, score=0.0, method="vector",
                               status="invalid_format", detail=_REWRITE_MSG)
        if not math.isfinite(x):
            return CheckResult(correct=False, score=0.0, method="vector")
        if not math.isfinite(y):
            return CheckResult(correct=False, score=0.0, method="vector",
                               status="invalid_format", detail=_REWRITE_MSG)
        if absolute:
            diff = abs(x - y)
            if precision * diff < 1:
                verdicts.append("yes")
            elif prec_loose * diff < 1:
                verdicts.append("almost")
            else:
                verdicts.append("bad")
        else:
            if _wims_num_equal(x, y, precision):
                verdicts.append("yes")
            elif _wims_num_equal(x, y, prec_loose):
                verdicts.append("almost")
            else:
                verdicts.append("bad")

    if all(v == "yes" for v in verdicts):
        return CheckResult(correct=True, score=1.0, method="vector")
    # `!if bad notin $test` : toutes les composantes sont au moins « almost ».
    if "bad" not in verdicts:
        return CheckResult(correct=False, score=0.5, method="vector",
                           detail=_POOR_PRECISION_MSG)
    return CheckResult(correct=False, score=0.0, method="vector")


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
    # Nombre simple, y compris notation scientifique (`3.34e-26`, `1.5E3`) que
    # la voie « expression arithmétique » ci-dessous rejette (le `e` n'est pas
    # dans sa classe de caractères). Masses atomiques, constantes physiques…
    if re.fullmatch(r"[+-]?\d+(?:\.\d+)?(?:[eE][+-]?\d+)?", s):
        return float(s)
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
    reply: str, expected: str, comma_is_decimal: bool = True,
    rational_only: bool = False,
) -> CheckResult:
    """
    Compare deux expressions algébriques via SymPy.
    Correct si la différence se simplifie à 0.

    ``rational_only`` (type ``algexp``) : simplification **rationnelle** seule
    (``cancel``), sans identités trigonométriques/fonctionnelles — comme le
    ``ratsimp`` de WIMS. Ainsi ``sin²+cos²`` n'est PAS accepté pour ``1`` (WIMS
    rejette : ratsimp ne connaît pas l'identité). Le défaut (``formal``,
    ``default``) garde ``simplify`` (avec trig), fidèle au ``trigsimp`` de
    ``anstype/formal``.
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

        if rational_only:
            correct = sympy.cancel(r_expr - e_expr) == 0
        else:
            correct = sympy.simplify(sympy.expand(r_expr) - sympy.expand(e_expr)) == 0

        return CheckResult(
            correct=correct, score=1.0 if correct else 0.0, method="sympy"
        )

    except Exception:
        # Fallback : comparaison numérique en plusieurs points
        return _check_algexp_numeric(reply, expected, comma_is_decimal)


# ------------------------------------------------------------------ #
# Équation — équivalence à facteur multiplicatif près                  #
# ------------------------------------------------------------------ #


def _equation_sides(s: str, comma_is_decimal: bool):
    """Membre gauche moins membre droit, en expression sympy.

    WIMS traduit le `=` en saut de ligne puis `!distribute lines … into t,t2` :
    au-delà de deux membres, le surplus est **perdu** (`a=b=c` devient `a-(b)`).
    On reproduit ce découpage plutôt que de rejeter, pour ne pas inventer un
    verdict que le C ne rend pas.
    """
    import sympy  # noqa: PLC0415
    from sympy.parsing.sympy_parser import (  # noqa: PLC0415
        implicit_multiplication_application,
        parse_expr,
        standard_transformations,
    )

    transformations = standard_transformations + (
        implicit_multiplication_application,
    )
    local_dict = {**_safe_locals(), "expand": sympy.expand, "factor": sympy.factor}
    parts = s.split("=")
    lhs = parse_expr(
        _normalize_expr(parts[0], comma_is_decimal),
        transformations=transformations, local_dict=local_dict,
    )
    if len(parts) < 2 or not parts[1].strip():
        return lhs
    rhs = parse_expr(
        _normalize_expr(parts[1], comma_is_decimal),
        transformations=transformations, local_dict=local_dict,
    )
    return lhs - rhs


def check_equation(
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
    eqsign: bool = True,
) -> CheckResult:
    """Type ``equation`` : deux équations sont égales **à un facteur près**.

    Portage de ``anstype/equation``. C'est tout l'intérêt du type, et ce que le
    repli texte détruisait : pour l'attendu `2*x - 3*y - 1=0` d'`equationDe2pts`,
    WIMS accepte `4x-6y-2=0`, `2x-3y=1` et `-2x+3y+1=0` — la même droite. La
    comparaison littérale n'acceptait que la seule écriture stockée par
    l'auteur, et notait faux toutes les autres.

    WIMS ramène chaque membre à `gauche-(droite)`, puis tire au sort des
    valeurs pour les variables et regarde si le **rapport** des deux
    expressions reste constant : constant ⇒ proportionnelles ⇒ même équation.
    Un rapport nul (`abs<1/precision`) ou qui change de signe (`max*min<0`)
    est rejeté.

    Nous menons ce test **symboliquement** — `cancel(E_reply/E_good)` sans
    variable libre —, ce qui rend le même verdict sans dépendre d'un tirage :
    le C échantillonne faute de CAS sous la main, et son `Error=bad` après
    `5*testnum` essais infructueux est un aveu de la méthode, pas une règle à
    porter. Le repli numérique ci-dessous reprend le principe du C pour ce que
    `cancel` ne réduit pas (trigonométrie, exponentielles).

    ``eqsign`` (option WIMS `eqsign`, vraie par défaut) : sans signe « = », la
    réponse est un `badform`, pas une réponse fausse. Avec `eqsign=no`, WIMS
    sous-entend « = 0 ».

    L'attendu peut lister des variables après l'équation (`x^2+y^2=1,x,y`) :
    elles n'entrent que dans le tirage du repli numérique, et une virgule
    décimale ne doit pas passer pour un séparateur — d'où le garde-fou.
    """
    from core.oef.def_engine import wims_lists as wl  # noqa: PLC0415

    good_raw = (expected or "").strip()
    items = [x.strip() for x in wl.cutitems(good_raw)]
    eq_str = items[0] if items else good_raw
    extra_vars = [v for v in items[1:] if re.fullmatch(r"[A-Za-z_]\w*", v)]
    # `0,5` n'est pas « 0 puis la variable 5 » : si le reste n'est pas une
    # liste de noms de variables, l'attendu est repris entier.
    if len(items) > 1 and len(extra_vars) != len(items) - 1:
        eq_str = good_raw
        extra_vars = []

    r_raw = (reply or "").strip()
    if "=" not in r_raw:
        if eqsign:
            return CheckResult(correct=False, score=0.0, method="equation",
                               status="invalid_format", detail=_EQSIGN_MSG)
        r_raw = f"{r_raw}=0" if r_raw else "0=0"

    try:
        import sympy  # noqa: PLC0415

        e_expr = _equation_sides(eq_str, comma_is_decimal)
        r_expr = _equation_sides(r_raw, comma_is_decimal)
    except Exception:  # noqa: BLE001
        return CheckResult(correct=False, score=0.0, method="equation",
                           status="invalid_format", detail=_REWRITE_MSG)

    # Une réponse identiquement nulle (`0=0`) n'est l'équation de rien : WIMS
    # la rejette par `abs($max)<1/$precision`.
    if r_expr == 0 or e_expr == 0:
        return CheckResult(correct=False, score=0.0, method="equation")

    try:
        ratio = sympy.cancel(sympy.together(r_expr / e_expr))
        if not ratio.free_symbols and ratio.is_finite is not False and ratio != 0:
            return CheckResult(correct=True, score=1.0, method="equation")
        # `cancel` ne réduit pas tout : on retombe sur l'échantillonnage du C.
        ok = _equation_ratio_constant(
            r_expr, e_expr, extra_vars, precision
        )
        return CheckResult(correct=ok, score=1.0 if ok else 0.0, method="equation")
    except Exception:  # noqa: BLE001
        return CheckResult(correct=False, score=0.0, method="equation")


def _equation_ratio_constant(
    r_expr, e_expr, extra_vars: list[str], precision: float
) -> bool:
    """Le rapport des deux expressions est-il constant, aux points d'essai ?

    Reprise de la boucle `!for N=1 to 5*$testnum` d'``anstype/equation``, avec
    des points **fixes** au lieu d'un tirage : un checker doit rendre deux fois
    le même verdict sur la même copie. Ils sont irrationnels et non alignés
    pour éviter les annulations heureuses (une racine commune ferait passer
    deux équations différentes).

    Un point où l'attendu s'annule est écarté, comme le `abs($gt)>10/$precision`
    du C — le rapport y explose sans rien dire de l'équivalence.
    """
    import sympy  # noqa: PLC0415

    variables = sorted(
        {str(s) for s in (r_expr.free_symbols | e_expr.free_symbols)}
        | set(extra_vars)
    )
    if not variables:
        return False
    probes = (0.7071067811865476, 1.4142135623730951, 2.718281828459045,
              3.141592653589793, 1.6180339887498949, 0.5772156649015329)
    ratios: list[float] = []
    for k in range(len(probes)):
        subs = {
            sympy.Symbol(v): probes[(k + i) % len(probes)] + k
            for i, v in enumerate(variables)
        }
        try:
            den = complex(e_expr.subs(subs).evalf())
            num = complex(r_expr.subs(subs).evalf())
        except Exception:  # noqa: BLE001
            return False
        if not (math.isfinite(den.real) and math.isfinite(num.real)):
            return False
        if abs(den) <= 10.0 / precision:
            continue
        ratios.append((num / den).real if abs(den) else 0.0)
    if len(ratios) < 3:
        return False
    hi, lo = max(ratios), min(ratios)
    scale = max(abs(hi), abs(lo))
    # Rapport nul ou changeant de signe : `test=100` chez WIMS, donc faux.
    if scale < 1.0 / precision or hi * lo < 0:
        return False
    return abs(hi - lo) / scale < 1.0 / precision


def _rawmath_normalize(s: str, comma_is_decimal: bool = True) -> str:
    """Normalisation « rawmath » légère pour la comparaison littérale de `litexp`.

    WIMS compare les formes rawmath-normalisées (pas via CAS) : espaces retirés,
    multiplication implicite explicitée, `**`→`^`. **Aucune simplification** :
    `6/4` reste `6/4`, `x*x` reste `x*x`, l'ordre des termes est préservé (les
    auteurs énumèrent les formes acceptées, ex. `5*sqrt(5),sqrt(5)*5`).

    Le `*` implicite n'est PAS inséré avant `(` après une lettre, pour ne pas
    casser les appels de fonction (`sqrt(5)` ne devient pas `sqrt*(5)`)."""
    if comma_is_decimal:
        s = s.replace(",", ".")
    s = s.replace(" ", "").replace("**", "^")
    s = re.sub(r"(\d)([A-Za-z(])", r"\1*\2", s)   # 2x → 2*x ; 2( → 2*(
    s = re.sub(r"(\))([A-Za-z0-9(])", r"\1*\2", s)  # )x → )*x ; )( → )*(
    return s


def check_litexp(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
    """Type ``litexp`` WIMS (plain, sans polexpand/polfactor) : la réponse doit
    être **mathématiquement égale** ET écrite **dans la même forme** que
    l'attendu (comparaison rawmath littérale, `$dd isitemof $good`).

    Donc `6/4` est refusé (badform) pour `3/2`, `x*x+3` pour `x^2+3`, `1.5` pour
    `3/2` — équivalents mais forme non conforme. `2x+3` reste accepté pour
    `2*x+3` (même forme rawmath)."""
    base = check_algexp(reply, expected, comma_is_decimal)
    if not base.correct:
        return base  # pas égal → mauvaise réponse
    if _rawmath_normalize(reply, comma_is_decimal) == _rawmath_normalize(expected, comma_is_decimal):
        return CheckResult(correct=True, score=1.0, method="litexp")
    # Égal mais forme non conforme → à réécrire.
    return CheckResult(correct=False, score=0.0, method="litexp_badform",
                       status="invalid_format", detail=_REWRITE_MSG)


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


def _parse_exact_rational(
    s: str, comma_is_decimal: bool
) -> tuple[Fraction, str, bool] | None:
    """Interprète ``s`` comme un rationnel exact : entier, décimal, ou fraction
    simple ``a/b``. Retourne ``(valeur, forme, réduite)`` où ``forme`` ∈
    {``"int"``, ``"decimal"``, ``"fraction"``} et ``réduite`` indique si une
    fraction ``a/b`` est irréductible (``pgcd=1`` et dénominateur > 0). Retourne
    ``None`` si ``s`` n'est pas un rationnel simple (expression composée,
    irrationnel…). Pas de tolérance : ``0.333`` ≠ ``1/3`` (WIMS `numexp`)."""
    s = s.strip().replace(" ", "")
    if comma_is_decimal:
        s = s.replace(",", ".")
    m = re.fullmatch(r"([+-]?\d+)/([+-]?\d+)", s)
    if m:
        num, den = int(m.group(1)), int(m.group(2))
        if den == 0:
            return None
        reduced = math.gcd(abs(num), abs(den)) == 1 and den > 0
        return Fraction(num, den), "fraction", reduced
    if re.fullmatch(r"[+-]?\d+", s):
        return Fraction(int(s)), "int", True
    if re.fullmatch(r"[+-]?(?:\d+\.\d*|\.\d+)", s):
        try:
            return Fraction(s), "decimal", True
        except (ValueError, ZeroDivisionError):
            return None
    return None


def check_numexp(
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
    noreduction: bool = False,
) -> CheckResult:
    """Type ``numexp`` (WIMS ``anstype/numexp``) : l'élève donne un nombre —
    entier, décimal, ou **fraction irréductible** — pas un calcul.

    Contrairement à une comparaison numérique tolérante, WIMS exige :
    - pas de mélange ``/`` et ``.`` (``badform``) ;
    - pas d'expression composée (``+ - * ^ (``, `nocompute`) ;
    - fraction sous forme **irréductible** (``2/8`` refusé pour ``1/4``), sauf
      option ``noreduction`` ;
    - égalité **rationnelle exacte** : ``0.333`` refusé pour ``1/3``.

    Repli sur une comparaison flottante (précision WIMS) quand un côté n'est pas
    un rationnel simple (attendu irrationnel, etc.)."""
    r = reply.strip()
    r_norm = (r.replace(",", ".") if comma_is_decimal else r).replace(" ", "")

    # badform : fraction ET décimal mélangés.
    if "/" in r_norm and "." in r_norm:
        return CheckResult(correct=False, score=0.0, method="numexp",
                           status="invalid_format", detail=_NUMEXP_BADFORM_MSG)
    # nocompute : expression composée interdite (numexp = une valeur).
    dd = r_norm[1:] if r_norm[:1] in "+-" else r_norm
    if any(op in dd for op in ("+", "-", "*", "^", "(")):
        return CheckResult(correct=False, score=0.0, method="numexp",
                           status="invalid_format", detail=_COMPUTE_MSG)

    rp = _parse_exact_rational(r, comma_is_decimal)
    ep = _parse_exact_rational(expected, comma_is_decimal)
    if rp is None or ep is None:
        # Attendu (ou réponse) non rationnel simple → comparaison flottante.
        return _check_numexp_float(reply, expected, precision, comma_is_decimal)

    r_val, r_form, r_reduced = rp
    if r_form == "fraction" and not noreduction and not r_reduced:
        return CheckResult(correct=False, score=0.0, method="numexp",
                           status="invalid_format", detail=_NUMEXP_REDUCE_MSG)
    correct = r_val == ep[0]
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="numexp")


def _check_numexp_float(
    reply: str, expected: str, precision: float, comma_is_decimal: bool
) -> CheckResult:
    """Repli de :func:`check_numexp` : évalue les deux côtés en flottant et
    compare à la précision WIMS (pour un attendu non rationnel simple)."""
    try:
        import sympy

        _loc = _safe_locals()
        r_in = reply.replace(",", ".") if comma_is_decimal else reply
        e_in = expected.replace(",", ".") if comma_is_decimal else expected
        r_val = float(sympy.sympify(_normalize_expr(r_in), locals=_loc))
        e_val = float(sympy.sympify(_normalize_expr(e_in), locals=_loc))
        if _wims_num_equal(r_val, e_val, precision):
            return CheckResult(correct=True, score=1.0, method="numexp")
        if _wims_num_equal(r_val, e_val, math.sqrt(precision)):
            return CheckResult(correct=False, score=0.5, method="numexp",
                               detail=_POOR_PRECISION_MSG)
        return CheckResult(correct=False, score=0.0, method="numexp")
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
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
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
            return _wims_num_equal(av, bv, precision)
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


def check_clickfill(reply: str, expected: str, noorder: bool = False) -> CheckResult:
    """Compare two drag-compose sequences (comma-joined slot values).

    Order matters; empty slots are ignored. Works for a single-slot clickfill
    too (one item each side). Under the `noorder` option (`anstype/dragfill`
    compares `!sort items` on both sides) only the multiset counts — that is
    what makes "sort these into groups" exercises gradable.
    """
    def seq(s: str) -> list[str]:
        return [x.strip() for x in s.split(",") if x.strip()]

    a, b = seq(reply), seq(expected)
    correct = sorted(a) == sorted(b) if noorder else a == b
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


def _deaccent(s: str) -> str:
    """Retire les diacritiques (é→e, ç→c…) — WIMS `!deaccent`."""
    return "".join(c for c in unicodedata.normalize("NFKD", s) if not unicodedata.combining(c))


# Ponctuation neutralisée par WIMS `nocase` (badchars → espaces).
_NOCASE_PUNCT = re.compile(r"""[-+/*='"`.;,!{}@#$%^&()\[\]?<>\\~]""")


def _nocase_normalize(s: str) -> str:
    """Normalisation `nocase` : ponctuation → espace, accents/casse/espaces
    multiples ignorés (WIMS : translate badchars, singlespace, deaccent, lower,
    trim)."""
    s = _NOCASE_PUNCT.sub(" ", s)
    s = _deaccent(s)
    return re.sub(r"\s+", " ", s).strip().lower()


def check_nocase(reply: str, expected: str) -> CheckResult:
    """Type WIMS `nocase` : correspondance **exacte après normalisation**
    (accents, casse, espaces et ponctuation ignorés), contre n'importe quelle
    alternative séparée par ``|``."""
    r = _nocase_normalize(reply)
    if not r:
        return CheckResult(correct=False, score=0.0, method="nocase")
    for alt in expected.split("|"):
        if r == _nocase_normalize(alt):
            return CheckResult(correct=True, score=1.0, method="nocase")
    return CheckResult(correct=False, score=0.0, method="nocase")


import os.path as _osp
from functools import lru_cache as _lru_cache


@_lru_cache(maxsize=None)
def _atext_dicts(lang: str) -> tuple[frozenset, tuple]:
    """Charge (mots à supprimer, règles de suffixe) pour `atext` depuis
    ``data/atext/`` (copiés de WIMS `scripts/oef/<lang>/atext.dic` et
    ``bases/sys/suffix.<lang>``). Règles triées par longueur de clé décroissante
    (plus longue correspondance d'abord). Repli sur ``fr`` si la langue manque."""
    base = _osp.join(_osp.dirname(__file__), "data", "atext")
    lang = (lang or "fr").split("-")[0].lower()
    dic_path = _osp.join(base, f"atext.{lang}.dic")
    suf_path = _osp.join(base, f"suffix.{lang}")
    if not _osp.exists(dic_path):
        dic_path, suf_path = _osp.join(base, "atext.fr.dic"), _osp.join(base, "suffix.fr")
    strip: set[str] = set()
    try:
        with open(dic_path, encoding="utf-8") as f:
            for line in f:
                w, _, tr = line.strip().partition(":")
                if w and not tr:  # traduction vide → mot supprimé
                    strip.add(w)
    except OSError:
        pass
    rules: list[tuple[str, str]] = []
    try:
        with open(suf_path, encoding="utf-8") as f:
            for line in f:
                k, _, v = line.strip().partition(":")
                if k:
                    rules.append((k, v))
    except OSError:
        pass
    rules.sort(key=lambda kv: len(kv[0]), reverse=True)
    return frozenset(strip), tuple(rules)


def _atext_stem(word: str, rules: tuple) -> str:
    """Racinise un mot via les règles de suffixe WIMS (appliquées sur le mot
    inversé : plus longue clé-préfixe remplacée)."""
    rev = word[::-1]
    for key, val in rules:
        if rev.startswith(key):
            rev = val + rev[len(key):]
            break
    return rev[::-1]


def _atext_normalize(s: str, lang: str) -> str:
    """Normalisation `atext` : nocase (accents/casse/ponctuation) + suppression
    des mots vides (articles) + racinisation (pluriel/genre) par dictionnaire."""
    strip, rules = _atext_dicts(lang)
    s = _nocase_normalize(s)  # deaccent, lower, ponctuation→espace, singlespace
    out = []
    for w in s.split():
        if w in strip:
            continue
        out.append(_atext_stem(w, rules))
    return " ".join(out)


def atext_good_line(expected: str) -> str:
    """La ligne de `replygood` qui porte la réponse, pour `atext`.

    `anstype/atext` ouvre sur `!singlespace`, `!rows2lines`, `!nonempty lines`
    puis `!line 1 of` : le `;` est un saut de ligne, et seule la première ligne
    est la réponse. Les suivantes sont les `badwords`, qui ne servent qu'au
    diagnostic `unknownword`.
    """
    from core.oef.def_engine.wims_lists import cutlines, rows2lines  # noqa: PLC0415

    good, _ = rows2lines(re.sub(r"[ \t]+", " ", expected or ""))
    for ligne in cutlines(good):
        if ligne.strip():
            return ligne
    return ""


def atext_display_answer(expected: str) -> str:
    """La bonne réponse **affichable** d'un `atext` — le `replyGood` de WIMS.

    Le checker la pose juste après avoir isolé la ligne 1 :

        replyGood$i=!translate | to <NL> in $good
        replyGood$i=!nonempty lines $(replyGood$i)
        replyGood$i=!line 1 of $(replyGood$i)

    C'est donc la **première alternative** de la première ligne : « Pays-Bas »
    pour un `Pays-Bas|Hollande;Belgique,Suisse`. Sans elle, le corrigé de
    `oefcountries` déroulait les deux cents pays du monde.
    """
    for alt in atext_good_line(expected).split("|"):
        if alt.strip():
            return alt.strip()
    return ""


def check_atext(reply: str, expected: str, lang: str = "fr") -> CheckResult:
    """Type WIMS `atext` : texte libre tolérant — accents/casse/ponctuation
    ignorés, **mots vides** (articles) supprimés, **pluriel/genre** normalisés
    par dictionnaire. Alternatives séparées par ``|``. Donc « les triangles »,
    « un triangle », « triangle » sont équivalents.

    Seule la **première ligne** de l'attendu porte la bonne réponse. Le
    checker WIMS (`anstype/atext`) ouvre sur :

        good=!singlespace $(replygood$i)
        good=!rows2lines $good
        good=!nonempty lines $good
        badwords=!line 2 to -1 of $good
        good=!line 1 of $good

    `rows2lines` fait des `;` des sauts de ligne : `oefcountries` écrit
    `Pologne;Algérie,Angola,…`, où la suite n'est pas une alternative mais la
    liste des **autres** pays. Elle sert à un diagnostic (`unknownword` quand
    la saisie ne contient aucun mot connu de l'exercice) que nous ne rendons
    pas encore — une mauvaise réponse est simplement fausse — mais elle ne
    doit surtout pas entrer dans la comparaison.
    """
    good = atext_good_line(expected)

    r = _atext_normalize(reply, lang)
    if not r:
        return CheckResult(correct=False, score=0.0, method="atext")
    for alt in good.split("|"):
        if r == _atext_normalize(alt, lang):
            return CheckResult(correct=True, score=1.0, method="atext")
    return CheckResult(correct=False, score=0.0, method="atext")


def check_raw(reply: str, expected: str, option: str = "") -> CheckResult:
    """Type WIMS `raw` : comparaison **exacte** de chaîne (sensible casse/espaces
    par défaut), après application des filtres pilotés par l'option :
    `nospace`, `nocase`, `deaccent`/`noaccent`, `nodigit`, `nopunct`,
    `noparenthesis`, `nomathop`, `noquote` (WIMS retire chaque classe de
    caractères, puis compare)."""
    opt = option.lower()

    def _filter(s: str) -> str:
        if "nospace" in opt:
            s = re.sub(r"\s+", "", s)
        if "nocase" in opt:
            s = s.lower()
        if "deaccent" in opt or "noaccent" in opt:
            s = _deaccent(s)
        if "nodigit" in opt:
            s = re.sub(r"[0-9]", "", s)
        if "noquote" in opt:
            s = re.sub(r"[\"'`]", "", s)
        if "nomathop" in opt:
            s = re.sub(r"[+\-=*/^<>%|]", "", s)
        if "noparenthes" in opt:  # noparenthesis / noparentheses
            s = re.sub(r"[()\[\]{}]", "", s)
        if "nopunct" in opt:
            s = re.sub(r"[.,;!?:()\[\]{}]", "", s)
        return s

    correct = _filter(reply.strip()) == _filter(expected.strip())
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="raw")


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
    # Alias, type vide, premier mot : WIMS canonise avant de dispatcher, et
    # tout ce qui suit raisonne sur le nom canonique. Le nom d'origine ne sert
    # plus qu'au journal, où il doit rester tel que l'auteur l'a écrit.
    raw_answer_type = answer_type
    answer_type = normalize_replytype(answer_type)
    # Précision WIMS (`\precision{M}`, grand entier) injectée par le moteur ;
    # défaut 10000 comme WIMS (var.prep). C'est un facteur, pas une tolérance.
    try:
        precision = float(options.get("precision", WIMS_DEFAULT_PRECISION))
    except (TypeError, ValueError):
        precision = WIMS_DEFAULT_PRECISION
    if precision <= 0:
        precision = WIMS_DEFAULT_PRECISION
    comma_is_decimal = uses_comma_decimal(lang)
    # Option WIMS `absolute` : comparaison en écart absolu (anstype/numeric).
    absolute = "absolute" in str(options.get("option", "")).lower()
    # `\computeanswer{no}` (défaut OEF) : une réponse numérique doit être un
    # nombre, pas une expression à calculer. `yes` autorise le calcul.
    compute_ok = str(options.get("computeanswer", "")).strip().lower() == "yes"

    # WIMS `option=default=X` (step.proc) : une réponse vide est remplacée par X
    # puis vérifiée normalement. Couvre `default=vide` (fset « ∅ » : un champ
    # laissé vide vaut la réponse « ensemble vide ») et `default=$valN` (valeur
    # déjà substituée par le moteur). Les brouillons (type=draft) sont exclus en
    # amont (check.py), donc n'atteignent pas ce point.
    if not reply.strip():
        m = re.search(r"default=(\S+)", str(options.get("option", "")))
        if m:
            reply = m.group(1)

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
    # `formal` = équivalence CAS pure (WIMS : `good-reply` simplifié à 0) :
    # aucune contrainte de forme développée/factorisée. `(x+1)(x-1)` est accepté
    # pour `x^2-1`. Les options explicites `polexpand`/`polfactor` (ci-dessus)
    # s'appliquent quand même si l'auteur les a posées.
    # `litexp` et `algexp` exclus : litexp fait une comparaison littérale de
    # forme (check_litexp) ; algexp accepte toute forme équivalente non
    # simplifiée (`(24+4)*x-53` pour `28*x-53`) — pas de contrainte
    # développé/factorisé auto-déduite. `default`/`auto` la gardent.
    if (
        not requires_expand
        and not requires_factor
        and answer_type.lower() in ("default", "auto")
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
            if not compute_ok and _wims_has_compound_arith(reply, comma_is_decimal):
                return CheckResult(
                    correct=False, score=0.0, method="numeric",
                    status="invalid_format", detail=_COMPUTE_MSG,
                )
            return check_numeric(reply, expected, precision, comma_is_decimal, absolute)
        case "numexp":
            noreduction = "noreduction" in opt_str
            return check_numexp(reply, expected, precision, comma_is_decimal, noreduction)
        case "units" | "unit":
            return check_unit(reply, expected, precision, comma_is_decimal)
        case "sigunits":
            return check_sigunits(reply, expected, comma_is_decimal)
        case "range":
            return check_range(reply, expected, comma_is_decimal)
        case "litexp":
            # Plain litexp = comparaison littérale (forme conforme). Avec une
            # option de forme (expand/polfactor), WIMS vérifie plutôt que la
            # réponse est développée/factorisée → voie check_algexp + pré-checks.
            if "expand" in opt_str or "polfactor" in opt_str:
                return check_algexp(reply, expected, comma_is_decimal)
            return check_litexp(reply, expected, comma_is_decimal)
        case "algexp":
            # Équivalence rationnelle (sans trig) ; formes équivalentes non
            # simplifiées acceptées (`(24+4)*x-53` = `28*x-53`).
            return check_algexp(reply, expected, comma_is_decimal, rational_only=True)
        case "formal":
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
            return check_clickfill(reply, expected, noorder="noorder" in opt_str)
        case "correspond":
            return check_correspond(reply, expected, partial=bool(options.get("partial")))
        case "jsxgraph":
            return check_jsxgraph(reply, expected, options)
        case "coord":
            return check_coord(reply, expected)
        case "equation":
            # `option:eqsign=yes` — le signe « = » est exigé sauf mention
            # contraire de l'auteur.
            return check_equation(
                reply, expected, precision, comma_is_decimal,
                eqsign="eqsign=no" not in opt_str.replace(" ", ""),
            )
        case "vector":
            return check_vector(reply, expected, precision, comma_is_decimal, absolute)
        case "case":
            return check_case(reply, expected)
        case "raw":
            return check_raw(reply, expected, opt_str)
        case "nocase":
            return check_nocase(reply, expected)
        case "atext":
            return check_atext(reply, expected, lang or "fr")
        case "default" | "auto":
            # `anstype/default` n'est pas un comparateur mais un aiguilleur :
            # sa toute première règle renvoie vers `equation` dès que l'attendu
            # porte un « = ».
            #
            #     eq==
            #     !if $eq isin $(replygood$i) and $wims_read_parm!=sub
            #       !changeto anstype/equation
            #
            # Sans quoi `fnctaff3`, qui attend `-1=3*a+b`, partait en
            # comparaison algébrique : le « = » y fait échouer le parse, et une
            # bonne réponse était notée fausse.
            if "=" in expected and not re.search(r"[<>=!]=|=[<>=]", expected):
                return check_equation(reply, expected, precision, comma_is_decimal)
            # Deuxième règle de l'aiguilleur : un attendu qui **s'évalue en
            # nombre** relève de `numeric`, et de sa tolérance.
            #
            #     nn=$[$(replygood$i)]
            #     !if NaN notin $nn
            #       !changeto anstype/numeric
            #
            # Sans elle, `1/4` se comparait symboliquement : juste dans les
            # faits, mais sans la marge de `\precision` que l'auteur a réglée.
            try:
                _val = _eval_scalar(expected, comma_is_decimal)
            except ValueError:
                _val = None
            if _val is not None and math.isfinite(_val):
                return check_numeric(reply, expected, precision, comma_is_decimal, absolute)
            # Faute de quoi WIMS regarde la longueur des variables et part sur
            # `function` (≤ 3 caractères) ou `atext`. `check_default` couvre les
            # deux : comparaison algébrique, puis textuelle.
            return check_default(reply, expected, comma_is_decimal)
        case _:
            # `replytype.proc` ne connaît pas de repli textuel : un type qu'il
            # ne reconnaît pas devient `default`, donc une comparaison
            # mathématique. C'est le cas des noms inventés par les auteurs
            # (`rational`, `fonction`, `numexp2`…), que `check_text` refusait
            # dès que l'élève écrivait la même valeur autrement.
            #
            # Un type que WIMS connaît mais que PAX n'a pas encore porté est
            # une autre affaire : ce n'est pas un `default`, c'est une dette.
            # On garde la comparaison littérale — `check_default` prétendrait
            # comparer mathématiquement un clic ou une figure — et on la trace.
            if answer_type in _WIMS_KNOWN_TYPES or answer_type in _MODULE_ANSTYPES:
                _log_unhandled_answer_type(raw_answer_type)
                return check_text(reply, expected)
            return check_default(reply, expected, comma_is_decimal)
