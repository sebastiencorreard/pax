"""L'émulation Maxima confrontée au vrai `maxima` (banc `scripts/banc_maxima`).

Chaque attendu est la sortie de Maxima 5.47.0 sous l'interface de WIMS
(`maxima.c`), comparée **aux espaces près** : SymPy écrit `x + 1`, Maxima
`x+1`, et l'écart n'est pas suivi.
"""
import pytest

from core.oef.def_engine.cas import _call_maxima


@pytest.mark.parametrize("expr,maxima", [
    # `\` protège le caractère qui suit : des variables OEF non substituées.
    ("factor((\\r2));", "r2"),
    ("fullratsimp(((-1)*1+\\sqrt(49))/(2*1));", "3"),
    ("\\x1*\\x2", "x1*x2"),
    # `divide` : quotient et reste ; tronqué vers zéro sur des entiers.
    ("divide(14,6)", "2,2"),
    ("divide(-14,6)", "-2,-2"),
    ("divide(14,-6)", "-2,2"),
    ("divide(7,2.0)", "3.5,0"),
    # Dérivée sur ℝ : plus de `re(x)`, `im(x)` ni `derivative(…)`.
    ("diff(ln(abs(x))-1*x,x);", "-1+1/x"),
    ("sum(0.875^n,n,0,2)", "2.640625"),
    ("solve((1/(x^2 - 6*x + 9)=1/25),x);", "x=-2,x=8"),
    # `logcontract` ne contracte qu'un coefficient entier.
    ("logcontract(log(x - 5) - log(3*x - 8)/3)", "log(x-5)-log(3*x-8)/3"),
    # Maxima ne développe pas : ni `simplify` sur une expression nue, ni
    # distribution d'un nombre sur une somme.
    ("1.12*(x+6)", "1.12*(x+6)"),
    ("((x+1/2)^2--3/2)", "(x+1/2)^2+3/2"),
    ("2*(x-1)*(x-3)", "2*(x-3)*(x-1)"),
    # … sauf `-1` sur une somme seule au numérateur.
    ("-1*(x^2 -12*x) +4", "-x^2+12*x+4"),
    ("-1*(x--1)/(2*(x--5))", "(-x-1)/(2*(x+5))"),
    ("-x*(x + 2) - 1", "-x*(x+2)-1"),
])
def test_comme_maxima(expr, maxima):
    assert _call_maxima(expr).replace(" ", "") == maxima.replace(" ", "")


def test_regle_du_produit():
    """`deriverProduit` : la dérivée d'un produit garde la règle du produit,
    `2*(7*x+1)+7*(2*x+5)` chez Maxima — non `28*x + 37`."""
    sortie = _call_maxima("diff((2*x+5)*(7*x+1),x);").replace(" ", "")
    assert sorted(sortie.split("+")) == sorted("2*(7*x+1)+7*(2*x+5)".split("+"))


def test_diff_garde_sa_forme():
    """La dérivée n'est pas simplifiée au-delà de ce que fait Maxima :
    `2*cos(x)*sin(x)`, non `sin(2*x)`."""
    assert _call_maxima("diff(sin(x)^2,x)").replace(" ", "") == "2*sin(x)*cos(x)"
