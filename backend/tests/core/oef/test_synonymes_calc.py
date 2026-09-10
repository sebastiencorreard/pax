"""Les synonymes de `calc_list` (`calc.c`) et `!evalsubst`.

Les modules importés de H1, H2, H5 et H6 emploient des noms que H3 et H4
n'employaient pas : `items`, `itemcount`, `position`, `listunique` — autant de
synonymes, dans la table C, d'une commande que PAX connaissait — et
`evalsubst`, qui enchaîne `mathsubst` et `evalue`. Tous tombaient sur
`UNKNOWN_CMD`, visible dans l'énoncé de `derivzoom.fr`.
"""
from core.oef.def_engine import DefEngine


def moteur() -> DefEngine:
    return DefEngine(seed=1)


def test_items_vaut_item():
    e = moteur()
    assert e._eval_cmd("items", "2 of a,b,c") == e._eval_cmd("item", "2 of a,b,c") == "b"


def test_itemcount_vaut_itemcnt():
    e = moteur()
    assert e._eval_cmd("itemcount", "a,b,c") == e._eval_cmd("itemcnt", "a,b,c") == "3"


def test_position_vaut_positionof():
    e = moteur()
    assert e._eval_cmd("position", "b in a,b,c") == e._eval_cmd("positionof", "b in a,b,c")
    assert e._eval_cmd("position", "b in a,b,c") == "2"


def test_listunique_vaut_listuniq():
    e = moteur()
    assert e._eval_cmd("listunique", "a,b,a") == e._eval_cmd("listuniq", "a,b,a")


def test_evalsubst_evalue_la_fonction_au_point():
    e = moteur()
    assert float(e._eval_cmd("evalsubst", "x=2 in x^2+1")) == 5
