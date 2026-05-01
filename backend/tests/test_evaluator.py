from core.oef.evaluator import OEFEvaluator


def test_basic_logic():
    ev = OEFEvaluator(seed=42)
    src = r"\integer{a=3+4}\text{b=\a * 2}"
    ev.evaluate_source(src)
    assert ev.ctx["a"] == "7"
    assert ev.ctx["b"] == "14"


def test_if_logic():
    ev = OEFEvaluator(seed=0)
    src = r"\integer{a=5}\if{\a>3}{\integer{res=1}}{\integer{res=0}}"
    ev.evaluate_source(src)
    assert ev.ctx["res"] == "1"


def test_rendering_integration():
    ev = OEFEvaluator(seed=0)
    ev.ctx["name"] = "World"
    # Use raw string to avoid \n being interpreted as newline
    res = ev.render_node(r"Hello \name !")
    assert "Hello World !" in res
