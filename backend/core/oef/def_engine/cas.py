"""Computer-algebra glue for the .def runtime.

This module hosts everything that ``DefEngine`` calls when a .def script
asks for symbolic / numeric evaluation:

- ``_MATH_NS`` — the WIMS arithmetic namespace (``rint``, ``sqrt``, …)
  used by ``$[expr]`` and ``!if`` numeric comparisons.
- ``_call_maxima`` — the Maxima emulation (single-arg + multi-arg via
  SymPy mappings + the explicit ``diff/subst/coeff/hipow/limit/cardinality``
  cases).
- ``_call_pari`` — PARI/GP emulation: dispatches the helper functions in
  ``_PARI_HELPERS`` and auto-binds unknown identifiers to ``sympy.Symbol``
  so polynomial expressions like ``polcoeff(x^2 + 3*x + 2, 1)`` work.
- ``_expr_to_latex`` — string-in / LaTeX-out helper used by ``!texmath``
  and ``!rawmath`` (the latter intentionally bypasses LaTeX conversion;
  see runtime).
- A handful of helpers (``_split_top_level_args``, ``_sympify_arg``,
  ``_format_pari_result``).
"""

from __future__ import annotations

import math
import re
from typing import Any


def _rint(x: Any) -> int:
    return int(round(float(x)))


def _lcm(*args: Any) -> int:
    # WIMS lcm() always operates on integers; coerce so "30"/"30.0" both work
    # (math.lcm rejects floats). Without this, $[rint(lcm(a,b))] fell through
    # the eval and leaked the literal "rint(lcm(…))" into the statement.
    return math.lcm(*(int(round(float(a))) for a in args))


_MATH_NS: dict = {
    "__builtins__": {},
    "rint": _rint,
    "round": round,
    "abs": abs,
    "max": max,
    "min": min,
    "sqrt": math.sqrt,
    "pow": pow,
    "sin": math.sin,
    "cos": math.cos,
    "tan": math.tan,
    "asin": math.asin,
    "acos": math.acos,
    "atan": math.atan,
    "atan2": math.atan2,
    # WIMS spells the inverse trig functions `arc*`; without these aliases
    # `$[rint(arctan(...)*180/pi)]` raised NameError and the un-evaluated
    # expression leaked into the answer (rectangle.oef's angle reply).
    "arcsin": math.asin,
    "arccos": math.acos,
    "arctan": math.atan,
    "arctan2": math.atan2,
    "log": math.log,
    "log10": math.log10,
    "log2": math.log2,
    # `lg` est le logarithme **décimal**, `ln` le népérien — table des
    # fonctions de `Lib/evalue.c` :
    #
    #     {"lg",   1, 0, log10, NULL},
    #     {"ln",   1, 0, log,   NULL},
    #
    # Sans elles, `lg(0.0312)` s'évaluait à 0 en silence, et l'arrondi aux
    # chiffres significatifs de `slib/triplerelation/tabular` —
    # `rint(10^(prec-1-floor(lg(x)))*x)/10^(prec-1-floor(lg(x)))` — ne
    # produisait plus rien d'exploitable. Vingt-cinq scripts WIMS emploient
    # `lg`. Les hyperboliques et `int`/`frac` de la même table complètent
    # l'alignement.
    "lg": math.log10,
    "ln": math.log,
    "sinh": math.sinh,
    "cosh": math.cosh,
    "tanh": math.tanh,
    "int": lambda x: int(float(x)),
    "frac": lambda x: float(x) - int(float(x)),
    "exp": math.exp,
    "floor": math.floor,
    "ceil": math.ceil,
    "pi": math.pi,
    # WIMS also spells π as `Pi` and `PI` — its evalue.c constant table lists
    # all three (`pi`/`Pi`/`PI` → M_PI). Without them `$[rint(…*PI)]` raised
    # NameError and the literal expression leaked into the expected answer
    # (`Pi`: quizz 1211's matrix `quest=e,Pi,sqrt(2)`; `PI`: quizz 1221's
    # `$[rint(($val9)*cos($val8*PI))]`).
    "Pi": math.pi,
    "PI": math.pi,
    "e": math.e,
    "mod": lambda a, b: float(a) % float(b),
    "fact": math.factorial,
    "sign": lambda x: 1 if x > 0 else -1 if x < 0 else 0,
    "gcd": math.gcd,
    "lcm": _lcm,
    # WIMS écrit parfois ces fonctions en majuscules dans `$[…]` (cf. GCD).
    "GCD": math.gcd,
    "LCM": _lcm,
    # ── Le reste de la table de `Lib/evalue.c` ──────────────────────────────
    #
    # Une fonction absente ne lève rien : `$[…]` rend l'expression telle quelle
    # (ou zéro), et le calcul se poursuit sur du faux. C'est ce qui a coûté
    # cinq niveaux de diagnostic avec `lg`, et le balayage de la table le
    # confirme — 36 des 70 entrées manquaient. Celles-ci sont déterministes,
    # donc sûres à poser ici ; les aléatoires (`random`, `drand`, `irand`…)
    # dépendent de la graine du rendu et vivent dans `_eval_arith`.
    #
    # WIMS accepte les noms français et allemands des mêmes fonctions :
    # `tg`/`ctg` (tangente, cotangente), `sh`/`ch`/`th` (hyperboliques),
    # `argsh`/`argch`/`argth` (réciproques hyperboliques).
    "asinh": math.asinh, "acosh": math.acosh, "atanh": math.atanh,
    "sh": math.sinh, "ch": math.cosh, "th": math.tanh,
    "argsh": math.asinh, "argch": math.acosh, "argth": math.atanh,
    "tg": math.tan, "arctg": math.atan,
    "cot": lambda x: 1.0 / math.tan(float(x)),
    "cotan": lambda x: 1.0 / math.tan(float(x)),
    "ctg": lambda x: 1.0 / math.tan(float(x)),
    "coth": lambda x: 1.0 / math.tanh(float(x)),
    "cotanh": lambda x: 1.0 / math.tanh(float(x)),
    "cth": lambda x: 1.0 / math.tanh(float(x)),
    "sec": lambda x: 1.0 / math.cos(float(x)),
    "csc": lambda x: 1.0 / math.sin(float(x)),
    "erf": math.erf, "erfc": math.erfc, "lgamma": math.lgamma,
    "factorial": math.factorial,
    "binomial": lambda n, k: math.comb(int(n), int(k)),
    "sgn": lambda x: 1 if x > 0 else -1 if x < 0 else 0,
    "euler": 0.5772156649015329,
}


_MAXIMA_TO_SYMPY: dict[str, str] = {
    "expand": "expand",
    "factor": "factor",
    "fullratsimp": "simplify",
    "ratsimp": "simplify",
    "simplify": "simplify",
    "cancel": "cancel",
    "radsimp": "radsimp",
}


def _split_top_level_args(arg_str: str) -> list[str]:
    """Split a comma-separated argument list at top-level commas only."""
    parts: list[str] = []
    depth = 0
    current: list[str] = []
    for ch in arg_str:
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
    return parts


def _sympify_arg(s: str):
    """sympify a Maxima/Pari arg, normalising `^` → `**` and supporting implicit mult."""
    import sympy  # noqa: PLC0415
    from sympy.parsing.sympy_parser import (
        implicit_multiplication_application,
        parse_expr,
        standard_transformations,
    )

    # Normalise WIMS-style artifacts (+-, --, etc.)
    s = s.replace("+-", "-").replace("-+", "-").replace("--", "+").replace("++", "+")
    
    transformations = standard_transformations + (implicit_multiplication_application,)
    # WIMS spells π as `Pi` (capital); map it to the constant so it isn't parsed
    # as a free symbol (sympy already knows lowercase `pi`/`E`). Idem pour les
    # fonctions WIMS écrites en majuscules (`GCD`/`LCM`/`Mod`) que sympy ne
    # connaît qu'en minuscules — sinon elles fuient en littéral dans l'attendu
    # (redfrac : `rint(GCD(720,1320);)` non évalué).
    # `coeff(e,v,n)` (coefficient de v^n) et `hipow(e,v)` (degré) : fonctions
    # maxima que sympy ne connaît pas. Fournies ici pour qu'elles s'évaluent même
    # imbriquées dans une expression composée (`coeff(P,b,2)*(b^2)` de
    # developper.def) — sinon la fonction fuit en littéral dans l'attendu.
    def _coeff(e, v, n):
        return e.coeff(v, int(n))

    def _hipow(e, v):
        return sympy.degree(e, v)

    return parse_expr(
        s.replace("^", "**"), transformations=transformations,
        local_dict={
            "Pi": sympy.pi,
            "GCD": sympy.gcd, "LCM": sympy.lcm, "Mod": sympy.Mod,
            "coeff": _coeff, "hipow": _hipow,
        },
    )


def _maxima_num_str(result) -> str:
    """Stringify a Maxima/SymPy result, trimming float noise. SymPy's
    ``str(Float('7.5'))`` emits ``7.50000000000000``; real Maxima (and WIMS)
    print ``7.5``. Integers stay integers; non-number results (symbols,
    expressions, sets) pass through unchanged."""
    import sympy  # noqa: PLC0415

    if isinstance(result, sympy.Float):
        from ..numfmt import format_wims_float  # noqa: PLC0415

        return format_wims_float(float(result))
    if isinstance(result, sympy.Integer):
        return str(int(result))
    return str(result)


def _split_equation(eq_s: str) -> tuple[str, str]:
    """Split ``lhs=rhs`` on the top-level ``=`` into ``(lhs, rhs)``.

    A bare expression (no top-level ``=``) is taken as ``expr = 0``. Brackets
    protect an inner ``=`` (none expected here, but keeps it robust).
    """
    depth = 0
    for i, ch in enumerate(eq_s):
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == "=" and depth == 0:
            return eq_s[:i], eq_s[i + 1:]
    return eq_s, "0"


def _numeric_root_in_interval(fexpr, var, a: float, b: float, n: int = 400):
    """Numeric root of ``fexpr`` (in ``var``) within ``[a, b]``, or None.

    Scans the interval for a sign change then bisects — robust for the smooth
    curves WIMS' ``solve(eq, x=a..b)`` is used on (e.g. placing a label where
    f(x)=k). Returns the first root found.
    """
    import sympy  # noqa: PLC0415

    f = sympy.lambdify(var, fexpr, modules=["math"])
    if b < a:
        a, b = b, a
    step = (b - a) / n
    prev_x = a
    try:
        prev_y = float(f(a))
    except Exception:
        prev_y = None
    for i in range(1, n + 1):
        xx = a + i * step
        try:
            yy = float(f(xx))
        except Exception:
            prev_x, prev_y = xx, None
            continue
        if prev_y is not None and prev_y == prev_y and yy == yy:
            if prev_y == 0.0:
                return prev_x
            if prev_y * yy < 0:
                lo, hi, ylo = prev_x, xx, prev_y
                for _ in range(60):
                    mid = (lo + hi) / 2.0
                    ym = float(f(mid))
                    if ym == 0.0:
                        return mid
                    if ylo * ym < 0:
                        hi = mid
                    else:
                        lo, ylo = mid, ym
                return (lo + hi) / 2.0
        prev_x, prev_y = xx, yy
    return None


def _call_maxima(expr: str) -> str:
    """Evaluate a Maxima CAS expression using SymPy as a drop-in replacement."""
    import sympy  # noqa: PLC0415

    clean = expr.strip().rstrip(";").strip()

    m = re.match(r"^(\w+)\s*\((.+)\)$", clean, re.DOTALL)
    if m:
        func_name = m.group(1).lower()
        arg_str = m.group(2).strip()
        args = _split_top_level_args(arg_str)

        if func_name == "printtex":
            try:
                return sympy.latex(_sympify_arg(arg_str))
            except Exception:
                return clean

        try:
            if func_name == "diff" and len(args) >= 2:
                e = _sympify_arg(args[0])
                var = _sympify_arg(args[1])
                order = int(args[2]) if len(args) >= 3 else 1
                return str(sympy.diff(e, var, order))
            if func_name == "ev" and args:
                # `ev(expr, x=0)` — Maxima évalue `expr` en lui appliquant les
                # équations qui suivent. L'ordre des arguments est l'inverse de
                # celui de `subst(nouveau, ancien, expr)`, avec quoi cette
                # branche était confondue : `ev` n'y entrait qu'à trois
                # arguments, si bien que la forme réelle du corpus repartait
                # telle quelle — et pire, `ev(x^2+1)` se lisait `e*v*(x^2+1)`,
                # un produit par la constante d'Euler.
                e = _sympify_arg(args[0])
                for arg in args[1:]:
                    var, sep, val = arg.partition("=")
                    # Un argument sans `=` est un mot-clé d'évaluation (`simp`,
                    # `numer`, `expand`) : sympy simplifie déjà, il n'y a rien
                    # à en faire de plus.
                    if sep and re.fullmatch(r"\s*[A-Za-z_]\w*\s*", var):
                        e = e.subs(_sympify_arg(var), _sympify_arg(val))
                return str(e)
            if func_name == "subst" and len(args) >= 3:
                val = _sympify_arg(args[0])
                var = _sympify_arg(args[1])
                e = _sympify_arg(args[2])
                return str(e.subs(var, val))
            if func_name == "coeff" and len(args) >= 2:
                e = _sympify_arg(args[0])
                var = _sympify_arg(args[1])
                n = int(args[2]) if len(args) >= 3 else 1
                return str(sympy.Poly(e, var).nth(n))  # pyright: ignore[reportCallIssue]
            if func_name == "hipow" and len(args) >= 2:
                e = _sympify_arg(args[0])
                var = _sympify_arg(args[1])
                return str(sympy.Poly(e, var).degree())  # pyright: ignore[reportCallIssue]
            if func_name == "limit" and len(args) >= 3:
                e = _sympify_arg(args[0])
                var = _sympify_arg(args[1])
                val = _sympify_arg(args[2])
                return str(sympy.limit(e, var, val))
            if func_name == "is" and len(args) == 1:
                # is(A=B) — checks equality of two expressions or sets.
                # Split the single argument on the first top-level '='.
                arg = args[0].strip()
                eq_pos = None
                depth_is = 0
                for i, ch in enumerate(arg):
                    if ch in "([{":
                        depth_is += 1
                    elif ch in ")]}":
                        depth_is -= 1
                    elif ch == "=" and depth_is == 0:
                        eq_pos = i
                        break
                if eq_pos is not None:
                    lhs_s = arg[:eq_pos].strip()
                    rhs_s = arg[eq_pos + 1:].strip()

                    def _set_from_literal(s: str):
                        """Parse a Maxima set literal {a,b,...} into a frozenset of sympified elements."""
                        s = s.strip()
                        if not (s.startswith("{") and s.endswith("}")):
                            return None
                        content = s[1:-1].strip()
                        if not content:
                            return frozenset()
                        try:
                            return frozenset(
                                _sympify_arg(x.strip())
                                for x in _split_top_level_args(content)
                                if x.strip()
                            )
                        except Exception:
                            return None

                    lhs_set = _set_from_literal(lhs_s)
                    rhs_set = _set_from_literal(rhs_s)
                    if lhs_set is not None and rhs_set is not None:
                        return "true" if lhs_set == rhs_set else "false"
                    # Fallback: numeric/algebraic equality
                    try:
                        diff = sympy.simplify(_sympify_arg(lhs_s) - _sympify_arg(rhs_s))
                        return "true" if diff == 0 else "false"
                    except Exception:
                        pass
                return clean  # cannot evaluate

            if func_name == "cardinality" and len(args) >= 1:
                inner_s = args[0].strip()
                # If the inner expression is not a plain set literal, evaluate it first.
                if not (inner_s.startswith("{") and inner_s.endswith("}")):
                    inner_s = _call_maxima(inner_s)
                if inner_s.startswith("{") and inner_s.endswith("}"):
                    content = inner_s[1:-1].strip()
                    if not content:
                        return "0"
                    # Deduplicate (sets have unique elements).
                    items = list(dict.fromkeys(x.strip() for x in _split_top_level_args(content) if x.strip()))
                    return str(len(items))
                return clean  # cannot evaluate

            if func_name == "op" and len(args) >= 1:
                e = _sympify_arg(args[0])
                if e.is_Atom:
                    return ""
                _OP_MAP = {
                    sympy.Add: "+",
                    sympy.Mul: "*",
                    sympy.Pow: "^",
                    sympy.Abs: "abs",
                }
                return _OP_MAP.get(type(e), e.func.__name__)

            if func_name == "args" and len(args) >= 1:
                e = _sympify_arg(args[0])
                if e.is_Atom:
                    return "[]"
                return "[" + ",".join(str(a) for a in e.args) + "]"

            if func_name == "ordergreat":
                return ""

            if func_name == "setdifference" and len(args) == 2:
                def _parse_finite_set(s: str):
                    s = s.strip().lstrip("{").rstrip("}")
                    items = _split_top_level_args(s) if s.strip() else []
                    elems = [_sympify_arg(x) for x in items if x.strip()]
                    return sympy.FiniteSet(*elems) if elems else sympy.EmptySet

                diff = _parse_finite_set(args[0]) - _parse_finite_set(args[1])
                if diff == sympy.EmptySet:
                    return "{}"
                return "{" + ",".join(str(e) for e in diff) + "}"

        except Exception:
            pass

        sympy_func_name = _MAXIMA_TO_SYMPY.get(func_name)
        if sympy_func_name:
            try:
                sympy_func = getattr(sympy, sympy_func_name)
                result = sympy_func(_sympify_arg(arg_str))
                return _maxima_num_str(result)
            except Exception:
                return clean

    try:
        result = sympy.simplify(_sympify_arg(clean))
        if result.is_number and result.is_integer:
            return str(int(result))
        return _maxima_num_str(result)
    except Exception:
        return expr


# A bare integer ratio `a/b` (optionally signed) — the only shape we re-evaluate
# in `_expr_to_latex` to strip the spurious `1 \cdot` unit coefficient.
_PURE_INT_FRAC_RE = re.compile(r"^-?\d+\s*/\s*-?\d+$")


def _split_top_level_equals(s: str) -> list[str] | None:
    """Membres d'une égalité de premier niveau, ou ``None`` s'il n'y en a pas.

    Seul le « = » **simple** et **hors parenthèses** sépare. Les opérateurs
    relationnels composés (``<=``, ``>=``, ``==``, ``!=``) restent dans leur
    membre : sympy sait les rendre lui-même (``\\leq``, ``\\geq``…), et les
    couper les détruirait.
    """
    parts: list[str] = []
    depth = start = 0
    for i, c in enumerate(s):
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif c == "=" and depth == 0:
            prev = s[i - 1] if i else ""
            nxt = s[i + 1] if i + 1 < len(s) else ""
            if prev in "<>=!" or nxt == "=":
                continue
            parts.append(s[start:i])
            start = i + 1
    if not parts:
        return None
    parts.append(s[start:])
    return parts


# Jetons que sympy ne sait pas lire au milieu d'une expression, et leur forme
# LaTeX. L'ordre compte : les composés d'abord, sinon `<=` se lirait `<`.
_PART_TOKENS: tuple[tuple[str, str], ...] = (
    ("<=", r"\leq"), (">=", r"\geq"), ("!=", r"\neq"), ("<>", r"\neq"),
    ("<", "<"), (">", ">"), (";", ";"),
)


def _split_top_level_tokens(s: str) -> tuple[list[str], list[str]] | None:
    """(morceaux, séparateurs LaTeX) autour des jetons de premier niveau."""
    parts: list[str] = []
    seps: list[str] = []
    depth = start = i = 0
    while i < len(s):
        c = s[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif depth == 0:
            for tok, tex in _PART_TOKENS:
                if s.startswith(tok, i):
                    parts.append(s[start:i])
                    seps.append(tex)
                    i += len(tok)
                    start = i
                    break
            else:
                i += 1
            continue
        i += 1
    if not seps:
        return None
    parts.append(s[start:])
    return parts, seps


def _render_by_parts(expr_strip: str, func_names, wrapped: bool) -> str | None:
    """Rend une expression morceau par morceau, quand sympy cale sur l'ensemble.

    Deux notations scolaires y échouent alors que chaque morceau se rend très
    bien :

    * l'**encadrement**, `3.87 < sqrt(15) < 3.88` (`solveineq3`) — sympy ne
      chaîne pas les comparaisons, là où `t_onestring` (`texmath.c`) découpe la
      chaîne en termes et laisse `t_oneterm` imprimer l'opérateur rencontré ;
    * le **couple de coordonnées à la française**, `( 5 ; 6*sqrt(2) )`
      (`longueur4`), dont le point-virgule n'est pas un opérateur.

    Faute de mieux, l'expression entière repartait telle quelle et son `sqrt(`
    s'affichait en clair. On ne tente ce découpage qu'**après** l'échec du
    parse : ce qui se rend d'un bloc continue de se rendre d'un bloc.
    """
    inner = expr_strip[1:-1].strip() if wrapped else expr_strip
    decoupe = _split_top_level_tokens(inner)
    if decoupe is None:
        return None
    parts, seps = decoupe
    if any(not p.strip() for p in parts):
        return None
    rendus = [_expr_to_latex(p.strip(), func_names) for p in parts]
    # Rien de gagné si aucun morceau n'a bougé : mieux vaut la chaîne d'origine
    # que la nôtre, recollée avec un espacement qui n'est pas celui de l'auteur.
    if all(r == p.strip() for r, p in zip(rendus, parts)):
        return None
    out = rendus[0]
    for sep, r in zip(seps, rendus[1:]):
        out = f"{out} {sep} {r}"
    return f"\\left({out}\\right)" if wrapped else out


def _wims_factor_rank(node) -> int:
    """Rang d'un facteur dans un terme, façon ``fsort`` (``src/texmath.c``).

    Le C classe par type et plafonne tout ce qui dépasse la variable :

        i1=t1->type; if(i1>type_var) i1=type_var;
        return i1-i2;

    avec ``enum {type_integer, type_numeric, type_var, type_poly,
    type_transcend}``. D'où trois rangs seulement — entier, numérique, le
    reste —, le coefficient passant devant sa variable (``x*3`` → ``3x``).
    """
    if getattr(node, "is_Integer", False):
        return 0
    if getattr(node, "is_Number", False):
        return 1
    return 2


def _drop_unit_factors(node):
    """Met l'arbre dans la forme que WIMS imprimerait : sans facteur 1, et les
    facteurs d'un terme classés par type.

    ``parse_expr(evaluate=False)`` garde l'arbre tel que l'auteur l'a écrit —
    c'est tout l'intérêt pour ``!texmath``, qui ne doit pas donner la réponse.
    Mais il garde aussi le ``1`` que sympy aurait absorbé de lui-même : ``1/x``
    est un ``Mul(Integer(1), Pow(x, -1))``, que ``sympy.latex`` imprime
    ``1 \\frac{1}{x}``. Un élève y lit un nombre mixte — « un et un sur x ».

    Le facteur neutre part donc à la **construction**, avant l'appel à
    ``latex``. Le retirer de la chaîne LaTeX après coup supposerait de
    distinguer ce ``1`` d'un ``1`` légitime, que plus rien ne sépare une fois
    le rendu fait (``1 \\frac{1}{2}`` parasite contre un « 1 » d'énoncé).

    Le ``-1`` est épargné, et il le faut : ``_expr_to_latex`` réécrit exprès
    ``-(`` en ``(-1)*(`` pour empêcher sympy de distribuer le signe, la forme
    non développée étant l'énoncé même de `distribuer1`.

    Le classement des facteurs (``_wims_factor_rank``) accompagne le
    ``order='none'`` de l'appelant : couper le tri du printer rend aux *termes*
    l'ordre de la source, ce que veut WIMS, mais le coupe aussi pour les
    *facteurs*, que WIMS trie. On le rétablit donc ici, au seul niveau où le C
    le fait — et de façon stable, là où son ``qsort`` laisse l'ordre des
    ex æquo indéterminé.
    """
    import sympy  # noqa: PLC0415

    if not getattr(node, "args", ()):
        return node
    new_args = [_drop_unit_factors(a) for a in node.args]
    if node.is_Mul:
        kept = [a for a in new_args if not (a.is_Integer and a == 1)]
        if not kept:  # `1*1` : il reste le neutre lui-même.
            return sympy.Integer(1)
        if len(kept) == 1:
            return kept[0]
        new_args = sorted(kept, key=_wims_factor_rank)
    if len(new_args) == len(node.args) and all(
        a is b for a, b in zip(new_args, node.args)
    ):
        return node
    try:
        return node.func(*new_args, evaluate=False)
    except TypeError:
        return node.func(*new_args)


def _expr_to_latex(expr: str, func_names: set[str] | None = None) -> str:
    """Convert a math expression string to LaTeX notation for display.

    ``func_names`` lists single identifiers that the caller knows are function
    applications (``f`` in ``f(x)``), not multiplication. They're bound to
    ``sympy.Function`` so SymPy keeps ``f(x)`` instead of reading it as ``f*x``
    and rendering ``f x`` (parens dropped).

    Critically does NOT simplify — used by ``!texmath`` to render an
    expression *as the author wrote it*. The reduire1..reduire5 family
    of exercises hands `3*x + 5*x + 2 + 1` to !texmath expecting the
    student to reduce it; ``sympify`` would have collapsed that to
    ``8*x + 3`` (Add simplifies on construction), giving the answer
    away in the statement. Use ``parse_expr(..., evaluate=False)`` to
    keep the Add/Mul tree intact.
    """
    import sympy  # noqa: PLC0415
    from sympy.parsing.sympy_parser import (
        implicit_multiplication_application,
        parse_expr,
        standard_transformations,
    )

    expr_strip = expr.strip()

    # Un « = » de premier niveau : chaque membre se rend séparément, puis on
    # les rejoint. `parse_expr` lit `C = x` comme une affectation Python et ne
    # renvoie que le membre droit — en distribuant, et en perdant le « C = ».
    # D'où l'ancien garde-fou, qui rendait toute l'expression telle quelle :
    # `-2*x = -1` s'affichait avec son astérisque et `-3*sqrt(x) - 9 = 0`
    # gardait son `sqrt(` en clair, 200 formules du corpus dans ce cas. Traiter
    # les membres un à un lève les deux : `C` reste `C`, et le reste passe par
    # le rendu normal. WIMS ne fait pas autrement — `t_oneterm` (`texmath.c`)
    # imprime l'opérateur de relation et poursuit sur le membre suivant.
    membres = _split_top_level_equals(expr_strip)
    if membres and any(m.strip() for m in membres):
        # Un membre vide est courant et voulu : `-4*(-2*x + 5) =` précède le
        # champ que l'élève remplit. On rend ce qu'il y a et on garde le « = ».
        return " = ".join(
            _expr_to_latex(m.strip(), func_names) if m.strip() else ""
            for m in membres
        ).rstrip()

    wrapped = False
    if expr_strip.startswith("(") and expr_strip.endswith(")"):
        depth = 0
        is_single_group = True
        for i, c in enumerate(expr_strip):
            if c == "(": depth += 1
            elif c == ")": depth -= 1
            if depth == 0 and i < len(expr_strip) - 1:
                is_single_group = False
                break
        if is_single_group:
            wrapped = True

    # Force the namespace-poisoning single-letter names (N, O, I, E,
    # S, Q, C) to Symbols so `\(N\)` doesn't render as the sympy.N
    # function — same fix as in checkers.py / presentation.py.
    locals_dict = {
        name: sympy.Symbol(name) for name in ("N", "O", "I", "E", "S", "Q", "C")
    }
    # Function-application names (``f(x)``) win over the Symbol poisoning above:
    # `\(f(x)\)` is a function, not the variable `f` times `x`.
    for fn in func_names or ():
        locals_dict[fn] = sympy.Function(fn)
    transformations = standard_transformations + (
        implicit_multiplication_application,
    )

    # Sympy distributes unary minus across an Add even with
    # evaluate=False: `-(5u+6)` becomes `-5u - 6` at parse, which is
    # wrong for `!texmath` (distribuer1: the statement should show the
    # *non*-distributed form for the student to develop). Rewriting
    # `-(` as `(-1)*(` keeps the parenthesised structure: sympy parses
    # it as `Mul(-1, Add(...))` without distributing.
    # Le motif doit enjamber les espaces des deux côtés du moins, et le
    # lookbehind de longueur fixe ne le permet pas : on capture donc ce qui
    # précède. Un moins est **unaire** en début de chaîne ou après un
    # opérateur ; après un opérande (mot, chiffre, parenthèse fermante) il est
    # binaire, quel que soit l'espacement. L'ancien `(?<![\w)])-\(` ne voyait
    # que le caractère collé au moins : `a -(b+c)` lui semblait unaire et
    # sortait `- a (b+c)`, et `- (7b+3)` lui échappait — donc se distribuait,
    # ce que `distribuer1` ne peut pas se permettre (la forme non développée
    # *est* l'énoncé).
    prep = re.sub(r'(^|[^\w)\s])\s*-\s*\(', r'\1(-1)*(', expr_strip)

    # A bare integer ratio `a/b` parses (evaluate=False) as `Mul(a, 1/b)` and
    # renders a spurious unit coefficient (`1/4` → `1 \cdot \frac{1}{4}`).
    # Emit `\frac{a}{b}` directly instead — *without* reducing: evaluate=True
    # would collapse `10/20` → `1/2`, changing the very fraction the author
    # chose to display (quizz 0512 shows the un-reduced form on purpose).
    if _PURE_INT_FRAC_RE.match(expr_strip):
        a_str, b_str = expr_strip.split("/")
        a, b = int(a_str), int(b_str)
        if b < 0:
            a, b = -a, -b
        sign = "-" if a < 0 else ""
        return rf"{sign}\frac{{{abs(a)}}}{{{b}}}"

    try:
        parsed = parse_expr(
            prep.replace("^", "**"),
            transformations=transformations,
            local_dict=locals_dict,
            evaluate=False,
        )
        # `order='none'` : imprimer les termes dans l'ordre où l'auteur les a
        # écrits. Le printer sympy trie par défaut (`order='lex'`), si bien que
        # `14/10 + 9/8` s'affichait `9/8 + 14/10` — les opérandes inversés dans
        # l'énoncé même. WIMS ne trie pas les termes d'une somme : `t_onestring`
        # (`src/texmath.c`) les émet dans l'ordre de la source, et son seul tri
        # (`qsort`/`fsort`) porte sur les facteurs *à l'intérieur* d'un terme.
        # Le tri était d'autant plus gênant que la famille `reduire1p…` compare
        # les rawmath littéralement (cf. `check_litexp`) : l'élève doit
        # retrouver l'ordre stocké, que l'énoncé lui montrait déjà réarrangé.
        res = sympy.latex(_drop_unit_factors(parsed), order="none")
        if wrapped and not (res.startswith("(") or res.startswith("\\left(")):
            res = f"\\left({res}\\right)"
        return res
    except Exception:
        rendu = _render_by_parts(expr_strip, func_names, wrapped)
        return rendu if rendu is not None else expr


# ── PARI helpers ─────────────────────────────────────────────────────────────


def _pari_concat(*args):
    """PARI `concat` : concaténation de **vecteurs**, en aplatissant d'un
    niveau — `concat(5,1)` vaut `[5,1]` et non la chaîne `"51"`. Tous les
    usages du corpus sont des accumulations de listes (`xl=concat(xl,xi)`).
    Le repli textuel ne sert que si un argument est déjà une chaîne.
    """
    if any(isinstance(a, str) for a in args):
        return "".join(str(a) for a in args)
    items: list = []
    for arg in args:
        if isinstance(arg, (list, tuple)):
            items.extend(arg)
        else:
            items.append(arg)
    return items


def _pari_expand(p):
    import sympy  # noqa: PLC0415

    return sympy.expand(p)


def _pari_denominator(x):
    import sympy  # noqa: PLC0415

    if isinstance(x, int) or (isinstance(x, float) and float(x).is_integer()):
        return 1
    return sympy.fraction(sympy.together(x))[1]


def _pari_numerator(x):
    import sympy  # noqa: PLC0415

    if isinstance(x, int):
        return x
    if isinstance(x, float) and float(x).is_integer():
        return int(x)
    return sympy.fraction(sympy.together(x))[0]


def _pari_vecmax(v):
    if hasattr(v, "__iter__") and not isinstance(v, str):
        return max(v)
    return v


def _pari_vecmin(v):
    if hasattr(v, "__iter__") and not isinstance(v, str):
        return min(v)
    return v


def _pari_divrem(a, b):
    import sympy  # noqa: PLC0415

    def _is_int_like(v) -> bool:
        return isinstance(v, int) or getattr(v, "is_integer", False) is True

    if _is_int_like(a) and _is_int_like(b):
        q, r = divmod(int(a), int(b))
        return [q, r]
    # Deux réels : `divrem` reste la division **euclidienne** — quotient entier,
    # reste de même signe que le diviseur, comme `divmod`. C'est la seule
    # lecture qui ait un sens pour les `divrem($val28, 60)` de `moho0`, qui
    # convertissent un temps de trajet en minutes et secondes. `sympy.div`,
    # elle, fait une division **polynomiale** : sur deux nombres elle rend
    # (a/b, 0), et le reste — la seconde composante, précisément ce que
    # l'exercice lit — était perdu.
    if _est_nombre(a) and _est_nombre(b):
        q, r = divmod(float(a), float(b))
        return [int(q), r]
    q, r = sympy.div(a, b)  # pyright: ignore[reportCallIssue]
    return [q, r]


def _est_nombre(v: Any) -> bool:
    """Vrai pour un scalaire numérique — Python ou sympy —, faux pour un
    polynôme ou une expression symbolique."""
    if isinstance(v, (int, float)):
        return True
    return bool(getattr(v, "is_number", False))


def _pari_polcoeff(p, n, var=None):
    import sympy  # noqa: PLC0415

    if var is None:
        syms = list(p.free_symbols) if hasattr(p, "free_symbols") else []
        var = syms[0] if syms else sympy.Symbol("x")
    return sympy.Poly(p, var).nth(int(n))  # pyright: ignore[reportCallIssue]


def _pari_poldegree(p, var=None):
    import sympy  # noqa: PLC0415

    if isinstance(p, (int, float)):
        return 0
    if var is None:
        syms = list(p.free_symbols)
        var = syms[0] if syms else sympy.Symbol("x")
    return sympy.Poly(p, var).degree()  # pyright: ignore[reportCallIssue]


def _pari_matdet(rows):
    import sympy  # noqa: PLC0415

    return sympy.Matrix(rows).det()


def _pari_isprime(n):
    import sympy  # noqa: PLC0415

    return 1 if sympy.isprime(int(n)) else 0


def _pari_subst(p, var, val):
    if hasattr(p, "subs"):
        return p.subs(var, val)
    return p


def _pari_vec(x=None):
    """`Vec(x)` — conversion en vecteur ligne.

    `slib/triplerelation/tabular` part d'une liste littérale (`Vec([1,0])`)
    avant de lui ajouter un vecteur indicateur. Sans cette entrée, `Vec` était
    auto-lié à un symbole libre : le résultat tombait juste par accident sur
    les cas simples, et faux dès que l'expression se compliquait.
    """
    if x is None:
        return []
    if isinstance(x, (list, tuple)):
        return list(x)
    if hasattr(x, "__iter__") and not isinstance(x, str):
        return list(x)
    return [x]


def _pari_matrix(rows, ncols=None, body=None):
    """`matrix(rows)` — depuis une liste — ou `matrix(m, n, I, J, expr)`.

    La seconde forme est la plus fréquente du corpus (160 usages), et son
    corps arrive en lambda à deux paramètres : PARI l'évalue case par case,
    lignes et colonnes numérotées à partir de 1.
    """
    import sympy  # noqa: PLC0415

    if callable(body):
        m, n = int(rows), int(ncols)
        return sympy.Matrix(
            m, n,
            lambda i, j: _pari_valeur_pari(
                body(sympy.Integer(i + 1), sympy.Integer(j + 1))
            ),
        )
    if ncols is not None:
        # `matrix(m, n)` — matrice nulle.
        return sympy.zeros(int(rows), int(ncols))
    return sympy.Matrix(rows)


def _pari_mat(v):
    """Pari Mat(v): convert vector/list to a matrix (row vector → 1×n matrix)."""
    import sympy  # noqa: PLC0415

    if isinstance(v, sympy.Matrix):
        return v
    if isinstance(v, (list, tuple)):
        if v and isinstance(v[0], (list, tuple, sympy.Matrix)):
            return sympy.Matrix(v)
        return sympy.Matrix([list(v)])
    return sympy.Matrix([[v]])


def _pari_mattranspose(m):
    """Pari mattranspose(m): transpose a matrix or row vector."""
    import sympy  # noqa: PLC0415

    if isinstance(m, sympy.Matrix):
        return m.T
    if isinstance(m, (list, tuple)):
        if m and isinstance(m[0], (list, tuple)):
            return sympy.Matrix(m).T
        return sympy.Matrix([list(m)]).T
    return m


def _pari_matsize(m):
    """Pari matsize(m): return [rows, cols]."""
    import sympy  # noqa: PLC0415

    if isinstance(m, sympy.Matrix):
        return [m.rows, m.cols]
    if isinstance(m, (list, tuple)):
        if m and isinstance(m[0], (list, tuple)):
            return [len(m), len(m[0]) if m else 0]
        return [1, len(m)]
    return [1, 1]


def _parse_pari_range(r, n: int) -> list[int]:
    """Convert a Pari range string like '1..3' or '-1..-2' to a list of 0-based indices."""
    r = str(r).strip().strip("\"'")
    m = re.match(r"^(-?\d+)\.\.(-?\d+)$", r)
    if m:
        a, b = int(m.group(1)), int(m.group(2))
        if a < 0:
            a = n + a + 1
        if b < 0:
            b = n + b + 1
        step = 1 if a <= b else -1
        return [i - 1 for i in range(a, b + step, step) if 1 <= i <= n]
    try:
        idx = int(r)
        if idx < 0:
            idx = n + idx + 1
        return [idx - 1] if 1 <= idx <= n else []
    except Exception:
        return list(range(n))


def _pari_vecextract(v, row_range, col_range=None):
    """Pari vecextract(v, range) or vecextract(mat, row_range, col_range)."""
    import sympy  # noqa: PLC0415

    if isinstance(v, sympy.Matrix):
        mat = v
    elif isinstance(v, (list, tuple)):
        if v and isinstance(v[0], (list, tuple)):
            mat = sympy.Matrix(v)
        else:
            mat = sympy.Matrix([list(v)])
    else:
        return v

    if col_range is None:
        flat = [mat[i, j] for i in range(mat.rows) for j in range(mat.cols)]
        indices = _parse_pari_range(row_range, len(flat))
        return [flat[i] for i in indices]

    row_indices = _parse_pari_range(row_range, mat.rows)
    col_indices = _parse_pari_range(col_range, mat.cols)
    result_rows = [
        [mat[ri, ci] for ci in col_indices]
        for ri in row_indices
    ]
    if len(result_rows) == 1:
        return result_rows[0]
    return sympy.Matrix(result_rows) if result_rows else []


def _pari_polrev(*args):
    """Pari Polrev(v): polynomial from coefficient list (index 0 = constant term)."""
    import sympy  # noqa: PLC0415

    if len(args) == 1 and hasattr(args[0], "__iter__") and not isinstance(args[0], str):
        coeffs = list(args[0])
    else:
        coeffs = list(args)
    x = sympy.Symbol("x")
    return sympy.expand(sum(c * x**i for i, c in enumerate(coeffs)))


def _pari_valeur_pari(val):
    """Ramène le résultat d'un corps lié à ce que PARI en ferait.

    Une comparaison y vaut 1 ou 0 — `(row==2)*(col==3)` est l'idiome du
    vecteur/matrice indicateur —, et un nombre exact perd sa forme sympy.
    """
    import sympy  # noqa: PLC0415

    if isinstance(val, bool) or val in (sympy.true, sympy.false):
        return 1 if bool(val) else 0
    try:
        fval = float(sympy.N(val))
    except Exception:
        return val
    return int(fval) if fval == int(fval) else fval


def _pari_vector(n_or_list=None, var=None, body=None):
    """Pari vector(n) → zero list; vector(n, i, expr) → list comprehension.

    Le corps arrive sous forme de **lambda** quand l'expression le liait à une
    variable (cf. `_LierVariables` dans `pari_prog`) : PARI l'évalue une fois
    par indice, ce que la forme paresseuse rend fidèlement. L'ancienne forme —
    variable et expression déjà évaluée — reste acceptée.
    """
    import sympy  # noqa: PLC0415

    if callable(var):
        n = int(n_or_list)
        return [_pari_valeur_pari(var(sympy.Integer(k))) for k in range(1, n + 1)]

    if var is None or body is None:
        try:
            n = int(n_or_list)
            return [sympy.Integer(0)] * n
        except Exception:
            return list(n_or_list) if hasattr(n_or_list, "__iter__") else []
    n = int(n_or_list)
    result = []
    for k in range(1, n + 1):
        val = body.subs(var, sympy.Integer(k))
        try:
            fval = float(sympy.N(val))
            result.append(int(fval) if fval == int(fval) else fval)
        except Exception:
            result.append(val)
    return result


def _pari_round(x):
    """Pari round(): works on SymPy expressions by numeric evaluation."""
    import sympy  # noqa: PLC0415

    try:
        return sympy.Integer(round(float(sympy.N(x))))
    except Exception:
        return x


def _pari_core(n):
    """Squarefree part of an integer (sign-preserving)."""
    import sympy  # noqa: PLC0415

    n = int(n)
    if n == 0:
        return 0
    sign = 1 if n > 0 else -1
    n = abs(n)
    result = 1
    for p, e in sympy.factorint(n).items():
        if e % 2 == 1:
            result *= p
    return sign * result


_PARI_HELPERS: dict = {
    "concat": _pari_concat,
    "expand": _pari_expand,
    "denominator": _pari_denominator,
    "numerator": _pari_numerator,
    "vecmax": _pari_vecmax,
    "vecmin": _pari_vecmin,
    "divrem": _pari_divrem,
    "polcoeff": _pari_polcoeff,
    "poldegree": _pari_poldegree,
    "matdet": _pari_matdet,
    "mattranspose": _pari_mattranspose,
    "matsize": _pari_matsize,
    "Mat": _pari_mat,
    "vecextract": _pari_vecextract,
    "Polrev": _pari_polrev,
    "isprime": _pari_isprime,
    "subst": _pari_subst,
    "matrix": _pari_matrix,
    "vector": _pari_vector,
    "Vec": _pari_vec,
    "round": _pari_round,
    "core": _pari_core,
}

_PYTHON_KEYWORDS: set = {
    "True",
    "False",
    "None",
    "and",
    "or",
    "not",
    "if",
    "else",
    "elif",
    "for",
    "in",
    "while",
    "lambda",
    "is",
}


def _format_pari_result(result) -> str:
    import sympy  # noqa: PLC0415

    if isinstance(result, bool):
        return "1" if result else "0"
    if isinstance(result, int):
        return str(result)
    if isinstance(result, float):
        if result.is_integer():
            return str(int(result))
        return f"{result:.10g}"
    if isinstance(result, sympy.Integer):
        return str(int(result))
    if isinstance(result, sympy.Float):
        f = float(result)
        if f.is_integer():
            return str(int(f))
        return f"{f:.10g}"
    if isinstance(result, sympy.Matrix):
        if result.rows == 1:
            return ",".join(_format_pari_result(result[0, j]) for j in range(result.cols))
        if result.cols == 1:
            return ",".join(_format_pari_result(result[i, 0]) for i in range(result.rows))
        rows = [
            ",".join(_format_pari_result(result[i, j]) for j in range(result.cols))
            for i in range(result.rows)
        ]
        return ";".join(rows)
    if isinstance(result, (list, tuple)):
        return ",".join(_format_pari_result(x) for x in result)
    # `PVec` (mini-interpréteur PARI) : un vecteur, qui s'écrit donc comme un
    # vecteur. Sans cette branche, son `repr` Python fuyait tel quel dans
    # l'attendu — `PVec([13,94,175],col=False)` au lieu de `13,94,175`, ce que
    # les `pixel_art_flag*` affichaient à l'élève.
    if hasattr(result, "items") and hasattr(result, "col") and not isinstance(result, dict):
        return ",".join(_format_pari_result(x) for x in result.items)
    # PARI uses `^` for exponentiation; SymPy's str() emits `**`. The downstream
    # WIMS pipeline (e.g. `!replace * by`) treats `*` literally, so leaving `**`
    # would corrupt powers like `x**2` into `x2`.
    return str(result).replace("**", "^")


# Wraps standalone integer literals so `/` between them produces a Rational
# (PARI semantics), not a float.
# The negative lookahead (?!\.\d?|\w) avoids wrapping in float literals (10., 10.5)
# or identifiers (10x would be unusual, but guards against partial matches).
_INT_LITERAL_RE = re.compile(r"(?<![\w.])(\d+)(?!\.\d?|\w)")

# A bare *flat* vector literal `[a,b,…]` (no nested brackets, and not an index
# like `v[1]` — guarded by the lookbehind). PARI allows scalar/vector arithmetic
# (`1.2*[a,b,c]` → `[1.2a,1.2b,1.2c]`), which is invalid Python; we wrap these as
# row matrices in the _call_pari fallback so the op broadcasts elementwise.
_VEC_LITERAL_RE = re.compile(r"(?<![\w\])])\[([^\[\]]+)\]")


def _call_pari(expr: str, session: dict | None = None) -> str:
    """Evaluate a PARI/GP-style expression via Python.

    Unknown identifiers are auto-bound to SymPy symbols, so polynomial
    expressions like ``polcoeff(x^2 + 3*x + 2, 1)`` evaluate symbolically.
    Integer literals are wrapped as ``sympy.Integer`` so ``3/4`` becomes the
    Rational 3/4 rather than the float 0.75.

    ``session`` porte les variables du mini-interpréteur entre deux ``!exec
    pari`` du même exercice (WIMS pilote un unique processus ``gp``).
    """
    import sympy  # noqa: PLC0415
    from sympy.parsing.sympy_parser import (
        implicit_multiplication_application,
        parse_expr,
        standard_transformations,
    )

    from .pari_prog import (  # noqa: PLC0415
        PariProgramError,
        looks_like_program,
        run_pari_program,
        session_porte_un_etat,
    )

    # Programme impératif (affectations, `for`, `print` multiples) : le mini-
    # interpréteur l'exécute. Une session qui porte déjà un état y route aussi
    # les expressions simples, qui peuvent lire ce qu'un `!exec pari` antérieur
    # y a posé (`print(l)` après `l=vector(n);…`, `print(f(2))` après
    # `f(t)=…`). Hors périmètre → on retombe sur l'évaluation d'expression
    # ci-dessous.
    if looks_like_program(expr) or session_porte_un_etat(session):
        try:
            return run_pari_program(
                expr, {**_MATH_NS, **_PARI_HELPERS}, session=session
            )
        except PariProgramError:
            pass

    clean = expr.strip().rstrip(";").strip()
    m = re.match(r"^print\s*\((.+)\)$", clean, re.DOTALL)
    if m:
        clean = m.group(1).strip()

    # Pre-process notation — preserve quoted string literals before integer wrapping
    clean = clean.replace("^", "**")
    _string_cache: dict[str, str] = {}

    def _stash_string(sm) -> str:
        key = f"\x00S{len(_string_cache)}\x00"
        _string_cache[key] = sm.group(0)
        return key

    clean = re.sub(r'"[^"]*"', _stash_string, clean)
    clean = _INT_LITERAL_RE.sub(r"_I(\1)", clean)
    for key, val in _string_cache.items():
        clean = clean.replace(key, val)

    ns: dict = dict(_MATH_NS)
    ns.update(_PARI_HELPERS)
    ns["_I"] = sympy.Integer
    # Auto-bind symbols
    for ident in set(re.findall(r"[a-zA-Z_]\w*", clean)):
        if ident not in ns and ident not in _PYTHON_KEYWORDS:
            ns[ident] = sympy.Symbol(ident)

    transformations = standard_transformations + (
        implicit_multiplication_application,
    )

    # PARI vectors `[...]` use *elementwise* +, -, and scalar * (e.g.
    # `[6,5]+[1,-2]` → `[7,3]`, `2*[1,2,3]` → `[2,4,6]`). Python lists, which
    # `parse_expr` would otherwise build, instead *concatenate*/​*repeat*
    # (`[6,5,1,-2]`, `[1,2,3,1,2,3]`) — wrong, and a silent success that never
    # reaches the exception fallback below. So when a flat vector literal takes
    # part in such arithmetic, wrap the literals as row matrices first so the
    # op broadcasts elementwise (coord2 builds the target point as `[v]+[P]`).
    # Skipped for matrix literals (`[[…],[…]]`) and bare/indexed vectors.
    if (
        "[[" not in clean
        and "]]" not in clean
        and _VEC_LITERAL_RE.search(clean)
        and (
            re.search(r"\]\s*[-+]\s*\[", clean)
            # scalar/​symbol after `]*` is `_I(…)`-wrapped, hence `[\w(]`.
            or re.search(r"\]\s*\*\s*[\w(]", clean)
            or re.search(r"[\w.)\]]\s*\*\s*\[", clean)
        )
    ):
        try:
            ns_v = dict(ns)
            ns_v["_V"] = lambda *a: sympy.Matrix([list(a)])
            vec_clean = _VEC_LITERAL_RE.sub(r"_V(\1)", clean)
            return _format_pari_result(
                parse_expr(vec_clean, local_dict=ns_v, transformations=transformations)
            )
        except Exception:
            pass  # fall back to the plain parse below

    try:
        result = parse_expr(clean, local_dict=ns, transformations=transformations)
        # PARI's internal representation of polynomials is always expanded;
        # mirror that so e.g. `pari (x-3)*(x+3)` returns `x^2 - 9`.
        if isinstance(result, sympy.Expr):
            result = sympy.expand(result)
        return _format_pari_result(result)
    except Exception:
        # Fallback: PARI vector arithmetic. A bare flat vector literal combined
        # with a scalar (e.g. `1.2*[a,b,c]`) is invalid Python, so the parse
        # above raised. Re-parse with such literals wrapped as row matrices so
        # the scalar op broadcasts elementwise; _format_pari_result then renders
        # the row matrix back as a comma list (used by slib/draw/range extents).
        if _VEC_LITERAL_RE.search(clean):
            try:
                ns["_V"] = lambda *a: sympy.Matrix([list(a)])
                vec_clean = _VEC_LITERAL_RE.sub(r"_V(\1)", clean)
                return _format_pari_result(
                    parse_expr(vec_clean, local_dict=ns, transformations=transformations)
                )
            except Exception:
                pass
        return expr
