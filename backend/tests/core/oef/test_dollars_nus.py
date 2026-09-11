"""`$ $` affecte une espace, comme chez WIMS.

`substit` (`src/evalue.c`) efface un `$` qui n'ouvre aucun nom. Les slibs de
numération s'en servent pour leur séparateur de milliers ; PAX gardait le
texte, et `8$ $000` s'affichait tel quel.
"""
import os

from core.oef.def_engine import DefEngine
from core.oef.def_engine.slib import _dollars_nus

RESSOURCES = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "../../../../ressources")
)
# Un `.def` réel : `_run_slib` cherche `wims-scripts/` en remontant depuis lui.
GRANDEUR = os.path.join(RESSOURCES, "H1/number/OEFevalwimsope.fr/def/oefgrandeuradd3.def")


class TestRegle:
    def test_une_espace(self):
        assert _dollars_nus("$ $") == " "

    def test_hors_de_l_idiome_rien_ne_change(self):
        assert _dollars_nus("$val1") is None
        assert _dollars_nus("a$ $b") is None
        assert _dollars_nus("") is None


class TestEcritureNombre:
    def test_separateur_de_milliers(self):
        e = DefEngine(seed=1, def_path=GRANDEUR)
        e._cmd_readproc("slib/numeration/ecriturenombre 8000")
        assert e.ctx["slib_out"] == "8 000"

    def test_la_somme_de_deux_nombres_ecrits(self):
        # OEFevalwimsope/oefgrandeuradd3 : `val28=$[$val26+$val27]`.
        e = DefEngine(seed=1, def_path=GRANDEUR)
        e._cmd_readproc("slib/numeration/ecriturenombre 8000")
        e.ctx["val26"] = e.ctx["slib_out"]
        e._cmd_readproc("slib/numeration/ecriturenombre 9000")
        e.ctx["val27"] = e.ctx["slib_out"]
        assert e._eval_value("$[$val26+$val27]") == "17000"
