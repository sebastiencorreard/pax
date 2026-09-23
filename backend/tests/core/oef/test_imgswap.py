"""Figures échangées par une carte d'image — `core/oef/imgswap.py`.

Sept exercices de physique règlent la base de temps d'un oscilloscope par un
bouton + / − : une carte d'image et un script qui échange la `src` des images.
PAX n'exécute pas ce script ; il le lit et livre toutes les vues. Sans cela,
l'élève restait sur la base de 500 ms/c, où la période est illisible.
"""

import os
import re

import pytest

from core.oef.flydraw import _SVG_CACHE
from core.oef.imgswap import port_imgswap
from core.oef.def_engine import load_and_render

_SVG = '<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="{h}"></svg>'


def _cle(nom: str, w: int = 100, h: int = 100) -> str:
    cle = f"{abs(hash(nom)) & 0xffffffff:08x}"
    _SVG_CACHE[cle] = _SVG.format(w=w, h=h)
    return f"/api/render/svg/{cle}"


def _enonce(extra_js: str = "", href_plus: str = "javascript:inc_choix();redraw();") -> str:
    ecrans = [_cle(f"e{i}", 400, 400) for i in range(3)]
    boutons = [_cle(f"b{i}", 150, 100) for i in range(3)]
    js = "  var ecran = new Array(3);  var bouton = new Array(3);  var choix = 0;\n"
    for i in range(3):
        js += f" /* bug wims */ ecran[{i + 1}-1] = '{ecrans[i]}';\n"
        js += f"  bouton[{i + 1}-1] = '{boutons[i]}';\n"
    js += (
        "  function inc_choix(){ if (choix < 2){ choix = choix + 1; } }\n"
        "  function dec_choix(){ if (choix > 0){ choix = choix - 1; } }\n"
        "  function redraw(){ document.images['ecran'].src=ecran[choix];\n"
        "      document.images['bouton'].src=bouton[choix]; }\n" + extra_js
    )
    return (
        f'<script language="javascript">{js}</script>'
        '<map name="map1">'
        '<area shape="rect" coords="0,0,76,100" title="tourne à gauche" '
        'href="javascript:dec_choix();redraw();">'
        f'<area shape="rect" coords="76,0,150,100" title="tourne à droite" href="{href_plus}">'
        '</map>'
        f'<td><img src="{ecrans[0]}" name="ecran"></td>'
        f"<img src='{boutons[0]}' name='bouton' border='0' usemap='#map1'>"
    )


class TestPortImgswap:
    def test_idiome_reconnu(self):
        out = port_imgswap(_enonce())
        assert "<script" not in out and "<map" not in out
        assert out.count('class="pax-swap"') == 2
        assert out.count("pax-swap-frame") == 6
        # Une seule vue visible par image : la première, comme `choix = 0`.
        assert out.count("pax-swap-frame\" hidden") == 4
        # Les vues restent des marqueurs : `inline_svg_imgs` les incorporera.
        assert out.count("/api/render/svg/") == 6

    def test_zones_en_pourcentages_de_l_image_qui_porte_la_carte(self):
        out = port_imgswap(_enonce())
        zones = re.findall(r'data-swap-step="(-?1)" style="([^"]*)"', out)
        assert zones == [
            ("-1", "left:0.00%;top:0.00%;width:50.67%;height:100.00%"),
            ("1", "left:50.67%;top:0.00%;width:49.33%;height:100.00%"),
        ]
        assert 'aria-label="tourne à gauche"' in out

    def test_script_qui_fait_autre_chose_reste_intact(self):
        # Mieux vaut un bouton inerte qu'un bouton qui ment : un script dont
        # une ligne échappe à l'idiome n'est pas traduit.
        html = _enonce(extra_js="  alert('coucou');\n")
        assert port_imgswap(html) == html

    def test_zone_qui_appelle_une_fonction_inconnue(self):
        html = _enonce(href_plus="javascript:autre();redraw();")
        assert port_imgswap(html) == html

    def test_sans_carte_rien_ne_change(self):
        html = "<p>Un énoncé <img src='/x.png' name='ecran'></p>"
        assert port_imgswap(html) == html


_PERIODE = "/ressources/H4/physics/temps.fr/def/periodefrequence.def"


@pytest.mark.skipif(not os.path.isfile(_PERIODE), reason="corpus absent")
def test_oscilloscope_de_periodefrequence():
    html = load_and_render(_PERIODE, seed=1).statement_html
    assert "<script" not in html.lower() and "<map" not in html
    assert html.count("pax-swap-frame") == 16  # 8 écrans, 8 boutons
    assert html.count("pax-swap-zone") == 2
    # Toutes les vues sont incorporées : la route `/api/render/svg` n'existe pas.
    assert "/api/render/svg/" not in html
