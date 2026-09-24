"""Le dialecte canvasdraw — ce qui le sépare de flydraw.

Les deux programmes de WIMS lisent la même syntaxe, mais canvasdraw dessine
dans un `<canvas>` HTML5 : opacités par défaut, texte posé sur sa ligne de
base, table de couleurs HTML, repère « quadrant I », et une grille avec ses
axes, sa numérotation, sa légende. Chaque attendu a été relevé sur le vrai
canvasdraw (`wims/src/Misc/canvasdraw`, recompilé sans `_FORTIFY_SOURCE`) et
sur le JS qu'il émet (`draw_grid`, `canvasutils.c`).
"""

import re

from core.oef.flydraw import _tex_en_texte, flydraw_to_svg


def cv(script: str, w: int = 200, h: int = 200) -> str:
    return flydraw_to_svg(w, h, script, dialecte="canvasdraw")


def textes(svg: str) -> list[str]:
    return re.findall(r"<text[^>]*>([^<]*)</text>", svg)


class TestConventions:
    def test_opacites_par_defaut(self):
        svg = cv("xrange -5,5\nyrange -5,5\nfcircle 0,0,20,red")
        assert 'stroke-opacity="0.8"' in svg and 'fill-opacity="0.5"' in svg

    def test_flydraw_reste_opaque(self):
        svg = flydraw_to_svg(200, 200, "xrange -5,5\nyrange -5,5\nfcircle 0,0,20,red")
        assert "opacity" not in svg

    def test_gris_de_la_table_html(self):
        # canvasmacro.c : grey = #808080 ; flydraw (X11) : #bebebe.
        assert "#808080" in cv("xrange -5,5\nyrange -5,5\nsegment 0,0,1,1,grey")

    def test_quadrant_un_sans_range(self):
        # y vers le haut : un point à y = 10 tombe près du **bas** du canvas.
        svg = cv("point 100,10,black")
        cy = float(re.search(r'cy="([\d.]+)"', svg).group(1))
        assert cy == 190

    def test_fontfamily_ne_change_pas_la_taille_des_text(self):
        # `huge` = fontsize (12) + 14, même après `fontfamily bold 15px`.
        svg = cv("xrange -5,5\nyrange -5,5\nfontfamily bold 15px Arial\ntext blue,0,0,huge,A")
        assert 'font-size="26px"' in svg


class TestGrille:
    _BASE = "xrange -1,8\nyrange -1,12\n"

    def test_sans_grid_ni_axes_ni_linegraph(self):
        svg = cv(self._BASE + "axis\naxisnumbering\nlinegraph 0:1:2:3\nlegend L")
        assert "<path" not in svg and not textes(svg)

    def test_la_grille_passe_sous_le_dessin(self):
        svg = cv(self._BASE + "segment 0,0,1,1,red\ngrid 1,1,grey")
        assert svg.index("<path") < svg.index("<line")

    def test_numerotation_sans_zero_et_precision(self):
        svg = cv(self._BASE + "precision 1\naxis\naxisnumbering\ngrid 1,1,grey,1,1,2,black")
        nombres = textes(svg)
        assert "0" not in nombres
        assert {"1", "7", "11"} <= set(nombres)
        # La boucle arrière s'arrête à `p > 0` : −1, au bord gauche, n'est pas
        # écrit (capture WIMS de `evolmeth`).
        assert "-1" not in nombres

    def test_precision_par_defaut_deux_decimales(self):
        svg = cv(self._BASE + "axis\naxisnumbering\ngrid 1,1,grey,1,1,2,black")
        assert "1.00" in textes(svg)

    def test_linegraph_legende_et_noms_des_axes(self):
        svg = cv(self._BASE + "axis\nxlabel temps\nylabel masse\ngrid 1,1,grey,1,1,2,black\n"
                 "linewidth 3\nstrokecolor red\nlinegraph 0:5:1:4:2:1\nlegend Titre")
        assert {"temps", "masse", "Titre"} <= set(textes(svg))
        assert re.search(r'<path d="M[^"]*" fill="none" stroke="#ff0000"[^>]*stroke-width="3"', svg)
        assert 'rotate(-90' in svg

    def test_flydraw_ignore_grid(self):
        svg = flydraw_to_svg(200, 200, self._BASE + "grid 1,1,grey")
        assert "<path" not in svg


class TestObjets:
    def test_curve_est_plot(self):
        assert "<polyline" in cv("xrange -5,5\nyrange -5,5\ncurve blue,x^2") or \
            "<path" in cv("xrange -5,5\nyrange -5,5\ncurve blue,x^2")

    def test_latex_prend_la_couleur_du_dernier_objet(self):
        svg = cv("xrange -5,5\nyrange -5,5\narrow 0,0,1,1,10,#EE0700\nlatex 0,0,\\vec{u}")
        assert re.search(r'<text[^>]*fill="#ee0700"[^>]*>u⃗</text>', svg)

    def test_tex_en_texte(self):
        assert _tex_en_texte(r"-2\vec{u} + 1.5\vec{v}") == "-2u⃗ + 1.5v⃗"
        assert _tex_en_texte(r"\mathcal{D}") == "D"

    def test_pointe_de_fleche_cernee(self):
        svg = cv("xrange -5,5\nyrange -5,5\nlinewidth 4\narrow 0,0,2,0,10,blue")
        assert re.search(r'<marker[^>]*overflow="visible".*?stroke-width="4"', svg)
