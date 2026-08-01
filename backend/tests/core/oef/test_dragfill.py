"""`dragfill` — le `clickfill` dont chaque étiquette ne sert qu'une fois.

`help/anstype/clickfill.phtml` documente les deux comme un seul widget, à une
différence près (réutilisation des étiquettes). Faute de reconnaître le nom,
PAX lisait la taille `HxVxLxT` comme un `textarea` : les 132 exercices du
corpus s'ouvraient sur une zone de texte libre géante à la place du glisser-
déposer.

La composition de la palette suit `anstype/fill.inc` : ligne 1 (la réponse)
puis le complément des lignes suivantes, sans `!listuniq`.
"""

import pytest

from core.answer.checkers import check_answer, check_clickfill
from core.oef.def_engine import _normalize_reply_type, load_and_render


class TestNormalizeReplyType:
    def test_dragfill_folds_onto_clickfill(self):
        assert _normalize_reply_type("dragfill") == "clickfill"
        assert _normalize_reply_type(" DragFill ") == "clickfill"

    def test_other_types_are_untouched(self):
        assert _normalize_reply_type("clickfill") == "clickfill"
        assert _normalize_reply_type("numeric") == "numeric"


class TestCheckNoorder:
    def test_order_matters_by_default(self):
        assert check_clickfill("b,a", "a,b").correct is False

    def test_noorder_compares_the_multiset(self):
        assert check_clickfill("b,a", "a,b", noorder=True).correct is True
        assert check_clickfill("a,a", "a,b", noorder=True).correct is False

    def test_option_reaches_the_checker(self):
        opts = {"option": "noorder"}
        assert check_answer("clickfill", "b,a", "a,b", opts).correct is True
        assert check_answer("clickfill", "b,a", "a,b", {}).correct is False


class TestCorpusRendering:
    """Trois exercices représentatifs, rendus depuis le corpus."""

    def _answer(self, path, n=0):
        r = load_and_render(f"/ressources/{path}.def", seed=42)
        slots = sum(1 for s in r.statement_segments if s.get("type") == "slot")
        slots += sum(
            s.get("content", "").count("<cf-slot")
            for s in r.statement_segments if s.get("type") == "html"
        )
        return r, r.answers[n], slots

    def test_single_slot_becomes_a_drop_target_not_a_textarea(self):
        # vocabulaire1 : « quelle est l'hypoténuse ? », une case, trois segments
        # candidats. Sa taille `80 x 30` se lisait en textarea 80 lignes.
        r, a, slots = self._answer("H4/analysis/evalwimstrigo.fr/def/vocabulaire1")
        assert not any(s.get("type") == "textarea" for s in r.statement_segments)
        assert slots == 1
        assert a.answer_type == "clickfill"
        assert a.options["single_use"] is True
        assert a.expected in a.options["choices"]
        assert len(a.options["choices"]) == 3

    def test_absent_pool_makes_the_answer_its_own_palette(self):
        # geo4 : anagramme, on rassemble le nom d'une ville lettre à lettre.
        # `replygood` n'a qu'une ligne — le vivier, c'est la réponse mélangée.
        _r, a, slots = self._answer("H3/geography/oefdeutsch.fr/def/geo4")
        letters = a.expected.split(",")
        assert len(letters) > 1
        assert slots == len(letters)
        assert sorted(a.options["choices"]) == sorted(letters)

    def test_correct_sequence_scores(self):
        _r, a, _ = self._answer("H4/algebra/oeffctref.fr/def/cubineq1")
        assert check_answer(a.answer_type, a.expected, a.expected, a.options).correct
        reversed_reply = ",".join(reversed(a.expected.split(",")))
        assert not check_answer(
            a.answer_type, reversed_reply, a.expected, a.options
        ).correct

    @pytest.mark.parametrize("path", [
        "H4/analysis/evalwimstrigo.fr/def/vocabulaire1",
        "H3/geography/oefdeutsch.fr/def/geo4",
        "H4/algebra/oeffctref.fr/def/cubineq1",
        "H3/geometry/oefprogpythag.fr/def/raisonn2",
    ])
    def test_the_expected_answer_is_reachable_from_the_palette(self, path):
        """Chaque étiquette attendue doit exister en palette, et en assez
        d'exemplaires — c'est tout l'intérêt de ne pas dédoublonner."""
        _r, a, _ = self._answer(path)
        pool = list(a.options.get("choices") or [])
        for item in a.expected.split(","):
            assert item in pool, f"{item!r} absent de la palette de {path}"
            pool.remove(item)
