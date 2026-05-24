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
- ``_sympy_to_latex`` — string-in / LaTeX-out helper used by ``!texmath``
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
    "log": math.log,
    "log10": math.log10,
    "log2": math.log2,
    "exp": math.exp,
    "floor": math.floor,
    "ceil": math.ceil,
    "pi": math.pi,
    "e": math.e,
    "mod": lambda a, b: float(a) % float(b),
    "fact": math.factorial,
    "sign": lambda x: 1 if x > 0 else -1 if x < 0 else 0,
    "gcd": math.gcd,
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
    return parse_expr(s.replace("^", "**"), transformations=transformations)


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
                return str(result)
            except Exception:
                return clean

    try:
        result = sympy.simplify(_sympify_arg(clean))
        if result.is_number and result.is_integer:
            return str(int(result))
        return str(result)
    except Exception:
        return expr


def _sympy_to_latex(expr: str) -> str:
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

    try:
        parsed = parse_expr(
            expr_strip.replace("^", "**"),
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

    try:
        transformations = standard_transformations + (
            implicit_multiplication_application,
        )
        result = parse_expr(clean, local_dict=ns, transformations=transformations)
        # PARI's internal representation of polynomials is always expanded;
        # mirror that so e.g. `pari (x-3)*(x+3)` returns `x^2 - 9`.
        if isinstance(result, sympy.Expr):
            result = sympy.expand(result)
        return _format_pari_result(result)
    except Exception:
        return expr
