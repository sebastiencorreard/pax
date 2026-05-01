"""
OEF Parser Module (Lark-based).
"""
from dataclasses import dataclass, field
from typing import Union, List, Any
from lark import Lark, Transformer, v_args, Token

OEF_GRAMMAR = r"""
    start: (comment | item)*

    ?item: command
         | variable
         | math_env
         | escaped_char
         | braced_group
         | backslash_orphan
         | text_block

    command.2: COMMAND_NAME _WS? "{" block_content "}" (_WS? "{" block_content "}")*
    variable: COMMAND_NAME
    math_env.2: MATH_START block_content MATH_END
    braced_group: "{" block_content "}"
    backslash_orphan.0: BACKSLASH
    block_content: (command | variable | math_env | escaped_char | braced_group | backslash_orphan | text_fragment)*
    
    escaped_char: ESC_CHAR
    MATH_START.3: "\\("
    MATH_END.3: "\\)"
    ESC_CHAR.2: /\\[{}%]/
    BACKSLASH: "\\"
    COMMAND_NAME.1: /\\([a-zA-Z][a-zA-Z0-9_]*|[0-9]+)/
    text_block: /[^\\{}%]+/s | /%/
    text_fragment: /[^\\{}]+/s
    COMMENT: /%%[^\n]*/
    _WS: /[ \t\f\r\n]+/
    comment: COMMENT
"""

@dataclass
class OEFNode:
    type: str
    name: str | None = None
    args: List[Any] = field(default_factory=list)
    content: Any = None

class OEFTransformer(Transformer):
    def _to_str(self, obj) -> str:
        if isinstance(obj, Token): return str(obj.value)
        if isinstance(obj, list): return "".join(self._to_str(i) for i in obj)
        if isinstance(obj, OEFNode):
            if obj.type == "variable": return f"\\{obj.name}"
            if obj.type == "math": return f"\\({self._to_str(obj.content)}\\)"
            if obj.type == "braced_group": return f"{{{self._to_str(obj.content)}}}"
            if obj.type == "instruction":
                res = f"\\{obj.name}"
                for arg in obj.args: res += f"{{{self._to_str(arg)}}}"
                return res
            if obj.content: return self._to_str(obj.content)
        return str(obj) if obj is not None else ""

    def start(self, items):
        flat = []
        for it in items:
            if isinstance(it, list): flat.extend(it)
            else: flat.append(it)
        return OEFNode(type="document", content=flat)

    def command(self, items):
        name = str(items[0].value)[1:].lower()
        args = []
        for it in items[1:]:
            if it is None or (isinstance(it, Token) and it.type == "_WS"): continue
            # On aplatit chaque bloc pour qu'il soit une liste simple d'items
            if isinstance(it, list):
                args.append(it)
            else:
                args.append([it])
        return OEFNode(type="instruction", name=name, args=args)

    def variable(self, items):
        return OEFNode(type="variable", name=str(items[0].value)[1:])

    def block_content(self, items):
        return list(items)

    def math_env(self, items):
        return OEFNode(type="math", content=items[1])

    def braced_group(self, items):
        return OEFNode(type="braced_group", content=items[0])

    def backslash_orphan(self, items): return "\\"

    @v_args(inline=True)
    def escaped_char(self, t): 
        val = str(t.value) if hasattr(t, "value") else str(t)
        return val[1:]

    @v_args(inline=True)
    def text_fragment(self, t): return str(t.value)

    @v_args(inline=True)
    def text_block(self, t): return str(t.value)

    @v_args(inline=True)
    def comment(self, t): return OEFNode(type="comment", content=str(t.value))

_PARSER = Lark(OEF_GRAMMAR, parser='earley', maybe_placeholders=False)
_TRANSFORMER = OEFTransformer()

def _reattach_braced_groups(nodes: list) -> list:
    """
    Earley peut parser {arg} comme un braced_group de niveau supérieur
    plutôt que comme arg supplémentaire d'une instruction précédente.
    Cette passe réattache les braced_groups orphelins à l'instruction qui précède.
    """
    new_content = []
    for item in nodes:
        if (isinstance(item, OEFNode) and item.type == "braced_group"
                and new_content
                and isinstance(new_content[-1], OEFNode)
                and new_content[-1].type == "instruction"):
            content = item.content if isinstance(item.content, list) else [item.content]
            new_content[-1].args.append(content)
        else:
            if isinstance(item, OEFNode):
                if item.type == "instruction":
                    item.args = [
                        _reattach_braced_groups(arg) if isinstance(arg, list) else arg
                        for arg in item.args
                    ]
                elif item.type == "braced_group" and isinstance(item.content, list):
                    item.content = _reattach_braced_groups(item.content)
            new_content.append(item)
    return new_content

def parse(source: str) -> OEFNode:
    source = source.replace('\r\n', '\n').replace('\r', '\n')
    ast = _TRANSFORMER.transform(_PARSER.parse(source))
    if isinstance(ast.content, list):
        ast.content = _reattach_braced_groups(ast.content)
    return ast

@dataclass
class Directive:
    name: str
    content: str

def _extract_braces(source: str, start: int) -> str:
    assert source[start] == '{'
    depth = 0; pos = start; n = len(source)
    while pos < n:
        if source[pos] == '{': depth += 1
        elif source[pos] == '}':
            depth -= 1
            if depth == 0: return source[start:pos + 1]
        pos += 1
    return source[start:]

def get_directives_compat(ast: OEFNode) -> List[Directive]:
    directives = []
    t = OEFTransformer()
    def _node_to_str(obj) -> str:
        return t._to_str(obj)
        
    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if isinstance(item, OEFNode) and item.type == "instruction":
                directives.append(Directive(name=item.name, content="".join(_node_to_str(arg) for arg in item.args)))
    return directives
