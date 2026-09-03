"""`aset` — le troisième de la famille `set` / `fset` / `aset`.

L'aide de WIMS (`help/anstype.fr/set.phtml`) les donne pour un même type à
trois évaluations : `set` ne compare que du texte, `fset` évalue ses éléments
comme des expressions formelles, `aset` comme des expressions approximatives.
`anstype/aset` y ajoute un préambule — `!declosing`, `!listuniq`, la coupe sur
les espaces — puis compare les deux ensembles en confiant à `anstype/function`
les polynômes ∏(J−xᵢ) formés de chaque côté.

Employé par `oef-resoudre/eq_prod` (deux champs, les solutions d'une équation
produit) et par `OEFalkashi/seconddeg`, dont le champ arrive à la troisième
étape d'un exercice `course`.
"""
from core.answer.checkers import check_aset, check_answer

# La précision de `eq_prod` : l'énoncé demande « la valeur exacte ou une valeur
# approchée à 1e-3 près ».
_OPT = {"precision": 1000.0}


def _res(reply, expected="3/7,1/90"):
    return check_answer("aset", reply, expected, _OPT, "fr")


class TestDispatch:
    def test_aset_ne_retombe_plus_sur_check_text(self):
        """La dette portée ici : `check_text` refusait toute écriture autre que
        la référence, et ne rendait donc juste que `3/7,1/90` mot pour mot."""
        assert _res("3/7,1/90").method == "aset"

    def test_la_bonne_reponse_vaut_un(self):
        assert _res("3/7,1/90").score == 1.0


class TestEnsemble:
    """L'ordre ne compte pas, les doublons non plus : c'est un ensemble."""

    def test_l_ordre_est_indifferent(self):
        assert _res("1/90,3/7").correct

    def test_les_doublons_sont_reduits(self):
        """`!listuniq` s'applique **avant** de compter les cardinaux ; sans lui,
        `check_fset` verrait trois éléments contre deux."""
        assert _res("3/7,3/7,1/90").correct

    def test_le_doublon_ne_dispense_pas_d_une_solution(self):
        assert not _res("3/7,3/7").correct


class TestEcritures:
    """Ce que `anstype/aset` accepte avant de comparer."""

    def test_les_delimiteurs_englobants_tombent(self):
        """L'énoncé pose « \\(S =\\) » devant le champ : l'élève écrit
        volontiers l'ensemble avec ses accolades."""
        assert _res("{3/7,1/90}").correct
        assert _res("(3/7,1/90)").correct
        assert _res("[3/7,1/90]").correct

    def test_les_espaces_separent_faute_de_virgule(self):
        """`!if , notin $dd → !words2items` : l'espace ne sépare qu'à défaut."""
        assert _res("3/7 1/90").correct

    def test_le_point_virgule_separe_aussi(self):
        """En locale à virgule décimale, `;` est le séparateur de liste
        (`core/oef/i18n.py`) — c'est ce qu'un élève francophone écrit."""
        assert _res("3/7;1/90").correct

    def test_les_valeurs_approchees_conviennent(self):
        """« approximatif » est ce qui distingue `aset` de `fset`."""
        assert _res("0.428571,0.011111").correct

    def test_une_valeur_trop_grossiere_est_refusee(self):
        assert not _res("0.43,0.011").correct


class TestToutOuRien:
    """WIMS compare deux polynômes : un seul élément faux les sépare, et il n'y
    a pas de demi-mesure. Le score partiel de `check_fset` en accorderait."""

    def test_une_solution_fausse_annule_tout(self):
        assert _res("3/7,1/9").score == 0.0

    def test_une_solution_manquante_annule_tout(self):
        assert _res("3/7").score == 0.0

    def test_une_solution_en_trop_annule_tout(self):
        assert _res("3/7,1/90,2").score == 0.0


class TestCardinal:
    def test_le_cardinal_prime_sur_le_contenu(self):
        """`!if $n1!=$n2 → badsize`, avant toute comparaison d'éléments."""
        res = check_aset("1,2,3", "1,2", precision=1000.0)
        assert not res.correct
        assert res.score == 0.0

    def test_un_singleton_se_compare_comme_tel(self):
        assert check_aset("-4", "-8/2", precision=1000.0).correct
