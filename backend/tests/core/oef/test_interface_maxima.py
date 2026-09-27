"""L'interface `src/Interfaces/maxima.c` autour du Maxima émulé.

WIMS ne passe pas la commande telle quelle : `check_parm` la met en
minuscules, l'en-tête pose `e:%e`, `i:%i`, `ln:log`, `ch:cosh`… ; et `output()`
rend la ligne en minuscules, `%` changé en espace. Le script reçoit donc
`3*x^2` et `%e^x` devenu `e^x` — jamais le `3*x**2` ni l'`exp(x)` de SymPy,
que `plot` de canvasdraw refuse.
"""
from core.oef.def_engine import DefEngine
from core.oef.def_engine.cas import _call_maxima, _exp_en_puissance


class TestSortie:
    def test_puissance(self):
        assert _call_maxima("diff(x^3,x)") == "3*x^2"

    def test_exponentielle(self):
        assert _call_maxima("diff(exp(2*x),x)") == "2*e^(2*x)"

    def test_exponentielle_elevee_a_une_puissance(self):
        # `^` est associatif à droite : `e^x^2` vaudrait e^(x²).
        assert _exp_en_puissance("exp(x)**2") == "(e^x)**2"

    def test_minuscules(self):
        assert _call_maxima("fullratsimp(abs(x-20)*2)") == "2*abs(x - 20)"

    def test_i_s_ecrit_comme_un_symbole(self):
        # Maxima : `-6*%i-2` ; SymPy rangeait la partie réelle devant.
        assert _call_maxima("fullratsimp(-2+-6*i);") == "-6*i - 2"


class TestEntree:
    def test_majuscules(self):
        # `oefsuites1S/limfrac1` : `INF` se lisait `I*N*F`.
        assert _call_maxima("limit((x^2+4)/(6*x^3),x,INF)") == "0"
        # `OEFfractrou` : `DENOM(…)` repartait tel quel.
        assert _call_maxima("DENOM((x+8)/(x+6));") == "x + 6"

    def test_en_tete(self):
        assert _call_maxima("diff(arctan(x),x);") == "1/(x^2 + 1)"
        assert _call_maxima("fullratsimp(ch(0));") == "1"
        assert _call_maxima("imagpart((i+1)^3)") == "2"

    def test_fonctions_de_maxima(self):
        assert _call_maxima("mod(35,2)") == "1"
        assert _call_maxima("logcontract(log(x)-log(y))") == "log(x/y)"

    def test_un_nom_n_est_jamais_decoupe(self):
        # Une fonction inconnue restait un produit de lettres :
        # `imagpart(…)` rendait `a**2*g*i*m*p*r*t*(…)`.
        assert _call_maxima("fullratsimp(foo(x)+foo(x))") == "2*foo(x)"
        assert _call_maxima("fullratsimp(polroots*2)") == "2*polroots"


class TestRawmath:
    def test_caracteres_remplaces(self):
        # `oefCCF/outil` écrit `x³` puis dérive par Maxima.
        e = DefEngine(seed=1)
        e.ctx["v"] = "-0.017x\xb3+3.91x\xb2+x**4"
        assert e._eval_cmd("rawmath", "$v") == "-0.017x^3 +3.91x^2 +x^4"

    def test_le_tex_n_est_pas_touche(self):
        e = DefEngine(seed=1)
        e.ctx["v"] = "\\frac{x**2}{2}"
        assert e._eval_cmd("rawmath", "$v") == "\\frac{x**2}{2}"


class TestConsommateursDeE:
    """Ce que la sortie `e^(…)` a révélé chez ceux qui la lisent.

    Trois défauts préexistants — un auteur qui écrit lui-même `e^x` les
    subissait déjà —, cachés tant que l'émulation écrivait `exp(…)`.
    """

    def test_check_function(self):
        from core.answer.checkers import check_answer

        # `e` laissé symbole : l'évaluation aux points échouait, la réponse
        # juste valait 0 face à elle-même (`oefintts/ipp`).
        assert check_answer("function", "-e^(-2*x)/2", "-e^(-2*x)/2", {}).score == 1.0
        assert check_answer("function", "-exp(-2*x)/2", "-e^(-2*x)/2", {}).score == 1.0

    def test_plot_de_flydraw(self):
        from core.oef.flydraw import flydraw_to_svg

        # `oefintts/equaire` : la courbe disparaissait sans bruit.
        svg = flydraw_to_svg(200, 200, "xrange -3,1\nyrange 0,20\nplot green,e^(3*x + 1)\n")
        assert "polyline" in svg

    def test_insmath(self):
        from core.oef.def_engine.presentation import _normalize_math_content

        # L'exposant accolé pour KaTeX passait pour du LaTeX d'auteur, et
        # l'expression sortait brute, `*` compris.
        assert _normalize_math_content("v'(x)=e^(-2*x)", "fr") == "v'(x) = e^{- 2 x}"
        assert _normalize_math_content("10^27", "fr") == "10^{27}"
        assert _normalize_math_content("85 \\times 10^27", "fr") == "85 \\times 10^{27}"

    def test_les_autres_exposants_ne_sont_pas_calcules(self):
        from core.oef.def_engine.presentation import _normalize_math_content

        # `puissances/val1` demande la valeur de `(-1)^(-1)` : le CAS l'écrirait
        # `\frac{1}{-1}`, soit la réponse.
        assert "frac" not in _normalize_math_content("(-1)^(-1) =", "fr")
        assert "frac" not in _normalize_math_content("10^(-2)", "fr")
