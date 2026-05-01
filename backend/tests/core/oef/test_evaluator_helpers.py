import os
import random
import sys

import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))
from core.oef.evaluator import (
    OEFEvaluator,
    _eval_exact_arithmetic,
    _pick_randitem_template,
    _split_top_level_commas,
)


# ---------- _split_top_level_commas ---------- #

def test_split_top_level_simple():
    assert _split_top_level_commas("a,b,c") == ["a", "b", "c"]


def test_split_top_level_respects_parens():
    assert _split_top_level_commas("a(1,2),b") == ["a(1,2)", "b"]


def test_split_top_level_nested_parens():
    assert _split_top_level_commas("f(g(1,2),3),h(4)") == ["f(g(1,2),3)", "h(4)"]


def test_split_top_level_strips_whitespace():
    assert _split_top_level_commas("  a , b , c ") == ["a", "b", "c"]


def test_split_top_level_no_commas():
    assert _split_top_level_commas("alone") == ["alone"]


def test_split_top_level_empty():
    assert _split_top_level_commas("") == [""]


# ---------- _pick_randitem_template ---------- #

def test_pick_randitem_returns_one_arg():
    random.seed(0)
    out = _pick_randitem_template("randitem(foo,bar,baz)")
    assert out in {"foo", "bar", "baz"}


def test_pick_randitem_with_template_args():
    """Le bug original : args contiennent des = et des \\x — pas parsables comme expression."""
    expr = r"randitem(\x(\v[3]*\x+\v[4])=0,(\v[3]*\x+\v[4])\x=0)"
    random.seed(0)
    out = _pick_randitem_template(expr)
    assert out in {
        r"\x(\v[3]*\x+\v[4])=0",
        r"(\v[3]*\x+\v[4])\x=0",
    }


def test_pick_randitem_not_a_randitem():
    assert _pick_randitem_template("wims(values v for v=2 to 9)") is None
    assert _pick_randitem_template("2+3") is None
    assert _pick_randitem_template("") is None


def test_pick_randitem_unbalanced_outer_parens():
    """randitem(...) suivi d'autre chose ne doit pas être traité comme un randitem."""
    assert _pick_randitem_template("randitem(a,b)+1") is None


def test_pick_randitem_seed_reproducibility():
    """Même seed → même choix."""
    random.seed(42)
    a = _pick_randitem_template("randitem(x,y,z,t)")
    random.seed(42)
    b = _pick_randitem_template("randitem(x,y,z,t)")
    assert a == b


# ---------- _eval_exact_arithmetic ---------- #

def test_eval_exact_returns_int_when_whole():
    assert _eval_exact_arithmetic("8+1") == 9
    assert _eval_exact_arithmetic("4*3") == 12
    assert _eval_exact_arithmetic("6/3") == 2


def test_eval_exact_returns_fraction_string():
    assert _eval_exact_arithmetic("4*5/3") == "20/3"
    assert _eval_exact_arithmetic("7/(8*2)") == "7/16"
    assert _eval_exact_arithmetic("-(4+7)/(8+9)") == "-11/17"


def test_eval_exact_handles_decimal_exactly():
    assert _eval_exact_arithmetic("0.5*4") == 2
    assert _eval_exact_arithmetic("2.5/3") == "5/6"


def test_eval_exact_returns_none_on_non_arithmetic():
    assert _eval_exact_arithmetic("2*x") is None
    assert _eval_exact_arithmetic("") is None
    assert _eval_exact_arithmetic("a+b") is None


# ---------- pari preprocessing in _eval_expr ---------- #

def test_pari_with_nested_parens_keeps_fraction():
    """Bug initial: pari(7/(8*2)) renvoyait 0.4375 au lieu de 7/16."""
    ev = OEFEvaluator(seed=42)
    ev.ctx["v"] = "5,6,8,9,4,7,2,3"
    out = ev._eval_expr(r"pari(\v[5]/(\v[6]*\v[4]))")
    assert out == "4/63"


def test_pari_list_keeps_fractions_for_each_element():
    """Le cas equaprod5 : liste de pari avec parens imbriquées."""
    ev = OEFEvaluator(seed=42)
    ev.ctx["v"] = "5,6,8,9,4,7,2,3"
    out = ev._eval_expr(
        r"pari(\v[2]*\v[3]/\v[1]),pari(\v[5]/(\v[6]*\v[4]))"
    )
    # Liste : ['48/5', '4/63']
    assert isinstance(out, list)
    assert out == ["48/5", "4/63"]


def test_pari_flat_still_works():
    """Régression : pari sans parens internes doit toujours marcher."""
    ev = OEFEvaluator(seed=42)
    ev.ctx["v"] = "8,2"
    assert ev._eval_expr(r"pari(\v[1]+1)") == 9


# ---------- intégration via OEFEvaluator ---------- #

def test_evaluator_falls_back_to_randitem_picker():
    """Reproduit le bug : enonce=randitem(...) avec args templates."""
    ev = OEFEvaluator(seed=42)
    # Quelques variables à substituer dans le branch choisi
    ev.ctx["x"] = "v"
    ev.ctx["v"] = "2,3,4,5,6,7,8,9"
    expr = r"randitem(\x(\v[3]*\x+\v[4])=0,(\v[3]*\x+\v[4])\x=0)"
    out = ev._eval_expr(expr)
    # Plus de "randitem" dans le résultat, et les variables sont substituées
    assert "randitem" not in out
    assert "\\x" not in out
    assert "\\v" not in out
    # Une des deux formes attendues, avec v[3]=4, v[4]=5, x=v
    assert out in {"v(4*v+5)=0", "(4*v+5)v=0"}
