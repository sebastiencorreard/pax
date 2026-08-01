"""Indices en liste dans `$(var[ligne;colonne])`.

`calc.c` — `_blockof`, branche « sinon » — accepte pour un indice une **liste
séparée par des virgules**, évalue chaque terme et **ignore** ceux hors bornes
au lieu d'échouer. PAX ne gérait que l'indice simple et la plage `a..b` : un
`$(m[1;2,4])` retombait sur la chaîne vide, ce qui cassait tout brassage de
matrice écrit `$(val6[$perm_lignes;$perm_colonnes])`.
"""

from core.oef.def_engine import DefEngine, load_and_render


def engine() -> DefEngine:
    e = DefEngine(seed=1)
    e.ctx["m"] = "a,b,c,d;e,f,g,h"
    return e


class TestColumnIndexList:
    def test_list_selects_in_the_order_given(self):
        assert engine()._subst("$(m[1;2,4])") == "b,d"
        assert engine()._subst("$(m[1;4,2])") == "d,b"

    def test_out_of_range_indices_are_skipped_not_fatal(self):
        # `_blockof` fait `continue` : la sélection garde ce qu'elle peut.
        assert engine()._subst("$(m[1;2,9])") == "b"

    def test_negative_indices_count_from_the_end(self):
        assert engine()._subst("$(m[1;1,-1])") == "a,d"

    def test_the_list_may_come_from_a_variable(self):
        e = engine()
        e.ctx["idx"] = "2,4"
        assert e._subst("$(m[1;$idx])") == "b,d"
        assert e._subst("$(m[2;$idx])") == "f,h"

    def test_row_list_and_column_list_combine(self):
        assert engine()._subst("$(m[1,2;2,4])") == "b,d;f,h"

    def test_single_index_and_range_are_unchanged(self):
        e = engine()
        assert e._subst("$(m[1;2])") == "b"
        assert e._subst("$(m[1;2..4])") == "b,c,d"
        assert e._subst("$(m[1;])") == "a,b,c,d"


class TestCorpus:
    def test_arithtable_has_one_field_per_cell(self):
        """`val6=1,0;0,0` puis `$(val6[$val9;$val10])` brasse la table (`val9`
        et `val10` sont des permutations). La sélection revenant vide, aucune
        case n'était marquée « déjà remplie » et les 16 réponses déclarées
        recevaient toutes un champ, quelle que soit la taille du tableau."""
        for name, cells in [("table2x2", 4), ("table2x3", 6), ("table3x4", 12)]:
            r = load_and_render(
                f"/ressources/H3/algebra/arithtable.en/def/{name}.def", seed=42
            )
            slots = sum(1 for s in r.statement_segments if s.get("type") == "slot")
            slots += sum(
                s.get("content", "").count("<cf-slot")
                for s in r.statement_segments if s.get("type") == "html"
            )
            assert slots == cells, f"{name}: {slots} cases pour {cells} attendues"
            assert len(r.answers) == cells

    def test_evolmeth1_recovers_its_answer(self):
        r = load_and_render(
            "/ressources/H4/biology/evolmeth.fr/def/evolmeth1.def", seed=42
        )
        a = r.answers[0]
        # `val21`/`val22` viennent de `$(val12[1;$val17])`, val17 étant la liste
        # des colonnes tirée au sort : l'attendu valait « ;# » et la palette
        # était vide.
        assert a.expected.strip()
        assert a.expected in (a.options.get("choices") or [])
