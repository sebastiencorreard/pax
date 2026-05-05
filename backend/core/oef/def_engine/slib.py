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
            with open(full, encoding="iso-8859-1") as f:
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

        if path == "oef/draw.phtml":
            head, _, body = proc_args.partition("\n")
            size_parts = [p.strip() for p in head.split(",")]
            try:
                xsize = int(float(size_parts[0])) if size_parts else 300
                ysize = int(float(size_parts[1])) if len(size_parts) > 1 else 80
            except ValueError:
                xsize, ysize = 300, 80
            self.ctx["ins_url"] = flydraw_to_url(xsize, ysize, body)
            return

        if path.startswith("slib/"):
            self._run_slib(path, proc_args)
            return

        # Other procs (oef/steps.proc, slib/oef, …) — silently ignore for now.
        return

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
            with open(script_path, encoding="iso-8859-1") as f:
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
        """Locate ``wims/public_html/scripts`` by walking up from ``def_path``."""
        if not self.def_path:
            return None
        d = os.path.abspath(self.def_path)
        for _ in range(10):
            d = os.path.dirname(d)
            if not d or d == "/":
                break
            candidate = os.path.join(d, "wims", "public_html", "scripts")
            if os.path.isdir(candidate):
                return candidate
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
                self._eval_cmd(cmd.lower(), cargs)
            else:
                m = re.match(r"^\s*(\w+)\s*=\s*(.*)$", line, re.DOTALL)
                if m:
                    self.ctx[m.group(1)] = self._eval_value(m.group(2))
            i += 1
