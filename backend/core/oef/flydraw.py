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
import re
import sys
from dataclasses import dataclass, field

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
    "gray": "#808080",
    "green": "#008000",
    "greenyellow": "#adff2f",
    "grey": "#808080",
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

_FONT_SIZES: dict[str, float] = {
    "small": 10,
    "medium": 12,
    "large": 16,
    "giant": 22,
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
    if _ARITH_RE.match(s):
        try:
            return float(eval(s, _NUM_NS))  # noqa: S307
        except Exception:
            # WIMS' flydraw parser tolerates a dangling trailing operator — some
            # generated coords look like "X +" (a tick's x2 in oefcalittaire1
            # branch 5). Evaluate them as just "X" instead of collapsing to 0
            # (which dragged the tick off to the axis as a stray diagonal).
            stripped = s.rstrip(" \t+-*/")
            if stripped and stripped != s:
                try:
                    return float(eval(stripped, _NUM_NS))  # noqa: S307
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
            args.append(arg_str[start:i].strip())
            start = i + 1
    args.append(arg_str[start:].strip())
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
    linewidth: float = 1.0
    crosshairsize: float = 8.0  # WIMS default
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
    # Raw values stashed by `boxplotdata` for use by the next `boxplot`.
    boxplotdata: list[float] = field(default_factory=list)

    def px(self, math_x: float) -> float:
        denom = self.xmax - self.xmin or 1.0
        return (math_x - self.xmin) * self.width / denom

    def py(self, math_y: float) -> float:
        # SVG y grows downward; flip math y (up) to screen y (down).
        denom = self.ymax - self.ymin or 1.0
        return self.height - (math_y - self.ymin) * self.height / denom


# ── Primitive handlers ────────────────────────────────────────────────────────


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
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head = _arrow_marker(state, head_len, color)
    _arrow_segment(state, x1, y1, x2, y2, color, marker_end=head)


def _cmd_arrow2(state: _State, args: list[str]) -> None:
    # arrow2 x1,y1,x2,y2,h,[color] — double-headed arrow (head at both ends).
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
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
    coords = [_num(a) for a in args[2:]]
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
    coords = [_num(a) for a in args[2:]]
    for i in range(0, len(coords) - 3, 4):
        x1, y1, x2, y2 = coords[i], coords[i + 1], coords[i + 2], coords[i + 3]
        _arrow_segment(state, x1, y1, x2, y2, color,
                       marker_end=head, marker_start=head)


def _cmd_darrow(state: _State, args: list[str]) -> None:
    # darrow x1,y1,x2,y2,l,[color] — dashed arrow.
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head = _arrow_marker(state, head_len, color)
    _arrow_segment(state, x1, y1, x2, y2, color, marker_end=head, dashed=True)


def _cmd_darrow2(state: _State, args: list[str]) -> None:
    # darrow2 x1,y1,x2,y2,l,[color] — dashed double-headed arrow.
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
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
    coords = [_num(a) for a in args[1:]]
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
    coords = [_num(a) for a in args[1:]]
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
    n = int(_num(args[6]))
    if n <= 0:
        return
    color = _color(args[7]) if len(args) > 7 else "#000000"
    for i in range(n):
        ox, oy = i * dx, i * dy
        state.segments.append(((x1 + ox, y1 + oy), (x2 + ox, y2 + oy)))
        state.elements.append(
            f'<line x1="{state.px(x1 + ox):.2f}" y1="{state.py(y1 + oy):.2f}" '
            f'x2="{state.px(x2 + ox):.2f}" y2="{state.py(y2 + oy):.2f}" '
            f'stroke="{color}" stroke-width="{state.linewidth}" />'
        )


def _cmd_text(state: _State, args: list[str]) -> None:
    # text [color],x,y,size,content
    if len(args) < 5:
        return
    color = _color(args[0])
    x, y = _num(args[1]), _num(args[2])
    size = _font_size(args[3])
    # Content may contain commas — re-join the tail
    content = ",".join(args[4:]).strip()
    # Drop leftover WIMS variable refs (\name) that were undefined: WIMS renders
    # them empty (e.g. `\c \unit` → "0.4" when `unit` is unset). flydraw text is
    # plain (never LaTeX), so a residual backslash-word is such a ref, not a
    # command.
    content = re.sub(r"\\[A-Za-z]\w*", "", content)
    content = re.sub(r"\s{2,}", " ", content).strip()
    state.elements.append(
        f'<text x="{state.px(x):.2f}" y="{state.py(y):.2f}" fill="{color}" '
        f'font-size="{size}" font-family="sans-serif" '
        f'text-anchor="start" dominant-baseline="hanging">'
        f"{_xml_escape(content)}</text>"
    )


def _cmd_line(state: _State, args: list[str]) -> None:
    # line x1,y1,x2,y2,[color] — INFINITE line through the two points,
    # clipped to the current x/yrange. Used by csga to draw an axis that
    # extends beyond the labelled markers.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
    color = _color(args[4]) if len(args) > 4 else "#000000"

    if x1 == x2:
        # Vertical line — span the full y-range.
        ax, ay = x1, state.ymin
        bx, by = x1, state.ymax
    elif y1 == y2:
        # Horizontal line — span the full x-range.
        ax, ay = state.xmin, y1
        bx, by = state.xmax, y1
    else:
        # General case: y = y1 + m(x - x1). Clip to x-range, then to y-range.
        m = (y2 - y1) / (x2 - x1)
        # Try x = xmin and x = xmax first.
        ax, ay = state.xmin, y1 + m * (state.xmin - x1)
        bx, by = state.xmax, y1 + m * (state.xmax - x1)
        # If those leave the y-range, clip via y boundaries.
        ymin, ymax = state.ymin, state.ymax
        if ay < ymin or ay > ymax:
            target = ymin if ay < ymin else ymax
            ax, ay = x1 + (target - y1) / m, target
        if by < ymin or by > ymax:
            target = ymin if by < ymin else ymax
            bx, by = x1 + (target - y1) / m, target

    state.segments.append(((ax, ay), (bx, by)))
    state.elements.append(
        f'<line x1="{state.px(ax):.2f}" y1="{state.py(ay):.2f}" '
        f'x2="{state.px(bx):.2f}" y2="{state.py(by):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_dsegment(state: _State, args: list[str]) -> None:
    # `dsegment x1,y1,x2,y2,[color]` — DASHED segment (WIMS 'd' prefix = dashed;
    # used for dimension / extension lines). Not recorded in state.segments: a
    # dimension line is not a figure boundary, so it must not feed `flood`.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
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
    coords = [_num(a) for a in args[1:]]
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
    coords = [_num(a) for a in args[1:]]
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
    # Sample the arc as a polyline so we don't have to figure out SVG's
    # convoluted A-command flags from math-coord angles.
    n = max(8, int(abs(end_deg - start_deg) / 5))
    pts = []
    for i in range(n + 1):
        t = start_deg + (end_deg - start_deg) * i / n
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
    coords = [_num(a) for a in args[1:]]
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
    x, y = _num(args[0]), _num(args[1])
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
    coords = [_num(a) for a in args[1:]]
    for i in range(0, len(coords) - 1, 2):
        state.elements.append(
            f'<circle cx="{state.px(coords[i]):.2f}" '
            f'cy="{state.py(coords[i + 1]):.2f}" '
            f'r="{max(state.linewidth / 2, 1):.2f}" '
            f'fill="{color}" stroke="none" />'
        )


def _cmd_circles(state: _State, args: list[str]) -> None:
    # circles [color],x1,y1,r1,x2,y2,r2,... — multiple outline circles.
    if not args:
        return
    color = _color(args[0])
    coords = [_num(a) for a in args[1:]]
    for i in range(0, len(coords) - 2, 3):
        x, y, r = coords[i], coords[i + 1], coords[i + 2]
        state.elements.append(
            f'<circle cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" '
            f'r="{r:.2f}" fill="none" stroke="{color}" '
            f'stroke-width="{state.linewidth}" />'
        )


def _cmd_rect(state: _State, args: list[str]) -> None:
    # rect x1,y1,x2,y2,[color] — outline rectangle, math coords for both corners.
    if len(args) < 4:
        return
    x1, y1, x2, y2 = (_num(a) for a in args[:4])
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
    coords = [_num(a) for a in args[1:]]
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
    y = _num(args[1])
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
    x = _num(args[0])
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
    x, y = _num(args[1]), _num(args[2])
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
    x, y = _num(args[1]), _num(args[2])
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
    # WIMS crosshair = small "×" centered on (x, y), size in pixels (default 8).
    s = state.crosshairsize / 2
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
    x, y = _num(args[0]), _num(args[1])
    color = _color(args[2]) if len(args) > 2 else "#000000"
    state.elements.append(_crosshair_svg(state, x, y, color))


def _cmd_crosshairs(state: _State, args: list[str]) -> None:
    # crosshairs [color],x1,y1,x2,y2,... — multiple × at given points.
    if not args:
        return
    color = _color(args[0])
    coords = [_num(a) for a in args[1:]]
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
    # rotation d — rotate subsequent drawing by d degrees. We don't support
    # the full WIMS matrix stack; rotation is rarely needed and would require
    # wrapping subsequent elements in a <g transform="…">. No-op for now.
    pass


def _cmd_killrotation(state: _State, args: list[str]) -> None:
    # Reset the rotation set by `rotation`. We don't track rotation state →
    # nothing to undo, but recognise the command to keep the log clean.
    pass


def _cmd_trange(state: _State, args: list[str]) -> None:
    # trange t1,t2 — parameter range for parametric plots (used with
    # `plot t,formula(t)`). We don't implement parametric plot mode yet;
    # accept silently to avoid log noise.
    pass


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
    y = _num(args[1])
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
    x = _num(args[0])
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
    # plot [color],[formula] — explicit function of x.
    if len(args) < 2:
        return
    color = _color(args[0])
    formula = ",".join(args[1:]).strip()
    if not formula:
        return
    try:
        import sympy  # noqa: PLC0415
    except ImportError:
        return
    try:
        x_sym = sympy.Symbol("x")
        expr = sympy.sympify(formula.replace("^", "**"))
        f = sympy.lambdify(x_sym, expr, modules=["math"])
    except Exception:
        return

    # Sample the curve and emit a polyline, clipping to the y range.
    n_samples = 200
    step = (state.xmax - state.xmin) / n_samples
    pts: list[str] = []
    for i in range(n_samples + 1):
        x = state.xmin + i * step
        try:
            y = float(f(x))
        except Exception:
            continue
        if y != y or y < state.ymin - 1 or y > state.ymax + 1:
            continue
        pts.append(f"{state.px(x):.2f},{state.py(y):.2f}")
    if len(pts) < 2:
        return
    state.elements.append(
        f'<polyline points="{" ".join(pts)}" fill="none" '
        f'stroke="{color}" stroke-width="{state.linewidth}" />'
    )


def _cmd_circle(state: _State, args: list[str]) -> None:
    # circle x,y,r,[color] — radius in pixels per flydraw spec.
    if len(args) < 3:
        return
    x, y, r = _num(args[0]), _num(args[1]), _num(args[2])
    color = _color(args[3]) if len(args) > 3 else "#000000"
    state.elements.append(
        f'<circle cx="{state.px(x):.2f}" cy="{state.py(y):.2f}" r="{r}" '
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


def _cmd_flood(state: _State, args: list[str]) -> None:
    """flood x,y,[color] — fill the grid cell containing (x,y).

    Strategy: group recorded segments into families of parallel lines (one
    family per direction). For each family, find the closest line ABOVE and
    BELOW the flood point. With 3 families that's 6 candidate lines and
    8 = 2³ ways to pick one from each side. For each combination, compute
    the 3 pairwise intersections — they're the candidate triangle vertices.
    Take the smallest valid triangle that contains (fx, fy). This guarantees
    the polygon's edges lie on actual grid lines (not just on arbitrary
    intersection points) so the fill aligns with the grid cell.
    """
    if len(args) < 2:
        return
    fx, fy = _num(args[0]), _num(args[1])
    color = _color(args[2]) if len(args) > 2 else "#000000"

    # Prefer an explicitly-drawn closed polygon containing the point. This fills
    # arbitrary shapes (e.g. the rhombus in oefcalittaire1) that the
    # triangle-from-segments fallback below can't handle. Smallest match wins so
    # an inner region is preferred over an enclosing one.
    containing = [poly for poly in state.polygons if _point_in_polygon((fx, fy), poly)]
    if containing:
        poly = min(containing, key=_polygon_area)
        pts = " ".join(f"{state.px(x):.2f},{state.py(y):.2f}" for x, y in poly)
        # Insert behind the outline/labels so the stroked border stays visible.
        state.elements.insert(0, f'<polygon points="{pts}" fill="{color}" stroke="none" />')
        return

    # Pie/wheel sector (spokes from a hub inside an ellipse) — the families
    # logic below can't handle it because every spoke pair meets at the hub.
    sector = _sector_fill_polygon(state, fx, fy)
    if sector is not None:
        pts = " ".join(f"{state.px(x):.2f},{state.py(y):.2f}" for x, y in sector)
        state.elements.insert(0, f'<polygon points="{pts}" fill="{color}" stroke="none" />')
        return

    if not state.segments:
        return

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
        return

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
            return
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
        return

    pts = " ".join(f"{state.px(p[0]):.2f},{state.py(p[1]):.2f}" for p in best)
    state.elements.insert(0, f'<polygon points="{pts}" fill="{color}" stroke="none" />')


def _xml_escape(s: str) -> str:
    return (
        s.replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
        .replace('"', "&quot;")
    )


_HANDLERS = {
    # Range / canvas
    "range": _cmd_range,
    "xrange": _cmd_xrange,
    "yrange": _cmd_yrange,
    "size": _cmd_size,
    "linewidth": _cmd_linewidth,
    "transparent": _cmd_transparent,
    "rotation": _cmd_rotation,
    "killrotation": _cmd_killrotation,
    "trange": _cmd_trange,
    "crosshair": _cmd_crosshair,
    "crosshairs": _cmd_crosshairs,
    "crosshairsize": _cmd_crosshairsize,
    # Lines / segments
    "segment": _cmd_segment,
    "segments": _cmd_segments,
    "dsegment": _cmd_dsegment,
    "line": _cmd_line,
    "lines": _cmd_lines,
    "dline": _cmd_dline,
    "dlines": _cmd_dlines,
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
    "arc": _cmd_arc,
    # Fill
    "fill": _cmd_flood,
    "flood": _cmd_flood,
    "gridfill": _cmd_gridfill,
    # Text / plot
    "text": _cmd_text,
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


def flydraw_to_svg(width: int, height: int, commands: str) -> str:
    """Render a flydraw command list to an SVG string.

    Commands may be separated by newline, tab, or semicolon — matching
    WIMS flydraw's ``ggetline`` (``flylines.c``), and matching how the
    .def-baked WIMS-script packs multiple commands on one line via tabs.

    When no xrange/yrange is set, coordinates are interpreted as pixels with
    (0, 0) at the top-left (HTML5 canvas convention). xrange/yrange commands
    override that default and switch to math coordinates.
    """
    w, h = int(width), int(height)
    # Pixel-mode defaults: ymin=h, ymax=0 inverts the y-flip in py() so that
    # raw pixel y values pass through unchanged.
    state = _State(width=w, height=h, xmin=0, xmax=w, ymin=h, ymax=0)
    raw_lines = re.split(r"[\n\t;]", commands)
    for raw in raw_lines:
        line = raw.strip().rstrip("\\").strip()
        if not line or line.startswith("#"):
            continue
        m = re.match(r"^(\w+)\s*(.*)$", line)
        if not m:
            continue
        cmd = m.group(1).lower()
        arg_str = m.group(2)
        args = _split_args(arg_str) if arg_str else []
        handler = _HANDLERS.get(cmd)
        if handler:
            handler(state, args)
        else:
            _log_unhandled_cmd(cmd, arg_str)

    body = "".join(state.elements)
    return (
        f'<svg xmlns="http://www.w3.org/2000/svg" '
        f'width="{state.width}" height="{state.height}" '
        f'viewBox="0 0 {state.width} {state.height}">{body}</svg>'
    )


# Module-level cache: a hash → SVG string. The backend route
# ``/api/render/svg/{id}`` reads from this. The cache lives for the
# process lifetime; it's small (hundreds of bytes per SVG) so we don't
# bother evicting.
_SVG_CACHE: dict[str, str] = {}


def flydraw_to_url(width: int, height: int, commands: str) -> str:
    """Render commands, cache the SVG, and return a comma-free URL.

    A data URI would contain ``,`` (between ``;base64`` and the data), which
    would break WIMS-script's comma-separated list handling further upstream
    (``!shuffle``, ``!positionof``). Instead, we hash the rendered SVG, cache
    it, and emit ``/api/render/svg/<hash>``.
    """
    svg = flydraw_to_svg(width, height, commands)
    key = hashlib.sha1(svg.encode("utf-8")).hexdigest()[:16]
    _SVG_CACHE[key] = svg
    return f"/api/render/svg/{key}"


def get_cached_svg(key: str) -> str | None:
    return _SVG_CACHE.get(key)


_IMG_SVG_RE = re.compile(r'<img\s+src="/api/render/svg/(?P<key>[a-f0-9]+)"[^>]*/?>')


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


def inline_pax_images(html: str, module_dir: str) -> str:
    """Rewrite ``pax-img:…`` URLs to point at the /api/static mount.

    PAX seeds ``$imagedir`` to the sentinel ``pax-img:_`` so the standard
    WIMS pattern ``$imagedir/../<file>`` becomes ``pax-img:_/../<file>`` in
    the rendered HTML. We extract the basename, locate the file in
    ``<module_dir>/images/``, and emit an URL relative to the ressources
    root (served by the backend StaticFiles mount at /api/static).
    """
    images_dir = _os.path.join(module_dir, "images")
    if not _os.path.isdir(images_dir):
        return html

    def repl(m: re.Match[str]) -> str:
        before, after = m.group("before"), m.group("after")
        raw_path = m.group("path")
        # Normalise out "../" segments and dummy "_" placeholders.
        norm = _posixpath.normpath("/" + raw_path).lstrip("/")
        filename = _posixpath.basename(norm)
        if not filename or filename == "_":
            return m.group(0)
        file_path = _os.path.join(images_dir, filename)
        if not _os.path.isfile(file_path):
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
