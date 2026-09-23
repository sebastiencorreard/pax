"""Flydraw → SVG renderer.

WIMS describes graphs with a small vector primitive language called *flydraw*
(implemented in C in WIMS as `wims/src/Flydraw/flydraw.c`). Each instruction
is one line of the form ``<command> arg1,arg2,...``. We re-implement enough
of those primitives to draw the number-line / inequality images used by
algebra exercises.

Output is an SVG string; ``flydraw_to_data_uri`` returns a
``data:image/svg+xml;base64,…`` URL for direct embedding in ``<img src=…>``.

Coordinate system: flydraw uses math-style (y-up); SVG is screen-style
(y-down). We convert each primitive's math-y to SVG-y inside the handlers
rather than relying on a group transform — keeps text right-side-up without
counter-transforms.
"""

from __future__ import annotations

import hashlib
import logging
import math
import re
import sys
from dataclasses import dataclass, field

import contextvars

from .safe_math import entree_math_sure

# Les variables d'une figure (`s=0.5`, `a1=3`) : `obj_main` range dans `vartab`
# toute ligne dont le premier mot fait une lettre, ou une lettre et un chiffre,
# et l'évaluateur les lit ensuite. Propres au rendu en cours, d'où une
# `ContextVar` que `_num` consulte.
_VARIABLES: contextvars.ContextVar[dict[str, float] | None] = contextvars.ContextVar(
    "flydraw_variables", default=None
)

_log = logging.getLogger("pax.flydraw")
_logged_unhandled: set[str] = set()


def _log_unhandled_cmd(cmd: str, args: str) -> None:
    """Log a flydraw command we don't implement. Dedup by name so the log
    stays readable: each command shows up once per process lifetime."""
    if cmd in _logged_unhandled:
        return
    _logged_unhandled.add(cmd)
    sample = (args or "").strip().replace("\n", " ")[:80]
    msg = f"[FLYDRAW-UNHANDLED] {cmd} {sample}"
    _log.warning(msg)
    # Fallback for environments where the logger isn't configured: also
    # write to stderr so docker compose logs surface it.
    print(msg, file=sys.stderr, flush=True)


# ── Color table (subset of wims/src/Flydraw/colors actually used in corpus) ──

# Subset of CSS / WIMS named colors covering what the corpus uses (full
# WIMS table at wims/src/Flydraw/colors has 152 entries).
_COLORS: dict[str, str] = {
    "aliceblue": "#f0f8ff",
    "aqua": "#00ffff",
    "aquamarine": "#7fffd4",
    "beige": "#f5f5dc",
    "black": "#000000",
    "blue": "#0000ff",
    "blueviolet": "#8a2be2",
    "brown": "#a52a2a",
    "burlywood": "#deb887",
    "chartreuse": "#7fff00",
    "chocolate": "#d2691e",
    "coral": "#ff7f50",
    "crimson": "#dc143c",
    "cyan": "#00ffff",
    "darkblue": "#00008b",
    "darkcyan": "#008b8b",
    "darkgray": "#a9a9a9",
    "darkgreen": "#006400",
    "darkgrey": "#a9a9a9",
    "darkmagenta": "#8b008b",
    "darkorange": "#ff8c00",
    "darkred": "#8b0000",
    "deeppink": "#ff1493",
    "fuchsia": "#ff00ff",
    "gold": "#ffd700",
    "gray": "#bebebe",
    "green": "#008000",
    "greenyellow": "#adff2f",
    "grey": "#bebebe",
    "indigo": "#4b0082",
    "khaki": "#f0e68c",
    "lavender": "#e6e6fa",
    "lightblue": "#add8e6",
    "lightcoral": "#f08080",
    "lightgray": "#d3d3d3",
    "lightgreen": "#90ee90",
    "lightgrey": "#d3d3d3",
    "lightpink": "#ffb6c1",
    "lightyellow": "#ffffe0",
    "lime": "#00ff00",
    "magenta": "#ff00ff",
    "maroon": "#800000",
    "navy": "#000080",
    "olive": "#808000",
    "orange": "#ffa500",
    "orangered": "#ff4500",
    "orchid": "#da70d6",
    "pink": "#ffc0cb",
    "plum": "#dda0dd",
    "purple": "#800080",
    "red": "#ff0000",
    "rosybrown": "#bc8f8f",
    "royalblue": "#4169e1",
    "salmon": "#fa8072",
    "sandybrown": "#f4a460",
    "seagreen": "#2e8b57",
    "seashell": "#fff5ee",
    "sienna": "#a0522d",
    "silver": "#c0c0c0",
    "skyblue": "#87ceeb",
    "slateblue": "#6a5acd",
    "slategray": "#708090",
    "slategrey": "#708090",
    "steelblue": "#4682b4",
    "tan": "#d2b48c",
    "teal": "#008080",
    "tomato": "#ff6347",
    "turquoise": "#40e0d0",
    "violet": "#ee82ee",
    "white": "#ffffff",
    "yellow": "#ffff00",
    "yellowgreen": "#9acd32",
}

# WIMS flydraw uses GD built-in bitmap fonts; these px values approximate each
# font's glyph height: gdFontSmall ≈ 12, gdFontMediumBold ≈ 13, gdFontLarge ≈ 16,
# gdFontGiant ≈ 15. PAX previously mapped `giant` to 22, making labels like the
# "(d)" line tag noticeably larger than WIMS.
_FONT_SIZES: dict[str, float] = {
    "small": 10,
    "medium": 12,
    "large": 16,
    "giant": 16,
}


def _color(name: str) -> str:
    name = (name or "").strip().lower()
    if not name:
        return "#000000"
    if name.startswith("#"):
        return name
    return _COLORS.get(name, "#000000")


def _font_size(s: str) -> float:
    s = (s or "").strip().lower()
    if s in _FONT_SIZES:
        return _FONT_SIZES[s]
    try:
        return float(s)
    except ValueError:
        return _FONT_SIZES["medium"]


def _font_weight(s: str) -> str:
    # WIMS' GD font table maps only `medium` to a *bold* face (gdFontMediumBold);
    # tiny/small/large/giant/huge are regular. So bold the `medium` labels (e.g.
    # axis numbers in quizz 1216) but leave `large`/`giant` (axis numbers in
    # 0406, the "(d)" tag) at normal weight.
    return "bold" if (s or "").strip().lower() == "medium" else "normal"


import math as _math  # noqa: E402

_NUM_NS: dict = {
    "__builtins__": {},
    "sqrt": _math.sqrt,
    "sin": _math.sin,
    "cos": _math.cos,
    "tan": _math.tan,
    "asin": _math.asin,
    "acos": _math.acos,
    "atan": _math.atan,
    "atan2": _math.atan2,
    "exp": _math.exp,
    "log": _math.log,
    "floor": _math.floor,
    "ceil": _math.ceil,
    "round": round,
    "abs": abs,
    "min": min,
    "max": max,
    "pi": _math.pi,
    "e": _math.e,
}

# Allow digits, whitespace, basic arithmetic, and identifier chars (for
# the function names / constants in `_NUM_NS`). The eval still runs in a
# restricted namespace, so identifier coverage is bounded by `_NUM_NS`.
_ARITH_RE = re.compile(r"^[\w\s+\-*/.,()]+$")


def _num(s: str) -> float:
    """Parse a flydraw numeric arg, evaluating simple arithmetic.

    WIMS slib scripts emit args like ``-15-2`` or ``10*sqrt(3)`` or
    ``cos(60*pi/180)`` (after WIMS variable substitution); the C flydraw
    binary evaluates these via its expression parser. We do the same in a
    restricted ``eval`` namespace covering basic trig/exp + ``pi``.
    """
    s = s.strip()
    if not s:
        return 0.0
    # A coordinate may arrive wrapped in WIMS inline-math delimiters, e.g.
    # repgraphint reuses `\(-6)` (its display form) as the x of a bracket and
    # label. Strip `\(` … `)`/`\)` so it parses as the number, not 0 (which
    # collapsed every bound to the axis centre).
    if s.startswith("\\("):
        inner = s[2:]
        if inner.endswith("\\)"):
            inner = inner[:-2]
        elif inner.endswith(")"):
            inner = inner[:-1]
        s = inner.strip()
        if not s:
            return 0.0
    try:
        return float(s)
    except ValueError:
        pass
    # Un argument de figure peut contenir la réponse d'un élève : `oefrelat`
    # trace `arc 3.6,($val9+\rep)/…` dans son corrigé. La garde des autres
    # `eval` du moteur (`safe_math`) vaut ici aussi — aucun nombre ni aucune
    # expression de figure n'a besoin d'un dunder ou d'un accès par attribut.
    if not entree_math_sure(s):
        return 0.0
    if _ARITH_RE.match(s):
        variables = _VARIABLES.get()
        espace = {**_NUM_NS, **variables} if variables else _NUM_NS
        try:
            return float(eval(s, espace))  # noqa: S307
        except Exception:
            # WIMS' flydraw parser tolerates a dangling trailing operator — some
            # generated coords look like "X +" (a tick's x2 in oefcalittaire1
            # branch 5). Evaluate them as just "X" instead of collapsing to 0
            # (which dragged the tick off to the axis as a stray diagonal).
            stripped = s.rstrip(" \t+-*/")
            if stripped and stripped != s:
                try:
                    return float(eval(stripped, espace))  # noqa: S307
                except Exception:
                    pass
            return 0.0
    return 0.0


def _split_args(arg_str: str) -> list[str]:
    """Split a flydraw command's argument list on top-level commas only.

    A comma inside a function call — e.g. `min(a,b)` / `max(a,b)`, which WIMS
    uses to clamp a dimension arrow — must stay within one argument. Splitting
    on every comma mis-aligned all following coordinates, turning a horizontal
    arrow into a stray diagonal line (oefcalittaire1 branches 4/5).
    """
    args: list[str] = []
    depth = 0
    start = 0
    for i, ch in enumerate(arg_str):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth = max(0, depth - 1)
        elif ch == "," and depth == 0:
            args.append(arg_str[start:i].rstrip())
            start = i + 1
    args.append(arg_str[start:].rstrip())
    return args


# ── Renderer state ────────────────────────────────────────────────────────────


_Pt = tuple[float, float]
_Seg = tuple[_Pt, _Pt]


@dataclass
class _State:
    """Renderer state.

    The output SVG uses pixel coordinates (``viewBox="0 0 width height"``)
    so that ``font-size``, arrow head sizes, and ``stroke-width`` stay in
    pixels regardless of the math range. Math coordinates are projected to
    pixels via :py:meth:`px` / :py:meth:`py`.

    ``segments`` records every line emitted (in math coordinates) so that
    ``flood`` can find the polygon enclosing its target point.
    """

    xmin: float = -5.0
    xmax: float = 5.0
    ymin: float = -5.0
    ymax: float = 5.0
    # Domaine du paramètre d'un tracé paramétrique, et son échantillonnage.
    # Valeurs par défaut de `flydraw.c:38` (`tstart`, `tend`, `tstep`).
    tmin: float = 0.0
    tmax: float = 1.0
    tstep: int = 100
    linewidth: float = 1.0
    crosshairsize: float = 4.0  # WIMS global `width2` default (full × extent = 2·this)
    # Font state for string / stringup (separate from text which takes a font arg).
    # CSS-shorthand parts; defaults match WIMS (12px sans-serif).
    font_size: str = "12px"
    font_family: str = "sans-serif"
    font_style: str = ""  # e.g. "italic"
    font_weight: str = ""  # e.g. "bold"
    elements: list[str] = field(default_factory=list)
    segments: list[_Seg] = field(default_factory=list)
    # Closed polygons actually drawn (polygon/fpolygon/triangle), in math
    # coords — `flood`/`fill` fills the smallest one containing its point.
    polygons: list[list[_Pt]] = field(default_factory=list)
    # Outline ellipses/circles in math coords (cx, cy, rx, ry) — used by
    # `flood`/`fill` as the rim boundary of a pie/wheel sector.
    circles: list[tuple[float, float, float, float]] = field(default_factory=list)
    width: int = 300
    height: int = 80
    # Exercise module directory (e.g. ressources/H3/math/quizz.fr) — lets
    # `copy <file>` resolve a module-local image (images/<file>) in addition to
    # the shared WIMS gifs tree.
    base_dir: str | None = None
    # Raw values stashed by `boxplotdata` for use by the next `boxplot`.
    boxplotdata: list[float] = field(default_factory=list)
    # La transformation que `scale()` (`flylines.c:151`) applique à **tout
    # point** d'un objet avant de le projeter : `affine`, `linear`, `rotation`
    # posent `matrix` (`objects.c:1482-1535`), `translation` le vecteur. Les
    # tailles — rayons, côté d'un `square`, texte — n'y passent pas, et c'est
    # pourquoi elle s'applique aux points parsés (`tr`) plutôt qu'à l'image.
    matrix: tuple[float, float, float, float] = (1.0, 0.0, 0.0, 1.0)
    transform: bool = False
    transx: float = 0.0
    transy: float = 0.0

    def lin(self, x: float, y: float) -> tuple[float, float]:
        """La partie linéaire seule — `scale2` pour un vecteur (`parallel`)."""
        if not self.transform:
            return x, y
        a, b, c, d = self.matrix
        return a * x + b * y, c * x + d * y

    def tr(self, x: float, y: float) -> tuple[float, float]:
        """Un point transformé, en coordonnées du repère (`scale_buf`)."""
        x, y = self.lin(x, y)
        return x + self.transx, y + self.transy

    def tr_flat(self, coords: list[float]) -> list[float]:
        """`x1,y1,x2,y2,…` transformés deux à deux ; un reste impair est gardé."""
        out = list(coords)
        for i in range(0, len(out) - 1, 2):
            out[i], out[i + 1] = self.tr(out[i], out[i + 1])
        return out

    def px(self, math_x: float) -> float:
        denom = self.xmax - self.xmin or 1.0
        return (math_x - self.xmin) * self.width / denom

    def py(self, math_y: float) -> float:
        # SVG y grows downward; flip math y (up) to screen y (down).
        denom = self.ymax - self.ymin or 1.0
        return self.height - (math_y - self.ymin) * self.height / denom


# ── Primitive handlers ────────────────────────────────────────────────────────


def _find_wims_gifs_dir() -> str | None:
    """Locate WIMS' shared gif tree (``raw/clock/120a.gif`` lives there).

    Mirrors :py:func:`_SlibMixin._find_wims_scripts_dir`: walks up from this
    file looking for either the vendored ``ressources/wims-gifs/`` mirror or
    the full ``wims/public_html/gifs/`` checkout. The first match wins.
    """
    import os as _os_local
    d = _os_local.path.dirname(_os_local.path.abspath(__file__))
    for _ in range(10):
        d = _os_local.path.dirname(d)
        if not d:
            break
        for sub in (
            _os_local.path.join("ressources", "wims-gifs"),
            _os_local.path.join("wims", "public_html", "gifs"),
        ):
            candidate = _os_local.path.join(d, sub)
            if _os_local.path.isdir(candidate):
                return candidate
        if d == "/":
            break
    return None


_WIMS_GIFS_DIR = _find_wims_gifs_dir()


def _cmd_copy(state: _State, args: list[str]) -> None:
    """``copy dx,dy,sx1,sy1,sx2,sy2,filename`` — paste a gif/png onto the canvas.

    Mirrors flydraw's ``obj_copy``: ``(dx,dy)`` is the destination in pixels;
    ``(sx1,sy1)-(sx2,sy2)`` is the source rect; all-(-1) means the full image.
    ``filename`` is resolved under WIMS' shared gifs tree (``raw/clock/120a.gif``
    et al.) and inlined as a base64 ``<image>`` so the SVG stays self-contained.
    Only the full-image case is implemented — partial source rects would need
    SVG ``<clipPath>`` for negligible benefit on the WIMS corpus.
    """
    import base64 as _base64_local
    import os as _os_local
    import posixpath as _pp_local

    if len(args) < 7:
        return
    try:
        dx = int(round(float(args[0])))
        dy = int(round(float(args[1])))
        sx1 = int(round(float(args[2])))
        sy1 = int(round(float(args[3])))
        sx2 = int(round(float(args[4])))
        sy2 = int(round(float(args[5])))
    except (ValueError, TypeError):
        return
    filename = args[6].strip()
    rel = _pp_local.normpath("/" + filename).lstrip("/")
    # Resolve module-local images (images/<file>, then <file>) first, then the
    # shared WIMS gifs tree — e.g. quizz 1128's `copy …,1128.png` (probability
    # tree skeleton) lives in the module's images/ dir, not the gifs tree.
    candidates = []
    if state.base_dir:
        candidates.append(_os_local.path.join(state.base_dir, "images", rel))
        candidates.append(_os_local.path.join(state.base_dir, rel))
    if _WIMS_GIFS_DIR:
        candidates.append(_os_local.path.join(_WIMS_GIFS_DIR, rel))
    fpath = next((p for p in candidates if _os_local.path.isfile(p)), None)
    if fpath is None:
        return
    with open(fpath, "rb") as f:
        data = f.read()
    # Detect format + width/height from header
    if data[:6] in (b"GIF87a", b"GIF89a") and len(data) >= 10:
        mime = "image/gif"
        img_w = data[6] | (data[7] << 8)
        img_h = data[8] | (data[9] << 8)
    elif data.startswith(b"\x89PNG\r\n\x1a\n") and len(data) >= 24:
        mime = "image/png"
        img_w = int.from_bytes(data[16:20], "big")
        img_h = int.from_bytes(data[20:24], "big")
    else:
        return
    if sx1 == -1 and sy1 == -1 and sx2 == -1 and sy2 == -1:
        sx1, sy1 = 0, 0
        sx2, sy2 = img_w - 1, img_h - 1
    src_w = sx2 - sx1 + 1
    src_h = sy2 - sy1 + 1
    if (sx1, sy1) != (0, 0) or (src_w, src_h) != (img_w, img_h):
        # Partial copy not implemented yet — fall back to whole-image paste.
        sx1 = sy1 = 0
        src_w, src_h = img_w, img_h
    b64 = _base64_local.b64encode(data).decode("ascii")
    # Project the destination through the coordinate system: with xrange/yrange
    # set, (dx,dy) is the image's top-left in user coords (1128: copy 0,160 with
    # yrange 0,160 → top of the canvas). In pixel mode px/py are the identity,
    # so the shared WIMS gifs (clock, …) keep pasting at raw pixel offsets.
    tdx, tdy = state.tr(dx, dy)
    x_px = state.px(tdx)
    y_px = state.py(tdy)
    state.elements.append(
        f'<image x="{x_px:.2f}" y="{y_px:.2f}" width="{src_w}" height="{src_h}" '
        f'href="data:{mime};base64,{b64}" preserveAspectRatio="none"/>'
    )


def _cmd_range(state: _State, args: list[str]) -> None:
    if len(args) >= 4:
        state.xmin = _num(args[0])
        state.xmax = _num(args[1])
        state.ymin = _num(args[2])
        state.ymax = _num(args[3])


def _cmd_linewidth(state: _State, args: list[str]) -> None:
    if args:
        try:
            state.linewidth = float(args[0])
        except ValueError:
            pass


def _cmd_segment(state: _State, args: list[str]) -> None:
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    state.segments.append(((x1, y1), (x2, y2)))
    state.elements.append(
        f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
        f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _arrow_marker(state: _State, head_len: float, color: str) -> str:
    """Emit a <marker> definition and return its ID — used by arrow variants."""
    head_id = f"ah{len(state.elements)}"
    # WIMS' 5th `arrow` arg is the arrowhead size in pixels — use it directly
    # (halving it made the heads visibly smaller than WIMS).
    head_size = max(head_len, 4)
    state.elements.append(
        f'<defs><marker id="{head_id}" viewBox="0 0 10 10" refX="10" refY="5" '
        f'markerWidth="{head_size}" markerHeight="{head_size}" '
        f'orient="auto-start-reverse" markerUnits="userSpaceOnUse">'
        f'<path d="M 0 0 L 10 5 L 0 10 z" fill="{color}" /></marker></defs>'
    )
    return head_id


def _arrow_segment(state: _State, x1: float, y1: float, x2: float, y2: float,
                   color: str, marker_end: str | None = None,
                   marker_start: str | None = None, dashed: bool = False) -> None:
    extra = ""
    if marker_end:
        extra += f' marker-end="url(#{marker_end})"'
    if marker_start:
        extra += f' marker-start="url(#{marker_start})"'
    if dashed:
        extra += ' stroke-dasharray="4,3"'
    state.elements.append(
        f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
        f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}"{extra} />'
    )


def _cmd_arrow(state: _State, args: list[str]) -> None:
    # arrow x1,y1,x2,y2,arrowhead_pixels,[color]
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head = _arrow_marker(state, head_len, color)
    _arrow_segment(state, x1, y1, x2, y2, color, marker_end=head)


def _cmd_arrow2(state: _State, args: list[str]) -> None:
    # arrow2 x1,y1,x2,y2,h,[color] — double-headed arrow (head at both ends).
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head = _arrow_marker(state, head_len, color)
    _arrow_segment(state, x1, y1, x2, y2, color,
                   marker_end=head, marker_start=head)


def _cmd_arrows(state: _State, args: list[str]) -> None:
    # arrows [color],l,x1,y1,x2,y2,x3,y3,x4,y4,... — pairs of (start,end) points
    if len(args) < 6:
        return
    color = _color(args[0])
    head_len = _num(args[1])
    head = _arrow_marker(state, head_len, color)
    coords = state.tr_flat([_num(a) for a in args[2:]])
    for i in range(0, len(coords) - 3, 4):
        x1, y1, x2, y2 = coords[i], coords[i + 1], coords[i + 2], coords[i + 3]
        _arrow_segment(state, x1, y1, x2, y2, color, marker_end=head)


def _cmd_arrows2(state: _State, args: list[str]) -> None:
    # arrows2 [color],l,x1,y1,x2,y2,... — multiple double-headed arrows.
    if len(args) < 6:
        return
    color = _color(args[0])
    head_len = _num(args[1])
    head = _arrow_marker(state, head_len, color)
    coords = state.tr_flat([_num(a) for a in args[2:]])
    for i in range(0, len(coords) - 3, 4):
        x1, y1, x2, y2 = coords[i], coords[i + 1], coords[i + 2], coords[i + 3]
        _arrow_segment(state, x1, y1, x2, y2, color,
                       marker_end=head, marker_start=head)


def _cmd_darrow(state: _State, args: list[str]) -> None:
    # darrow x1,y1,x2,y2,l,[color] — dashed arrow.
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head = _arrow_marker(state, head_len, color)
    _arrow_segment(state, x1, y1, x2, y2, color, marker_end=head, dashed=True)


def _cmd_darrow2(state: _State, args: list[str]) -> None:
    # darrow2 x1,y1,x2,y2,l,[color] — dashed double-headed arrow.
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head = _arrow_marker(state, head_len, color)
    _arrow_segment(state, x1, y1, x2, y2, color,
                   marker_end=head, marker_start=head, dashed=True)


def _cmd_halfline(state: _State, args: list[str]) -> None:
    # halfline x1,y1,x2,y2,[color] — ray starting at (x1,y1), through (x2,y2),
    # extended to the canvas edge.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    # Find where the ray (x1,y1)→(x2,y2)→∞ leaves the canvas box.
    dx, dy = x2 - x1, y2 - y1
    if dx == 0 and dy == 0:
        return
    # Walk t > 0 until we hit a boundary; clip by xmin/xmax/ymin/ymax.
    t_max = float("inf")
    if dx > 0:
        t_max = min(t_max, (state.xmax - x1) / dx)
    elif dx < 0:
        t_max = min(t_max, (state.xmin - x1) / dx)
    if dy > 0:
        t_max = min(t_max, (state.ymax - y1) / dy)
    elif dy < 0:
        t_max = min(t_max, (state.ymin - y1) / dy)
    if t_max == float("inf") or t_max <= 0:
        # Direction has no canvas exit (shouldn't happen); just draw segment.
        bx, by = x2, y2
    else:
        bx, by = x1 + dx * t_max, y1 + dy * t_max
    state.segments.append(((x1, y1), (bx, by)))
    state.elements.append(
        f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
        f'x2="{state.px(bx):.2f}" y2="{state.py(by):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_dashhalfline(state: _State, args: list[str]) -> None:
    # Dashed half-line: same geometry as halfline, but rendered dashed.
    if len(args) < 4:
        return
    # Re-use the geometry, then patch the last <line> with stroke-dasharray.
    _cmd_halfline(state, args)
    if state.elements and "<line " in state.elements[-1]:
        state.elements[-1] = state.elements[-1].replace(
            ' stroke-width="', ' stroke-dasharray="4,3" stroke-width="', 1
        )


def _cmd_square(state: _State, args: list[str]) -> None:
    # square x,y,side(px),[color] — top-left corner (x,y) in math coords,
    # side length in pixels (per WIMS doc).
    if len(args) < 3:
        return
    x, y, side = _num(args[0]), _num(args[1]), _num(args[2])
    x, y = state.tr(x, y)
    color = _color(args[3]) if len(args) > 3 else "#000000"
    x_px = state.px(x)
    y_px = state.py(y)
    state.elements.append(
        f'<rect x="{x_px:.2f}" y="{y_px:.2f}" '
        f'width="{side:.2f}" height="{side:.2f}" '
        f'fill="none" stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_fsquare(state: _State, args: list[str]) -> None:
    # fsquare x,y,side(px),[color] — filled variant of square.
    if len(args) < 3:
        return
    x, y, side = _num(args[0]), _num(args[1]), _num(args[2])
    x, y = state.tr(x, y)
    color = _color(args[3]) if len(args) > 3 else "#000000"
    x_px = state.px(x)
    y_px = state.py(y)
    state.elements.append(
        f'<rect x="{x_px:.2f}" y="{y_px:.2f}" '
        f'width="{side:.2f}" height="{side:.2f}" '
        f'fill="{color}" stroke="none" />'
    )


def _cmd_fpolygon(state: _State, args: list[str]) -> None:
    # fpolygon [color],x1,y1,x2,y2,... — filled polygon.
    if len(args) < 5:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    if len(coords) < 4 or len(coords) % 2 != 0:
        return
    pts = " ".join(
        f"{state.px(coords[i]):.2f},{state.py(coords[i + 1]):.2f}"
        for i in range(0, len(coords), 2)
    )
    state.elements.append(
        f'<polygon points="{pts}" fill="{color}" stroke="none" />'
    )


def _cmd_dpolyline(state: _State, args: list[str]) -> None:
    # dpolyline [color],x1,y1,x2,y2,... — dashed polyline.
    if len(args) < 5:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    if len(coords) < 4 or len(coords) % 2 != 0:
        return
    pts = " ".join(
        f"{state.px(coords[i]):.2f},{state.py(coords[i + 1]):.2f}"
        for i in range(0, len(coords), 2)
    )
    state.elements.append(
        f'<polyline points="{pts}" fill="none" '
        f'stroke="{color}" stroke-width="{state.linewidth}" '
        f'stroke-dasharray="4,3" />'
    )


def _cmd_parallel(state: _State, args: list[str]) -> None:
    # parallel x1,y1,x2,y2,dx,dy,n,[color] — n copies offset by (dx,dy)
    if len(args) < 7:
        return
    x1, y1, x2, y2, dx, dy = (_num(a) for a in args[:6])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    dx, dy = state.lin(dx, dy)  # `scale2` : sans la translation
    n = int(_num(args[6]))
    if n <= 0:
        return
    # Garde-fou : au-delà de la résolution de l'image, les lignes parallèles se
    # superposent en aplat — inutile de les tracer. Sans plafond, une donnée
    # corrompue en amont (ex. `slib/stat/freq` cassé gonfle `s_ymax` à 230000,
    # cf. mediane5) fait dessiner des centaines de milliers de lignes et bloque
    # le rendu plusieurs secondes. On borne au nombre de pixels + une marge.
    n = min(n, max(state.width, state.height) + 100)
    color = _color(args[7]) if len(args) > 7 else "#000000"
    for i in range(n):
        ox, oy = i * dx, i * dy
        state.segments.append(((x1 + ox, y1 + oy), (x2 + ox, y2 + oy)))
        state.elements.append(
            f'<line x1="{state.px(x1 + ox):.2f}" y1="{state.py(y1 + oy):.2f}" '
            f'x2="{state.px(x2 + ox):.2f}" y2="{state.py(y2 + oy):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )


# `MAX_SIZE` de `flydraw.h` : au-delà, `obj_size` refuse la taille.
_TAILLE_MAX = 4096


def _cmd_new(state: _State, args: list[str]) -> None:
    """`new w,h` — `obj_new` détruit l'image et en crée une de w×h.

    `insdraw..processor` écrit déjà `new <taille de l'en-tête>` avant le corps :
    un `new` dans le corps **remplace** donc cette taille. `slib/graphpaper/*`
    commence ainsi (`new $[60*xd],$[60*yd]`), `oefresistance` aussi (`new
    300,220` sous un en-tête 200×200) : l'ignorer dessinait la figure dans le
    cadre de l'en-tête, rapport d'aspect compris — déformée.

    Seul le dessin disparaît. Repère, épaisseur, transformations sont des
    globales du C, que `obj_new` ne touche pas ; le repère par défaut, en
    pixels, suit la nouvelle taille. Le cadre que le C trace en `color_frame`
    (254,254,254) est invisible, on ne le trace pas.
    """
    state.elements.clear()
    state.segments.clear()
    state.polygons.clear()
    state.circles.clear()
    if len(args) < 2:
        return
    w, h = round(_num(args[0])), round(_num(args[1]))
    if not (0 < w <= _TAILLE_MAX and 0 < h <= _TAILLE_MAX):
        return
    en_pixels = (state.xmin, state.xmax, state.ymin, state.ymax) == (0, state.width, state.height, 0)
    state.width, state.height = w, h
    if en_pixels:
        state.xmin, state.xmax, state.ymin, state.ymax = 0, w, h, 0


def _contenu_texte(brut: str) -> str:
    r"""La chaîne d'un `text`/`textup`, comme `obj_string` (`objects.c`) la lit.

    Élaguée d'abord (`find_word_start` + `strip_trailing_spaces`) : une espace
    de tête n'est pas un décalage — c'est ce qui garde les nombres d'axe sous
    leur graduation. Puis, si elle s'ouvre sur `"` et que le guillemet suivant
    la **termine**, les deux tombent et l'intérieur est gardé tel quel : c'est
    ainsi qu'un auteur obtient une espace de tête. `oefohm` et `oefresistance`
    affichaient leurs guillemets (`" R2 = 55 ohm"`).

    Les références `\nom` restées indéfinies sont retirées : WIMS les rend
    vides (`\c \unit` → « 0.4 » quand `unit` n'est pas posée). Le texte de
    flydraw n'est jamais du LaTeX, donc un `\mot` résiduel est une telle
    référence, non une commande.
    """
    contenu = brut.strip()
    cite = False
    if contenu.startswith('"') and contenu.find('"', 1) == len(contenu) - 1:
        contenu, cite = contenu[1:-1], True
    contenu = re.sub(r"\\[A-Za-z]\w*", "", contenu)
    if not cite:
        return re.sub(r"\s{2,}", " ", contenu).strip()
    # SVG replie les blancs de bord ; l'espace insécable les garde visibles.
    tete = len(contenu) - len(contenu.lstrip(" "))
    queue = len(contenu) - len(contenu.rstrip(" "))
    return "\u00a0" * tete + contenu.strip(" ") + "\u00a0" * queue


def _cmd_text(state: _State, args: list[str]) -> None:
    # text [color],x,y,size,content
    if len(args) < 5:
        return
    color = _color(args[0])
    x, y = state.tr(_num(args[1]), _num(args[2]))
    size = _font_size(args[3])
    weight = _font_weight(args[3])
    # Content may contain commas — re-join the tail
    content = _contenu_texte(",".join(args[4:]))
    state.elements.append(
        f'<text x="{state.px(x):.2f}" y="{state.py(y):.2f}" fill="{color}" '
        f'font-size="{size}" font-family="sans-serif" font-weight="{weight}" '
        f'text-anchor="start" dominant-baseline="hanging">'
        f"{_xml_escape(content)}</text>"
    )


def _cmd_textup(state: _State, args: list[str]) -> None:
    # textup [color],x,y,size,content — same args as `text`, but the string is
    # rotated 90° counter-clockwise (vertical, reading bottom-to-top — e.g. the
    # left-side length label of 0923's rectangle). SVG rotate is clockwise, so
    # 90° CCW = rotate(-90) around the anchor point.
    if len(args) < 5:
        return
    color = _color(args[0])
    x, y = state.tr(_num(args[1]), _num(args[2]))
    size = _font_size(args[3])
    weight = _font_weight(args[3])
    content = _contenu_texte(",".join(args[4:]))
    cx, cy = state.px(x), state.py(y)
    state.elements.append(
        f'<text x="{cx:.2f}" y="{cy:.2f}" fill="{color}" '
        f'font-size="{size}" font-family="sans-serif" font-weight="{weight}" '
        f'text-anchor="start" dominant-baseline="hanging" '
        f'transform="rotate(-90, {cx:.2f}, {cy:.2f})">'
        f"{_xml_escape(content)}</text>"
    )


def _ligne_infinie(state: _State, x1: float, y1: float, x2: float, y2: float,
                   color: str, dashed: bool = False) -> None:
    """La droite passant par deux points, prolongée jusqu'au cadre.

    `line_extend` (`objects.c`) étend dans les deux sens jusqu'au bord de
    l'image ; on le fait ici en coordonnées du repère, ce qui revient au même,
    l'un étant l'image affine de l'autre.
    """
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    # Deux points confondus : `line_extend` y calcule `t3 = INFINITY` puis un
    # `NaN` converti en entier — indéfini, pas une règle. PAX garde ce qu'il
    # traçait, une verticale plein cadre, plutôt que d'inventer une garde.
    if x1 == x2:
        ax, ay, bx, by = x1, state.ymin, x1, state.ymax
    elif y1 == y2:
        ax, ay, bx, by = state.xmin, y1, state.xmax, y1
    else:
        m = (y2 - y1) / (x2 - x1)
        ax, ay = state.xmin, y1 + m * (state.xmin - x1)
        bx, by = state.xmax, y1 + m * (state.xmax - x1)
        ymin, ymax = state.ymin, state.ymax
        if ay < ymin or ay > ymax:
            cible = ymin if ay < ymin else ymax
            ax, ay = x1 + (cible - y1) / m, cible
        if by < ymin or by > ymax:
            cible = ymin if by < ymin else ymax
            bx, by = x1 + (cible - y1) / m, cible
    tirets = ' stroke-dasharray="4,3"' if dashed else ""
    state.segments.append(((ax, ay), (bx, by)))
    state.elements.append(
        f'<line x1="{state.px(ax):.2f}" y1="{state.py(ay):.2f}" '
        f'x2="{state.px(bx):.2f}" y2="{state.py(by):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}"{tirets} />'
    )


def _cmd_line(state: _State, args: list[str]) -> None:
    # line x1,y1,x2,y2,[color] — la DROITE passant par les deux points
    # (`obj_fullline`), prolongée jusqu'au cadre.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    color = _color(args[4]) if len(args) > 4 else "#000000"
    _ligne_infinie(state, x1, y1, x2, y2, color)


def _cmd_fulllines(state: _State, args: list[str], dashed: bool = False) -> None:
    """`lines [color],x1,y1,x2,y2,x3,y3,x4,y4,…` — `obj_fulllines`.

    **Des droites, pas des segments** : les points sont pris quatre
    coordonnées à la fois (`for(i=0;i<pm->pcnt;i+=4)`), et chaque paire donne
    une droite prolongée jusqu'au bord. PAX en faisait des segments
    indépendants, et jetait un reste de moins de quatre coordonnées :
    `addfig/triangle` écrit `lines rouge,x1,y1,x2,y2,x3,y3` pour chacun de ses
    trois côtés — trois points alignés — et n'en voyait tracer que la moitié.

    Le C, lui, fait une itération de plus sur ce reste, en lisant deux
    coordonnées **non initialisées** (`struct objparm pm;` est une locale
    d'`obj_main`) : comportement indéfini, que nous ne reproduisons pas. Un
    groupe incomplet est ignoré.
    """
    if not args:
        return
    color = _color(args[0])
    coords = [_num(a) for a in args[1:]]
    for i in range(0, len(coords) - 3, 4):
        _ligne_infinie(state, coords[i], coords[i + 1], coords[i + 2],
                       coords[i + 3], color, dashed)


def _cmd_fulldlines(state: _State, args: list[str]) -> None:
    # dlines — `obj_fulllines` avec `fill_tag` -1 : les mêmes, en pointillés.
    _cmd_fulllines(state, args, dashed=True)


def _cmd_dsegment(state: _State, args: list[str]) -> None:
    # `dsegment x1,y1,x2,y2,[color]` — DASHED segment (WIMS 'd' prefix = dashed;
    # used for dimension / extension lines). Not recorded in state.segments: a
    # dimension line is not a figure boundary, so it must not feed `flood`.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    state.elements.append(
        f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
        f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" stroke-dasharray="4,3" />'
    )


def _cmd_triangle(state: _State, args: list[str]) -> None:
    # triangle x1,y1,x2,y2,x3,y3,[color],[fill]
    if len(args) < 6:
        return
    x1, y1, x2, y2, x3, y3 = (_num(a) for a in args[:6])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    x3, y3 = state.tr(x3, y3)
    color = _color(args[6]) if len(args) > 6 else "#000000"
    fill = _color(args[7]) if len(args) > 7 else "none"
    pts = (
        f"{state.px(x1):.2f},{state.py(y1):.2f} "
        f"{state.px(x2):.2f},{state.py(y2):.2f} "
        f"{state.px(x3):.2f},{state.py(y3):.2f}"
    )
    state.segments.append(((x1, y1), (x2, y2)))
    state.segments.append(((x2, y2), (x3, y3)))
    state.segments.append(((x3, y3), (x1, y1)))
    state.polygons.append([(x1, y1), (x2, y2), (x3, y3)])
    state.elements.append(
        f'<polygon points="{pts}" fill="{fill}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_polyline(state: _State, args: list[str]) -> None:
    # polyline color, x1,y1,x2,y2,... — open chain of line segments.
    if len(args) < 5:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    if len(coords) < 4 or len(coords) % 2 != 0:
        return
    pts = " ".join(
        f"{state.px(coords[i]):.2f},{state.py(coords[i + 1]):.2f}"
        for i in range(0, len(coords), 2)
    )
    state.elements.append(
        f'<polyline points="{pts}" fill="none" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_polygon(state: _State, args: list[str]) -> None:
    # polygon color, x1,y1,x2,y2,... — closed filled polygon outline.
    if len(args) < 5:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    if len(coords) < 4 or len(coords) % 2 != 0:
        return
    verts = [(coords[i], coords[i + 1]) for i in range(0, len(coords), 2)]
    state.polygons.append(verts)
    pts = " ".join(f"{state.px(x):.2f},{state.py(y):.2f}" for x, y in verts)
    state.elements.append(
        f'<polygon points="{pts}" fill="none" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_arc(state: _State, args: list[str]) -> None:
    # arc xc,yc,w,h,start,end,[color]
    # Per WIMS doc: (xc, yc) is the *center* of the ellipse in math coords;
    # w and h are full width/height in x/y-range units; start/end in degrees
    # counter-clockwise from +x axis (math convention).
    if len(args) < 6:
        return
    import math
    cx, cy, w, h, start_deg, end_deg = (_num(a) for a in args[:6])
    color = _color(args[6]) if len(args) > 6 else "#000000"
    rx, ry = w / 2, h / 2
    # Seul le centre passe par la transformation (`obj_arc` : `scale` sur un
    # point, rayons en `xscale`/`yscale`) : les angles restent absolus — le
    # rapporteur de 0724 est écrit à 10–190° pour une base tournée de 10°.
    cx, cy = state.tr(cx, cy)
    # `myGdImageArc` part de `start` dans le sens direct, sur un écart ramené
    # dans [0, 360[ — et un écart nul trace le cercle entier. `arc …,357,3`
    # (`oefreprodangle2`) est donc le petit arc de 6° qui passe par 0°, non le
    # grand de 354° qu'une interpolation de 357 à 3 parcourait à reculons.
    ecart = (end_deg - start_deg) % 360 or 360
    # Sample the arc as a polyline so we don't have to figure out SVG's
    # convoluted A-command flags from math-coord angles.
    n = max(8, int(ecart / 5))
    pts = []
    for i in range(n + 1):
        t = start_deg + ecart * i / n
        rad = math.radians(t)
        mx = cx + rx * math.cos(rad)
        my = cy + ry * math.sin(rad)
        pts.append(f"{state.px(mx):.2f},{state.py(my):.2f}")
    state.elements.append(
        f'<polyline points="{" ".join(pts)}" fill="none" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_fcircle(state: _State, args: list[str]) -> None:
    # fcircle x,y,d,[color] — filled circle. Per WIMS doc d is the *diameter*
    # in pixels (not the radius — circle's third arg is the radius).
    if len(args) < 3:
        return
    x, y, d = _num(args[0]), _num(args[1]), _num(args[2])
    x, y = state.tr(x, y)
    color = _color(args[3]) if len(args) > 3 else "#000000"
    state.elements.append(
        f'<circle cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" '
        f'r="{d / 2:.2f}" fill="{color}" stroke="none" />'
    )


def _cmd_fellipse(state: _State, args: list[str]) -> None:
    # fellipse x,y,w,h,[color] — filled ellipse centered at (x,y).
    if len(args) < 4:
        return
    x, y, w, h = _num(args[0]), _num(args[1]), _num(args[2]), _num(args[3])
    x, y = state.tr(x, y)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    state.elements.append(
        f'<ellipse cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" '
        f'rx="{abs(w / 2):.2f}" ry="{abs(h / 2):.2f}" '
        f'fill="{color}" stroke="none" />'
    )


def _cmd_ellipse(state: _State, args: list[str]) -> None:
    # ellipse x,y,w,h,[color] — outline ellipse centered at (x,y) (math coords).
    if len(args) < 4:
        return
    x, y, w, h = _num(args[0]), _num(args[1]), _num(args[2]), _num(args[3])
    x, y = state.tr(x, y)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    # w and h are in x/y-range units, so convert each via the px/py deltas.
    rx_px = abs(state.px(x + w / 2) - state.px(x))
    ry_px = abs(state.py(y) - state.py(y + h / 2))
    # Record in math coords so a later `fill` can use it as the rim of a
    # pie/wheel sector (see _sector_fill_polygon).
    state.circles.append((x, y, abs(w / 2), abs(h / 2)))
    state.elements.append(
        f'<ellipse cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" '
        f'rx="{rx_px:.2f}" ry="{ry_px:.2f}" '
        f'fill="none" stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_lines(state: _State, args: list[str]) -> None:
    # lines [color],x1,y1,x2,y2,x3,y3,... — independent (x1,y1)→(x2,y2),
    # (x3,y3)→(x4,y4), … segments (NOT a connected polyline).
    if not args:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    if len(coords) < 4 or len(coords) % 4 != 0:
        # accept odd counts gracefully — drop trailing incomplete pair
        coords = coords[: (len(coords) // 4) * 4]
    for i in range(0, len(coords), 4):
        x1, y1, x2, y2 = coords[i], coords[i + 1], coords[i + 2], coords[i + 3]
        state.segments.append(((x1, y1), (x2, y2)))
        state.elements.append(
            f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
            f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )


def _cmd_segments(state: _State, args: list[str]) -> None:
    # segments [color],x1,y1,x2,y2,x3,y3,x4,y4,... — same as lines.
    _cmd_lines(state, args)


def _cmd_point(state: _State, args: list[str]) -> None:
    # point x,y,[color] — single pixel/dot.
    if len(args) < 2:
        return
    x, y = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.elements.append(
        f'<circle cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" '
        f'r="{max(state.linewidth / 2, 1):.2f}" fill="{color}" stroke="none" />'
    )


def _cmd_points(state: _State, args: list[str]) -> None:
    # points [color],x1,y1,x2,y2,... — multiple dots.
    if not args:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    for i in range(0, len(coords) - 1, 2):
        state.elements.append(
            f'<circle cx="{state.px(coords[i]):.2f}" '
            f'cy="{state.py(coords[i + 1]):.2f}" '
            f'r="{max(state.linewidth / 2, 1):.2f}" '
            f'fill="{color}" stroke="none" />'
        )


def _cmd_circles(state: _State, args: list[str], fill: bool = False) -> None:
    """`circles color,x1,y1,r1,…` — `obj_circles`. Le rayon est en **unités du
    repère** (`rint(2*r*xscale)` pixels de diamètre), non en pixels comme le
    disque isolé de `circle`. `fcircles` : la même, pleine."""
    if not args:
        return
    color = _color(args[0])
    coords = [_num(a) for a in args[1:]]
    xscale = state.width / ((state.xmax - state.xmin) or 1.0)
    for i in range(0, len(coords) - 2, 3):
        x, y = state.tr(coords[i], coords[i + 1])
        r = abs(coords[i + 2]) * xscale
        remplissage = color if fill else "none"
        state.elements.append(
            f'<circle cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" '
            f'r="{r:.2f}" fill="{remplissage}" stroke="{color}" '
            f'stroke-width="{state.linewidth}" />'
        )


def _cmd_fcircles(state: _State, args: list[str]) -> None:
    _cmd_circles(state, args, fill=True)


def _cmd_ftriangle(state: _State, args: list[str]) -> None:
    # ftriangle x1,y1,x2,y2,x3,y3,color — `obj_triangle` avec `fill_tag` 1.
    if len(args) < 6:
        return
    color = args[6] if len(args) > 6 else "black"
    _cmd_triangle(state, list(args[:6]) + [color, color])


def _cmd_rect(state: _State, args: list[str]) -> None:
    # rect x1,y1,x2,y2,[color] — outline rectangle, math coords for both corners.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    # Record the rectangle so a later `fill` inside it works (the rhombus/
    # triangle path handles polygon/triangle; rectangles went unfilled).
    state.polygons.append([(x1, y1), (x2, y1), (x2, y2), (x1, y2)])
    px1, px2 = state.px(min(x1, x2)), state.px(max(x1, x2))
    py1, py2 = state.py(max(y1, y2)), state.py(min(y1, y2))
    state.elements.append(
        f'<rect x="{px1:.2f}" y="{py1:.2f}" '
        f'width="{(px2 - px1):.2f}" height="{(py2 - py1):.2f}" '
        f'fill="none" stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_frect(state: _State, args: list[str]) -> None:
    # frect x1,y1,x2,y2,[color] — filled rectangle.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    px1, px2 = state.px(min(x1, x2)), state.px(max(x1, x2))
    py1, py2 = state.py(max(y1, y2)), state.py(min(y1, y2))
    state.elements.append(
        f'<rect x="{px1:.2f}" y="{py1:.2f}" '
        f'width="{(px2 - px1):.2f}" height="{(py2 - py1):.2f}" '
        f'fill="{color}" stroke="none" />'
    )


def _cmd_dline(state: _State, args: list[str]) -> None:
    # dline x1,y1,x2,y2,[color] — dashed segment.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    x1, y1 = state.tr(x1, y1)
    x2, y2 = state.tr(x2, y2)
    color = _color(args[4]) if len(args) > 4 else "#000000"
    state.segments.append(((x1, y1), (x2, y2)))
    state.elements.append(
        f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
        f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" '
        f'stroke-dasharray="4,3" />'
    )


def _cmd_dlines(state: _State, args: list[str]) -> None:
    # dlines [color],x1,y1,x2,y2,x3,y3,... — multiple dashed segments.
    if not args:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    for i in range(0, len(coords) - 3, 4):
        x1, y1, x2, y2 = coords[i], coords[i + 1], coords[i + 2], coords[i + 3]
        state.segments.append(((x1, y1), (x2, y2)))
        state.elements.append(
            f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
            f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth}" '
            f'stroke-dasharray="4,3" />'
        )


def _cmd_dhline(state: _State, args: list[str]) -> None:
    # dhline x,y,[color] — dashed full-width horizontal line.
    if len(args) < 2:
        return
    _, y = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.elements.append(
        f'<line x1="{state.px(state.xmin):.2f}" y1="{state.py(y):.2f}" '
        f'x2="{state.px(state.xmax):.2f}" y2="{state.py(y):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" '
        f'stroke-dasharray="4,3" />'
    )


def _cmd_dvline(state: _State, args: list[str]) -> None:
    # dvline x,y,[color] — dashed full-height vertical line.
    if len(args) < 2:
        return
    x, _ = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.elements.append(
        f'<line x1="{state.px(x):.2f}" y1="{state.py(state.ymin):.2f}" '
        f'x2="{state.px(x):.2f}" y2="{state.py(state.ymax):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" '
        f'stroke-dasharray="4,3" />'
    )


# ── Statistical / chart primitives ──────────────────────────────────────────

def _cmd_barchart(state: _State, args: list[str]) -> None:
    # barchart x_1:y_1:color_1:x_2:y_2:color_2:...
    # Per the WIMS doc, the colon-separated args come as ONE comma-list cell
    # OR are split across multiple cells if WIMS-script flattened them via
    # commas. Re-join then split on ':'.
    raw = ":".join(args).strip()
    if not raw:
        return
    parts = [p.strip() for p in raw.split(":") if p.strip()]
    if len(parts) % 3 != 0:
        return
    bars = []
    for i in range(0, len(parts), 3):
        try:
            bars.append((_num(parts[i]), _num(parts[i + 1]), _color(parts[i + 2])))
        except (ValueError, TypeError):
            return
    if not bars:
        return
    # Bar width: half the smallest gap between consecutive x's (or fallback).
    xs = sorted(set(b[0] for b in bars))
    if len(xs) >= 2:
        gap = min(xs[i + 1] - xs[i] for i in range(len(xs) - 1))
        bw = gap * 0.8
    else:
        bw = (state.xmax - state.xmin) * 0.1 or 1.0
    for x, y, color in bars:
        x0_px = state.px(x - bw / 2)
        x1_px = state.px(x + bw / 2)
        y_top = state.py(max(y, 0))
        y_bot = state.py(min(y, 0))
        state.elements.append(
            f'<rect x="{min(x0_px, x1_px):.2f}" y="{y_top:.2f}" '
            f'width="{abs(x1_px - x0_px):.2f}" '
            f'height="{abs(y_bot - y_top):.2f}" '
            f'fill="{color}" stroke="{color}" stroke-width="0.5" />'
        )


def _cmd_piechart(state: _State, args: list[str]) -> None:
    # piechart xc,yc,radius,'data+colorlist'
    # data+colorlist = "v1:c1:v2:c2:..." (colon-separated)
    if len(args) < 4:
        return
    try:
        xc = _num(args[0])
        yc = _num(args[1])
        radius = _num(args[2])  # pixels
    except (ValueError, TypeError):
        return
    raw = ":".join(args[3:]).strip().strip("'\"")
    parts = [p.strip() for p in raw.split(":") if p.strip()]
    if len(parts) < 2 or len(parts) % 2 != 0:
        return
    slices = []
    total = 0.0
    for i in range(0, len(parts), 2):
        try:
            v = _num(parts[i])
        except (ValueError, TypeError):
            return
        slices.append((v, _color(parts[i + 1])))
        total += v
    if total <= 0:
        return

    import math
    cx_px = state.px(xc)
    cy_px = state.py(yc)
    # Start at "12 o'clock" (top) and go clockwise — standard pie convention.
    angle_start = -math.pi / 2
    for v, color in slices:
        sweep = 2 * math.pi * (v / total)
        angle_end = angle_start + sweep
        x1 = cx_px + radius * math.cos(angle_start)
        y1 = cy_px + radius * math.sin(angle_start)
        x2 = cx_px + radius * math.cos(angle_end)
        y2 = cy_px + radius * math.sin(angle_end)
        large_arc = 1 if sweep > math.pi else 0
        # SVG path: move to centre, line to first edge, arc, line back to centre.
        path = (
            f"M {cx_px:.2f},{cy_px:.2f} "
            f"L {x1:.2f},{y1:.2f} "
            f"A {radius:.2f},{radius:.2f} 0 {large_arc} 1 {x2:.2f},{y2:.2f} "
            f"Z"
        )
        state.elements.append(
            f'<path d="{path}" fill="{color}" stroke="#000000" stroke-width="0.5" />'
        )
        angle_start = angle_end


def _cmd_boxplotdata(state: _State, args: list[str]) -> None:
    # boxplotdata v1,v2,v3,... — stash raw values; the next `boxplot` reads them.
    try:
        values = sorted(_num(a) for a in args if a.strip())
    except (ValueError, TypeError):
        return
    if not values:
        return
    state.boxplotdata = values


def _percentile(sorted_vals: list[float], q: float) -> float:
    # Linear-interpolated percentile (q ∈ [0, 1]).
    if not sorted_vals:
        return 0.0
    if len(sorted_vals) == 1:
        return sorted_vals[0]
    pos = q * (len(sorted_vals) - 1)
    lo, hi = int(pos), min(int(pos) + 1, len(sorted_vals) - 1)
    frac = pos - lo
    return sorted_vals[lo] * (1 - frac) + sorted_vals[hi] * frac


def _cmd_boxplot(state: _State, args: list[str]) -> None:
    # boxplot x_or_y,box-height_or_box-width,position[,min,Q1,median,Q3,max]
    # If only the first 3 args are present, expect prior `boxplotdata`.
    if len(args) < 3:
        return
    direction = args[0].strip().lower()
    if direction not in ("x", "y"):
        return
    try:
        thickness = _num(args[1])
        position = _num(args[2])
    except (ValueError, TypeError):
        return
    if len(args) >= 8:
        try:
            mn, q1, med, q3, mx = (_num(a) for a in args[3:8])
        except (ValueError, TypeError):
            return
    else:
        data = state.boxplotdata
        if not data:
            return
        mn = data[0]
        mx = data[-1]
        q1 = _percentile(data, 0.25)
        med = _percentile(data, 0.5)
        q3 = _percentile(data, 0.75)
    color = "#000000"

    if direction == "x":
        # Boxplot horizontal: stat values along x, centred on y=position with
        # ± thickness/2 above and below.
        y_lo = position - thickness / 2
        y_hi = position + thickness / 2
        # Whisker line min → max along x at y=position.
        state.elements.append(
            f'<line x1="{state.px(mn):.2f}" y1="{state.py(position):.2f}" '
            f'x2="{state.px(mx):.2f}" y2="{state.py(position):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )
        # Vertical caps at min and max.
        for v in (mn, mx):
            state.elements.append(
                f'<line x1="{state.px(v):.2f}" y1="{state.py(y_lo):.2f}" '
                f'x2="{state.px(v):.2f}" y2="{state.py(y_hi):.2f}" '
                f'stroke="{color}" stroke-width="{state.linewidth}" />'
            )
        # Q1-Q3 box.
        x_l, x_r = state.px(q1), state.px(q3)
        y_t, y_b = state.py(y_hi), state.py(y_lo)
        state.elements.append(
            f'<rect x="{min(x_l, x_r):.2f}" y="{min(y_t, y_b):.2f}" '
            f'width="{abs(x_r - x_l):.2f}" height="{abs(y_b - y_t):.2f}" '
            f'fill="none" stroke="{color}" stroke-width="{state.linewidth}" />'
        )
        # Median line.
        state.elements.append(
            f'<line x1="{state.px(med):.2f}" y1="{state.py(y_lo):.2f}" '
            f'x2="{state.px(med):.2f}" y2="{state.py(y_hi):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth + 0.5}" />'
        )
    else:  # direction == "y"
        x_lo = position - thickness / 2
        x_hi = position + thickness / 2
        state.elements.append(
            f'<line x1="{state.px(position):.2f}" y1="{state.py(mn):.2f}" '
            f'x2="{state.px(position):.2f}" y2="{state.py(mx):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )
        for v in (mn, mx):
            state.elements.append(
                f'<line x1="{state.px(x_lo):.2f}" y1="{state.py(v):.2f}" '
                f'x2="{state.px(x_hi):.2f}" y2="{state.py(v):.2f}" '
                f'stroke="{color}" stroke-width="{state.linewidth}" />'
            )
        x_l, x_r = state.px(x_lo), state.px(x_hi)
        y_t, y_b = state.py(q3), state.py(q1)
        state.elements.append(
            f'<rect x="{min(x_l, x_r):.2f}" y="{min(y_t, y_b):.2f}" '
            f'width="{abs(x_r - x_l):.2f}" height="{abs(y_b - y_t):.2f}" '
            f'fill="none" stroke="{color}" stroke-width="{state.linewidth}" />'
        )
        state.elements.append(
            f'<line x1="{state.px(x_lo):.2f}" y1="{state.py(med):.2f}" '
            f'x2="{state.px(x_hi):.2f}" y2="{state.py(med):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth + 0.5}" />'
        )


_FONT_SIZE_RE = re.compile(r"\b(\d+(?:\.\d+)?(?:px|pt|em|rem|%))\b", re.IGNORECASE)
_FONT_STYLE_RE = re.compile(r"\b(italic|oblique|normal)\b", re.IGNORECASE)
_FONT_WEIGHT_RE = re.compile(r"\b(bold|bolder|lighter|[1-9]00)\b", re.IGNORECASE)


def _cmd_fontfamily(state: _State, args: list[str]) -> None:
    # fontfamily font_description — e.g. "15px Arial", "italic 24pt Courier".
    # Parse out size / style / weight / family from a CSS-like shorthand.
    desc = ",".join(args).strip()
    if not desc:
        return
    rest = desc
    m = _FONT_SIZE_RE.search(rest)
    if m:
        state.font_size = m.group(1)
        rest = rest.replace(m.group(0), "", 1)
    m = _FONT_STYLE_RE.search(rest)
    if m:
        state.font_style = m.group(1).lower()
        rest = rest.replace(m.group(0), "", 1)
    m = _FONT_WEIGHT_RE.search(rest)
    if m:
        state.font_weight = m.group(1).lower()
        rest = rest.replace(m.group(0), "", 1)
    family = rest.strip().strip(",").strip()
    if family:
        state.font_family = family


def _cmd_fontsize(state: _State, args: list[str]) -> None:
    # fontsize int — set font size in pixels (WIMS default 12).
    if args:
        try:
            n = float(args[0])
            state.font_size = f"{n:g}px"
        except (TypeError, ValueError):
            pass


def _string_attrs(state: _State) -> str:
    parts = [f'font-size="{state.font_size}"',
             f'font-family="{state.font_family}"']
    if state.font_style and state.font_style != "normal":
        parts.append(f'font-style="{state.font_style}"')
    if state.font_weight:
        parts.append(f'font-weight="{state.font_weight}"')
    return " ".join(parts)


def _cmd_string(state: _State, args: list[str]) -> None:
    # string color,x,y,the text string — text in current fontfamily.
    if len(args) < 4:
        return
    color = _color(args[0])
    x, y = state.tr(_num(args[1]), _num(args[2]))
    content = ",".join(args[3:]).strip()
    state.elements.append(
        f'<text x="{state.px(x):.2f}" y="{state.py(y):.2f}" fill="{color}" '
        f'{_string_attrs(state)} dominant-baseline="middle">'
        f"{_xml_escape(content)}</text>"
    )


def _cmd_stringup(state: _State, args: list[str]) -> None:
    # stringup color,x,y,rotation_degrees,the text string — rotated text.
    # WIMS canvasdraw uses HTML5 Canvas's clockwise rotation convention,
    # which matches SVG's transform="rotate(deg)" — so we pass the angle
    # through as-is (270° = text reads bottom-to-top, like a typical y-axis
    # label).
    if len(args) < 5:
        return
    color = _color(args[0])
    x, y = state.tr(_num(args[1]), _num(args[2]))
    rot = _num(args[3])
    content = ",".join(args[4:]).strip()
    cx, cy = state.px(x), state.py(y)
    state.elements.append(
        f'<text x="{cx:.2f}" y="{cy:.2f}" fill="{color}" '
        f'{_string_attrs(state)} dominant-baseline="middle" '
        f'transform="rotate({rot:.2f}, {cx:.2f}, {cy:.2f})">'
        f"{_xml_escape(content)}</text>"
    )


def _cmd_size(state: _State, args: list[str]) -> None:
    # size x,y — set canvas size in pixels. We ignore: width/height come
    # from the !readproc oef/draw.phtml header; recomputing px/py would
    # invalidate already-drawn elements.
    pass


def _crosshair_svg(state: _State, x: float, y: float, color: str) -> str:
    # WIMS crosshair = "×" centered on (x, y). `crosshairsize` is the half-length
    # (radius): WIMS draws each branch from (x-size, y-size) to (x+size, y+size),
    # i.e. full extent = 2·size (see canvasdraw draw_crosshairs). Don't halve it.
    s = state.crosshairsize
    cx, cy = state.px(x), state.py(y)
    return (
        f'<line x1="{cx - s:.2f}" y1="{cy - s:.2f}" '
        f'x2="{cx + s:.2f}" y2="{cy + s:.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
        f'<line x1="{cx - s:.2f}" y1="{cy + s:.2f}" '
        f'x2="{cx + s:.2f}" y2="{cy - s:.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_crosshair(state: _State, args: list[str]) -> None:
    # crosshair x,y,[color] — single × at (x, y).
    if len(args) < 2:
        return
    x, y = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.elements.append(_crosshair_svg(state, x, y, color))


def _cmd_crosshairs(state: _State, args: list[str]) -> None:
    # crosshairs [color],x1,y1,x2,y2,... — multiple × at given points.
    if not args:
        return
    color = _color(args[0])
    coords = state.tr_flat([_num(a) for a in args[1:]])
    for i in range(0, len(coords) - 1, 2):
        state.elements.append(_crosshair_svg(state, coords[i], coords[i + 1], color))


def _cmd_crosshairsize(state: _State, args: list[str]) -> None:
    # crosshairsize int — set the × size in pixels (default 8).
    if args:
        try:
            state.crosshairsize = float(args[0])
        except (TypeError, ValueError):
            pass


def _cmd_transparent(state: _State, args: list[str]) -> None:
    # transparent [color] — declare a color as transparent. No-op in SVG
    # since we already emit fill="none" for outlines.
    pass


def _cmd_rotation(state: _State, args: list[str]) -> None:
    """`rotation d` / `rotate d` (`obj_rotation`) : la matrice de la rotation
    de `d` degrés autour de l'origine. Absolue — elle remplace la précédente —
    et elle garde la translation en cours."""
    if not args:
        return
    r = math.radians(_num(args[0]))
    state.matrix = (math.cos(r), -math.sin(r), math.sin(r), math.cos(r))
    state.transform = True


def _cmd_linear(state: _State, args: list[str]) -> None:
    # linear a,b,c,d — `obj_linear` : la matrice seule, translation gardée.
    if len(args) < 4:
        return
    state.matrix = tuple(_num(a) for a in args[:4])
    state.transform = True


def _cmd_affine(state: _State, args: list[str]) -> None:
    # affine a,b,c,d,tx,ty — `obj_affine` : matrice et translation.
    if len(args) < 6:
        return
    state.matrix = tuple(_num(a) for a in args[:4])
    state.transx, state.transy = _num(args[4]), _num(args[5])
    state.transform = True


def _cmd_translation(state: _State, args: list[str]) -> None:
    # translation tx,ty — `obj_translation` : le vecteur seul.
    if len(args) < 2:
        return
    state.transx, state.transy = _num(args[0]), _num(args[1])


def _cmd_killlinear(state: _State, args: list[str]) -> None:
    # killlinear / killrotation / killrotate — la matrice, pas la translation.
    state.matrix = (1.0, 0.0, 0.0, 1.0)
    state.transform = False


def _cmd_killtranslation(state: _State, args: list[str]) -> None:
    state.transx = state.transy = 0.0


def _cmd_killaffine(state: _State, args: list[str]) -> None:
    _cmd_killlinear(state, args)
    _cmd_killtranslation(state, args)


def _cmd_trange(state: _State, args: list[str]) -> None:
    # trange t1,t2 — domaine du paramètre d'un tracé paramétrique.
    if len(args) >= 2:
        state.tmin = _num(args[0])
        state.tmax = _num(args[1])


def _cmd_plotstep(state: _State, args: list[str]) -> None:
    """`plotstep n` / `plotsteps n` — nombre d'échantillons d'un tracé.

    `flydraw.c` la nomme `tstep` et la partage entre `plot` et `dplot`.
    """
    if not args:
        return
    try:
        n = int(float(_num(args[0])))
    except (TypeError, ValueError):
        return
    if n > 0:
        state.tstep = min(n, 5000)


def _cmd_xrange(state: _State, args: list[str]) -> None:
    if len(args) >= 2:
        state.xmin = _num(args[0])
        state.xmax = _num(args[1])


def _cmd_yrange(state: _State, args: list[str]) -> None:
    if len(args) >= 2:
        state.ymin = _num(args[0])
        state.ymax = _num(args[1])


def _cmd_hline(state: _State, args: list[str]) -> None:
    # hline x,y,[color] — full-width horizontal line at math y.
    if len(args) < 2:
        return
    _, y = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.segments.append(((state.xmin, y), (state.xmax, y)))
    state.elements.append(
        f'<line x1="{state.px(state.xmin):.2f}" y1="{state.py(y):.2f}" '
        f'x2="{state.px(state.xmax):.2f}" y2="{state.py(y):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_vline(state: _State, args: list[str]) -> None:
    # vline x,y,[color] — full-height vertical line at math x.
    if len(args) < 2:
        return
    x, _ = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.segments.append(((x, state.ymin), (x, state.ymax)))
    state.elements.append(
        f'<line x1="{state.px(x):.2f}" y1="{state.py(state.ymin):.2f}" '
        f'x2="{state.px(x):.2f}" y2="{state.py(state.ymax):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_gridfill(state: _State, args: list[str]) -> None:
    """``gridfill x,y,nx,ny,[color]``

    Per WIMS flydraw: fill the region containing (x,y) with a grid of
    horizontal and vertical lines spaced (nx, ny) pixels apart. We render
    it as an SVG ``<pattern>`` covering the whole viewport — visually the
    same effect as the WIMS flood-fill on an unbounded background, and
    cheaper than emitting hundreds of explicit ``<line>`` elements.
    """
    if len(args) < 4:
        return
    try:
        nx = float(args[2])
        ny = float(args[3])
    except ValueError:
        return
    if nx <= 0 or ny <= 0:
        return
    color = _color(args[4]) if len(args) > 4 else "#cccccc"
    pid = f"gp{len(state.elements)}"
    # Fine grid pattern; stroke 0.5 keeps the lines visually thin even at
    # small spacings. The pattern unit is `userSpaceOnUse` so nx/ny are in
    # pixels (matching flydraw's spec).
    pattern = (
        f'<defs><pattern id="{pid}" width="{nx}" height="{ny}" '
        f'patternUnits="userSpaceOnUse">'
        f'<path d="M {nx} 0 L 0 0 L 0 {ny}" fill="none" '
        f'stroke="{color}" stroke-width="0.5" />'
        f"</pattern></defs>"
    )
    rect = (
        f'<rect x="0" y="0" width="{state.width}" height="{state.height}" '
        f'fill="url(#{pid})" stroke="none" />'
    )
    # Prepend so the grid sits behind axes, plotted curves, and labels.
    state.elements.insert(0, pattern + rect)


def _cmd_plot(state: _State, args: list[str]) -> None:
    """`plot couleur,f(x)` — ou `plot couleur,x(t),y(t)`, la forme paramétrique.

    Les deux formes partagent `obj_plot` dans `nametab.c`, et le corpus les
    emploie autant l'une que l'autre : 326 appels explicites, 70 paramétriques
    répartis sur vingt fichiers. La seconde n'était pas traitée — les trois
    arguments étaient recollés en une seule formule, que sympy refusait, et la
    courbe disparaissait sans bruit. C'est ainsi que la figure de
    `oefpolygon/quadrilatere` ne portait plus que son cadre.
    """
    if len(args) < 2:
        return
    color = _color(args[0])
    if len(args) >= 3:
        _plot_parametrique(state, color, args[1].strip(), ",".join(args[2:]).strip())
        return
    formula = ",".join(args[1:]).strip()
    # `parse_expr` exécute du Python : même garde que `_num`, la formule
    # pouvant être celle qu'un élève a saisie.
    if not formula or not entree_math_sure(formula):
        return
    try:
        import sympy  # noqa: PLC0415
    except ImportError:
        return
    try:
        x_sym = sympy.Symbol("x")
        # Parse with implicit multiplication so WIMS tangents like `1(x-2)+2`
        # (from `\z2(x-\x2)+\y2`) work — bare sympify reads `1(...)` as a call
        # and rejects it, dropping the curve (quizz 1120 tangent). Done with
        # sympy directly to avoid importing the def_engine (circular).
        from sympy.parsing.sympy_parser import (  # noqa: PLC0415
            implicit_multiplication_application,
            parse_expr,
            standard_transformations,
        )
        transformations = standard_transformations + (implicit_multiplication_application,)
        expr = parse_expr(formula.replace("^", "**"), transformations=transformations)
        f = sympy.lambdify(x_sym, expr, modules=["math"])
    except Exception:
        return

    # Sample the curve and emit one polyline per continuous branch, clipping to
    # the y range. A sample that is undefined, NaN or out of range is dropped;
    # whenever that breaks the run of consecutive samples we start a *new*
    # polyline rather than bridging the gap — otherwise the two points either
    # side of a pole (e.g. 1/x at x=0) get joined by a spurious near-vertical
    # segment across the asymptote.
    n_samples = 200
    step = (state.xmax - state.xmin) / n_samples
    branches: list[list[str]] = []
    cur: list[str] = []
    prev_i: int | None = None
    for i in range(n_samples + 1):
        x = state.xmin + i * step
        try:
            y = float(f(x))
        except Exception:
            continue
        # Bornes **ordonnées** : en mode pixel `ymin` vaut la hauteur et
        # `ymax` zéro (l'axe y descend), si bien que la comparaison brute
        # écartait tous les points — `periodefrequence` n'avait pas de courbe.
        bas, haut = min(state.ymin, state.ymax), max(state.ymin, state.ymax)
        if y != y or y < bas - 1 or y > haut + 1:
            continue
        if cur and prev_i is not None and i != prev_i + 1:
            branches.append(cur)
            cur = []
        tx, ty = state.tr(x, y)
        cur.append(f"{state.px(tx):.2f},{state.py(ty):.2f}")
        prev_i = i
    if cur:
        branches.append(cur)
    for pts in branches:
        if len(pts) < 2:
            continue
        state.elements.append(
            f'<polyline points="{" ".join(pts)}" fill="none" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )


def _plot_parametrique(state: _State, color: str, sx: str, sy: str) -> None:
    """`plot couleur,x(t),y(t)` — une courbe échantillonnée sur `trange`.

    Le découpage en branches suit celui du tracé explicite : un échantillon
    indéfini ou hors cadre interrompt la polyligne au lieu d'être relié au
    suivant, pour ne pas barrer la figure d'un trait qui n'existe pas.
    """
    if not sx or not sy:
        return
    fx = _fonction_de_t(sx)
    fy = _fonction_de_t(sy)
    if fx is None or fy is None:
        return

    n = max(2, state.tstep)
    pas = (state.tmax - state.tmin) / n
    branches: list[list[str]] = []
    cur: list[str] = []
    for i in range(n + 1):
        t = state.tmin + i * pas
        try:
            x = float(fx(t))
            y = float(fy(t))
        except Exception:  # noqa: BLE001 — point indéfini : on coupe la branche
            if cur:
                branches.append(cur)
                cur = []
            continue
        # Fenêtrage au cadre **exact** : flydraw dessine dans un bitmap de
        # taille fixe, ce qui en sort n'existe pas. La tolérance d'une unité
        # que s'accorde le tracé explicite n'a pas cours ici — sur un `xrange`
        # de six unités elle laissait la courbe déborder de cinquante pixels.
        gauche, droite = min(state.xmin, state.xmax), max(state.xmin, state.xmax)
        bas, haut = min(state.ymin, state.ymax), max(state.ymin, state.ymax)
        if x != x or y != y or not (
            gauche <= x <= droite and bas <= y <= haut
        ):
            if cur:
                branches.append(cur)
                cur = []
            continue
        tx, ty = state.tr(x, y)
        cur.append(f"{state.px(tx):.2f},{state.py(ty):.2f}")
    if cur:
        branches.append(cur)
    for pts in branches:
        if len(pts) < 2:
            continue
        state.elements.append(
            f'<polyline points="{" ".join(pts)}" fill="none" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )


def _fonction_de_t(formule: str):
    """Compile une expression du paramètre `t` en fonction Python, ou None."""
    if not entree_math_sure(formule):
        return None
    try:
        import sympy  # noqa: PLC0415
        from sympy.parsing.sympy_parser import (  # noqa: PLC0415
            implicit_multiplication_application,
            parse_expr,
            standard_transformations,
        )
    except ImportError:
        return None
    try:
        transformations = standard_transformations + (
            implicit_multiplication_application,
        )
        expr = parse_expr(formule.replace("^", "**"), transformations=transformations)
        return sympy.lambdify(sympy.Symbol("t"), expr, modules=["math"])
    except Exception:  # noqa: BLE001 — hors périmètre : pas de courbe
        return None


def _cmd_circle(state: _State, args: list[str]) -> None:
    # circle x,y,d,[color] — d is the *diameter* in pixels (WIMS flydraw spec,
    # same convention as fcircle), so the SVG radius is d/2. (E.g. 0718: a
    # `circle E,d` of diameter 2·EF passing through F, not a radius-EF·2 one.)
    if len(args) < 3:
        return
    x, y, d = _num(args[0]), _num(args[1]), _num(args[2])
    x, y = state.tr(x, y)
    r = abs(d) / 2
    color = _color(args[3]) if len(args) > 3 else "#000000"
    state.elements.append(
        f'<circle cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" r="{r:.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" fill="none" />'
    )


def _segment_intersection(a: _Seg, b: _Seg, eps: float = 1e-7) -> _Pt | None:
    """Intersection point of two segments, or None if they don't cross.

    Both ``t`` and ``u`` parameters must lie in [0, 1] (with epsilon slack)
    so that endpoints touching counts as an intersection.
    """
    (x1, y1), (x2, y2) = a
    (x3, y3), (x4, y4) = b
    denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if abs(denom) < eps:
        return None
    t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom
    u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom
    if -eps <= t <= 1 + eps and -eps <= u <= 1 + eps:
        return (x1 + t * (x2 - x1), y1 + t * (y2 - y1))
    return None


def _point_in_triangle(p: _Pt, a: _Pt, b: _Pt, c: _Pt, eps: float = 1e-7) -> bool:
    def _sign(p1: _Pt, p2: _Pt, p3: _Pt) -> float:
        return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1])

    d1, d2, d3 = _sign(p, a, b), _sign(p, b, c), _sign(p, c, a)
    has_neg = (d1 < -eps) or (d2 < -eps) or (d3 < -eps)
    has_pos = (d1 > eps) or (d2 > eps) or (d3 > eps)
    return not (has_neg and has_pos)


def _triangle_area(a: _Pt, b: _Pt, c: _Pt) -> float:
    return 0.5 * abs((b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1]))


def _polygon_area(poly: list[_Pt]) -> float:
    """Absolute area of a (possibly non-convex) polygon — shoelace formula."""
    n = len(poly)
    s = 0.0
    for i in range(n):
        x1, y1 = poly[i]
        x2, y2 = poly[(i + 1) % n]
        s += x1 * y2 - x2 * y1
    return abs(s) / 2.0


def _point_in_polygon(p: _Pt, poly: list[_Pt]) -> bool:
    """Ray-casting point-in-polygon test (works for convex & concave)."""
    x, y = p
    inside = False
    n = len(poly)
    for i in range(n):
        x1, y1 = poly[i]
        x2, y2 = poly[(i + 1) % n]
        if (y1 > y) != (y2 > y):
            x_cross = x1 + (y - y1) * (x2 - x1) / (y2 - y1)
            if x < x_cross:
                inside = not inside
    return inside


def _line_intersection(a: _Pt, b: _Pt, c: _Pt, d: _Pt, eps: float = 1e-9) -> _Pt | None:
    """Intersection of two infinite lines defined by points (a,b) and (c,d)."""
    x1, y1 = a
    x2, y2 = b
    x3, y3 = c
    x4, y4 = d
    denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if abs(denom) < eps:
        return None
    t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom
    return (x1 + t * (x2 - x1), y1 + t * (y2 - y1))


def _sector_fill_polygon(state: _State, fx: float, fy: float) -> list[_Pt] | None:
    """Pie/wheel sector containing ``(fx, fy)``, or None.

    A roue is drawn as spokes radiating from a common hub plus an enclosing
    ellipse. Every pair of spokes meets only at the hub, so the triangle-from-
    parallel-families logic in _cmd_flood degenerates and fills nothing.
    Instead: locate the hub (the endpoint shared by the most segments) and an
    ellipse centred on it that contains the point, then return the wedge between
    the two spokes that angularly bracket the point, capped by the rim arc.
    """
    import math  # noqa: PLC0415
    from collections import defaultdict  # noqa: PLC0415

    if not state.segments or not state.circles:
        return None

    # Hub = the segment endpoint shared by the most spokes.
    by_pt: dict[tuple[float, float], list[_Pt]] = defaultdict(list)
    for p1, p2 in state.segments:
        by_pt[(round(p1[0], 6), round(p1[1], 6))].append(p2)
        by_pt[(round(p2[0], 6), round(p2[1], 6))].append(p1)
    hub_key = max(by_pt, key=lambda k: len(by_pt[k]))
    spoke_ends = by_pt[hub_key]
    if len(spoke_ends) < 2:
        return None
    hub = (hub_key[0], hub_key[1])

    # An ellipse centred (near) the hub that contains the flood point gives the
    # rim radius; its presence is what marks this as a genuine pie/wheel.
    rim: tuple[float, float] | None = None
    for cx, cy, rx, ry in state.circles:
        if rx < 1e-9 or ry < 1e-9:
            continue
        if math.hypot(cx - hub[0], cy - hub[1]) > 0.05 * max(rx, ry):
            continue
        if ((fx - cx) / rx) ** 2 + ((fy - cy) / ry) ** 2 <= 1.0:
            rim = (rx, ry)
            break
    if rim is None:
        return None
    rx, ry = rim

    # Distinct spoke angles around the hub.
    angs: list[float] = []
    for end in spoke_ends:
        dx, dy = end[0] - hub[0], end[1] - hub[1]
        if math.hypot(dx, dy) < 1e-9:
            continue
        a = math.atan2(dy, dx) % (2 * math.pi)
        if not any(abs(a - e) < 1e-4 for e in angs):
            angs.append(a)
    angs.sort()
    if len(angs) < 2:
        return None

    fdx, fdy = fx - hub[0], fy - hub[1]
    if math.hypot(fdx, fdy) < 1e-9:
        return None
    fang = math.atan2(fdy, fdx) % (2 * math.pi)

    # The two consecutive spokes that bracket the flood point (wrapping past 2π).
    n = len(angs)
    lo = hi = None
    for k in range(n):
        a_lo = angs[k]
        a_hi = angs[(k + 1) % n] + (2 * math.pi if k + 1 == n else 0.0)
        f = fang if fang >= a_lo else fang + 2 * math.pi
        if a_lo <= f < a_hi:
            lo, hi = a_lo, a_hi
            break
    if lo is None:
        return None

    # Wedge: hub → rim arc from lo to hi (~5° resolution).
    steps = max(2, int((hi - lo) / (math.pi / 36)) + 1)
    poly: list[_Pt] = [hub]
    for s in range(steps + 1):
        a = lo + (hi - lo) * s / steps
        poly.append((hub[0] + rx * math.cos(a), hub[1] + ry * math.sin(a)))
    return poly


def _flood_region(state: _State, fx: float, fy: float) -> list[_Pt] | None:
    """Math-coord polygon of the connected region containing (fx, fy), or None.

    Shared by the solid fill (`fill`/`flood`) and the pattern fills
    (`hatchfill`, …). Strategy, smallest-first:
    1. an explicitly-drawn closed polygon containing the point;
    2. a pie/wheel sector (spokes from a hub inside an ellipse);
    3. a grid cell reconstructed from three families of parallel segments —
       find the closest line above/below the point in each family, then take
       the smallest triangle of pairwise intersections that contains the
       point, so its edges lie on actual grid lines.
    """
    # Prefer an explicitly-drawn closed polygon containing the point. This fills
    # arbitrary shapes (e.g. the rhombus in oefcalittaire1) that the
    # triangle-from-segments fallback below can't handle. Smallest match wins so
    # an inner region is preferred over an enclosing one.
    containing = [poly for poly in state.polygons if _point_in_polygon((fx, fy), poly)]
    if containing:
        return min(containing, key=_polygon_area)

    # Pie/wheel sector — the families logic below can't handle it because every
    # spoke pair meets at the hub.
    sector = _sector_fill_polygon(state, fx, fy)
    if sector is not None:
        return sector

    if not state.segments:
        return None

    # Group segments by direction. Each family entry is keyed by a rounded
    # canonical normal so that segments with opposite orientation merge.
    families: dict[tuple[int, int], list[tuple[float, _Seg]]] = {}
    for seg in state.segments:
        (x1, y1), (x2, y2) = seg
        dx, dy = x2 - x1, y2 - y1
        length = (dx * dx + dy * dy) ** 0.5
        if length < 1e-9:
            continue
        # Unit normal (left of direction).
        nx, ny = -dy / length, dx / length
        # Canonicalise: force first non-zero component positive.
        if nx < -1e-9 or (abs(nx) < 1e-9 and ny < 0):
            nx, ny = -nx, -ny
        c = nx * x1 + ny * y1  # n·p == c for any p on the line
        key = (round(nx, 4), round(ny, 4))
        families.setdefault(key, []).append((c, seg))

    if len(families) < 3:
        return None

    # For each family find the closest line above and below the flood point.
    # Each candidate is (offset c, sample segment).
    candidate_pairs: list[list[tuple[float, _Seg]]] = []
    for key, lines in families.items():
        nx, ny = key
        c_p = nx * fx + ny * fy
        # Dedupe by offset (multiple segments lie on the same line).
        by_offset: dict[float, _Seg] = {}
        for c, seg in lines:
            by_offset.setdefault(round(c, 6), seg)
        offsets = sorted(by_offset.keys())
        below = [c for c in offsets if c < c_p]
        above = [c for c in offsets if c >= c_p]
        cands: list[tuple[float, _Seg]] = []
        if below:
            cands.append((below[-1], by_offset[below[-1]]))
        if above:
            cands.append((above[0], by_offset[above[0]]))
        if not cands:
            return None
        candidate_pairs.append(cands)

    # We expect exactly 3 families; with more, take the 3 with members
    # closest to the flood point.
    if len(candidate_pairs) > 3:
        candidate_pairs.sort(key=lambda fam: min(abs(c - 0) for c, _ in fam))
        candidate_pairs = candidate_pairs[:3]

    # Try every combination of one candidate per family.
    import itertools  # noqa: PLC0415

    best: tuple[_Pt, _Pt, _Pt] | None = None
    best_area = float("inf")
    for combo in itertools.product(*candidate_pairs):
        segs = [seg for _, seg in combo]
        v01 = _line_intersection(segs[0][0], segs[0][1], segs[1][0], segs[1][1])
        v12 = _line_intersection(segs[1][0], segs[1][1], segs[2][0], segs[2][1])
        v02 = _line_intersection(segs[0][0], segs[0][1], segs[2][0], segs[2][1])
        if v01 is None or v12 is None or v02 is None:
            continue
        area = _triangle_area(v01, v12, v02)
        if area <= 1e-9 or area >= best_area:
            continue
        if _point_in_triangle((fx, fy), v01, v12, v02):
            best = (v01, v12, v02)
            best_area = area
    if best is None:
        return None
    return [best[0], best[1], best[2]]


def _cmd_flood(state: _State, args: list[str]) -> None:
    """fill/flood x,y,[color] — fill the connected region containing (x,y)."""
    if len(args) < 2:
        return
    fx, fy = state.tr(_num(args[0]), _num(args[1]))
    color = _color(args[2]) if len(args) > 2 else "#000000"
    poly = _flood_region(state, fx, fy)
    if poly is None and not state.elements:
        # Aucune figure n'entoure le point : chez WIMS le remplissage s'étend
        # alors à **toute** la zone de même couleur, c'est-à-dire au fond de
        # l'image — c'est ainsi que `temps.fr/periodefrequence` se donne un
        # écran d'oscilloscope noir, par un `fill` posé en première commande.
        # Le rectangle est mis au fond de la pile : ce qui a déjà été tracé
        # bornerait le remplissage chez WIMS, donc reste visible ici. D'où la
        # condition : **rien de tracé**. Sinon le point est simplement dans
        # une région que notre recherche géométrique n'a pas su reconstituer
        # (les arcs n'y sont pas des frontières), et peindre toute l'image
        # serait bien pire que de ne rien peindre — `oefreprodangle2`
        # ressortait tout noir.
        state.elements.insert(
            0,
            f'<rect x="0" y="0" width="{state.width}" height="{state.height}" '
            f'fill="{color}" stroke="none" />',
        )
        return
    if poly is None:
        return
    pts = " ".join(f"{state.px(x):.2f},{state.py(y):.2f}" for x, y in poly)
    # Insert behind the outline/labels so the stroked border stays visible.
    state.elements.insert(0, f'<polygon points="{pts}" fill="{color}" stroke="none" />')


def _cmd_hatchfill(state: _State, args: list[str]) -> None:
    """hatchfill xc,yc,dx,dy,[color] — hatch the region containing (xc,yc).

    Per WIMS' ``draw_hatchfill`` (canvasdraw/canvasutils.c), the 3rd/4th args
    are pixel *increments* ``(dx, dy)`` setting the hatch line *direction* — NOT
    a (distance, angle°) pair. The corpus value ``10,10`` therefore means 45°
    (``dx == dy``), which is why WIMS hatches T1130 diagonally, not the ~10°
    a degree reading produced. We tile an SVG ``<pattern>`` of one ``dx×dy``
    cell with its diagonal drawn: the cells stitch into continuous parallel
    lines at angle ``atan2(dy, dx)`` (perpendicular spacing
    ``dx·dy/hypot(dx, dy)``), clipped to the region polygon. A later white
    ``fcircle`` then masks the centre, leaving the corners hatched.
    """
    if len(args) < 2:
        return
    fx, fy = state.tr(_num(args[0]), _num(args[1]))
    dx = abs(_num(args[2])) if len(args) > 2 else 10.0
    dy = abs(_num(args[3])) if len(args) > 3 else 10.0
    color = _color(args[4]) if len(args) > 4 else "#000000"
    poly = _flood_region(state, fx, fy)
    if poly is None:
        return
    dx = max(dx, 2.0)  # avoid a degenerate / solid-black tile
    dy = max(dy, 2.0)
    pid = f"hatch{len(state.elements)}_{abs(hash((round(fx, 3), round(fy, 3)))) % 100000}"
    # One corner-to-corner diagonal per dx×dy tile. Endpoints sit exactly on the
    # tile corners, so neighbouring tiles' segments meet → continuous parallel
    # lines. (0,0)→(dx,dy) leans "\" in SVG's y-down space, matching WIMS.
    pattern = (
        f'<defs><pattern id="{pid}" width="{dx:.2f}" height="{dy:.2f}" '
        f'patternUnits="userSpaceOnUse">'
        f'<line x1="0" y1="0" x2="{dx:.2f}" y2="{dy:.2f}" '
        f'stroke="{color}" stroke-width="{max(state.linewidth, 1.0):.2f}" />'
        f"</pattern></defs>"
    )
    pts = " ".join(f"{state.px(x):.2f},{state.py(y):.2f}" for x, y in poly)
    # Behind the outline/labels (and any later masking fill) like `fill`.
    state.elements.insert(0, pattern + f'<polygon points="{pts}" fill="url(#{pid})" stroke="none" />')


def _xml_escape(s: str) -> str:
    return (
        s.replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
        .replace('"', "&quot;")
    )



# ── Couleurs écrites en r,g,b (`nametab.c`) ──────────────────────────────────
#
# Chez WIMS, une couleur occupe **trois items** : `substit` (`flydraw.c:87`)
# remplace d'abord un nom (`red`) par sa définition (`255,0,0`), et
# `parse_parms` en consomme toujours trois. PAX lit la couleur comme un seul
# jeton — ce qui marche pour un nom, mais lisait `51,51,51` comme `51`, donc
# noir. La table dit où chercher : `required_parms` et `color_pos`, ce dernier
# valant -1 quand la couleur précède les paramètres et 1 quand elle les suit.
_COULEUR_POS: dict[str, tuple[int, int]] = {
    "arc": (6, 1),
    "arrow": (5, 1),
    "arrow2": (5, 1),
    "arrows": (5, -1),
    "arrows2": (5, -1),
    "ball": (3, 1),
    "brokenline": (4, -1),
    "circle": (3, 1),
    "circles": (3, -1),
    "crosshair": (2, 1),
    "crosshairs": (2, -1),
    "darrow": (5, 1),
    "darrow2": (5, 1),
    "dasharrow": (5, 1),
    "dasharrow2": (5, 1),
    "dashedarrow2": (5, 1),
    "dashedline": (4, 1),
    "dashedlines": (4, -1),
    "dashhalfline": (4, 1),
    "dashline": (4, 1),
    "dashlines": (4, -1),
    "dashsegment": (4, 1),
    "demiline": (4, 1),
    "dhline": (2, 1),
    "disk": (3, 1),
    "dline": (4, 1),
    "dlines": (4, -1),
    "dpolyline": (4, -1),
    "dsegment": (4, 1),
    "dvline": (2, 1),
    "ellipse": (4, 1),
    "fcircle": (3, 1),
    "fcircles": (3, -1),
    "fellipse": (4, 1),
    "fill": (2, 1),
    "fillcircle": (3, 1),
    "filledcircle": (3, 1),
    "filledellipse": (4, 1),
    "filledpoly": (4, -1),
    "filledpolygon": (4, -1),
    "filledrect": (4, 1),
    "filledrectangle": (4, 1),
    "filledsquare": (3, 1),
    "filledtriangle": (6, 1),
    "fillellipse": (4, 1),
    "fillrect": (4, 1),
    "fillrectangle": (4, 1),
    "fillsquare": (3, 1),
    "filltriangle": (6, 1),
    "flood": (2, 1),
    "floodfill": (2, 1),
    "fpoly": (4, -1),
    "fpolygon": (4, -1),
    "frect": (4, 1),
    "frectangle": (4, 1),
    "fsquare": (3, 1),
    "ftriangle": (6, 1),
    "gridfill": (4, 1),
    "halfline": (4, 1),
    "hatchfill": (4, 1),
    "hline": (2, 1),
    "line": (4, 1),
    "lines": (4, -1),
    "parallel": (7, 1),
    "plot": (0, -1),
    "point": (2, 1),
    "points": (2, -1),
    "poly": (4, -1),
    "polygon": (4, -1),
    "polyline": (4, -1),
    "rect": (4, 1),
    "rectangle": (4, 1),
    "seg": (4, 1),
    "segment": (4, 1),
    "segments": (4, -1),
    "square": (3, 1),
    "string": (2, -1),
    "stringup": (2, -1),
    "text": (2, -1),
    "textup": (2, -1),
    "transparent": (0, -1),
    "triangle": (6, 1),
    "vline": (2, 1),
}


def _est_octet(s: str) -> bool:
    s = s.strip()
    return s.isdigit() and 0 <= int(s) <= 255


def _fusionner_couleur(cmd: str, args: list[str]) -> list[str]:
    """La couleur, lue comme le fait `parse_parms` : **trois items**.

    `substit` remplace d'abord chaque nom par sa définition (`red` →
    `255,0,0`), puis `calc_color` prend les trois items suivants. D'où un
    résultat déroutant quand l'auteur met un argument de trop :
    `fill 3,-0.5,6,red` (`oefreprodangle2`) donne la couleur `(6, 255, 0)` —
    un vert — parce que le `6` en trop devient sa composante rouge. PAX lisait
    `6` seul, donc noir.

    Le développement des noms est borné à la fenêtre de la couleur : WIMS,
    lui, substitue toute la ligne, et abîme au passage un mot de couleur
    écrit dans un texte non guillemeté.
    """
    meta = _COULEUR_POS.get(cmd)
    if not meta:
        return args
    requis, pos = meta
    i = 0 if pos < 0 else requis
    if len(args) <= i:
        return args
    fenetre: list[str] = []
    consommes = 0
    for a in args[i:]:
        if len(fenetre) >= 3:
            break
        consommes += 1
        hexa = _COLORS.get(a.strip().lower())
        if hexa and hexa.startswith("#") and len(hexa) == 7:
            fenetre.extend(str(int(hexa[k : k + 2], 16)) for k in (1, 3, 5))
        else:
            fenetre.append(a.strip())
    if len(fenetre) < 3 or not all(_est_octet(x) for x in fenetre[:3]):
        return args
    r, v, b = (int(x) for x in fenetre[:3])
    reste = fenetre[3:] + args[i + consommes :]
    return args[:i] + [f"#{r:02x}{v:02x}{b:02x}"] + reste


_HANDLERS = {
    # Range / canvas
    "range": _cmd_range,
    "xrange": _cmd_xrange,
    "yrange": _cmd_yrange,
    "size": _cmd_size,
    "linewidth": _cmd_linewidth,
    "transparent": _cmd_transparent,
    # Transformations (`objects.c:1482-1535`) et leurs synonymes (`nametab.c`).
    "rotation": _cmd_rotation,
    "rotate": _cmd_rotation,
    "linear": _cmd_linear,
    "affine": _cmd_affine,
    "translation": _cmd_translation,
    "translate": _cmd_translation,
    "killrotation": _cmd_killlinear,
    "killrotate": _cmd_killlinear,
    "killlinear": _cmd_killlinear,
    "killtranslation": _cmd_killtranslation,
    "killtranslate": _cmd_killtranslation,
    "killaffine": _cmd_killaffine,
    "trange": _cmd_trange,
    "ranget": _cmd_trange,
    "tstep": _cmd_plotstep,
    "tsteps": _cmd_plotstep,
    "rangex": _cmd_xrange,
    "rangey": _cmd_yrange,
    "plotstep": _cmd_plotstep,
    "plotsteps": _cmd_plotstep,
    "crosshair": _cmd_crosshair,
    "crosshairs": _cmd_crosshairs,
    "crosshairsize": _cmd_crosshairsize,
    # Lines / segments
    "segment": _cmd_segment,
    "segments": _cmd_segments,
    "dsegment": _cmd_dsegment,
    "line": _cmd_line,
    "lines": _cmd_fulllines,
    "dline": _cmd_dline,
    "dlines": _cmd_fulldlines,
    # `obj_dlines` : la ligne brisée en pointillés, que `dpolyline` rend déjà.
    "dashedlines": _cmd_dpolyline,
    "dashlines": _cmd_dpolyline,
    "brokenline": _cmd_polyline,
    "hline": _cmd_hline,
    "dhline": _cmd_dhline,
    "vline": _cmd_vline,
    "dvline": _cmd_dvline,
    "halfline": _cmd_halfline,
    "dashhalfline": _cmd_dashhalfline,
    # Arrows
    "arrow": _cmd_arrow,
    "arrow2": _cmd_arrow2,
    "arrows": _cmd_arrows,
    "arrows2": _cmd_arrows2,
    "darrow": _cmd_darrow,
    "darrow2": _cmd_darrow2,
    "dasharrow": _cmd_darrow,  # alias per WIMS doc
    "dasharrow2": _cmd_darrow2,
    "dashedarrow2": _cmd_darrow2,  # second alias
    "parallel": _cmd_parallel,
    # Points / circles / ellipses
    "point": _cmd_point,
    "points": _cmd_points,
    "circle": _cmd_circle,
    "circles": _cmd_circles,
    "fcircle": _cmd_fcircle,
    "disk": _cmd_fcircle,  # alias per WIMS doc
    "ball": _cmd_fcircle,
    "filledcircle": _cmd_fcircle,
    "ellipse": _cmd_ellipse,
    "fellipse": _cmd_fellipse,
    # Shapes
    "triangle": _cmd_triangle,
    "polyline": _cmd_polyline,
    "dpolyline": _cmd_dpolyline,
    "polygon": _cmd_polygon,
    "poly": _cmd_polygon,  # alias used by corpus (not in summary doc but works)
    "fpolygon": _cmd_fpolygon,
    "fpoly": _cmd_fpolygon,
    "filledpoly": _cmd_fpolygon,
    "filledpolygon": _cmd_fpolygon,
    "rect": _cmd_rect,
    "rectangle": _cmd_rect,  # alias per WIMS doc
    "frect": _cmd_frect,
    "frectangle": _cmd_frect,
    "filledrect": _cmd_frect,
    "filledrectangle": _cmd_frect,
    "square": _cmd_square,
    "fsquare": _cmd_fsquare,
    # Synonymes de `nametab.c`, chacun sur la variante — pleine ou non — que
    # lui donne son `fill_tag`.
    "seg": _cmd_segment,
    "demiline": _cmd_halfline,
    "dashedline": _cmd_dsegment,
    "dashline": _cmd_dsegment,
    "dashsegment": _cmd_dsegment,
    "ftriangle": _cmd_ftriangle,
    "filledtriangle": _cmd_ftriangle,
    "filltriangle": _cmd_ftriangle,
    "fillrect": _cmd_frect,
    "fillrectangle": _cmd_frect,
    "fillcircle": _cmd_fcircle,
    "fcircles": _cmd_fcircles,
    "fillellipse": _cmd_fellipse,
    "filledellipse": _cmd_fellipse,
    "filledsquare": _cmd_fsquare,
    "fillsquare": _cmd_fsquare,
    "floodfill": _cmd_flood,
    "arc": _cmd_arc,
    # Fill
    "fill": _cmd_flood,
    "flood": _cmd_flood,
    "gridfill": _cmd_gridfill,
    "hatchfill": _cmd_hatchfill,
    # Image paste
    "copy": _cmd_copy,
    "insert": _cmd_copy,  # alias per WIMS nametab
    # Text / plot
    "new": _cmd_new,
    "text": _cmd_text,
    "textup": _cmd_textup,
    "string": _cmd_string,
    "stringup": _cmd_stringup,
    "fontfamily": _cmd_fontfamily,
    "fontsize": _cmd_fontsize,
    "plot": _cmd_plot,
    # Charts
    "barchart": _cmd_barchart,
    "piechart": _cmd_piechart,
    "boxplot": _cmd_boxplot,
    "boxplotdata": _cmd_boxplotdata,
}


# ── Public API ────────────────────────────────────────────────────────────────


def flydraw_to_svg(width: int, height: int, commands: str, base_dir: str | None = None) -> str:
    """Render a flydraw command list to an SVG string.

    Commands may be separated by newline, tab, or semicolon — matching
    WIMS flydraw's ``ggetline`` (``flylines.c``), and matching how the
    .def-baked WIMS-script packs multiple commands on one line via tabs.

    When no xrange/yrange is set, coordinates are interpreted as pixels with
    (0, 0) at the top-left (HTML5 canvas convention). xrange/yrange commands
    override that default and switch to math coordinates.
    """
    state = _rendre(width, height, commands, base_dir)
    return _svg(state.width, state.height, "".join(state.elements))


def _svg(width: int, height: int, corps: str) -> str:
    return (
        f'<svg xmlns="http://www.w3.org/2000/svg" '
        f'width="{width}" height="{height}" '
        f'viewBox="0 0 {width} {height}">{corps}</svg>'
    )


def _rendre(width: int, height: int, commands: str, base_dir: str | None = None,
            variables: dict[str, float] | None = None) -> "_State":
    """Exécute les commandes et rend l'état final (éléments SVG compris)."""
    w, h = int(width), int(height)
    # Pixel-mode defaults: ymin=h, ymax=0 inverts the y-flip in py() so that
    # raw pixel y values pass through unchanged.
    state = _State(width=w, height=h, xmin=0, xmax=w, ymin=h, ymax=0, base_dir=base_dir)
    variables = dict(variables or {})
    jeton = _VARIABLES.set(variables)
    try:
        raw_lines = re.split(r"[\n\t;]", commands)
        for raw in raw_lines:
            line = raw.strip().rstrip("\\").strip()
            if not line or line.startswith("#"):
                continue
            m = re.match(r"^(\w+)\s*(.*)$", line)
            if not m:
                continue
            nom = m.group(1)
            if len(nom) == 1 or (len(nom) == 2 and nom[1].isdigit()):
                # `obj_main` : un nom d'une lettre (ou lettre + chiffre) est une
                # variable, et le `=` (ou `:=`) qui suit est facultatif.
                valeur = re.sub(r"^:?=", "", m.group(2).strip())
                variables[nom] = _num(valeur)
                continue
            cmd = nom.lower()
            arg_str = m.group(2)
            args = _split_args(arg_str) if arg_str else []
            args = _fusionner_couleur(cmd, args)
            handler = _HANDLERS.get(cmd)
            if handler:
                handler(state, args)
            else:
                _log_unhandled_cmd(cmd, arg_str)
    finally:
        _VARIABLES.reset(jeton)
    return state


# Module-level cache: a hash → SVG string. The backend route
# ``/api/render/svg/{id}`` reads from this. The cache lives for the
# process lifetime; it's small (hundreds of bytes per SVG) so we don't
# bother evicting.
_SVG_CACHE: dict[str, str] = {}


def flydraw_to_url(width: int, height: int, commands: str, base_dir: str | None = None) -> str:
    """Render commands, cache the SVG, and return a comma-free URL.

    A data URI would contain ``,`` (between ``;base64`` and the data), which
    would break WIMS-script's comma-separated list handling further upstream
    (``!shuffle``, ``!positionof``). Instead, we hash the rendered SVG, cache
    it, and emit ``/api/render/svg/<hash>``.
    """
    svg = flydraw_to_svg(width, height, commands, base_dir=base_dir)
    key = hashlib.sha1(svg.encode("utf-8")).hexdigest()[:16]
    _SVG_CACHE[key] = svg
    return f"/api/render/svg/{key}"


# `ins_anim_limit` (`config.c`) : `exec_insdraw` plafonne à `ANIM_LIMIT-1`.
_ANIM_MAX = 399
_ANIM_RE = re.compile(r"^\s*animate\s+([^\n\t]*)(?:[\n\t]|$)", re.I)
# `varchr` : le corps n'anime rien s'il ne cite ni `s`, ni `animstep`, ni `step`.
_ANIM_VARS_RE = re.compile(r"(?<![A-Za-z0-9_])(?:s|animstep|step)(?![A-Za-z0-9_])")


def flydraw_anime_to_url(width: int, height: int, commands: str,
                         base_dir: str | None = None) -> str:
    """`oef/draw.phtml` : un `animate f,d,b` en tête du corps en fait un GIF animé.

    `insdraw..processor` rend alors f images, la i-ième précédée de
    `s=i/f` (et d'un `animstep=i` que `obj_main` rejette : le nom est trop long
    pour une variable), puis `whirlgif` les assemble, `d` secondes par image,
    `b` boucles (0 : sans fin). `OEFevalwimstrian` y montre la construction
    d'un triangle au compas ; sans cela PAX figeait la première image — un
    segment de longueur nulle.

    Le GIF devient un SVG : ce qui est commun à toutes les images est tracé une
    fois, le reste par image, chacune visible à son tour (SMIL, discret). La
    dernière est visible par défaut, de sorte qu'un lecteur sans SMIL voit la
    figure achevée.
    """
    m = _ANIM_RE.match(commands)
    if not m:
        return flydraw_to_url(width, height, commands, base_dir=base_dir)
    corps = commands[m.end():]
    parms = [p.strip() for p in m.group(1).split(",")]
    try:
        images = int(_num(parms[0])) if parms and parms[0] else 1
    except (TypeError, ValueError):
        images = 1
    images = max(1, min(images, _ANIM_MAX))
    if images > 1 and not _ANIM_VARS_RE.search(corps):
        images = 1
    if images == 1:
        return flydraw_to_url(width, height, corps, base_dir=base_dir)
    delai = min(max(_num(parms[1]) if len(parms) > 1 else 0.0, 0.0), 10.0)
    boucles = int(_num(parms[2])) if len(parms) > 2 and parms[2] else 0
    # `whirlgif -time` compte en centièmes (`int2str(d*100)`) ; les navigateurs
    # portent à 10 cs un délai de 0 ou 1 cs — `animate 40,0.01,0` défile donc
    # à 0,1 s par image chez l'élève de WIMS.
    centiemes = int(delai * 100)
    pas = 0.1 if centiemes <= 1 else centiemes / 100

    etats = [_rendre(width, height, corps, base_dir, {"s": i / images})
             for i in range(images)]
    listes = [e.elements for e in etats]
    debut = 0
    while all(len(l) > debut for l in listes) and all(l[debut] == listes[0][debut] for l in listes):
        debut += 1
    fin = 0
    while all(len(l) - debut > fin for l in listes) and all(
            l[len(l) - 1 - fin] == listes[0][len(listes[0]) - 1 - fin] for l in listes):
        fin += 1
    duree = images * pas
    repetition = "indefinite" if boucles <= 0 else str(boucles)
    groupes = []
    for i, l in enumerate(listes):
        propre = "".join(l[debut:len(l) - fin])
        derniere = i == images - 1
        a, b = i / images, (i + 1) / images
        if derniere:
            valeurs, temps, garde = "hidden;visible", f"0;{a:.4f}", ' fill="freeze"'
        else:
            valeurs, temps, garde = "hidden;visible;hidden", f"0;{a:.4f};{b:.4f}", ""
        groupes.append(
            f'<g visibility="{"visible" if derniere else "hidden"}">'
            f'<animate attributeName="visibility" calcMode="discrete" values="{valeurs}" '
            f'keyTimes="{temps}" dur="{duree:.2f}s" repeatCount="{repetition}"{garde} />'
            f"{propre}</g>"
        )
    corps_svg = "".join(listes[0][:debut]) + "".join(groupes) + "".join(listes[0][len(listes[0]) - fin:])
    svg = _svg(etats[0].width, etats[0].height, corps_svg)
    key = hashlib.sha1(svg.encode("utf-8")).hexdigest()[:16]
    _SVG_CACHE[key] = svg
    return f"/api/render/svg/{key}"


def get_cached_svg(key: str) -> str | None:
    return _SVG_CACHE.get(key)


# La balise que ce motif doit reconnaître est écrite **par l'exercice**, pas
# par PAX : `patron1.def` pose `val20=<img src='$val20' alt=''>`. Elle prend
# donc toutes les formes que le HTML autorise, et le motif d'origine —
# `<img\s+src="…"` — en ratait quatre, mesurées sur le corpus (522 marqueurs,
# 16 exercices) :
#
#   apostrophes            381   <img src='…' alt=''>
#   attribut avant `src`    51   <img name="0" src="…" alt="0">
#   blanc dans la valeur    51   <img src="<TAB>…"<TAB>width="40">
#   espace après `src=`     36   <img src= "…" width="160">
#   sans guillemets         12   <img src=… style="float:right">
#
# Chacune laissait sortir le marqueur tel quel — et comme la route
# `/api/render/svg/…` **n'existe pas** (le cache est en mémoire, lu ici même),
# l'élève voyait une image morte à la place de la figure. La dernière forme,
# valide en HTML, cassait `oefrelat` et `solide6-5.nl` (2026-09-24). Le
# guillemet est donc facultatif, mais s'il s'ouvre il doit se fermer : un
# `src="…` jamais refermé est une coquille d'auteur que WIMS sert cassée
# aussi (`oefpscal/cercle`), et qu'on ne répare pas.
_IMG_SVG_RE = re.compile(
    r'<img\b[^>]*?\bsrc\s*=\s*(?P<q>["\']?)\s*'
    r'/api/render/svg/(?P<key>[a-f0-9]+)\s*(?P=q)[^>]*>'
)


# Block-level tags that act as "wrap reset" boundaries when grouping a figure
# with its preceding label. A figure can't be glued to a label that lives on
# the other side of a <br>, table cell, paragraph break, etc.
_FIG_BOUNDARY_RE = re.compile(
    r'<br\s*/?>|</?(?:p|div|h[1-6]|li|ul|ol|table|tr|td|th|section|article|header|footer|figure)\b[^>]*>',
    re.IGNORECASE,
)


_VIDES = frozenset(
    "area base br col embed hr img input link meta param source track wbr".split()
)
_BALISE_RE = re.compile(r"<(/?)([a-zA-Z][a-zA-Z0-9]*)\b[^>]*?(/?)>")


def _balises_equilibrees(fragment: str) -> bool:
    """Tout ce que `fragment` ouvre s'y referme-t-il ?

    Sert à décider si `group_inline_figures` peut reculer son `<span>` jusqu'à
    une balise : envelopper un fragment déséquilibré produirait du HTML mal
    imbriqué. Les éléments vides (`<img>`, `<br>`, `<input>`…) et les balises
    auto-fermantes ne comptent pas.
    """
    profondeur = 0
    for m in _BALISE_RE.finditer(fragment):
        fermante, nom, auto = m.group(1), m.group(2).lower(), m.group(3)
        if nom in _VIDES or auto:
            continue
        if fermante:
            profondeur -= 1
            if profondeur < 0:
                return False
        else:
            profondeur += 1
    return profondeur == 0


def group_inline_figures(html: str) -> str:
    """Wrap each flydraw figure placeholder with its preceding label text
    in a ``<span class="pax-fig-group">``.

    Without this, a render like ``Figure 1 : <svg> Figure 2 : <svg>`` is just
    inline content with breakable whitespace everywhere — narrow viewports
    can end up wrapping mid-pair (``Figure 1 : <svg> Figure 2 :`` on line one,
    ``<svg> Figure 3 : <svg>`` on line two), which reads badly. By gluing each
    label to its figure under ``white-space: nowrap``, the only breakable
    points are *between* groups.

    Runs in the engine pipeline *before* ``inline_svg_imgs`` so the SVG body
    (which contains its own ``<image>``/``<polygon>`` tags) doesn't confuse
    the boundary regex — placeholders here are still ``<img src="/api/render/
    svg/…">`` one-liners.
    """
    out: list[str] = []
    pos = 0
    for m in _IMG_SVG_RE.finditer(html):
        segment = html[pos:m.start()]
        # The label spans from the latest block boundary (or the previous
        # figure's end) to this figure's start. If neither exists in
        # `segment`, we glue from `pos`.
        last_b = None
        for bm in _FIG_BOUNDARY_RE.finditer(segment):
            last_b = bm.end()
        label_start = pos + last_b if last_b is not None else pos

        # Cap the label at 80 chars so a stray figure inside running prose
        # doesn't pull the whole sentence into one non-wrapping line. Snap to
        # the nearest preceding whitespace so we don't slice mid-word.
        if m.start() - label_start > 80:
            cap = m.start() - 80
            space = html.rfind(" ", label_start, cap)
            label_start = (space + 1) if space > label_start else cap
            # Ce plafond coupe à l'espace, et une balise en contient : celle
            # de `patron1` — `<label class="oef-checkbox-label">` précédée d'un
            # `<input>` fait plus de 80 caractères — se voyait tranchée entre
            # `<label` et `class=`, le `<span>` ouvert au milieu, et le reste
            # de la balise sortait **en texte** sous les yeux de l'élève.
            #
            # Quand la coupe tombe dans du balisage, on recule jusqu'au début
            # de la balise : c'est la seule bordure propre à portée. Sortir par
            # sa **fin** atterrirait *dans* l'élément, et
            # `<span class="oef-radio-inline" …></span>` — que le découpage en
            # segments reconnaît à son `></span>` collé — s'en trouvait
            # éventré, donc plus rendu du tout.
            #
            # Reculer n'est sûr que si tout ce qu'on enveloppe s'y referme :
            # sinon le `<span>` ouvrirait avant une balise que `m.end()` ne
            # refermerait pas. À défaut, on n'enveloppe que la figure — il n'y
            # a alors pas d'étiquette à coller, et c'est sans conséquence.
            dernier_lt = html.rfind("<", 0, label_start)
            dernier_gt = html.rfind(">", 0, label_start)
            if dernier_lt > dernier_gt:
                recule = dernier_lt
                label_start = (
                    recule if _balises_equilibrees(html[recule:m.end()])
                    else m.start()
                )

        out.append(html[pos:label_start])
        out.append('<span class="pax-fig-group">')
        out.append(html[label_start:m.end()])
        out.append('</span>')
        pos = m.end()
    out.append(html[pos:])
    return ''.join(out)


def inline_svg_imgs(html: str) -> str:
    """Replace ``<img src="/api/render/svg/<key>">`` markers with the cached SVG.

    The URL form is used internally so that values flowing through WIMS-script
    list operations (which split on ``,``) stay intact. At the boundary of the
    rendered exercise we inline the SVG to give the frontend a single payload —
    no out-of-band fetches, no cache lifecycle to worry about.
    """

    def repl(m: re.Match[str]) -> str:
        svg = _SVG_CACHE.get(m.group("key"))
        return svg if svg is not None else m.group(0)

    return _IMG_SVG_RE.sub(repl, html)


# ── WIMS domain GIFs (calculator_not.svg, course.svg, …) ────────────────────

import os as _os

# WIMS exercises reference these as e.g. "gifs/domains/general/calculator_not.svg".
# PAX consolidates them into ``ressources/gifs/<file>``. We rewrite the path
# to point at /api/static/gifs/<file> served by the backend.
_GIFS_DIR = _os.path.normpath(
    _os.path.join(_os.path.dirname(__file__), "..", "..", "..", "ressources", "gifs")
)
_WIMS_GIF_IMG_RE = re.compile(
    r'<img(?P<before>[^>]*?)\ssrc=(?P<q>["\']?)gifs/domains/[^/"\'\s]+/(?P<file>[^"\'\s>]+)(?P=q)(?P<after>[^>]*?)>',
    re.IGNORECASE,
)


# ── Module-shared images ($imagedir/../<file>) ──────────────────────────────

import posixpath as _posixpath

# Root of the PAX exercise corpus. URLs we emit are relative to this root,
# served by the FastAPI StaticFiles mount at /api/static.
_RESSOURCES_ROOT = _os.path.normpath(
    _os.path.join(_os.path.dirname(__file__), "..", "..", "..", "ressources")
)

# Matches <img src="pax-img:…/<file>" …> regardless of "../" segments inside.
# The `src=` value can be quoted (single or double) or unquoted — WIMS .def
# templates often write `<img src=$imagedir/foo.jpg>` with no quotes,
# which a strict `"..."` pattern would miss.
_PAX_IMG_RE = re.compile(
    r'<img(?P<before>[^>]*?)\ssrc=(?P<q>["\']?)pax-img:(?P<path>[^"\'\s>]+)(?P=q)(?P<after>[^>]*?)>',
    re.IGNORECASE,
)


def inline_pax_images(html: str, module_dir: str, exercise: str | None = None) -> str:
    """Rewrite ``pax-img:…`` URLs to point at the /api/static mount.

    PAX seeds ``$imagedir`` to the sentinel ``pax-img:_`` so the standard
    WIMS pattern ``$imagedir/../<file>`` becomes ``pax-img:_/../<file>`` in
    the rendered HTML. We extract the basename and locate the file under
    ``<module_dir>/images/`` — directly, in a per-exercise subdirectory
    ``images/<exercise>/`` (oefracine.fr's layout), or anywhere below
    ``images/`` as a last resort — then emit an URL relative to the ressources
    root (served by the backend StaticFiles mount at /api/static).
    """
    images_dir = _os.path.join(module_dir, "images")
    if not _os.path.isdir(images_dir):
        return html

    def _locate(filename: str) -> str | None:
        # 1. flat images/<file>  2. per-exercise images/<exercise>/<file>
        candidates = [_os.path.join(images_dir, filename)]
        if exercise:
            candidates.append(_os.path.join(images_dir, exercise, filename))
        for p in candidates:
            if _os.path.isfile(p):
                return p
        # 3. recursive fallback (first match anywhere under images/). Le
        # parcours est **trié** : `os.walk` rend les dossiers dans l'ordre du
        # système de fichiers, et 14 modules du corpus rangent un même nom de
        # fichier dans plusieurs sous-dossiers — le rendu différait sinon
        # entre un poste et la CI.
        for root, dirs, files in _os.walk(images_dir):
            dirs.sort()
            if filename in files:
                return _os.path.join(root, filename)
        return None

    def repl(m: re.Match[str]) -> str:
        before, after = m.group("before"), m.group("after")
        raw_path = m.group("path")
        # Normalise out "../" segments and dummy "_" placeholders.
        norm = _posixpath.normpath("/" + raw_path).lstrip("/")
        filename = _posixpath.basename(norm)
        if not filename or filename == "_":
            return m.group(0)
        file_path = _locate(filename)
        if not file_path:
            return m.group(0)
        rel = _os.path.relpath(file_path, _RESSOURCES_ROOT).replace(_os.sep, "/")
        return f'<img{before} src="/api/static/{rel}"{after}>'

    return _PAX_IMG_RE.sub(repl, html)


def inline_wims_gifs(html: str) -> str:
    """Rewrite WIMS domain GIF refs (gifs/domains/<dir>/<file>) to /api/static.

    WIMS exercises reference shared icons via paths like
    ``gifs/domains/general/calculator_not.svg``. PAX consolidates them under
    ``ressources/gifs/<file>``; we rewrite the URL to point at the backend's
    /api/static mount so the browser can fetch (and cache) them directly.
    """

    def repl(m: re.Match[str]) -> str:
        before, after = m.group("before"), m.group("after")
        filename = m.group("file")
        # Only rewrite if the file is actually present in ressources/gifs.
        file_path = _os.path.join(_GIFS_DIR, filename)
        if not _os.path.isfile(file_path):
            return m.group(0)
        return f'<img{before} src="/api/static/gifs/{filename}"{after}>'

    return _WIMS_GIF_IMG_RE.sub(repl, html)
