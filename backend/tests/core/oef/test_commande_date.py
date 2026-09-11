"""`!date` lit l'horloge du rendu, que `PAX_WIMS_NOW` gèle.

`oefcalcLP/facture1` date sa facture par `!date +%d`, `+%m`, `+%Y` : lue sur
l'horloge du système, sa référence changeait chaque jour.
"""
from core.oef.def_engine import DefEngine


def test_date_gelee(monkeypatch):
    monkeypatch.setenv("PAX_WIMS_NOW", "20240229.03:04:05")
    e = DefEngine(seed=1)
    assert e._eval_cmd("date", "+%d") == "29"
    assert e._eval_cmd("date", "+%m") == "02"
    assert e._eval_cmd("date", "+%Y") == "2024"


def test_format_par_defaut(monkeypatch):
    monkeypatch.setenv("PAX_WIMS_NOW", "20240229.03:04:05")
    assert DefEngine(seed=1)._eval_cmd("date", "") == "2024-02-29"
