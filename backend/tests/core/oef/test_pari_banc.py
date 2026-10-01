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


HOUSEHOLDER = (
    "{slib_A=matid(3);slib_n=2; \nslib_M= Mat([1,-2,0;0,1,0]);\\\n"
    "for(slib_j=1 , slib_n,slib_vv=slib_M[slib_j,]; "
    "slib_A=slib_A*(matid(3)-2/norml2(slib_vv)*slib_vv~*slib_vv));\nprint(slib_A)}"
)


@pytest.mark.parametrize("expr,wims", [
    ("floor(3398 \\ 119)", "28"),          # quotient entier `\`
    ("-7 \\ 2", "-4"),
    ("if(0, log(0), 5)", "5"),             # `if` paresseux
    ("binary(41)", "1,0,1,0,0,1"),
    ("core(27,1)", "3,3"),
    ("L=List([3,-1,2]); listsort(L) ;Vec(L)", "-1,2,3"),
    # Réflexions de Householder : produit colonne × ligne (OEFbarypdtsc…).
    (HOUSEHOLDER, "3/5,-4/5,0;4/5,3/5,0;0,0,1"),
])
def test_troisieme_lot_comme_gp(expr, wims):
    assert _call_pari(expr, session={}) == wims


@pytest.mark.parametrize("expr,wims", [
    # `I`, et `i` dans l'évaluation d'expression (`i=I` de l'en-tête).
    ("print(arg(0.3+I*(-0.3)))", -0.78539816339744830962),
    ("abs(-(i - 2))", 2.2360679774997896964),
])
def test_imaginaire_meme_valeur_que_gp(expr, wims):
    # La valeur, non l'écriture : PAX garde `sqrt(5)` où PARI écrit un flottant.
    import sympy

    assert float(sympy.N(sympy.sympify(_call_pari(expr, session={})))) == pytest.approx(wims, rel=1e-8)


@pytest.mark.parametrize("expr,wims", [
    # Arithmétique du collège : chacune rendait un produit (`140*factor`).
    ("factor(140)", "2,2;5,1;7,1"),
    ("factor(32)", "2,5"),
    ("divisors(28)", "1,2,4,7,14,28"),
    ("numdiv(12)", "6"),
    ("primes(4)", "2,3,5,7"),
    ("sumdigits(13 467)", "21"),
    # Valait 0 par accident (`truncate*0`) tant que le nom était un symbole.
    ("truncate(0)", "0"),
    ("truncate(-2.7)", "-2"),
])
def test_arithmetique_comme_gp(expr, wims):
    assert _call_pari(expr, session={}) == wims


def test_un_appel_inconnu_n_est_pas_un_produit():
    # Une fonction que PAX ne connaît pas : l'appel reste lisible, et surtout
    # ne devient pas `12*qfbclassno`.
    assert "*" not in _call_pari("qfbclassno(12,2)", session={})


@pytest.mark.parametrize("expr,valeur", [
    # PARI réduit une fraction rationnelle ; SymPy développée l'éclatait en
    # somme (`-x/(x + 1) - 1/(x + 1)`). L'ordre des termes, lui, n'est pas
    # suivi (`gp` : `-4*x+1`) : c'est une décision, non un oubli.
    ("(-(x + 1)*(3*x - 1))/((x + 1)*(3*x - 1))", "-1"),
    ("((-17*x - 11)/(2*(2*x + 1)))*(-4*x-2)", "17*x + 11"),
    ("(-(x + 1)*(4*x - 1))/((x + 1))", "1 - 4*x"),
    ("(x^2+1)/(x+1)", "(x^2 + 1)/(x + 1)"),
    ("1/(x-2)+1/(x+2)", "2*x/(x^2 - 4)"),
    ("(x+1)^2", "x^2 + 2*x + 1"),
])
def test_fraction_rationnelle_reduite(expr, valeur):
    assert _call_pari(expr, session={}) == valeur


@pytest.mark.parametrize("expr,wims", [
    # Cinquième lot. Vecteurs colonne : `output()` de `pari.c` n'ôte que des
    # crochets terminaux, le `~` survit — `tgte2par` découpe cette écriture.
    ("polroots(numerator(-2*(x - 3)*(x + 7)))", "[-7.0+0.0*I,3.0+0.0*I]~"),
    ("polroots(numerator(-(2*x - 3)^2*(2*x + 3)^2/4))",
     "[-1.5+0.0*I,-1.5+0.0*I,1.5+0.0*I,1.5+0.0*I]~"),
    ("nfroots(,numerator(-(x + 2)*(7*x - 6)/(25*(x - 3)^2)))", "[-2,6/7]~"),
    ("print([1,2]~)", "[1,2]~"),
    ("divrem(10,3)~", "3,1"),
    # Numérateur et dénominateur réduits comme PARI (`assocfct`).
    ("numerator((3*(2*x + 1)^2 + 23)/((2*x + 1)^2 + 1))", "6*x^2 + 6*x + 13"),
    ("denominator((3*(2*x + 1)^2 + 23)/((2*x + 1)^2 + 1))", "2*x^2 + 2*x + 1"),
    ("denominator(-x/(-2*x+1))", "2*x - 1"),
    ("numerator(3/(4*x+6))", "3"),
    ("denominator(x/2+1/3)", "1"),
    # Complexes : module, norme, racine d'un négatif.
    ("abs(3-4*I)", "5"),
    ("abs(-3/2)", "3/2"),
    ("norm(-5 - i-(5 - 4*i))", "109"),
    ("sqrt(-4)", "2.0*I"),
    ("if(-(sqrt(2)*(i + 1)/4)==0,0,abs(arg(-(sqrt(2)*(i + 1)/4))-((pi/2)/2)))",
     "3.141592654"),
    ("poldisc(4*x^2 - 12*x - 16)", "400"),
    # Séquence en argument : son dernier terme (`bernoulli2`).
    ("print(0.05*5;0.05*11)", "0.55"),
    ("8e+09", "8000000000.0"),
    # Un réel reste un réel, même de valeur entière (`etagere2`) ; notation
    # `E` hors de [1e-4, 1e19[ ; `n!` exact, `factorial(n)` réel.
    ("[455,460,458,462]/10.", "45.5,46.0,45.8,46.2"),
    ("4./2", "2.0"),
    ("[1.,-0.]", "1.0,0.0"),
    ("10.^25", "1.0E25"),
    ("0.00001", "1.0E-5"),
    ("(15!)/((15-2)!)", "210"),
    ("factorial(4)/factorial(2)", "12.0"),
    ("binomial(8,4)*truncate(factorial(4))", "1680"),
    # `limfrac` : valuation, série, degré d'une fraction rationnelle.
    (("P=Pol([6, -6, 5],x); Q=Pol([1, -2, -3, -3, 0, 0],x); "
      "v0=valuation(P/Q,x);\tS=subst(P/Q,x,1/x);\tvi=valuation(S,x);\t"
      "[P,Q,v0,pollead(P/Q+O(x^50)),poldegree(P/Q,x),pollead(S+O(x^50)),"
      "poldegree(P,x),valuation(P,x)]"),
     "6*x^2 - 6*x + 5,x^5 - 2*x^4 - 3*x^3 - 3*x^2,-2,-5/3,-3,6,2,0"),
    ("valuation(72,2)", "3"),
    # Permutations (`evolmeth4`), factorielle et incrément postfixes.
    ("vector(3,k,numtoperm(3,k))",
     "Vecsmall([1,3,2]),Vecsmall([2,1,3]),Vecsmall([2,3,1])"),
    ("print(numtoperm(5,-4))", "5,4,2,1,3"),
    ("(#[1,2,3])!", "6"),
    ("x=[0,0];x[1]++;x", "1,0"),
    # Corps de `vector` en séquence (`1_decompo_qcm`).
    ("v=[2,2,5,7];nb=140;vector(4,i,m=v[1..i];concat(m,nb/prod(t=1,#m,m[t])))",
     "[2,70],[2,2,35],[2,2,5,7],[2,2,5,7,1]"),
    # Un polynôme sort développé, mini-interpréteur compris (`multparm3`).
    ("P=2*(x +11)*(x +11)*(x +17);cc=polcoeff(P,1);P+(m-cc)*x^1",
     "m*x + 2*x^3 + 78*x^2 + 4114"),
])
def test_cinquieme_lot_comme_gp(expr, wims):
    assert _call_pari(expr, session={}) == wims
