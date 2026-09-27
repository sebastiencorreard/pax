"""`mynumexp` — le type de `frac5` (`anstype/mynumexp`), sur ses exercices
`add` et `soust` : calculer une somme de fractions, sans obligation de réduire
(`noreduction`).

Retombé sur la comparaison par défaut, il acceptait `1/3+1/30` pour `11/30` :
l'énoncé tenait lieu de réponse.
"""
import pytest

from core.answer.checkers import check_answer

NOREDUC = {"option": "noreduction"}


def _res(reply, expected="11/30", options=NOREDUC):
    return check_answer("mynumexp", reply, expected, options, "fr")


@pytest.mark.parametrize("reply", ["11/30", "22/60", "11 / 30", "+11/30", "1.1/3", "11,0/30"])
def test_valeurs_egales_admises(reply):
    assert _res(reply).correct


@pytest.mark.parametrize("reply", ["1/3+1/30", "11/30+0", "(11)/30", "2*11/60", "11/30^1"])
def test_une_operation_est_hors_format(reply):
    r = _res(reply)
    assert r.score == 0.0 and r.status == "invalid_format"


def test_valeur_approchee_refusee():
    # `is(equal(0.3666666, 11/30))` : faux.
    assert not _res("0.3666666").correct


def test_seules_deux_parts_comptent():
    # `!distribute item … into num,den` : `11/30/2` se lit `11/30`.
    assert _res("11/30/2").correct


def test_zero():
    assert _res("0", "0").correct
    assert _res("0/5", "0").status == "invalid_format"


def test_sans_noreduction_aucune_fraction_ne_passe():
    # Défaut du fichier, reproduit : il compare la forme **reconstruite**
    # (`11*1/(30*1)`) à la forme réduite. Sans effet dans le corpus.
    assert _res("11/30", options={}).status == "invalid_format"
