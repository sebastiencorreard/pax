"""`wlist` — une liste de mots à prendre dans un répertoire.

Ce n'est pas une égalité d'ensembles, et c'est ce qui le sépare de `set` :
`anstype/wlist` demande que chaque mot cité appartienne au répertoire, et
qu'il y en ait au moins `n`. Un sous-ensemble suffit donc, pourvu qu'il
atteigne le seuil.

Un seul exercice l'emploie, `H3/chemistry/mol.fr/molecule2` (« Liste des
atomes »), et il ne pose aucun seuil : son `replygood` est la liste des quatre
atomes, sans nombre en tête.
"""
from core.answer.checkers import check_answer, check_wlist

# Le `replygood` de `molecule2` : `$val21`, constant d'une graine à l'autre.
_ATOMES = "carbone,hydrogène,azote,oxygène"


def _res(reply, expected=_ATOMES):
    return check_answer("wlist", reply, expected, {}, "fr")


class TestDispatch:
    def test_wlist_ne_retombe_plus_sur_check_text(self):
        """La dette portée ici : `check_text` n'acceptait que les quatre atomes
        écrits dans l'ordre exact du `replygood`."""
        assert _res("carbone,hydrogène").method == "wlist"


class TestAppartenance:
    """« tous les mots cités sont du répertoire » — pas « tous les mots du
    répertoire sont cités »."""

    def test_un_sous_ensemble_suffit(self):
        assert _res("carbone,hydrogène").correct

    def test_le_repertoire_entier_convient_aussi(self):
        assert _res("carbone,hydrogène,azote,oxygène").correct

    def test_un_seul_mot_suffit_faute_de_seuil(self):
        """`molecule2` ne pose pas de seuil : `n` retombe à 1. Laxisme de
        l'exercice, non du checker — cf. `TestSeuil`."""
        assert _res("azote").correct

    def test_un_intrus_annule_tout(self):
        assert not _res("carbone,fer").correct

    def test_le_detail_nomme_l_intrus(self):
        assert "fer" in (_res("carbone,fer").detail or "")

    def test_une_reponse_vide_est_fausse(self):
        assert not _res("").correct


class TestEcritures:
    """La normalisation est celle d'`atext`, dont `wlist` partage le
    dictionnaire (`scripts/oef/fr/atext.dic`, `bases/sys/suffix.fr`)."""

    def test_l_espace_separe_comme_la_virgule(self):
        assert _res("carbone hydrogène").correct

    def test_la_casse_et_les_accents_sont_indifferents(self):
        assert _res("Carbone, Hydrogene").correct

    def test_les_articles_tombent(self):
        """`le`, `la`, `de` portent une traduction vide dans le dictionnaire."""
        assert _res("le carbone, l'hydrogène").correct

    def test_une_conjonction_reste_un_intrus(self):
        """`et` n'est pas dans le dictionnaire, et `translator_unknown=leave`
        le laisse passer tel quel : WIMS le compte alors comme un mot du
        répertoire, qu'il n'est pas. Fidèle, quoique sévère."""
        assert not _res("le carbone et l'hydrogène").correct

    def test_les_doublons_sont_reduits(self):
        """`!listuniq $dd` avant de compter."""
        assert _res("carbone,carbone").correct


class TestSeuil:
    """`n=!word 1 of $good`, `!if $n>0` : un nombre en tête du `replygood` fixe
    le minimum de mots, et sort du répertoire."""

    def test_un_nombre_en_tete_fixe_le_minimum(self):
        good = "2,carbone,hydrogène,azote,oxygène"
        assert not check_wlist("carbone", good).correct
        assert check_wlist("carbone,hydrogène", good).correct

    def test_le_nombre_ne_fait_pas_partie_du_repertoire(self):
        assert not check_wlist("2", "2,carbone,hydrogène").correct

    def test_le_detail_dit_le_seuil_quand_rien_n_est_intrus(self):
        detail = check_wlist("carbone", "2,carbone,hydrogène").detail or ""
        assert "2" in detail

    def test_sans_nombre_en_tete_le_seuil_vaut_un(self):
        assert check_wlist("carbone", "carbone,hydrogène").correct


class TestBadwords:
    """Le `;` de `replygood` fait un saut de ligne : la première ligne est le
    répertoire, les suivantes les `badwords` du diagnostic `unknownword` — que
    PAX ne rend pas, comme pour `atext`. Elles ne doivent surtout pas entrer
    dans le répertoire."""

    def test_ce_qui_suit_le_point_virgule_n_est_pas_une_bonne_reponse(self):
        assert not check_wlist("fer", "carbone,hydrogène;fer,cuivre").correct

    def test_la_premiere_ligne_reste_le_repertoire(self):
        assert check_wlist("carbone", "carbone,hydrogène;fer,cuivre").correct
