"""`wims_float2str` — l'écriture des réels de `$[…]`, d'après `src/evalue.c`.

    if(d<1000000 && d>-1000000 && d==floor(d)) → entier
    sinon "%.<print_precision>g", print_precision = 8 pour un OEF
"""
import math

from core.oef.def_engine import DefEngine
from core.oef.numfmt import wims_float2str


class TestFloat2str:
    def test_zero(self):
        assert wims_float2str(0.0) == "0"
        assert wims_float2str(-0.0) == "0"

    def test_entier_sous_un_million(self):
        assert wims_float2str(7.0) == "7"
        assert wims_float2str(-999999.0) == "-999999"

    def test_entier_a_partir_d_un_million(self):
        # Hors de la borne, `%.8g` : il tient encore sur 8 chiffres…
        assert wims_float2str(1000000.0) == "1000000"
        assert wims_float2str(12345678) == "12345678"
        # … puis passe en notation scientifique.
        assert wims_float2str(123456789) == "1.2345679e+08"

    def test_huit_chiffres_significatifs(self):
        assert wims_float2str(1 / 3) == "0.33333333"
        assert wims_float2str(2 + 0.9 + 0.05) == "2.95"

    def test_masse_de_la_terre(self):
        # oefsolaire/kepler3a
        assert wims_float2str(6.021511770820834e24) == "6.0215118e+24"

    def test_non_finis(self):
        assert wims_float2str(math.inf) == "Inf"
        assert wims_float2str(-math.inf) == "-Inf"
        assert wims_float2str(math.nan) == "NaN"


class TestFractionAttendue:
    """`_expected_as_fraction` compare la fraction au calcul écrit sur 8 chiffres."""

    def test_la_fraction_rejoint_son_ecriture_a_8_chiffres(self):
        e = DefEngine(seed=1)
        assert e._expected_as_fraction("$[5/3]", "1.6666667") == "5/3"

    def test_une_vraie_divergence_reste_rejetee(self):
        # quizz/course12_2step : l'attendu vaut -0.5, la reconstruction 1/2.
        e = DefEngine(seed=1)
        assert e._expected_as_fraction("$[1/2]", "-0.5") is None


class TestDansLeMoteur:
    def test_dollar_crochet(self):
        e = DefEngine(seed=1)
        assert e._eval_value("$[1/3]") == "0.33333333"
        assert e._eval_value("$[123456789]") == "1.2345679e+08"
        assert e._eval_value("$[2+3]") == "5"
