import os
import sys
import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))
from core.answer.checkers import check_answer, check_fset


# Bug fix : type "fset" tombait dans le case "text" (comparaison de chaînes),
# donc -4 ne matchait pas -8/2.

def test_fset_dispatcher_routes_to_fset():
    """fset doit être dispatché vers check_fset, pas vers check_text."""
    result = check_answer("fset", "-4", "-8/2")
    assert result.method == "fset"
    assert result.correct is True
    assert result.score == 1.0


def test_fset_single_value_equivalent_forms():
    """Un seul élément exprimé sous différentes formes équivalentes."""
    assert check_fset("-4", "-8/2").correct
    assert check_fset("-4.0", "-8/2").correct
    assert check_fset("-4", "-4").correct
    assert check_fset("0.5", "1/2").correct


def test_fset_multiple_values_order_independent():
    """L'ordre des éléments n'a pas d'importance."""
    assert check_fset("-6/5,-9/8", "-9/8,-6/5").correct
    assert check_fset("-9/8,-4", "-8/2,-9/8").correct


def test_fset_mixed_decimal_and_fraction():
    """Forme décimale et fractionnaire mélangées des deux côtés."""
    assert check_fset("-1.125,-4", "-9/8,-8/2").correct


def test_fset_separator_semicolon():
    """Séparateur ; accepté en plus de ,."""
    assert check_fset("-4;-9/8", "-8/2;-9/8").correct


def test_fset_wrong_value():
    """Valeur incorrecte → faux."""
    r = check_fset("-4", "-3/2")
    assert r.correct is False
    assert r.score == 0.0


def test_fset_cardinality_mismatch():
    """Pas le bon nombre d'éléments → faux, score 0."""
    r = check_fset("1", "1,2")
    assert r.correct is False
    assert r.score == 0.0


def test_fset_partial_credit():
    """Un élément correct sur deux → score = 0.5, mais correct=False."""
    r = check_fset("-4,99", "-8/2,-9/8")
    assert r.correct is False
    assert r.score == pytest.approx(0.5)


def test_fset_empty_reply_against_non_empty_expected():
    """Réponse vide contre attendue non vide → faux."""
    r = check_fset("", "-8/2,-9/8")
    assert r.correct is False
    assert r.score == 0.0


def test_fset_duplicate_in_reply_does_not_double_count():
    """Une même valeur dupliquée ne doit pas matcher deux éléments distincts."""
    r = check_fset("-4,-4", "-8/2,-9/8")
    assert r.correct is False
    # Un -4 matche -8/2, l'autre ne matche pas -9/8
    assert r.score == pytest.approx(0.5)


def test_fset_falls_back_to_symbolic():
    """Quand le parseur numérique échoue, sympy doit prendre le relais."""
    # 2*x equivaut à x+x (forme symbolique, pas numérique)
    assert check_fset("2*x", "x+x").correct
