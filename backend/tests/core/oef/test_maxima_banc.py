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
])
def test_comme_maxima(expr, maxima):
    assert _call_maxima(expr).replace(" ", "") == maxima.replace(" ", "")


def test_diff_garde_sa_forme():
    """La dérivée n'est pas simplifiée au-delà de ce que fait Maxima :
    `2*cos(x)*sin(x)`, non `sin(2*x)`."""
    assert _call_maxima("diff(sin(x)^2,x)").replace(" ", "") == "2*sin(x)*cos(x)"
