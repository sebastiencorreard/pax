"""`!exec graphviz` — le port de `public_html/bin/graphviz`.

Le script de WIMS écrit le graphe dans un fichier, lance le moteur de
Graphviz (`dot`, ou `neato`, `circo`, `fdp`, `twopi` selon `graphviz_format`)
et rend, ligne à ligne :

    <URL de l'image>
    <largeur>,<hauteur>          (ce que mesure `identify`)
    <sortie -Tplain>             (les coordonnées des nœuds)

ou, si `graphviz_output` vaut `svg`, le SVG lui-même suivi d'une ligne
`plain` puis de la sortie `-Tplain`. `slib/graph/graphviz` et
`slib/draw/graphviz` lisent la première ligne ; `slib/draw/graphvizpoints`
tire de la taille et des coordonnées les points cliquables des nœuds.

Graphviz n'est pas dans WIMS : c'est un logiciel à part, que le serveur
installe (paquet `graphviz` du `Dockerfile`). PAX rend toujours du SVG — mis
en cache comme une figure flydraw — à la taille en pixels du PNG que WIMS
aurait produit (96 points par pouce), pour que les coordonnées de
`graphvizpoints` tombent au même endroit.

Binaire absent ou graphe refusé : la chaîne vide, comme avant le portage.
"""

from __future__ import annotations

import functools
import hashlib
import re
import shutil
import subprocess

# Les moteurs que le script accepte ; tout autre retombe sur `dot`.
_MOTEURS = ("dot", "neato", "circo", "fdp", "twopi")
# `dot -Tpng` rend à 96 ppp une mise en page exprimée en points (1/72 po).
_PX_PAR_PT = 96 / 72
_DELAI = 10  # secondes : un graphe du corpus se met en page en quelques ms
_TAILLE_RE = re.compile(r'<svg\b[^>]*?\bwidth="([\d.]+)pt"[^>]*?\bheight="([\d.]+)pt"')


@functools.lru_cache(maxsize=256)
def _lancer(moteur: str, entree: str, format_: str) -> str | None:
    binaire = shutil.which(moteur)
    if binaire is None:
        return None
    try:
        fini = subprocess.run(
            [binaire, f"-T{format_}", "-Gcharset=UTF-8"],
            input=entree.encode("utf-8"),
            capture_output=True,
            timeout=_DELAI,
            check=False,
        )
    except (OSError, subprocess.TimeoutExpired):
        return None
    if fini.returncode != 0:
        return None
    return fini.stdout.decode("utf-8", errors="replace")


def _svg_en_pixels(svg: str) -> tuple[str, int, int] | None:
    """Le `<svg>` nu (sans prologue XML ni DOCTYPE), dimensionné en pixels."""
    debut = svg.find("<svg")
    if debut < 0:
        return None
    svg = svg[debut:].strip()
    m = _TAILLE_RE.search(svg)
    if not m:
        return None
    w = round(float(m.group(1)) * _PX_PAR_PT)
    h = round(float(m.group(2)) * _PX_PAR_PT)
    svg = svg.replace(f'width="{m.group(1)}pt"', f'width="{w}"', 1)
    svg = svg.replace(f'height="{m.group(2)}pt"', f'height="{h}"', 1)
    # Les commentaires de Graphviz (`<!-- 1 -->`, un par nœud) ne servent à
    # rien ici, et gêneraient les passes qui découpent le HTML de l'énoncé.
    svg = re.sub(r"<!--.*?-->", "", svg, flags=re.S)
    # Graphviz tait le noir d'un texte (`fill` par défaut) mais écrit tout le
    # reste. Le thème sombre, qui n'adapte que les couleurs **écrites**,
    # assombrissait alors le fond en laissant le texte noir dessus :
    # `oefproba/ex` devenait illisible. Le noir, écrit, s'inverse avec le fond.
    svg = re.sub(r"<text\b(?![^>]*\bfill=)", '<text fill="#000000"', svg)
    return svg, w, h


def graphviz(entree: str, moteur: str = "", sortie: str = "") -> str:
    """La sortie de `bin/graphviz` pour ce graphe, ou `""`."""
    from ..flydraw import _SVG_CACHE  # noqa: PLC0415

    moteur = moteur.strip() if moteur.strip() in _MOTEURS else "dot"
    entree = entree.strip()
    if not entree:
        return ""
    brut = _lancer(moteur, entree, "svg")
    plain = _lancer(moteur, entree, "plain")
    if brut is None or plain is None:
        return ""
    lu = _svg_en_pixels(brut)
    if lu is None:
        return ""
    svg, w, h = lu
    if sortie.strip() == "svg":
        return f"{svg}\nplain\n{plain}"
    cle = hashlib.sha1(svg.encode("utf-8")).hexdigest()[:16]
    _SVG_CACHE[cle] = svg
    return f"/api/render/svg/{cle}\n{w},{h}\n{plain}"
