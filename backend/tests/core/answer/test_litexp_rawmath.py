"""`litexp` : la forme se juge sur le `rawmath` de WIMS, non sur une regex.

`anstype/litexp` traduit l'attendu et la réponse par `!rawmath` — la réponse
avec les variables de l'attendu déclarées — puis exige que la réponse, sans
espace, soit l'une des formes de l'attendu (`isitemof`).
"""
import pytest

from core.answer.checkers import check_answer


@pytest.mark.parametrize("reponse,attendu,note", [
    ("2x+3", "2*x+3", 1.0),
    ("x*x+3", "x^2+3", 0.0),            # égal, mais pas la forme demandée
    ("6/4", "3/2", 0.0),
    ("sqrt(5)*5", "5*sqrt(5),sqrt(5)*5", 1.0),   # l'une des formes admises
    ("5sqrt(5)", "5*sqrt(5),sqrt(5)*5", 1.0),
    ("2ab", "2*ab", 1.0),               # `ab` déclarée : un nom, pas a*b
    ("(x+1)(x-1)", "(x+1)*(x-1)", 1.0),
    ("|x|+1", "abs(x)+1", 1.0),
    ("1,5x", "1.5*x", 1.0),             # virgule décimale, comme partout
    ("sqrt 5*5", "5*sqrt(5)", 0.0),     # rawmath lit sqrt(5*5)
])
def test_forme_litexp(reponse, attendu, note):
    assert check_answer("litexp", reponse, attendu, {}).score == note
