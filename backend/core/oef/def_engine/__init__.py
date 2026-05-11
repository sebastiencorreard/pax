"""
Engine for compiled WIMS .def script files.

Evaluates the variable section, renders the :question section (or the literal
question= text), extracts answer metadata, and returns an ExerciseRender.
"""

from __future__ import annotations

import random
import re

from .cas import (
    _MATH_NS,
    _PARI_HELPERS,
    _PYTHON_KEYWORDS,
    _call_maxima,
    _call_pari,
    _format_pari_result,
    _MAXIMA_TO_SYMPY,
    _rint,
    _split_top_level_args,
    _sympify_arg,
    _sympy_to_latex,
)
from .presentation import _close_inline_math, _normalize_math_content
from .slib import _SlibExit, _SlibMixin
from ..def_parser import (
    Assign,
    DefFile,
    ForLoop,
    IfBlock,
    Insmath,
    Output,
    ReadDraw,
    ReadEmbed,
    ReadProc,
    parse as parse_def,
)
from ..engine import AnswerDef, ExerciseRender, _segment_statement


# Patterns for variable substitution
_RANGE_SLICE_RE = re.compile(r"\$\((\w+)\[(\d+)\.\.(\d+)\]\)")  # $(var[n..m])
_INDEXED2_RE = re.compile(r"\$\((\w+)\[([^\]]*?);([^\]]*)\]\)")  # $(var[n;m])
_INDEXED1_RE = re.compile(r"\$\((\w+)\[([^\]]+)\]\)")  # $(var[n])
_PAREN_VAR_RE = re.compile(r"\$\((\w+)\)")  # $(var)
_DOLLAR_VAR_RE = re.compile(r"\$([a-zA-Z_][a-zA-Z0-9_]*)")  # $varname


# ── Public entry point ────────────────────────────────────────────────────────


def load_and_render(def_path: str, seed: int | None = None, m_step: int | None = None) -> ExerciseRender:
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
    engine = DefEngine(seed=seed, def_path=def_path)
    if m_step is not None:
        engine.ctx["m_step"] = str(m_step)
        engine.ctx["step"] = str(m_step)  # WIMS alias
    return engine.render(def_file)


# ── Engine ────────────────────────────────────────────────────────────────────


class DefEngine(_SlibMixin):
    def __init__(self, seed: int, def_path: str | None = None):
        self.seed = seed
        self.rng = random.Random(seed)
        # WIMS treats ``$empty`` as the predefined empty-string sentinel;
        # exposing it as a regular ctx entry keeps `_subst` happy.
        # Always initialize m_step to "1" so it's defined when var_instructions execute.
        # Also set step as an alias for m_step (WIMS uses both \step and \m_step).
        self.ctx: dict[str, str] = {
            "empty": "", 
            "m_step": "1", 
            "step": "1",
            "m_times": "×",
            "m_div": "÷",
            "m_le": "≤",
            "m_ge": "≥",
            "m_neq": "≠",
        }
        # Path of the .def file being rendered. Used to resolve `!readproc
        # slib/<name>` paths relative to the module directory.
        self.def_path = def_path

    # ── Top-level render ──────────────────────────────────────────────────────

    def render(self, df: DefFile) -> ExerciseRender:
        # m_step is now always initialized to "1" in __init__, and can be
        # overridden by load_and_render before calling render(). This ensures
        # m_step is defined when var_instructions execute, so conditions like
        # !if $m_step=2 work correctly.

        # Reply metadata (`replytype1=…`, `replyname1=…`, …) lives in
        # df.reply_meta, not in var_instructions. Seed it into ctx so the
        # statement rendering (specifically `_render_embed`) can see e.g.
        # `replytype1` to decide whether to emit a text input.
        for rm in df.reply_meta:
            n = rm.get("n")
            if n is None:
                continue
            for key in ("type", "name", "good", "option", "weight"):
                if key in rm:
                    self.ctx[f"reply{key}{n}"] = rm[key]

        self._exec(df.var_instructions, output_buf=None)

        # Render statement HTML
        stmt = df.statement.strip()
        if "__EXECUTED__" in stmt or "__EXECUTED" in stmt:
            q_section = df.sections.get("question", [])
            html = self._render_section(q_section)
        else:
            html = self._subst(stmt)

        from ..flydraw import inline_svg_imgs  # noqa: PLC0415

        html = _close_inline_math(html)
        html = inline_svg_imgs(html)
        # Drop empty `<li>` / `<ul>` shells left behind when radio embeds
        # are stripped (the frontend renders the radio buttons separately
        # from `options.choices`).
        html = re.sub(r"<li[^>]*>\s*</li>", "", html)
        html = re.sub(r"<ul[^>]*>\s*</ul>", "", html)
        answers = self._extract_answers(df)

        # If the question text has no input/slot widget but the exercise
        # declares replies, append a default input for each so the frontend
        # has somewhere to type the answer (matches WIMS' fallback behaviour).
        # Skip this for dynamic steps exercises (they control visibility per step).
        segments = _segment_statement(html)
        widget_names = {s["name"] for s in segments if s["type"] in ("input", "slot", "menu")}
        
        # Extract dynamic steps info
        oefsteps_val = self.ctx.get("oefsteps", "").strip()
        is_dynsteps_var = self.ctx.get("dynsteps", "").strip().lower() == "yes"
        
        if is_dynsteps_var:
            exercise_type = "dynsteps"
        elif oefsteps_val:
            exercise_type = "course"
        else:
            exercise_type = "standard"

        type_meta = {}
        if exercise_type != "standard":
            try:
                type_meta["current_step"] = int(self.ctx.get("m_step", "1"))
            except (ValueError, TypeError):
                type_meta["current_step"] = 1
            
            # Try to extract total steps from common variable names.
            # 1. Look at oefsteps first
            if oefsteps_val:
                # oefsteps may be tab-, semicolon-, or newline-separated (e.g. "r1\tr2\tr3\tr4")
                steps = re.split(r"[;\n\r\t]+", oefsteps_val)
                steps = [s.strip() for s in steps if s.strip()]
                if steps:
                    type_meta["total_steps"] = len(steps)
            
            # 2. Fall back to other common variables if total_steps still missing
            if "total_steps" not in type_meta:
                for var_name in ("val62", "val71", "cnt", "val61", "val70"):
                    val = self.ctx.get(var_name, "")
                    try:
                        type_meta["total_steps"] = int(val)
                        break
                    except (ValueError, TypeError):
                        # Try counting tab-separated items in the list
                        if "\t" in val:
                            type_meta["total_steps"] = len(val.split("\t"))
                            break
                        continue

        is_dynsteps_flag = exercise_type != "standard"
        text_replies = [
            a for a in answers if a.answer_type.lower() not in ("radio", "menu")
        ]
        if text_replies and not widget_names and not is_dynsteps_flag:
            for a in text_replies:
                html += (
                    f'<br><span class="oef-input" name="{a.input_name}" '
                    f'data-size="10"></span>'
                )
            segments = _segment_statement(html)
            widget_names = {
                s["name"] for s in segments if s["type"] in ("input", "slot", "menu")
            }

        raw_css = self.ctx.get("oefcss") or self.ctx.get("css", "")
        css = None
        if raw_css:
            css = re.sub(r"</?style[^>]*>", "", raw_css, flags=re.IGNORECASE).strip()

        check_sections = None
        if "postdef" in df.sections or "test" in df.sections or "feedback" in df.sections:
            check_sections = {
                "postdef": df.sections.get("postdef", []),
                "test": df.sections.get("test", []),
                "feedback": df.sections.get("feedback", []),
                "ctx": dict(self.ctx),
            }

        return ExerciseRender(
            title=self._subst(df.title),
            lang=df.meta.get("language", "fr"),
            statement_html=html,
            statement_segments=segments,
            answers=answers,
            hint_html=self._render_block_or_text(df.meta.get("hint", ""), df.sections.get("hint", [])),
            solution_html=self._render_block_or_text(df.meta.get("solution", ""), df.sections.get("solution", [])),
            seed=self.seed,
            meta={k: v for k, v in df.meta.items() if k not in ("language",)},
            ev_ctx=dict(self.ctx),
            check_sections=check_sections,
            exercise_type=exercise_type,
            is_dynsteps=is_dynsteps_flag,
            current_step=type_meta.get("current_step"),
            total_steps=type_meta.get("total_steps"),
            type_meta=type_meta,
            css=css,
        )

    # ── Instruction execution ─────────────────────────────────────────────────

    def _exec(self, instructions: list, output_buf: list[str] | None) -> None:
        """Execute a list of instructions sequentially."""
        for instr in instructions:
            if isinstance(instr, Assign):
                val = self._eval_value(instr.value)
                self.ctx[instr.name] = val

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
                # Run for its side effects (sets ctx['ins_url'], etc.) — the
                # call's textual output is empty for our supported procs.
                self._cmd_readproc(f"{instr.path} {instr.args}".strip())
                if output_buf is not None:
                    output_buf.append("")

            elif isinstance(instr, ReadDraw):
                # !read oef/draw.phtml ARGS — render a graph and inline it
                # right where the directive sits in the question section.
                self._cmd_readproc(f"oef/draw.phtml {instr.args}")
                url = self.ctx.get("ins_url", "")
                if output_buf is not None and url:
                    output_buf.append(f'<img src="{url}" alt="">')

    def _exec_for(self, loop: ForLoop, output_buf: list[str] | None) -> None:
        """Execute a !for loop."""
        range_s = self._subst(loop.range_expr)
        m = re.match(r"(.*?)\s+to\s+(.*)", range_s, re.I)
        if not m:
            return
        try:
            start = int(round(float(self._eval_arith(m.group(1).strip()))))
            end = int(round(float(self._eval_arith(m.group(2).strip()))))
        except (ValueError, TypeError):
            return

        var = loop.var.lstrip("$")
        saved = self.ctx.get(var)
        for i in range(start, end + 1):
            self.ctx[var] = str(i)
            self._exec(loop.body, output_buf)
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)

    def _eval_value(self, value: str) -> str:
        """Evaluate the RHS of an assignment."""
        # !cmd — WIMS command
        if value.startswith("!"):
            cmd_line = value[1:].strip()
            cmd, _, args = cmd_line.partition(" ")
            cmd = cmd.lower()
            if cmd == "nosubst":
                return args
            
            # For other commands, substitute variables first
            args = self._subst(args)
            return self._eval_cmd(cmd, args)

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
        ns = dict(_MATH_NS)
        # Also inject current context for bare variable names
        for k, v in self.ctx.items():
            s = v.strip()
            try:
                ns[k] = int(s) if s.lstrip("-").isdigit() else float(s)
            except (ValueError, AttributeError):
                ns[k] = s
        try:
            res = eval(expr, ns)  # noqa: S307
            if isinstance(res, float) and res.is_integer():
                return str(int(res))
            return str(res)
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
        s = _PAREN_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "")), s)
        # 6. $var simple reference (skip $[ which was already handled)
        s = _DOLLAR_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "")), s)
        return s

    def _subst_for_arith(self, expr: str) -> str:
        """Substitute variable references inside an arithmetic expression."""
        if not expr or "$" not in expr:
            return expr
        expr = _RANGE_SLICE_RE.sub(lambda m: self._resolve_range_slice(m), expr)
        expr = _INDEXED2_RE.sub(lambda m: self._resolve_indexed2(m), expr)
        expr = _INDEXED1_RE.sub(lambda m: self._resolve_indexed1(m), expr)
        expr = _PAREN_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "0")), expr)
        expr = _DOLLAR_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "0")), expr)
        return expr

    def _resolve_range_slice(self, m: re.Match) -> str:
        """Resolve $(var[n..m]) — items n through m as a comma list."""
        name, start_s, end_s = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        try:
            start, end = int(float(start_s)), int(float(end_s))
        except ValueError:
            return ""
        items = value.split("\t") if "\t" in value else value.split(",")
        return ",".join(items[start - 1 : end])

    def _resolve_indexed1(self, m: re.Match) -> str:
        """Resolve $(var[n]) — 1-indexed item from tab/comma-separated list."""
        name, idx_expr = m.group(1), m.group(2)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        idx_s = self._subst_for_arith(idx_expr)

        # Determine list delimiter
        delimiter = "\t" if "\t" in value else ","
        items = value.split(delimiter)

        # Try to parse as single integer first
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            if 1 <= idx <= len(items):
                return items[idx - 1].strip()
            return ""
        except (ValueError, TypeError):
            pass

        # Handle list of indices (WIMS feature): $(var[$list]) where $list='5,4'
        # Returns items 5 and 4, separated by same delimiter as source
        idx_list_str = idx_s.strip()
        idx_parts = idx_list_str.split(",") if "," in idx_list_str else idx_list_str.split("\t")
        result_items = []
        for idx_part in idx_parts:
            try:
                idx = int(round(float(self._eval_arith(idx_part.strip()))))
                if 1 <= idx <= len(items):
                    result_items.append(items[idx - 1].strip())
            except (ValueError, TypeError):
                continue
        return delimiter.join(result_items) if result_items else ""

    def _resolve_indexed2(self, m: re.Match) -> str:
        """Resolve $(var[n;m]) — row n, column m."""
        name, row_expr, col_expr = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        row_s = self._subst_for_arith(row_expr)
        col_s = self._subst_for_arith(col_expr).strip()

        try:
            row = int(round(float(self._eval_arith(row_s))))
        except (ValueError, TypeError):
            return ""

        # Split by tab first (rows)
        rows = value.split("\t") if "\t" in value else value.split(";")
        if not (1 <= row <= len(rows)):
            return ""

        # If col_expr is empty, return entire row
        if not col_s:
            return rows[row - 1].strip()

        try:
            col = int(round(float(self._eval_arith(col_s))))
        except (ValueError, TypeError):
            return ""

        cols = re.split(r"[;,]", rows[row - 1])
        if 1 <= col <= len(cols):
            return cols[col - 1].strip()
        return ""

    # ── Condition evaluation ──────────────────────────────────────────────────

    def _eval_condition(self, kind: str, condition: str) -> bool:
        """Evaluate an !if or !ifval condition."""
        cond = self._subst(condition)

        # WIMS string operators: `A isin B` (substring), `A notin B`,
        # `A wordof B` (whole-word match), `A notwordof B`,
        # `A issametext B`, `A isnotreexpanded B`.
        # Check these before falling through to numeric comparison.
        m = re.match(
            r"^\s*(.+?)\s+(isin|notin|wordof|notwordof|issametext|isnotreexpanded)\s+(.+?)\s*$",
            cond,
            re.I,
        )
        if m:
            needle = m.group(1).strip()
            op = m.group(2).lower()
            haystack = m.group(3).strip()
            if op == "isin":
                return needle in haystack
            if op == "notin":
                return needle not in haystack
            if op in ("issametext", "isnotreexpanded"):
                # Literal string comparison (re-expanded is for WIMS' internal CAS cache)
                return needle == haystack
            words = re.split(r"[,\s\t]+", haystack)
            if op == "wordof":
                return needle in words
            return needle not in words

        # WIMS string `!=` and `=`: handled BEFORE numeric comparison so
        # that values like `<,3,…` (which aren't valid Python) don't trip
        # the numeric branch.
        if kind != "ifval":
            m = re.match(r"^\s*(.+?)\s*!=\s*(.+?)\s*$", cond)
            if m and not re.fullmatch(r"[\d\s\-+*/.()e]+", m.group(1)):
                return m.group(1).strip() != m.group(2).strip()

        # Numeric comparison: !ifval $val10<4, $val8 issametext X,...
        if kind == "ifval" or re.search(r"[<>!=]=?", cond):
            try:
                # Handle WIMS comparison operators
                # Protect multi-char operators before replacing single `=`
                cond_py = cond
                cond_py = (
                    cond_py.replace("!=", "!__NE__")
                    .replace(">=", "!__GE__")
                    .replace("<=", "!__LE__")
                )
                cond_py = cond_py.replace("=", "==")
                cond_py = (
                    cond_py.replace("!__NE__", "!=")
                    .replace("!__GE__", ">=")
                    .replace("!__LE__", "<=")
                )
                
                # Use a small epsilon for comparisons to handle float precision issues
                # e.g. 0.8000000000000001 should not be > 0.8
                ns_with_epsilon = dict(_MATH_NS)
                
                def robust_eval(c_py):
                    # Round float-like numbers in the string to 10 decimal places
                    c_rounded = re.sub(r"(\d+\.\d+)", lambda m: str(round(float(m.group(1)), 10)), c_py)
                    return bool(eval(c_rounded.replace("^", "**"), ns_with_epsilon))
                
                return robust_eval(cond_py)
            except Exception:
                pass

        # String equality: $val22=posi
        if "=" in cond:
            left, _, right = cond.partition("=")
            return left.strip() == right.strip()

        # Fallback for remaining cases
        stripped = cond.strip()
        if not stripped:
            return False
        
        # If it looks like a failed numeric comparison, don't return True just because it's non-empty
        if any(op in stripped for op in ("<", ">", "!=")):
            return False
            
        if stripped == "0":
            return False
            
        return True

    def _eval_loop_expr(self, expr: str, var: str, val: str) -> str:
        """Evaluate a loop body expression, substituting the loop variable."""
        # Substitute bare loop variable (e.g. 'x' in 'reply x')
        # We use a regex to match the variable name as a whole word
        res = re.sub(rf"\b{re.escape(var)}\b", val, expr)
        # Also handle standard substitution (for other variables)
        res = self._subst(res.replace("\\", "$"))
        
        # If it looks like arithmetic, try to eval it
        if any(c in res for c in "+-*/^"):
            try:
                # Use a dummy namespace with common math functions
                ns = dict(_MATH_NS)
                # Also inject all current ctx
                for k, v in self.ctx.items():
                    try: ns[k] = float(v)
                    except: ns[k] = v
                
                eval_res = eval(res.replace("^", "**"), ns)
                if isinstance(eval_res, (int, float)):
                    if isinstance(eval_res, float) and eval_res.is_integer():
                        return str(int(eval_res))
                    return str(eval_res)
            except:
                pass
        return res

    # ── Commands ──────────────────────────────────────────────────────────────

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
            subst_args = self._subst(args)
            items = [x for x in re.split(r",|\t", subst_args) if x.strip()]
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
            # `!rawmath` normalises a math expression, keeping it in a form
            # suitable for downstream evaluation (`pari print()`, plotting).
            # NOT a LaTeX conversion — that's `!texmath`.
            expr = self._subst(args)
            expr = expr.replace("+-", "-").replace("-+", "-").replace("--", "+").replace("++", "+")
            return expr

        if cmd == "texmath":
            return _sympy_to_latex(self._subst(args))

        if cmd == "insmath":
            return self._subst(args)

        if cmd == "nosubst":
            return args

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
            # !mathsubst x=1 in x^2+x -> 1^2+1
            m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
            if not m:
                return self._subst(args)
            subst_list = self._subst(m.group(1)).strip()
            expr = self._subst(m.group(2)).strip()
            for part in subst_list.split(","):
                if "=" in part:
                    k, v = part.split("=", 1)
                    k, v = k.strip(), v.strip()
                    # case-insensitive match for the variable key
                    expr = re.sub(rf"\b{re.escape(k)}\b", v, expr, flags=re.IGNORECASE)
            return expr

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

        return f"UNKNOWN_CMD:{cmd}"

    def _cmd_randint(self, args: str) -> str:
        """!randint a, b — random integer in [a, b]."""
        parts = [self._subst(p.strip()) for p in args.split(",")]
        if len(parts) < 2:
            return "0"
        try:
            a = int(round(float(self._eval_arith(parts[0]))))
            b = int(round(float(self._eval_arith(parts[1]))))
            return str(self.rng.randint(a, b))
        except (ValueError, TypeError):
            return "0"

    def _cmd_random(self, args: str) -> str:
        """!random a, b — random float in [a, b]."""
        parts = [self._subst(p.strip()) for p in args.split(",")]
        if len(parts) < 2:
            return "0"
        try:
            a = float(self._eval_arith(parts[0]))
            b = float(self._eval_arith(parts[1]))
            return f"{self.rng.uniform(a, b):.4f}"
        except (ValueError, TypeError):
            return "0"

    def _cmd_randitem(self, args: str) -> str:
        """!randitem item1, item2, ... — pick one randomly."""
        val = self._subst(args)
        items = [x.strip() for x in re.split(r",|\t", val) if x.strip()]
        return self.rng.choice(items) if items else ""

    def _cmd_nonempty(self, args: str) -> str:
        """!nonempty items/rows list — remove empty entries."""
        m = re.match(r"(items?|rows?)\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind = m.group(1).lower()
        val = self._subst(m.group(2))
        sep = "\t" if kind.startswith("row") else ","
        items = [x.strip() for x in val.split(sep) if x.strip()]
        return sep.join(items)

    def _cmd_shuffle(self, args: str) -> str:
        """!shuffle list — return list items in random order."""
        # !shuffle 10 -> [1, 2, ..., 10] shuffled
        val = self._subst(args.strip())
        if val.isdigit():
            items = [str(i) for i in range(1, int(val) + 1)]
        else:
            items = [x.strip() for x in re.split(r",|\t", val) if x.strip()]
        self.rng.shuffle(items)
        return ",".join(items)

    def _cmd_item(self, args: str) -> str:
        """!item I of list — 1-indexed item, or list of items.

        ``I`` may be a single index, a ``N to M`` range, or a comma-separated
        list of indices.
        """
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())

        def split_items(s: str) -> list[str]:
            if "\t" in s:
                return s.split("\t")
            return re.split(r",(?![^(]*\))", s)

        # Range: "2 to 5" → items 2 through 5
        range_m = re.match(r"(\d+)\s+to\s+(\d+)", idx_s)
        if range_m:
            a, b = int(range_m.group(1)), int(range_m.group(2))
            items = split_items(data)
            return ",".join(items[a - 1 : b])

        # Comma-separated list of indices → pick each, join with commas
        if "," in idx_s:
            indices: list[int] = []
            for p in idx_s.split(","):
                try:
                    indices.append(int(round(float(self._eval_arith(p.strip())))))
                except (ValueError, TypeError):
                    continue
            items = split_items(data)
            res = []
            for idx in indices:
                if 1 <= idx <= len(items):
                    res.append(items[idx - 1].strip())
            return ",".join(res)

        # Single index
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            items = split_items(data)
            if 1 <= idx <= len(items):
                return items[idx - 1].strip()
        except (ValueError, TypeError):
            pass
        return ""

    def _cmd_row(self, args: str) -> str:
        """!row I of matrix — 1-indexed tab-separated row."""
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            rows = data.split("\t")
            if 1 <= idx <= len(rows):
                return rows[idx - 1].strip()
        except (ValueError, TypeError):
            pass
        return ""

    def _cmd_replace(self, args: str) -> str:
        """!replace [internal/word] A by B in text."""
        # Standard: !replace internal x by y in text
        # Shortcut: !replace x by y in text (defaults to internal)
        m = re.match(r"(internal|word)\s+(.*?)\s+by\s+(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if m:
            mode, old, new, text = m.groups()
        else:
            # Try shortcut without mode prefix
            m = re.match(r"(.*?)\s+by\s+(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
            if m:
                mode, old, new, text = "internal", m.group(1), m.group(2), m.group(3)
            else:
                # Handle cases like '!replace * by in $text' where 'new' is empty and only 1 space exists
                m = re.match(r"(.*?)\s+by\s+in\s+(.*)", args, re.I | re.DOTALL)
                if m:
                    mode, old, new, text = "internal", m.group(1), "", m.group(2)
                else:
                    return self._subst(args)
        
        if mode.lower() == "word":
            # Escape old for regex if using word mode
            return re.sub(rf"\b{re.escape(old)}\b", new, text)
        return text.replace(old, new)

    def _cmd_translate(self, args: str) -> str:
        """!translate A to B in text — character-wise translation."""
        # !translate internal $ to ; in text
        m = re.match(r"(?:internal\s+)?(.*?)\s+to\s+(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        a, b, text = m.groups()
        
        # WIMS translation: if len(b) < len(a), extra chars in a are deleted
        if len(b) < len(a):
            table = str.maketrans(a[:len(b)], b, a[len(b):])
        elif len(b) > len(a):
            table = str.maketrans(a, b[:len(a)])
        else:
            table = str.maketrans(a, b)
            
        return text.translate(table)

    def _cmd_append(self, args: str) -> str:
        """!append item/line X to list."""
        m = re.match(r"(items?|lines?)\s+(.*?)\s+to\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind, val, target = m.groups()
        sep = "\n" if kind.lower().startswith("line") else ","
        if not target.strip():
            return val
        return f"{target}{sep}{val}"

    def _cmd_exec(self, args: str) -> str:
        """!exec maxima expr / !exec pari expr — call external CAS."""
        m = re.match(r"(maxima|pari)\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        engine = m.group(1).lower()
        expr = m.group(2).strip()
        if engine == "maxima":
            return _call_maxima(expr)
        if engine == "pari":
            return _call_pari(expr)
        return ""

    def _cmd_makelist(self, args: str) -> str:
        """!makelist expr for var=start to end — comma-separated list."""
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
            val_str = str(i)
            self.ctx[var] = val_str
            # Expression may contain commas (multi-column row): eval each part
            parts = [self._eval_loop_expr(p.strip(), var, val_str) for p in expr.split(",")]
            results.append(",".join(parts))
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)

        # WIMS standard: !makelist returns a comma-separated list
        # unless it's a matrix with multiple columns (then it's tab-row/comma-col).
        has_multi_col = any("," in r for r in results)
        return ("\t" if has_multi_col else ",").join(results)

    def _cmd_positionof(self, args: str) -> str:
        """!positionof item X in $list — 1-indexed position, 0 if absent."""
        m = re.match(r"item\s+(.*?)\s+in\s*(.*)", args, re.DOTALL | re.I)
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
        """!sort items/rows list — sort alphabetically."""
        m = re.match(r"(items?|rows?)\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind, val = m.group(1).lower(), self._subst(m.group(2))
        sep = "\t" if kind.startswith("row") else ","
        items = [x.strip() for x in val.split(sep) if x.strip()]
        items.sort()
        return sep.join(items)

    def _cmd_values(self, args: str) -> str:
        """!values V for var=start to end — list of values."""
        return self._cmd_makelist(args).replace("\t", ",")

    def _cmd_listuniq(self, args: str) -> str:
        """!listuniq list — remove duplicates."""
        items = [x.strip() for x in self._subst(args).split(",") if x.strip()]
        seen = set()
        res = []
        for x in items:
            if x not in seen:
                seen.add(x)
                res.append(x)
        return ",".join(res)

    def _cmd_declosing(self, args: str) -> str:
        """!declosing text — remove outer parentheses/brackets."""
        s = self._subst(args).strip()
        if (s.startswith("(") and s.endswith(")")) or (s.startswith("[") and s.endswith("]")):
            return s[1:-1].strip()
        return s

    def _cmd_getopt(self, args: str) -> str:
        """!getopt key in list — extract value from key=value options."""
        m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if not m: return ""
        key, text = m.group(1).strip().lower(), self._subst(m.group(2))
        for part in re.split(r"[\s,]+", text):
            if "=" in part:
                k, v = part.split("=", 1)
                if k.strip().lower() == key:
                    return v.strip()
        return ""

    def _cmd_embraced(self, args: str) -> str:
        """!embraced item N of list — return content inside { }."""
        # WIMS specific; simplified implementation
        items = re.findall(r"\{(.*?)\}", self._subst(args))
        # This is a bit of a guess on how WIMS uses this command
        return ",".join(items)

    def _cmd_word(self, args: str) -> str:
        """!word N of text — 1-indexed word."""
        m = re.match(r"(.*?)\s+of\s+(.*)", args, re.I | re.DOTALL)
        if not m: return ""
        try:
            idx = int(round(float(self._eval_arith(self._subst(m.group(1).strip())))))
            words = self._subst(m.group(2)).split()
            if 1 <= idx <= len(words):
                return words[idx - 1].strip()
        except (ValueError, TypeError):
            pass
        return ""

    def _cmd_column(self, args: str) -> str:
        """!column C of matrix — column slice as comma list."""
        m = re.match(r"(.*?)\s+of\s+(.*)", args, re.I | re.DOTALL)
        if not m: return ""
        try:
            col_idx = int(round(float(self._eval_arith(self._subst(m.group(1).strip())))))
            rows = self._subst(m.group(2)).split("\t")
            res = []
            for r in rows:
                cols = re.split(r"[;,]", r)
                if 1 <= col_idx <= len(cols):
                    res.append(cols[col_idx - 1].strip())
            return ",".join(res)
        except (ValueError, TypeError):
            pass
        return ""

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

        # Some .def files write `reply 1,30` (space between word and index)
        # instead of `reply1,30`; collapse internal whitespace so the ref
        # matches the answer's input_name.
        ref = re.sub(r"\s+", "", ref)

        # Normalise reply ref: r1 → reply1, r\1 → reply1 (loop var refs)
        if ref.startswith("r") and not ref.startswith("reply"):
            suffix = ref[1:]
            # 1. Handle loop variables like \qq in r\qq
            def resolve_loop_var(m):
                name = m.group(1)
                # Try exact, then lowercase, then with m_ prefix (compiler artifact)
                for candidate in (name, name.lower(), f"m_{name}", f"m_{name.lower()}"):
                    if candidate in self.ctx:
                        return str(self.ctx[candidate])
                return name
            
            suffix = re.sub(r"\\(\w+)", resolve_loop_var, suffix)
            # 2. Evaluate bracketed expressions like \[3*\k-2]
            suffix = re.sub(
                r"\\?\[(.+?)\]",
                lambda m: self._eval_arith(m.group(1).replace("\\", "$")),
                suffix,
            )
            try:
                # Suffix might still contain a variable reference like $m_qq
                suffix_val = self._subst(suffix)
                ref = f"reply{int(float(suffix_val))}"
            except (ValueError, TypeError, OverflowError):
                ref = f"reply{suffix}"

        # Handle radio and menu types specially.
        nm = re.match(r"^r(?:eply)?(\d+)$", ref)
        if nm:
            n = nm.group(1)
            reply_type = self.ctx.get(f"replytype{n}", "").strip().lower()
            if reply_type == "radio":
                # Radios are rendered separately by the frontend
                return ""
            elif reply_type == "menu":
                # Menus need a placeholder in the HTML for inline positioning
                label = self._subst(self.ctx.get(f"replyname{n}", "")).strip()
                return f'<span class="oef-menu" name="{ref}" data-label="{label}"></span>'
            elif reply_type == "clickfill":
                return f'<cf-slot name="{ref}"></cf-slot>'

        size_raw = self._subst(size_str).strip()
        textarea_m = re.match(r"^(\d+)\s*[xX]\s*(\d+)$", size_raw)
        if textarea_m:
            return f'<span class="oef-input" name="{ref}" data-size="{size_raw}"></span>'
        try:
            size = int(round(float(self._eval_arith(size_raw))))
        except (ValueError, TypeError):
            size = 10

        return f'<span class="oef-input" name="{ref}" data-size="{size}"></span>'

    # ── Answer extraction ─────────────────────────────────────────────────────

    def _extract_answers(self, df: DefFile) -> list[AnswerDef]:
        answers: list[AnswerDef] = []

        for rm in df.reply_meta:
            n = rm["n"]
            ans_type = self._subst(rm.get("type", "numeric")).strip()
            label = _close_inline_math(self._subst(rm.get("name", "")))
            good_raw = self._eval_value(rm.get("good", ""))
            weight = float(self._subst(rm.get("weight", "1")) or "1")
            option = self._subst(rm.get("option", ""))
            options: dict = {"option": option} if option else {}

            expected = good_raw
            # ?analyze N — réponse vérifiée via :postdef + :test
            analyze_m = re.match(r"^\?analyze\s*(\d+)(?:;(.+))?", good_raw.strip(), re.I)
            if analyze_m:
                ans_type = "analyze"
                options["analyze_var"] = f"val{analyze_m.group(1)}"
                if analyze_m.group(2):
                    expected = analyze_m.group(2)
                else:
                    expected = good_raw

            if ans_type == "radio":
                # Choices are stored in `choice_meta` but usually also in variables
                # referred to by options.
                choices = []
                for cm in df.choice_meta:
                    if cm["n"] == n:
                        # Extract choices
                        correct = self._subst(cm.get("good", ""))
                        wrong = self._subst(cm.get("bad", "")).split(",")
                        choices = [correct] + [w.strip() for w in wrong if w.strip()]
                        # Shuffle choices with a local seed for determinism
                        rng = random.Random(f"{self.seed}_{n}")
                        rng.shuffle(choices)
                        expected = correct
                        break
                options["choices"] = choices

            elif ans_type == "menu":
                # WIMS menu format: "correct_index;choice1,choice2,..."
                if ";" in good_raw:
                    idx_str, choices_str = good_raw.split(";", 1)
                    try:
                        correct_idx = int(idx_str.strip())
                        choices = [c.strip() for c in choices_str.split(",") if c.strip()]
                        if 1 <= correct_idx <= len(choices):
                            expected = choices[correct_idx - 1]
                        if "shuffle" in option.lower():
                            rng = random.Random(f"{self.seed}_{n}")
                            rng.shuffle(choices)
                        options["choices"] = choices
                    except (ValueError, IndexError):
                        pass

            elif ans_type == "clickfill":
                # Format: "correct_answer;wrong1,wrong2,..."
                if ";" in good_raw:
                    correct_part, wrongs_str = good_raw.split(";", 1)
                    correct_part = correct_part.strip()
                    wrong_items = [w.strip() for w in wrongs_str.split(",") if w.strip()]
                else:
                    correct_part = good_raw.strip()
                    wrong_items = []
                if correct_part:
                    correct_part = _close_inline_math(correct_part)
                    wrong_items = [_close_inline_math(w) for w in wrong_items]
                    choices = [correct_part] + wrong_items
                    seen: set[str] = set()
                    choices = [c for c in choices if not (c in seen or seen.add(c))]  # type: ignore[func-returns-value]
                    random.Random(f"{self.seed}_{n}").shuffle(choices)
                    expected = correct_part
                    options["choices"] = choices

            answers.append(
                AnswerDef(
                    label=label,
                    expected=expected,
                    answer_type=ans_type,
                    options=options,
                    weight=weight,
                    input_name=f"reply{n}",
                    logical_name=label if label else f"reply{n}",
                )
            )

        return answers

    def _cmd_mathsubst(self, args: str) -> str:
        """!mathsubst x=1 in x^2+x -> 1^2+1"""
        # (This is already handled inline in _eval_cmd, but keeping the method stub
        # if other parts of the engine call it directly)
        return self._eval_cmd("mathsubst", args)


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


def check_analyze(
    ev_ctx: dict,
    postdef_instructions: list,
    test_instructions: list,
    analyze_replies: dict,
    seed: int,
) -> dict:
    """Exécute :postdef puis :test avec les réponses élève et retourne les condtestN."""
    engine = DefEngine(seed=seed)
    engine.ctx.update(ev_ctx)
    for var_n, value in analyze_replies.items():
        # var_n is a number (e.g. 64); set the matching valN variable
        engine.ctx[f"val{var_n}"] = f"({value})"
    engine._exec(postdef_instructions, output_buf=None)
    engine._exec(test_instructions, output_buf=None)
    return {k: int(v) for k, v in engine.ctx.items()
            if k.startswith("condtest") and str(v).strip() in ("0", "1")}


def render_feedback(
    ev_ctx: dict,
    postdef_instructions: list,
    test_instructions: list,
    feedback_instructions: list,
    replies_by_name: dict,
    results: list,  # list of AnswerResult
    seed: int,
) -> str:
    """Exécute :postdef, :test puis :feedback avec les réponses élève et retourne le HTML."""
    engine = DefEngine(seed=seed)
    engine.ctx.update(ev_ctx)

    # CRITICAL: Clear any pre-existing internal reply variables to prevent leakage
    # of correct answers into the student reply context.
    keys_to_clear = [
        k for k in engine.ctx.keys() 
        if re.match(r"^(m_)?(?:reply|r)\d+$", k, re.I) 
        or re.match(r"^reply(good|name|type|option|weight)\d+$", k, re.I)
    ]
    for k in keys_to_clear:
        engine.ctx.pop(k)

    # Inject student replies and scores into context
    # First, ensure all possible reply variables are at least an empty string
    for i in range(1, 101): # OEF typically has at most 100 replies
        engine.ctx[f"reply{i}"] = ""
        engine.ctx[f"m_reply{i}"] = ""
        engine.ctx[f"r{i}"] = ""
        engine.ctx[f"m_r{i}"] = ""

    for name, value in replies_by_name.items():
        engine.ctx[name] = value
        engine.ctx[f"m_{name}"] = value
        # Also alias to short names r1, r2 etc. if it's reply1, reply2
        m = re.match(r"^reply(\d+)$", name, re.I)
        if m:
            engine.ctx[f"r{m.group(1)}"] = value
            engine.ctx[f"m_r{m.group(1)}"] = value
            
    for res in results:
        engine.ctx[f"m_sc_{res.input_name}"] = str(res.score)
        m = re.match(r"^reply(\d+)$", res.input_name, re.I)
        if m:
            engine.ctx[f"m_sc_r{m.group(1)}"] = str(res.score)

    engine._exec(postdef_instructions, output_buf=None)
    engine._exec(test_instructions, output_buf=None)
    
    html = engine._render_section(feedback_instructions)
    from .presentation import _close_inline_math
    from ..flydraw import inline_svg_imgs
    html = _close_inline_math(html)
    html = inline_svg_imgs(html)
    return html


def _parse_numeric(s: str) -> float:
    """Parse a numeric string that may be a fraction like '3/2' or '-7/4'."""
    s = s.strip()
    if "/" in s:
        parts = s.split("/", 1)
        return float(parts[0]) / float(parts[1])
    return float(s)
