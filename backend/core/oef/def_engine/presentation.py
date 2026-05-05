"""Post-render HTML cleanup for KaTeX-friendly inline math.

WIMS authors open inline math with ``\\(`` but close with a plain ``)``;
KaTeX requires ``\\)``. ``_close_inline_math`` walks the rendered HTML,
finds each ``\\(``, locates its balanced closing ``)`` (or pre-existing
``\\)``), and rewrites the closer. While we have the content in hand we
also push raw expressions like ``-3*x + 3 = -1*x+-5`` through
``_normalize_math_content`` (SymPy → LaTeX per side of ``=``), so they
render as ``3 - 3 x = - x - 5`` without a literal ``*``.
"""

from __future__ import annotations


def _normalize_math_content(s: str) -> str:
    """Best-effort cleanup of an inline math expression for KaTeX rendering.

    Tries to render each side of an `=` via SymPy → LaTeX (drops `*`, fixes
    `+-` → `-`, etc.). Falls back to the original on parse failure so that
    pre-formatted LaTeX (`\\frac{}{}`, `\\sqrt{}`, …) is preserved.
    """
    import sympy  # noqa: PLC0415

    if not s.strip() or "\\" in s or "{" in s or "}" in s:
        return s

    def _render_side(side: str) -> str:
        side = side.strip()
        if not side:
            return side
        try:
            return sympy.latex(sympy.sympify(side.replace("^", "**")))
        except Exception:
            return side

    parts = s.split("=")
    if all(p.strip() for p in parts) and len(parts) > 1:
        rendered = [_render_side(p) for p in parts]
        if all(r != p.strip() for r, p in zip(rendered, parts)):
            return " = ".join(rendered)
    rendered = _render_side(s)
    if rendered != s.strip():
        return rendered
    return s


def _close_inline_math(text: str) -> str:
    """Convert WIMS-style ``\\(...)`` to KaTeX ``\\(...\\)`` and clean content."""
    out: list[str] = []
    i = 0
    n = len(text)
    while i < n:
        if i + 1 < n and text[i] == "\\" and text[i + 1] == "(":
            depth = 1
            j = i + 2
            closed_proper = False
            while j < n:
                if text[j] == "\\" and j + 1 < n and text[j + 1] == ")":
                    closed_proper = True
                    break
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            if j < n and not closed_proper and depth == 0:
                content = text[i + 2 : j]
                out.append("\\(")
                out.append(_normalize_math_content(content))
                out.append("\\)")
                i = j + 1
                continue
            if closed_proper:
                content = text[i + 2 : j]
                out.append("\\(")
                out.append(_normalize_math_content(content))
                out.append("\\)")
                i = j + 2
                continue
        out.append(text[i])
        i += 1
    return "".join(out)
