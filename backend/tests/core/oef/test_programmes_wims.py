"""`moneyprint`, `float_calc` et `lceb` — trois binaires WIMS portés en Python.

Les attendus de `moneyprint` sont les exemples de l'en-tête de
`src/Misc/moneyprint/moneyprint.c` (sauf la notation scientifique, que le code
écrit `*10^` depuis 2012) ; ceux de `float_calc` suivent `bc` ; ceux de `lceb`
se déroulent à la main dans l'ordre de génération de `lceb_dynopt.c`.
"""
from core.oef.def_engine import DefEngine
from core.oef.def_engine.programmes import float_calc, lceb, moneyprint


class TestMoneyprint:
    def test_deux_decimales_par_defaut(self):
        assert moneyprint("0.1,17,123.4,123.99765") == "0.10,17.00,123.40,124.00"

    def test_nombre_de_decimales(self):
        assert moneyprint("2.1,4.123,5 4") == "2.1000,4.1230,5.0000"

    def test_les_points_virgules_sont_conserves(self):
        assert moneyprint("1,2,3;4,5,6") == "1.00,2.00,3.00;4.00,5.00,6.00"

    def test_la_correction_evite_de_tronquer(self):
        assert moneyprint("15.625") == "15.63"

    def test_notation_scientifique(self):
        assert moneyprint("1.23456e+06,1.23456*10^6 3") == "1.235*10^06,1.235*10^6"


class TestFloatCalc:
    def test_changement_de_base(self):
        assert float_calc("obase=2; ibase=10; 5") == "101"
        assert float_calc("obase=13; ibase=10; 12") == "C"

    def test_calcul_en_base_b(self):
        # 12 en base 5 vaut 7 ; 7 + 3 = 10, qui s'écrit 20 en base 5.
        assert float_calc("obase=5; ibase=5; 12 + 3") == "20"
        # `10` en base 7 vaut 7 : 7² - 1 = 48, qui s'écrit 66 en base 7.
        assert float_calc("obase=7; ibase=7; 10^2 - 1") == "66"

    def test_le_tab_de_l_appel_ne_gene_pas(self):
        e = DefEngine(seed=1)
        assert e._cmd_exec("float_calc\tobase=2; ibase=10; 6") == "110"


class TestLceb:
    def test_premiere_solution_dans_l_ordre_du_c(self):
        # Paires dans l'ordre (1,2), (1,3)… : la première à donner 10 est
        # (2,5), dont le produit vient après la somme 7.
        sortie = lceb("10 1 2 3 4 5 6")
        lignes = sortie.split("\n")
        assert lignes[0] == "Processing 1 2 3 4 5 6 . Goal : 10"
        assert lignes[1] == "FOUND"
        assert lignes[2:] == ["5 * 2 = 10"]

    def test_mauvais_nombre_d_arguments(self):
        assert lceb("10 1 2").startswith("There should be 7 arguments")

    def test_branchement_dans_exec(self):
        e = DefEngine(seed=1)
        assert e._cmd_exec("lceb 10 1 2 3 4 5 6").split("\n")[1] == "FOUND"
