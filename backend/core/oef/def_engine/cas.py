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
    """sympify a Maxima/Pari arg, normalising `^` → `**`."""
    import sympy  # noqa: PLC0415

    return sympy.sympify(s.replace("^", "**"))


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
            if func_name == "cardinality" and len(args) >= 1:
                inner = args[0].strip().lstrip("{").rstrip("}")
                items = {x.strip() for x in inner.split(",") if x.strip()}
                return str(len(items))
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
    """Convert a SymPy output string to LaTeX notation for display."""
    import sympy  # noqa: PLC0415

    try:
        return sympy.latex(sympy.sympify(expr.replace("^", "**")))
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


def _pari_vector(*args):
    return list(args)


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
    "isprime": _pari_isprime,
    "subst": _pari_subst,
    "matrix": _pari_matrix,
    "vector": _pari_vector,
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
    if isinstance(result, (list, tuple)):
        return ",".join(_format_pari_result(x) for x in result)
    return str(result)


# Wraps standalone integer literals so `/` between them produces a Rational
# (PARI semantics), not a float.
_INT_LITERAL_RE = re.compile(r"(?<![\w.])(\d+)(?!\.\d|\w)")


def _call_pari(expr: str) -> str:
    """Evaluate a PARI/GP-style expression via Python.

    Unknown identifiers are auto-bound to SymPy symbols, so polynomial
    expressions like ``polcoeff(x^2 + 3*x + 2, 1)`` evaluate symbolically.
    Integer literals are wrapped as ``sympy.Integer`` so ``3/4`` becomes the
    Rational 3/4 rather than the float 0.75.
    """
    import sympy  # noqa: PLC0415

    clean = expr.strip().rstrip(";").strip()
    m = re.match(r"^print\s*\((.+)\)$", clean, re.DOTALL)
    if m:
        clean = m.group(1).strip()
    clean = clean.replace("^", "**")
    clean = _INT_LITERAL_RE.sub(r"_I(\1)", clean)

    ns: dict = dict(_MATH_NS)
    ns.update(_PARI_HELPERS)
    ns["_I"] = sympy.Integer
    for ident in set(re.findall(r"[a-zA-Z_]\w*", clean)):
        if ident not in ns and ident not in _PYTHON_KEYWORDS:
            ns[ident] = sympy.Symbol(ident)

    try:
        result = eval(clean, ns)  # noqa: S307
        return _format_pari_result(result)
    except Exception:
        return expr
