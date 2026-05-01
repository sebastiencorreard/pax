"""
Évaluateur de variables OEF.
Optimisé pour la résolution des fonctions WIMS et la clarté de l'affichage.
"""
import re
import math
import random
from typing import Any, List
from fractions import Fraction
from lark import Lark, Transformer, v_args, Token
from .parser import Directive, OEFNode

EXPR_GRAMMAR = r"""
    ?start: expression_list

    ?expression_list: expression ("," expression)* -> list_val
    
    ?expression: ternary | logic_or

    ?ternary: logic_or "?" expression (":" expression)?

    ?logic_or: logic_and ("or" logic_and)*
    ?logic_and: comparison ("and" comparison)*

    ?comparison: math_expr (COMP_OP math_expr)*
    
    ?math_expr: product (ADD_OP product)*
    ?product: power (MULT_OP power)*
    ?power: atom ("^" atom)*

    ?atom: number | string | variable | func_call | "(" expression_list ")" | range

    range: atom ".." atom
    variable: BACKSLASH NAME ("[" index_list "]")?
    index_list: expression_list

    func_call: "wims" "(" RAW_CONTENT ")" -> wims_call
             | "pari" "(" RAW_CONTENT ")" -> pari_call
             | NAME "(" (arg_list)? ")"
             | "slib" "(" PATH (arg_list)? ")"
             | "items" "(" (arg_list)? ")"

    arg_list: expression_list

    number: SIGNED_NUMBER
    string: /'[^']*'/ | /"[^"]*"/ | /[a-zA-Z_][a-zA-Z0-9_ ]*/
    
    PATH: /[a-zA-Z0-9_\/]+/
    NAME: /[a-zA-Z0-9_]+/
    BACKSLASH: "\\"
    
    RAW_CONTENT: /.+?(?=\))/

    COMP_OP: "==" | "!=" | ">=" | "<=" | ">" | "<" | "not" | "="
    ADD_OP: "+" | "-"
    MULT_OP: "*" | "/" | "%"

    %import common.SIGNED_NUMBER
    %import common.WS
    %ignore WS
"""

class AbortAssignment(Exception): pass

class OEFEvaluator:
    def __init__(self, seed: int | None = None):
        self.ctx = {f"confparm{i}": "" for i in range(1, 10)}
        self.meta = {}
        if seed is not None:
            self.meta["seed"] = seed
            random.seed(seed)
        self._expr_parser = Lark(EXPR_GRAMMAR, parser='earley', maybe_placeholders=False)

    def evaluate_ast(self, ast: OEFNode):
        if ast.type == "document" and isinstance(ast.content, list):
            self._eval_nodes(ast.content)
        return self.ctx

    def evaluate_source(self, source: str) -> dict:
        from .parser import parse
        return self.evaluate_ast(parse(source))

    def _eval_nodes(self, nodes: list):
        for node in nodes:
            if isinstance(node, OEFNode): self._eval_node(node)
            elif isinstance(node, list): self._eval_nodes(node)

    def _eval_node(self, node: OEFNode):
        if node.type == "instruction":
            if node.name in ["integer", "real", "rational", "text", "function", "matrix"]:
                content = "".join(self._to_raw_string(arg) for arg in node.args)
                if "=" in content:
                    varname, expr = content.split("=", 1)
                    varname = varname.strip().lstrip("\\")
                    try:
                        val = self._eval_expr(expr)
                        self.ctx[varname] = self._to_wims_string(val)
                    except AbortAssignment: pass
            elif node.name == "if":
                if len(node.args) >= 1:
                    cond = self._eval_expr(self._to_raw_string(node.args[0]), kind="logic")
                    if cond and len(node.args) >= 2: self._eval_nodes(node.args[1])
                    elif not cond and len(node.args) >= 3: self._eval_nodes(node.args[2])
            elif node.name == "while":
                if len(node.args) >= 2:
                    cond_raw = self._to_raw_string(node.args[0])
                    for _ in range(50):
                        if not self._eval_expr(cond_raw, kind="logic"): break
                        self._eval_nodes(node.args[1])
            elif node.name in ["title", "author", "email", "language", "range", "keywords"]:
                self.meta[node.name] = self.render_node(node.args)

    def _eval_expr(self, expr_str: str, kind: str = "text") -> Any:
        try:
            tree = self._expr_parser.parse(expr_str.strip())
            val = OEFExprEvaluator(self.ctx, self).transform(tree)
            if kind == "logic": return bool(val)
            return val
        except Exception as e:
            cause = getattr(e, "orig_exc", None)
            if isinstance(cause, AbortAssignment): raise cause
            # randitem(template1, template2, ...) used as a textual chooser
            # (args contain literal LaTeX/template content the math grammar
            # can't parse). Pick a random branch then substitute variables.
            picked = _pick_randitem_template(expr_str.strip())
            if picked is not None:
                return self._substitute_vars(picked).strip()
            return self._substitute_vars(expr_str).strip()

    def _to_wims_string(self, val: Any) -> str:
        if isinstance(val, list): return ",".join(self._to_wims_string(i) for i in val)
        if isinstance(val, bool): return "1" if val else "0"
        if isinstance(val, float) and val.is_integer(): return str(int(val))
        return str(val)

    def render_node(self, node: Any) -> str:
        if isinstance(node, str): return self._substitute_vars(node)
        if isinstance(node, list): return "".join(self.render_node(i) for i in node)
        if isinstance(node, OEFNode):
            if node.type == "variable": return str(self.ctx.get(node.name, f"\\{node.name}"))
            if node.type == "math": return f"\\({self.render_node(node.content)}\\)"
            if node.type == "braced_group": return f"{self.render_node(node.content)}"
            if node.type == "instruction":
                if node.name == "special" and len(node.args) >= 2:
                    stype = self._to_raw_string(node.args[0]).strip()
                    if stype.startswith("color="):
                        return f'<span style="color:{stype.split("=", 1)[1]}">{self.render_node(node.args[1])}</span>'
                if node.name == "embed" and len(node.args) >= 1:
                    raw_arg = self._to_raw_string(node.args[0]).strip()
                    parts = raw_arg.split(",", 1)
                    target = self._substitute_vars(parts[0].strip())
                    size = self._substitute_vars(parts[1].strip()) if len(parts) > 1 else ""
                    return f'<span class="oef-input" name="{target}" data-size="{size}"></span>'
                return f"\\{node.name}" + "".join(f"{{{self.render_node(a)}}}" for a in node.args)
            if node.content: return self.render_node(node.content)
        return ""

    def _to_raw_string(self, obj) -> str:
        if isinstance(obj, str): return obj
        if isinstance(obj, list): return "".join(self._to_raw_string(i) for i in obj)
        if isinstance(obj, OEFNode):
            if obj.type == "variable": return f"\\{obj.name}"
            if obj.type == "math": return f"\\({self._to_raw_string(obj.content)}\\)"
            if obj.type == "braced_group": return f"{{{self._to_raw_string(obj.content)}}}"
            if obj.type == "instruction":
                return f"\\{obj.name}" + "".join(f"{{{self._to_raw_string(a)}}}" for a in obj.args)
            if obj.content: return self._to_raw_string(obj.content)
        return str(obj)

    def _substitute_vars(self, text: str) -> str:
        def replace_indexed(m):
            name, idx_str = m.groups()
            val = self.ctx.get(name, "")
            try:
                idx = int(float(self._eval_expr(idx_str))) - 1
                parts = [x.strip() for x in str(val).split(",")]
                return parts[idx] if 0 <= idx < len(parts) else ""
            except: return ""
        text = re.sub(r'\\([a-zA-Z0-9_]+)\[([^\]]+)\]', replace_indexed, text)
        text = re.sub(r'\\([a-zA-Z0-9_]+)', lambda m: str(self.ctx.get(m.group(1), m.group(0))), text)
        return text

class OEFExprEvaluator(Transformer):
    def __init__(self, ctx, evaluator):
        self.ctx = ctx
        self.evaluator = evaluator

    def list_val(self, items):
        # Un seul item : retourner la valeur directement (évite d'emballer en liste)
        return items[0] if len(items) == 1 else items

    @v_args(inline=True)
    def expression(self, item): return item

    @v_args(inline=True)
    def ternary(self, cond, true_val, false_val=None):
        if cond: return true_val
        if false_val is not None: return false_val
        raise AbortAssignment()

    def logic_or(self, items): return any(items)
    def logic_and(self, items): return all(items)

    def comparison(self, items):
        left = items[0]
        for i in range(1, len(items), 2):
            op, right = str(items[i]), items[i+1]
            if op in ("==", "=", "==="): left = (str(left) == str(right))
            elif op == "!=": left = (str(left) != str(right))
            else:
                try:
                    l, r = float(left), float(right)
                    if op == ">": left = (l > r)
                    elif op == "<": left = (l < r)
                    elif op == ">=": left = (l >= r)
                    elif op == "<=": left = (l <= r)
                except: left = False
        return left

    def math_expr(self, items):
        res = items[0]
        for i in range(1, len(items), 2):
            op, val = str(items[i]), items[i+1]
            try: res = float(res) + float(val) if op == "+" else float(res) - float(val)
            except: pass
        return res

    def product(self, items):
        res = items[0]
        for i in range(1, len(items), 2):
            op, val = str(items[i]), items[i+1]
            try:
                if op == "*": res = float(res) * float(val)
                elif op == "/": res = float(res) / float(val)
                else: res = float(res) % float(val)
            except: pass
        return res

    def power(self, items):
        res = items[0]
        for i in range(1, len(items)):
            try: res = float(res) ** float(items[i])
            except: pass
        return res

    @v_args(inline=True)
    def number(self, t): return float(t)

    @v_args(inline=True)
    def string(self, t): return str(t).strip("'\"")

    def variable(self, items):
        name = str(items[1].value)
        val = self.ctx.get(name, "0")
        if len(items) > 2:
            try:
                idx_expr = self.evaluator._to_raw_string(items[2])
                idx = int(float(self.evaluator._eval_expr(idx_expr))) - 1
                return [x.strip() for x in str(val).split(",")][idx]
            except: return ""
        return val

    def func_call(self, items):
        name = str(items[0])
        args = items[1] if len(items) > 1 else []
        
        if name in ("random", "randitem"):
            lst = args if isinstance(args, list) else [args]
            return random.choice(lst)
        if name == "randint":
            try:
                if isinstance(args, str) and ".." in args: a, b = map(int, args.split('..'))
                elif isinstance(args, list) and len(args) >= 2: a, b = int(float(args[0])), int(float(args[1]))
                else: a, b = 0, 10
                return float(random.randint(a, b))
            except: return 0.0
        if name == "item":
            try:
                idx = int(float(args[0])) - 1
                lst = args[1:] if len(args) > 2 else str(args[1]).split(",")
                return lst[idx] if 0 <= idx < len(lst) else ""
            except: return ""
        if name == "items":
            lst = args if isinstance(args, list) else str(args).split(",")
            return float(len([x for x in lst if str(x).strip()]))
        if name in ("abs", "sqrt", "floor", "ceil"):
            try: return float(getattr(math, name)(float(args[0] if isinstance(args, list) else args)))
            except: return 0.0
        if name == "shuffle":
            # args est [csv_string] après arg_list fix → on split le CSV
            if isinstance(args, list) and len(args) == 1 and isinstance(args[0], str):
                lst = [x.strip() for x in args[0].split(",")]
            elif isinstance(args, list):
                lst = list(args)
            else:
                lst = str(args).split(",")
            random.shuffle(lst)
            return lst  # retourné comme liste ; _to_wims_string join avec ","
        return self.evaluator._to_wims_string(args)

    @v_args(inline=True)
    def wims_call(self, content):
        inner = self.evaluator._substitute_vars(str(content.value))
        if "values" in inner and "for" in inner:
            m = re.search(r'values\s+(.+)\s+for\s+(\w+)\s*=\s*(\d+)\s+to\s+(\d+)', inner)
            if m:
                expr, var, start, end = m.groups()
                return [expr.replace(var, str(i)) for i in range(int(start), int(end)+1)]
        return [inner]

    @v_args(inline=True)
    def pari_call(self, content):
        inner = self.evaluator._substitute_vars(str(content.value)).strip()
        if inner.startswith("core("):
            try: return float(_pari_core(int(re.search(r'\d+', inner).group())))
            except: pass
        # Évalue l'expression arithmétique (ex: \v[1]+1 → "9+1" → 10)
        try:
            return self.evaluator._eval_expr(inner)
        except:
            return inner

    def range(self, items): return f"{items[0]}..{items[1]}"
    def index_list(self, items): return items
    def arg_list(self, items):
        # expression_list produit déjà une liste — on évite le double-wrapping
        return items[0] if len(items) == 1 else items

def _oef_cond_to_py(c: str) -> str:
    c = str(c).strip().replace("^", "**").replace("<>", "!=")
    return c.replace("=", "==").replace("====", "==").replace("<==", "<=").replace(">===", ">=")


def _split_top_level_commas(s: str) -> list[str]:
    """Découpe sur les virgules de profondeur 0, en respectant les parenthèses."""
    parts: list[str] = []
    depth = 0
    last = 0
    for i, ch in enumerate(s):
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        elif ch == ',' and depth == 0:
            parts.append(s[last:i])
            last = i + 1
    parts.append(s[last:])
    return [p.strip() for p in parts]


def _pick_randitem_template(expr: str) -> str | None:
    """
    Si expr est de la forme `randitem(a, b, c)` au niveau top-level,
    renvoie un des arguments choisi aléatoirement (sans substituer les variables).
    Sinon renvoie None. Utilisé pour les randitem dont les arguments ne sont
    pas des expressions parsables (templates contenant \\x, =, etc.).
    """
    if not expr.startswith("randitem(") or not expr.endswith(")"):
        return None
    # Vérifie que la parenthèse fermante finale clôt bien le randitem (pas une
    # parenthèse interne suivie d'autre chose).
    depth = 0
    for i, ch in enumerate(expr):
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
            if depth == 0 and i != len(expr) - 1:
                return None
    inner = expr[len("randitem("):-1]
    items = _split_top_level_commas(inner)
    items = [it for it in items if it]
    if not items:
        return None
    return random.choice(items)

def _pari_core(n: int) -> int:
    d = 2; res = n
    while d * d <= res:
        if res % (d * d) == 0: res //= (d * d)
        else: d += 1
    return res
