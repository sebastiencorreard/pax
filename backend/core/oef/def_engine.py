"""
Engine for compiled WIMS .def script files.

Evaluates the variable section, renders the :question section (or the literal
question= text), extracts answer metadata, and returns an ExerciseRender.
"""

from __future__ import annotations

import math
import random
import re
from typing import Any

from .def_parser import (
    Assign,
    DefFile,
    ForLoop,
    IfBlock,
    Insmath,
    Output,
    ReadEmbed,
    ReadProc,
    parse as parse_def,
)
from .engine import AnswerDef, ExerciseRender, _segment_statement


# ── WIMS arithmetic namespace ─────────────────────────────────────────────────


def _rint(x: Any) -> int:
    return int(round(float(x)))


_MATH_NS: dict = {
    "__builtins__": {},
    "rint": _rint,
    "round": round,
    "abs": abs,
    "max": max,
    "min": min,
    "sqrt": math.sqrt,
    "pow": pow,
    "sin": math.sin,
    "cos": math.cos,
    "tan": math.tan,
    "asin": math.asin,
    "acos": math.acos,
    "atan": math.atan,
    "atan2": math.atan2,
    "log": math.log,
    "log10": math.log10,
    "log2": math.log2,
    "exp": math.exp,
    "floor": math.floor,
    "ceil": math.ceil,
    "pi": math.pi,
    "e": math.e,
    "mod": lambda a, b: float(a) % float(b),
    "fact": math.factorial,
    "sign": lambda x: 1 if x > 0 else -1 if x < 0 else 0,
    "gcd": math.gcd,
}

# Patterns for variable substitution
_RANGE_SLICE_RE = re.compile(r"\$\((\w+)\[(\d+)\.\.(\d+)\]\)")  # $(var[n..m])
_INDEXED2_RE = re.compile(r"\$\((\w+)\[([^\]]+);([^\]]+)\]\)")  # $(var[n;m])
_INDEXED1_RE = re.compile(r"\$\((\w+)\[([^\]]+)\]\)")  # $(var[n])
_PAREN_VAR_RE = re.compile(r"\$\((\w+)\)")  # $(var)
_DOLLAR_VAR_RE = re.compile(r"\$([a-zA-Z_]\w*)")  # $varname


# ── Public entry point ────────────────────────────────────────────────────────


def load_and_render(def_path: str, seed: int | None = None) -> ExerciseRender:
    """Parse and evaluate a .def file, returning an ExerciseRender."""
    try:
        with open(def_path, encoding="utf-8") as f:
            text = f.read()
    except UnicodeDecodeError:
        with open(def_path, encoding="iso-8859-1") as f:
            text = f.read()

    if seed is None:
        seed = random.randint(0, 2**31)

    def_file = parse_def(text)
    engine = DefEngine(seed=seed)
    return engine.render(def_file)


# ── Engine ────────────────────────────────────────────────────────────────────


class DefEngine:
    def __init__(self, seed: int):
        self.seed = seed
        self.rng = random.Random(seed)
        self.ctx: dict[str, str] = {}

    # ── Top-level render ──────────────────────────────────────────────────────

    def render(self, df: DefFile) -> ExerciseRender:
        self._exec(df.var_instructions, output_buf=None)

        # Render statement HTML
        stmt = df.statement.strip()
        if "__EXECUTED__" in stmt or "__EXECUTED" in stmt:
            q_section = df.sections.get("question", [])
            html = self._render_section(q_section)
        else:
            html = self._subst(stmt)

        segments = _segment_statement(html)
        answers = self._extract_answers(df)

        # Same widget-filter logic as OEF engine
        widget_names = {s["name"] for s in segments if s["type"] in ("input", "slot")}
        if widget_names:
            answers = [
                a for a in answers if a.input_name.replace(" ", "") in widget_names
            ]

        hint = self._render_block_or_text(df.hint, df.sections.get("hint", []))
        solution = self._render_block_or_text(
            df.solution, df.sections.get("solution", [])
        )

        return ExerciseRender(
            title=self._subst(df.title),
            lang=df.meta.get("language", "fr"),
            statement_html=html,
            statement_segments=segments,
            answers=answers,
            hint_html=hint,
            solution_html=solution,
            seed=self.seed,
            meta={k: v for k, v in df.meta.items() if k not in ("language",)},
        )

    # ── Instruction execution ─────────────────────────────────────────────────

    def _exec(self, instructions: list, output_buf: list | None) -> None:
        """Execute a list of instructions sequentially."""
        for instr in instructions:
            if isinstance(instr, Assign):
                self.ctx[instr.name] = self._eval_value(instr.value)

            elif isinstance(instr, IfBlock):
                cond = self._eval_condition(instr.kind, instr.condition)
                body = instr.then_body if cond else instr.else_body
                self._exec(body, output_buf)

            elif isinstance(instr, ForLoop):
                self._exec_for(instr, output_buf)

            elif isinstance(instr, Output):
                if output_buf is not None:
                    output_buf.append(self._subst(instr.html))

            elif isinstance(instr, Insmath):
                if output_buf is not None:
                    expr = self._subst(instr.expr)
                    output_buf.append(f"\\({expr}\\)")

            elif isinstance(instr, ReadEmbed):
                if output_buf is not None:
                    output_buf.append(self._render_embed(instr.args))

            elif isinstance(instr, ReadProc):
                if output_buf is not None:
                    output_buf.append("")  # placeholder for unimplemented procs

    def _exec_for(self, loop: ForLoop, output_buf: list | None) -> None:
        range_s = self._subst(loop.range_expr)
        m = re.match(r"(.+?)\s+to\s+(.+)", range_s, re.I)
        if not m:
            return
        try:
            start = int(round(float(self._eval_arith(m.group(1).strip()))))
            end = int(round(float(self._eval_arith(m.group(2).strip()))))
        except (ValueError, TypeError):
            return
        for i in range(start, end + 1):
            self.ctx[loop.var] = str(i)
            self._exec(loop.body, output_buf)

    # ── Value evaluation ──────────────────────────────────────────────────────

    def _eval_value(self, value: str) -> str:
        """Evaluate the RHS of an assignment."""
        # !cmd — WIMS command
        if value.startswith("!"):
            cmd_line = value[1:].strip()
            cmd, _, args = cmd_line.partition(" ")
            return self._eval_cmd(cmd.lower(), args)

        # $[expr] — arithmetic
        if value.startswith("$["):
            return self._eval_dollar_bracket(value)

        # Literal string with variable substitution
        return self._subst(value)

    def _eval_dollar_bracket(self, s: str) -> str:
        """Evaluate $[expr] — find the outermost brackets and eval."""
        # May be embedded in a larger string, e.g. "prefix$[expr]suffix"
        result = []
        i = 0
        while i < len(s):
            if s[i] == "$" and i + 1 < len(s) and s[i + 1] == "[":
                end = _find_matching_bracket(s, i + 1, "[", "]")
                expr = s[i + 2 : end]
                result.append(self._eval_arith(expr))
                i = end + 1
            else:
                result.append(s[i])
                i += 1
        return "".join(result)

    def _eval_arith(self, expr: str) -> str:
        """Evaluate a WIMS arithmetic expression string."""
        # 1. Substitute all variable references
        expr = self._subst_for_arith(expr)
        # 2. Replace ^ with ** for Python
        expr = expr.replace("^", "**")
        # 3. Evaluate
        try:
            result = eval(expr, _MATH_NS)  # noqa: S307
            if isinstance(result, float) and result.is_integer():
                return str(int(result))
            if isinstance(result, float):
                # Format: avoid scientific notation for small numbers
                formatted = f"{result:.10g}"
                return formatted
            return str(result)
        except Exception:
            return expr  # return as-is on failure

    # ── Variable substitution ─────────────────────────────────────────────────

    def _subst(self, s: str) -> str:
        """Substitute all WIMS variable references in a string."""
        if not s or "$" not in s:
            return s
        # 1. $[expr] blocks first
        s = self._eval_dollar_bracket(s)
        # 2. $(var[n..m]) range slice
        s = _RANGE_SLICE_RE.sub(lambda m: self._resolve_range_slice(m), s)
        # 3. $(var[n;m]) matrix access
        s = _INDEXED2_RE.sub(lambda m: self._resolve_indexed2(m), s)
        # 4. $(var[n]) list access
        s = _INDEXED1_RE.sub(lambda m: self._resolve_indexed1(m), s)
        # 5. $(var) simple reference
        s = _PAREN_VAR_RE.sub(lambda m: self.ctx.get(m.group(1), ""), s)
        # 6. $var simple reference (skip $[ which was already handled)
        s = _DOLLAR_VAR_RE.sub(lambda m: self.ctx.get(m.group(1), m.group(0)), s)
        return s

    def _subst_for_arith(self, expr: str) -> str:
        """Substitute variable references inside an arithmetic expression."""
        if not expr or "$" not in expr:
            return expr
        expr = _RANGE_SLICE_RE.sub(lambda m: self._resolve_range_slice(m), expr)
        expr = _INDEXED2_RE.sub(lambda m: self._resolve_indexed2(m), expr)
        expr = _INDEXED1_RE.sub(lambda m: self._resolve_indexed1(m), expr)
        expr = _PAREN_VAR_RE.sub(lambda m: self.ctx.get(m.group(1), "0"), expr)
        expr = _DOLLAR_VAR_RE.sub(lambda m: self.ctx.get(m.group(1), "0"), expr)
        return expr

    def _resolve_range_slice(self, m: re.Match) -> str:
        """Resolve $(var[n..m]) — items n through m as a comma list."""
        name, start_s, end_s = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, "")
        if not value:
            return ""
        try:
            start, end = int(start_s), int(end_s)
        except ValueError:
            return ""
        items = value.split("\t") if "\t" in value else value.split(",")
        return ",".join(items[start - 1 : end])

    def _resolve_indexed1(self, m: re.Match) -> str:
        """Resolve $(var[n]) — 1-indexed item from tab-separated list."""
        name, idx_expr = m.group(1), m.group(2)
        value = self.ctx.get(name, "")
        if not value:
            return ""
        idx_s = self._subst_for_arith(idx_expr)
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
        except (ValueError, TypeError):
            return ""
        items = value.split("\t") if "\t" in value else value.split(",")
        if 1 <= idx <= len(items):
            return items[idx - 1].strip()
        return ""

    def _resolve_indexed2(self, m: re.Match) -> str:
        """Resolve $(var[n;m]) — row n, column m of a tab-row/semicolon-col matrix."""
        name, row_expr, col_expr = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, "")
        if not value:
            return ""
        row_s = self._subst_for_arith(row_expr)
        col_s = self._subst_for_arith(col_expr)
        try:
            row = int(round(float(self._eval_arith(row_s))))
            col = int(round(float(self._eval_arith(col_s))))
        except (ValueError, TypeError):
            return ""
        rows = value.split("\t")
        if not (1 <= row <= len(rows)):
            return ""
        cols = re.split(r"[;,]", rows[row - 1])
        if 1 <= col <= len(cols):
            return cols[col - 1].strip()
        return ""

    # ── Condition evaluation ──────────────────────────────────────────────────

    def _eval_condition(self, kind: str, condition: str) -> bool:
        """Evaluate an !if or !ifval condition."""
        cond = self._subst(condition)

        # Numeric comparison: !ifval $val10<4, $val8 issametext X,...
        if kind == "ifval" or re.search(r"[<>!=]=?", cond):
            try:
                # Handle WIMS comparison operators
                cond_py = cond
                cond_py = (
                    cond_py.replace("!=", "!__NE__")
                    .replace(">=", ">=")
                    .replace("<=", "<=")
                )
                cond_py = cond_py.replace("=", "==").replace("!__NE__", "!=")
                cond_py = cond_py.replace("^", "**")
                return bool(eval(cond_py, _MATH_NS))  # noqa: S307
            except Exception:
                pass

        # String equality: $val22=posi
        m = re.match(r"^\s*(.+?)\s*=\s*(.+?)\s*$", cond)
        if m:
            return m.group(1).strip() == m.group(2).strip()

        # Fallback: truthy
        return bool(cond)

    # ── WIMS command evaluation ───────────────────────────────────────────────

    def _eval_cmd(self, cmd: str, args: str) -> str:
        """Evaluate a WIMS !cmd and return the result as a string."""
        args = args.strip()

        if cmd == "randint":
            return self._cmd_randint(args)

        if cmd == "random":
            return self._cmd_random(args)

        if cmd == "randitem":
            return self._cmd_randitem(args)

        if cmd == "nonempty":
            return self._cmd_nonempty(args)

        if cmd == "shuffle":
            return self._cmd_shuffle(args)

        if cmd == "item":
            return self._cmd_item(args)

        if cmd == "row":
            return self._cmd_row(args)

        if cmd == "itemcnt":
            items = [x for x in re.split(r",|\t", self._subst(args)) if x.strip()]
            return str(len(items))

        if cmd == "rowcnt":
            val = self._subst(args)
            rows = [r for r in val.split("\t") if r.strip()]
            return str(len(rows))

        if cmd == "trim":
            return self._subst(args).strip()

        if cmd == "lower":
            return self._subst(args).lower()

        if cmd == "upper" or cmd == "uppercase":
            return self._subst(args).upper()

        if cmd == "replace":
            return self._cmd_replace(args)

        if cmd == "translate":
            return self._cmd_translate(args)

        if cmd == "append":
            return self._cmd_append(args)

        if cmd == "exec":
            return self._cmd_exec(args)

        if cmd == "rawmath":
            return _sympy_to_latex(self._subst(args))

        if cmd == "texmath":
            return _sympy_to_latex(self._subst(args))

        if cmd == "insmath":
            return self._subst(args)

        if cmd == "values":
            return self._cmd_values(args)

        if cmd == "makelist":
            return self._cmd_makelist(args)

        if cmd == "positionof":
            return self._cmd_positionof(args)

        if cmd in ("randrow", "randitem_row"):
            return self._cmd_randrow(args)

        if cmd == "sort":
            return self._cmd_sort(args)

        if cmd == "mathsubst":
            return self._cmd_mathsubst(args)

        if cmd == "listuniq":
            return self._cmd_listuniq(args)

        if cmd == "declosing":
            return self._cmd_declosing(args)

        if cmd == "nospace":
            return re.sub(r"\s+", "", self._subst(args))

        if cmd in ("getopt", "getdef"):
            return self._cmd_getopt(args)

        if cmd == "embraced":
            return self._cmd_embraced(args)

        if cmd == "word":
            return self._cmd_word(args)

        if cmd == "column":
            return self._cmd_column(args)

        if cmd == "charcnt":
            return str(len(self._subst(args).strip()))

        if cmd in ("nosubst",):
            return args  # literal, no substitution

        # Unknown command — return empty
        return ""

    # ── Specific command implementations ─────────────────────────────────────

    def _cmd_randint(self, args: str) -> str:
        """!randint a, b — random integer in [a, b]."""
        parts = [self._eval_arith(p.strip()) for p in args.split(",")]
        try:
            a, b = int(parts[0]), int(parts[1])
            return str(self.rng.randint(a, b))
        except (IndexError, ValueError):
            return "0"

    def _cmd_random(self, args: str) -> str:
        """!random a, b — random real in [a, b]."""
        parts = [self._eval_arith(p.strip()) for p in args.split(",")]
        try:
            a, b = float(parts[0]), float(parts[1])
            val = self.rng.uniform(a, b)
            return f"{val:.10g}"
        except (IndexError, ValueError):
            return "0"

    def _cmd_nonempty(self, args: str) -> str:
        """!nonempty items list — filter blank items, return filtered list."""
        # Syntax: "items item1,item2,..." or "rows matrix"
        rest = self._subst(args)
        m = re.match(r"^(items|rows)\s+(.*)", rest, re.DOTALL)
        if m:
            mode, data = m.group(1), m.group(2)
            sep = "\t" if mode == "rows" else ","
            items = [x for x in data.split(sep) if x.strip()]
            return sep.join(items)
        return rest

    def _cmd_randitem(self, args: str) -> str:
        """!randitem list — random item from a tab/comma-separated list."""
        val = self._subst(args.strip())
        if "\t" in val:
            items = [x.strip() for x in val.split("\t") if x.strip()]
        else:
            items = [x.strip() for x in val.split(",") if x.strip()]
        if not items:
            return ""
        return self.rng.choice(items)

    def _cmd_shuffle(self, args: str) -> str:
        """!shuffle list — shuffle a comma-separated list."""
        val = self._subst(args)
        if "\t" in val:
            sep = "\t"
            items = val.split("\t")
        else:
            sep = ","
            items = val.split(",")
        items = [x for x in items if x.strip()]
        self.rng.shuffle(items)
        return sep.join(items)

    def _cmd_item(self, args: str) -> str:
        """!item n of list — 1-indexed item."""
        m = re.match(r"(.+?)\s+of\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())

        # Range: "2 to 5" → items 2 through 5
        range_m = re.match(r"(\d+)\s+to\s+(\d+)", idx_s)
        if range_m:
            a, b = int(range_m.group(1)), int(range_m.group(2))
            if "\t" in data:
                items = data.split("\t")
            else:
                items = data.split(",")
            return ",".join(items[a - 1 : b])

        try:
            idx = int(round(float(self._eval_arith(idx_s))))
        except (ValueError, TypeError):
            return ""
        if "\t" in data:
            items = data.split("\t")
        else:
            items = re.split(r",(?![^(]*\))", data)  # comma not inside parens
        if 1 <= idx <= len(items):
            return items[idx - 1].strip()
        return ""

    def _cmd_row(self, args: str) -> str:
        """!row n of matrix — 1-indexed tab-separated row."""
        m = re.match(r"(.+?)\s+of\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
        except (ValueError, TypeError):
            return ""
        rows = data.split("\t")
        if 1 <= idx <= len(rows):
            return rows[idx - 1].strip()
        return ""

    def _cmd_replace(self, args: str) -> str:
        """!replace internal X by Y in S — string replacement."""
        # Syntax: "internal <old> by <new> in <var>"
        m = re.match(
            r"internal\s+(.*?)\s+by\s+(.*?)\s+in\s+(.*)", args, re.DOTALL | re.I
        )
        if not m:
            return self._subst(args)
        old = m.group(1).strip()
        new = m.group(2).strip()
        src = self._subst(m.group(3).strip())
        # Handle escape sequences in old/new (e.g. \( → literal backslash paren)
        old = old.replace("\\(", "\\(")
        return src.replace(old, new)

    def _cmd_translate(self, args: str) -> str:
        """!translate [internal] chars_from to chars_to in S — tr-style char translation."""
        m_int = re.match(
            r"internal\s+(.*?)\s+to\s+(.*?)\s+in\s+(.*)", args, re.DOTALL | re.I
        )
        m_plain = (
            re.match(r"(.*?)\s+to\s+(.*?)\s+in\s+(.*)", args, re.DOTALL | re.I)
            if not m_int
            else None
        )
        m = m_int or m_plain
        if not m:
            return self._subst(args)

        chars_from = m.group(1).strip()
        chars_to_raw = m.group(2).strip()
        src = self._subst(m.group(3).strip())

        # Resolve tab shorthands
        chars_from = chars_from.replace("$\t$", "\t").replace("$\\t$", "\t")
        chars_to = chars_to_raw.replace(";;", "\t")

        # Build tr-style character translation table
        trans: dict[int, str | None] = {}
        for i, c in enumerate(chars_from):
            trans[ord(c)] = chars_to[i] if i < len(chars_to) else None

        return src.translate(trans)

    def _cmd_append(self, args: str) -> str:
        """!append item X to list — append item to tab-separated list."""
        m = re.match(r"item\s+(.*?)\s+to\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return self._subst(args)
        item = self._subst(m.group(1).strip())
        lst = self._subst(m.group(2).strip())
        if lst:
            return lst + "\t" + item
        return item

    def _eval_loop_expr(self, expr: str) -> str:
        """Evaluate a loop body expression supporting bare variable names from ctx.

        Handles $var references via _subst, and bare identifiers (e.g. 'v', 'v*v')
        by injecting the current ctx into the eval namespace.
        """
        ev = self._subst(expr)
        if ev != expr or expr.startswith("$"):
            return ev
        ns = dict(_MATH_NS)
        for k, v in self.ctx.items():
            s = v.strip()
            try:
                ns[k] = int(s) if s.lstrip("-").isdigit() else float(s)
            except (ValueError, AttributeError):
                ns[k] = s
        try:
            res = eval(expr.replace("^", "**"), ns)  # noqa: S307
            if isinstance(res, float) and res.is_integer():
                return str(int(res))
            return str(res)
        except Exception:
            return ev

    def _cmd_values(self, args: str) -> str:
        """!values expr for var=start to end — comma-separated list."""
        m = re.match(
            r"(.*?)\s+for\s+(\w+)\s*=\s*(.+?)\s+to\s+(.+)", args, re.I | re.DOTALL
        )
        if not m:
            return ""
        expr, var, start_s, end_s = (
            m.group(1).strip(),
            m.group(2),
            m.group(3).strip(),
            m.group(4).strip(),
        )
        try:
            start = int(round(float(self._eval_arith(self._subst(start_s)))))
            end = int(round(float(self._eval_arith(self._subst(end_s)))))
        except (ValueError, TypeError):
            return ""
        saved = self.ctx.get(var)
        results = []
        for i in range(start, end + 1):
            self.ctx[var] = str(i)
            results.append(self._eval_loop_expr(expr))
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)
        return ",".join(results)

    def _cmd_exec(self, args: str) -> str:
        """!exec maxima expr / !exec pari expr — call external CAS."""
        m = re.match(r"(maxima|pari)\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        engine = m.group(1).lower()
        expr = self._subst(m.group(2).strip())
        if engine == "maxima":
            return _call_maxima(expr)
        if engine == "pari":
            return _call_pari(expr)
        return ""

    def _cmd_makelist(self, args: str) -> str:
        """!makelist expr for var=start to end — tab-separated list (matrix rows)."""
        m = re.match(
            r"(.*?)\s+for\s+(\w+)\s*=\s*(.+?)\s+to\s+(.+)", args, re.I | re.DOTALL
        )
        if not m:
            return ""
        expr, var, start_s, end_s = (
            m.group(1).strip(),
            m.group(2),
            m.group(3).strip(),
            m.group(4).strip(),
        )
        try:
            start = int(round(float(self._eval_arith(self._subst(start_s)))))
            end = int(round(float(self._eval_arith(self._subst(end_s)))))
        except (ValueError, TypeError):
            return ""
        saved = self.ctx.get(var)
        results = []
        for i in range(start, end + 1):
            self.ctx[var] = str(i)
            # Expression may contain commas (multi-column row): eval each part
            parts = [self._eval_loop_expr(p.strip()) for p in expr.split(",")]
            results.append(",".join(parts))
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)
        return "\t".join(results)

    def _cmd_positionof(self, args: str) -> str:
        """!positionof item X in $list — 1-indexed position, 0 if absent."""
        m = re.match(r"item\s+(.*?)\s+in\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return "0"
        needle = self._subst(m.group(1).strip())
        haystack = self._subst(m.group(2).strip())
        items = haystack.split("\t") if "\t" in haystack else haystack.split(",")
        for i, item in enumerate(items, 1):
            if item.strip() == needle:
                return str(i)
        return "0"

    def _cmd_randrow(self, args: str) -> str:
        """!randrow $matrix — pick a random tab-separated row."""
        val = self._subst(args.strip())
        rows = [r for r in val.split("\t") if r.strip()]
        if not rows:
            return ""
        return self.rng.choice(rows)

    def _cmd_sort(self, args: str) -> str:
        """!sort numeric items/list $val — sort items numerically."""
        m = re.match(r"numeric\s+(?:items?|list|rows?)\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        data = self._subst(m.group(1).strip())
        if "\t" in data:
            sep, items = "\t", data.split("\t")
        else:
            sep, items = ",", data.split(",")
        items = [x for x in items if x.strip()]
        try:
            items.sort(key=lambda x: _parse_numeric(x.strip()))
        except (ValueError, ZeroDivisionError):
            items.sort()
        return sep.join(items)

    def _cmd_mathsubst(self, args: str) -> str:
        """!mathsubst var=(value) in $expr — substitute var with (value) in expression."""
        m = re.match(r"(\w+)\s*=\s*(.+?)\s+in\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return self._subst(args)
        var = m.group(1)
        val = self._subst(m.group(2).strip())
        expr = self._subst(m.group(3).strip())
        # Wrap val in parens if not already (preserves precedence in the result)
        if not (val.startswith("(") and val.endswith(")")):
            val = f"({val})"
        return re.sub(r"\b" + re.escape(var) + r"\b", val, expr)

    def _cmd_listuniq(self, args: str) -> str:
        """!listuniq $list — remove duplicates, preserve order."""
        val = self._subst(args.strip())
        if "\t" in val:
            sep, items = "\t", val.split("\t")
        else:
            sep, items = ",", val.split(",")
        seen: set[str] = set()
        result = []
        for item in items:
            key = item.strip()
            if key and key not in seen:
                seen.add(key)
                result.append(item)
        return sep.join(result)

    def _cmd_declosing(self, args: str) -> str:
        """!declosing $val — remove outermost matching brackets/parens/braces."""
        val = self._subst(args.strip()).strip()
        pairs = {"(": ")", "[": "]", "{": "}"}
        if val and val[0] in pairs and val[-1] == pairs[val[0]]:
            return val[1:-1]
        return val

    def _cmd_getopt(self, args: str) -> str:
        """!getopt key in $var — extract value for 'key=value' from options string."""
        m = re.match(r"(\S+)\s+in\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        key = re.escape(m.group(1).strip())
        val = self._subst(m.group(2).strip())
        found = re.search(r"\b" + key + r"\s*=\s*(\S+)", val)
        return found.group(1) if found else ""

    def _cmd_embraced(self, args: str) -> str:
        """!embraced randitem $list — pick a random item, wrap in parens if needed."""
        m = re.match(r"randitem\s+(.*)", args, re.DOTALL | re.I)
        if m:
            item = self._cmd_randitem(m.group(1).strip())
        else:
            item = self._subst(args)
        # Wrap in parens if the item could cause sign/precedence issues embedded in math
        needs_parens = bool(re.search(r"[+\-*/]", item.lstrip("-")))
        return f"({item})" if needs_parens else item

    def _cmd_word(self, args: str) -> str:
        """!word n of $str — nth space-separated word (1-indexed)."""
        m = re.match(r"(.+?)\s+of\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        text = self._subst(m.group(2).strip())
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
        except (ValueError, TypeError):
            return ""
        words = text.split()
        return words[idx - 1] if 1 <= idx <= len(words) else ""

    def _cmd_column(self, args: str) -> str:
        """!column n of $matrix — extract column n from each tab-separated row."""
        m = re.match(r"(.+?)\s+of\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        # Handle "n to m" range (return items in those columns across all rows)
        range_m = re.match(r"(\d+)\s+to\s+\S+", idx_s)
        col_idx = int(range_m.group(1)) if range_m else None
        if col_idx is None:
            try:
                col_idx = int(round(float(self._eval_arith(idx_s))))
            except (ValueError, TypeError):
                return ""
        rows = data.split("\t")
        result = []
        for row in rows:
            cols = re.split(r"[;,]", row)
            if 1 <= col_idx <= len(cols):
                result.append(cols[col_idx - 1].strip())
        return ",".join(result)

    # ── Section rendering ─────────────────────────────────────────────────────

    def _render_section(self, instructions: list) -> str:
        """Render an executed section (:question etc.) to HTML."""
        buf: list[str] = []
        self._exec(instructions, output_buf=buf)
        return "".join(buf)

    def _render_block_or_text(self, literal: str, section_instrs: list) -> str:
        """Render hint/solution: use section if it has content, else literal."""
        if section_instrs:
            rendered = self._render_section(section_instrs)
            if rendered.strip():
                return rendered
        if literal and literal.strip():
            return self._subst(literal)
        return ""

    def _render_embed(self, args: str) -> str:
        """Render an !read oef/embed.phtml marker as an input span."""
        args = self._subst(args).strip()
        # Parse: "r1,10" or "reply1,$val10" or "r1" etc.
        parts = [p.strip() for p in args.split(",")]
        ref = parts[0] if parts else "reply1"
        size_str = parts[1] if len(parts) > 1 else "10"

        # Normalise reply ref: r1 → reply1, r\1 → reply1 (loop var refs)
        if ref.startswith("r") and not ref.startswith("reply"):
            suffix = ref[1:]
            # Evaluate suffix (may be an expression like \[3*\k-2])
            suffix = re.sub(
                r"\\?\[(.+?)\]",
                lambda m: self._eval_arith(self._subst(m.group(1).replace("\\", "$"))),
                suffix,
            )
            suffix = re.sub(
                r"\\(\w+)", lambda m: self.ctx.get(m.group(1), m.group(1)), suffix
            )
            try:
                ref = f"reply{int(suffix)}"
            except ValueError:
                ref = f"reply{suffix}"

        try:
            size = int(self._subst(size_str))
        except ValueError:
            size = 10

        return f'<span class="oef-input" name="{ref}" data-size="{size}"></span>'

    # ── Answer extraction ─────────────────────────────────────────────────────

    def _extract_answers(self, df: DefFile) -> list[AnswerDef]:
        answers: list[AnswerDef] = []

        for rm in df.reply_meta:
            n = rm["n"]
            ans_type = self._subst(rm.get("type", "numeric"))
            label = self._subst(rm.get("name", ""))
            expected = self._subst(rm.get("good", ""))
            weight = float(self._subst(rm.get("weight", "1")) or "1")
            option = self._subst(rm.get("option", ""))
            options = {"option": option} if option else {}
            answers.append(
                AnswerDef(
                    label=label,
                    expected=expected,
                    answer_type=ans_type,
                    options=options,
                    weight=weight,
                    input_name=f"reply{n}",
                    logical_name=label or f"reply{n}",
                )
            )

        for cm in df.choice_meta:
            n = cm["n"]
            label = self._subst(cm.get("name", ""))
            correct = self._subst(cm.get("good", ""))
            bad_raw = self._subst(cm.get("bad", ""))
            wrong_items = [w.strip() for w in bad_raw.split(",") if w.strip()]
            all_items = [correct] + wrong_items

            import random as _random

            _random.Random(f"{self.seed}_{n}").shuffle(all_items)

            option = cm.get("option", "")
            if "noidontknow" not in option:
                _dont_know = {
                    "fr": "Je ne sais pas",
                    "nl": "Ik weet het niet",
                    "en": "I don't know",
                }
                lang = df.meta.get("language", "fr")[:2].lower()
                all_items.append(_dont_know.get(lang, "Je ne sais pas"))

            answers.append(
                AnswerDef(
                    label=label,
                    expected=correct,
                    answer_type="radio",
                    options={"choices": all_items},
                    input_name=f"reply{n}",
                    logical_name=label or f"reply{n}",
                )
            )

        return answers


# ── CAS helpers ───────────────────────────────────────────────────────────────


_MAXIMA_TO_SYMPY: dict[str, str] = {
    "expand": "expand",
    "factor": "factor",
    "fullratsimp": "simplify",
    "ratsimp": "simplify",
    "simplify": "simplify",
    "cancel": "cancel",
    "radsimp": "radsimp",
}


def _call_maxima(expr: str) -> str:
    """Evaluate a Maxima CAS expression using SymPy as a drop-in replacement."""
    import sympy  # noqa: PLC0415

    clean = expr.strip().rstrip(";").strip()

    # Match a single function call: funcname(args…)
    m = re.match(r"^(\w+)\s*\((.+)\)$", clean, re.DOTALL)
    if m:
        func_name = m.group(1).lower()
        arg_str = m.group(2).strip()

        if func_name == "printtex":
            try:
                return sympy.latex(sympy.sympify(arg_str.replace("^", "**")))
            except Exception:
                return clean

        sympy_func_name = _MAXIMA_TO_SYMPY.get(func_name)
        if sympy_func_name:
            try:
                sympy_func = getattr(sympy, sympy_func_name)
                result = sympy_func(sympy.sympify(arg_str.replace("^", "**")))
                return str(result)
            except Exception:
                return clean

    # Fallback: plain arithmetic / variable expression
    try:
        result = sympy.simplify(sympy.sympify(clean.replace("^", "**")))
        if result.is_number and result.is_integer:
            return str(int(result))
        return str(result)
    except Exception:
        return expr


def _sympy_to_latex(expr: str) -> str:
    """Convert a SymPy output string to LaTeX notation for display."""
    import sympy  # noqa: PLC0415

    try:
        return sympy.latex(sympy.sympify(expr.replace("^", "**")))
    except Exception:
        return expr


def _call_pari(expr: str) -> str:
    """Evaluate a PARI/GP-style arithmetic expression via Python."""
    clean = expr.strip().rstrip(";")
    # PARI print(expr) outputs and returns the value — unwrap it
    m = re.match(r"^print\s*\((.+)\)$", clean, re.DOTALL)
    if m:
        clean = m.group(1).strip()
    clean = clean.replace("^", "**")
    try:
        result = eval(clean, _MATH_NS)  # noqa: S307
        if isinstance(result, float) and result.is_integer():
            return str(int(result))
        if isinstance(result, float):
            return f"{result:.10g}"
        return str(result)
    except Exception:
        return expr


# ── Numeric helpers ───────────────────────────────────────────────────────────


def _parse_numeric(s: str) -> float:
    """Parse a numeric string that may be a fraction like '3/2' or '-7/4'."""
    s = s.strip()
    if "/" in s:
        parts = s.split("/", 1)
        return float(parts[0]) / float(parts[1])
    return float(s)


# ── Utility ───────────────────────────────────────────────────────────────────


def _find_matching_bracket(s: str, start: int, open_c: str, close_c: str) -> int:
    """Find the index of the closing bracket matching s[start] = open_c."""
    depth = 0
    for i in range(start, len(s)):
        if s[i] == open_c:
            depth += 1
        elif s[i] == close_c:
            depth -= 1
            if depth == 0:
                return i
    return len(s) - 1
