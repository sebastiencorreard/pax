"""Plages et listes d'indices pour `!row` et `!word`.

`calc.c` route `item`, `line`, `row`, `word` et `char` par le **même**
`_blockof` : tous acceptent donc un indice, une plage (`3 to -1`, `2..3`) ou
une liste (`1,3`). PAX avait bien ce sélecteur générique, mais `!row` et
`!word` ne s'y branchaient pas et ne géraient que l'indice simple.
"""

from core.oef.def_engine import DefEngine, load_and_render


def engine() -> DefEngine:
    e = DefEngine(seed=1)
    e.ctx["m"] = "l1\nl2\nl3\nl4"
    e.ctx["s"] = "a,b;c,d;e,f"
    e.ctx["w"] = "un deux trois quatre"
    return e


class TestRow:
    def test_single_index_unchanged(self):
        assert engine()._eval_cmd("row", "2 of $m") == "l2"

    def test_open_ended_range(self):
        # La forme qui bloquait `arithtable` : `!row 3 to -1` sur un
        # enregistrement de 3 lignes rendait la chaîne vide.
        assert engine()._eval_cmd("row", "3 to -1 of $m") == "l3\nl4"

    def test_dotted_range(self):
        assert engine()._eval_cmd("row", "2..3 of $m") == "l2\nl3"

    def test_index_list(self):
        assert engine()._eval_cmd("row", "1,3 of $m") == "l1\nl3"

    def test_output_separator_follows_the_input(self):
        # `calc_rowof` ressort les lignes avec leur séparateur d'origine.
        assert engine()._eval_cmd("row", "2 to -1 of $s") == "c,d;e,f"


class TestWord:
    def test_single_index_unchanged(self):
        assert engine()._eval_cmd("word", "2 of $w") == "deux"

    def test_range(self):
        assert engine()._eval_cmd("word", "2 to -1 of $w") == "deux trois quatre"

    def test_index_list(self):
        assert engine()._eval_cmd("word", "1,3 of $w") == "un trois"

    def test_out_of_range_is_empty(self):
        assert engine()._eval_cmd("word", "9 of $w") == ""


class TestCorpus:
    def test_arithtable_computes_its_cells(self):
        """`val33=!record N of src/data_<lang>` puis `!row 3 to -1` en extrait
        la liste de nombres. La plage rendant vide, plus aucune valeur n'était
        tirée : les cellules affichaient `expand((f = s \\in) + ())`."""
        r = load_and_render(
            "/ressources/H3/algebra/arithtable.en/def/table2x2.def", seed=42
        )
        c = r.ev_ctx
        assert c["val33"], "la liste de nombres du fichier de données est vide"
        # val47 = les 4 valeurs tirées ; val50/val53 = sommes lignes/colonnes.
        values = [int(x) for x in c["val47"].split(",")]
        assert len(values) == 4
        rows = [int(x) for x in c["val50"].split(",")]
        assert rows == [values[0] + values[1], values[2] + values[3]]
        cols = [int(x) for x in c["val53"].split(",")]
        assert cols == [values[0] + values[2], values[1] + values[3]]

    def test_country_lists_are_recovered(self):
        """`oefcountries` construit ses colonnes avec `!row` ; elles étaient
        vides (l'exercice n'avait plus aucun pays à apparier)."""
        r = load_and_render(
            "/ressources/H3/geography/oefcountries.en/def/flagall.def", seed=42
        )
        expected = r.answers[0].expected
        assert len(expected.split(",")) > 1, expected
