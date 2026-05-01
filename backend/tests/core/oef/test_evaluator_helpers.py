import os
import random
import sys

import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))
from core.oef.evaluator import (
    OEFEvaluator,
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
