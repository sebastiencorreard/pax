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

import re


# Decimal dot between two digits (a number like 1.21 / 0.3). Used to localise
# displayed numbers to the exercise language's separator.
_DECIMAL_DOT_RE = re.compile(r"(?<=\d)\.(?=\d)")
# A *real* HTML tag (starts with a letter or "/"), so a math "<"/">" (e.g.
# "\(x<3\)") is never mistaken for a tag and split apart.
_HTML_TAG_RE = re.compile(r"(<[/!]?[A-Za-z][^>]*>)")


# Inline / display math spans. The matrix conversion must stay scoped to math
# (where WIMS' ``[a,b;c,d]`` notation lives) — never plain text/HTML brackets.
_MATH_SPAN_RE = re.compile(r"\\\((.*?)\\\)|\\\[(.*?)\\\]", re.DOTALL)


def _matrix_close(s: str, start: int, close: str) -> int:
    """Index of the nesting-aware match for ``close`` from ``start``, or -1.

    Mirrors WIMS' ``liblines.c:find_matching`` so ``;`` / ``,`` nested in inner
    ()/[]/{} are never mistaken for matrix separators.
    """
    paren = brak = brace = 0
    for i in range(start, len(s)):
        ch = s[i]
        if ch == "[":
            brak += 1
        elif ch == "]":
            brak -= 1
        elif ch == "(":
            paren += 1
        elif ch == ")":
            paren -= 1
        elif ch == "{":
            brace += 1
        elif ch == "}":
            brace -= 1
        else:
            continue
        if paren < 0 or brak < 0 or brace < 0:
            if ch == close and paren <= 0 and brak <= 0 and brace <= 0:
                return i
            return -1
    return -1


def _split_top_level(s: str, sep: str) -> list[str]:
    """Split ``s`` on ``sep`` only at bracket depth 0."""
    parts: list[str] = []
    paren = brak = brace = 0
    start = 0
    for i, ch in enumerate(s):
        if ch == "(":
            paren += 1
        elif ch == ")":
            paren -= 1
        elif ch == "[":
            brak += 1
        elif ch == "]":
            brak -= 1
        elif ch == "{":
            brace += 1
        elif ch == "}":
            brace -= 1
        elif ch == sep and paren == 0 and brak == 0 and brace == 0:
            parts.append(s[start:i])
            start = i + 1
    parts.append(s[start:])
    return parts


def _maybe_pmatrix(span: str) -> str:
    """Turn a *standalone* ``[a,b;c,d]`` bracket into a LaTeX ``pmatrix``.

    Only a bracket that is the **entire** (trimmed) content of the math span is a
    vector/matrix — ``\\([7;5]\\)`` (column vector, quizz 1216 colinéaires). A
    bracket embedded in a larger expression is interval / list / delimiter
    notation and must render literally: ``\\(x \\in [2;5]\\)`` (French interval,
    quizz 1222), ``\\left[ x_1,x_2 \\right]`` (2nddegre). This matches the web
    math renderer (MathJax/KaTeX), which never reads ``[a;b]`` as a matrix —
    WIMS' ``[…]``→matrix rule lives only in the legacy GIF path (texmath.c).

    A bracket is a matrix iff it then carries a top-level ``;`` (rows) or ``,``
    (columns).
    """
    s = span.strip()
    if not (s.startswith("[") and s.endswith("]")):
        return span
    # The first "[" must close on the final "]" (a single group, not "[a][b]").
    if _matrix_close(s, 1, "]") != len(s) - 1:
        return span
    inner = s[1:-1]
    rows = _split_top_level(inner, ";")
    if len(rows) <= 1 and len(_split_top_level(inner, ",")) <= 1:
        return span
    body = r" \\ ".join(
        " & ".join(_maybe_pmatrix(c.strip()) for c in _split_top_level(row, ","))
        for row in rows
    )
    return r"\begin{pmatrix}" + body + r"\end{pmatrix}"


def wims_matrices_to_latex(text: str) -> str:
    """Rewrite WIMS matrix-bracket notation to ``pmatrix`` inside math spans.

    Runs in the backend *before* ``localize_decimals`` so the structural
    ``,`` / ``;`` separators are consumed while numbers are still dot-decimal —
    otherwise a localised ``1,2`` decimal would be mistaken for two columns.
    Only a standalone bracket is converted (see :func:`_maybe_pmatrix`).
    """
    if "[" not in text:
        return text

    def repl(m: re.Match) -> str:
        if m.group(1) is not None:
            return "\\(" + _maybe_pmatrix(m.group(1)) + "\\)"
        return "\\[" + _maybe_pmatrix(m.group(2)) + "\\]"

    return _MATH_SPAN_RE.sub(repl, text)


def localize_decimals(text: str, lang: str | None = None) -> str:
    """In a comma-decimal locale, render ``1.21`` as ``1,21``.

    Converts the decimal dot of every ``digit.digit`` to the locale's separator,
    but only in *text* — never inside an HTML tag's attributes (e.g. an image
    ``src`` or a ``data-w``). Dots inside ``\\(…\\)`` math are converted too
    (they're plain text at this stage; KaTeX renders them later), so
    ``\\(\\sqrt{0.3}\\)`` becomes ``\\(\\sqrt{0,3}\\)``.
    """
    from ..i18n import uses_comma_decimal  # noqa: PLC0415

    if "." not in text or not uses_comma_decimal(lang):
        return text
    parts = _HTML_TAG_RE.split(text)
    for i, part in enumerate(parts):
        if not _HTML_TAG_RE.fullmatch(part):
            parts[i] = _DECIMAL_DOT_RE.sub(",", part)
    return "".join(parts)


def _wrap_katex_exponents(s: str) -> str:
    """Brace multi-character exponents so KaTeX raises the whole token.

    WIMS lets ``^`` grab a whole number or parenthesised group; KaTeX only
    raises the next single token, so ``10^27`` → ``10²7``. We rewrite
    ``10^(27)`` → ``10^{27}`` (parens dropped) and ``10^27`` → ``10^{27}``.
    Single-character exponents (``x^2``) and already-braced ones (``^{…}``)
    are left untouched.
    """
    s = re.sub(r"\^\(([^()]+)\)", r"^{\1}", s)
    s = re.sub(r"\^(-?\d{2,}|-\d)", r"^{\1}", s)
    return s


def _positions_virgule_decimale(s: str) -> list[int]:
    """Index des virgules décimales de ``s`` : entre deux chiffres, **hors**
    de toute parenthèse, crochet ou accolade.

    La profondeur fait toute la différence : `C = 6,6` porte un nombre, quand
    `A = (1, 2)` porte un couple de coordonnées et `f(a,b)` deux arguments.
    """
    positions: list[int] = []
    depth = 0
    for i, ch in enumerate(s):
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif (
            ch == ","
            and depth == 0
            and i and s[i - 1].isdigit()
            and i + 1 < len(s) and s[i + 1].isdigit()
        ):
            positions.append(i)
    return positions


def _virgule_decimale_au_sommet(s: str) -> bool:
    return bool(_positions_virgule_decimale(s))


def _remplacer_au_sommet(s: str) -> str:
    """``s`` avec ses seules virgules décimales de premier niveau en points."""
    out = list(s)
    for i in _positions_virgule_decimale(s):
        out[i] = "."
    return "".join(out)


def _normalize_math_content(s: str, lang: str | None = None) -> str:
    """Best-effort cleanup of an inline math expression for KaTeX rendering.

    Delegates to ``_expr_to_latex`` (implicit multiplication + evaluate=False)
    so author expressions render as written: ``sqrt(5)`` → ``\\sqrt{5}`` and
    implicit products like ``(1+sqrt(5))(1-sqrt(5))`` parse instead of leaking
    a literal ``sqrt(5)``. Crucially it does *not* simplify — collapsing that
    product to ``-4`` would give the answer away in an ecrdec-style exercise.
    Each side of an ``=`` is rendered independently. Falls back to the original
    string on parse failure so pre-formatted LaTeX (``\\frac{}{}``,
    ``\\sqrt{}``, …) is preserved.

    ``lang`` drives the decimal separator (see ``core/oef/i18n.py``): a
    standalone decimal number renders with the locale's separator (``3.93`` →
    ``3,93`` in comma-decimal locales) and is *never* fed to SymPy — otherwise
    ``sympify("3,93")`` reads the comma as a tuple separator and emits
    ``\\left( 3, \\  93\\right)``.
    """
    from .cas import _expr_to_latex  # noqa: PLC0415 — lazy, avoids circular import
    from ..i18n import uses_comma_decimal  # noqa: PLC0415

    # WIMS colours inline math with `\special{color=NAME}` — a TeX colour
    # *switch* applying from that point to the end of the group (deve1 solution:
    # `\(\special{color=green} -4 \special{color=black} (…)\)`). KaTeX spells the
    # same switch `\color{NAME}` (named CSS colours render fine). Translate first,
    # before the backslash/brace bail below — coloured content always has both,
    # so it would otherwise leak the raw `\special{…}` and break KaTeX.
    s = re.sub(r"\\special\s*\{\s*color\s*=\s*([^}]+?)\s*\}", r"\\color{\1}", s)

    # WIMS writes interval brackets as `\lbracket` / `\rbracket` (e.g.
    # `\(\lbracket1;2\rbracket\)` — balayage1), which KaTeX doesn't know → red
    # error. Map to the valid `\lbrack` / `\rbrack` (NOT literal `[` / `]`):
    # a literal `[…;…]` would then be mistaken by `wims_matrices_to_latex`
    # /`_maybe_pmatrix` for a column vector and stacked vertically, whereas an
    # interval must stay inline `[1;2]`. Matching the long form leaves the short
    # `\lbrack`/`\rbrack` untouched. Before the backslash bail below.
    s = s.replace(r"\lbracket", r"\lbrack ").replace(r"\rbracket", r"\rbrack ")

    # WIMS lets `^` grab a whole number or parenthesised group (`10^27`,
    # `10^(27)`), but KaTeX only raises the next single token — so `10^27`
    # renders as `10²7`. Brace multi-character exponents so KaTeX raises the
    # whole thing. Done *before* the backslash/brace bail so it also fixes
    # content like `85 \times 10^27` that skips the CAS path below.
    s = _wrap_katex_exponents(s)

    # WIMS scientific notation often juxtaposes mantissa and power of ten with a
    # bare space (`5 10^2`, from `\c4 10^\m4`); KaTeX collapses that space so it
    # reads `510^2`. Make the implied product explicit — matching the corpus'
    # usual `\times 10^` form. Done before the brace bail below so it also fixes
    # content already braced into `10^{-2}` by _wrap_katex_exponents.
    s = re.sub(r"(\d)\s+(10\^)", r"\1 \\times \2", s)

    if not s.strip() or "\\" in s or "{" in s or "}" in s:
        return s

    # HTML entities (`&le;`, `&infin;`, `&#93;`, …) are display symbols the
    # author embedded in the math span — e.g. `\(f(x)&le; 2\)`. SymPy can't
    # parse them and would mangle the surrounding expression (`f(x)` → `f x`),
    # so leave the span untouched: the frontend KaTeX layer decodes the entity
    # to its LaTeX command (`\le`) at display time.
    if re.search(r"&[A-Za-z]+;|&#x?[0-9A-Fa-f]+;", s):
        return s

    # WIMS inline math uses bare relation *words* — e.g. `\(I in [EG]\)` for set
    # membership (rendered ``I ∈ [EG]``). SymPy can't parse these, so map the
    # known ones to their LaTeX command and skip the CAS path. The lookbehind/
    # lookahead keep the match to a *standalone* token so substrings of real
    # identifiers (`sin`, `min`, `index`) are left untouched.
    _word_ops = {"in": r"\in", "notin": r"\notin"}
    _alts = "|".join(sorted(_word_ops, key=len, reverse=True))
    _op_pat = re.compile(rf"(?<![A-Za-z\\])({_alts})(?![A-Za-z])")
    if _op_pat.search(s):
        return _op_pat.sub(lambda m: _word_ops[m.group(1)], s)

    # A standalone decimal number (comma or dot): render it directly, never via
    # SymPy — otherwise the comma is mistaken for a tuple/list separator. In a
    # comma-decimal locale we also normalise a dot to a comma (covers exercises
    # whose author didn't `!replace . by ,`); in a dot locale the token is left
    # exactly as authored.
    num = s.strip()
    if re.fullmatch(r"-?\d+[.,]\d+", num):
        return num.replace(".", ",") if uses_comma_decimal(lang) else num

    # A bare word (units/labels like `min`, `cm`, `max`) is not a CAS
    # expression. SymPy would resolve `min`/`max` to the Min/Max functions
    # (`\operatorname{Min}`, capitalised) and split `cm` into `c m`. WIMS renders
    # such a word as upright normal text, so wrap it in `\text{}`. A single
    # letter, though, is a variable (`\(x\)`) — keep it italic.
    word = s.strip()
    if re.fullmatch(r"[A-Za-z]+", word):
        return word if len(word) == 1 else rf"\text{{{word}}}"

    # Une virgule **entre deux chiffres** est un séparateur décimal dans ces
    # locales, et le CAS n'a aucun moyen de le savoir : il y lit un séparateur
    # de tuple, et — c'est le piège — il y **réussit**. `\(C = 6,6\)`
    # ressortait `C = \left( 6, \  6\right)`. Le garde-fou du nombre isolé,
    # plus haut, ne voit que la chaîne entière et laissait passer tout ce qui
    # l'entoure ; le repli `virgule → point` de `_to_latex`, lui, ne se
    # déclenche que quand le CAS échoue — ce qui n'était pas le cas ici.
    #
    # On lui soumet donc la lecture décimale d'abord, et on ne garde le
    # résultat que s'il parse. Sinon le contenu part tel quel à KaTeX, qui
    # l'affiche correctement : ne rien convertir vaut mieux qu'une conversion
    # fausse.
    # …mais **hors parenthèses** seulement. Entre parenthèses, la même virgule
    # sépare deux coordonnées ou deux arguments : `A = (1, 2)` est un point, et
    # le confondre avec un décimal le réduisait à `(1.2)`, `A(0,5)` à `0.5 A`.
    # C'est le contexte qui tranche, comme dans la branche `texmath` — la
    # profondeur zéro, et rien d'autre.
    if uses_comma_decimal(lang) and _virgule_decimale_au_sommet(s):
        pointe = _remplacer_au_sommet(s)
        parts_p = pointe.split("=")
        if all(p.strip() for p in parts_p) and len(parts_p) > 1:
            rendus = [_expr_to_latex(p.strip()) for p in parts_p]
            if all(r != p.strip() for r, p in zip(rendus, parts_p)):
                return " = ".join(rendus)
        rendu = _expr_to_latex(pointe.strip())
        return rendu if rendu != pointe.strip() else s

    def _to_latex(expr: str) -> str:
        # A single letter immediately followed by ``(`` is function-application
        # notation — ``f(x)``, ``g(t)`` — not implicit multiplication. SymPy's
        # implicit-mult transform would read ``f(x)`` as ``f*x`` and drop the
        # parens (``f x``); telling ``_expr_to_latex`` to treat those letters as
        # functions keeps ``f(x)`` intact (so e.g. ``\(f(x)< 2\)`` renders right).
        funcs = set(re.findall(r"(?<![A-Za-z0-9_])([A-Za-z])(?=\()", expr))
        # `expr` is already stripped; _expr_to_latex returns it unchanged on a
        # parse failure. French exercises write decimals with a comma
        # (``sqrt(0,01)/2``) which SymPy can't parse — retry once with the
        # digit,digit commas turned into dots, but only adopt that reading if
        # it actually parses, so ``f(a,b)`` (comma = separator) is untouched.
        out = _expr_to_latex(expr, funcs)
        if out != expr:
            return out
        alt = re.sub(r"(?<=\d),(?=\d)", ".", expr)
        if alt != expr:
            alt_out = _expr_to_latex(alt, funcs)
            if alt_out != alt:
                return alt_out
        return out

    parts = s.split("=")
    if all(p.strip() for p in parts) and len(parts) > 1:
        rendered = [_to_latex(p.strip()) for p in parts]
        if all(r != p.strip() for r, p in zip(rendered, parts)):
            return " = ".join(rendered)
    rendered = _to_latex(s.strip())
    if rendered != s.strip():
        return rendered
    return s


_MATH_BLOCK_RE = re.compile(r"<math[\s>]")


def _close_inline_math(text: str, lang: str | None = None) -> str:
    """Convert WIMS-style ``\\(...)`` to KaTeX ``\\(...\\)`` and clean content.

    ``lang`` is forwarded to :func:`_normalize_math_content` for locale-aware
    decimal-separator rendering.
    """
    out: list[str] = []
    i = 0
    n = len(text)
    while i < n:
        # Copy a native MathML ``<math>…</math>`` block verbatim. Its ``\\(…\\)``
        # spans are already finalised by ``_mathmlinput_inline`` (and the browser
        # KaTeX-renders them); re-scanning them here is pointless and risks
        # mangling an already-closed span like ``\\()\\)`` (a mathmlinput cell's
        # trailing paren). MathML doesn't nest, so the next ``</math>`` closes it.
        if text[i] == "<" and _MATH_BLOCK_RE.match(text, i):
            end = text.find("</math>", i)
            if end != -1:
                end += len("</math>")
                out.append(text[i:end])
                i = end
                continue
        # A "\\(" (escaped backslash before the paren) is NOT an inline-math
        # opener — it's a literal backslash, e.g. a JSON-escaped "\\(" inside a
        # widget's data-config attribute. Treating it as math would shred that
        # structured data (the correspond table in cof).
        if (
            i + 1 < n
            and text[i] == "\\"
            and text[i + 1] == "("
            and not (i > 0 and text[i - 1] == "\\")
        ):
            # Find the closer the way WIMS does (lines.c:output0 →
            # find_matching): the math ends at the first ``)`` that drives the
            # paren depth below zero — the first *unmatched* ``)`` — with ``[]``
            # / ``{}`` balanced. This closes ``\(K) sont (5;10)`` right after the
            # ``K`` (instead of swallowing the trailing ``) sont (5;10`` like a
            # naive "last ``)``" rule did — cercle1). An explicit ``\)`` closes
            # too. PAX safety nets, because PAX interleaves HTML widgets in math
            # where WIMS uses separate !insmath calls: an HTML tag or the next
            # ``\(`` is a hard boundary; if no balanced ``)`` is found before it,
            # fall back to the last plain ``)`` (covers unbalanced embed-in-math
            # fragments). A boundary ``<`` is one *starting a tag*
            # (``<[/!]?[A-Za-z]``), not the ``<`` of an inequality ``\(x<3\)``.
            j = i + 2
            paren = brak = brace = 0
            last_paren = -1  # last plain ')' seen (fallback)
            content_end = -1  # where the math content stops
            advance = -1      # where to resume scanning after the span
            # Premier ``)`` non apparié — le closer de `find_matching`. On le
            # mémorise au lieu de s'arrêter dessus : un ``\)`` explicite avant
            # la prochaine frontière le coiffe, parce qu'il vient du moteur
            # lui-même. C'est l'idempotence de la passe. `signeprod2` fait
            # compléter `( … ) × (+34) = -1564` : son `.def` extrait les deux
            # parenthèses d'un `val14=()` par `!char 1`/`!char 2`, si bien que
            # le `!insmath` suivant vaut `46 ) \times (+34) = -1564`. Ce ``)``
            # est du contenu, et le span est déjà fermé — s'arrêter là coupait
            # la formule après `46` et laissait le reste en texte brut.
            first_unmatched = -1
            while j < n:
                c = text[j]
                if c == "\\" and j + 1 < n and text[j + 1] == ")":
                    content_end, advance = j, j + 2  # explicit \)
                    break
                if c == "\\" and j + 1 < n and text[j + 1] == "(":
                    break  # next math span opens — hard boundary
                if c == "<" and j + 1 < n and (text[j + 1] in "/!" or text[j + 1].isalpha()):
                    break  # HTML tag (embed marker) — hard boundary
                if c == "(":
                    paren += 1
                elif c == ")":
                    last_paren = j
                    paren -= 1
                    # Candidat closer, retenu mais pas suivi tout de suite (cf.
                    # `first_unmatched` plus haut). Un contenu vide le
                    # disqualifie d'emblée : `deve7` produit `\()^2 + 2\times (\)`
                    # et le `)` de tête y est du contenu, pas une fermeture.
                    if (
                        first_unmatched < 0
                        and paren < 0 and brak <= 0 and brace <= 0
                        and text[i + 2 : j].strip()
                    ):
                        first_unmatched = j
                elif c == "[":
                    brak += 1
                elif c == "]":
                    brak -= 1
                elif c == "{":
                    brace += 1
                elif c == "}":
                    brace -= 1
                j += 1
            if content_end < 0 and first_unmatched >= 0:
                # Pas de `\)` avant la frontière : le closer de `find_matching`
                # reprend la main, comme chez WIMS.
                content_end, advance = first_unmatched, first_unmatched + 1
            if content_end < 0:
                # Boundary or EOL without a balanced closer.
                if last_paren >= 0:
                    content_end, advance = last_paren, last_paren + 1
                elif j == n:
                    content_end, advance = n, n  # unclosed to EOL — wrap the rest
                else:
                    out.append(text[i])  # boundary, no ')' → not math, "\(" literal
                    i += 1
                    continue
            out.append("\\(")
            out.append(_normalize_math_content(text[i + 2 : content_end], lang))
            out.append("\\)")
            i = advance
            continue
        out.append(text[i])
        i += 1
    return "".join(out)
