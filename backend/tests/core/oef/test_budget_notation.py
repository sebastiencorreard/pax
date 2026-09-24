"""La notation ne doit pas pouvoir être tenue en otage par une réponse.

`run_analyze` rejoue `:postdef` et `:test` avec la réponse de l'élève, que
l'auteur fait parfois entrer dans un calcul. Deux cas relevés le 2026-09-24 en
sondant les 882 exercices notés par `:test` sans référence :

- `oefnumeration/mult` écrit `!exec float_calc obase=$val20; ibase=$val20; …`,
  `val20` étant la réponse. Une réponse `1` faisait tourner la conversion en
  base 1 sans fin, jusqu'à épuiser la mémoire du serveur ;
- la notation n'avait aucun budget de temps, là où le rendu en a un.
"""

import time

from core.oef.def_engine import analyze as module_analyze
from core.oef.def_engine import check_analyze
from core.oef.def_engine.programmes import float_calc
from core.oef.def_parser import Assign, ForLoop


class TestFloatCalc:
    """Confronté à GNU `bc` 1.07 : les bases hors bornes y sont ramenées."""

    def test_bases_trop_petites_ramenees_a_2(self):
        # `bc` : « obase too small, set to 2 » — et `12` en base 2 vaut 3.
        for b in ("1", "0", "-3"):
            assert float_calc(f"obase={b}; ibase={b}; 12*13") == "1001"

    def test_bases_trop_grandes(self):
        assert float_calc("ibase=40; 12") == "38"
        assert float_calc("obase=100000; ibase=10; 12*13") == " 00156"

    def test_puissance_demesuree_refusee(self):
        debut = time.monotonic()
        assert float_calc("obase=9^9^9; 5") == ""
        assert float_calc("2^99999999") == ""
        assert time.monotonic() - debut < 1

    def test_usage_du_corpus_intact(self):
        assert float_calc("obase=7; ibase=10; 48") == "66"
        assert float_calc("obase=5; ibase=5; 12 + 3") == "20"


def test_la_notation_a_un_budget(monkeypatch):
    monkeypatch.setattr(module_analyze, "_CHECK_TIME_BUDGET", 0.2)
    boucle = [ForLoop(var="i", range_expr="1 to 100000000",
                      body=[Assign(name="x", value="$i")])]
    # Une condition déjà acquise avant l'arrêt ne doit pas compter.
    test = [Assign(name="condtest1", value="1")] + boucle
    debut = time.monotonic()
    condtest, poids = check_analyze({}, [], test, {}, seed=1)
    assert time.monotonic() - debut < 2
    assert condtest == {} and poids == {}
