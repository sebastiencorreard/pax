"""`!rawmath` — le port de `rawmath.c`.

Chaque attendu ci-dessous est la sortie du **vrai** `rawmath()` de WIMS,
compilé depuis l'arbre dans un harnais qui le nourrit ligne à ligne (les deux
variables de session qu'il lit — `wims_rawmath_variables`/`functions` —
restant vides, comme pour tout exercice OEF). Le port a été confronté à ce
harnais sur les 4 669 entrées que le corpus soumet à `!rawmath` et sur
300 000 chaînes aléatoires : aucun écart, avertissements compris.
"""
import pytest

from core.oef.def_engine.rawmath import rawmath, varlist

# (entrée, sortie de WIMS, avertissement de WIMS)
REFERENCE = [
    ("2x+3", "2*x+3", ""),
    ("3(x+1)", "3*(x+1)", ""),
    ("(x+1)(x-1)", "(x+1)*(x-1)", ""),
    ("sin x", "sin(x)", " ambiguous"),
    ("sinx^2", "sin(x)^2", " ambiguous"),
    ("sin^2 x", "sin(x)^2", " ambiguous"),
    ("|x-1|", "abs(x-1)", ""),
    (".5x", "0.5*x", ""),
    ("4.", "4.0", ""),
    ("xy+ab", "x*y+ab", " ambiguous unknown"),
    ("abcdefghij", "abcdefghij", " unknown"),
    ("arc cos x", "arccos(x)", " ambiguous"),
    ("Arcsin x", "Arcsin*x", " unknown"),
    ("1x+-15", "1*x-15", ""),
    ("0.75cos(t) + 9", "0.75*cos(t) + 9", ""),
    ("2e-3x", "2e-3*x", ""),
    ("x-->y", "x-->y", ""),
    ("2 3", "2*3", ""),
    ('"a"', "''a''", " unknown"),
    ("x^1/2", "x^1/2", " badprec"),
    ("(x+1", "(x+1", ""),
    ("sqrt 2x", "sqrt(2*x)", " ambiguous"),
    ("-0.017x\xb3+3.91x\xb2", "-0.017*x^3 +3.91*x^2 ", " flatpower"),
    ("x**2", "x^2", ""),
]


@pytest.mark.parametrize("entree,sortie,avertissement", REFERENCE)
def test_comme_wims(entree, sortie, avertissement):
    assert rawmath(entree) == (sortie, avertissement)


def test_le_tex_n_est_pas_touche():
    # `rawmath.c` : « looks like a TeX source : do nothing ». La fusion des
    # signes elle-même n'y passe pas.
    assert rawmath("\\frac{1}{2}+-x")[0] == "\\frac{1}{2}+-x"
    assert rawmath("{2x}")[0] == "{2x}"


# Noms déclarés (`wims_rawmath_variables` / `_functions`) et `!varlist nofn`,
# sortis du même harnais — c'est ainsi qu'`anstype/litexp` traduit la réponse.

@pytest.mark.parametrize("entree,variables,fonctions,sortie,avertissement", [
    ("2ab+xy", "ab", "", "2*ab+x*y", " ambiguous"),
    ("3uv+uw", "uv", "", "3*uv+uw", " unknown"),
    ("g x+1", "", "g", "g(x)+1", " ambiguous"),
    ("2a b", "ab", "", "2*a*b", ""),
])
def test_noms_declares(entree, variables, fonctions, sortie, avertissement):
    assert rawmath(entree, variables, fonctions) == (sortie, avertissement)


@pytest.mark.parametrize("entree,sortie", [
    ("2*ab+sqrt(x)+ab", "ab,x"),
    ("x^2+3*x*y-sin(t)", "x,y,t"),
    ("f (x)+abc2", "x,abc2"),
])
def test_varlist_nofn(entree, sortie):
    assert varlist(entree, nofn=True) == sortie
