"""
Évaluateur de variables OEF.
Optimisé pour la résolution des fonctions WIMS et la clarté de l'affichage.
"""

import re
import math
import random
from typing import Any
from fractions import Fraction
from lark import Lark, Transformer, v_args
from .parser import OEFNode

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

    ?atom: number | string | variable | func_call | "(" expression_list ")" | range | neg_atom

    neg_atom: "-" atom
    range: atom ".." atom
    variable: BACKSLASH NAME ("[" index_list "]")?
    index_list: expression_list

    func_call: "wims" "(" RAW_CONTENT ")" -> wims_call
             | "pari" "(" RAW_CONTENT ")" -> pari_call
             | "random" "(" RAW_CONTENT ")" -> random_call
             | "randint" "(" RAW_CONTENT ")" -> randint_call
             | "texmath" "(" RAW_CONTENT ")" -> texmath_call
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


class AbortAssignment(Exception):
    pass


class OEFEvaluator:
    def __init__(self, seed: int | None = None):
        self.ctx = {f"confparm{i}": "" for i in range(1, 10)}
        self.meta = {}
        if seed is not None:
            self.meta["seed"] = seed
            random.seed(seed)
        self._expr_parser = Lark(
            EXPR_GRAMMAR, parser="earley", maybe_placeholders=False
        )
        self._pari_counter = 0
        self._wims_counter = 0

    def evaluate_ast(self, ast: OEFNode):
        if ast.type == "document" and isinstance(ast.content, list):
            self._eval_nodes(ast.content)
        return self.ctx

    def evaluate_source(self, source: str) -> dict:
        from .parser import parse

        return self.evaluate_ast(parse(source))

    def _eval_nodes(self, nodes: list):
        for node in nodes:
            if isinstance(node, OEFNode):
                self._eval_node(node)
            elif isinstance(node, list):
                self._eval_nodes(node)

    def _eval_node(self, node: OEFNode):
        if node.type == "instruction":
            if node.name in [
                "integer",
                "real",
                "rational",
                "text",
                "function",
                "matrix",
            ]:
                content = "".join(self._to_raw_string(arg) for arg in node.args)
                if "=" in content:
                    varname, expr = content.split("=", 1)
                    varname = varname.strip().lstrip("\\")
                    try:
                        val = self._eval_expr(expr)
                        # Pour \text/\function/\matrix, un résultat booléen signifie
                        # que Lark a interprété un "=" littéral (ex: \x^2=\a) comme
                        # comparaison. On retombe sur la substitution de variables.
                        if isinstance(val, bool) and node.name in (
                            "text",
                            "function",
                            "matrix",
                        ):
                            val = self._substitute_vars(expr)
                        self.ctx[varname] = self._to_wims_string(val)
                    except AbortAssignment:
                        pass
            elif node.name == "if":
                if len(node.args) >= 1:
                    cond = self._eval_expr(
                        self._to_raw_string(node.args[0]), kind="logic"
                    )
                    if cond and len(node.args) >= 2:
                        self._eval_nodes(node.args[1])
                    elif not cond and len(node.args) >= 3:
                        self._eval_nodes(node.args[2])
            elif node.name == "while":
                if len(node.args) >= 2:
                    cond_raw = self._to_raw_string(node.args[0])
                    for _ in range(50):
                        if not self._eval_expr(cond_raw, kind="logic"):
                            break
                        self._eval_nodes(node.args[1])
            elif node.name == "for":
                if len(node.args) >= 2:
                    spec = self._to_raw_string(node.args[0]).strip()
                    m = re.match(r"(\w+)\s*=\s*(.+?)\s+to\s+(.+)", spec)
                    if m:
                        var, start_str, end_str = m.groups()
                        try:
                            start = int(float(self._eval_expr(start_str.strip())))
                            end = int(float(self._eval_expr(end_str.strip())))
                            for i in range(start, end + 1):
                                self.ctx[var] = str(i)
                                self._eval_nodes(node.args[1])
                        except Exception:
                            pass
            elif node.name in [
                "title",
                "author",
                "email",
                "language",
                "range",
                "keywords",
            ]:
                self.meta[node.name] = self.render_node(node.args)

    def _preprocess_pari(self, expr: str) -> str:
        """
        Évalue les pari(...) à parenthèses imbriquées en arithmétique exacte
        et les remplace par une référence à une variable temporaire (\\__pariN__)
        ajoutée au contexte. La grammaire Lark gère bien les pari à paren plate
        (via pari_call), mais retombe sur func_call générique dès qu'il y a
        des parens internes — d'où ce pré-traitement ciblé.
        """
        out = []
        i = 0
        n = len(expr)
        while i < n:
            if expr[i : i + 5] == "pari(":
                depth = 1
                j = i + 5
                while j < n and depth > 0:
                    ch = expr[j]
                    if ch == "(":
                        depth += 1
                    elif ch == ")":
                        depth -= 1
                    if depth > 0:
                        j += 1
                if depth != 0:
                    out.append(expr[i])
                    i += 1
                    continue
                inner = expr[i + 5 : j]
                if "(" in inner:
                    substituted = self._substitute_vars(inner)
                    result = _eval_exact_arithmetic(substituted)
                    if result is not None:
                        name = f"__pari{self._pari_counter}__"
                        self._pari_counter += 1
                        self.ctx[name] = str(result)
                        out.append(f"\\{name}")
                        i = j + 1
                        continue
                out.append(expr[i : j + 1])
                i = j + 1
            else:
                out.append(expr[i])
                i += 1
        return "".join(out)

    def _eval_wims(self, inner: str):
        """Evaluate the content of a wims(...) call."""
        inner = inner.strip()
        if inner.startswith("append item ") and " to " in inner:
            rest = inner[len("append item ") :]
            idx = rest.rfind(" to ")
            if idx >= 0:
                item = rest[:idx].strip()
                existing = rest[idx + 4 :].strip()
                parts = [x.strip() for x in existing.split(",") if x.strip()]
                parts.append(item)
                return parts
        if "values" in inner and "for" in inner:
            m = re.search(
                r"values\s+(.+)\s+for\s+(\w+)\s*=\s*(\d+)\s+to\s+(\d+)", inner
            )
            if m:
                expr_val, var, start, end = m.groups()
                return [
                    expr_val.replace(var, str(i))
                    for i in range(int(start), int(end) + 1)
                ]
        return [inner]

    def _preprocess_wims(self, expr: str) -> str:
        """
        Évalue les wims(...) à parenthèses imbriquées (ex : wims(append item \\(expr) to list))
        avant que Lark parse l'expression. RAW_CONTENT s'arrête au premier ')' ce qui tronque
        le contenu quand il contient \\(...) de mode mathématique.
        """
        out = []
        i = 0
        n = len(expr)
        while i < n:
            if expr[i : i + 5] == "wims(":
                depth = 1
                j = i + 5
                while j < n and depth > 0:
                    if expr[j] == "(":
                        depth += 1
                    elif expr[j] == ")":
                        depth -= 1
                    if depth > 0:
                        j += 1
                if depth != 0:
                    out.append(expr[i])
                    i += 1
                    continue
                inner_raw = expr[i + 5 : j]
                if "(" in inner_raw:
                    inner = self._substitute_vars(inner_raw)
                    result = self._eval_wims(inner)
                    name = f"__wims{self._wims_counter}__"
                    self._wims_counter += 1
                    self.ctx[name] = self._to_wims_string(result)
                    out.append(f"\\{name}")
                    i = j + 1
                    continue
                out.append(expr[i : j + 1])
                i = j + 1
            else:
                out.append(expr[i])
                i += 1
        return "".join(out)

    def _eval_expr(self, expr_str: str, kind: str = "text") -> Any:
        expr_str = self._preprocess_pari(expr_str)
        expr_str = self._preprocess_wims(expr_str)
        try:
            tree = self._expr_parser.parse(expr_str.strip())
            val = OEFExprEvaluator(self.ctx, self).transform(tree)
            if kind == "logic":
                return bool(val)
            return val
        except Exception as e:
            cause = getattr(e, "orig_exc", None)
            if isinstance(cause, AbortAssignment):
                raise cause
            # randitem(template1, template2, ...) used as a textual chooser
            # (args contain literal LaTeX/template content the math grammar
            # can't parse). Pick a random branch then substitute variables.
            picked = _pick_randitem_template(expr_str.strip())
            if picked is not None:
                return self._substitute_vars(picked).strip()
            return self._substitute_vars(expr_str).strip()

    def _to_wims_string(self, val: Any) -> str:
        if isinstance(val, list):
            return ",".join(self._to_wims_string(i) for i in val)
        if isinstance(val, bool):
            return "1" if val else "0"
        if isinstance(val, Fraction):
            if val.denominator == 1:
                return str(val.numerator)
            return f"{val.numerator}/{val.denominator}"
        if isinstance(val, float) and val.is_integer():
            return str(int(val))
        return str(val)

    def render_node(self, node: Any) -> str:
        if isinstance(node, str):
            return self._substitute_vars(node)
        if isinstance(node, list):
            return "".join(self.render_node(i) for i in node)
        if isinstance(node, OEFNode):
            if node.type == "variable":
                name = node.name or ""
                return str(self.ctx.get(name, f"\\{name}"))
            if node.type == "math":
                return f"\\({self.render_node(node.content)}\\)"
            if node.type == "braced_group":
                return f"{self.render_node(node.content)}"
            if node.type == "instruction":
                if node.name == "special" and len(node.args) >= 2:
                    stype = self._to_raw_string(node.args[0]).strip()
                    if stype.startswith("color="):
                        return f'<span style="color:{stype.split("=", 1)[1]}">{self.render_node(node.args[1])}</span>'
                if node.name == "embed" and len(node.args) >= 1:
                    raw_arg = self._to_raw_string(node.args[0]).strip()
                    parts = raw_arg.split(",", 1)
                    target = self._substitute_vars(parts[0].strip())
                    size = (
                        self._substitute_vars(parts[1].strip())
                        if len(parts) > 1
                        else ""
                    )
                    return f'<span class="oef-input" name="{target}" data-size="{size}"></span>'
                return f"\\{node.name}" + "".join(
                    f"{{{self.render_node(a)}}}" for a in node.args
                )
            if node.content:
                return self.render_node(node.content)
        return ""

    def _to_raw_string(self, obj) -> str:
        if isinstance(obj, str):
            return obj
        if isinstance(obj, list):
            return "".join(self._to_raw_string(i) for i in obj)
        if isinstance(obj, OEFNode):
            if obj.type == "variable":
                return f"\\{obj.name}"
            if obj.type == "math":
                return f"\\({self._to_raw_string(obj.content)}\\)"
            if obj.type == "braced_group":
                return f"{{{self._to_raw_string(obj.content)}}}"
            if obj.type == "instruction":
                return f"\\{obj.name}" + "".join(
                    f"{{{self._to_raw_string(a)}}}" for a in obj.args
                )
            if obj.content:
                return self._to_raw_string(obj.content)
        return str(obj)

    def _substitute_vars(self, text: str) -> str:
        def replace_indexed(m):
            name, idx_str = m.groups()
            val = self.ctx.get(name, "")
            try:
                idx = int(float(self._eval_expr(idx_str))) - 1
                parts = [x.strip() for x in str(val).split(",")]
                return parts[idx] if 0 <= idx < len(parts) else ""
            except Exception:
                return ""

        # Passe 1 : variables indexées \name[expr] — doit précéder la passe 2
        # pour éviter que \name soit substitué avant que [expr] soit évalué.
        text = re.sub(r"\\([a-zA-Z0-9_]+)\[([^\]]+)\]", replace_indexed, text)
        # Passe 2 : variables simples \name → valeur du contexte (ou \name inchangé).
        text = re.sub(
            r"\\([a-zA-Z0-9_]+)",
            lambda m: str(self.ctx.get(m.group(1), m.group(0))),
            text,
        )
        return text


class OEFExprEvaluator(Transformer):
    def __init__(self, ctx, evaluator):
        self.ctx = ctx
        self.evaluator = evaluator

    def list_val(self, items):
        # Un seul item : retourner la valeur directement (évite d'emballer en liste)
        return items[0] if len(items) == 1 else items

    @v_args(inline=True)
    def expression(self, item):
        return item

    @v_args(inline=True)
    def ternary(self, cond, true_val, false_val=None):
        if cond:
            return true_val
        if false_val is not None:
            return false_val
        raise AbortAssignment()

    def logic_or(self, items):
        return any(items)

    def logic_and(self, items):
        return all(items)

    def comparison(self, items):
        left = items[0]
        for i in range(1, len(items), 2):
            op, right = str(items[i]), items[i + 1]
            if op in ("==", "=", "==="):
                left = str(left) == str(right)
            elif op == "!=":
                left = str(left) != str(right)
            else:
                try:
                    lv, r = _to_numeric(left), _to_numeric(right)
                    if op == ">":
                        left = lv > r
                    elif op == "<":
                        left = lv < r
                    elif op == ">=":
                        left = lv >= r
                    elif op == "<=":
                        left = lv <= r
                except Exception:
                    left = False
        return left

    def math_expr(self, items):
        res = items[0]
        for i in range(1, len(items), 2):
            op, val = str(items[i]), items[i + 1]
            try:
                lf = _to_exact(res)
                rf = _to_exact(val)
                if lf is not None and rf is not None:
                    res = lf + rf if op == "+" else lf - rf
                else:
                    res = (
                        float(res) + float(val)
                        if op == "+"
                        else float(res) - float(val)
                    )
            except Exception:
                pass
        return res

    def product(self, items):
        res = items[0]
        for i in range(1, len(items), 2):
            op, val = str(items[i]), items[i + 1]
            try:
                lf = _to_exact(res)
                rf = _to_exact(val)
                if lf is not None and rf is not None:
                    if op == "*":
                        res = lf * rf
                    elif op == "/":
                        res = lf / rf
                    else:
                        res = float(lf) % float(rf)
                else:
                    if op == "*":
                        res = float(res) * float(val)
                    elif op == "/":
                        res = float(res) / float(val)
                    else:
                        res = float(res) % float(val)
            except Exception:
                pass
        return res

    def power(self, items):
        res = items[0]
        for i in range(1, len(items)):
            exp = items[i]
            try:
                base_f = _to_exact(res)
                exp_f = _to_exact(exp)
                if base_f is not None and exp_f is not None and exp_f.denominator == 1:
                    res = base_f**exp_f.numerator
                else:
                    res = float(res) ** float(exp)
            except Exception:
                pass
        return res

    def neg_atom(self, items):
        v = items[0]
        exact = _to_exact(v)
        if exact is not None:
            return -exact
        try:
            return -float(v)
        except (TypeError, ValueError):
            return f"-{v}"

    @v_args(inline=True)
    def number(self, t):
        s = str(t)
        if "." not in s and "e" not in s.lower():
            return int(s)
        f = float(s)
        if f == int(f) and abs(f) < 1e15:
            return int(f)
        return f

    @v_args(inline=True)
    def string(self, t):
        return str(t).strip("'\"")

    def variable(self, items):
        name = str(items[1].value)
        val = self.ctx.get(name, "0")
        if len(items) > 2:
            try:
                idx_expr = self.evaluator._to_raw_string(items[2])
                idx = int(float(self.evaluator._eval_expr(idx_expr))) - 1
                return [x.strip() for x in str(val).split(",")][idx]
            except Exception:
                return ""
        return val

    def func_call(self, items):
        name = str(items[0])
        args = items[1] if len(items) > 1 else []

        # random et randint ont leurs propres règles Lark (random_call / randint_call)
        # qui contournent le conflit SIGNED_NUMBER / ".." — ils n'arrivent ici que
        # s'ils sont appelés sans parenthèses, ce qui n'existe pas en pratique.
        if name == "randitem":
            lst = args if isinstance(args, list) else [args]
            return random.choice(lst)
        if name == "item":
            try:
                idx = int(float(args[0])) - 1
                lst = args[1:] if len(args) > 2 else str(args[1]).split(",")
                return lst[idx] if 0 <= idx < len(lst) else ""
            except Exception:
                return ""
        if name == "items":
            lst = args if isinstance(args, list) else str(args).split(",")
            return len([x for x in lst if str(x).strip()])
        if name in ("abs", "sqrt", "floor", "ceil"):
            try:
                arg = args[0] if isinstance(args, list) else args
                if name == "sqrt":
                    result = math.sqrt(_to_numeric(arg))
                    if result == int(result):
                        return int(result)  # carré parfait : entier exact
                    # Irrationnel : forme symbolique sqrt(n) plutôt que float.
                    # neg_atom("-sqrt(n)") retombe sur f"-{v}" proprement.
                    return f"sqrt({self.evaluator._to_wims_string(arg)})"
                if name in ("floor", "ceil"):
                    return int(getattr(math, name)(_to_numeric(arg)))
                # abs : garde l'exactitude
                exact = _to_exact(arg)
                if exact is not None:
                    return abs(exact)
                return float(math.fabs(float(arg)))
            except Exception:
                return 0
        if name == "row":
            try:
                idx = int(float(args[0])) - 1
                text = str(args[1]) if isinstance(args, list) and len(args) > 1 else ""
                lines = text.splitlines()
                return lines[idx].strip() if 0 <= idx < len(lines) else ""
            except Exception:
                return ""
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
        # Fonctions WIMS dont l'argument est déjà évalué par l'arithmétique exacte
        # avant d'arriver ici (simplify, expand, factor, …) : on retourne simplement
        # la représentation chaîne du résultat, ce qui est sémantiquement correct
        # pour des expressions numériques (ex : simplify(7-3) → "4").
        return self.evaluator._to_wims_string(args)

    @v_args(inline=True)
    def random_call(self, content):
        # RAW_CONTENT évite le conflit SIGNED_NUMBER / ".." du tokeniseur Lark.
        # Formes supportées : random(a..b) → entier aléatoire, random(x,y,z) → choix.
        inner = self.evaluator._substitute_vars(str(content.value)).strip()
        m = re.fullmatch(r"(-?\d+)\.\.(-?\d+)", inner)
        if m:
            return random.randint(int(m.group(1)), int(m.group(2)))
        items = [x.strip() for x in inner.split(",") if x.strip()]
        return random.choice(items) if items else ""

    @v_args(inline=True)
    def randint_call(self, content):
        # RAW_CONTENT évite le conflit SIGNED_NUMBER / ".." du tokeniseur Lark.
        # Formes supportées : randint(a..b) et randint(a, b).
        inner = self.evaluator._substitute_vars(str(content.value)).strip()
        m = re.fullmatch(r"(-?\d+)\.\.(-?\d+)", inner)
        if m:
            return random.randint(int(m.group(1)), int(m.group(2)))
        parts = [x.strip() for x in inner.split(",") if x.strip()]
        if len(parts) >= 2:
            try:
                return random.randint(int(float(parts[0])), int(float(parts[1])))
            except (ValueError, TypeError):
                pass
        return 0

    @v_args(inline=True)
    def texmath_call(self, content):
        # texmath(expr) est capturé via RAW_CONTENT pour éviter que le '='
        # d'une équation (ex : texmath(\x+\v[1]=\v[2])) ne soit interprété
        # par Lark comme opérateur de comparaison. On substitue les variables
        # puis on convertit les fractions entières en \frac{}{}.
        inner = self.evaluator._substitute_vars(str(content.value)).strip()
        return _expr_to_latex(inner)

    @v_args(inline=True)
    def wims_call(self, content):
        inner = self.evaluator._substitute_vars(str(content.value))
        return self.evaluator._eval_wims(inner)

    @v_args(inline=True)
    def pari_call(self, content):
        inner = self.evaluator._substitute_vars(str(content.value)).strip()
        if inner.startswith("core("):
            try:
                # Extrait le premier entier de "core(N)" pour calculer le radical.
                m = re.search(r"\d+", inner)
                return float(_pari_core(int(m.group() if m else "0")))
            except Exception:
                pass
        # PARI fait de l'arithmétique exacte : on garde les fractions sous la
        # forme 'a/b' réduite plutôt que de les convertir en flottants.
        exact = _eval_exact_arithmetic(inner)
        if exact is not None:
            return exact
        try:
            return self.evaluator._eval_expr(inner)
        except Exception:
            return inner

    def range(self, items):
        return f"{items[0]}..{items[1]}"

    def index_list(self, items):
        return items

    def arg_list(self, items):
        # expression_list produit déjà une liste — on évite le double-wrapping
        return items[0] if len(items) == 1 else items


def _oef_cond_to_py(c: str) -> str:
    c = str(c).strip().replace("^", "**").replace("<>", "!=")
    return (
        c.replace("=", "==")
        .replace("====", "==")
        .replace("<==", "<=")
        .replace(">===", ">=")
    )


def _split_top_level_commas(s: str) -> list[str]:
    """Découpe sur les virgules de profondeur 0, en respectant les parenthèses."""
    parts: list[str] = []
    depth = 0
    last = 0
    for i, ch in enumerate(s):
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "," and depth == 0:
            parts.append(s[last:i])
            last = i + 1
    parts.append(s[last:])
    return [p.strip() for p in parts]


# Reconnaît un rapport entier/entier (éventuellement signés) dans une expression.
# Utilisé par _expr_to_latex pour convertir a/b en \frac{a}{b}.
_INT_FRAC_RE = re.compile(r"(-?\d+)/(-?\d+)")

# Vérifie qu'une expression ne contient que des caractères arithmétiques purs
# (chiffres, espaces, + - * / ( ) .) — condition préalable à _eval_exact_arithmetic.
_ARITHMETIC_RE = re.compile(r"^[\d\s\+\-\*\/\(\)\.]+$")
# Reconnaît les nombres entiers et décimaux dans une expression arithmétique,
# pour les envelopper en Fraction("…") avant eval().
_NUMBER_RE = re.compile(r"(\d+(?:\.\d+)?)")

# Reconnaît une chaîne au format fraction réduite "-a/b" (ex : "2/3", "-11/6").
_FRACTION_STR_RE = re.compile(r"^-?\d+/-?\d+$")
# Reconnaît une chaîne entière signée (ex : "7", "-3").
_INTEGER_STR_RE = re.compile(r"^-?\d+$")


def _to_exact(v) -> "Fraction | None":
    """Tente de convertir v en Fraction exacte.
    Retourne None pour les décimaux et les chaînes non parsables.
    """
    if isinstance(v, Fraction):
        return v
    if isinstance(v, bool):
        return None
    if isinstance(v, int):
        return Fraction(v)
    s = str(v).strip()
    if _INTEGER_STR_RE.fullmatch(s):
        return Fraction(int(s))
    if _FRACTION_STR_RE.fullmatch(s):
        try:
            return Fraction(s)
        except (ValueError, ZeroDivisionError):
            return None
    try:
        f = float(s)
        if f == int(f) and abs(f) < 1e15:
            return Fraction(int(f))
    except (ValueError, TypeError):
        pass
    return None


def _to_numeric(v) -> float:
    """Convertit v en float, en gérant Fraction et chaînes 'a/b'."""
    exact = _to_exact(v)
    if exact is not None:
        return float(exact)
    return float(str(v))


def _eval_exact_arithmetic(expr: str) -> str | int | None:
    """
    Évalue une expression purement arithmétique en arithmétique exacte
    (Fraction). Retourne :
      - un int si le résultat est entier (ex. pari(8+1) → 9),
      - une chaîne 'a/b' réduite si fractionnaire (ex. pari(4*5/3) → '20/3'),
      - None si l'expression contient autre chose que des nombres et + - * / ( ).
    """
    expr = expr.strip()
    if not expr or not _ARITHMETIC_RE.match(expr):
        return None
    try:
        wrapped = _NUMBER_RE.sub(r'Fraction("\1")', expr)
        result = eval(wrapped, {"__builtins__": {}, "Fraction": Fraction})
    except Exception:
        return None
    if isinstance(result, Fraction):
        if result.denominator == 1:
            return result.numerator
        return f"{result.numerator}/{result.denominator}"
    if isinstance(result, int):
        return result
    return None


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
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0 and i != len(expr) - 1:
                return None
    inner = expr[len("randitem(") : -1]
    items = _split_top_level_commas(inner)
    items = [it for it in items if it]
    if not items:
        return None
    return random.choice(items)


def _pari_core(n: int) -> int:
    d = 2
    res = n
    while d * d <= res:
        if res % (d * d) == 0:
            res //= d * d
        else:
            d += 1
    return res


def _expr_to_latex(expr: str) -> str:
    """Convertit les fractions entières a/b en \\frac{a}{b} dans une expression OEF.

    Exemples :
      '10/3*z+-8/9'   → '\\frac{10}{3}z-\\frac{8}{9}'
      '7/-4*y+-10/9'  → '-\\frac{7}{4}y-\\frac{10}{9}'
      '-5/-6*u+-4/5'  → '\\frac{5}{6}u-\\frac{4}{5}'

    Règles appliquées dans l'ordre :
      1. a/b (entiers signés) → \\frac{|a|}{|b|} avec le signe devant le \\frac
      2. \\frac{}{} suivi de * puis d'une lettre → supprime le *
      3. Double signe (+-  -+  --) → signe simplifié
    """

    def replace_frac(m: re.Match) -> str:
        num, den = int(m.group(1)), int(m.group(2))
        # Signe toujours dans le numérateur : dénominateur toujours positif.
        if den < 0:
            num, den = -num, -den
        if num < 0:
            return rf"-\frac{{{-num}}}{{{den}}}"
        return rf"\frac{{{num}}}{{{den}}}"

    result = _INT_FRAC_RE.sub(replace_frac, expr)
    # Supprime le * de multiplication entre \frac{}{} et une variable (lettre).
    result = re.sub(r"(\\frac\{[^}]+\}\{[^}]+\})\*([a-zA-Z])", r"\1\2", result)
    # Simplifie les doubles signes issus de la normalisation des fractions.
    result = result.replace("+-", "-").replace("-+", "-").replace("--", "+")
    return result
