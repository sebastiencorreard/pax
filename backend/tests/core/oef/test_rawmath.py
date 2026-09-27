"""`!rawmath` — le port de `rawmath.c`.

Chaque attendu ci-dessous est la sortie du **vrai** `rawmath()` de WIMS,
compilé depuis l'arbre dans un harnais qui le nourrit ligne à ligne (les deux
variables de session qu'il lit — `wims_rawmath_variables`/`functions` —
restant vides, comme pour tout exercice OEF). Le port a été confronté à ce
harnais sur les 4 669 entrées que le corpus soumet à `!rawmath` et sur
300 000 chaînes aléatoires : aucun écart, avertissements compris.
"""
import pytest

from core.oef.def_engine.rawmath import rawmath

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
