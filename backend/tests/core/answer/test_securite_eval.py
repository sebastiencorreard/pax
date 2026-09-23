"""La réponse d'un élève ne doit jamais exécuter de code côté serveur.

`sympify`/`parse_expr` de SymPy et le `eval` du moteur exécutent du Python
arbitraire. `core/oef/safe_math.py` refuse en amont l'accès par attribut (`.`
non décimal) et les dunders (`__`) — le seul pivot vers un objet dangereux, les
noms nus étant masqués en `Symbol`. Ces tests vérifient le garde-fou sans jamais
lancer de charge réelle : le témoin ne fait rien, on mesure seulement qu'il
n'est pas appelé.
"""
import os

import pytest

from core.answer.checkers import check_answer
from core.oef.def_engine import DefEngine
from core.oef.safe_math import entree_math_sure, valider_entree_math, EntreeMathRefusee

# Chaînes d'attaque — inertes : aucune n'a d'effet, on ne teste que le refus.
ATTAQUES = [
    "__import__('os').getpid()",
    "().__class__.__base__.__subclasses__()",
    "(1).__class__",
    "x.__class__",
    "sqrt(2).__reduce__()",
]

LEGITIMES = [
    "2*x+1", "3.14", "-5/3", "sqrt(2)/2", "e^x", "1.5e-8", ".5", "3.",
    "sin(x)+cos(x)", "(x+1)*(x-1)", "[1,2,3]", "{1,2,3}", "2*e",
]


class TestValidateur:
    @pytest.mark.parametrize("s", ATTAQUES)
    def test_attaque_refusee(self, s):
        assert not entree_math_sure(s)
        with pytest.raises(EntreeMathRefusee):
            valider_entree_math(s)

    @pytest.mark.parametrize("s", LEGITIMES)
    def test_expression_legitime_acceptee(self, s):
        assert entree_math_sure(s)
        valider_entree_math(s)  # ne lève pas


class TestCheckAnswer:
    @pytest.mark.parametrize("s", ATTAQUES)
    @pytest.mark.parametrize("t", ["default", "algexp", "formal", "numeric", "function"])
    def test_reponse_dangereuse_refusee(self, s, t):
        r = check_answer(t, s, "x+1", {}, "fr")
        assert not r.correct
        assert r.status == "invalid_format"

    def test_le_temoin_n_est_jamais_appele(self, monkeypatch):
        temoin = []
        monkeypatch.setattr(os, "getpid", lambda: (temoin.append(1), 1)[1])
        check_answer("default", "__import__('os').getpid()", "x+1", {}, "fr")
        assert temoin == []

    def test_reponse_legitime_toujours_notee(self):
        # Le garde-fou ne gêne pas une vraie réponse.
        assert check_answer("formal", "2*x+2", "2*(x+1)", {}, "fr").correct

    def test_type_texte_garde_ses_points(self):
        # `atext` n'atteint aucun évaluateur : une phrase avec points passe.
        r = check_answer("atext", "3.5 pommes.", "3.5 pommes.", {}, "fr")
        assert r.correct


class TestMoteur:
    def test_eval_arith_refuse_le_dunder(self):
        e = DefEngine(seed=1)
        # En substitution simple, l'expression dangereuse n'est pas évaluée.
        assert e._eval_value("$[().__class__]") == "().__class__"

    def test_eval_arith_strict_donne_nan(self):
        e = DefEngine(seed=1)
        e._strict_arith = True
        assert e._eval_value("$[().__class__.__base__]") == "NaN"

    def test_le_calcul_normal_marche(self):
        e = DefEngine(seed=1)
        assert e._eval_value("$[2+3*4]") == "14"


class TestFigures:
    """Les figures aussi évaluent : `_num` par `eval`, `plot` et les courbes
    paramétrées par `parse_expr`. Un corrigé peut y insérer la réponse de
    l'élève — `oefrelat` trace `arc 3.6,($val9+\\rep)/…`."""

    def test_le_temoin_n_est_jamais_touche(self, monkeypatch):
        from core.oef import flydraw

        touche = []

        class Temoin:
            def __getattribute__(self, nom):
                touche.append(nom)
                return 0

        monkeypatch.setitem(flydraw._NUM_NS, "x", Temoin())
        assert flydraw._num("x.__class__") == 0.0
        assert flydraw._num("x.real") == 0.0
        assert touche == []

    @pytest.mark.parametrize("s", ATTAQUES)
    def test_plot_refuse(self, s):
        from core.oef.flydraw import flydraw_to_svg
        assert "<polyline" not in flydraw_to_svg(100, 100, f"range -1,1,-1,1\nplot red,{s}")

    def test_figure_legitime_intacte(self):
        from core.oef.flydraw import _num, flydraw_to_svg
        assert _num("2*sin(pi/6)+0.5") == 1.5
        assert "<polyline" in flydraw_to_svg(100, 100, "range -1,1,-1,1\nplot red,x^2-0.5")
