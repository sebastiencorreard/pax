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
import re
from dataclasses import dataclass, field

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
    try:
        return float(s)
    except ValueError:
        pass
    if _ARITH_RE.match(s):
        try:
            return float(eval(s, _NUM_NS))  # noqa: S307
        except Exception:
            return 0.0
    return 0.0


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
    elements: list[str] = field(default_factory=list)
    segments: list[_Seg] = field(default_factory=list)
    width: int = 300
    height: int = 80

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


def _cmd_arrow(state: _State, args: list[str]) -> None:
    # arrow x1,y1,x2,y2,arrowhead_pixels,[color]
    if len(args) < 5:
        return
    x1, y1, x2, y2, head_len = (_num(a) for a in args[:5])
    color = _color(args[5]) if len(args) > 5 else "#000000"
    head_id = f"ah{len(state.elements)}"
    head_size = max(head_len / 2, 4)
    state.elements.append(
        f'<defs><marker id="{head_id}" viewBox="0 0 10 10" refX="10" refY="5" '
        f'markerWidth="{head_size}" markerHeight="{head_size}" '
        f'orient="auto-start-reverse" markerUnits="userSpaceOnUse">'
        f'<path d="M 0 0 L 10 5 L 0 10 z" fill="{color}" /></marker></defs>'
    )
    state.elements.append(
        f'<line x1="{state.px(x1):.2f}" y1="{state.py(y1):.2f}" '
        f'x2="{state.px(x2):.2f}" y2="{state.py(y2):.2f}" '
        f'stroke="{color}" stroke-width="{state.linewidth}" '
        f'marker-end="url(#{head_id})" />'
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
    state.elements.append(
        f'<text x="{state.px(x):.2f}" y="{state.py(y):.2f}" fill="{color}" '
        f'font-size="{size}" font-family="sans-serif" '
        f'text-anchor="start" dominant-baseline="hanging">'
        f"{_xml_escape(content)}</text>"
    )


def _cmd_line(state: _State, args: list[str]) -> None:
    # `line` in flydraw is an infinite line through two points; in our
    # exercises it's used the same way as `segment` — render as segment.
    _cmd_segment(state, args)


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
    "range": _cmd_range,
    "xrange": _cmd_xrange,
    "yrange": _cmd_yrange,
    "linewidth": _cmd_linewidth,
    "segment": _cmd_segment,
    "arrow": _cmd_arrow,
    "parallel": _cmd_parallel,
    "text": _cmd_text,
    "line": _cmd_line,
    "hline": _cmd_hline,
    "vline": _cmd_vline,
    "circle": _cmd_circle,
    "flood": _cmd_flood,
    "gridfill": _cmd_gridfill,
    "plot": _cmd_plot,
}


# ── Public API ────────────────────────────────────────────────────────────────


def flydraw_to_svg(width: int, height: int, commands: str) -> str:
    """Render a flydraw command list to an SVG string.

    Commands may be separated by newline, tab, or semicolon — matching
    WIMS flydraw's ``ggetline`` (``flylines.c``), and matching how the
    .def-baked WIMS-script packs multiple commands on one line via tabs.
    """
    state = _State(width=int(width), height=int(height))
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
        args = [a.strip() for a in arg_str.split(",")] if arg_str else []
        handler = _HANDLERS.get(cmd)
        if handler:
            handler(state, args)

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
