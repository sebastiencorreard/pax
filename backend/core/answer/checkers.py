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

from core.oef.def_engine import wims_lists as wl

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


def _est_constante(s: str) -> bool:
    """Vrai si l'expression ne porte aucune variable — `6`, `-3/4`, `2^3`.

    Une telle réponse échappe à l'opposition développé / factorisé, dont les
    deux pré-contrôles de forme dépendent.
    """
    try:
        import sympy  # noqa: PLC0415
        from sympy.parsing.sympy_parser import (  # noqa: PLC0415
            implicit_multiplication_application,
            parse_expr,
            standard_transformations,
        )

        expr = parse_expr(
            _normalize_expr(s),
            transformations=standard_transformations
            + (implicit_multiplication_application,),
            local_dict=_safe_locals(),
        )
        return not expr.free_symbols
    except Exception:  # noqa: BLE001 — illisible : on ne conclut pas
        return False


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
    precweight: float = 0.5,
) -> CheckResult:
    """
    Compare deux nombres avec la sémantique de précision WIMS (``anstype/numeric``).
    Accepte les fractions (1/2), les expressions simples (2*3).
    ``comma_is_decimal`` : voir :func:`_parse_number`.

    ``precision`` est la précision WIMS (grand entier, défaut 10000), *pas* une
    tolérance. Deux passages, comme WIMS :

    - à ``precision`` : réponse exacte → correct, score 1.0 ;
    - sinon à ``sqrt(precision)`` (comparaison relâchée) → « bonne à la précision
      près » : ``correct=False`` et score partiel **0,5** (``precgood`` de
      WIMS).

    Ce 0,5 est celui de ``oef/screply.proc`` :

        !if $(precreply$i)=yes and $(diareply$i)=bad
          !default m_sc_reply$i=0.5

    et c'est la seule valeur de crédit partiel qui figure dans les scripts OEF.
    On a cru un temps que le crédit venait de ``precweight``, le réglage du
    niveau de sévérité qui vaut 0,9 au niveau 1. **Une mesure sur WIMS l'a
    démenti** : `OEFevalwimsfctref/valtrigo1`, deux réponses approchées, donne
    4,9/10 — soit ~0,49 par réponse, et non 0,9. ``precweight`` sert ailleurs,
    dans l'ajustement de poids d'``ans.proc``.

    L'écart résiduel entre 0,49 et 0,50 n'est pas expliqué ; il est trop faible
    pour venir du crédit lui-même.

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
            return CheckResult(correct=False, score=precweight, method="numeric",
                               detail=_POOR_PRECISION_MSG)
        return CheckResult(correct=False, score=0.0, method="numeric")

    if _wims_num_equal(r, e, precision):
        return CheckResult(correct=True, score=1.0, method="numeric")
    if _wims_num_equal(r, e, math.sqrt(precision)):
        return CheckResult(correct=False, score=precweight, method="numeric",
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


def units_filter(args: str) -> str:
    """``!exec units-filter <quantité>#<chiffres>[:<unité voulue>]``.

    `units-filter` est un binaire de WIMS : il lit une quantité avec son unité,
    l'arrondit au nombre de chiffres **significatifs** demandé, et sait la
    convertir vers une autre unité. PAX ne le fournissait pas, et `!exec` ne
    connaissant que `maxima` et `pari`, l'appel rendait une chaîne vide — d'où
    l'attendu ` s#2` de `periodefrequence`, réduit à son unité, la valeur
    partie. Soixante-dix fichiers du corpus passent par `slib/text/sigunits`,
    qui n'est qu'une enveloppe autour de cet appel.

    L'arrondi est porté ici ; la **conversion** d'unité ne l'est pas — elle
    demanderait la table de WIMS — et un appel qui en réclame une rend la
    chaîne vide comme avant, plutôt qu'une valeur non convertie qui serait
    fausse sans le dire.
    """
    from core.oef.numfmt import format_wims_float  # noqa: PLC0415

    spec = (args or "").strip()
    if not spec:
        return ""
    # `:unité` — conversion demandée. Tolérée seulement si l'unité voulue est
    # celle de départ, auquel cas il n'y a rien à convertir.
    voulue = ""
    if ":" in spec:
        spec, _, voulue = spec.partition(":")
        voulue = voulue.strip()
    quantite, _, chiffres = spec.partition("#")
    try:
        n_sig = int(chiffres.strip())
    except ValueError:
        n_sig = 3  # `!default slib_sig=3` dans `slib/text/sigunits`
    val, unite = _split_sci_value_unit(quantite.strip())
    if val is None:
        return ""
    if voulue and voulue != unite:
        return ""
    try:
        arrondi = _round_sig(_sci_to_float(val, comma_is_decimal=False), n_sig)
    except (ValueError, OverflowError):
        return ""
    texte = (
        str(int(arrondi)) if arrondi == int(arrondi) else format_wims_float(arrondi)
    )
    return f"{texte} {unite}".strip()


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


def coord_display_answer(expected: str) -> str:
    """Un clic qui tombe dans la click-zone — le centre, quand il en a un.

    Un `coord` n'attend pas une zone mais un **point** : `reply` est le pixel
    cliqué. L'attendu, lui, décrit la cible (`circle,110,80,30/3`,
    `point,204,338`, `rectangle,x1,y1,x2,y2`). Les confondre revient à demander
    à l'élève de saisir la consigne, comme les bornes d'un `range` ou le `#N`
    d'un `sigunits`.

    Rend `""` pour les formes dont le centre ne se calcule pas — `polygon`
    demanderait le centroïde.
    """
    from core.oef.numfmt import format_wims_float  # noqa: PLC0415

    # Seule la première zone est la bonne réponse (cf. `check_coord`) ; les
    # suivantes servent au diagnostic.
    premiere = _declosing(expected or "").split(";")[0]
    # Une ligne peut offrir plusieurs régions, séparées par `|` (cf.
    # `_ligne_zone`) : la première suffit à répondre.
    premiere = _coupe_hors_parentheses(premiere, "|")[0]
    parts = [p.strip() for p in _declosing(premiere).split(",")]
    if (parts and parts[0].strip().lower().startswith("b")
            and len(parts) >= 4 and parts[1].strip()):
        # `b,<figure>,x,y` : le point de référence de la région **est** un clic
        # valide, puisqu'il appartient par construction à la zone visée.
        return f"{parts[2].strip()},{parts[3].strip()}"
    if len(parts) < 2:
        return ""
    shape = parts[0].lower()
    vals: list[float] = []
    for v in parts[1:]:
        if not v:
            continue
        try:
            vals.append(_eval_scalar(v, comma_is_decimal=False))
        except ValueError:
            return ""
    if shape.startswith(("point", "circle", "ellipse")) and len(vals) >= 2:
        # Les deux premières composantes sont le centre dans les trois cas ;
        # `point` accepte plusieurs cibles, la première suffit.
        return f"{format_wims_float(vals[0])},{format_wims_float(vals[1])}"
    if shape.startswith("rectangle") and len(vals) >= 4:
        return (f"{format_wims_float((vals[0] + vals[2]) / 2)},"
                f"{format_wims_float((vals[1] + vals[3]) / 2)}")
    return ""


def sigunits_display_answer(expected: str, comma_is_decimal: bool = True) -> str:
    """La valeur affichée en corrigé pour un `sigunits`.

    L'attendu est stocké `"<valeur> <unité> #N"`, où `#N` n'est pas une réponse
    mais une **consigne** : le nombre de chiffres significatifs exigé. Montré
    tel quel, le corrigé d'`astron2` affichait `74753832.77 km^2 #4` — la
    valeur que l'élève devait justement arrondir, suivie d'un marqueur qui ne
    veut rien dire pour lui. On rend ce qu'on lui demandait : `7.475e7 km^2`.

    Chez WIMS le corrigé passe par `!exec units-filter` en mode `o`
    (`anstype/sigunits`), un binaire externe que PAX ne reproduit pas ; on s'en
    tient à la valeur arrondie et à son unité, ce que le checker attend.
    """
    from core.oef.numfmt import format_wims_float  # noqa: PLC0415

    m = re.match(r"^(.*?)\s*#\s*(\d+)\s*$", (expected or "").strip(), re.DOTALL)
    if not m:
        return expected
    n_sig = int(m.group(2))
    val, unit = _split_sci_value_unit(m.group(1))
    if val is None:
        return m.group(1).strip()
    try:
        arrondi = _round_sig(_sci_to_float(val, comma_is_decimal), n_sig)
    except (ValueError, OverflowError):
        return m.group(1).strip()
    texte = format_wims_float(arrondi) if arrondi != int(arrondi) else str(int(arrondi))
    # Au-delà de N chiffres devant la virgule, la forme décimale ferait croire
    # à une précision qu'on vient justement de retirer (74750000 pour quatre
    # chiffres significatifs) : la notation scientifique la rend visible.
    if arrondi and abs(arrondi) >= 10 ** n_sig:
        mant = arrondi / 10 ** math.floor(math.log10(abs(arrondi)))
        expo = math.floor(math.log10(abs(arrondi)))
        texte = f"{format_wims_float(round(mant, n_sig - 1))}e{expo}"
    return f"{texte} {unit}".strip()


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


def _coords(s: str) -> list[float]:
    """Les nombres d'une liste de coordonnées, chacun **évalué** : le corpus y
    écrit des expressions (`400-0.087*400`, `160+2*200/5`)."""
    out: list[float] = []
    for morceau in s.split(","):
        morceau = morceau.strip()
        if not morceau:
            continue
        try:
            out.append(_eval_scalar(morceau, comma_is_decimal=False))
        except ValueError:
            return []
    return out


def check_jsxgraphcurve(
    reply: str, expected: str, options: dict | None = None
) -> CheckResult:
    """Figure tracée sur une image — `anstype/jsxgraphcurve`.

    L'attendu s'écrit `<image>;<forme>,<coordonnées…>` et la forme choisit le
    comparateur, chacun dans son `anstype/javacurve.<forme>`. Le corpus n'en
    emploie que quatre, portés ici avec leurs précisions par défaut :

    * `points` (15) — chaque point attendu doit trouver un point de l'élève à
      moins de `precision` ; il faut ni manque ni excédent, et le partiel suit
      `max(0, Bon - trop)` ;
    * `vector` (10) — les deux extrémités coïncident, à `max` des deux écarts ;
    * `line` (5) — même **droite**, comparée par ses coefficients normalisés
      `a = y₁-y₂`, `b = x₂-x₁`, `c = y₁x₂-x₁y₂` : deux droites sont égales si
      `max(|t1|, |t2|)` reste sous la précision ;
    * `sline` (5) — la demi-droite : `line`, plus l'origine commune (`t3`) et
      le même sens (`t4 > 0`).

    Ces onze rendus étaient notés par comparaison de chaînes, ce qui ne
    reconnaissait que la figure écrite exactement comme l'auteur l'avait
    stockée.
    """
    options = options or {}
    opt = str(options.get("option", ""))
    m = re.search(r"precision\s*=\s*([\d.]+)", opt)

    zone = (expected or "").split(";", 1)[-1].strip()
    forme, _, coords_att = zone.partition(",")
    forme = forme.strip().lower()
    g = _coords(coords_att)
    # La réponse peut arriver préfixée `free=…` (`!getopt free in $reply`).
    brut = (reply or "").split("=", 1)[-1] if "=" in (reply or "") else (reply or "")
    r = _coords(brut.replace(";", ","))
    if not g or not r:
        return CheckResult(correct=False, score=0.0, method="jsxgraphcurve")

    def resultat(bon: bool, score: float | None = None) -> CheckResult:
        note = (1.0 if bon else 0.0) if score is None else score
        return CheckResult(correct=bon, score=note, method="jsxgraphcurve")

    if forme == "points":
        precision = float(m.group(1)) if m else 15.0
        att = [(g[i], g[i + 1]) for i in range(0, len(g) - 1, 2)]
        rep = [(r[i], r[i + 1]) for i in range(0, len(r) - 1, 2)]
        if not att:
            return resultat(False)
        trouves = sum(
            any(math.hypot(ax - bx, ay - by) < precision for bx, by in rep)
            for ax, ay in att
        )
        part_bonne = trouves / len(att)
        trop = (len(rep) - trouves) / len(att)
        manque = 1 - part_bonne
        if trop == 0 and manque == 0:
            return resultat(True)
        note = max(0.0, part_bonne - trop)
        return resultat(part_bonne > trop + manque, min(1.0, note))

    if forme == "vector":
        precision = float(m.group(1)) if m else 10.0
        if len(g) < 4 or len(r) < 4:
            return resultat(False)
        ecart = max(math.hypot(g[0] - r[0], g[1] - r[1]),
                    math.hypot(g[2] - r[2], g[3] - r[3]))
        return resultat(ecart < precision)

    if forme in ("line", "sline"):
        precision = float(m.group(1)) if m else 5.0
        if len(g) < 4 or len(r) < 4:
            return resultat(False)
        ga, gb = g[1] - g[3], g[2] - g[0]
        gc = g[1] * g[2] - g[0] * g[3]
        ra, rb = r[1] - r[3], r[2] - r[0]
        rc = r[1] * r[2] - r[0] * r[3]
        gm, rm = max(abs(ga), abs(gb)), max(abs(ra), abs(rb))
        # Deux points confondus ne définissent pas de droite.
        if gm < precision or rm < precision:
            return resultat(False)
        t1 = (ga * rb - gb * ra) / gm
        t2 = (ga * rc - gc * ra) if abs(ga) > abs(gb) else (gb * rc - gc * rb)
        t2 /= gm ** 2
        ecart = max(abs(t1), abs(t2))
        if forme == "line":
            return resultat(ecart < precision)
        # `sline` : même origine, et même sens que le vecteur attendu.
        t3 = math.hypot(g[0] - r[0], g[1] - r[1])
        t4 = (g[2] - g[0]) * (r[2] - g[1]) + (g[3] - g[1]) * (r[3] - g[1])
        return resultat(max(ecart, t3) < precision and t4 > 0)

    return CheckResult(correct=False, score=0.0, method="jsxgraphcurve")


def check_chemeq(reply: str, expected: str) -> CheckResult:
    """Équation chimique — `anstype/chemeq`.

    WIMS passe par `slib/chemistry/chemeq_compare`, qui normalise les deux
    écritures avec `chemeq -n` et compare les chaînes obtenues. PAX compare le
    **sens** : deux équations sont les mêmes si chaque membre coïncide à un
    seul et même facteur d'échelle près (`chemeq.equations_equivalentes`).

    Le résultat est le même là où le binaire fonctionne — vérifié sur douze
    couples représentatifs, états, charges et groupes parenthésés compris. Il
    en diffère là où le binaire échoue : `Fe2(SO4)3 -> Fe2(SO4)3` lui fait
    rendre ` -> `, donc deux membres vides qu'il déclare égaux — n'importe
    quelle réponse y passerait.

    Sans ce cas, `chemeq` tombait dans le repli `check_text` : seule la chaîne
    stockée au caractère près était acceptée. Une espace en plus (`Fe + 3/2 Cl2`)
    ou des coefficients mis à l'échelle (`2Fe + 3Cl2 -> 2FeCl3`) — que WIMS
    accepte — étaient comptés faux. Le test du corpus ne le voyait pas : il
    soumet l'attendu lui-même, donc la seule écriture qui passait.
    """
    from core.oef.def_engine.chemeq import equations_equivalentes  # noqa: PLC0415

    bon = equations_equivalentes(reply, expected)
    return CheckResult(correct=bon, score=1.0 if bon else 0.0, method="chemeq")


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


def _ligne_zone(cx: float, cy: float, ligne: str, options: dict | None) -> bool:
    """Une **ligne** de click-zone — port d'`oneline` (`Misc/clickzone.c:231`).

    Une ligne n'est pas une zone unique : c'est une expression booléenne sur
    des zones, avec `|` pour le ou, `&` pour le et, `^` pour la négation et des
    parenthèses pour grouper. `oefpolygon/quadrilatere` s'en sert pour offrir
    plusieurs régions acceptables — « le quadrilatère est concave » en admet
    quatre —, séparées par des `|`.

    Les séparateurs se lisent à profondeur de parenthèses zéro (`strparchr`),
    sans quoi la virgule interne d'une zone couperait au mauvais endroit.
    """
    p = (ligne or "").strip()
    morceaux = _coupe_hors_parentheses(p, "|")
    if len(morceaux) > 1:
        return any(_ligne_zone(cx, cy, m, options) for m in morceaux)
    morceaux = _coupe_hors_parentheses(p, "&")
    if len(morceaux) > 1:
        return all(_ligne_zone(cx, cy, m, options) for m in morceaux)

    inverse = False
    if p.startswith("^"):
        inverse = True
        p = p[1:].strip()
    if not p:
        # `if(*p1==0) return rev^1` : une ligne vide est vraie, sa négation fausse.
        return not inverse
    if p.startswith("("):
        fin = _appariement(p, 1, ")")
        if fin >= 0:
            return _ligne_zone(cx, cy, p[1:fin], options) != inverse
    return _zone_contient(cx, cy, p, options) != inverse


def _coupe_hors_parentheses(s: str, sep: str) -> list[str]:
    """Découpe sur `sep` à profondeur de parenthèses zéro (`strparchr`)."""
    parts, courant, profondeur = [], [], 0
    for ch in s:
        if ch == "(":
            profondeur += 1
        elif ch == ")":
            profondeur = max(0, profondeur - 1)
        if ch == sep and profondeur == 0:
            parts.append("".join(courant))
            courant = []
        else:
            courant.append(ch)
    parts.append("".join(courant))
    return [x.strip() for x in parts]


def _appariement(s: str, depart: int, fermant: str) -> int:
    """Index du `fermant` appariant l'ouvrant qui précède `depart`, ou -1."""
    profondeur = 1
    for i in range(depart, len(s)):
        if s[i] == "(":
            profondeur += 1
        elif s[i] == fermant:
            profondeur -= 1
            if profondeur == 0:
                return i
    return -1


def _segments_du_svg(svg: str) -> list[tuple[tuple[float, float], tuple[float, float]]]:
    """Les frontières d'une figure SVG, en segments.

    On ne lit que les primitives que flydraw produit pour un **tracé** :
    polylignes (les courbes et les `plot`), lignes, polygones et le cadre.
    Les arcs (`<path>`) sont hors de cette lecture — aucune figure du corpus
    n'en fait une frontière de région.
    """
    segs: list[tuple[tuple[float, float], tuple[float, float]]] = []

    def suite(points: list[tuple[float, float]], ferme: bool = False) -> None:
        for i in range(len(points) - 1):
            segs.append((points[i], points[i + 1]))
        if ferme and len(points) > 2:
            segs.append((points[-1], points[0]))

    def lis_points(brut: str) -> list[tuple[float, float]]:
        nombres = [float(x) for x in re.findall(r"-?\d+(?:\.\d+)?", brut)]
        return [(nombres[i], nombres[i + 1]) for i in range(0, len(nombres) - 1, 2)]

    for m in re.finditer(r'<polyline[^>]*points="([^"]*)"', svg):
        suite(lis_points(m.group(1)))
    for m in re.finditer(r'<polygon[^>]*points="([^"]*)"', svg):
        suite(lis_points(m.group(1)), ferme=True)
    for m in re.finditer(
        r'<line[^>]*x1="([-\d.]+)"[^>]*y1="([-\d.]+)"[^>]*x2="([-\d.]+)"[^>]*y2="([-\d.]+)"',
        svg,
    ):
        x1, y1, x2, y2 = (float(v) for v in m.groups())
        segs.append(((x1, y1), (x2, y2)))
    for m in re.finditer(
        r'<rect[^>]*x="([-\d.]+)"[^>]*y="([-\d.]+)"[^>]*width="([-\d.]+)"[^>]*height="([-\d.]+)"',
        svg,
    ):
        x, y, w, h = (float(v) for v in m.groups())
        suite([(x, y), (x + w, y), (x + w, y + h), (x, y + h)], ferme=True)
    for m in re.finditer(
        r'<circle[^>]*cx="([-\d.]+)"[^>]*cy="([-\d.]+)"[^>]*r="([-\d.]+)"', svg
    ):
        cx, cy, r = (float(v) for v in m.groups())
        pts = [
            (cx + r * math.cos(2 * math.pi * k / 64), cy + r * math.sin(2 * math.pi * k / 64))
            for k in range(64)
        ]
        suite(pts, ferme=True)
    return segs


def _meme_region_svg(
    clic: tuple[float, float], repere: tuple[float, float], svg: str
) -> bool:
    """Les deux points sont-ils dans la même région de la figure ?

    WIMS répond en **remplissant** l'image bitmap depuis le clic et en
    regardant si le point de référence a pris la couleur. PAX n'a pas de
    bitmap : sa figure est vectorielle. La question se reformule alors
    exactement — deux points sont dans la même région si le segment qui les
    joint ne croise **aucune** frontière tracée.

    L'équivalence est stricte tant que les régions sont convexes, ce qui est le
    cas d'un découpage par des droites — celui de `oefpolygon/quadrilatere`,
    seul `bound` du corpus. Sur une région en croissant, un chemin droit
    pourrait sortir et revenir : la réponse serait alors trop sévère, jamais
    trop permissive.
    """
    from core.oef.flydraw import _segment_intersection  # noqa: PLC0415

    trajet = (clic, repere)
    for frontiere in _segments_du_svg(svg):
        if _segment_intersection(trajet, frontiere) is not None:
            return False
    return True


def _bound_atteint(clic: tuple[float, float], zone: list[str], images_dir: str) -> bool:
    """Zone ``b,<fichier.gif>,x,y`` — appartenance à une **région de l'image**.

    Portage de la branche `bound` de `Misc/clickzone.c` : elle remplit l'image
    par diffusion depuis le point cliqué, puis regarde si le point de référence
    de la zone a pris la couleur. Deux points d'un même département de
    `dept.gif` communiquent ; le tracé les sépare de leurs voisins.

    Le C distingue deux formes selon le nombre de coordonnées données (`T`) :
    sans point de référence, il compare simplement la couleur du clic à celle
    du coin (1,1), c'est-à-dire au fond. Les deux sont ici.
    """
    from core.oef.def_engine.gif import GifError, lire_gif  # noqa: PLC0415

    if len(zone) < 2:
        return False
    fichier = zone[1].strip()

    # Figure produite par PAX : `$ins_filename` porte l'URL de son SVG, et la
    # région se teste en géométrie plutôt que par remplissage.
    m_svg = re.search(r"/api/render/svg/([a-f0-9]+)", fichier)
    if m_svg is not None:
        from core.oef.flydraw import get_cached_svg  # noqa: PLC0415

        svg = get_cached_svg(m_svg.group(1))
        reperes_svg = [v.strip() for v in zone[2:] if v.strip()]
        if not svg or len(reperes_svg) < 2:
            return False
        try:
            rx, ry = float(reperes_svg[0]), float(reperes_svg[1])
        except ValueError:
            return False
        return _meme_region_svg(clic, (rx, ry), svg)

    if not images_dir:
        return False
    if not fichier or "/" in fichier or ".." in fichier:
        return False
    from core.oef.flydraw import _RESSOURCES_ROOT  # noqa: PLC0415

    # `images_dir` est relatif à la racine des ressources (cf. le moteur).
    chemin = _osp.join(_RESSOURCES_ROOT, images_dir, fichier)
    if not _osp.isfile(chemin):
        return False
    try:
        image = lire_gif(chemin)
    except (GifError, OSError):
        return False
    cx, cy = int(clic[0]), int(clic[1])
    reperes = [v.strip() for v in zone[2:] if v.strip()]
    if len(reperes) < 2:
        # `T == 0` : est-on ailleurs que sur le fond ?
        couleur = image.pixel(cx, cy)
        return couleur is not None and couleur != image.pixel(1, 1)
    try:
        rx, ry = int(float(reperes[0])), int(float(reperes[1]))
    except ValueError:
        return False
    return image.region_atteint((cx, cy), (rx, ry))


def check_coord(reply: str, expected: str, options: dict | None = None) -> CheckResult:
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

    # `clickzone.c` lit **une zone par ligne** et imprime le rang de la
    # première qui contient le clic ; le moteur les joint par `;`. Mais
    # `anstype/coord` ne retient ce rang que s'il vaut 1 :
    #
    #     !distribute words $test1 into i_,prec
    #     !if $i_=1
    #
    # La bonne réponse est donc le clic dans la **première** zone, les
    # suivantes servant au diagnostic — la carte d'`oefdepregfr` y range les
    # autres départements pour pouvoir colorier celui qu'il fallait. Accepter
    # n'importe laquelle rendrait l'exercice trivial.
    zones = [z.strip() for z in _declosing(expected or "").split(";") if z.strip()]
    # Une *ligne* de zones n'est pas une zone : `oneline` y lit une expression
    # booléenne (`|`, `&`, `^`, parenthèses). Plusieurs régions acceptables s'y
    # écrivent donc sur la même ligne, séparées par des `|`.
    ok = bool(zones) and _ligne_zone(cx, cy, zones[0], options)
    return CheckResult(correct=ok, score=1.0 if ok else 0.0, method="coord")


# Nombre de coordonnées par objet tracé (`anstype/draw`, bloc `type_cnt`).
_DRAW_TAILLES: dict[str, int] = {
    "points": 2, "crosshairs": 2, "polyline": 2, "polygon": 2,
    "circles": 3,
    "segments": 4, "arrows": 4, "arrows2": 4, "rects": 4,
    "lines": 4, "demilines": 4,
    "curvedarrows": 6, "curvedarrows2": 6,
}
# Types dont un objet se lit à l'envers aussi bien qu'à l'endroit.
_DRAW_SYMETRIQUES = frozenset({"segments", "arrows2", "rects"})


def check_draw(reply: str, expected: str, options: dict | None = None) -> CheckResult:
    r"""Type ``draw`` : l'élève trace des objets sur une figure.

    Port d'``anstype/draw`` et de son ``draw.inc``. ``expected`` porte deux
    rangées — la figure de fond, puis ``<type>,<coordonnées…>`` :

        [xrange …\npolygon black, …];crosshairs,1.596,-0.044,-2.128,-0.966

    ``reply`` est la liste plate des coordonnées posées par l'élève, **dans le
    repère du dessin** et non en pixels.

    La comparaison est un appariement glouton : chaque objet rendu cherche le
    premier attendu dont il s'écarte de moins de ``1/precision``, et chacun ne
    sert qu'une fois. L'écart est la distance euclidienne du premier point,
    doublée du second quand l'objet en a deux (``draw.inc``, ``ecart1`` /
    ``ecart2``, dont le maximum décide).

    Le barème suit `anstype/draw` : tout ou rien par défaut ; avec ``split`` ou
    ``partialscore`` une pénalité pleine par objet en trop ou manquant, avec
    ``eqweight`` une demi-pénalité.

        score = max(0, min(1, (justes − coeff·max(en trop, manquants)) / attendus))
    """
    opts = options or {}
    opt_str = str(opts.get("option", "") or "")

    rangees = _rangees_draw(expected or "")
    ligne_bonne = rangees[1] if len(rangees) > 1 else ""
    morceaux = [x.strip() for x in ligne_bonne.split(",")]
    type_objet = re.sub(r"[0-9.]", "", morceaux[0] if morceaux else "").strip()
    if type_objet.startswith("poly") and type_objet not in ("polyline", "polygon"):
        type_objet = "polygon"
    largeur = _DRAW_TAILLES.get(type_objet, 2)

    bons = _nombres(",".join(morceaux[1:]))
    rendus = _nombres(reply or "")
    if not bons:
        return CheckResult(correct=False, score=0.0, method="draw")

    # `!default precision=1000` ; l'auteur la règle par `precision=` dans
    # `replyoption`. Un `precision=0` est ignoré, comme dans le script.
    tolerance = 1.0 / 1000.0
    m = re.search(r"precision\s*=\s*([0-9.]+)", opt_str)
    if m:
        try:
            p = float(m.group(1))
            if p:
                tolerance = 1.0 / p
        except ValueError:
            pass

    attendus = _objets_draw(bons, largeur, type_objet)
    poses = _objets_draw(rendus, largeur, type_objet)
    if not attendus:
        return CheckResult(correct=False, score=0.0, method="draw")

    pris: set[int] = set()
    justes = 0
    for objet in poses:
        for i, cible in enumerate(attendus):
            if i in pris:
                continue
            if _ecart_draw(objet, cible, type_objet) < tolerance:
                pris.add(i)
                justes += 1
                break

    en_trop = len(poses) - justes
    manquants = len(attendus) - len(pris)

    if "eqweight" in opt_str:
        coeff = 0.5
    elif "split" in opt_str or "partialscore" in opt_str:
        coeff = 1.0
    else:
        coeff = 0.0

    if coeff == 0:
        score = 1.0 if (manquants == 0 and en_trop == 0) else 0.0
    else:
        score = max(
            0.0,
            min(1.0, (justes - coeff * max(en_trop, manquants)) / len(attendus)),
        )
    return CheckResult(correct=score >= 1.0, score=score, method="draw")


def draw_display_answer(expected: str) -> str:
    """Les coordonnées attendues d'un `type=draw`, sans la figure ni le type.

    `expected` juxtapose le fond et la réponse — `[<figure>];crosshairs,1.59,…`.
    C'est la seconde partie, privée de son mot de tête, que l'élève produit en
    traçant : la rendre séparément sert à afficher le corrigé, et au test qui
    rejoue la bonne réponse.
    """
    rangees = _rangees_draw(expected or "")
    if len(rangees) < 2:
        return ""
    _, _, coords = rangees[1].strip().partition(",")
    return coords.strip()


def draw_feedback_answer(expected: str) -> str:
    """Les coordonnées attendues, groupées par objet pour la lecture.

    `draw_display_answer` rend la liste plate, celle que l'élève produit ;
    affichée telle quelle, « 3,3,1,-3 » se lit comme quatre nombres alors que
    ce sont deux points. On les rend donc `(3, 3) ; (1, -3)`.
    """
    plat = draw_display_answer(expected)
    if not plat:
        return ""
    rangees = _rangees_draw(expected or "")
    tete = rangees[1].strip().split(",", 1)[0] if len(rangees) > 1 else ""
    type_objet = re.sub(r"[0-9.]", "", tete).strip()
    if type_objet.startswith("poly") and type_objet not in ("polyline", "polygon"):
        type_objet = "polygon"
    largeur = _DRAW_TAILLES.get(type_objet, 2)
    morceaux = [m.strip() for m in plat.split(",") if m.strip()]
    if largeur < 2 or len(morceaux) < largeur:
        return plat
    groupes = [
        "(" + ", ".join(morceaux[i : i + largeur]) + ")"
        for i in range(0, len(morceaux) - largeur + 1, largeur)
    ]
    return " ; ".join(groupes)


def _rangees_draw(s: str) -> list[str]:
    """Rangées d'un `replygood` de `draw` : les `;` hors crochets.

    La figure de fond est entre crochets et peut contenir des `;` comme des
    sauts de ligne ; seuls les `;` de profondeur zéro séparent."""
    parts: list[str] = []
    courant: list[str] = []
    profondeur = 0
    for ch in s:
        if ch in "([{":
            profondeur += 1
        elif ch in ")]}":
            profondeur = max(0, profondeur - 1)
        if ch == ";" and profondeur == 0:
            parts.append("".join(courant))
            courant = []
        else:
            courant.append(ch)
    parts.append("".join(courant))
    return parts


def _nombres(s: str) -> list[float]:
    return [float(x) for x in re.findall(r"-?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?", s or "")]


def _objets_draw(plat: list[float], largeur: int, type_objet: str) -> list[list[float]]:
    """Découpe une liste plate de coordonnées en objets de `largeur` nombres.

    `polyline` et `polygon` font exception : WIMS y voit **un seul** objet, dont
    chaque sommet est comparé — on garde donc les points deux à deux, comme
    pour `points`, ce que fait `type_cnt=2` dans le script.
    """
    del type_objet  # même découpage pour tous : `type_cnt` porte déjà la nuance
    if largeur <= 0:
        return []
    return [plat[i : i + largeur] for i in range(0, len(plat) - largeur + 1, largeur)]


def _ecart_draw(a: list[float], b: list[float], type_objet: str) -> float:
    """L'écart de `draw.inc` : le pire des deux extrémités.

    Pour un objet à deux points, WIMS compare aussi l'ordre inverse quand le
    type est symétrique (`segments`, `arrows2`, `rects` : le script en ajoute
    la version retournée à la liste des bonnes réponses).
    """
    def dist(x1, y1, x2, y2):
        return math.hypot(x1 - x2, y1 - y2)

    if len(a) < 2 or len(b) < 2:
        return float("inf")
    if len(a) == 2:
        return dist(a[0], a[1], b[0], b[1])
    if len(a) == 3:  # circles : centre puis rayon
        return max(dist(a[0], a[1], b[0], b[1]), abs(a[2] - b[2]))
    direct = max(dist(a[0], a[1], b[0], b[1]), dist(a[2], a[3], b[2], b[3]))
    if type_objet in _DRAW_SYMETRIQUES:
        inverse = max(dist(a[0], a[1], b[2], b[3]), dist(a[2], a[3], b[0], b[1]))
        return min(direct, inverse)
    return direct


def _zone_contient(cx: float, cy: float, zone: str, options: dict | None) -> bool:
    """Le clic tombe-t-il dans cette click-zone ? (`test()` de `clickzone.c`)"""
    parts = [p.strip() for p in _declosing(zone).split(",")]
    if not parts:
        return False
    shape = parts[0].lower()
    if shape in ("b", "bound") or shape.startswith("bound"):
        return _bound_atteint((cx, cy), parts, (options or {}).get("images_dir", ""))
    # Les composantes d'une click-zone sont des **expressions**, pas des
    # littéraux : `getvalue` (`Misc/clickzone.c`) passe chaque item au
    # calculateur. `somvect` pose `circle,110,80,30/3` et `tracredstep`
    # `circle,200,200-20*7,9`. Ne garder que les nombres purs, comme le
    # faisait un filtre par expression régulière, laissait le cercle sans
    # rayon — et refusait alors tous les clics.
    vals: list[float] = []
    for v in parts[1:]:
        if not v:
            continue
        try:
            vals.append(_eval_scalar(v, comma_is_decimal=False))
        except ValueError:
            continue

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


# Les tirets qu'un élève peut poser à la place du trait d'union-moins ASCII.
# Le signe moins typographique `−` (U+2212) est celui que produisent un
# copier-coller depuis un énoncé mathématique, le pavé numérique de certains
# systèmes et l'autocorrection de plusieurs traitements de texte ; les tirets
# demi-cadratin et cadratin viennent des mêmes autocorrections. Sans cette
# table, `−1` était refusé comme « non reconnu comme un nombre » alors que la
# réponse est juste.
#
# C'est une tolérance propre à PAX, non une règle WIMS : le moteur d'origine
# travaille en ISO-8859-1 et ne rencontre aucun de ces caractères. Elle
# n'assouplit donc aucun verdict que WIMS rendrait — elle rattrape une saisie
# que lui n'aurait jamais reçue.
_MOINS_UNICODE = {
    ord("\u2212"): "-",  # signe moins
    ord("\u2013"): "-",  # tiret demi-cadratin
    ord("\u2014"): "-",  # tiret cadratin
    ord("\u2010"): "-",  # trait d'union
    ord("\u2011"): "-",  # trait d'union insécable
}


def _parse_number(s: str, comma_is_decimal: bool = True) -> float:
    """Parse un nombre : entier, décimal, fraction, expression simple.

    ``comma_is_decimal`` (vrai par défaut, locales à virgule) traite la virgule
    comme séparateur décimal — on accepte alors aussi le point (``3,5`` et
    ``3.5`` valent 3,5). En locale à point, la virgule n'est PAS décimale : un
    ``3,5`` n'est pas reconnu comme un nombre (il échoue au parsing).
    """
    s = s.strip().translate(_MOINS_UNICODE)
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
            # `anstype/algexp` ne s'arrête pas à `ratsimp(good-dd)=0` : il exige
            # aussi `$t2 isitemof $t1`, où `t1` et `t2` sont ce que Maxima
            # **imprime** de l'attendu et de la réponse — leur forme après sa
            # simplification automatique, qui replie les coefficients
            # (`(24+4)*x` → `28*x`) et ordonne les termes (`x-y*y` → `x-y^2`)
            # mais ne développe pas un produit. Le manuel (§1.3.5.2) en donne
            # la conséquence : `(x+1)(x-1)` est refusé pour `x^2-1`. La
            # simplification automatique de sympy fait les mêmes replis, et
            # l'égalité structurelle des deux arbres joue le rôle du `isitemof`.
            if correct and r_expr != e_expr:
                return CheckResult(
                    correct=False, score=0.0, method="algexp_badform",
                    status="invalid_format", detail=_REWRITE_MSG,
                )
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


def check_function(
    reply: str, expected: str, precision: float, comma_is_decimal: bool = True,
    plage: tuple[float, float] | None = None, precweight: float = 0.5,
) -> CheckResult:
    """Type ``function`` — comparaison **numérique** sur ``\\range``.

    Port de `anstype/function`. L'attendu est `fonction, var1, var2…` : le
    premier item est la fonction, les suivants les variables autorisées en
    plus des siennes. Une variable de la réponse qui n'y figure pas est une
    `bad_variable` (`5*t` refusé pour `5*x`). Puis, sur des points tirés dans
    `[leftrange, rightrange]` — `\\range`, défaut `[-5,5]` — l'écart moyen
    `|reply − good|` décide :

        < 1/precision        → juste
        < 1/sqrt(precision)  → juste « à la précision près » (`precgood`)

    C'est pourquoi `5*x+0.000001` vaut `5*x` (§1.3.5.1) : la comparaison
    symbolique, qui tenait lieu de `function` jusqu'ici, ne pouvait pas le voir.

    Le nombre de points, `$testnum`, n'est défini nulle part dans l'arbre WIMS
    que nous avons ; vingt points tirés d'une graine fixe donnent une mesure
    stable et suffisamment serrée. C'est une hypothèse, consignée comme telle.
    """
    import sympy
    from sympy.parsing.sympy_parser import (
        parse_expr, standard_transformations, implicit_multiplication_application,
    )
    transformations = standard_transformations + (implicit_multiplication_application,)
    items = [x.strip() for x in _split_top_level(expected, ",") if x.strip()]
    if not items:
        return CheckResult(correct=False, score=0.0, method="function")
    good_src, extra_vars = items[0], items[1:]
    try:
        loc = _safe_locals()
        good = parse_expr(_normalize_expr(good_src, comma_is_decimal),
                          transformations=transformations, local_dict=loc)
        rep = parse_expr(_normalize_expr(reply, comma_is_decimal),
                         transformations=transformations, local_dict=loc)
    except Exception:
        return CheckResult(correct=False, score=0.0, method="function",
                           detail="Expression non reconnue")
    # `2*x+1, 4` parse en tuple, `{1,2}` en ensemble : ni l'un ni l'autre n'est
    # une fonction à échantillonner. WIMS les enverrait à Maxima, qui bute
    # aussi ; on refuse sans juger.
    if not isinstance(good, sympy.Expr) or not isinstance(rep, sympy.Expr):
        return CheckResult(correct=False, score=0.0, method="function",
                           status="invalid_format", detail="Expression non reconnue")
    constantes = {"e", "E", "pi", "Pi", "PI"}
    permises = ({str(v) for v in good.free_symbols} | {v for v in extra_vars}) - constantes
    inconnues = {str(v) for v in rep.free_symbols} - permises - constantes
    if inconnues:
        return CheckResult(correct=False, score=0.0, method="function",
                           status="invalid_format",
                           detail=f"Variable inconnue : {', '.join(sorted(inconnues))}")
    gauche, droite = plage if plage else (-5.0, 5.0)
    symboles = {v: sympy.Symbol(v) for v in sorted(permises)}
    import random as _random
    rng = _random.Random(20260906)
    ecart = 0.0
    n_points = 20
    for _ in range(n_points):
        point = {sym: rng.uniform(gauche, droite) for sym in symboles.values()}
        try:
            g = complex(good.subs(point).evalf())
            r = complex(rep.subs(point).evalf())
        except Exception:
            return CheckResult(correct=False, score=0.0, method="function")
        if not (math.isfinite(g.real) and math.isfinite(r.real)):
            return CheckResult(correct=False, score=0.0, method="function")
        ecart += abs(r - g)
    ecart /= n_points
    if ecart < 1 / precision:
        return CheckResult(correct=True, score=1.0, method="function")
    if ecart < 1 / math.sqrt(precision):
        return CheckResult(correct=False, score=precweight, method="function",
                           detail=_POOR_PRECISION_MSG)
    return CheckResult(correct=False, score=0.0, method="function")


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


# `f'`, `f''`, et la variante typographique que produit un traitement de texte
# ou un clavier français. Le nom doit précéder l'apostrophe : celle d'un mot
# (`l'aire`) n'a pas cette forme dans une expression.
_DERIVEE_APOSTROPHE_RE = re.compile(r"([A-Za-z]\w*)(['’]+)")


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
    # Dérivée notée par une apostrophe : `f'(x)` devient un nom de fonction à
    # part entière. Python y lisait le début d'une f-string — littéralement,
    # `parse_expr("f'(x_i)")` lève « unterminated f-string literal » —, le
    # parse échouait, le repli numérique échouait avec lui, et le score tombait
    # à 0 : l'attendu se refusait lui-même dans `euler1`, `euler2` et
    # `tangente1`. WIMS n'a pas d'opérateur apostrophe non plus ; `f'` y est un
    # nom, que la comparaison distingue de `f` sans jamais dériver quoi que ce
    # soit. Traduire plutôt que dériver garde cette sémantique, et une dérivée
    # seconde reste distincte d'une première.
    expr = _DERIVEE_APOSTROPHE_RE.sub(
        lambda m: m.group(1) + "_prime" * len(m.group(2)), expr
    )
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


# `numexp2` : la fraction demandée n'a pas à être irréductible.
_NUMEXP2_ZERO_MSG = "Pour une valeur nulle, écrivez simplement 0."

# `[+-]? nombre ( / nombre )?` — le signe ne peut porter que sur la tête, le
# fichier rejetant tout `-` ou `+` après le premier caractère.
_NUMEXP2_RE = re.compile(
    r"(?P<signe>[+-]?)(?P<num>\d+(?:\.\d*)?|\.\d+)"
    r"(?:/(?P<den>\d+(?:\.\d*)?|\.\d+))?"
)


def _numexp2_rationnel(s: str) -> Fraction | None:
    """Valeur exacte d'une écriture `a`, `a/b` ou `-a/b`, décimales comprises.

    `None` si l'écriture sort de cette grammaire — le fichier du module parle
    alors de `nocompute` : ce n'est pas une réponse fausse, c'est une réponse
    hors format.
    """
    m = _NUMEXP2_RE.fullmatch(s)
    if m is None:
        return None
    try:
        val = Fraction(m.group("num"))
        if m.group("den") is not None:
            den = Fraction(m.group("den"))
            if den == 0:
                # Un dénominateur nul ne franchit pas `!if NaN isin $test` :
                # le fichier sort sans verdict, ce qui vaut ici hors format.
                return None
            val /= den
    except (ValueError, ZeroDivisionError):
        return None
    return -val if m.group("signe") == "-" else val


def check_numexp2(
    reply: str, expected: str, comma_is_decimal: bool = True
) -> CheckResult:
    """Type `numexp2` — défini par le module `OEFevalwimsfrac`
    (`anstype/numexp2`), employé par ses six exercices sur les fractions.

    C'est le `numexp` du cœur amputé de sa contrainte d'irréductibilité, ce qui
    est tout l'objet du module : `6/4` y **vaut** `3/2`, l'élève apprenant
    d'abord à écrire un quotient avant d'apprendre à le réduire. Le fichier
    compare par produit en croix (`t1_reply*t2_replygood - t1_replygood*t2_reply`)
    après avoir chassé les décimales des deux côtés — soit, ici, l'égalité de
    deux `Fraction`.

    Ce qu'il refuse, en revanche :

    - toute **opération** — `+ - * ^ (` après un éventuel signe de tête, ou une
      seconde barre de fraction (`c>2`) : `test=NaN nocompute` ;
    - un attendu nul auquel l'élève répond autre chose que le texte `0` —
      `!if $good=0 and $(reply$i) notsametext 0` : ni `0/5`, ni `0.0`.

    Il accepte en revanche ce que `numexp` nomme `badform`, le mélange de la
    barre et de la virgule : `1,5/2` passe par la mise à l'échelle du `!for`.
    """
    r = _rawmath_normalize(reply, comma_is_decimal).strip()
    if not r:
        return CheckResult(correct=False, score=0.0, method="numexp2")

    # `!if ( + isin $dd or … )` — le signe de tête est ôté avant l'examen, si
    # bien qu'un `1/-2` reste hors format.
    dd = r[1:] if r[:1] in "+-" else r
    if any(op in dd for op in ("+", "-", "*", "^", "(")) or dd.count("/") > 1:
        return CheckResult(correct=False, score=0.0, method="numexp2",
                           status="invalid_format", detail=_COMPUTE_MSG)

    r_val = _numexp2_rationnel(r)
    if r_val is None:
        return CheckResult(correct=False, score=0.0, method="numexp2",
                           status="invalid_format", detail=_REWRITE_MSG)

    e_val = _numexp2_rationnel(
        _rawmath_normalize(expected, comma_is_decimal).strip()
    )
    if e_val is None:
        # `!if NaN isin $good or Inf isin $good` → `Test=bad`, une erreur
        # d'auteur. Rien de mieux à faire que de refuser sans accuser l'élève
        # d'une faute de forme.
        return CheckResult(correct=False, score=0.0, method="numexp2")

    if e_val == 0 and reply.strip() != "0":
        return CheckResult(correct=False, score=0.0, method="numexp2",
                           status="invalid_format", detail=_NUMEXP2_ZERO_MSG)

    correct = r_val == e_val
    return CheckResult(correct=correct, score=1.0 if correct else 0.0,
                       method="numexp2")


def jsxgraphobjet_display_answer(expected: str) -> str:
    """Ce qu'il y a à montrer d'un attendu `jsxgraphobjet` : sa première ligne.

    `replygood=hypo;cat1|cat2` décrit la figure entière — l'objet demandé, puis
    les leurres à rendre cliquables. Le corrigé n'a rien à dire des seconds :
    les afficher revenait à souffler les trois réponses possibles.
    """
    return expected.split(";", 1)[0].strip()


def check_jsxgraphobjet(
    reply: str, expected: str, opt_str: str = ""
) -> CheckResult:
    """Type `jsxgraphobjet` — les objets qu'un élève a cliqués sur une figure.

    Défini par `oeftrigoclg1` (`anstype/jsxgraphobjet`), employé par ses trois
    exercices « sélectionner l'hypoténuse / le côté adjacent / opposé ». La
    réponse est la liste des objets, dans l'ordre des clics
    (`jsxbox_objet.toString()`).

    L'attendu n'est que la **première ligne** de `replygood` —
    `replygood=$(replygood$i[1;])` : dans `hypo;cat1|cat2`, seul `hypo` est
    demandé, `cat1|cat2` énumérant les leurres à rendre cliquables (voir
    `_objets_cliquables`).

    Le fichier compare ensuite de deux façons :

    - sans `noorder`, une égalité de texte stricte (`==`), ordre compris ;
    - avec `noorder`, à nombre d'items égal, une part par item attendu retrouvé
      dans la réponse — le score partiel vaut `bon/total`.

    Un nombre d'items différent annule le score dans les deux cas
    (`!if $(cnt_rg)=!$(cnt_r)` → `score=0`), y compris une réponse vide.
    """
    attendu = expected.split(";", 1)[0]
    e_items = [x.strip() for x in attendu.split(",") if x.strip()]
    r_items = [x.strip() for x in reply.split(",") if x.strip()]
    if not e_items or len(r_items) != len(e_items):
        return CheckResult(correct=False, score=0.0, method="jsxgraphobjet")
    if "noorder" not in opt_str.lower():
        correct = r_items == e_items
        return CheckResult(correct=correct, score=1.0 if correct else 0.0,
                           method="jsxgraphobjet")
    trouves = sum(1 for g in e_items if g in r_items)
    score = trouves / len(r_items)
    return CheckResult(correct=score >= 1.0, score=score,
                       method="jsxgraphobjet")


# ------------------------------------------------------------------ #
# Ensemble (set)                                                       #
# ------------------------------------------------------------------ #


def check_set(reply: str, expected: str, opt_str: str = "") -> CheckResult:
    """Ensembles de valeurs, ordre non significatif — `set`, `checkbox`,
    `multipleclick`.

    Les trois anstype de WIMS exigent la **même** chose, et c'est une égalité :

        menupos=!listintersect $menupos and $good
        !if $poscnt1=$poscnt2 and $poscnt1=$poscnt3   → good, sinon bad

    autrement dit « autant de cases cochées que de bonnes réponses, et toutes
    justes ». Le score partiel de PAX ne valait pas seulement une note trop
    généreuse : il ne pénalisait pas les réponses **en trop**, si bien que
    cocher tout donnait 1.0 — `{1,3,4}` contre `{1,3}` rendait
    `len({1,3})/len({1,3})`. Cocher toutes les cases était donc la stratégie
    gagnante sur 214 rendus du corpus.

    Le partiel n'existe que sous `split` ou `partialscore`
    (`anstype/checkbox`, `anstype/multipleclick`), et il retranche alors les
    mauvaises réponses :

        diaratio = 3*bonnes_cochées - 2*cochées      (2*… - … sous `eqweight`)
        note     = max(0, diaratio / max(attendues, 1))
    """

    def parse_set(s: str) -> set:
        sep = ";" if ";" in s else ","
        return {x.strip().lower() for x in s.split(sep) if x.strip()}

    r_set = parse_set(reply)
    e_set = parse_set(expected)

    if r_set == e_set:
        return CheckResult(correct=True, score=1.0, method="set")

    mots = (opt_str or "").lower()
    if "split" in mots or "partialscore" in mots:
        cochees, bonnes = len(r_set), len(r_set & e_set)
        ratio = (2 * bonnes - cochees) if "eqweight" in mots else (3 * bonnes - 2 * cochees)
        note = max(0.0, ratio / max(len(e_set), 1))
        return CheckResult(correct=note > 0, score=min(1.0, note), method="set")
    return CheckResult(correct=False, score=0.0, method="set")


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


def check_aset(
    reply: str,
    expected: str,
    precision: float = WIMS_DEFAULT_PRECISION,
    comma_is_decimal: bool = True,
) -> CheckResult:
    """Ensemble approximatif — le troisième de la famille `set`/`fset`/`aset`.

    L'aide de WIMS les donne pour un même type à trois évaluations : `set` ne
    compare que du texte, `fset` évalue ses éléments comme des expressions
    formelles, `aset` comme des expressions approximatives. `check_fset` fait
    déjà les deux dernières — il essaie le numérique avant le symbolique —, et
    c'est lui qui apparie ici.

    Ce que `anstype/aset` ajoute tient dans son préambule, et il faut le
    reproduire avant de comparer :

    * `!declosing` retire une paire de délimiteurs englobants. L'énoncé pose
      « \(S =\) » devant le champ, alors l'élève écrit volontiers `{3/7,1/90}` ;
    * `!listuniq` dédoublonne **les deux** côtés avant de compter. `1,1,2` vaut
      donc `1,2`, là où `check_fset` seul y verrait deux cardinaux différents ;
    * sans virgule, la liste se coupe sur les espaces (`!words2items`), ce qui
      accepte `3/7 1/90`.

    La note est tout ou rien. WIMS compare les deux ensembles par un détour
    élégant — il forme ∏(J−xᵢ) de chaque côté et confie les deux polynômes à
    `anstype/function`, deux ensembles étant égaux exactement quand leurs
    polynômes le sont — et un seul élément faux suffit à les séparer. Le score
    partiel de `check_fset` accorderait des points là où WIMS n'en donne aucun.
    """
    def declos(s: str) -> str:
        s = s.strip()
        for ouvrant, fermant in (("{", "}"), ("(", ")"), ("[", "]")):
            if s.startswith(ouvrant) and s.endswith(fermant):
                return s[1:-1].strip()
        return s

    def uniq(s: str, sep: str) -> str:
        vus: list[str] = []
        for x in s.split(sep):
            x = x.strip()
            if x and x not in vus:
                vus.append(x)
        return sep.join(vus)

    reply, expected = declos(reply), declos(expected)
    # `!if , notin $dd → !words2items` : l'espace ne sépare que faute de virgule.
    if "," not in reply and ";" not in reply:
        reply = ",".join(reply.split())
    if "," not in expected and ";" not in expected:
        expected = ",".join(expected.split())
    reply = uniq(reply, ";" if ";" in reply else ",")
    expected = uniq(expected, ";" if ";" in expected else ",")

    res = check_fset(reply, expected, precision, comma_is_decimal)
    if res.correct:
        return CheckResult(correct=True, score=1.0, method="aset")
    return CheckResult(correct=False, score=0.0, method="aset", detail=res.detail)


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


# Découpage à profondeur zéro : une seule version, celle de `wims_lists`.
_split_top_level = wl.split_top_level

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


# Ponctuation neutralisée par WIMS `case` : les `badchars` d'`anstype/case`,
# soit ceux de `nocase` plus la barre verticale — laquelle sépare les
# alternatives de l'attendu, et n'a donc à être neutralisée que dans la réponse
# (l'attendu est découpé dessus avant d'arriver ici).
_CASE_PUNCT = re.compile(r"""[-+/*='"`.;,!|{}@#$%^&()\[\]?<>\\~]""")


def _case_normalize(s: str) -> str:
    """`translate badchars → espaces`, `singlespace`, `trim` — la préparation
    que `anstype/case` applique à la réponse **comme** à l'attendu.

    **La casse compte.** WIMS compare par `!if $dd=$g`, et c'est tout le sens
    du type : `case` est sensible à la casse, `nocase` ne l'est pas. Le manuel
    (§1.3.3) le dit en toutes lettres — « chaque mot de la réponse doit être
    exactement le même » — et l'exemple du dollar refuse `Dollar`. PAX mettait
    tout en minuscules, un écart que sa propre docstring avouait.
    """
    s = _CASE_PUNCT.sub(" ", s)
    return re.sub(r"\s+", " ", s).strip()


def check_case(reply: str, expected: str) -> CheckResult:
    """WIMS `case` type: ``expected`` lists alternatives separated by ``|``.
    The reply matches an alternative literally (case/space-insensitive), or —
    for WIMS' ``[Alt:[Apick:N,…]]`` construct (prime factorisation, 1024) — as
    a product whose factor multiset equals an accepted one (order-free). E.g.
    ``5^2*2*7|[Alt:[Apick:3,[*],[*],5^2,2,7],[Apick:4,[*],[*],[*],5,5,2,7]]``
    accepts ``2*5*5*7`` as well as ``5^2*2*7`` in any factor order.

    **La ponctuation ne compte pas.** `anstype/case` traduit une liste de
    `badchars` en espaces — des deux côtés — puis `!singlespace` et `!trim`
    avant de comparer. Sans cela, `mathelexikon1/Kreisenkette` était
    inaccessible : son `replygood1=$(val74[1;]);$(val72[1;])` sort `e;`, le
    `;` n'étant qu'un séparateur entre deux composantes dont la seconde est
    **délibérément vide** (`!ifval $val21 iswordof case raw → val72=`). Il
    fallait taper `e;` pour avoir juste, là où la désinence attendue est `e`.
    Ses vingt-deux champs sont dans ce cas.
    """
    reply_norm = _case_normalize(reply)
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
            literal_alts.add(_case_normalize(part))

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


def check_wlist(reply: str, expected: str, lang: str = "fr") -> CheckResult:
    """Type WIMS `wlist` : une liste de mots, tous à prendre dans un répertoire.

    Ce n'est pas une égalité d'ensembles, et c'est ce qui le distingue de
    `set` : `anstype/wlist` demande que **chaque mot cité appartienne** au
    répertoire, et qu'il y en ait au moins `n`.

        gd = 0
        !for w in $dd
          !if $w isitemof $good
            !advance gd
        tt = !itemcnt $dd
        !ifval $gd=$tt and $gd>=$n   → good

    Le seuil `n` est le **premier mot** de `replygood`, quand c'en est un
    nombre (`n=!word 1 of $good`, `n=$[$n]`, `!if $n>0`) ; sinon il vaut 1 et
    le répertoire commence au premier mot. `mol/molecule2` est dans ce second
    cas : il pose les quatre atomes sans seuil, si bien qu'un seul d'entre eux
    fait une réponse juste — laxisme de l'exercice, que nous reproduisons.

    Le `;` de `replygood` fait un saut de ligne (`!rows2lines`) : la première
    ligne est le répertoire, les suivantes les `badwords`, qui ne servent qu'au
    diagnostic `unknownword` — non rendu ici, comme pour `atext`.

    La normalisation est celle d'`atext`, dont `wlist` partage le dictionnaire
    (`scripts/oef/<lang>/atext.dic` et `bases/sys/suffix.<lang>`) : accents,
    casse, ponctuation, mots vides et racinisation. « le Carbone et
    l'hydrogène » vaut donc « carbone hydrogene ».

    La note est tout ou rien. WIMS marque bien un `precgood` quand la moitié
    des mots au moins est juste, mais c'est `freegot` qui note, et il n'avance
    que dans la branche « good » : le `precgood` ne vaut qu'un message.
    """
    # `!items2words` d'abord : les virgules de `replygood` deviennent des
    # espaces, et seul le `;` sépare encore le répertoire des badwords.
    brut = (expected or "").replace(",", " ")
    lignes = [ligne for ligne in brut.split(";") if ligne.strip()]
    repertoire = lignes[0] if lignes else ""

    mots_good = repertoire.split()
    seuil = 1
    if mots_good:
        try:
            premier = int(mots_good[0])
        except ValueError:
            premier = 0
        if premier > 0:
            seuil = premier
            mots_good = mots_good[1:]

    good = set(_atext_normalize(" ".join(mots_good), lang).split())
    if not good:
        return CheckResult(correct=False, score=0.0, method="wlist")

    # `!listuniq $dd` : un mot répété ne compte qu'une fois, des deux côtés.
    donnes: list[str] = []
    for mot in _atext_normalize(reply, lang).split():
        if mot not in donnes:
            donnes.append(mot)
    if not donnes:
        return CheckResult(correct=False, score=0.0, method="wlist")

    justes = sum(1 for mot in donnes if mot in good)
    if justes == len(donnes) and justes >= seuil:
        return CheckResult(correct=True, score=1.0, method="wlist")

    intrus = [mot for mot in donnes if mot not in good]
    detail = (
        f"mot(s) hors sujet : {', '.join(intrus)}" if intrus
        else f"{len(donnes)} mot(s), {seuil} attendu(s) au moins"
    )
    return CheckResult(correct=False, score=0.0, method="wlist", detail=detail)


# ------------------------------------------------------------------ #
# GeoGebra : la figure que l'élève construit                           #
# ------------------------------------------------------------------ #

# Ce qu'un objet met à disposition d'une condition, par type. `anstype/geogebra`
# les substitue avant d'évaluer : `x_A` devient l'abscisse de A, `v_t` la valeur
# du texte t. Les coniques et les droites en offrent davantage (`a_`, `b_`,
# `R_`, `x2_`…) ; aucun exercice du corpus n'en pose, et les porter à l'aveugle
# reviendrait à écrire du code que rien n'éprouve.
_GGB_COORDS = ("point", "vector")
_GGB_VALEUR = ("segment", "function", "angle", "numeric", "text", "boolean")


def _ggb_nombre(brut: str) -> Fraction | None:
    """Un littéral de la figure, en rationnel exact.

    Les coordonnées arrivent en écriture décimale (`-12`, `0.5`), et c'est
    Pari qui les évalue chez WIMS — en exact, non en binaire. `Fraction` tient
    la même promesse : `0.1+0.2 == 0.3` y est vrai, ce qu'un `float` refuse.
    Or ces conditions sont pleines d'égalités à zéro (`x_u*y_v-y_u*x_v==0`),
    où le bruit binaire déciderait à la place de la géométrie.
    """
    try:
        return Fraction(brut.strip())
    except (ValueError, ZeroDivisionError):
        return None


def _ggb_objets(reply: str) -> tuple[dict[str, tuple[str, list[str]]], dict[str, str]]:
    """Les deux moitiés de la réponse : les valeurs, puis les définitions.

    `geogebra2wims()` compose une chaîne à deux parties séparées par `;` —
    d'abord `<nom>=<type>,<données>` joints par `&&`, puis
    `<nom>=<commande>` de même. La première dit *où* sont les objets, la
    seconde *comment* ils ont été obtenus : un point posé à la main et un point
    construit par intersection ont les mêmes coordonnées et des définitions
    différentes, ce que les conditions `f` savent distinguer.
    """
    valeurs, definitions = {}, {}
    zone_val, _, zone_def = reply.partition(";")
    for morceau in zone_val.split("&&"):
        nom, sep, reste = morceau.partition("=")
        if not sep or not reste.strip():
            continue
        champs = [c.strip() for c in reste.split(",")]
        valeurs[nom.strip()] = (champs[0].lower(), champs[1:])
    for morceau in zone_def.split("&&"):
        nom, sep, reste = morceau.partition("=")
        if sep:
            definitions[nom.strip()] = reste.strip()
    return valeurs, definitions


def _ggb_tests(expected: str) -> list[tuple[str, str, str]]:
    """Les conditions de `replygood`, en triplets `(genre, condition, message)`.

    Elles sont séparées par `;`, et chacune s'écrit `<genre>,<condition>,<msg>` :
    `n` pour une condition numérique, `f` pour une condition formelle (WIMS
    accepte aussi les mots entiers `numeric` et `formal`). Le message `hiden`
    est celui qu'on ne montre pas.

    La condition s'arrête à la première virgule — c'est `!item 1 of $cond` chez
    WIMS, qui ne regarde pas davantage les parenthèses que nous ici.
    """
    tests = []
    for ligne in expected.replace("\t", "").split(";"):
        ligne = ligne.strip()
        if not ligne:
            continue
        genre, sep, reste = ligne.partition(",")
        genre = genre.strip().lower()
        if not sep or genre not in ("n", "f", "numeric", "formal"):
            continue
        condition, _, message = reste.partition(",")
        tests.append(
            ("f" if genre in ("f", "formal") else "n",
             condition.strip(), message.strip())
        )
    return tests


def _ggb_substitue(condition: str, valeurs: dict) -> str:
    """Remplace `x_A`, `y_A`, `z_A`, `v_t` par ce que la figure porte.

    Les noms les plus longs d'abord : sans cela, un objet `u` verrait son
    `x_u` substitué à l'intérieur du `x_u1` d'un voisin.
    """
    for nom in sorted(valeurs, key=len, reverse=True):
        type_obj, champs = valeurs[nom]
        if type_obj in _GGB_COORDS:
            for prefixe, rang in (("x_", 0), ("y_", 1), ("z_", 2)):
                if rang < len(champs):
                    condition = condition.replace(
                        f"{prefixe}{nom}", f"({champs[rang]})"
                    )
        elif type_obj in _GGB_VALEUR:
            valeur = ",".join(champs) or "0"
            condition = condition.replace(f"v_{nom}=", f"({valeur})==")
            condition = condition.replace(f"v_{nom}", f"({valeur})")
    return condition


def _ggb_evalue(condition: str) -> bool:
    """Évalue une condition numérique, en arithmétique exacte.

    WIMS la confie à Pari (`check=!exec pari ($cond)`), d'où une syntaxe de
    C : `&&`/`&` pour l'et, `||` pour le ou, `^` pour la puissance. On la
    traduit en Python, et les nombres deviennent des `Fraction` : les
    conditions sont pleines d'égalités à zéro, que le bruit binaire des
    flottants trancherait de travers.
    """
    expr = condition.strip()
    if not expr:
        return False
    # Un identifiant qui subsiste est un objet que la figure ne porte pas : la
    # condition est alors fausse, non erronée (WIMS y voit Pari rendre vide,
    # qu'il ramène à 0).
    reste = re.sub(r"\b(abs|sqrt|min|max)\b", "", expr)
    if re.search(r"[A-Za-z_]", reste):
        return False
    expr = expr.replace("&&", " and ").replace("||", " or ")
    expr = re.sub(r"(?<![&])&(?![&])", " and ", expr)
    expr = expr.replace("^", "**")
    # Chaque littéral en rationnel exact, la puissance mise à part : un exposant
    # doit rester un entier Python.
    expr = re.sub(
        r"(?<![\w.])(\d+\.?\d*)(?![\w.])",
        lambda m: f"Fraction('{m.group(1)}')",
        expr,
    )
    expr = re.sub(r"\*\*\s*Fraction\('(\d+)'\)", r"**\1", expr)
    try:
        return bool(eval(expr, {"__builtins__": {}}, {  # noqa: S307
            "Fraction": Fraction, "abs": abs, "min": min, "max": max,
        }))
    except (ValueError, TypeError, SyntaxError, ZeroDivisionError, NameError):
        return False


def _ggb_evalue_formelle(condition: str, definitions: dict) -> bool:
    """Une condition `f` : l'objet nommé a-t-il été **construit** comme il faut ?

    Elle s'écrit `<nom>=<Commande>` et se lit sur la seconde moitié de la
    réponse, celle des définitions. WIMS y ramène `Point[a,b]` à `Point,a,b`
    (`!replace internal [ by ,`) puis compare le nom de commande ; on compare
    de même, sans la casse — un point libre y répond par son type, `point`,
    faute de commande.
    """
    nom, sep, attendu = condition.partition("=")
    if not sep:
        return False
    definition = definitions.get(nom.strip())
    if definition is None:
        return False
    tete = re.split(r"[\[(]", definition.strip(), maxsplit=1)[0]
    return tete.strip().lower() == attendu.strip().lower()


def geogebra_memo_reply(reply: str) -> str:
    """La réponse dans la forme que WIMS **mémorise**, pour le `:postdef`.

    `anstype/geogebra` ne range pas dans `$m_reply<i>` la chaîne que le
    navigateur envoie, mais une structure à trois blocs de lignes :

        $ynamecnt          le nombre d'objets
        $yourggb           les définitions, une par ligne
        $yourlist_name     les valeurs (`v=vector,3,6`), une par ligne

    C'est là-dessus que les exercices bâtissent leur feedback :
    `oefvectdirnorm/06memenorme` lit `!line 1` pour le compte, en déduit les
    deux blocs, et va chercher `!getopt v in` le troisième pour comparer les
    normes. Sans cette mise en forme, son `:postdef` travaillait sur du vide et
    concluait à l'échec — l'élève lisait « Correct ! 100 % » suivi de « les
    vecteurs n'ont pas la même norme ».

    Le bloc des définitions est rendu tel que l'applet le donne. WIMS le
    retravaille (une centaine de lignes pour reconstruire des commandes
    GeoGebra affichables) ; ce qu'un `:postdef` y lit — les coordonnées d'un
    objet nommé — s'y retrouve de la même façon.
    """
    valeurs, definitions = _ggb_objets(reply)
    lignes_val = [f"{nom}={t},{','.join(champs)}" for nom, (t, champs) in valeurs.items()]
    lignes_def = [f"{nom}={cmd}" for nom, cmd in definitions.items()]
    return "\n".join([str(len(lignes_val)), *lignes_def, *lignes_val])


def check_geogebra(
    reply: str,
    expected: str,
    options: dict | None = None,
) -> CheckResult:
    """Type WIMS `geogebra` : la figure que l'élève construit ou déplace.

    La réponse n'est pas un nombre mais un **état de figure**, que
    `geogebra2wims()` compose côté navigateur (porté dans
    `composables/useGeogebra.ts`). Le `replygood` en regard n'est pas une
    valeur non plus : c'est une liste de conditions à vérifier, dont chacune
    porte son message.

        n,(x_B-x_C)!=0||(y_B-y_C)!=0 & (x_u)*(y_v)-(y_u)*(x_v)==0,hiden

    « le vecteur CB n'est pas nul, et son déterminant avec FH est nul » —
    autrement dit *les deux vecteurs sont colinéaires*, sans exiger de l'élève
    un placement particulier. C'est tout l'intérêt du type : la bonne réponse
    est un ensemble de figures, pas une figure.

    **La note** suit `anstype/geogebra` :

        score = (w₁·formelles + w₂·noms + w₃·numériques) / (w₁+w₂+w₃)

    chaque terme étant la fraction des conditions de son genre qui passent, et
    son poids ramené à zéro quand l'exercice n'en pose aucune. `weight` vaut
    `1,0.2,1` par défaut. Le second terme, la vérification des **noms** donnés
    aux objets, n'est pas porté : aucun des dix-sept exercices ne le demande,
    et son total nul annule son poids — la formule reste donc exacte ici.

    Le reste du script — traduction des conditions formelles en conditions
    numériques, dictionnaire multilingue des types, coniques et droites — suit
    la même règle : rien n'est porté qu'aucun exercice n'éprouve.
    """
    tests = _ggb_tests(expected)
    if not tests:
        return CheckResult(correct=False, score=0.0, method="geogebra")
    valeurs, definitions = _ggb_objets(reply)
    if not valeurs and not definitions:
        return CheckResult(
            correct=False, score=0.0, method="geogebra",
            detail="figure vide",
        )

    poids = [1.0, 0.2, 1.0]
    m = re.search(r"\bweights?\s*=\s*(\S+)", str((options or {}).get("option", "")))
    if m:
        lus = [_ggb_nombre(x) for x in m.group(1).replace("&", ",").split(",")]
        if len(lus) == 3 and all(v is not None for v in lus):
            poids = [float(v) for v in lus]  # type: ignore[arg-type]

    reussies = {"n": 0, "f": 0}
    totaux = {"n": 0, "f": 0}
    manquees: list[str] = []
    for genre, condition, message in tests:
        totaux[genre] += 1
        if genre == "f":
            ok = _ggb_evalue_formelle(condition, definitions)
        else:
            ok = _ggb_evalue(_ggb_substitue(condition, valeurs))
        if ok:
            reussies[genre] += 1
        elif message and message.lower() != "hiden":
            manquees.append(message)

    parts = (
        (poids[0], reussies["f"], totaux["f"]),
        (poids[1], 0, 0),  # noms : non porté, et sans emploi dans le corpus
        (poids[2], reussies["n"], totaux["n"]),
    )
    numerateur = sum(p * (n / t) for p, n, t in parts if t)
    denominateur = sum(p for p, _, t in parts if t)
    if not denominateur:
        return CheckResult(correct=False, score=0.0, method="geogebra")
    score = numerateur / denominateur
    # `diareply=good` seulement si le score vaut 1 (`anstype/geogebra`).
    return CheckResult(
        correct=score >= 1.0,
        score=min(1.0, max(0.0, score)),
        method="geogebra",
        detail="; ".join(manquees) or None,
    )


def check_runcode(
    reply: str,
    expected: str,
    precision: float = 1000.0,
) -> CheckResult:
    """Type `runcode` : le code Python que l'élève écrit, jugé sur ses variables.

    Le type n'existe pas chez WIMS — huit modules d'`H4/programming` le
    définissent, à quelques lignes près les uns des autres. Et son correcteur
    **n'exécute rien** : Skulpt fait tourner le programme dans le navigateur,
    le `.input` relève les variables globales (`Sk.ffi.remapToJs`) et compose
    la réponse

        [<code source>],[<valeur 1>],[<valeur 2>]…

    dont le serveur ne compare que les valeurs, dans l'ordre où `replygood`
    nomme les variables (`[vi,1],[vf,4]` : « vi doit valoir 1, vf 4 »). Le code
    lui-même n'est pas jugé — seulement ce qu'il produit.

    Une variable peut porter une **liste** (`x_list`, les abscisses d'une
    courbe) : chaque terme compte alors pour une fraction de sa variable, et
    chaque variable pour une fraction du tout — c'est le
    `1/$nbr_good/$cnt_variable` du module. Un terme numérique se compare à
    `1/precision` près, un terme textuel à l'identique.
    """
    from core.oef.def_engine.wims_lists import cutitems  # noqa: PLC0415

    attendus = [x for x in cutitems(expected or "") if x.strip()]
    if not attendus:
        return CheckResult(correct=False, score=0.0, method="runcode")
    donnes = [x for x in cutitems(reply or "") if x.strip()]
    # Item 1 = le code source ; les valeurs commencent au deuxième.
    valeurs = donnes[1:]

    total = 0.0
    manquantes: list[str] = []
    for j, brut in enumerate(attendus):
        couple = cutitems(_declose(brut))
        if len(couple) < 2:
            continue
        nom, attendu_var = couple[0].strip(), ",".join(couple[1:])
        recu = valeurs[j] if j < len(valeurs) else ""
        termes_a = [t.strip() for t in cutitems(_declose(attendu_var))]
        termes_r = [t.strip() for t in cutitems(_declose(recu))]
        if not termes_a:
            continue
        justes = 0
        for k, ta in enumerate(termes_a):
            tr = termes_r[k] if k < len(termes_r) else ""
            if _est_nombre(ta) and _est_nombre(tr):
                try:
                    if abs(float(ta) - float(tr)) < 1 / precision:
                        justes += 1
                except (ValueError, OverflowError):
                    pass
            elif ta == tr:
                justes += 1
        total += justes / len(termes_a) / len(attendus)
        if justes < len(termes_a):
            manquantes.append(nom)

    note = min(1.0, max(0.0, total))
    return CheckResult(
        correct=note >= 1.0,
        score=note,
        method="runcode",
        detail=("variable(s) fausse(s) : " + ", ".join(manquantes)) if manquantes else None,
    )


def check_js2wims1(reply: str, expected: str) -> CheckResult:
    """Type `js2wims1` : les variables d'une exécution Python, relues telles quelles.

    Défini par `oefechpython`, et jumeau simplifié de `runcode` — dont il
    dépend : son `.input` ne monte aucun éditeur, il pose un champ **caché**
    et le remplit, à l'envoi, des variables laissées par le programme que
    l'élève a joué dans le `runcode` voisin. D'où une réponse sans code source
    en tête, `[valeur 1],[valeur 2]…`, là où `runcode` ouvre par le programme.

    Deux autres écarts avec son jumeau, tous deux dans le sens de la
    simplicité : la comparaison est **purement textuelle** — pas de tolérance
    numérique —, et chaque variable vaut `1/n` sans découpage par terme.

    Un attendu dont la valeur est vide vaut juste d'office : le module sort
    alors sur `diareply=good`. C'est le cas de `de4`, `de5` et `de6`, dont le
    `replygood` se réduit à un nom (`nn`) — et dont le champ pèse zéro.
    Treize des quatorze champs du corpus sont dans ce cas ; seul `de3/reply2`
    compte dans une note.
    """
    from core.oef.def_engine.wims_lists import cutitems  # noqa: PLC0415

    attendus = [x for x in cutitems(expected or "") if x.strip()]
    if not attendus:
        return CheckResult(correct=False, score=0.0, method="js2wims1")
    donnes = [x for x in cutitems(reply or "")]

    total = 0.0
    juges = 0
    manquantes: list[str] = []
    for j, brut in enumerate(attendus):
        # `!if \ notin …` : un item porteur d'une contre-oblique est ignoré.
        if "\\" in brut:
            continue
        couple = cutitems(_declose(brut))
        nom = couple[0].strip() if couple else ""
        valeur = _declose(",".join(couple[1:])) if len(couple) > 1 else ""
        if not valeur:
            # Rien à comparer : le module conclut « juste » et s'arrête là.
            return CheckResult(correct=True, score=1.0, method="js2wims1")
        juges += 1
        recu = _declose(donnes[j]) if j < len(donnes) else ""
        if j == 0:
            recu = re.sub(r"\s+", "", recu)
        if valeur == recu:
            total += 1
        else:
            manquantes.append(nom or f"#{j + 1}")

    if not juges:
        return CheckResult(correct=False, score=0.0, method="js2wims1")
    note = total / juges
    return CheckResult(
        correct=note >= 1.0,
        score=note,
        method="js2wims1",
        detail=("variable(s) fausse(s) : " + ", ".join(manquantes)) if manquantes else None,
    )


def js2wims1_display_answer(expected: str) -> str:
    """Une réponse `js2wims1` que l'attendu suffit à composer.

    Même service que `runcode_display_answer`, sans le code en tête :
    `[n,[3]]` dit que la variable `n` doit valoir 3, et la réponse qui le
    satisfait s'écrit `[3]`. Un attendu réduit à un nom (`nn`, chez `de4` à
    `de6`) ne décrit aucune valeur — le module conclut alors juste d'office,
    et n'importe quelle réponse convient.
    """
    from core.oef.def_engine.wims_lists import cutitems  # noqa: PLC0415

    valeurs = []
    for couple in cutitems(expected or ""):
        champs = cutitems(_declose(couple))
        if len(champs) < 2:
            return ""
        valeurs.append(_declose(",".join(champs[1:])))
    return ",".join(f"[{v}]" for v in valeurs) if valeurs else ""


def runcode_display_answer(expected: str) -> str:
    """Une réponse `runcode` que l'attendu suffit à composer.

    `[vi,1],[vf,4]` dit ce que les variables doivent valoir ; la réponse qui
    satisfait cet attendu s'écrit donc `[<code>],[1],[4]`. Le code lui-même
    n'entre pas dans la note — le correcteur ne juge que les valeurs —, d'où le
    marqueur en première position.

    Sert au test de corpus, qui soumet l'attendu tel quel pour vérifier qu'une
    bonne réponse vaut 1. Sans cette conversion, il soumettrait la *consigne*
    au lieu de la réponse, comme pour les bornes d'un `range`.
    """
    from core.oef.def_engine.wims_lists import cutitems  # noqa: PLC0415

    valeurs = []
    for couple in cutitems(expected or ""):
        champs = cutitems(_declose(couple))
        if len(champs) < 2:
            return ""
        valeurs.append(_declose(",".join(champs[1:])))
    if not valeurs:
        return ""
    return ",".join(["[code]", *(f"[{v}]" for v in valeurs)])


def _est_nombre(texte: str) -> bool:
    """Le test du module : `!text remove 0123456789e.-` ne laisse rien."""
    return bool(texte) and not (set(texte) - set("0123456789e.-+"))


# `!declosing` : la version équilibrée de `wims_lists`, seule juste sur `[a],[b]`.
_declose = wl.declosing

def check_jmolclick(reply: str, expected: str) -> CheckResult:
    """Type WIMS `jmolclick` : les atomes qu'on clique sur une molécule.

    Le correcteur ne corrige pas. `anstype/jmolclick` reçoit une réponse dont
    la **première ligne est déjà la note**, calculée dans le navigateur par le
    JavaScript de son `.input` — l'applet seule sait ce qu'est « un oxygène lié
    à un hydrogène et à un carbone », et c'est elle qui compare la sélection de
    l'élève à l'expression attendue. Le script WIMS s'en tient à :

        !distribute lines $(reply$i) into score,selgood,selbad,selforget,…
        score=$[round($score)/10]

    PAX fait de même : la note est portée par `noterSelectionJmol`
    (`composables/useJsmol.ts`), et il ne reste ici qu'à la relire. Les lignes
    suivantes — atomes justes, faux, oubliés — servent au seul feedback.

    L'attendu n'entre pas dans le calcul : il a déjà servi, dans l'applet.
    """
    premiere = (reply or "").strip().splitlines()
    if not premiere:
        return CheckResult(correct=False, score=0.0, method="jmolclick")
    try:
        note = round(float(premiere[0].strip())) / 10
    except (ValueError, TypeError):
        return CheckResult(correct=False, score=0.0, method="jmolclick")
    note = min(1.0, max(0.0, note))
    return CheckResult(correct=note >= 1.0, score=note, method="jmolclick")


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
    # Crédit d'une réponse juste « à la précision près » : `precweight`, que le
    # niveau de sévérité fixe. Le moteur le pose dans les options à la
    # correction ; à défaut 0,5, la valeur historique de PAX.
    try:
        precweight = float(options.get("precweight", 0.5))
    except (TypeError, ValueError):
        precweight = 0.5
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
    # `function` est exclu : chez WIMS sa virgule sépare la fonction de la liste
    # des variables autorisées (`\g,x,t`, §1.3.5.1), non des alternatives — le
    # découper ici aurait accepté `x` comme réponse.
    if answer_type.lower() in ("algexp", "litexp", "formal", "default", "auto", "numeric", "numexp"):
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
        # Une **constante** n'a pas de forme factorisée par opposition à une
        # forme développée : elle est les deux. `is_polexpand` la dit pourtant
        # développée — un nombre est un monôme —, si bien qu'exiger une
        # factorisation la refusait. `T1110` demande « 30 % de 20 » et attend
        # `6`, sous un `polfactor` que le module pose pour toutes ses
        # questions : son attendu se refusait lui-même.
        if reply.strip() and not _est_constante(reply) and is_polexpand(reply):
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
            return check_numeric(reply, expected, precision, comma_is_decimal, absolute, precweight)
        case "numexp":
            noreduction = "noreduction" in opt_str
            return check_numexp(reply, expected, precision, comma_is_decimal, noreduction)
        case "numexp2":
            return check_numexp2(reply, expected, comma_is_decimal)
        case "jsxgraphobjet":
            return check_jsxgraphobjet(reply, expected, opt_str)
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
            return check_function(reply, expected, precision, comma_is_decimal,
                                  options.get("range"), precweight)
        case "fset":
            return check_fset(reply, expected, precision, comma_is_decimal)
        case "aset":
            return check_aset(reply, expected, precision, comma_is_decimal)
        case "geogebra":
            return check_geogebra(reply, expected, options)
        case "jmolclick":
            return check_jmolclick(reply, expected)
        case "runcode":
            return check_runcode(reply, expected, precision)
        case "js2wims1":
            return check_js2wims1(reply, expected)
        # `multipleclick` note par égalité d'ensembles de positions, comme
        # `checkbox` (cf. le moteur) : `!listintersect` puis trois comptes
        # égaux dans `anstype/multipleclick`.
        case "set" | "checkbox" | "multipleclick":
            return check_set(reply, expected, opt_str)
        # `anstype/click` compare des **positions** : il cherche le rang de la
        # réponse dans la liste des choix et le confronte à la première ligne
        # de `replygood` (`!if $menupos isitemof $good`). C'est le contrat de
        # `mark`, et le moteur lui donne désormais la même forme — d'où le
        # même comparateur, plutôt que le repli textuel qui traînait ici.
        case "radio" | "menu" | "mark" | "click":
            return check_radio(reply, expected)
        case "clickfill":
            return check_clickfill(reply, expected, noorder="noorder" in opt_str)
        case "correspond":
            return check_correspond(reply, expected, partial=bool(options.get("partial")))
        case "chemeq":
            return check_chemeq(reply, expected)
        case "jsxgraph":
            return check_jsxgraph(reply, expected, options)
        case "jsxgraphcurve":
            return check_jsxgraphcurve(reply, expected, options)
        case "coord":
            return check_coord(reply, expected, options)
        case "draw":
            return check_draw(reply, expected, options)
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
        case "wlist":
            return check_wlist(reply, expected, lang or "fr")
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
                return check_numeric(reply, expected, precision, comma_is_decimal, absolute, precweight)
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
