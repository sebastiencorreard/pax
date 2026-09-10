"""`e` et `subst(x=a, expr)` dans le Maxima émulé.

WIMS envoie à Maxima un en-tête qui pose `e:%e` (`src/Interfaces/maxima.c`) :
`e` y est la constante d'Euler, jamais une variable. Et la primitive évaluée
entre deux bornes s'y écrit `subst(x=b,F)-subst(x=a,F)`, forme que Python ne
lit pas telle quelle.
"""
import sympy

from core.answer.checkers import check_answer
from core.oef.def_engine.cas import _call_maxima, _reecrire_subst_equation


def _vaut(sortie: str, attendu) -> bool:
    return sympy.simplify(sympy.sympify(sortie) - attendu) == 0


class TestConstanteE:
    def test_primitive_d_une_exponentielle(self):
        # Lu comme un symbole, `e` donnait `Piecewise((… /log(e), …))`.
        sortie = _call_maxima("integrate(2*e^(-x-3),x);")
        assert "Piecewise" not in sortie and "log" not in sortie
        x = sympy.Symbol("x")
        assert _vaut(sortie, -2 * sympy.exp(-x - 3))

    def test_integrale_definie(self):
        assert _vaut(_call_maxima("integrate(e^x,x,0,1);"), sympy.E - 1)

    def test_borne_infinie(self):
        # oefprobtes/loiexpo1 : espérance d'une loi exponentielle de paramètre 6.
        assert _vaut(_call_maxima("integrate(x*6*e^(-6*x),x,0,inf);"), sympy.Rational(1, 6))

    def test_inf_reste_un_symbole_hors_des_bornes(self):
        # inequations/ineqlin1 : la borne `-inf` comparée à la réponse `-inf`.
        assert _call_maxima("fullratsimp(-inf-(-inf));") == "0"

    def test_limites_infinies_ecrites_a_la_maxima(self):
        # limpolfrac compare la sortie au texte `minf`.
        assert _call_maxima("limit((-3*x^3),x,inf)") == "minf"
        assert _call_maxima("limit((x^2),x,minf)") == "inf"
        assert _call_maxima("limit((x^3+5*x+1)/(5*x^3+5*x),x,inf)") == "1/5"

    def test_equation_simplifiee_membre_a_membre(self):
        # OEFgeospace/interobjplan : l'appel repartait tel quel dans le TeX.
        sortie = _call_maxima("fullratsimp(y-4-sqrt((4)^2-(-2--1)^2)=0)")
        gauche, _, droite = sortie.partition(" = ")
        y = sympy.Symbol("y")
        assert _vaut(gauche, y - 4 - sympy.sqrt(15)) and droite == "0"

    def test_un_symbole_libre_s_evalue_en_lui_meme(self):
        # OEFexpalgTS/eqexpo1 compare ensuite le résultat au mot `vide`.
        assert _call_maxima("vide") == "vide"


class TestSubstEquation:
    def test_reecriture(self):
        assert _reecrire_subst_equation("subst(x=-3,x*y)") == "_subst_eq(x,-3,x*y)"

    def test_la_forme_a_trois_arguments_reste(self):
        assert _reecrire_subst_equation("subst(2,x,x^2)") == "subst(2,x,x^2)"

    def test_difference_de_deux_substitutions(self):
        # oefinteg1/Calculintgral3 : F(-3) - F(-4) avec F = x e^(-2x).
        sortie = _call_maxima("subst(x=-3,x*exp(-2*x))-subst(x=-4,x*exp(-2*x));")
        assert _vaut(sortie, -3 * sympy.exp(6) + 4 * sympy.exp(8))

    def test_substitution_imbriquee(self):
        sortie = _call_maxima("expand(subst(x=2,x^2+subst(y=1,x*y)));")
        assert sortie == "6"


class TestNumeriqueAvecFonctions:
    """`anstype/numeric` évalue la réponse par `$[…]`, fonctions comprises."""

    def test_calculintgral3_accepte_son_attendu(self):
        opts = {"precision": 10000.0, "computeanswer": "yes"}
        attendu = "(-3 + 4*exp(2))*exp(6)"
        assert check_answer("auto", attendu, attendu, opts, "fr").correct
        assert check_answer("auto", "-3*exp(6)+4*exp(8)", attendu, opts, "fr").correct
        assert not check_answer("auto", "-3*exp(6)+4*exp(7)", attendu, opts, "fr").correct

    def test_computeanswer_no_refuse_toujours_le_calcul(self):
        # `default` passe la main à `numeric`, garde compris : sans
        # `\computeanswer{yes}`, une expression n'est pas une valeur.
        r = check_answer("auto", "-3*exp(6)+4*exp(8)", "8.84e5", {}, "fr")
        assert not r.correct and r.status == "invalid_format"
