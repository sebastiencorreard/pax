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

    Delegates to ``_expr_to_latex`` (implicit multiplication + evaluate=False)
    so author expressions render as written: ``sqrt(5)`` → ``\\sqrt{5}`` and
    implicit products like ``(1+sqrt(5))(1-sqrt(5))`` parse instead of leaking
    a literal ``sqrt(5)``. Crucially it does *not* simplify — collapsing that
    product to ``-4`` would give the answer away in an ecrdec-style exercise.
    Each side of an ``=`` is rendered independently. Falls back to the original
    string on parse failure so pre-formatted LaTeX (``\\frac{}{}``,
    ``\\sqrt{}``, …) is preserved.
    """
    from .cas import _expr_to_latex  # noqa: PLC0415 — lazy, avoids circular import

    if not s.strip() or "\\" in s or "{" in s or "}" in s:
        return s

    parts = s.split("=")
    if all(p.strip() for p in parts) and len(parts) > 1:
        rendered = [_expr_to_latex(p.strip()) for p in parts]
        if all(r != p.strip() for r, p in zip(rendered, parts)):
            return " = ".join(rendered)
    rendered = _expr_to_latex(s.strip())
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
            if (j < n and not closed_proper and depth == 0) or (j == n and not closed_proper):
                content = text[i + 2 : j]
                out.append("\\(")
                out.append(_normalize_math_content(content))
                out.append("\\)")
                i = j + 1 if j < n else n
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
