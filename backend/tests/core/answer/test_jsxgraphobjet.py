"""`jsxgraphobjet` — les objets cliqués sur une figure JSXGraph.

Type défini par `H3/geometry/oeftrigoclg1.fr/anstype/jsxgraphobjet`, employé
par ses trois exercices de repérage des côtés d'un triangle rectangle.
"""
import pytest

from core.answer.checkers import check_answer
from core.oef.def_engine import _objets_cliquables


def _res(reply, expected, opt=""):
    return check_answer("jsxgraphobjet", reply, expected, {"option": opt}, "fr")


class TestObjetsCliquables:
    """Le `replygood` décrit la figure entière, pas seulement la bonne réponse :
    `!listuniq` sur `;`, `&` et `|` ramenés à la virgule."""

    def test_les_trois_separateurs_valent_la_virgule(self):
        assert _objets_cliquables("hypo;cat1|cat2") == ["hypo", "cat1", "cat2"]
        assert _objets_cliquables("cat1;hypo|cat2") == ["cat1", "hypo", "cat2"]
        assert _objets_cliquables("a&b;c|d") == ["a", "b", "c", "d"]

    def test_dedoublonne_en_conservant_l_ordre(self):
        assert _objets_cliquables("b;a|b,c") == ["b", "a", "c"]

    def test_ecarte_ce_qui_n_est_pas_un_identifiant(self):
        """Le nom finit en variable JavaScript dans le script de la figure."""
        assert _objets_cliquables("hypo;2 3;alert(1)") == ["hypo"]
        assert _objets_cliquables("") == []


class TestComparaison:
    """Sans `noorder`, `$(replygood)==$(reply$i)` — texte contre texte."""

    def test_seule_la_premiere_ligne_de_replygood_est_attendue(self):
        """`replygood=$(replygood$i[1;])` : `cat1|cat2` ne sont que des leurres."""
        assert _res("hypo", "hypo;cat1|cat2").correct
        assert not _res("cat1", "hypo;cat1|cat2").correct
        assert _res("cat1", "cat1;hypo|cat2").correct

    def test_le_nombre_d_objets_doit_coincider(self):
        """`!if $(cnt_rg)=!$(cnt_r)` → `score=0` : cliquer deux segments quand
        on en demande un ne vaut aucun point, fût-ce le bon parmi eux."""
        r = _res("hypo,cat1", "hypo;cat1|cat2")
        assert not r.correct and r.score == 0.0

    def test_reponse_vide(self):
        r = _res("", "hypo;cat1|cat2")
        assert not r.correct and r.score == 0.0

    def test_l_ordre_des_clics_compte(self):
        assert _res("a,b", "a,b").correct
        assert not _res("b,a", "a,b").correct


class TestNoorder:
    """Avec l'option, une part par objet retrouvé — le fichier accorde même un
    `partialgood` au-delà de 0,3."""

    @pytest.mark.parametrize("reply,score", [
        ("a,b", 1.0), ("b,a", 1.0), ("a,c", 0.5), ("c,d", 0.0),
    ])
    def test_score_partiel(self, reply, score):
        r = _res(reply, "a,b", opt="noorder")
        assert r.score == pytest.approx(score)
        assert r.correct is (score >= 1.0)
