"""
Engine for compiled WIMS .def script files.

Evaluates the variable section, renders the :question section (or the literal
question= text), extracts answer metadata, and returns an ExerciseRender.
"""

from __future__ import annotations

import os
import random
import re
from functools import lru_cache

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
    _expr_to_latex,
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
from ..engine import AnswerDef, ExerciseRender, _segment_statement, _embedded_widget_names

# Sous-modules extraits — re-exportés ici pour rétrocompatibilité des imports
# externes : `from core.oef.def_engine import check_analyze` continue de fonctionner.
from .compare import _wims_compare                                      # noqa: E402
from .analyze import _analyze_wrap, check_analyze, render_feedback, _parse_numeric  # noqa: E402


# Patterns for variable substitution.
# A subscript char: anything but "]"/";"/"$", plus a "$" that does NOT start
# a "$(" — so arithmetic parens are allowed (`(2*$m_k-1)%3+1`, `(1+3)`) and
# plain `$var` refs too, but a *nested* `$(…)` makes the pattern stop. That
# deferral lets a nested $(outer[…$(inner[i])…]) resolve inner-first:
# _resolve_indexed_forms loops and picks up the outer once the inner is gone
# (e.g. $(val14[$m_h;$(val11[$m_h])])).
_SUB = r"(?:[^\]$;]|\$(?!\())"
# `$(var[n..m])` — bounds may be ints, `$var`, or arithmetic; _eval_arith
# reduces them after substitution. Bounds use _SUB so a nested range-slice
# `$(outer[$(inner[1..3]);])` doesn't make this regex match the OUTER ref on
# the inner's "..".
_RANGE_SLICE_RE = re.compile(rf"\$\((\w+)\[({_SUB}+?)\.\.({_SUB}+?)\]\)")
_INDEXED2_RE = re.compile(rf"\$\((\w+)\[({_SUB}*?);({_SUB}*)\]\)")  # $(var[n;m])
# INDEXED1's subscript also excludes ";" (built into _SUB) so it never
# swallows a $(var[n;m]) matrix form, whose ";" must go to _INDEXED2_RE.
_INDEXED1_RE = re.compile(rf"\$\((\w+)\[({_SUB}+)\]\)")  # $(var[n])
_PAREN_VAR_RE = re.compile(r"\$\((\w+)\)")  # $(var)
_DOLLAR_VAR_RE = re.compile(r"\$([a-zA-Z_][a-zA-Z0-9_]*)")  # $varname

# Detects "$a,$b,$c" pattern (comma-concat of variable references only).
# Used in _eval_value to neutralise tabs in the substituted parts so the
# resulting list stays unambiguously comma-separated.
_COMMA_VARLIST_RE = re.compile(
    r"^\s*(?:\$\w+|\$\([^)]+\))(?:\s*,\s*(?:\$\w+|\$\([^)]+\)))+\s*$"
)


# ── Public entry point ────────────────────────────────────────────────────────


@lru_cache(maxsize=2048)
def _parse_def_cached(def_path: str) -> DefFile:
    """Parse a .def file into an AST and cache the result by path.

    The AST (DefFile) is read-only: DefEngine re-evaluates it for each seed.
    Files are static during a process lifetime, so no TTL is needed.
    maxsize=2048 covers the full H4 corpus (2270 files) with some headroom.
    """
    try:
        with open(def_path, encoding="utf-8") as f:
            text = f.read()
    except UnicodeDecodeError:
        with open(def_path, encoding="cp1252") as f:
            text = f.read()
    return parse_def(text)


def load_and_render(def_path: str, seed: int | None = None, m_step: int | None = None) -> ExerciseRender:
    """Parse (cached) and evaluate a .def file, returning an ExerciseRender."""
    if seed is None:
        seed = random.randint(0, 2**31)

    def_file = _parse_def_cached(def_path)
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
        # ``imagedir`` is a sentinel "pax-img:_" — the trailing "_" is a dummy
        # path element so ``$imagedir/../<file>`` (the common WIMS pattern)
        # normalises to ``pax-img:<file>`` after path resolution. The actual
        # file lookup happens in inline_pax_images() during post-render.
        self.ctx: dict[str, str] = {
            "empty": "",
            "m_step": "1",
            "step": "1",
            "m_times": "×",
            "m_div": "÷",
            "m_le": "≤",
            "m_ge": "≥",
            "m_neq": "≠",
            "imagedir": "pax-img:_",
        }
        # Path of the .def file being rendered. Used to resolve `!readproc
        # slib/<name>` paths relative to the module directory.
        self.def_path = def_path
        # Set of reply names (e.g. "reply4") referenced by !read oef/embed.phtml
        # during the current render. Used to filter `answers` for dynsteps/course
        # exercises so only the active step's answers are exposed to the API.
        self._touched_replies: set[str] = set()

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

        from ..flydraw import inline_svg_imgs, inline_wims_gifs, inline_pax_images, group_inline_figures, hoist_wims_instruction  # noqa: PLC0415

        html = _close_inline_math(html)
        # Lift the calculator/instruction warning to the top of the statement.
        # Some .def templates (course03_2step.def et al.) emit it AFTER the
        # question, which reads badly — hoist it so it always comes first.
        html = hoist_wims_instruction(html)
        # Group each flydraw figure with its label *before* the SVGs are
        # inlined — the placeholder is a single <img> tag here, easy to
        # locate; once inlined, the body contains its own <image>/<polygon>
        # which the boundary regex would otherwise stumble on.
        html = group_inline_figures(html)
        html = inline_svg_imgs(html)
        html = inline_wims_gifs(html)
        if self.def_path:
            module_dir = os.path.dirname(os.path.dirname(self.def_path))
            html = inline_pax_images(html, module_dir)
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
        widget_names = {
            s["name"] for s in segments
            if s["type"] in ("input", "slot", "menu", "textarea", "correspond")
        }
        # Widgets embedded inside a <table> become native <input>s and don't
        # surface as input segments — count them too so the fallback below
        # doesn't re-append every reply underneath the table.
        widget_names |= _embedded_widget_names(html)
        
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

        # For dynsteps/course exercises, only the answers referenced by the
        # current step's statement are active. `_render_embed` records each
        # reply it sees in `_touched_replies`; we filter `answers` to those.
        # This makes downstream code (hasRadioAnswers, allFilled, check route)
        # naturally correct without per-step bookkeeping.
        if is_dynsteps_flag and self._touched_replies:
            answers = [a for a in answers if a.input_name in self._touched_replies]

        text_replies = [
            a for a in answers
            if a.answer_type.lower()
            not in ("radio", "menu", "mark", "correspond", "jsxgraph")
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

        import html as _html  # noqa: PLC0415
        return ExerciseRender(
            # Decode HTML entities (e.g. "&euro;" → "€") so the title reads as
            # text wherever it is shown plainly (page header, sidebar list).
            title=_html.unescape(self._subst(df.title)),
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
        """Execute a !for loop — numeric (`X = a to b`) or list (`X in list`)."""
        range_s = self._subst(loop.range_expr)

        # List form: `!for VAR in LIST` — iterate VAR over each item of LIST
        # (tab- or comma-separated). For this form the parser leaves loop.var
        # empty and keeps the whole `VAR in LIST` in range_expr.
        m_in = re.match(r"\$?(\w+)\s+in\s+(.*)", range_s, re.I | re.S)
        if m_in and not re.search(r"\s+to\s+", range_s, re.I):
            var = (loop.var.lstrip("$") or m_in.group(1)).strip()
            items_raw = m_in.group(2).strip()
            items = items_raw.split("\t") if "\t" in items_raw else items_raw.split(",")
            saved = self.ctx.get(var)
            for item in items:
                self.ctx[var] = item.strip()
                self._exec(loop.body, output_buf)
            if saved is not None:
                self.ctx[var] = saved
            else:
                self.ctx.pop(var, None)
            return

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

        # Pattern: comma-separated list of $var references only
        # (e.g. "val14=$val19,$val37,$val52,...").  Substitute each ref and
        # neutralise any tabs in the substituted content so the resulting
        # comma-separated list is unambiguous to $(var[i]) access.
        if _COMMA_VARLIST_RE.match(value):
            parts = [self._subst(ref) for ref in re.split(r"\s*,\s*", value.strip())]
            # An item that is a comma-laden HTML blob (e.g. a JSXGraph board
            # div) can't be comma-joined without breaking $(var[i]); use a TAB
            # separator. Plain comma-data items (numbers, fractions) keep the
            # flattening comma-join.
            if any("," in p and "<" in p for p in parts):
                return "\t".join(parts)
            return ",".join(p.replace("\t", " ") for p in parts)

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
        # 2-4. $(var[n..m]) slices, $(var[n;m]) matrices and $(var[n]) lists,
        #      resolved inner-first to a fixpoint (handles nested subscripts).
        s = self._resolve_indexed_forms(s)
        # 5. $(var) simple reference
        s = _PAREN_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "")), s)
        # 6. $var simple reference (skip $[ which was already handled)
        s = _DOLLAR_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "")), s)
        return s

    def _subst_for_arith(self, expr: str) -> str:
        """Substitute variable references inside an arithmetic expression."""
        if not expr or "$" not in expr:
            return expr
        expr = self._resolve_indexed_forms(expr)
        expr = _PAREN_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "0")), expr)
        expr = _DOLLAR_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "0")), expr)
        return expr

    def _resolve_indexed_forms(self, s: str) -> str:
        """Resolve $(var[n..m]), $(var[n;m]) and $(var[n]) inner-first.

        Subscripts exclude "(" (see the regex definitions), so a nested
        reference like $(val14[$m_h;$(val11[$m_h])]) only matches its inner
        $(val11[…]) on the first pass; once that is gone the outer matrix
        form matches on the next pass. We loop to a fixpoint (a small bound
        guards against pathological input) instead of a fixed pass count.
        """
        if "$(" not in s:
            return s
        for _ in range(8):
            before = s
            s = _RANGE_SLICE_RE.sub(self._resolve_range_slice, s)
            s = _INDEXED2_RE.sub(self._resolve_indexed2, s)
            s = _INDEXED1_RE.sub(self._resolve_indexed1, s)
            # Collapse *defined* simple `$(var)` refs too: subscripts exclude
            # `$(`, so a simple ref nested in a subscript (e.g. the row index in
            # `$(val8[$(tmp0);])`) would otherwise never disappear and the outer
            # matrix form could never match. Undefined names are left as-is so
            # the caller's final pass applies its own default ("" vs "0").
            s = _PAREN_VAR_RE.sub(
                lambda m: str(self.ctx[m.group(1)]) if m.group(1) in self.ctx
                else (str(self.ctx[m.group(1).lower()]) if m.group(1).lower() in self.ctx
                      else m.group(0)),
                s,
            )
            if s == before:
                break
        return s

    @staticmethod
    def _tab_is_separator(value: str) -> bool:
        """Whether the TAB acts as the list separator in ``value``.

        The WIMS list separator is the comma. pax additionally uses a TAB as an
        *internal* separator for lists whose items contain commas (HTML/board
        blobs — see _eval_assignment), where each item ends in a non-comma char
        (``>``/``}``) so the tab follows it. But a tab that merely follows a
        comma (``,\\t``) is cosmetic source whitespace, not a separator: e.g.
        ``val7=… suivante&nbsp;,\\t… suivantes&nbsp;`` is a 2-item *comma* list,
        the tab just padding the source. So a TAB is the separator only when at
        least one tab is preceded (modulo spaces) by a non-comma character.
        """
        return "\t" in value and re.search(r"[^,\s]\s*\t", value) is not None

    def _split_list_items(self, value: str) -> list[str]:
        """Split a WIMS list value into items (TAB- or comma-separated)."""
        if self._tab_is_separator(value):
            return value.split("\t")
        # Comma split, but keep commas nested inside parentheses intact.
        return re.split(r",(?![^(]*\))", value)

    def _resolve_range_slice(self, m: re.Match) -> str:
        """Resolve $(var[n..m]) — items n through m as a comma list.

        Bounds can be expressions (e.g. `$val6`, `$val6+1`); they're
        substituted and evaluated via `_eval_arith` before slicing.
        """
        name, start_s, end_s = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        try:
            start = int(round(float(self._eval_arith(self._subst_for_arith(start_s)))))
            end = int(round(float(self._eval_arith(self._subst_for_arith(end_s)))))
        except (ValueError, TypeError):
            return ""
        items = self._split_list_items(value)
        return ",".join(items[start - 1 : end])

    def _resolve_indexed1(self, m: re.Match) -> str:
        """Resolve $(var[n]) — 1-indexed item from tab/semicolon/comma-separated list."""
        name, idx_expr = m.group(1), m.group(2)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        idx_s = self._subst_for_arith(idx_expr)

        # Detect delimiter: a TAB is the separator only when it follows a
        # non-comma char (a real pax tab-join); a ",\t" is cosmetic source
        # whitespace, so the comma is the separator (see _tab_is_separator).
        # Do NOT treat ";" as a delimiter for single-subscript access — items
        # may legitimately contain ";" inside HTML entities like &#44; (comma).
        if self._tab_is_separator(value):
            delimiter = "\t"
            items = value.split("\t")
        else:
            delimiter = ","
            items = re.split(r",(?![^(]*\))", value)

        # Try to parse as single integer first
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            if 1 <= idx <= len(items):
                return items[idx - 1].strip()
            # WIMS negative index: -1 = last item, -2 = second-to-last, …
            if -len(items) <= idx <= -1:
                return items[idx].strip()
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

    @staticmethod
    def _split_rows_by_semi(value: str) -> list[str]:
        """Split by ';' while preserving ';' that closes an HTML entity (&#40; &amp; …).

        WIMS data files may contain HTML-encoded characters like &#40; (left paren)
        whose closing ';' would otherwise be mistaken for a row separator.
        """
        _PH = "\x01"
        protected = re.sub(
            r"(&(?:#x?[0-9a-fA-F]+|[a-zA-Z][a-zA-Z0-9]*));",
            lambda mm: mm.group(1) + _PH,
            value,
        )
        return [p.replace(_PH, ";") for p in protected.split(";")]

    def _resolve_indexed2(self, m: re.Match) -> str:
        """Resolve $(var[n;m]) — row n, column m. Supports a list of row indices."""
        name, row_expr, col_expr = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        row_s = self._subst_for_arith(row_expr)
        col_s = self._subst_for_arith(col_expr).strip()

        # Row-separator detection. The OEF source frequently writes
        #   \text{list=item1;\nitem2;\nitem3;\nitem4}
        # which compiles to ``item1;\titem2;\titem3;\titem4`` — the tab is the
        # cosmetic newline, the *real* separator is ``;``. Splitting by tab
        # first would leave a stray ";" on each row (Quiz course03_2step's
        # enonceb list). So: when ``;`` is present AND ``[n;]`` asks for a
        # whole row (col_expr empty), prefer ``;``. For genuine 2D matrices
        # with ``[n;m]``, the existing tab-first split is preserved because
        # those typically don't carry inner ``;`` between rows.
        prefer_semi = (not col_s) and (";" in value)
        if prefer_semi:
            row_sep = ";"
            rows = self._split_rows_by_semi(value)
        elif "\t" in value:
            row_sep = "\t"
            rows = value.split("\t")
        else:
            row_sep = ";"
            rows = self._split_rows_by_semi(value)

        # WIMS feature: $(matrix[$list;]) where $list = "2,3,1,4" returns rows
        # 2,3,1,4 joined by the source separator. Used for shuffled matrices.
        def parse_indices(s: str) -> list[int] | None:
            parts = s.split(",") if "," in s else s.split("\t")
            if len(parts) <= 1:
                return None
            indices: list[int] = []
            for p in parts:
                try:
                    indices.append(int(round(float(self._eval_arith(p.strip())))))
                except (ValueError, TypeError):
                    return None
            return indices

        idx_list = parse_indices(row_s.strip())
        if idx_list is not None:
            picked = [rows[i - 1] for i in idx_list if 1 <= i <= len(rows)]
            if not col_s:
                return row_sep.join(p.strip() for p in picked)
            try:
                col = int(round(float(self._eval_arith(col_s))))
            except (ValueError, TypeError):
                return ""
            result = []
            for r in picked:
                cols = re.split(r"[;,]", r)
                if 1 <= col <= len(cols):
                    result.append(cols[col - 1].strip())
            return row_sep.join(result)

        # Empty row spec → column `col` across ALL rows, e.g. $(matrix[;1])
        # (cof builds the correspond's right column this way). Joined by "," so
        # `$lefts;$(m[;1])` stays a 2-part "lefts;rights" with comma items.
        if not row_s.strip():
            if not col_s:
                return value
            try:
                col = int(round(float(self._eval_arith(col_s))))
            except (ValueError, TypeError):
                return ""
            out = []
            for r in rows:
                cols = re.split(r"[;,]", r)
                if 1 <= col <= len(cols):
                    out.append(cols[col - 1].strip())
            return ",".join(out)

        try:
            row = int(round(float(self._eval_arith(row_s))))
        except (ValueError, TypeError):
            return ""
        if not (1 <= row <= len(rows)):
            return ""

        # If col_expr is empty, return entire row
        if not col_s:
            return rows[row - 1].strip()

        cols = re.split(r"[;,]", rows[row - 1])
        return self._select_cols(cols, col_s)

    def _select_cols(self, cols: list[str], col_s: str) -> str:
        """Select column(s) from a row's cells.

        ``col_s`` is either a single 1-based index or a WIMS range
        ``a..b``. Bounds may be negative (``-1`` = last column), so
        ``2..-1`` means "from column 2 to the end" (used by quizz 0408's
        ``$(matrix[row;2..-1])`` to collect the divisor columns). Returns the
        selected cells joined by ``,``; empty string if the spec can't be
        parsed.
        """
        n = len(cols)

        def _norm(i: int) -> int:
            # WIMS counts negative indices from the end: -1 → n, -2 → n-1.
            return i + n + 1 if i < 0 else i

        if ".." in col_s:
            a, _, b = col_s.partition("..")
            try:
                start = _norm(int(round(float(self._eval_arith(a.strip())))))
                end = _norm(int(round(float(self._eval_arith(b.strip())))))
            except (ValueError, TypeError):
                return ""
            if start > end:
                start, end = end, start
            sel = [cols[i - 1].strip() for i in range(start, end + 1) if 1 <= i <= n]
            return ",".join(sel)

        try:
            col = _norm(int(round(float(self._eval_arith(col_s)))))
        except (ValueError, TypeError):
            return ""
        if 1 <= col <= n:
            return cols[col - 1].strip()
        return ""

    # ── Condition evaluation ──────────────────────────────────────────────────

    def _eval_condition(self, kind: str, condition: str) -> bool:
        """Evaluate a !if or !ifval condition (port of WIMS compare.c).

        Pass ``self._subst`` so substitution happens *after* operator
        identification — matches compare.c's late ``substitute(buf1/buf2)``
        and prevents a `<`/`>` inside a substituted HTML value (e.g. a
        ``$val6`` instruction div) from being parsed as a relational op.
        """
        return _wims_compare(condition, numeric=(kind == "ifval"), subst=self._subst)

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

        if cmd in ("row", "rows"):
            return self._cmd_row(args)

        if cmd == "itemcnt":
            subst_args = self._subst(args)
            items = [x for x in re.split(r",|\t", subst_args) if x.strip()]
            return str(len(items))

        if cmd in ("rowcnt", "rowcount", "rowno", "rownum"):
            val = self._subst(args)
            return str(len(self._split_rows(val)))

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
            # Mirrors WIMS' __replace_plusminus (rawmath.c) which collapses
            # any run of +/- (possibly separated by whitespace) into a
            # single sign. Without this, substituting a negative variable
            # into `$a - $b` produces `3 - -6` instead of `3 + 6`.
            expr = self._subst(args)
            def _collapse(m: re.Match) -> str:
                signs = re.findall(r"[+-]", m.group(0))
                return "-" if signs.count("-") % 2 == 1 else "+"
            expr = re.sub(r"[+-](\s*[+-])+", _collapse, expr)
            return expr

        if cmd == "texmath":
            return _expr_to_latex(self._subst(args))

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

        if cmd == "listintersect":
            return self._cmd_listintersect(args)

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

        if cmd in ("charcnt", "charcount", "charno", "charnum", "lengthof"):
            return str(len(self._subst(args).strip()))

        # ── Missing aliases for already-implemented commands ──────────────────
        if cmd in ("tolower", "lowercase"):
            return self._subst(args).lower()

        if cmd in ("toupper", "uppercase"):
            return self._subst(args).upper()

        if cmd in ("randperm", "randpermute"):
            return self._cmd_shuffle(args)

        # ── Line-based access (like !item but for newline-separated data) ─────
        if cmd in ("line", "lines"):
            return self._cmd_line(args)

        if cmd in ("linecnt", "linecount", "lineno", "linenum"):
            s = self._subst(args)
            n = len([l for l in s.splitlines() if l.strip()])
            return str(n) if n else "0"

        # ── Character access ──────────────────────────────────────────────────
        if cmd in ("char", "chars"):
            return self._cmd_char(args)

        # ── Word count ────────────────────────────────────────────────────────
        if cmd in ("wordcnt", "wordcount", "wordno", "wordnum"):
            return str(len(self._subst(args).split()))

        # ── Arithmetic aggregate ──────────────────────────────────────────────
        if cmd in ("add", "sum"):
            return self._cmd_sum(args)

        if cmd in ("multiply", "prod", "product"):
            return self._cmd_product(args)

        # ── List set operations ───────────────────────────────────────────────
        if cmd in ("listunion",):
            return self._cmd_listunion(args)

        if cmd in ("listcomplement",):
            return self._cmd_listcomplement(args)

        # ── Conversion: items ↔ lines ↔ words ────────────────────────────────
        if cmd in ("items2lines", "itemstolines", "list2lines", "listtolines"):
            s = self._subst(args)
            return "\n".join(x.strip() for x in s.split(",") if x.strip())

        if cmd in ("lines2items", "linestoitems", "lines2list", "linestolist"):
            s = self._subst(args)
            return ",".join(x.strip() for x in s.splitlines() if x.strip())

        if cmd in ("words2items", "wordstoitems", "words2list", "wordstolist"):
            s = self._subst(args)
            return ",".join(s.split())

        if cmd in ("items2words", "itemstowords", "list2words", "listtowords"):
            s = self._subst(args)
            return " ".join(x.strip() for x in s.split(",") if x.strip())

        if cmd in ("lines2words", "linestowords"):
            s = self._subst(args)
            return " ".join(x.strip() for x in s.splitlines() if x.strip())

        if cmd in ("words2lines", "wordstolines"):
            s = self._subst(args)
            return "\n".join(s.split())

        if cmd in ("rows2lines",):
            s = self._subst(args)
            if "\n" not in s and ";" in s:
                return "\n".join(x.strip() for x in s.split(";"))
            return "\n".join(x.strip() for x in s.split("\t") if x.strip())

        if cmd in ("lines2rows",):
            s = self._subst(args)
            return "\t".join(x.strip() for x in s.splitlines() if x.strip())

        # ── String normalisation ──────────────────────────────────────────────
        if cmd in ("singlespace",):
            return re.sub(r"\s+", " ", self._subst(args)).strip()

        if cmd in ("detag",):
            return re.sub(r"<[^>]*>", "", self._subst(args))

        if cmd in ("deaccent",):
            import unicodedata
            s = self._subst(args)
            return "".join(
                c for c in unicodedata.normalize("NFD", s)
                if unicodedata.category(c) != "Mn"
            )

        # ── Random variants ───────────────────────────────────────────────────
        if cmd in ("randword",):
            return self._cmd_randword(args)

        if cmd in ("randline",):
            return self._cmd_randline(args)

        if cmd in ("randchar",):
            s = self._subst(args)
            return self.rng.choice(list(s)) if s else ""

        # ── Arithmetic evaluation ─────────────────────────────────────────────
        if cmd in ("evalue", "eval"):
            try:
                result = self._eval_arith(self._subst(args))
                v = float(result)
                if v == int(v):
                    return str(int(v))
                return f"{v:.6g}"
            except Exception:
                return "0"

        # ── Explicit substitution (no-op: subst already done by caller) ───────
        if cmd in ("subst", "substit", "substitute"):
            return self._subst(args)

        # ── Record access (WIMS datafiles : records séparés par \n:) ─────────
        if cmd in ("record", "records"):
            return self._cmd_record(args)

        if cmd in ("recordcnt", "recordcount", "recordno", "recordnum"):
            return self._cmd_recordcnt(args)

        if cmd in ("randfile",):
            return ""

        if cmd in ("randrecord",):
            return self._cmd_randrecord(args)

        # ── Slib helper commands (mutate self.ctx, return empty string) ────────
        if cmd in ("distribute",):
            self._cmd_distribute(args)
            return ""

        if cmd in ("bound",):
            self._cmd_bound(args)
            return ""

        if cmd in ("default",):
            self._cmd_default(args)
            return ""

        if cmd in ("advance",):
            self._cmd_advance(args)
            return ""

        if cmd in ("reset",):
            self._cmd_reset(args)
            return ""

        # ── Select rows by condition ──────────────────────────────────────────
        if cmd in ("select",):
            return self._cmd_select(args)

        # ── Remaining calc.c commands ─────────────────────────────────────────
        if cmd in ("listintersection",):
            return self._cmd_listintersect(args)

        if cmd in ("date",):
            import datetime
            fmt = self._subst(args).strip() or "+%Y-%m-%d"
            fmt = fmt.lstrip("+")
            try:
                return datetime.datetime.now().strftime(fmt)
            except Exception:
                return datetime.datetime.now().strftime("%Y-%m-%d")

        if cmd in ("htmlmath", "math2html"):
            # PAX uses KaTeX on the frontend; return the LaTeX expression wrapped
            # in \(...\) so the frontend can render it.
            expr = self._subst(args)
            return f"\\({expr}\\)"

        if cmd in ("lookup",):
            return self._cmd_lookup(args)

        if cmd in ("text",):
            return self._cmd_text(args)

        if cmd in ("solve", "rootof"):
            return self._cmd_solve(args)

        if cmd == "insdraw":
            return self._cmd_insdraw(args)

        return f"UNKNOWN_CMD:{cmd}"

    def _cmd_randint(self, args: str) -> str:
        """!randint a, b — random integer in [a, b]; !randint N — in [1, N]."""
        parts = [self._subst(p.strip()) for p in args.split(",")]
        try:
            if len(parts) == 1:
                # Single-arg form: WIMS returns integer in [1, N]
                n = int(round(float(self._eval_arith(parts[0]))))
                return str(self.rng.randint(1, n))
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
        m = re.match(r"(items?|rows?)\s*(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind = m.group(1).lower()
        val = self._subst(m.group(2))
        # Same separator logic as _cmd_shuffle: tab first, then smart comma.
        # Do NOT detect ";" — items may contain ";" inside HTML entities.
        if kind.startswith("row") or "\t" in val:
            sep = "\t"
            items = [x.strip() for x in val.split(sep) if x.strip()]
        else:
            sep = ","
            items = [x.strip() for x in re.split(r",(?![^(]*\))", val) if x.strip()]
        return sep.join(items)

    def _cmd_shuffle(self, args: str) -> str:
        """!shuffle list — return list items in random order."""
        val = self._subst(args.strip())
        if val.isdigit():
            items = [str(i) for i in range(1, int(val) + 1)]
            self.rng.shuffle(items)
            return ",".join(items)
        # Detect separator: tab first; otherwise smart comma split.
        # Do NOT use ";" as a separator: items may contain ";" inside HTML
        # entities like &#44; (comma) or &#40; (open paren).
        if "\t" in val:
            sep, items = "\t", val.split("\t")
        else:
            sep = ","
            items = re.split(r",(?![^(]*\))", val)
        items = [x.strip() for x in items if x.strip()]
        self.rng.shuffle(items)
        return sep.join(items)

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

    @staticmethod
    def _split_rows(data: str) -> list[str]:
        """Sépare les lignes d'une matrice WIMS.

        Priorité : \\n (enregistrements/slib) > \\; > \\t (makelist).
        Correspond à la logique de calc_rowof() dans calc.c.
        Le split par ``;`` protège les entités HTML (&#59;, &amp;, …).
        """
        if "\n" in data:
            return [r for r in data.split("\n") if r.strip()]
        if ";" in data:
            return [r.strip() for r in DefEngine._split_rows_by_semi(data) if r.strip()]
        return [r for r in data.split("\t") if r.strip()]

    def _cmd_row(self, args: str) -> str:
        """!row I of matrix — ligne I (1-indexée), séparateur auto."""
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            rows = self._split_rows(data)
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
        """!translate A to B in text — character-wise translation (port of calc.c calc_translate).

        WIMS allows $CHARS$ as a dollar-delimited character set, e.g.
        ``!translate internal $\\t\\n$ to ;; in $src`` translates each tab or
        newline to a semicolon.  The surrounding ``$`` are delimiters, not
        characters to translate.
        """
        m = re.match(r"(?:internal\s+)?(.*?)\s+to\s+(.*?)\s+in\s*(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        a_raw, b_raw, text_raw = m.groups()

        # Strip $...$ delimiters from character set (WIMS quoting for whitespace/special chars)
        a_stripped = a_raw.strip()
        if a_stripped.startswith("$") and a_stripped.endswith("$") and len(a_stripped) >= 2:
            a = a_stripped[1:-1]  # Literal chars between the $ delimiters
        else:
            a = self._subst(a_raw)

        b = self._subst(b_raw)
        text = self._subst(text_raw)

        # C: if len(b) < len(a), truncate a to len(b) (extra chars in a are IGNORED, not deleted)
        if len(b) < len(a):
            a = a[:len(b)]
        elif len(b) > len(a):
            b = b[:len(a)]

        if not a:
            return text

        table = str.maketrans(a, b)
        return text.translate(table)

    def _cmd_append(self, args: str) -> str:
        """!append item/line/word/semicolon X to list — append with appropriate separator."""
        # Also accepts 'word' (→ space), 'semicolon' (→ ;), 'colon' (→ :).
        m = re.match(r"(items?|lines?|words?|semicolons?|colons?)\s+(.*?)\s+to\s*(.*)",
                     args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind_raw = m.group(1).lower()
        val = self._subst(m.group(2))
        target = self._subst((m.group(3) or "").strip())

        if kind_raw.startswith("line"):
            sep = "\n"
        elif kind_raw.startswith("word"):
            sep = " "
        elif kind_raw.startswith("semi"):
            sep = ";"
        elif kind_raw.startswith("colon"):
            sep = ":"
        else:
            # item: comma-separated, but switch to TAB when the list can't be
            # comma-joined unambiguously — i.e. the new item (or the list)
            # itself contains a comma/tab (e.g. cof appends JSXGraph
            # `board.create('line',[…],{…})` snippets, comma-laden, into one
            # list then reads them back with $(list[N])).
            sep = "\t" if ("\t" in target or "\t" in val or "," in val) else ","

        if not target:
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
        """!makelist expr for var=start to end — or — for var in list."""
        # "for var in list" form: iterate over a comma/tab-separated list
        in_m = re.match(r"(.*?)\s+for\s+(\w+)\s+in\s+(.*)", args, re.I | re.DOTALL)
        range_m = re.match(
            r"(.*?)\s+for\s+(\w+)\s*=\s*(.+?)\s+to\s+(.+)", args, re.I | re.DOTALL
        )
        if in_m:
            expr = in_m.group(1).strip()
            var = in_m.group(2)
            list_raw = self._subst(in_m.group(3).strip())
            # Split list by tab, semicolon, or comma
            if "\t" in list_raw:
                items = list_raw.split("\t")
            elif ";" in list_raw:
                items = list_raw.split(";")
            else:
                items = re.split(r",(?![^(]*\))", list_raw)
            items = [x.strip() for x in items if x.strip()]
        elif range_m:
            expr = range_m.group(1).strip()
            var = range_m.group(2)
            start_s = range_m.group(3).strip()
            end_s = range_m.group(4).strip()
            try:
                start = int(round(float(self._eval_arith(self._subst(start_s)))))
                end = int(round(float(self._eval_arith(self._subst(end_s)))))
            except (ValueError, TypeError):
                return ""
            items = [str(i) for i in range(start, end + 1)]
        else:
            return ""

        saved = self.ctx.get(var)
        results = []
        for val_str in items:
            self.ctx[var] = val_str
            parts = [self._eval_loop_expr(p.strip(), var, val_str) for p in expr.split(",")]
            results.append(",".join(parts))
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)

        # WIMS: !makelist returns tab-separated rows; columns within each row keep commas.
        return "\t".join(results)

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
        """!randrow $matrix — ligne aléatoire (séparateur auto)."""
        val = self._subst(args.strip())
        rows = self._split_rows(val)
        return self.rng.choice(rows) if rows else ""

    def _cmd_sort(self, args: str) -> str:
        """!sort [numeric|reverse] [items|rows|list] LIST — sort."""
        # Strip optional modifiers: numeric, alphabetic, alpha, reverse, down
        numeric = False
        reverse = False
        rest = args
        while True:
            m = re.match(r"(numeric|alphabetic|alpha|reverse|down)\s+(.*)", rest, re.I | re.DOTALL)
            if not m:
                break
            modifier = m.group(1).lower()
            rest = m.group(2)
            if modifier in ("numeric",):
                numeric = True
            if modifier in ("reverse", "down"):
                reverse = True

        m = re.match(r"(items?|rows?|list)\s+(.*)", rest, re.I | re.DOTALL)
        if m:
            kind, val = m.group(1).lower(), self._subst(m.group(2))
        else:
            kind, val = "items", self._subst(rest)

        sep = "\t" if kind.startswith("row") else ","
        items = [x.strip() for x in val.split(sep) if x.strip()]

        if numeric:
            def _num_key(s: str) -> float:
                try:
                    return float(self._eval_arith(s))
                except Exception:
                    return 0.0
            items.sort(key=_num_key, reverse=reverse)
        else:
            items.sort(reverse=reverse)

        return sep.join(items)

    def _cmd_values(self, args: str) -> str:
        """!values V for var=start to end — list of values."""
        return self._cmd_makelist(args).replace("\t", ",")

    def _cmd_listuniq(self, args: str) -> str:
        """!listuniq list — remove duplicates (preserves separator style)."""
        s = self._subst(args)
        sep = "\t" if "\t" in s else ","
        items = [x.strip() for x in s.split(sep) if x.strip()]
        seen: dict = {}
        res = []
        for x in items:
            if x not in seen:
                seen[x] = True
                res.append(x)
        return sep.join(res)

    def _cmd_listintersect(self, args: str) -> str:
        """!listintersect list1 and list2 — items of list1 that appear in list2."""
        m = re.match(r"(.*?)\s+and\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        list1_str = m.group(1).strip()
        list2_str = m.group(2).strip()
        if not list1_str or not list2_str:
            return ""
        sep = "\t" if "\t" in list1_str else ","
        items1 = [x.strip() for x in list1_str.split(sep) if x.strip()]
        items2 = {x.strip() for x in re.split(r"[,\t]", list2_str) if x.strip()}
        return ",".join(x for x in items1 if x in items2)

    def _cmd_declosing(self, args: str) -> str:
        """!declosing text — remove outer parentheses/brackets/braces."""
        s = self._subst(args).strip()
        pairs = [("(", ")"), ("[", "]"), ("{", "}")]
        for open_, close_ in pairs:
            if s.startswith(open_) and s.endswith(close_):
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
        """!column C of matrix — column slice as comma list.

        Rows may be tab-separated (raw WIMS) or ``;``-separated (post-
        ``!translate \\t\\n to ;;``). Columns are always comma-separated,
        and we use a smart split that preserves commas inside ``\\(...\\)``
        (LaTeX) and other parenthesised groups.
        """
        m = re.match(r"(.*?)\s+of\s+(.*)", args, re.I | re.DOTALL)
        if not m: return ""
        try:
            col_idx = int(round(float(self._eval_arith(self._subst(m.group(1).strip())))))
            value = self._subst(m.group(2))
            if "\t" in value:
                rows = value.split("\t")
            else:
                rows = self._split_rows_by_semi(value)
            # Column separator: prefer comma with parenthesis-aware split
            # (default for WIMS matrices). If no row produces multiple
            # comma-cols, the author likely used ``;`` instead.
            all_cols = [re.split(r",(?![^(]*\))", r) for r in rows]
            if all(len(c) == 1 for c in all_cols):
                all_cols = [r.split(";") for r in rows]
            res = []
            for cols in all_cols:
                if 1 <= col_idx <= len(cols):
                    res.append(cols[col_idx - 1].strip())
            return ",".join(res)
        except (ValueError, TypeError):
            pass
        return ""

    # ── Slib helper command implementations ──────────────────────────────────

    def _cmd_distribute(self, args: str) -> None:
        """!distribute items $src into a,b,c — assign each item to a variable."""
        m = re.match(r"items?\s+(.*?)\s+into\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return
        src = self._subst(m.group(1).strip())
        targets = [t.strip() for t in self._subst(m.group(2)).split(",")]
        items = [x.strip() for x in src.split(",")]
        for i, t in enumerate(targets):
            self.ctx[t] = items[i] if i < len(items) else ""

    def _cmd_bound(self, args: str) -> None:
        """!bound VAR within|among LIST [default DEF] — clamp to allowed values.
        !bound VAR between [integer[s]] MIN and|, MAX [default DEF] — numeric clamp.

        Port of exec_bound (exec.c): with `integer`, rounds the input; if the
        value lies in [MIN, MAX] it's kept (or rounded). Otherwise: use DEF if
        provided, else clamp to the nearest boundary.
        """
        # Form 1: "VAR between [integer[s]] MIN <and|,> MAX [default DEF]"
        m = re.match(
            r"(\w+)\s+between\s+(.*?)(?:\s+default\s+(.*))?$",
            args, re.I | re.DOTALL,
        )
        if m:
            var = m.group(1).strip()
            body = self._subst(m.group(2).strip())
            default_s = self._subst(m.group(3).strip()) if m.group(3) else None

            integer_mode = False
            int_m = re.match(r"^integers?\s+(.*)", body, re.I | re.DOTALL)
            if int_m:
                integer_mode = True
                body = int_m.group(1).strip()

            # `and` or `,` separator
            split_m = re.match(r"(.*?)\s+and\s+(.*)", body, re.I | re.DOTALL)
            if not split_m:
                split_m = re.match(r"(.*?),\s*(.*)", body, re.DOTALL)
            if not split_m:
                return
            lo_s = split_m.group(1).strip()
            hi_s = split_m.group(2).strip()

            raw = self.ctx.get(var, "").strip()
            try:
                val = float(self._eval_arith(raw)) if raw else None
                lo = float(self._eval_arith(lo_s))
                hi = float(self._eval_arith(hi_s))
            except (ValueError, TypeError):
                if default_s is not None:
                    self.ctx[var] = default_s
                return
            if lo > hi:
                lo, hi = hi, lo
            if integer_mode and val is not None:
                val = round(val)
            if val is not None and lo <= val <= hi:
                if integer_mode:
                    self.ctx[var] = str(int(val))
                return
            if default_s is not None:
                self.ctx[var] = default_s
                return
            if integer_mode:
                from math import ceil as _ceil, floor as _floor
                lo, hi = _ceil(lo), _floor(hi)
            clamped = lo if (val is None or val < lo) else hi
            self.ctx[var] = str(int(clamped)) if integer_mode else str(clamped)
            return

        # Form 2: "VAR within|among LIST [default DEF]"
        m = re.match(
            r"(\w+)\s+(?:within|among)\s+(.*?)(?:\s+default\s+(.*))?$",
            args, re.I | re.DOTALL,
        )
        if m:
            var = m.group(1).strip()
            allowed = [x.strip() for x in self._subst(m.group(2).strip()).split(",")]
            default_s = self._subst(m.group(3).strip()) if m.group(3) else None
            if self.ctx.get(var, "") in allowed:
                return
            self.ctx[var] = default_s if default_s is not None else (allowed[0] if allowed else "")

    def _cmd_default(self, args: str) -> None:
        """!default VAR=VALUE — set VAR to VALUE only if VAR is currently empty/unset."""
        m = re.match(r"(\w+)\s*=\s*(.*)", args, re.DOTALL)
        if not m:
            return
        var, value = m.group(1).strip(), self._subst(m.group(2).strip())
        if not self.ctx.get(var, "").strip():
            self.ctx[var] = value

    def _cmd_advance(self, args: str) -> None:
        """!advance VAR [step] — increment a counter variable."""
        parts = args.split()
        if not parts:
            return
        var = parts[0].strip()
        step = 1
        if len(parts) >= 2:
            try:
                step = int(self._eval_arith(self._subst(parts[1])))
            except (ValueError, TypeError):
                pass
        try:
            self.ctx[var] = str(int(self.ctx.get(var, "0")) + step)
        except (ValueError, TypeError):
            self.ctx[var] = str(step)

    def _cmd_reset(self, args: str) -> None:
        """!reset VAR — reset a variable to empty string."""
        var = self._subst(args.strip())
        self.ctx[var] = ""

    def _blockof(self, data: str, split_fn, sep: str, idx_s: str) -> str:
        """Generic N-of-LIST picker (port of _blockof in calc.c).

        split_fn(s) -> list[str]; sep is joined between multiple results.
        idx_s may be a single int, 'A to B' range, or comma-separated indices.
        Negative indices are Python-style from end (-1 = last).
        """
        parts = split_fn(data)
        n = len(parts)

        def resolve(i: int) -> int:
            if i < 0:
                return n + i + 1
            return i

        # Range: "2 to 5" or "2..5"
        range_m = re.match(r"(-?\d+)\s+to\s+(-?\d+)", idx_s) or \
                  re.match(r"(-?\d+)\.\.(-?\d+)", idx_s)
        if range_m:
            a = resolve(int(range_m.group(1)))
            b = resolve(int(range_m.group(2)))
            a = max(1, a); b = min(n, b)
            return sep.join(parts[i - 1] for i in range(a, b + 1))

        # Multiple indices
        raw_indices = [s.strip() for s in idx_s.split(",") if s.strip()]
        if len(raw_indices) > 1:
            res = []
            for s in raw_indices:
                try:
                    i = resolve(int(round(float(self._eval_arith(s)))))
                    if 1 <= i <= n:
                        res.append(parts[i - 1])
                except (ValueError, TypeError):
                    pass
            return sep.join(res)

        # Single index
        try:
            i = resolve(int(round(float(self._eval_arith(idx_s)))))
            if 1 <= i <= n:
                return parts[i - 1]
        except (ValueError, TypeError):
            pass
        return ""

    def _cmd_line(self, args: str) -> str:
        """!line N of text — Nth newline-separated line (1-indexed)."""
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        return self._blockof(data, lambda s: [l.strip() for l in s.splitlines() if l.strip()], "\n", idx_s)

    def _cmd_char(self, args: str) -> str:
        """!char N of text — Nth character (1-indexed)."""
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        return self._blockof(data, list, "", idx_s)

    def _cmd_randword(self, args: str) -> str:
        """!randword list — random word from space-separated list."""
        data = self._subst(args)
        words = data.split()
        return self.rng.choice(words) if words else ""

    def _cmd_randline(self, args: str) -> str:
        """!randline text — random newline-separated line."""
        data = self._subst(args)
        lines = [l.strip() for l in data.splitlines() if l.strip()]
        return self.rng.choice(lines) if lines else ""

    def _cmd_sum(self, args: str) -> str:
        """!add / !sum list — arithmetic sum of comma-separated values."""
        parts = [self._subst(p.strip()) for p in args.split(",")]
        total = 0.0
        for p in parts:
            try:
                total += float(self._eval_arith(p))
            except (ValueError, TypeError):
                pass
        if total == int(total):
            return str(int(total))
        return f"{total:g}"

    def _cmd_product(self, args: str) -> str:
        """!multiply / !product — arithmetic product of comma-separated values."""
        parts = [self._subst(p.strip()) for p in args.split(",")]
        result = 1.0
        for p in parts:
            try:
                result *= float(self._eval_arith(p))
            except (ValueError, TypeError):
                pass
        if result == int(result):
            return str(int(result))
        return f"{result:g}"

    def _cmd_listunion(self, args: str) -> str:
        """!listunion L1 and L2 — union of two comma-separated lists (no duplicates)."""
        m = re.match(r"(.*?)\s+and\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        l1 = [x.strip() for x in self._subst(m.group(1)).split(",") if x.strip()]
        l2 = [x.strip() for x in self._subst(m.group(2)).split(",") if x.strip()]
        seen: dict = {}
        result = []
        for item in l1 + l2:
            if item not in seen:
                seen[item] = True
                result.append(item)
        return ",".join(result)

    def _cmd_listcomplement(self, args: str) -> str:
        """!listcomplement L1 in L2 — items of L2 NOT in L1."""
        m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        l1 = {x.strip() for x in self._subst(m.group(1)).split(",") if x.strip()}
        l2 = [x.strip() for x in self._subst(m.group(2)).split(",") if x.strip()]
        seen: dict = {}
        result = []
        for item in l2:
            if item not in l1 and item not in seen:
                seen[item] = True
                result.append(item)
        return ",".join(result)

    def _cmd_select(self, args: str) -> str:
        """!select DATA where CONDITION — filter rows matching condition.

        Supports 'column N' references in CONDITION (replaced by the Nth
        comma-separated column of each row, then evaluated via _eval_condition).
        """
        m = re.match(r"(.*?)\s+where\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        data_raw = self._subst(m.group(1).strip())
        cond_template = m.group(2).strip()

        # Normalise rows to newline-separated
        if "\n" not in data_raw and ";" in data_raw:
            rows = [r.strip() for r in data_raw.split(";") if r.strip()]
        elif "\t" in data_raw:
            rows = [r.strip() for r in data_raw.split("\t") if r.strip()]
        else:
            rows = [r.strip() for r in data_raw.splitlines() if r.strip()]

        selected = []
        for row in rows:
            cols = [c.strip() for c in row.split(",")]

            def inject_columns(cond: str, cols: list[str]) -> str:
                def replace_col(mo: re.Match) -> str:
                    try:
                        ci = int(mo.group(1)) - 1
                        return cols[ci] if 0 <= ci < len(cols) else ""
                    except (ValueError, IndexError):
                        return ""
                return re.sub(r"\bcolumn\s+(\d+)\b", replace_col, cond, flags=re.I)

            cond = inject_columns(cond_template, cols)
            cond = self._subst(cond)
            if _wims_compare(cond, numeric=False):
                selected.append(row)

        return "\n".join(selected)

    def _read_module_file(self, filename: str) -> str | None:
        """Lit un fichier relatif au répertoire module ; None si absent."""
        if not self.def_path:
            return None
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        full = os.path.join(module_dir, filename)
        if not os.path.exists(full):
            return None
        try:
            return open(full, encoding="utf-8").read()
        except UnicodeDecodeError:
            return open(full, encoding="cp1252").read()
        except OSError:
            return None

    @staticmethod
    def _split_records(text: str) -> list[str]:
        """Découpe un fichier WIMS en enregistrements séparés par \\n:.

        Chaque enregistrement inclut son nom comme première ligne
        (sans le ':' initial), conformément au comportement de
        datafile_fnd_record() dans WIMS calc.c.
        """
        chunks = re.split(r"(?:^|\n):", text)
        return [c.rstrip("\n") for c in chunks if c.strip()]

    def _cmd_record(self, args: str) -> str:
        """!record N of FILE — Nième enregistrement d'un fichier données WIMS.

        Format du fichier :
            :nom_enregistrement1
            ligne1
            ligne2
            :nom_enregistrement2
            ...

        Retourne l'enregistrement avec son nom comme première ligne
        (les lignes suivantes sont accessibles via !row 2, !row 3, …).
        """
        m = re.match(r"(.+?)\s+of\s+(\S+)", args, re.I | re.DOTALL)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        filename = self._subst(m.group(2).strip())
        text = self._read_module_file(filename)
        if text is None:
            return ""
        records = self._split_records(text)
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            if 1 <= idx <= len(records):
                return records[idx - 1]
        except (ValueError, TypeError):
            pass
        return ""

    def _cmd_recordcnt(self, args: str) -> str:
        """!recordcnt FILE — nombre d'enregistrements dans un fichier données."""
        filename = self._subst(args.strip())
        text = self._read_module_file(filename)
        if text is None:
            return "0"
        return str(len(self._split_records(text)))

    def _cmd_lookup(self, args: str) -> str:
        """!lookup KEY in DATAFILE — look up KEY in a key:value data file.

        Format of data file:
            key1: value line 1 (may be comma-separated list)
            key2: value line 2
        Lookup is case-insensitive; KEY is trimmed.
        Resolves DATAFILE relative to the module directory (two levels above def).
        """
        m = re.match(r"(.*?)\s+in\s+(\S+)", args, re.I | re.DOTALL)
        if not m:
            return ""
        key = self._subst(m.group(1)).strip()
        filename = self._subst(m.group(2)).strip()
        if not self.def_path or not key:
            return ""
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        full_path = os.path.join(module_dir, filename)
        if not os.path.exists(full_path):
            return ""
        try:
            try:
                text = open(full_path, encoding="utf-8").read()
            except UnicodeDecodeError:
                text = open(full_path, encoding="cp1252").read()
        except OSError:
            return ""
        # Search for "KEY:" at the start of a line (case-insensitive)
        needle = key.lower() + ":"
        for line in text.splitlines():
            if line.lower().startswith(needle):
                return line[len(needle):].strip()
        return ""

    def _cmd_text(self, args: str) -> str:
        """!text SUBCOMMAND ... — WIMS string manipulation for structured text.

        Supported sub-commands (from calc.c `text`):
          select CHARS in STRING  — keep only chars of STRING present in CHARS
          copy   STRING mask MASK — keep chars where MASK digit is '1'
          expand STRING using MASK — replicate chars where MASK digit is '1'
          insert SRC into DST mask MASK — insert SRC chars into DST at '1' positions
        """
        s = self._subst(args)

        # select CHARS in STRING
        m = re.match(r"select\s+(.*?)\s+in\s+(.*)", s, re.I | re.DOTALL)
        if m:
            charset = set(m.group(1).strip())
            text = m.group(2).strip()
            return "".join(c for c in text if c in charset)

        # copy STRING mask MASK
        m = re.match(r"copy\s+(.*?)\s+mask\s+(\S+)", s, re.I | re.DOTALL)
        if m:
            src = m.group(1).strip()
            mask = m.group(2).strip()
            return "".join(c for c, bit in zip(src, mask) if bit == "1")

        # expand STRING using MASK — port of Lib/text.c text_expand:
        # walk MASK cyclically, emitting ' ' for a '0' bit and the next src
        # char for a '1' bit, until every char of STRING has been placed.
        m = re.match(r"expand\s+(.*?)\s+using\s+(\S+)", s, re.I | re.DOTALL)
        if m:
            src = m.group(1).strip()
            mask = m.group(2).strip()
            if not src or not mask or "1" not in mask:
                return ""
            result = []
            i = j = 0
            while i < len(src):
                if mask[j % len(mask)] == "0":
                    result.append(" ")
                else:
                    result.append(src[i])
                    i += 1
                j += 1
            return "".join(result)

        # insert SRC into DST mask MASK
        m = re.match(r"insert\s+(.*?)\s+into\s+(.*?)\s+mask\s+(\S+)", s, re.I | re.DOTALL)
        if m:
            src = m.group(1).strip()
            dst = list(m.group(2).strip())
            mask = m.group(3).strip()
            src_iter = iter(src)
            for i, bit in enumerate(mask):
                if bit == "1" and i < len(dst):
                    try:
                        dst[i] = next(src_iter)
                    except StopIteration:
                        break
            return "".join(dst)

        return s

    def _cmd_insdraw(self, args: str) -> str:
        """!insdraw <flydraw commands> — render the body via flydraw and set
        ``$ins_url`` to the resulting URL. The slib draw/* scripts rely on
        this side effect (they then wrap ``$ins_url`` in an <img> themselves).

        Size comes from ``$insdraw_size`` (``W,H``) — set by the caller right
        before invoking !insdraw. Defaults to 300x300 when missing.
        """
        from ..flydraw import flydraw_to_url  # noqa: PLC0415

        body = self._subst(args)
        size_raw = self._subst(self.ctx.get("insdraw_size", "")).strip()
        size_parts = [p.strip() for p in size_raw.split(",") if p.strip()]
        try:
            w = int(float(size_parts[0])) if size_parts else 300
            h = int(float(size_parts[1])) if len(size_parts) > 1 else w
        except ValueError:
            w, h = 300, 300

        url = flydraw_to_url(w, h, body)
        self.ctx["ins_url"] = url
        return ""

    def _cmd_solve(self, args: str) -> str:
        """!solve EXPR for VAR = START to END — find root of EXPR=0 in [START,END].

        Uses bisection. Returns the root as a decimal string, or '' if not found.
        EXPR may contain '=' (treated as LHS-RHS=0).
        """
        m = re.match(r"(.*?)\s+for\s+(\w+)\s*=\s*(.*?)\s+to\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        expr_raw = self._subst(m.group(1)).strip()
        var = m.group(2).strip()
        try:
            start = float(self._eval_arith(self._subst(m.group(3).strip())))
            stop = float(self._eval_arith(self._subst(m.group(4).strip())))
        except (ValueError, TypeError):
            return ""

        # If expr contains '=', turn it into LHS - RHS
        if "=" in expr_raw and "==" not in expr_raw:
            lhs, _, rhs = expr_raw.partition("=")
            expr_py = f"({lhs.strip()}) - ({rhs.strip()})".replace("^", "**")
        else:
            expr_py = expr_raw.replace("^", "**")

        ns = dict(_MATH_NS)

        def f(v: float) -> float:
            ns[var] = v
            try:
                return float(eval(expr_py, ns))
            except Exception:
                return float("nan")

        # Bisection with 50 steps
        fa, fb = f(start), f(stop)
        if fa != fa or fb != fb:  # NaN check
            return ""
        if fa * fb > 0:
            return ""  # no sign change
        for _ in range(50):
            mid = (start + stop) / 2
            fm = f(mid)
            if fm != fm or abs(stop - start) < 1e-12:
                break
            if fa * fm <= 0:
                stop, fb = mid, fm
            else:
                start, fa = mid, fm
        result = (start + stop) / 2
        if result == int(result):
            return str(int(result))
        return f"{result:.6g}"

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

        # Normalise reply ref: r1 → reply1, r\1 → reply1 (loop var refs),
        # reply\h → reply1 (same loop-var substitution, just with the
        # full `reply` prefix the author wrote).
        prefix = None
        if ref.startswith("reply"):
            prefix = "reply"
        elif ref.startswith("r"):
            prefix = "r"
        if prefix is not None:
            suffix = ref[len(prefix):]
            # 1. Handle loop variables like \qq in r\qq or reply\h
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
            # Record that this reply is referenced by the current statement.
            # Used in render() to filter `answers` for dynsteps/course exercises.
            self._touched_replies.add(f"reply{n}")
            reply_type = self.ctx.get(f"replytype{n}", "").strip().lower()
            if reply_type == "radio":
                # Inline radio (couf): `reply{n},POS,CONTENT` places one choice
                # *here* in the statement, value = POS, label = CONTENT. The
                # whole option set is laid out by the author (e.g. a vertical
                # <ul>), so it's rendered inline instead of in the grid zone.
                if len(parts) >= 3 and parts[1].strip():
                    import html as _h  # noqa: PLC0415
                    pos = parts[1].strip()
                    content = ",".join(parts[2:]).strip()
                    self._inline_radio = getattr(self, "_inline_radio", set())
                    self._inline_radio.add(str(n))
                    return (
                        f'<span class="oef-radio-inline" name="reply{n}" '
                        f'data-value="{pos}" data-content="{_h.escape(content, quote=True)}"></span>'
                    )
                # Plain radio: choices are rendered by the frontend in a
                # dedicated section below the statement; no widget here.
                return ""
            elif reply_type == "mark":
                # mark: clickable choices, reply = the 1-based position clicked.
                # replygood = "correct_pos;choice1,choice2,...".
                # size_str may be a loop variable like "\r" — resolve \varname patterns.
                size_resolved = re.sub(
                    r"\\(\w+)",
                    lambda m: str(
                        self.ctx.get(m.group(1),
                        self.ctx.get(f"m_{m.group(1)}", m.group(0)))
                    ),
                    self._subst(size_str).strip(),
                )
                # Evaluate replygoodN — may still contain $var refs if seeded raw
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                # Format: "pos;choice1,choice2,..." or "pos;choice1;choice2;..."
                if ";" in good_raw:
                    _pos_part, _, choices_part = good_raw.partition(";")
                else:
                    choices_part = good_raw
                # Choices may be ";"-joined (translate chain) or ","-joined.
                # For comma-separated lists use a smart split that avoids breaking
                # commas inside LaTeX \(...) expressions (e.g. "2,5 × 10^19").
                # Always use smart comma split — choices_part may contain ";"
                # inside HTML entities (e.g. &#44; = comma) that must NOT split.
                choices = [c.strip() for c in re.split(r",(?![^(]*\))", choices_part) if c.strip()]

                def _mark_span(col: int) -> str:
                    label = self._subst(choices[col - 1]) if 1 <= col <= len(choices) else ""
                    return (
                        f'<span class="oef-mark-choice" name="{ref}" '
                        f'data-pos="{col}">{label}</span>'
                    )

                # A size_str naming a valid 1-based column → this embed is one
                # choice of a "split" group (author placed one \embed per column).
                # Otherwise (no index, or out of range — e.g. the leftover input
                # width "10") the single embed expands to all proposition choices,
                # as WIMS does by default.
                try:
                    col = int(float(size_resolved))
                except (ValueError, TypeError):
                    col = None
                if col is not None and choices and 1 <= col <= len(choices):
                    return _mark_span(col)
                if choices:
                    return " ".join(_mark_span(i + 1) for i in range(len(choices)))
                return _mark_span(col or 1)
            elif reply_type == "checkbox":
                # The student's reply is the set of checked option *indices*
                # (compared order-insensitively via check_set); the labels come
                # from the proposition list in replygood = "correct;prop1,prop2,…".
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                labels_part = good_raw.partition(";")[2] if ";" in good_raw else ""
                # Smart comma split: don't break commas inside \(...\) math.
                labels = [
                    c.strip()
                    for c in re.split(r",(?![^(]*\))", labels_part)
                    if c.strip()
                ]

                def _box(i: int, label: str) -> str:
                    lbl = self._subst(label)
                    return (
                        f'<label class="oef-checkbox-label">'
                        f'<input type="checkbox" class="oef-checkbox" '
                        f'name="{ref}" value="{i}" /> {lbl}</label>'
                    )

                # A leading integer in size_str that names a valid 1-based option
                # → this embed is one box of a "split" group (author placed one
                # \embed per option via a \for loop). Otherwise (no index, or out
                # of range — e.g. the leftover input width "10") the single embed
                # expands to the whole proposition list, as WIMS does by default.
                idx_m = re.match(r"-?\d+", self._subst(size_str).strip())
                idx = int(idx_m.group()) if idx_m else None
                if idx is not None and labels and 1 <= idx <= len(labels):
                    return _box(idx, labels[idx - 1])
                if labels:
                    return ", ".join(_box(i + 1, lbl) for i, lbl in enumerate(labels))
                # No proposition list available — fall back to a single box.
                value = self._subst(size_str).strip()
                return (
                    f'<input type="checkbox" class="oef-checkbox" '
                    f'name="{ref}" value="{value}" />'
                )
            elif reply_type == "menu":
                # Menus need a placeholder in the HTML for inline positioning
                label = self._subst(self.ctx.get(f"replyname{n}", "")).strip()
                return f'<span class="oef-menu" name="{ref}" data-label="{label}"></span>'
            elif reply_type == "clickfill":
                # Drag-compose answer: emit one target slot per cell. The embed
                # size is "W x H x N" (cell width/height in px, N = slot count,
                # e.g. repgraphint's 60x40x12). Fall back to the length of the
                # correct sequence when N is absent. All slots share `ref`; the
                # frontend composes their ordered, non-empty values into one
                # reply. Entity-safe split (replygood holds &#91;/&#93;/&#59;
                # whose ";" must not be read as the correct;pool separator).
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                # WIMS treats "|" as a row separator too (anstype/fill.inc:15
                # does `!translate internal | to <newline>`), so `correct|pool`
                # is equivalent to `correct;pool`. Normalise before splitting.
                good_raw = good_raw.replace("|", ";")
                rows = self._split_rows_by_semi(good_raw)
                correct_items = [c for c in (rows[0].split(",") if rows else []) if c.strip()]
                size_parts = re.split(r"\s*[xX]\s*", self._subst(size_str).strip())
                nslots = 0
                if len(size_parts) >= 3:
                    try:
                        nslots = int(float(size_parts[2]))
                    except (ValueError, TypeError):
                        nslots = 0
                if nslots <= 0:
                    nslots = len(correct_items) or 1
                try:
                    slot_w = int(float(size_parts[0])) if size_parts else 0
                except (ValueError, TypeError):
                    slot_w = 0
                w_attr = f' data-w="{slot_w}"' if slot_w > 0 else ""
                return "".join(
                    f'<cf-slot name="{ref}" data-index="{i}"{w_attr}></cf-slot>'
                    for i in range(nslots)
                )
            elif reply_type == "correspond":
                # `correspond`: bijection between two columns. replygood
                # is "left1,left2,...;right1,right2,..." (rows separated
                # by ``;``, items by ``,`` — same format as `\column N of`).
                # The right column is shuffled at render time; the user
                # reorders it to match. Size is "V x HG x HD" (vertical,
                # left width, right width).
                import json as _json  # noqa: PLC0415
                import random as _random  # noqa: PLC0415
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                rows = self._split_rows_by_semi(good_raw)
                if len(rows) != 2:
                    return ""
                # Close WIMS inline math `\(…)` to KaTeX `\(…\)` so the
                # frontend typesets the labels (e.g. `\(x \mapsto 2x-2)`); a
                # no-op for plain text.
                # Each column is a WIMS list: TAB-separated when items contain
                # commas (e.g. coordinates "(-1,-2)\t(2,-1)"), otherwise
                # comma-separated. Split per-column so the two sides line up;
                # a bare comma split would yield e.g. 3 colours but 1 coord
                # blob, fail the bijection check below, and render nothing.
                lefts = [
                    _close_inline_math(self._subst(c.strip()))
                    for c in self._split_list_items(rows[0]) if c.strip()
                ]
                rights = [
                    _close_inline_math(self._subst(c.strip()))
                    for c in self._split_list_items(rows[1]) if c.strip()
                ]
                if not lefts or len(lefts) != len(rights):
                    return ""
                # Deterministic shuffle from the engine seed + reply index
                rng = _random.Random(f"{self.seed}_correspond_{n}")
                rights_shuffled = list(rights)
                rng.shuffle(rights_shuffled)
                # Parse size "V x HG x HD"
                size_raw = self._subst(size_str).strip()
                size_parts = re.split(r"\s*[xX]\s*", size_raw)
                try:
                    sizev = int(size_parts[0]) if len(size_parts) >= 1 else 40
                    sizeh1 = int(size_parts[1]) if len(size_parts) >= 2 else 200
                    sizeh2 = int(size_parts[2]) if len(size_parts) >= 3 else sizeh1
                except (ValueError, TypeError):
                    sizev, sizeh1, sizeh2 = 40, 200, 200
                opt_str = self._subst(self.ctx.get(f"replyoption{n}", "")).lower()
                partial = "split" in opt_str or "partialscore" in opt_str
                config = _json.dumps({
                    "lefts": lefts,
                    "rights": rights_shuffled,
                    "sizev": sizev,
                    "sizeh1": sizeh1,
                    "sizeh2": sizeh2,
                    "partial": partial,
                }, ensure_ascii=False)
                # Stash for _extract_answers so AnswerDef gets the same
                # expected/options without re-parsing.
                self._correspond_meta = getattr(self, "_correspond_meta", {})
                self._correspond_meta[ref] = {
                    "lefts": lefts,
                    "rights_correct": rights,
                    "rights_shuffled": rights_shuffled,
                    "sizev": sizev, "sizeh1": sizeh1, "sizeh2": sizeh2,
                    "partial": partial,
                }
                import html as _html  # noqa: PLC0415
                return (
                    f'<span class="oef-correspond" name="{ref}" '
                    f'data-config="{_html.escape(config)}"></span>'
                )

            elif reply_type == "jsxgraph":
                # `type=jsxgraph`: the answer field *is* an interactive board.
                # Render the board (display) here; the script has commas, so we
                # re-parse the raw args instead of the comma-split `size_str`.
                return self._render_jsxgraph_embed(args, ref)

        size_raw = self._subst(size_str).strip()
        textarea_m = re.match(r"^(\d+)\s*[xX]\s*(\d+)$", size_raw)
        if textarea_m:
            return f'<span class="oef-input" name="{ref}" data-size="{size_raw}"></span>'
        try:
            size = int(round(float(self._eval_arith(size_raw))))
        except (ValueError, TypeError):
            size = 10

        return f'<span class="oef-input" name="{ref}" data-size="{size}"></span>'

    def _render_jsxgraph_embed(self, args: str, ref: str) -> str:
        """Render a `type=jsxgraph` answer embed as an interactive board.

        Mirrors WIMS' ``anstype/jsxgraph.input`` parsing of the embed
        ``inputsize``. After the reply ref (before the first comma), the
        remaining TAB-separated "lines" are:

            <W>x<H>                     ← board pixel size
            <divid> <boardvar> [opts]   ← container id, JS board var, [responsive…]
            <script…>                   ← board-init JS (JSXGraph)
            <name>=<val>; …             ← trailing line: the draggable point
                                          placeholder(s) — a NAME used in the
                                          script and its initial VALUE

        WIMS substitutes each placeholder NAME textually with its VALUE so the
        element consuming it (e.g. ``glider [p2_var1,0,l1]`` or
        ``create('point',jxgbox_var1,…)``) is defined. We do the same, then hand
        the board id + size + script to ``_render_jsxgraph`` (the slib renderer
        used by ``slib/geo2D/jsxgraph``). A plain ``var NAME=VALUE`` would break
        when VALUE isn't a single JS expression (coord2's ``[…],{…}``). Answer
        *capture* (reading the dragged position back) is not wired yet — this
        restores the board display in place of a stray text field.
        """
        _, _, rest = args.partition(",")
        lines = rest.split("\t")
        while lines and not lines[-1].strip():
            lines.pop()
        if not lines:
            return ""

        # Trailing line = draggable-variable initialisation (e.g. "p2_var1=1;").
        var_line = lines[-1].strip()
        body = lines[:-1]

        # Line 1 = board size "WxH" (digits and 'x' only).
        if body and re.fullmatch(r"[\dxX\s]+", body[0].strip()):
            size = body[0].strip()
            body = body[1:]
        else:
            size = "500x500"

        # Next line = "<divid> <boardvar> [responsive …options]".
        jbox_line = body[0].strip() if body else ""
        script_lines = body[1:]
        opts = ""
        mopt = re.search(r"\[([^\]]*)\]", jbox_line)
        if mopt:
            opts = mopt.group(1).replace("responsive", "").strip()
            jbox_line = jbox_line[: mopt.start()].strip()
        words = jbox_line.split()
        div_id = words[0] if words else "jsxbox"
        board_var = words[1] if len(words) > 1 else "brd"

        wh = re.search(r"(\d+)\s*[xX]\s*(\d+)", size)
        w, h = (wh.group(1), wh.group(2)) if wh else ("500", "500")

        script = "\t".join(script_lines)
        # Substitute each placeholder NAME with its VALUE in the script (WIMS
        # semantics). Multiple declarations are ";"-separated; split on the
        # first "=" only since VALUE may itself contain "=". Each placeholder
        # also names a draggable element whose coordinates form the reply: WIMS
        # renames `…var…` → `…rep…` (the element actually created in the script)
        # and captures `.X()` (+ `.Y()` for a 2-D point) — dim = item count of
        # the initial value (scalar → 1, `[x,y]` → 2).
        captures: list[tuple[str, int]] = []
        for decl in var_line.split(";"):
            decl = decl.strip()
            if "=" not in decl:
                continue
            vname, vval = (p.strip() for p in decl.split("=", 1))
            if not vname:
                continue
            script = re.sub(rf"\b{re.escape(vname)}\b", lambda _m, v=vval: v, script)
            captures.append((vname.replace("var", "rep"), _jsxgraph_value_dim(vval)))

        full_script = script + self._jsxgraph_capture_js(board_var, captures)
        size_field = f"{w} x {h}" + (f",{opts}" if opts else "")
        proc_args = f"{div_id} {board_var},[{size_field}],{full_script}"
        div = self._render_jsxgraph(proc_args)
        # Tag the board with the reply name so the frontend binds the captured
        # coordinates to this answer field.
        if captures:
            div = div.replace(
                '<div class="pax-jsxgraph"',
                f'<div class="pax-jsxgraph" data-reply="{ref}"', 1,
            )
        return div

    @staticmethod
    def _jsxgraph_capture_js(board_var: str, captures: list[tuple[str, int]]) -> str:
        """JS appended to the board script: report the dragged point(s) back to
        the answer field. Reads each element's coordinates on every board update
        (i.e. while dragging) and calls the `__paxReport` callback the frontend
        injects. Reply format mirrors WIMS: rows ";"-separated, a 2-D point's
        coordinates ","-separated — e.g. "7;" or "3,5;"."""
        if not captures:
            return ""
        parts = [
            f"({obj}.X()+','+{obj}.Y())" if dim >= 2 else f"{obj}.X()"
            for obj, dim in captures
        ]
        arr = "[" + ",".join(parts) + "]"
        return (
            "\t;try{var __paxC=function(){return " + arr + ".join(';')+';';};"
            "if(typeof __paxReport==='function'){"
            f"{board_var}.on('update',function(){{__paxReport(__paxC());}});"
            "__paxReport(__paxC());}}"
            "catch(e){if(typeof console!=='undefined')console.error('pax jsx capture',e);}"
        )

    # ── Answer extraction ─────────────────────────────────────────────────────

    def _resolve_analyze_expected(self, var_name: str, df: "DefFile") -> str:
        """Scan the :test section for an equality involving `$<var_name>`
        and return the evaluated RHS — used by debug/auto-fill for the
        `analyze` answer type.

        Looks for ``$val<N>=<expr>`` (or the symmetric ``<expr>=$val<N>``)
        inside any !if/!ifval condition reachable from :test. Returns
        the first match evaluated against the current ctx, or "" if
        none is found.
        """
        from ..def_parser import IfBlock  # noqa: PLC0415
        # Accept both `=` and WIMS text comparators (issametext / sametext).
        # The operand is a single value that may be a `$(…)` reference (whose
        # own ")" must not truncate the match) — but stop at whitespace so a
        # multi-clause condition (`$v = 5 and …`) still yields just `5`.
        _op = r"(?:==?|issametext|sametext)"
        _val = r"(?:\$\([^()]*\)|[^\s)])+"
        pat_rhs = re.compile(rf"\${re.escape(var_name)}\b\s*{_op}\s*({_val})")
        pat_lhs = re.compile(rf"({_val})\s*{_op}\s*\${re.escape(var_name)}\b")

        def walk(body: list) -> str | None:
            for instr in body:
                if isinstance(instr, IfBlock):
                    cond = instr.condition
                    m = pat_rhs.search(cond) or pat_lhs.search(cond)
                    if m:
                        return self._subst(m.group(1)).strip()
                    sub = walk(instr.then_body) or walk(instr.else_body)
                    if sub:
                        return sub
            return None

        return walk(df.sections.get("test", [])) or ""

    def _extract_answers(self, df: DefFile) -> list[AnswerDef]:
        answers: list[AnswerDef] = []

        # When replycnt=0 but choicecnt>0, synthesise implicit radio replies from
        # choice_meta (WIMS creates an implicit reply slot in this case).
        if not df.reply_meta and df.choice_meta:
            for cm in df.choice_meta:
                n = cm["n"]
                correct = self._subst(cm.get("good", ""))
                wrong_raw = self._subst(cm.get("bad", ""))
                wrong = [w.strip() for w in wrong_raw.split(",") if w.strip()]
                seen_set: set[str] = set()
                choices: list[str] = []
                for c in [correct] + wrong:
                    if c not in seen_set:
                        seen_set.add(c)
                        choices.append(c)
                jnsp = "Je ne sais pas"
                rng = random.Random(f"{self.seed}_{n}")
                rng.shuffle(choices)
                # WIMS always presents "I don't know" as the last option, so
                # append it *after* shuffling the real choices.
                if jnsp not in seen_set:
                    choices.append(jnsp)
                # Close WIMS inline math `\(…)` → KaTeX `\(…\)` so the frontend
                # renders the labels (choices here carry texmath output like
                # `\(y < \frac{9}{3})`). Mirrors the reply_meta path below;
                # `expected` is one of the choices, so close it the same way to
                # keep the reply comparison consistent.
                choices = [_close_inline_math(c) for c in choices]
                # `choicename` is internal metadata in WIMS (field id / answer
                # summary), not a visible prompt: when the choice isn't embedded
                # inline the buttons are shown without it (e.g. ineqequi4's
                # "Intru"). Leave the label empty so the frontend falls back to
                # its neutral "choose an answer" prompt instead of surfacing it.
                answers.append(
                    AnswerDef(
                        label="",
                        expected=_close_inline_math(correct),
                        answer_type="radio",
                        options={"choices": choices},
                        weight=1.0,
                        input_name=f"reply{n}",
                        logical_name=f"reply{n}",
                    )
                )
            return answers

        for rm in df.reply_meta:
            n = rm["n"]
            ans_type = self._subst(rm.get("type", "numeric")).strip()
            label = _close_inline_math(self._subst(rm.get("name", "")))
            good_raw = self._eval_value(rm.get("good", ""))
            weight = float(self._subst(rm.get("weight", "1")) or "1")
            option = self._subst(rm.get("option", ""))
            options: dict = {"option": option} if option else {}

            # Expose to ctx so _render_embed can access them during statement rendering
            self.ctx[f"replygood{n}"] = good_raw
            self.ctx[f"replytype{n}"] = ans_type

            expected = good_raw
            # `analyze_choices` holds the choice list when a radio/menu is
            # *displayed* normally but *checked* via ?analyze (ecrdecimal).
            analyze_choices: str | None = None
            # ?analyze N — réponse vérifiée via :postdef + :test
            analyze_m = re.match(r"^\?analyze\s*(\d+)(?:;(.+))?", good_raw.strip(), re.I)
            if analyze_m:
                var_name = f"val{analyze_m.group(1)}"
                options["analyze_var"] = var_name
                rest = analyze_m.group(2)
                if ans_type in ("radio", "menu"):
                    # radio/menu DISPLAY + analyze-based checking: the part
                    # after ";" is the comma-separated choice list, and the
                    # correct choice comes from the matching :test condition
                    # (e.g. `$val25 issametext $(val11[1;])`). Keep the radio/
                    # menu type so the choices actually render — overriding to
                    # "analyze" here dropped them, leaving an empty <ol>.
                    analyze_choices = rest or ""
                    expected = self._resolve_analyze_expected(var_name, df) or ""
                else:
                    ans_type = "analyze"
                    if rest:
                        expected = rest
                    else:
                        # `$val<N>` is the student's reply, not a stored answer
                        # — the check path uses options["analyze_var"] to feed
                        # the :test section. For debug / auto-fill, peek into
                        # :test for an equality like `$val<N>=<rhs>` and
                        # evaluate `<rhs>` against the current ctx.
                        expected = self._resolve_analyze_expected(var_name, df) or ""

            if ans_type == "radio" and str(n) in getattr(self, "_inline_radio", set()):
                # Inline radio (couf): choices are laid out in the statement by
                # the author (oef-radio-inline spans, value = position). No grid
                # choices; the reply is the selected position and the correct
                # one is the part before ";" in replygood (e.g. "3;2,3,1,4").
                options["inline"] = True
                expected = good_raw.split(";", 1)[0].strip() if ";" in good_raw else good_raw.strip()

            elif ans_type == "radio":
                choices: list[str] = []
                if analyze_choices is not None:
                    # Choices in author order (they already include "Je ne
                    # sais pas"); the correct one was resolved above via the
                    # analyze condition, so no index/shuffle handling here.
                    choices = [c.strip() for c in analyze_choices.split(",") if c.strip()]
                else:
                    for cm in df.choice_meta:
                        if cm["n"] == n:
                            correct = self._subst(cm.get("good", ""))
                            wrong_raw = self._subst(cm.get("bad", ""))
                            wrong = [w.strip() for w in wrong_raw.split(",") if w.strip()]
                            # Dedup: remove duplicates (correct may already be in wrong)
                            seen_set: set[str] = set()
                            choices = []
                            for c in [correct] + wrong:
                                if c not in seen_set:
                                    seen_set.add(c)
                                    choices.append(c)
                            jnsp = "Je ne sais pas"
                            rng = random.Random(f"{self.seed}_{n}")
                            rng.shuffle(choices)
                            # WIMS always presents "I don't know" as the last
                            # option — append it after shuffling the real choices.
                            if jnsp not in seen_set:
                                choices.append(jnsp)
                            expected = correct
                            break

                    if not choices and ";" in good_raw:
                        # Indexed format: "correct_idx;choice1,choice2,..." (like !menu)
                        # Display order = order in the .def. Authors who want
                        # randomisation do it explicitly (e.g. !shuffle on the valN
                        # used for the choices). Re-shuffling here would double up.
                        idx_str, choices_str = good_raw.split(";", 1)
                        try:
                            correct_idx = int(idx_str.strip())
                            choices = [c.strip() for c in choices_str.split(",") if c.strip()]
                            if 1 <= correct_idx <= len(choices):
                                expected = choices[correct_idx - 1]
                        except (ValueError, IndexError):
                            pass

                # Choices may carry WIMS inline math `\(…)` (e.g. sdlectgraph1's
                # factored forms) — close it to KaTeX `\(…\)` so the frontend
                # renders them instead of showing the raw delimiters. No-op for
                # plain-text choices. `expected` is one of the choices, so close
                # it the same way to keep the reply comparison consistent.
                choices = [_close_inline_math(c) for c in choices]
                expected = _close_inline_math(expected)
                options["choices"] = choices

            elif ans_type == "menu":
                # WIMS menu format: "correct_index;choice1,choice2,..."
                if analyze_choices is not None:
                    # menu DISPLAY + analyze checking (see the radio branch).
                    options["choices"] = [
                        c.strip() for c in analyze_choices.split(",") if c.strip()
                    ]
                elif ";" in good_raw:
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

            elif ans_type == "checkbox":
                # Format: "correct_indices;all_indices" (e.g. "1,3;1,2,3,4").
                # The student's reply is the set of checked option indices;
                # expected is the correct subset, compared order-insensitively
                # (check_set). The checkboxes themselves are emitted inline by
                # _render_embed; no choices list is needed here.
                correct_part = good_raw.split(";", 1)[0] if ";" in good_raw else good_raw
                expected = ",".join(
                    c.strip() for c in correct_part.split(",") if c.strip()
                )

            elif ans_type == "mark":
                # Format: "correct_pos;choice1,choice2,..." (WIMS mark / click-in-table)
                # The student's reply is the 1-based column they clicked.
                # expected = that column index as a string.
                if ";" in good_raw:
                    pos_str, _, choices_str = good_raw.partition(";")
                    expected = pos_str.strip()
                    choices = [
                        c.strip()
                        for c in re.split(r",(?![^(]*\))", choices_str)
                        if c.strip()
                    ]
                    options["choices"] = choices
                else:
                    expected = good_raw.strip()

            elif ans_type == "correspond":
                # Bijection between two columns. expected is the right-column
                # items in their *correct* order (joined by ``,``); the
                # widget config (lefts, shuffled rights, sizes) is exposed
                # via the data-config attribute by _render_embed and also
                # mirrored into options for direct access.
                meta = getattr(self, "_correspond_meta", {}).get(f"reply{n}")
                if meta:
                    expected = ",".join(meta["rights_correct"])
                    options["lefts"] = meta["lefts"]
                    options["rights_shuffled"] = meta["rights_shuffled"]
                    options["partial"] = meta["partial"]
                    options["sizes"] = {
                        "v": meta["sizev"],
                        "hg": meta["sizeh1"],
                        "hd": meta["sizeh2"],
                    }
                else:
                    # _render_embed wasn't called (no \embed{} in statement).
                    # Parse replygood directly to still produce a usable
                    # expected value.
                    rows = self._split_rows_by_semi(good_raw)
                    if len(rows) == 2:
                        rights = [
                            self._subst(c.strip())
                            for c in self._split_list_items(rows[1]) if c.strip()
                        ]
                        expected = ",".join(rights)

            elif ans_type == "clickfill":
                # Format: "correct;pool". Split entity-safe — the parts hold
                # HTML entities (&#91; [ , &#93; ] , &#59; ;) whose trailing ";"
                # must not be mistaken for the correct;pool separator. WIMS also
                # accepts "|" as the separator (anstype/fill.inc:15 translates it
                # to a newline/row break), so normalise "|" → ";" first.
                good_raw = good_raw.replace("|", ";")
                rows = self._split_rows_by_semi(good_raw)
                if len(rows) >= 2:
                    correct_str, pool_str = rows[0], ";".join(rows[1:])
                else:
                    correct_str, pool_str = good_raw, ""
                correct_items = [
                    _close_inline_math(c.strip()) for c in correct_str.split(",") if c.strip()
                ]
                pool_items = [
                    _close_inline_math(p.strip()) for p in pool_str.split(",") if p.strip()
                ]
                rng = random.Random(f"{self.seed}_{n}")
                if len(correct_items) > 1:
                    # Multi-slot drag-compose (e.g. repgraphint): the student
                    # arranges labels from the pool into an ordered sequence.
                    # expected = the ordered sequence (comma-joined); choices =
                    # the pool (it already contains every needed label).
                    seen: set[str] = set()
                    choices = [c for c in pool_items if not (c in seen or seen.add(c))]  # type: ignore[func-returns-value]
                    rng.shuffle(choices)
                    options["choices"] = choices
                    options["slots"] = len(correct_items)
                    expected = ",".join(correct_items)
                elif correct_items:
                    # Single-slot: pick the one correct label among distractors.
                    correct = correct_items[0]
                    choices = [correct] + pool_items
                    seen2: set[str] = set()
                    choices = [c for c in choices if not (c in seen2 or seen2.add(c))]  # type: ignore[func-returns-value]
                    rng.shuffle(choices)
                    expected = correct
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


def _jsxgraph_value_dim(value: str) -> int:
    """Dimension of a jsxgraph draggable's initial value: a bracketed
    ``[x,y]`` → the number of top-level items inside (2 here); anything else
    (a scalar like ``1``) → 1. Used to decide whether the reply captures just
    ``.X()`` or both ``.X()`` and ``.Y()``."""
    v = value.strip()
    if not v.startswith("["):
        return 1
    depth = 0
    items = 1
    for ch in v:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
            if depth == 0:
                break
        elif ch == "," and depth == 1:
            items += 1
    return items


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


# _wims_* functions and _WIMS_* constants → compare.py (voir re-export en tête)

