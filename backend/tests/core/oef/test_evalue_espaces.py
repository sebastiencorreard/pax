"""`$[…]` retire toutes les espaces avant d'évaluer, comme WIMS.

`strevalue` (`src/Lib/evalue.c`) : `substitute(buf); nospace(buf);`. Un nombre
écrit avec son séparateur de milliers reste un nombre — `oefsolaire/kepler3a`
tire `384 000` d'un `!item` et le multiplie.
"""
from core.oef.def_engine import DefEngine


def test_separateur_de_milliers():
    e = DefEngine(seed=1)
    assert e._eval_value("$[384 000+1]") == "384001"


def test_espaces_autour_des_operateurs():
    e = DefEngine(seed=1)
    assert e._eval_value("$[ 2 * 3 ]") == "6"


def test_les_zeros_de_tete_ne_mangent_plus_le_nombre():
    # Avant, la règle des zéros de tête lisait ` 000` comme un `0` isolé.
    e = DefEngine(seed=1)
    e.ctx["val13"] = "384 000"
    # 384 000 000 dépasse 10⁶ : `float2str` l'écrit en `%.8g`.
    assert e._eval_value("$[1000*$val13]") == "3.84e+08"
