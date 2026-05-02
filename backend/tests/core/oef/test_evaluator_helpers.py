import os
import random
import sys
from fractions import Fraction


sys.path.insert(
    0,
    os.path.dirname(
        os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    ),
)
from core.oef.evaluator import (
    OEFEvaluator,
    _eval_exact_arithmetic,
    _expr_to_latex,
    _pick_randitem_template,
    _split_top_level_commas,
    _to_exact,
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
    out = ev._eval_expr(r"pari(\v[2]*\v[3]/\v[1]),pari(\v[5]/(\v[6]*\v[4]))")
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


# ---------- randint(a..b) preprocessing ---------- #


def test_randint_range_evaluates_to_integer():
    """Bug : randint(2..13) était stocké littéralement au lieu d'être évalué."""
    import random as _random
    _random.seed(0)
    ev = OEFEvaluator(seed=0)
    ev.evaluate_source(r"\integer{v=randint(2..13)}")
    val = ev.ctx["v"]
    assert val.lstrip("-").isdigit(), f"Expected integer string, got {val!r}"
    assert 2 <= int(val) <= 13


def test_randint_range_used_in_rep():
    """Reproduction du bug equatcar3.oef : rep=\\v,-\\v ne doit pas contenir randint."""
    ev = OEFEvaluator(seed=5)
    ev.evaluate_source(r"\integer{v=randint(2..13)}" + "\n" + r"\text{rep=\v,-\v}")
    assert "randint" not in ev.ctx["rep"]
    parts = [p.strip() for p in ev.ctx["rep"].split(",")]
    assert len(parts) == 2
    assert int(parts[0]) == -int(parts[1])


def test_text_with_equation_template():
    """Bug equatcar3.oef : \\text{enonce=\\x^2=\\a} stockait '0' (bool False) au lieu
    de la chaîne substituée."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["x"] = "x"
    ev.ctx["a"] = "9"
    ev.evaluate_source(r"\text{enonce=\x^2=\a}")
    assert ev.ctx["enonce"] == "x^2=9"


def test_text_arithmetic_still_works():
    """La correction ne doit pas casser \\text{b=\\a * 2} qui fait de l'arithmétique."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "7"
    ev.evaluate_source(r"\text{b=\a * 2}")
    assert ev.ctx["b"] == "14"


# ---------- moins unaire et ternaire ---------- #


def test_neg_atom_variable():
    """Bug equation5.oef : -\\v[2] n'était pas parseable (pas de moins unaire)."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "7"
    result = ev._eval_expr(r"-\a")
    assert result == Fraction(-7)


def test_ternary_true_branch():
    """\\v[1]=-\\v[2]?10:\\v[1] → 10 quand v[1] = -v[2]."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["v1"] = "3"
    ev.ctx["v2"] = "-3"   # -v[2] = 3 = v[1] → condition vraie
    ev.evaluate_source(r"\text{res=\v1=-\v2?10:\v1}")
    assert ev.ctx["res"] == "10"


def test_ternary_false_branch():
    """\\v[1]=-\\v[2]?10:\\v[1] → \\v[1] quand v[1] ≠ -v[2]."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["v1"] = "3"
    ev.ctx["v2"] = "5"    # -v[2] = -5 ≠ 3 → condition fausse
    ev.evaluate_source(r"\text{res=\v1=-\v2?10:\v1}")
    assert ev.ctx["res"] == "3"


def test_ternary_negative_then():
    """\\v[3]=-\\v[4]?-10:\\v[3] → -10 quand condition vraie."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["v3"] = "4"
    ev.ctx["v4"] = "-4"
    ev.evaluate_source(r"\text{res=\v3=-\v4?-10:\v3}")
    assert ev.ctx["res"] == "-10"


# ---------- _expr_to_latex ---------- #


def test_expr_to_latex_simple_fraction():
    assert _expr_to_latex("10/3*z") == r"\frac{10}{3}z"


def test_expr_to_latex_negative_denominator():
    assert _expr_to_latex("7/-4*y") == r"-\frac{7}{4}y"


def test_expr_to_latex_negative_numerator():
    assert _expr_to_latex("-8/9") == r"-\frac{8}{9}"


def test_expr_to_latex_both_negative():
    assert _expr_to_latex("-5/-6*u") == r"\frac{5}{6}u"


def test_expr_to_latex_equation5_seed1():
    """Cas réel equation5.oef seed=1 : 7/-4*y+-10/9=169/18."""
    result = _expr_to_latex("7/-4*y+-10/9=169/18")
    assert result == r"-\frac{7}{4}y-\frac{10}{9}=\frac{169}{18}"


def test_expr_to_latex_no_fraction():
    """Les expressions sans fraction ne doivent pas être modifiées (sauf les signes)."""
    assert _expr_to_latex("x+3=-3") == "x+3=-3"


# ---------- arithmétique exacte (_to_exact, product, math_expr) ---------- #


def test_to_exact_integer_string():
    assert _to_exact("3") == Fraction(3)
    assert _to_exact("-5") == Fraction(-5)


def test_to_exact_fraction_string():
    assert _to_exact("2/3") == Fraction(2, 3)
    assert _to_exact("-7/4") == Fraction(-7, 4)


def test_to_exact_int_object():
    assert _to_exact(4) == Fraction(4)


def test_to_exact_float_integer():
    assert _to_exact(3.0) == Fraction(3)


def test_to_exact_float_decimal_returns_none():
    assert _to_exact(3.14) is None
    assert _to_exact("3.14") is None


def test_to_exact_fraction_object_passthrough():
    f = Fraction(5, 7)
    assert _to_exact(f) is f


def test_division_of_context_integers_gives_fraction():
    """Bug rapporté : \\v[2]/\\v[1] retournait 0.666... au lieu de 2/3."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "2"
    ev.ctx["b"] = "3"
    result = ev._eval_expr(r"\a/\b")
    assert result == Fraction(2, 3)


def test_wims_string_fraction():
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "2"
    ev.ctx["b"] = "3"
    ev.evaluate_source(r"\text{rep=\a/\b}")
    assert ev.ctx["rep"] == "2/3"


def test_fraction_addition_gives_exact():
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "1"
    ev.ctx["b"] = "3"
    ev.ctx["c"] = "1"
    ev.ctx["d"] = "6"
    ev.evaluate_source(r"\text{rep=\a/\b+\c/\d}")
    assert ev.ctx["rep"] == "1/2"


def test_fraction_addition_whole_result():
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "1"
    ev.ctx["b"] = "3"
    ev.ctx["c"] = "2"
    ev.ctx["d"] = "3"
    ev.evaluate_source(r"\text{rep=\a/\b+\c/\d}")
    assert ev.ctx["rep"] == "1"


def test_fraction_multiplication():
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "2"
    ev.ctx["b"] = "3"
    ev.ctx["c"] = "6"
    ev.evaluate_source(r"\text{rep=\a/\b*\c}")
    assert ev.ctx["rep"] == "4"


def test_integer_power_of_fraction():
    ev = OEFEvaluator(seed=1)
    ev.ctx["a"] = "2"
    ev.ctx["b"] = "3"
    ev.evaluate_source(r"\text{rep=(\a/\b)^2}")
    assert ev.ctx["rep"] == "4/9"


def test_comparison_with_fraction_context():
    """\\if avec une variable fraction en contexte ne doit pas crasher."""
    ev = OEFEvaluator(seed=1)
    ev.ctx["x"] = "2/3"
    ev.evaluate_source(r"\if{\x>0}{\text{sign=pos}}{\text{sign=neg}}")
    assert ev.ctx.get("sign") == "pos"


def test_equaprod4_rep_is_fraction():
    """Reproduction du bug de l'exercice equaprod4.oef."""
    ev = OEFEvaluator(seed=7)
    ev.ctx["v"] = "3,2,5,4,7,6,9,8"
    ev.ctx["x"] = "x"
    ev.evaluate_source(r"\text{rep=\v[2]/\v[1]}")
    assert ev.ctx["rep"] == "2/3"
