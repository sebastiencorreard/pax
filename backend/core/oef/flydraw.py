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

_COLORS: dict[str, str] = {
    "black": "#000000",
    "white": "#ffffff",
    "red": "#ff0000",
    "green": "#008000",
    "blue": "#0000ff",
    "yellow": "#ffff00",
    "orange": "#ffa500",
    "purple": "#800080",
    "magenta": "#ff00ff",
    "cyan": "#00ffff",
    "grey": "#808080",
    "gray": "#808080",
    "lightgrey": "#d3d3d3",
    "lightgray": "#d3d3d3",
    "darkgrey": "#404040",
    "darkgray": "#404040",
    "pink": "#ffc0cb",
    "brown": "#a52a2a",
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


_ARITH_RE = re.compile(r"^[\d\s+\-*/.()e]+$")


def _num(s: str) -> float:
    """Parse a flydraw numeric arg, evaluating simple arithmetic.

    WIMS slib scripts emit args like ``-15-2`` (i.e. ``$s_xmin-2`` after
    substitution); flydraw itself evaluates these. We do the same with a
    restricted ``eval``.
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
            return float(eval(s, {"__builtins__": {}}))  # noqa: S307
        except Exception:
            return 0.0
    return 0.0


# ── Renderer state ────────────────────────────────────────────────────────────


@dataclass
class _State:
    """Renderer state.

    The output SVG uses pixel coordinates (``viewBox="0 0 width height"``)
    so that ``font-size``, arrow head sizes, and ``stroke-width`` stay in
    pixels regardless of the math range. Math coordinates are projected to
    pixels via :py:meth:`px` / :py:meth:`py`.
    """

    xmin: float = -5.0
    xmax: float = 5.0
    ymin: float = -5.0
    ymax: float = 5.0
    linewidth: float = 1.0
    elements: list[str] = field(default_factory=list)
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


def _xml_escape(s: str) -> str:
    return (
        s.replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
        .replace('"', "&quot;")
    )


_HANDLERS = {
    "range": _cmd_range,
    "linewidth": _cmd_linewidth,
    "segment": _cmd_segment,
    "arrow": _cmd_arrow,
    "parallel": _cmd_parallel,
    "text": _cmd_text,
    "line": _cmd_line,
}


# ── Public API ────────────────────────────────────────────────────────────────


def flydraw_to_svg(width: int, height: int, commands: str) -> str:
    """Render a flydraw command list to an SVG string."""
    state = _State(width=int(width), height=int(height))
    for raw in commands.splitlines():
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
