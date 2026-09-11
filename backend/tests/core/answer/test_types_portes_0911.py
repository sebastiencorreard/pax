"""Les sept types de réponse portés le 2026-09-11.

Ils retombaient sur `check_text` (égalité littérale) ; chaque checker suit
désormais son `anstype/<type>` de WIMS.
"""
from core.answer.checkers import (
    check_answer,
    check_chset,
    check_clicktile,
    check_complex,
    check_compose,
    check_crossword,
    check_matrix,
    check_reorder,
)


class TestChset:
    def test_ordre_et_espaces_ignores(self):
        assert check_chset("9 4", "49").correct
        assert check_chset("4,9", "94").correct

    def test_casse_et_accents_ignores(self):
        assert check_chset("A B", "ab").correct

    def test_norepeat(self):
        assert check_chset("aab", "ab", norepeat=True).correct
        assert not check_chset("aab", "ab", norepeat=False).correct

    def test_mauvaise_reponse(self):
        assert not check_chset("123", "49").correct


class TestReorder:
    def test_ordre_respecte(self):
        assert check_reorder("a,b,c", "a,b,c").correct

    def test_ordre_faux(self):
        assert not check_reorder("b,a,c", "a,b,c").correct


class TestCompose:
    def test_alternatives(self):
        assert check_compose("x < 2", "x < 2|2 > x").correct
        assert check_compose("2 > x", "x < 2|2 > x").correct

    def test_virgule_vaut_espace(self):
        assert check_compose("a,b,c", "a b c").correct

    def test_faux(self):
        assert not check_compose("x > 2", "x < 2").correct


class TestComplex:
    def test_nombre_simple(self):
        assert check_complex("2+3i", "2+3i").correct

    def test_j_option(self):
        assert check_complex("2+3j", "2+3i", use_j=True).correct

    def test_attendu_est_une_expression(self):
        # i^2 - 2i + 1 = -2i
        assert check_complex("-2i", "i^2-2*i+1").correct

    def test_faux(self):
        assert not check_complex("2-3i", "2+3i").correct

    def test_reponse_illisible(self):
        r = check_complex("blabla", "2+3i")
        assert not r.correct and r.status == "invalid_format"


class TestMatrix:
    def test_egalite(self):
        assert check_matrix("1,2;3,4", "1,2;3,4").correct

    def test_coefficients_evalues(self):
        # -6/3 == -2, 1+1 == 2
        assert check_matrix("-2,2", "-6/3,1+1").correct

    def test_dimension_differente(self):
        r = check_matrix("1,2,3", "1,2")
        assert not r.correct and r.status == "invalid_format"

    def test_coefficient_faux(self):
        assert not check_matrix("1,2;3,5", "1,2;3,4").correct


class TestClicktile:
    def test_groupes_par_couleur(self):
        # couleur, tuiles — l'ordre des clics ne compte pas
        assert check_clicktile("red,3;red,1", "red,1,3").correct

    def test_faux(self):
        assert not check_clicktile("red,1,2", "red,1,3").correct


class TestCrossword:
    ATTENDU = "[],[organeau,une définition\nbaleinière,une autre]"

    def test_mots_justes(self):
        assert check_crossword("organeau;baleinière", self.ATTENDU).correct

    def test_ordre_indifferent_accents_casse(self):
        assert check_crossword("BALEINIERE\nORGANEAU", self.ATTENDU).correct

    def test_mot_manquant(self):
        assert not check_crossword("organeau", self.ATTENDU).correct


class TestSecuriteConservee:
    def test_matrix_refuse_une_charge(self):
        # matrix évalue ses coefficients : le garde-fou doit tenir.
        r = check_answer("matrix", "().__class__,2", "1,2", {}, "fr")
        assert not r.correct
