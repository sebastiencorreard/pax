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
    ("(g(val)=x=val;f=-11*(x + 10)*(x - 17);eval(f));g(-1010)", "-11297000"),
    # Second lot : puissance et inverse de matrice, transposée indexée,
    # fonctions composante par composante, `Pol`, `matid`, `polroots`.
    ("B=[-6,5];R=[0,-1;1,0];B*(R^1)", "5,6"),
    ("divrem(1,2)~[2]", "1"),
    ("divrem(7,2)~[1]", "3"),
    ("vecmax(abs([0,0,3;3,0,0]*[1,0;0,1;1,1]))", "3"),
    ("slib_V=[7,8,1,1];print(Pol(slib_V,x))", "7*x^3 + 8*x^2 + x + 1"),
    ("slib_M=Mat([1,1;0,-1]);slib_vv=slib_M[1,];norml2(slib_vv)", "2"),
])


def test_comme_gp(expr, wims):
    assert _call_pari(expr, session={}) == wims


@pytest.mark.parametrize("expr,wims", [
    # Même valeur que `gp`, écriture de PAX (précision, `.0`, espaces) :
    # ce qui reste à trancher est la forme, non le calcul.
    ("floor([9,(1-(-0.6946583721)*9)/(0.7193397987)]*1000)/1000.", 9.0),
    ("g=real(polroots(-2*x^2 + 14*x + 5*1.)) ; g[#g]", 7.3405728739343040879),
    ("([134,107,54]*([36,183,199;149,32,161;118,18,17]^-1)~)*248.0", 89.852624744295176978),
])
def test_meme_valeur_que_gp(expr, wims):
    premiere = _call_pari(expr, session={}).split(",")[0]
    assert float(premiere) == pytest.approx(wims, rel=1e-8)
