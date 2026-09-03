"""`js2wims1` — les variables d'une exécution Python, relues telles quelles.

Jumeau simplifié de `runcode`, et dépendant de lui : son `.input` ne monte
aucun éditeur. Il pose un champ **caché** que son JavaScript remplit, à
l'envoi, des variables laissées par le programme joué dans le `runcode`
voisin. D'où une réponse sans code source en tête — `[valeur],[valeur]…` —
là où `runcode` ouvre par le programme.

Deux autres écarts, tous deux vers la simplicité : la comparaison est
**purement textuelle**, sans tolérance numérique, et chaque variable vaut
`1/n` sans découpage par terme.

Quatorze champs dans `oefechpython`, dont **un seul pèse** (`de3/reply2`) ;
les treize autres ne servent qu'à dresser le tableau récapitulatif.
"""
from core.answer.checkers import check_answer, check_js2wims1


def _res(reply, expected="[n,[3]]"):
    return check_answer("js2wims1", reply, expected, {}, "fr")


class TestDispatch:
    def test_js2wims1_ne_retombe_plus_sur_check_text(self):
        assert _res("[3]").method == "js2wims1"


class TestComparaison:
    """La réponse ne porte **pas** le code source : les valeurs commencent au
    premier item, non au second comme dans `runcode`."""

    def test_la_variable_juste_vaut_un(self):
        assert _res("[3]").score == 1.0

    def test_une_valeur_fausse_vaut_zero(self):
        assert _res("[5]").score == 0.0

    def test_le_detail_nomme_la_variable(self):
        assert "n" in (_res("[5]").detail or "")

    def test_chaque_variable_vaut_sa_part(self):
        e = "[a,[1]],[b,[2]]"
        assert check_js2wims1("[1],[2]", e).score == 1.0
        assert check_js2wims1("[1],[9]", e).score == 0.5
        assert check_js2wims1("[8],[9]", e).score == 0.0

    def test_une_valeur_manquante_compte_comme_fausse(self):
        assert check_js2wims1("[1]", "[a,[1]],[b,[2]]").score == 0.5


class TestComparaisonTextuelle:
    """Pas de tolérance numérique, contrairement à `runcode` : le module
    compare `$(good) == $(rep)`, deux chaînes."""

    def test_un_ecart_meme_minime_est_faux(self):
        assert check_js2wims1("[3.0]", "[n,[3]]").score == 0.0

    def test_une_valeur_textuelle_se_compare_a_l_identique(self):
        assert check_js2wims1("[oui]", "[rep,[oui]]").score == 1.0
        assert check_js2wims1("[Oui]", "[rep,[oui]]").score == 0.0


class TestAttenduSansValeur:
    """`!if $(good)==$empty → diareply=good` : le module sort alors sur un
    verdict juste. C'est le cas de `de4`, `de5` et `de6`, dont le `replygood`
    se réduit à un nom — et dont le champ pèse zéro."""

    def test_un_attendu_reduit_a_un_nom_vaut_juste(self):
        assert check_js2wims1("", "nn").correct
        assert check_js2wims1("n'importe quoi", "nn").score == 1.0


class TestReponsesMalFormees:
    def test_un_attendu_vide_ne_note_rien(self):
        assert check_js2wims1("[3]", "").score == 0.0

    def test_une_reponse_vide_est_fausse(self):
        assert _res("").score == 0.0
