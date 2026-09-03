"""`jmolclick` — les atomes qu'on clique sur une molécule.

Le correcteur ne corrige pas, et c'est ce qui distingue ce type de tous les
autres : `anstype/jmolclick` reçoit une réponse dont la **première ligne est
déjà la note**, calculée dans le navigateur. L'applet seule sait ce qu'est
« un oxygène lié à un hydrogène et à un carbone » — elle évalue l'expression
attendue et la compare à la sélection de l'élève. Le script WIMS s'en tient à
`!distribute lines … into score,…` puis `score=$[round($score)/10]`.

Le calcul, lui, vit dans `composables/useJsmol.ts` (`noterSelectionJmol`),
port du `analyserep` du `.input` : les atomes justes, les faux, les oubliés.
Un seul exercice l'emploie, `oefmolecule/reconnaissance`, et son
`replyoption` est vide — donc pas de barème partiel (`coeff=0`) : aucun atome
faux, et tous les bons.
"""
from core.answer.checkers import check_answer, check_jmolclick


def _res(reply):
    return check_answer("jmolclick", reply, "oxygen and connected(hydrogen)", {}, "fr")


class TestDispatch:
    def test_jmolclick_ne_retombe_plus_sur_check_text(self):
        assert _res("10").method == "jmolclick"


class TestNote:
    """`score=$[round($score)/10]` — WIMS relit, il ne recalcule pas."""

    def test_la_selection_exacte_vaut_un(self):
        res = _res("10")
        assert res.score == 1.0
        assert res.correct

    def test_une_selection_fautive_vaut_zero(self):
        res = _res("0")
        assert res.score == 0.0
        assert not res.correct

    def test_seule_la_premiere_ligne_compte(self):
        """Les suivantes portent les atomes justes, faux et oubliés — de quoi
        colorer la molécule, rien qui entre dans la note."""
        assert _res("10\n({1 2})\n({})\n({})\norientation").score == 1.0

    def test_la_note_est_arrondie_comme_chez_wims(self):
        assert check_jmolclick("9.6", "").score == 1.0
        assert check_jmolclick("4.4", "").score == 0.4

    def test_la_note_reste_entre_zero_et_un(self):
        assert check_jmolclick("50", "").score == 1.0
        assert check_jmolclick("-10", "").score == 0.0


class TestReponsesMalFormees:
    """Le champ vient du navigateur : il peut arriver vide, ou sans chiffre."""

    def test_une_reponse_vide_est_fausse(self):
        assert not _res("").correct
        assert _res("").score == 0.0

    def test_une_reponse_non_numerique_est_fausse(self):
        assert not _res("beaucoup").correct

    def test_les_espaces_ne_genent_pas(self):
        assert _res("  10  ").correct


class TestAttendu:
    """L'expression de sélection n'entre pas dans le calcul : elle a déjà
    servi, dans l'applet. Le checker ne doit pas s'en soucier."""

    def test_l_attendu_ne_change_rien(self):
        assert check_jmolclick("10", "").score == 1.0
        assert check_jmolclick("10", "nitrogen and connected(3)").score == 1.0
