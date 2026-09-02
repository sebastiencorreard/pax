"""`numexp2` — le `numexp` sans la contrainte d'irréductibilité.

Le type est défini par `H3/number/OEFevalwimsfrac.fr/anstype/numexp2`, dont il
suit le fichier pas à pas : garde de format, cas de l'attendu nul, puis produit
en croix. Les six exercices du module en dépendent, et jusqu'ici ils tombaient
sur `check_text` — qui refusait `6/4` pour `3/2` comme il refusait `1,5`.
"""
import pytest

from core.answer.checkers import check_answer


def _res(reply, expected, lang="fr"):
    return check_answer("numexp2", reply, expected, {}, lang)


class TestEgalite:
    """Le produit en croix : deux écritures de même valeur se valent."""

    @pytest.mark.parametrize("reply,expected", [
        ("3/2", "3/2"),
        ("6/4", "3/2"),        # tout l'objet du module : pas d'irréductibilité
        ("3/2", "6/4"),
        ("15/10", "3/2"),
        ("1.5", "3/2"),        # décimal contre fraction
        ("0.75", "3/4"),
        ("1,5/2", "3/4"),      # barre *et* virgule — `numexp` dirait badform
        ("-3/2", "-6/4"),
        ("+2", "2"),
        ("2", "2"),
        ("0", "0"),
    ])
    def test_accepte(self, reply, expected):
        r = _res(reply, expected)
        assert r.correct and r.score == 1.0 and r.method == "numexp2"

    @pytest.mark.parametrize("reply,expected", [
        ("2/3", "3/2"),
        ("0.333", "1/3"),      # pas de tolérance : l'égalité est rationnelle
        ("1", "1/2"),
    ])
    def test_refuse(self, reply, expected):
        r = _res(reply, expected)
        assert not r.correct and r.score == 0.0 and r.status == "ok"


class TestHorsFormat:
    """`test=NaN nocompute` : une opération n'est pas une réponse fausse, c'est
    une réponse qui n'a pas été menée à son terme."""

    @pytest.mark.parametrize("reply", [
        "1/2+1/4", "3-1/4", "3*1/4", "2^2", "(3)/4", "1/2/3", "1/-2",
    ])
    def test_une_operation_est_hors_format(self, reply):
        r = _res(reply, "3/4")
        assert r.status == "invalid_format" and r.score == 0.0

    def test_le_signe_de_tete_ne_compte_pas_pour_une_operation(self):
        """Le fichier ôte le premier caractère avant de chercher un `-` : c'est
        ce qui distingue `-3/2` de `1/-2`."""
        assert _res("-3/2", "-3/2").correct
        assert _res("1/-2", "-1/2").status == "invalid_format"


class TestAttenduNul:
    """`!if $good=0 and $(reply$i) notsametext 0` — pour zéro, on écrit `0`."""

    @pytest.mark.parametrize("reply", ["0/5", "0.0", "0,0", "00", "-0"])
    def test_seul_le_texte_zero_passe(self, reply):
        assert _res(reply, "0").status == "invalid_format"

    def test_zero_ecrit_zero(self):
        assert _res("0", "0").correct


def test_reponse_vide():
    """Pas de verdict à rendre, mais pas de faute de forme à reprocher non plus."""
    r = _res("", "3/4")
    assert not r.correct and r.status == "ok"
