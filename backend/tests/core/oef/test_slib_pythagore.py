"""`slib/pythagore`, portée en natif : la même sortie, sans le budget.

La slib d'`OEFevalwimssecdeg.fr` énumère les triplets pythagoriciens par une
triple boucle. Jusqu'à 100 (`coefracine2|3`), interprétée, elle butait sur le
budget de rendu et tirait dans une liste tronquée — un rendu qui dépendait de
la machine. Le port doit rendre **ce que rend le script**, hasard compris.
"""
import os

import pytest

from core.oef.def_engine import DefEngine

RESSOURCES = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "../../../../ressources")
)
COEFRACINE2 = os.path.join(
    RESSOURCES, "H5/algebra/OEFevalwimssecdeg.fr/def/coefracine2.def"
)
avec_corpus = pytest.mark.skipif(
    not os.path.isfile(COEFRACINE2), reason="corpus absent"
)


@avec_corpus
@pytest.mark.parametrize("borne", [5, 13, 20])
@pytest.mark.parametrize("graine", range(4))
def test_le_port_rend_ce_que_rend_le_script(borne, graine):
    """Petite borne : le script interprété va au bout, on peut comparer."""
    script = DefEngine(graine, COEFRACINE2)
    script._run_slib("slib/pythagore", str(borne))
    port = DefEngine(graine, COEFRACINE2)
    assert port._slib_pythagore(str(borne)) == script.ctx["slib_out"].strip()
    # Un seul tirage des deux côtés : la suite de l'exercice voit le même hasard.
    assert port.rng.random() == script.rng.random()


def test_borne_100_complete():
    """Les triplets jusqu'à 100 — ce que la boucle interprétée n'atteignait pas."""
    vus = set()
    for graine in range(60):
        a, b, c = map(int, DefEngine(graine)._slib_pythagore("100").split(","))
        assert a * a + b * b == c * c and 1 <= a <= 100 and b <= 101
        vus.add((a, b, c))
    # Au-delà de ce que couvrait l'état tronqué (a petit) : des `a` élevés sortent.
    assert max(a for a, _, _ in vus) > 50


def test_parametre_vide():
    assert DefEngine(1)._slib_pythagore("") == ""
