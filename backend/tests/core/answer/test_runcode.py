"""`runcode` — le code Python que l'élève écrit, jugé sur ses variables.

Le type n'existe pas chez WIMS : huit modules d'`H4/programming` le
définissent, à quelques lignes près les uns des autres. Et son correcteur
**n'exécute rien** — Skulpt fait tourner le programme dans le navigateur, le
`.input` relève les variables globales (`Sk.ffi.remapToJs`) et compose

    [<code source>],[<valeur 1>],[<valeur 2>]…

dont le serveur ne compare que les valeurs, dans l'ordre où `replygood` nomme
les variables. Le code lui-même n'est pas jugé : seulement ce qu'il produit.

99 champs sur 4 familles — variables simples, sortie `print`, listes
`x_list`/`y_list` d'une courbe, matrice `mat` de pixelart.
"""
from core.answer.checkers import check_answer, check_runcode


def _res(reply, expected="[vi,1],[vf,4]", precision=100.0):
    return check_answer("runcode", reply, expected, {"precision": precision}, "fr")


class TestDispatch:
    def test_runcode_ne_retombe_plus_sur_check_text(self):
        assert _res("[code],[1],[4]").method == "runcode"


class TestVariablesSimples:
    """`[vi,1],[vf,4]` : « vi doit valoir 1, vf 4 »."""

    def test_les_deux_justes_valent_un(self):
        assert _res("[n=1@@@@n=n+3],[1],[4]").score == 1.0

    def test_une_variable_fausse_coute_sa_part(self):
        assert _res("[code],[1],[9]").score == 0.5

    def test_les_deux_fausses_valent_zero(self):
        assert _res("[code],[7],[9]").score == 0.0

    def test_une_variable_manquante_compte_comme_fausse(self):
        assert _res("[code],[1]").score == 0.5

    def test_le_detail_nomme_la_variable(self):
        assert "vf" in (_res("[code],[1],[9]").detail or "")

    def test_le_code_source_ne_se_juge_pas(self):
        """Item 1 = le programme. Deux codes différents qui produisent les
        mêmes valeurs valent tous deux 1 — c'est tout l'objet du type."""
        assert _res("[vi=1@@@@vf=4],[1],[4]").score == 1.0
        assert _res("[from math import *],[1],[4]").score == 1.0


class TestTolerance:
    """`abs(good - rep) < 1/precision` pour un terme numérique, égalité
    littérale sinon."""

    def test_un_ecart_sous_la_precision_passe(self):
        assert _res("[code],[1.001],[4]", precision=100.0).score == 1.0

    def test_un_ecart_au_dessus_ne_passe_pas(self):
        assert _res("[code],[1.5],[4]", precision=100.0).score == 0.5

    def test_une_valeur_textuelle_se_compare_a_l_identique(self):
        assert check_runcode("[code],[bonjour]", "[mot,bonjour]").score == 1.0
        assert check_runcode("[code],[Bonjour]", "[mot,bonjour]").score == 0.0


class TestListes:
    """Une variable peut porter une liste — `x_list`, les abscisses d'une
    courbe. Chaque terme compte pour une fraction de sa variable, et chaque
    variable pour une fraction du tout (`1/nbr_good/cnt_variable`).

    Un tableau JavaScript s'interpole de lui-même en `1,2,3` : c'est la forme
    que le navigateur envoie, et le découpage en items la respecte grâce aux
    crochets."""

    ATTENDU = "[x_list,[1,2,3]],[y_list,[4,5,6]]"

    def test_les_deux_listes_justes(self):
        assert check_runcode("[code],[1,2,3],[4,5,6]", self.ATTENDU).score == 1.0

    def test_un_terme_faux_sur_six(self):
        res = check_runcode("[code],[1,2,3],[4,5,9]", self.ATTENDU)
        assert round(res.score, 3) == 0.833

    def test_une_liste_trop_courte_perd_ses_termes_manquants(self):
        res = check_runcode("[code],[1,2],[4,5,6]", self.ATTENDU)
        assert round(res.score, 3) == 0.833


class TestSortiePrint:
    """22 champs attendent `print` — non une variable, mais ce que le
    programme **affiche**. Le composant y met la sortie, sauts de ligne
    remplacés par `:`, et le correcteur la compare comme un texte."""

    def test_la_sortie_se_compare_comme_un_texte(self):
        assert check_runcode("[code],[1:2:3]", "[print,1:2:3]").score == 1.0
        assert check_runcode("[code],[1:2:4]", "[print,1:2:3]").score == 0.0


class TestReponsesMalFormees:
    def test_une_reponse_vide_est_fausse(self):
        assert _res("").score == 0.0

    def test_un_attendu_vide_ne_note_rien(self):
        assert check_runcode("[code],[1]", "").score == 0.0

    def test_une_reponse_sans_valeur_est_fausse(self):
        """Le programme n'a pas tourné : il ne reste que le code."""
        assert _res("[code]").score == 0.0
