import pytest
from core.oef.def_engine import DefEngine, check_analyze
from core.oef.def_engine.cas import _call_maxima, _call_pari, _sympify_arg
from core.oef.def_parser import Assign, IfBlock

def test_sympify_implicit_multiplication():
    # Test implicit multiplication support
    expr1 = _sympify_arg("8 x")
    assert str(expr1) == "8*x"

    expr2 = _sympify_arg("8(x - 1)")
    assert str(expr2) == "8*x - 8"

def test_sympify_sign_normalization():
    # Test normalization of WIMS-style signs
    expr = _sympify_arg("8*x +- 8")
    assert str(expr) == "8*x - 8"
    
    expr2 = _sympify_arg("8*x -- 8")
    assert str(expr2) == "8*x + 8"

def test_def_engine_issametext():
    engine = DefEngine(seed=42)
    # Literal equality
    assert engine._eval_condition("ifval", "foo issametext foo") is True
    assert engine._eval_condition("ifval", "foo issametext bar") is False
    assert engine._eval_condition("ifval", "expand(8*x-8) isnotreexpanded expand(8*x-8)") is True

def test_def_engine_cmd_exec_subst():
    engine = DefEngine(seed=42)
    engine.ctx["t_"] = "expand((8*x-8)*(8-5*x))"
    # The engine should substitute $t_ before sending to CAS
    res = engine._eval_value("!exec maxima $t_")
    # Result should be the expanded polynomial
    assert res == "-40*x**2 + 104*x - 64"

def test_check_analyze():
    # Mock context from factdir1.def
    ev_ctx = {
        "val63": "-40*x**2 + 104*x - 64"
    }
    postdef = [
        Assign(name="t_", value="!exec maxima expand($val64 * $val65)"),
        Assign(name="val66", value="!exec maxima $t_")
    ]
    test_instr = [
        IfBlock(
            kind="ifval", 
            condition="$val66 issametext $val63",
            then_body=[Assign(name="condtest1", value="1")],
            else_body=[Assign(name="condtest1", value="0")]
        )
    ]

    # Test exact expected factors
    replies_perfect = {64: "8*x-8", 65: "8-5*x"}
    res1 = check_analyze(ev_ctx, postdef, test_instr, replies_perfect, seed=1)
    assert res1.get("condtest1") == 1

    # Test alternative valid factors (swapped)
    replies_swapped = {64: "8-5*x", 65: "8*x-8"}
    res2 = check_analyze(ev_ctx, postdef, test_instr, replies_swapped, seed=1)
    assert res2.get("condtest1") == 1

    # Test alternative valid factors (implicit mult and factored out)
    replies_implicit = {64: "8(x-1)", 65: "8 - 5 x"}
    res3 = check_analyze(ev_ctx, postdef, test_instr, replies_implicit, seed=1)
    assert res3.get("condtest1") == 1

    # Test invalid factors
    replies_wrong = {64: "8*x", 65: "8-5*x"}
    res4 = check_analyze(ev_ctx, postdef, test_instr, replies_wrong, seed=1)
    assert res4.get("condtest1") == 0
