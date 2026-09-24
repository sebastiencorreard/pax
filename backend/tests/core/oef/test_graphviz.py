"""`!exec graphviz` — le port de `public_html/bin/graphviz`.

Graphviz n'est pas dans WIMS : le serveur l'installe, et l'image de PAX aussi
(`backend/Dockerfile`). Sans le binaire, ces tests sont sautés et l'appel rend
la chaîne vide, comme avant le portage.
"""

import os
import re
import shutil

import pytest

from core.oef.def_engine import DefEngine, load_and_render
from core.oef.def_engine.graphviz import graphviz
from core.oef.flydraw import get_cached_svg

avec_dot = pytest.mark.skipif(shutil.which("dot") is None, reason="Graphviz absent")

_GRAPHE = 'digraph G { rankdir="LR"; 1 -> 2; 2 [label="fin"]; }'


@avec_dot
class TestContrat:
    def test_url_taille_puis_plain(self):
        lignes = graphviz(_GRAPHE).split("\n")
        assert lignes[0].startswith("/api/render/svg/")
        w, h = (int(v) for v in lignes[1].split(","))
        assert lignes[2].startswith("graph ")
        assert any(l.startswith("node 2 ") and '"fin"' not in l and "fin" in l for l in lignes)
        svg = get_cached_svg(lignes[0].rsplit("/", 1)[1])
        # Le SVG porte la taille en pixels du PNG que WIMS aurait mesuré.
        assert f'width="{w}"' in svg and f'height="{h}"' in svg
        assert not svg.startswith("<?xml") and "<!--" not in svg

    def test_sortie_svg(self):
        sortie = graphviz(_GRAPHE, sortie="svg")
        assert sortie.startswith("<svg") and "\nplain\ngraph " in sortie

    def test_moteur_inconnu_retombe_sur_dot(self):
        assert graphviz(_GRAPHE, moteur="rm") == graphviz(_GRAPHE, moteur="dot")

    def test_graphe_refuse(self):
        assert graphviz("ceci n'est pas un graphe {") == ""


def test_words_synonyme_de_word():
    # `calc_list` : `word` et `words` appellent la même fonction C.
    assert DefEngine(seed=1)._eval_value("!words 2 to 3 of a b c d") == "b c"


_LCEB = "/ressources/H2/number/oeflceb.fr/def/graphe0.def"


@avec_dot
@pytest.mark.skipif(not os.path.isfile(_LCEB), reason="corpus absent")
def test_oeflceb_graphe_et_points():
    r = load_and_render(_LCEB, seed=1)
    assert r.statement_html.count('class="graph"') == 1
    e = DefEngine(seed=1, def_path=_LCEB)
    from core.oef.def_engine import _parse_def_cached
    e.render(_parse_def_cached(_LCEB))
    points = e.ctx["val43"].split("\n")
    # `graphvizpoints` : la taille, puis un `x,y,étiquette` par nœud.
    assert re.fullmatch(r"\d+,\d+", points[0])
    noeuds = [p for p in points[1:] if re.match(r"-?[\d.]+,-?[\d.]+,", p)]
    assert len(noeuds) >= 3
    assert all(p.split(",", 2)[2] and "UNKNOWN_CMD" not in p for p in noeuds)
