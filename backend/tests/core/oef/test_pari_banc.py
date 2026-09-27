"""L'émulation PARI confrontée au vrai `gp` (banc `scripts/banc_pari`).

Chaque attendu est la sortie de `gp` sous l'interface de WIMS (`pari.c`) :
en-tête d'alias, `\\p 20`, crochets et `Mat(…)` extérieurs ôtés.
"""
import pytest

from core.oef.def_engine.cas import _call_pari


@pytest.mark.parametrize("expr,wims", [
    # Fonctions qui retombaient en produit (`bigomega(12)` → `12*bigomega`).
    ("bigomega(12)", "3"),
    ("omega(12)", "2"),
    ("nextprime(8)", "11"),
    ("nextprime(11)", "11"),
    ("precprime(10)", "7"),
    ("prime(24)", "89"),
    ("digits(215,10)", "2,1,5"),
    ("matrank([1,2;2,4])", "1"),
    # Littéraux matriciels : l'évaluation d'expression les renvoyait tels quels.
    ("mattranspose([1,2;2,0])", "1,2;2,0"),
    ("matdet([1,2;3,4])", "-2"),
    # Égalité de valeurs, non d'objets.
    ("50==0.5*100", "1"),
    ("3!=3", "0"),
    # `gp` ignore les blancs : `13 467` est un nombre.
    ("digits(13 467,10)", "1,3,4,6,7"),
    # Fonction définie à la volée, évaluée (qcuautomatism, oefseconddegree).
    ("(g(val)=x=val;f=(2*x + 6)*(x - 2);eval(f));g(-0.5)", "-12.5"),
])
def test_comme_gp(expr, wims):
    assert _call_pari(expr, session={}) == wims
