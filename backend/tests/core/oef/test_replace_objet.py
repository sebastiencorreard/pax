"""`!replace <style> [number n] … by … in …` — port de `_obj_replace`.

`calc_replace` (`calc.c`) lit d'abord `internal`, puis un **style** — `word`,
`item`, `line`, `char` —, puis `number`. PAX n'en gérait aucun : la forme
tombait dans le remplacement textuel, qui cherchait `item number 1` dans le
texte et n'y trouvait rien. 591 `!replace item number` du corpus étaient ainsi
sans effet, en silence — `challenge2005b/triangle` proposait six étiquettes
valant toutes `0`, et les arbres d'`oefprobatree` n'avaient pas de branches.
"""
import pytest

from core.oef.def_engine import DefEngine
from core.oef.def_engine.wims_lists import replace_objet


def moteur() -> DefEngine:
    return DefEngine(seed=1)


class TestParNumero:
    """Avec `number`, c'est le n-ième objet qui est remplacé."""

    def test_item(self):
        assert replace_objet("1", "3", "0,0,0,0,0,0", "item", 1) == "3,0,0,0,0,0"
        assert replace_objet("6", "1", "3,0,0,6,0,0", "item", 6) == "3,0,0,6,0,1"

    def test_indice_negatif_compte_depuis_la_fin(self):
        assert replace_objet("", "X", "a,b,c", "item", -1) == "a,b,X"

    def test_hors_bornes_et_indice_nul_laissent_le_texte(self):
        # `_obj_replace` : `if(i>num || i<1) return;` — et `bad_index` pour 0,
        # que PAX ne peut pas remonter à l'élève.
        assert replace_objet("", "X", "a,b,c", "item", 9) == "a,b,c"
        assert replace_objet("", "X", "a,b,c", "item", 0) == "a,b,c"

    def test_les_blancs_de_bord_partent_avec_l_item(self):
        # La zone remplacée va du caractère qui suit la virgule précédente
        # jusqu'à celui qui suit la suivante (`fnd_position`, avant le
        # `find_word_start` de `fnd_item`).
        assert replace_objet("", "X", "a, b ,c", "item", 2) == "a,X,c"

    def test_word_line_char(self):
        assert replace_objet("", "X", "un deux trois", "word", 2) == "un X trois"
        assert replace_objet("", "L2", "l1\nl2\nl3", "line", 2) == "l1\nL2\nl3"
        assert replace_objet("", "Z", "abc", "char", 2) == "aZc"


class TestParOccurrence:
    """Sans `number`, ce sont les occurrences de l'objet, frontières comprises."""

    def test_item_entier_seulement(self):
        assert replace_objet("b", "X", "a, b ,c", "item") == "a, X ,c"
        # `ab` n'est pas un item de `a,ab,b` — mais `b` l'est, une seule fois.
        assert replace_objet("b", "X", "a,ab,b", "item") == "a,ab,X"

    def test_mot_entier_seulement(self):
        assert replace_objet("deux", "X", "un deux trois", "word") == "un X trois"
        assert replace_objet("un", "X", "un lundi un", "word") == "X lundi X"

    def test_char_prend_le_premier_caractere(self):
        assert replace_objet("b", "Z", "abcb", "char") == "aZcZ"


class TestCommandeComplete:
    """L'analyse de la commande, dans l'ordre du C."""

    @pytest.mark.parametrize(
        "args,attendu",
        [
            ("item number 1 by 3 in 0,0,0", "3,0,0"),
            ("internal item number 2 by X in a,b,c", "a,X,c"),
            ("item b by X in a, b ,c", "a, X ,c"),
            ("internal word deux by X in un deux trois", "un X trois"),
            ("char number 2 by Z in abc", "aZc"),
            ("line number 2 by L2 in l1\nl2\nl3", "l1\nL2\nl3"),
        ],
    )
    def test_formes(self, args, attendu):
        assert moteur()._cmd_replace(args) == attendu

    def test_l_indice_est_une_expression(self):
        e = moteur()
        e.ctx["i"] = "3"
        assert e._cmd_replace("item number 1+2 by X in a,b,c") == "a,b,X"

    def test_un_motif_vide_apres_un_style_rend_le_texte(self):
        # `calc_replace` : `if(bf[0][0]==0) {copie bf[2]; return;}` — ici le
        # style mange le seul mot disponible.
        assert moteur()._cmd_replace("internal line by X in a") == "a"

    def test_internal_coupe_toujours_la_voie_regexp(self):
        # Sans `internal`, `.` est un métacaractère et sed remplace tout ;
        # avec, le point est un point. La distinction ne doit pas se perdre
        # dans la lecture du style.
        assert moteur()._cmd_replace("internal . by , in 8000") == "8000"
        assert moteur()._cmd_replace("[0-9] by $ in UF4") == "UF"
