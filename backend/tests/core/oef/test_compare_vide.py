"""Une chaîne vide vaut **zéro** dans une comparaison numérique WIMS.

`Lib/evalue.c:324` — `if(*evalue_pt==0) return 0; /* empty string */`. PAX n'y
arrivait pas : `_wims_eval_num("")` échouait, et `_wims_relational` retombait
sur une comparaison *textuelle* où `"" == "0"` est faux.

Le cas n'est pas théorique. Un `.def` teste couramment le résultat d'un calcul
qui a pu ne rien rendre, pour se rabattre sur une autre voie :

  - `oefpytha/etagere2` cherche un triplet pythagoricien par `!exec pari`. Sur
    `pyth(522,124,25)` il n'en existe aucun ; son `!ifval $(val18[1])==0` doit
    déclencher une seconde recherche, plus large, qui aboutit à
    `(672,754,1010)`. Le test étant faux, le repli ne partait pas, et l'énoncé
    proposait `[-1,,+2,-3]/10.` — l'expression PARI elle-même — en guise de
    palette de réponses.
  - `slib/chemistry/chemeq_equilibrium` compare la version du binaire à
    `1.119999` ; l'émulation ne la donnait pas, et le vide qui en sortait
    devait faire échouer le test.

Mesuré sur le corpus : 4406 comparaisons portent un opérande vide sans que le
verdict change, 1002 ont l'autre opérande inévaluable, et **246, sur 14
exercices, avaient le verdict inversé**.
"""

from core.oef.def_engine.compare import _wims_eval_num, _wims_relational


class TestChaineVideVautZero:
    def test_evaluation(self):
        assert _wims_eval_num("") == 0.0
        assert _wims_eval_num("   ") == 0.0
        # Ce qui n'est pas évaluable reste inévaluable.
        assert _wims_eval_num("chemeq") is None

    def test_egalite_a_zero(self):
        # `!ifval $(val18[1])==0` avec val18 vide : WIMS dit vrai.
        assert _wims_relational("", "0", 101, False, True) is True

    def test_inferieur(self):
        # `!if $slib_out < 1.119999` avec une version absente : vrai.
        assert _wims_relational("", "1.119999", 102, False, True) is True
        assert _wims_relational("1.119999", "", 102, False, True) is False

    def test_superieur(self):
        assert _wims_relational("", "-1", 103, False, True) is True
        assert _wims_relational("", "1", 103, False, True) is False

    def test_la_negation_suit(self):
        assert _wims_relational("", "0", 101, True, True) is False

    def test_une_comparaison_textuelle_ne_bouge_pas(self):
        # op_code 0 : `!if` non numérique, comparaison de chaînes.
        assert _wims_relational("", "0", 0, False, False) is False
        assert _wims_relational("", "", 0, False, False) is True
