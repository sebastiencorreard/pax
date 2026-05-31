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
    "exp": math.exp,
    "floor": math.floor,
    "ceil": math.ceil,
    "pi": math.pi,
    # WIMS also spells π as `Pi` (capital) — e.g. quizz 1211's matrix
    # `quest=e,Pi,sqrt(2)`; without it `$[rint(…+Pi)]` raised NameError and the
    # literal `rint(1.414…+Pi)` leaked into the expected answer.
    "Pi": math.pi,
    "e": math.e,
    "mod": lambda a, b: float(a) % float(b),
    "fact": math.factorial,
    "sign": lambda x: 1 if x > 0 else -1 if x < 0 else 0,
    "gcd": math.gcd,
    "lcm": _lcm,
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
    # as a free symbol (sympy already knows lowercase `pi`/`E`).
    return parse_expr(
        s.replace("^", "**"), transformations=transformations,
        local_dict={"Pi": sympy.pi},
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
            if func_name in ("subst", "ev") and len(args) >= 3:
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


def _expr_to_latex(expr: str) -> str:
    """Convert a math expression string to LaTeX notation for display.

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

    # Single-expression renderer: a top-level lone "=" means we were handed an
    # equation/assignment (e.g. "C = -(7b+3)", built by _normalize_math_content
    # from "$name = $texmath"). Don't sympify it — parse_expr would raise for an
    # ordinary name (→ returned unchanged) but, for a name poisoned into
    # local_dict below (C, E, N, …), parses "C = x" as a Python assignment and
    # silently returns just the RHS (dropping "C =" and distributing it). Leave
    # such strings to the caller; relational "=" (<=, >=, ==, !=) still render.
    if re.search(r"(?<![<>=!])=(?!=)", expr_strip):
        return expr

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
    transformations = standard_transformations + (
        implicit_multiplication_application,
    )

    # Sympy distributes unary minus across an Add even with
    # evaluate=False: `-(5u+6)` becomes `-5u - 6` at parse, which is
    # wrong for `!texmath` (distribuer1: the statement should show the
    # *non*-distributed form for the student to develop). Rewriting
    # `-(` as `(-1)*(` keeps the parenthesised structure: sympy parses
    # it as `Mul(-1, Add(...))` without distributing.
    prep = re.sub(r'(?<![\w)])-\(', '(-1)*(', expr_strip)

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
        res = sympy.latex(parsed)
        if wrapped and not (res.startswith("(") or res.startswith("\\left(")):
            res = f"\\left({res}\\right)"
        return res
    except Exception:
        return expr


# ── PARI helpers ─────────────────────────────────────────────────────────────


def _pari_concat(*args) -> str:
    return "".join(str(a) for a in args)


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
    q, r = sympy.div(a, b)  # pyright: ignore[reportCallIssue]
    return [q, r]


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


def _pari_matrix(rows):
    import sympy  # noqa: PLC0415

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


def _pari_vector(n_or_list=None, var=None, body=None):
    """Pari vector(n) → zero list; vector(n, i, expr) → list comprehension."""
    import sympy  # noqa: PLC0415

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


def _call_pari(expr: str) -> str:
    """Evaluate a PARI/GP-style expression via Python.

    Unknown identifiers are auto-bound to SymPy symbols, so polynomial
    expressions like ``polcoeff(x^2 + 3*x + 2, 1)`` evaluate symbolically.
    Integer literals are wrapped as ``sympy.Integer`` so ``3/4`` becomes the
    Rational 3/4 rather than the float 0.75.
    """
    import sympy  # noqa: PLC0415
    from sympy.parsing.sympy_parser import (
        implicit_multiplication_application,
        parse_expr,
        standard_transformations,
    )

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
