import pytest
from core.oef.parser import parse, OEFNode

def test_parse_simple_command():
    src = r"\title{My Title}"
    ast = parse(src)
    assert ast.type == "document"
    content = [it for it in ast.content if isinstance(it, OEFNode)]
    assert len(content) == 1
    node = content[0]
    assert node.type == "instruction"
    assert node.name == "title"
    # Arguments are lists of content per block
    assert node.args == [["My Title"]]

def test_parse_variable():
    src = r"\text{a=1}\n\b"
    ast = parse(src)
    items = [it for it in ast.content if isinstance(it, OEFNode)]
    assert any(it.type == "instruction" and it.name == "text" for it in items)
    # \n and \b are both COMMAND_NAME tokens
    assert any(it.type == "variable" and it.name == "n" for it in items)
    assert any(it.type == "variable" and it.name == "b" for it in items)

def test_nested_blocks():
    src = r"\if{1=1}{\text{true_branch}}{\text{false_branch}}"
    ast = parse(src)
    content = [it for it in ast.content if isinstance(it, OEFNode)]
    node = content[0]
    assert node.type == "instruction"
    assert node.name == "if"
    assert len(node.args) == 3
    assert "true_branch" in str(node.args[1])

def test_math_environment():
    src = r"Calcul: \(\n1 + 2 = \res\)"
    ast = parse(src)
    math_nodes = [it for it in ast.content if isinstance(it, OEFNode) and it.type == "math"]
    assert len(math_nodes) == 1
    content = math_nodes[0].content
    # Check if variables inside math are recognized
    vars_in_math = [it for it in content if isinstance(it, OEFNode) and it.type == "variable"]
    assert any(v.name == "n1" for v in vars_in_math)
    assert any(v.name == "res" for v in vars_in_math)

def test_escaped_chars():
    src = r"Braces: \{ \}"
    ast = parse(src)
    # Escaped chars are returned as their literal value by the transformer
    assert "{" in ast.content
    assert "}" in ast.content

def test_orphan_backslash():
    src = r"A single backslash \ here."
    ast = parse(src)
    assert "\\" in ast.content

def test_complex_wims_name():
    src = r"\my_custom_var123"
    ast = parse(src)
    content = [it for it in ast.content if isinstance(it, OEFNode)]
    assert content[0].type == "variable"
    assert content[0].name == "my_custom_var123"
