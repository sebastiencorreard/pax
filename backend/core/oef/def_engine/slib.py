"""Sub-script (slib) execution + the small built-in proc handlers.

WIMS exercises delegate to *slib* scripts (under ``<module>/slib/<name>``
or the WIMS shared ``slib/<…>`` tree) and to the ``oef/draw.phtml`` /
``slib/stat/median`` built-ins. Both are entered through ``!readproc`` in
the .def, with the question section sometimes calling them via
``!read oef/draw.phtml`` for inline graphs.

The mixin in this module provides:

- ``_cmd_readproc`` — dispatcher: handles the two built-ins and
  delegates ``slib/<name>`` to ``_run_slib``.
- ``_run_slib`` — locates the script (module-local first, then the
  vendored WIMS ``scripts/slib/`` tree), reads it, and runs the line
  list through ``_run_script_lines`` while sharing the engine's ctx.
- ``_run_script_lines`` — flat single-pointer interpreter for the
  WIMS-script subset that slib needs (``!if/!else/!endif``,
  ``!for/!next``, ``!goto :label``, ``!exit``). Distinct from
  ``DefEngine._exec`` which walks the structured ``Instruction`` tree
  parsed from the .def itself.
- ``_compute_weighted_median`` — built-in for ``slib/stat/median`` so
  we don't have to fully run that slib's chain of dependencies.
- ``_find_wims_scripts_dir`` — walks up from ``def_path`` to find the
  vendored WIMS scripts directory.

The mixin reaches into ``DefEngine`` for ``ctx`` (the var dict),
``def_path`` (for path resolution), and the helpers ``_subst``,
``_eval_value``, ``_eval_arith``, ``_eval_condition``, ``_eval_cmd``.
"""

from __future__ import annotations

import os
import random
import re

from .cas import _MATH_NS  # noqa: F401  # re-exported for callers if needed


class _SlibExit(Exception):
    """Sentinel raised by `!exit` inside a slib script to stop execution."""


class _SlibMixin:
    """Slib runner methods. Mixed into ``DefEngine`` — see ``runtime`` notes."""

    # Attributes provided by the concrete ``DefEngine`` class.
    ctx: dict[str, str]
    def_path: str | None
    rng: "random.Random"

    # Methods provided by the concrete ``DefEngine`` class. Stub bodies make
    # ``self._subst(...)`` resolvable for type-checkers; at runtime the MRO
    # picks ``DefEngine``'s real implementations, which override these.
    def _subst(self, s: str) -> str: ...

    def _eval_value(self, value: str) -> str: ...

    def _eval_arith(self, expr: str) -> str: ...

    def _eval_condition(self, kind: str, condition: str) -> bool: ...

    def _eval_cmd(self, cmd: str, args: str) -> str: ...

    # ── Public slib entry points ────────────────────────────────────────────

    def _cmd_randrecord(self, args: str) -> str:
        """``!randrecord <path>`` — pick a random record from a `.don` data file.

        Mirrors WIMS ``calc.c:calc_randfile``: records are separated by lines
        starting with ``:`` (WIMS' ``tag_string`` is ``"\\n:"``). Path is
        resolved relative to the .def file's module directory.
        """
        if not self.def_path:
            return ""
        path = self._subst(args.strip().split()[0]) if args.strip() else ""
        if not path:
            return ""
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        full = os.path.join(module_dir, path)
        if not os.path.exists(full):
            return ""
        try:
            with open(full, encoding="utf-8") as f:
                text = f.read()
        except UnicodeDecodeError:
            with open(full, encoding="cp1252") as f:
                text = f.read()

        chunks = re.split(r"(?:^|\n):", text)
        records = [c.strip("\n") for c in chunks if c.strip()]
        if not records:
            return ""
        return self.rng.choice(records)

    def _cmd_readproc(self, args: str) -> None:
        """`!readproc <path> <args>` — execute a slib script or built-in proc.

        Supports two destinations:
        - ``oef/draw.phtml`` — built-in: render flydraw commands to an SVG
          data URI, store it in ``ctx['ins_url']``.
        - ``slib/<name>`` — read the script next to the .def file and run it
          as a sub-engine sharing this engine's ctx.
        """
        from ..flydraw import flydraw_to_url  # noqa: PLC0415

        rest = args.strip()
        m = re.match(r"^(\S+)\s*(.*)$", rest, re.DOTALL)
        if not m:
            return
        path = m.group(1).strip()
        proc_args = self._subst(m.group(2).strip())

        if path == "slib/stat/median":
            self.ctx["slib_out"] = self._compute_weighted_median(proc_args)
            return

        if path in ("oef/draw.phtml", "oef/canvasdraw.phtml"):
            head, _, body = proc_args.partition("\n")
            size_parts = [p.strip() for p in head.split(",")]
            try:
                xsize = int(float(size_parts[0])) if size_parts else 300
                ysize = int(float(size_parts[1])) if len(size_parts) > 1 else 80
            except ValueError:
                xsize, ysize = 300, 80
            url = flydraw_to_url(xsize, ysize, body)
            # $ins_url stays a bare URL — WIMS callers wrap it explicitly in <img>.
            # $canvasdraw_out is used inline in question text without an explicit
            # <img>, so we store it as a ready-to-render <img> tag.
            self.ctx["ins_url"] = url
            self.ctx["canvasdraw_out"] = f'<img src="{url}" alt="">'
            return

        if path == "slib/geo2D/jsxgraph":
            self.ctx["slib_out"] = self._render_jsxgraph(proc_args)
            return

        if path == "slib/data/random":
            self.ctx["slib_out"] = self._slib_data_random(proc_args)
            return

        if path == "slib/numeration/ecriturelettre":
            res = _ecriture_lettre(proc_args)
            if res is not None:
                self.ctx["slib_out"] = res
                return
            # Non-trivial case (en/it, ordinals, options) → fall through to the
            # generic runner below.

        if path.startswith("slib/"):
            self._run_slib(path, proc_args)
            return

        # Other procs (oef/steps.proc, slib/oef, …) — silently ignore for now.
        return

    def _slib_data_random(self, args: str) -> str:
        """Built-in for ``slib/data/random N,type,data`` — N random items of
        ``data`` (no replacement), seeded. ``type`` is item / word / row; the
        WIMS script chokes in our sub-engine (!distribute/!bound/…), so emulate
        it (couf builds its constant terms this way; without it the list was
        empty and the whole CAS chain derailed).
        """
        parts = args.split(",")
        if len(parts) < 3:
            return ""
        try:
            n = int(float(parts[0].strip()))
        except (ValueError, TypeError):
            return ""
        typ = parts[1].strip().lower()
        data = ",".join(parts[2:]).strip()
        if typ in ("word", "words"):
            items, sep = [w for w in data.split() if w], " "
        elif typ in ("row", "rows", "line", "lines"):
            items, sep = [r.strip() for r in re.split(r"[;\n]", data) if r.strip()], ";"
        else:  # item(s) — comma-separated
            items, sep = [c.strip() for c in data.split(",") if c.strip()], ","
        if not items:
            return ""
        n = max(1, min(n, len(items)))
        shuffled = items[:]
        self.rng.shuffle(shuffled)
        return sep.join(shuffled[:n])

    def _render_jsxgraph(self, proc_args: str) -> str:
        """Built-in for ``slib/geo2D/jsxgraph``: emit a marker div that
        _segment_statement turns into a ``jsxgraph`` segment, rendered by the
        ExerciseJsxgraph Vue component.

        Args from the .def are ``<divid> <boardvar>,[<size>], <jscode>``. We
        keep the div id (the JS calls ``initBoard('<divid>', …)``) and the
        board-init JS. Because it becomes segment *data* (not statement HTML),
        the KaTeX pass never sees the ``\\(d_1\\)``-style labels inside it.
        """
        import html as _html  # noqa: PLC0415

        m = re.match(r"(\S+)\s+[^,]*,\s*\[([^\]]*)\]\s*,(.*)", proc_args, re.DOTALL)
        if m:
            div_id, size_spec, js = m.group(1).strip(), m.group(2), m.group(3).strip()
        else:
            div_id, size_spec, js = "jsxbox", "", proc_args.strip()
        wh = re.search(r"(\d+)\s*x\s*(\d+)", size_spec)
        w, h = (int(wh.group(1)), int(wh.group(2))) if wh else (500, 500)
        mx = re.search(r"max\s*=\s*(\d+)\s*px", size_spec)
        maxw = int(mx.group(1)) if mx else 500
        mn = re.search(r"min\s*=\s*(\d+)\s*px", size_spec)
        minw = int(mn.group(1)) if mn else 0
        # Tabs are just statement separators in the .def-authored JS; drop them
        # so the emitted board div is tab-free and can be stored in a
        # TAB-separated list (couf indexes its boards via $(val44[…])).
        js = js.replace("\t", " ")
        minw_attr = f' data-minw="{minw}"' if minw else ""
        return (
            f'<div class="pax-jsxgraph" id="{div_id}" '
            f'data-w="{w}" data-h="{h}" data-maxw="{maxw}"{minw_attr} '
            f'data-jsxgraph="{_html.escape(js, quote=True)}"></div>'
        )

    def _run_slib(self, slib_path: str, params: str) -> None:
        """Locate and execute a ``slib/<name>`` script."""
        from ..def_parser import _merge_continuations  # noqa: PLC0415

        if not self.def_path:
            return
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        wims_scripts_dir = self._find_wims_scripts_dir()
        candidates = [
            os.path.join(module_dir, slib_path),
            os.path.join(module_dir, "slib", "local", slib_path[len("slib/") :]),
        ]
        if wims_scripts_dir:
            candidates.append(os.path.join(wims_scripts_dir, slib_path))
        script_path = next((p for p in candidates if os.path.exists(p)), None)
        if not script_path:
            return
        try:
            with open(script_path, encoding="utf-8") as f:
                text = f.read()
        except UnicodeDecodeError:
            with open(script_path, encoding="cp1252") as f:
                text = f.read()

        saved_parm = self.ctx.get("wims_read_parm", "")
        self.ctx["wims_read_parm"] = params

        lines = _merge_continuations(text.split("\n"))
        try:
            self._run_script_lines(lines)
        except _SlibExit:
            pass
        finally:
            self.ctx["wims_read_parm"] = saved_parm

    def _compute_weighted_median(self, args: str) -> str:
        """Compute the median for ``slib/stat/median`` argument forms.

        Accepts the WIMS ``slib_example`` shapes:
        - ``[v1,v2,...]`` — flat list, plain median
        - ``[v1,v2,...; w1,w2,...]`` — values + weights
        - ``[v1,v2,...],[w1,w2,...]`` — values, weights as separate lists
        """
        s = args.strip()
        if s.startswith("[") and s.endswith("]"):
            s = s[1:-1]
        elif s.startswith("[") and "],[" in s:
            s = s[1:-1].replace("],[", ";")

        if ";" in s:
            v_str, w_str = s.split(";", 1)
            values = [
                self._eval_arith(x.strip()) for x in v_str.split(",") if x.strip()
            ]
            weights = [
                self._eval_arith(x.strip()) for x in w_str.split(",") if x.strip()
            ]
        else:
            values = [self._eval_arith(x.strip()) for x in s.split(",") if x.strip()]
            weights = ["1"] * len(values)

        try:
            vals_f = [float(v) for v in values]
            wts_i = [int(round(float(w))) for w in weights]
        except (ValueError, TypeError):
            return ""

        expanded: list[float] = []
        for v, w in zip(vals_f, wts_i):
            if w > 0:
                expanded.extend([v] * w)
        if not expanded:
            return "0"
        expanded.sort()
        n = len(expanded)
        if n % 2 == 1:
            med = expanded[n // 2]
        else:
            med = (expanded[n // 2 - 1] + expanded[n // 2]) / 2
        if med == int(med):
            return str(int(med))
        return f"{med:g}"

    def _find_wims_scripts_dir(self) -> str | None:
        """Locate the WIMS scripts directory.

        Walks up from ``def_path`` looking for either ``wims-scripts/`` (the
        vendored subset committed under ``ressources/``) or the full
        ``wims/public_html/scripts/`` tree (only present when developing
        against a local WIMS checkout). The first match wins.
        """
        if not self.def_path:
            return None
        d = os.path.abspath(self.def_path)
        for _ in range(10):
            d = os.path.dirname(d)
            if not d:
                break
            for sub in ("wims-scripts", os.path.join("wims", "public_html", "scripts")):
                candidate = os.path.join(d, sub)
                if os.path.isdir(candidate):
                    return candidate
            if d == "/":
                break
        return None

    def _run_script_lines(self, lines: list[str]) -> None:
        """Execute a flat WIMS-script sequence (used for slib scripts).

        Single-pointer interpreter: walks the line list once with branching
        controlled by setting `i` directly. Supports ``!if/!else/!endif``,
        ``!goto :label``, ``!for/!next``, ``!exit``. Designed so a ``!goto``
        nested inside an ``!if`` body can still jump to a top-level
        ``:label`` marker — which is the common slib idiom for the
        help/help_proc dispatch.
        """
        labels: dict[str, int] = {}
        for idx, raw in enumerate(lines):
            s = raw.strip()
            if s.startswith(":") and len(s) > 1 and not s.startswith("::"):
                labels[s[1:].strip()] = idx

        if_stack: list[int] = []
        i = 0
        n = len(lines)
        while i < n:
            line = lines[i]
            stripped = line.strip()
            if not stripped or stripped.startswith("#") or stripped.startswith(":"):
                i += 1
                continue
            if stripped.startswith("!if "):
                cond = stripped[len("!if ") :]
                taken = self._eval_condition("if", cond)
                depth = 1
                j = i + 1
                else_at = -1
                while j < n and depth > 0:
                    s = lines[j].strip()
                    if s.startswith("!if "):
                        depth += 1
                    elif s == "!endif":
                        depth -= 1
                        if depth == 0:
                            break
                    elif s == "!else" and depth == 1:
                        else_at = j
                    j += 1
                if depth != 0:
                    return
                if_stack.append(j)
                if taken:
                    i += 1
                else:
                    i = (else_at + 1) if else_at != -1 else j
                continue
            if stripped == "!else":
                if if_stack:
                    i = if_stack[-1]
                    continue
                i += 1
                continue
            if stripped == "!endif":
                if if_stack:
                    if_stack.pop()
                i += 1
                continue
            if stripped == "!exit":
                raise _SlibExit()
            if stripped.startswith("!for "):
                m = re.match(r"^!for\s+(\w+)\s*=\s*(.+?)\s+to\s+(.+)$", stripped)
                depth = 1
                j = i + 1
                while j < n and depth > 0:
                    s = lines[j].strip()
                    if s.startswith("!for "):
                        depth += 1
                    elif s.startswith("!next"):
                        depth -= 1
                        if depth == 0:
                            break
                    j += 1
                if not m or depth != 0:
                    i = (j + 1) if j < n else n
                    continue
                var = m.group(1)
                try:
                    start = int(round(float(self._eval_arith(self._subst(m.group(2))))))
                    end = int(round(float(self._eval_arith(self._subst(m.group(3))))))
                except (ValueError, TypeError):
                    i = j + 1
                    continue
                body = lines[i + 1 : j]
                saved = self.ctx.get(var)
                for v in range(start, end + 1):
                    self.ctx[var] = str(v)
                    self._run_script_lines(body)
                if saved is not None:
                    self.ctx[var] = saved
                else:
                    self.ctx.pop(var, None)
                i = j + 1
                continue
            if stripped.startswith("!goto "):
                target = stripped[len("!goto ") :].strip().lstrip(":")
                tgt_idx = labels.get(target)
                if tgt_idx is not None:
                    if_stack.clear()
                    i = tgt_idx + 1
                else:
                    i += 1
                continue
            if stripped.startswith("!"):
                cmd_line = stripped[1:].strip()
                cmd, _, cargs = cmd_line.partition(" ")
                # Command results in slib are either used for side effects
                # or stored in slib_out.
                self.ctx["slib_out"] = self._eval_cmd(cmd.lower(), cargs)
            else:
                # Assign: key=value
                m = re.match(r"^\s*(\w+)\s*=\s*(.*)$", line, re.DOTALL)
                if m:
                    name, val = m.group(1), m.group(2)
                    self.ctx[name] = self._eval_value(val)
            i += 1


# ── slib/numeration/ecriturelettre — French cardinal number → words ──────────
#
# Native port of the French *cardinal* path of the WIMS slib script (which is
# too command-heavy to run through the sub-engine, so it returned an empty
# slib_out — bug on quizz 0619). Follows the WIMS default `frrule=1990`: every
# component is joined by hyphens (`sept-millions-soixante-mille`). `vingt`/`cent`
# take a plural `s` only when they end the number; `mille` is invariable.
# English/Italian, ordinals and other options fall back to the generic runner.

_FR_UNITS = (
    "zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
    "neuf", "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
    "dix-sept", "dix-huit", "dix-neuf",
)
_FR_TENS = {2: "vingt", 3: "trente", 4: "quarante", 5: "cinquante", 6: "soixante"}


def _fr_below_100(n: int, final: bool = True) -> str:
    if n < 20:
        return _FR_UNITS[n]
    t, u = divmod(n, 10)
    if t in _FR_TENS:  # 20..69
        base = _FR_TENS[t]
        if u == 0:
            return base
        if u == 1:
            return f"{base}-et-un"
        return f"{base}-{_FR_UNITS[u]}"
    if t == 7:  # 70..79  (soixante + 10..19; 71 = soixante-et-onze)
        if u == 1:
            return "soixante-et-onze"
        return f"soixante-{_FR_UNITS[10 + u]}"
    if t == 8:  # 80..89  (plural s only on a standalone 80)
        if u == 0:
            return "quatre-vingts" if final else "quatre-vingt"
        return f"quatre-vingt-{_FR_UNITS[u]}"
    return f"quatre-vingt-{_FR_UNITS[10 + u]}"  # 90..99


def _fr_below_1000(n: int, final: bool = True) -> str:
    if n < 100:
        return _fr_below_100(n, final)
    h, rest = divmod(n, 100)
    head = "cent" if h == 1 else f"{_FR_UNITS[h]}-cent"
    if rest == 0:
        return head + ("s" if (h > 1 and final) else "")
    return f"{head}-{_fr_below_100(rest, final)}"


def _fr_cardinal(n: int) -> str:
    if n < 0:
        return "moins-" + _fr_cardinal(-n)
    if n == 0:
        return "zéro"
    milliards, n = divmod(n, 1_000_000_000)
    millions, n = divmod(n, 1_000_000)
    milliers, units = divmod(n, 1000)

    parts: list[str] = []
    if milliards:
        c = _fr_below_1000(milliards, final=False)
        parts.append("un-milliard" if milliards == 1 else f"{c}-milliards")
    if millions:
        c = _fr_below_1000(millions, final=False)
        parts.append("un-million" if millions == 1 else f"{c}-millions")
    if milliers:
        # "mille" is invariable, and 1000 is "mille", not "un-mille".
        parts.append("mille" if milliers == 1
                     else f"{_fr_below_1000(milliers, final=False)}-mille")
    if units:
        parts.append(_fr_below_1000(units, final=True))
    return "-".join(parts)


def _split_top_level_commas(s: str) -> list[str]:
    """Split on commas that are not inside [...] brackets."""
    out: list[str] = []
    depth = 0
    cur: list[str] = []
    for ch in s:
        if ch == "[":
            depth += 1
        elif ch == "]":
            depth = max(0, depth - 1)
        if ch == "," and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    out.append("".join(cur))
    return out


def _ecriture_lettre(args: str) -> str | None:
    """Built-in for ``slib/numeration/ecriturelettre``.

    Returns the WIMS item-list of French cardinal spellings, or ``None`` to
    signal the caller to fall back to the generic slib runner (non-French
    language, ordinals, or any explicit options — not ported natively).
    """
    fields = _split_top_level_commas(args)
    lang = fields[1].strip().lower() if len(fields) > 1 and fields[1].strip() else "fr"
    opts = fields[2].strip() if len(fields) > 2 else ""
    if lang != "fr" or opts:
        return None

    data = fields[0].strip() if fields else ""
    if data.startswith("[") and data.endswith("]"):
        items = [x.strip() for x in data[1:-1].split(",") if x.strip()]
    else:
        items = [data] if data else []

    words = []
    for x in items:
        try:
            n = int(round(float(x)))
        except (ValueError, TypeError):
            return None  # not a plain number → let the generic runner try
        words.append(_fr_cardinal(n))
    return ",".join(words)
