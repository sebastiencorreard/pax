"""Figures échangées par une carte d'image — l'idiome WIMS, sans son JavaScript.

PAX n'exécute pas les ``<script>`` d'un énoncé. Or sept exercices de physique
(``temps``, ``OEFondes``, ``circuitRC``) règlent la base de temps d'un
oscilloscope par un bouton *+ / −* : huit oscillogrammes pré-calculés dans un
tableau JavaScript, une carte d'image (``<map>``/``<area>``) posée sur l'image
du bouton, et une fonction ``redraw`` qui échange la ``src`` des images. Sans
le script, l'élève reste sur la première base de temps, où la courbe est
illisible, et ne peut pas mesurer la période qu'on lui demande.

Les sept portent le même script, mot pour mot :

    var ecran = new Array(8);  var choix = 0;
    ecran[1-1] = '<figure>'; …
    function inc_choix(){ if (choix < 7){ choix = choix + 1; } }
    function dec_choix(){ if (choix > 0){ choix = choix - 1; } }
    function redraw(){ document.images['ecran'].src=ecran[choix]; … }
    <map name="map1"><area shape="rect" coords="…"
         href="javascript:dec_choix();redraw();"> …</map>

On le **lit** au lieu de l'exécuter. Chaque image nommée par ``redraw`` devient
un ``<span class="pax-swap">`` qui contient toutes ses vues, une seule visible.
Chaque ``<area>`` devient un ``<button class="pax-swap-zone">`` posé en
pourcentages sur l'image qui portait la carte. Le front déplace l'index au
clic (``BaseExerciseStatement.vue``). Aucune ligne de l'auteur ne s'exécute.

La reconnaissance est **stricte** : un script qui contient autre chose que
l'idiome ou une zone qui appelle une fonction inconnue laissent l'énoncé tel
quel. Mieux vaut un bouton inerte qu'un bouton qui ment.
"""

from __future__ import annotations

import html as _html
import re

from .flydraw import _SVG_CACHE

_SCRIPT_RE = re.compile(r"<script\b[^>]*>(.*?)</script>", re.S | re.I)
_MAP_RE = re.compile(r"<map\s+name=[\"']?([\w-]+)[\"']?\s*>(.*?)</map>", re.S | re.I)
_AREA_RE = re.compile(r"<area\b([^>]*)>", re.I)
_IMG_RE = re.compile(r"<img\b[^>]*>", re.I)

_COMMENT_RE = re.compile(r"/\*.*?\*/", re.S)
_NEW_ARRAY_RE = re.compile(r"var\s+\w+\s*=\s*new\s+Array\(\s*\d+\s*\)\s*;")
_VAR_ZERO_RE = re.compile(r"var\s+(\w+)\s*=\s*0\s*;")
# `ecran[3-1] = '…';` — l'indice s'écrit `k-1` parce que la boucle `!for` de
# WIMS déroule `$m_k-1` en texte (le commentaire de l'auteur s'en plaint).
_ELEM_RE = re.compile(r"(\w+)\[\s*(\d+)\s*-\s*1\s*\]\s*=\s*'([^']*)'\s*;")
_STEP_RE = re.compile(
    r"function\s+(\w+)\s*\(\s*\)\s*\{\s*if\s*\(\s*(\w+)\s*([<>])\s*(\d+)\s*\)\s*\{"
    r"\s*(\w+)\s*=\s*(\w+)\s*([+-])\s*1\s*;\s*\}\s*\}"
)
_REDRAW_RE = re.compile(
    r"function\s+(\w+)\s*\(\s*\)\s*\{((?:\s*document\.images\[\s*'\w+'\s*\]\.src"
    r"\s*=\s*\w+\[\s*\w+\s*\]\s*;)+)\s*\}"
)
_ASSIGN_RE = re.compile(r"document\.images\[\s*'(\w+)'\s*\]\.src\s*=\s*(\w+)\[\s*(\w+)\s*\]")
_HREF_CALLS_RE = re.compile(r"^javascript:\s*(\w+)\(\)\s*;\s*(\w+)\(\)\s*;?\s*$")
_SVG_KEY_RE = re.compile(r"^\s*/api/render/svg/([a-f0-9]+)\s*$")
_SVG_SIZE_RE = re.compile(r"<svg\b[^>]*?\bwidth=\"([\d.]+)\"[^>]*?\bheight=\"([\d.]+)\"")


def _attr(tag: str, name: str) -> str | None:
    m = re.search(rf"\b{name}\s*=\s*(?:\"([^\"]*)\"|'([^']*)'|([^\s>]+))", tag, re.I)
    if not m:
        return None
    return next(g for g in m.groups() if g is not None)


def _parse_script(body: str):
    """Lit le script ; ``None`` s'il contient quoi que ce soit hors idiome."""
    rest = _COMMENT_RE.sub("", body)
    rest = _NEW_ARRAY_RE.sub("", rest)
    counters = set(_VAR_ZERO_RE.findall(rest))
    rest = _VAR_ZERO_RE.sub("", rest)

    arrays: dict[str, dict[int, str]] = {}
    for name, k, val in _ELEM_RE.findall(rest):
        arrays.setdefault(name, {})[int(k) - 1] = val
    rest = _ELEM_RE.sub("", rest)

    steps: dict[str, tuple[str, int, int]] = {}  # fonction → (compteur, pas, borne)
    for fn, var, op, bound, lhs, rhs, sign in _STEP_RE.findall(rest):
        if not (var == lhs == rhs) or var not in counters:
            return None
        pas = 1 if sign == "+" else -1
        # `<` va de pair avec `+`, `>` avec `-` : l'autre combinaison ne borne rien.
        if (op == "<") != (pas == 1):
            return None
        steps[fn] = (var, pas, int(bound))
    rest = _STEP_RE.sub("", rest)

    redraws: dict[str, list[tuple[str, str, str]]] = {}
    for m in _REDRAW_RE.finditer(rest):
        redraws[m.group(1)] = _ASSIGN_RE.findall(m.group(2))
    rest = _REDRAW_RE.sub("", rest)

    if rest.strip() or not steps or len(redraws) != 1:
        return None
    return arrays, steps, redraws


def _frames(values: dict[int, str]) -> list[str] | None:
    n = len(values)
    if n < 2 or sorted(values) != list(range(n)):
        return None
    return [values[i] for i in range(n)]


def _svg_size(url: str) -> tuple[float, float] | None:
    m = _SVG_KEY_RE.match(url)
    svg = _SVG_CACHE.get(m.group(1)) if m else None
    s = _SVG_SIZE_RE.search(svg) if svg else None
    return (float(s.group(1)), float(s.group(2))) if s else None


def port_imgswap(html: str) -> str:
    """Remplace l'idiome carte d'image + ``redraw`` par des vues échangeables.

    À appeler **avant** ``inline_svg_imgs`` : les vues sont émises comme des
    marqueurs ``<img src="/api/render/svg/…">``, que cette passe incorporera
    comme toute autre figure.
    """
    if "<map" not in html.lower() or "document.images" not in html:
        return html
    for group, sm in enumerate(_SCRIPT_RE.finditer(html)):
        parsed = _parse_script(sm.group(1))
        if parsed is None:
            continue
        new = _port_one(html, sm, parsed, f"s{group}")
        if new is not None:
            return new  # un seul idiome par énoncé dans le corpus
    return html


def _port_one(html: str, sm: re.Match, parsed, gid: str) -> str | None:
    arrays, steps, redraws = parsed
    (redraw_fn, assigns), = redraws.items()

    # Image nommée → ses vues. Toutes se déplacent d'un même compteur.
    targets: dict[str, list[str]] = {}
    counters = {var for var, _, _ in steps.values()}
    for img_name, arr, idx in assigns:
        frames = _frames(arrays.get(arr, {}))
        if frames is None or idx not in counters:
            return None
        targets[img_name] = frames
    if len(counters) != 1 or len({len(f) for f in targets.values()}) != 1:
        return None
    n = len(next(iter(targets.values())))
    for _, pas, bound in steps.values():
        if bound != (n - 1 if pas == 1 else 0):
            return None

    # La carte : chaque zone appelle une fonction de pas puis `redraw`.
    maps: dict[str, list[tuple[tuple[float, ...], int, str]]] = {}
    for mm in _MAP_RE.finditer(html):
        zones = []
        for am in _AREA_RE.finditer(mm.group(2)):
            a = am.group(1)
            href = _html.unescape(_attr(a, "href") or "")
            calls = _HREF_CALLS_RE.match(href)
            shape = (_attr(a, "shape") or "rect").lower()
            try:
                coords = tuple(float(c) for c in (_attr(a, "coords") or "").split(","))
            except ValueError:
                return None
            if (not calls or calls.group(1) not in steps or calls.group(2) != redraw_fn
                    or shape != "rect" or len(coords) != 4):
                return None
            label = _attr(a, "title") or _attr(a, "alt") or ""
            zones.append((coords, steps[calls.group(1)][1], label.strip()))
        if zones:
            maps[mm.group(1)] = zones
    if not maps:
        return None

    # Les images : chaque cible nommée, et celle qui porte la carte.
    repl: list[tuple[int, int, str]] = []
    seen: set[str] = set()
    for im in _IMG_RE.finditer(html):
        tag = im.group(0)
        name = _attr(tag, "name")
        if name not in targets:
            continue
        frames = targets[name]
        usemap = (_attr(tag, "usemap") or "").lstrip("#")
        zones_html = ""
        if usemap:
            if usemap not in maps:
                return None
            size = _svg_size(frames[0])
            if size is None:
                return None
            w, h = size
            for (x1, y1, x2, y2), pas, label in maps[usemap]:
                style = (f"left:{100 * x1 / w:.2f}%;top:{100 * y1 / h:.2f}%;"
                         f"width:{100 * (x2 - x1) / w:.2f}%;height:{100 * (y2 - y1) / h:.2f}%")
                lab = _html.escape(label, quote=True)
                zones_html += (f'<button type="button" class="pax-swap-zone" data-swap="{gid}" '
                               f'data-swap-step="{pas}" style="{style}" title="{lab}" '
                               f'aria-label="{lab}"></button>')
        vues = "".join(
            f'<span class="pax-swap-frame"{"" if i == 0 else " hidden"}>'
            f'<img src="{_html.escape(f.strip(), quote=True)}" alt=""></span>'
            for i, f in enumerate(frames)
        )
        repl.append((im.start(), im.end(),
                     f'<span class="pax-swap" data-swap="{gid}">{vues}{zones_html}</span>'))
        seen.add(name)
    if seen != set(targets):
        return None

    # Le script et les cartes disparaissent : ils n'ont plus rien à faire.
    for mm in _MAP_RE.finditer(html):
        if mm.group(1) in maps:
            repl.append((mm.start(), mm.end(), ""))
    repl.append((sm.start(), sm.end(), ""))

    out, pos = [], 0
    for start, end, text in sorted(repl):
        if start < pos:
            return None
        out.append(html[pos:start])
        out.append(text)
        pos = end
    out.append(html[pos:])
    return "".join(out)
