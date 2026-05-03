"""
Parser for compiled WIMS .def script files produced by OefMsg2wims.

A .def file has this structure (in order):
  1. Header boilerplate   (!set title=, !if $wims_read_parm..., metadata, val1-5)
  2. Variable section     (sequential assignments, !for, !if blocks)
  3. Answer metadata      (replytype1=, replygood1=, choicename1=, ...)
  4. Statement fields     (question=, hint=, solution=, ...)
  5. !goto stat / !exit
  6. Named sections       (:question, :hint, :solution, :stat, ...)
"""

from __future__ import annotations

import re
from dataclasses import dataclass, field
from typing import Union


# ── Instruction types ─────────────────────────────────────────────────────────


@dataclass
class Assign:
    """key=value — variable assignment (value may start with ! for a command)."""

    name: str
    value: str


@dataclass
class IfBlock:
    """!if / !ifval conditional block."""

    kind: str  # "if" or "ifval"
    condition: str
    then_body: list = field(default_factory=list)
    else_body: list = field(default_factory=list)


@dataclass
class ForLoop:
    """!for var=start to end loop."""

    var: str  # variable name, e.g. "val17", "m_k"
    range_expr: str  # e.g. "1 to 3" or "1 to $val7"
    body: list = field(default_factory=list)


@dataclass
class Output:
    """$() text — output directive in executed sections."""

    html: str  # content after $() and leading tab


@dataclass
class Insmath:
    """!insmath expr — emit a rendered math formula."""

    expr: str


@dataclass
class ReadEmbed:
    """!read oef/embed.phtml args — input widget marker."""

    args: str  # e.g. "r1,10" or "reply1,$val10"


@dataclass
class ReadProc:
    """!readproc path args — complex proc (placeholder/not-implemented)."""

    path: str
    args: str


Instruction = Union[Assign, IfBlock, ForLoop, Output, Insmath, ReadEmbed, ReadProc]


# ── DefFile ───────────────────────────────────────────────────────────────────


@dataclass
class DefFile:
    title: str
    meta: dict  # author, language, precision, varcnt, etc.
    var_instructions: list  # sequential variable evaluation instructions
    reply_meta: list  # [{'n':1,'type':'numeric','name':'...','good':'...'}]
    choice_meta: list  # [{'n':1,'name':'...','good':'...','bad':'...'}]
    ansorder: str  # "r,r,c,r,..."
    statement: str  # literal text or "__EXECUTED__"
    hint: str
    help_text: str
    solution: str
    sections: dict  # {label: [Instruction]}
    stat: dict  # vsavelist, embedcnt


# ── Constants ─────────────────────────────────────────────────────────────────

_SKIP_CONDITIONS = ("wims_read_parm", "testcondition", "status=waiting")

_META_KEYS = frozenset(
    {
        "oef2wims_version",
        "author",
        "email",
        "language",
        "keywords",
        "leftrange",
        "rightrange",
        "computeanswer",
        "precision",
        "varcnt",
        "prevarcnt",
        "postvarcnt",
        "replycnt",
        "choicecnt",
        "conditioncnt",
        "feedbackcnt",
        "format",
    }
)

_REPLY_PREFIXES = ("replytype", "replyname", "replygood", "replyoption", "replyweight")
_CHOICE_PREFIXES = (
    "choicename",
    "choicegood",
    "choicebad",
    "choiceoption",
    "choiceweight",
)

_VAL_BOILERPLATE_RE = re.compile(r"^val[1-5]$", re.IGNORECASE)


# ── Public entry point ────────────────────────────────────────────────────────


def parse(text: str) -> DefFile:
    """Parse a .def file text and return a DefFile."""
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    lines = _merge_continuations(text.split("\n"))

    title = _extract_title(lines)
    raw_sections = _split_by_label(lines)
    main_lines = raw_sections.pop("", [])

    (
        meta,
        var_instr,
        reply_fields,
        choice_fields,
        ansorder,
        statement,
        hint,
        help_text,
        solution,
    ) = _parse_main(main_lines)

    sections: dict[str, list] = {}
    stat: dict = {}
    for label, sec_lines in raw_sections.items():
        instr_list, _ = _parse_instructions(sec_lines, 0)
        if label == "stat":
            for inst in instr_list:
                if isinstance(inst, Assign):
                    stat[inst.name] = inst.value
        else:
            sections[label] = instr_list

    return DefFile(
        title=title,
        meta=meta,
        var_instructions=var_instr,
        reply_meta=_build_indexed_meta(reply_fields, _REPLY_PREFIXES),
        choice_meta=_build_indexed_meta(choice_fields, _CHOICE_PREFIXES),
        ansorder=ansorder,
        statement=statement,
        hint=hint,
        help_text=help_text,
        solution=solution,
        sections=sections,
        stat=stat,
    )


# ── Line pre-processing ───────────────────────────────────────────────────────


def _merge_continuations(lines: list[str]) -> list[str]:
    """Merge lines ending with backslash into the next line.

    The newline is kept (turns into a literal ``\\n`` inside the joined line)
    because WIMS-script values like ``slib_out=cmd1\\<nl>cmd2\\<nl>cmd3``
    must preserve the line breaks: downstream consumers like flydraw require
    one command per line.
    """
    result: list[str] = []
    buf = ""
    for raw in lines:
        if raw.endswith("\\"):
            buf += raw[:-1] + "\n"
        else:
            result.append(buf + raw)
            buf = ""
    if buf:
        result.append(buf)
    return result


def _extract_title(lines: list[str]) -> str:
    for line in lines:
        s = line.strip()
        if s.lower().startswith("!set title="):
            return s.split("=", 1)[1].strip()
    return ""


def _split_by_label(lines: list[str]) -> dict[str, list[str]]:
    """Split lines into sections keyed by their :label.
    The '' key holds lines before the first label."""
    sections: dict[str, list[str]] = {"": []}
    current = ""
    for line in lines:
        s = line.strip()
        if s.startswith(":") and not s.startswith("$()") and len(s) > 1:
            label = s[1:].split()[0].lower()
            current = label
            sections.setdefault(current, [])
        else:
            sections.setdefault(current, []).append(line)
    return sections


# ── Main block parsing ────────────────────────────────────────────────────────


def _parse_main(lines: list[str]):
    instr_list, _ = _parse_instructions(lines, 0)

    meta: dict = {}
    var_instr: list = []
    reply_fields: dict = {}
    choice_fields: dict = {}
    ansorder = ""
    statement = ""
    hint = ""
    help_text = ""
    solution = ""

    for instr in instr_list:
        if not isinstance(instr, Assign):
            var_instr.append(instr)
            continue

        key = instr.name.lower()
        val = instr.value

        if key in _META_KEYS:
            meta[key] = val
        elif key == "ansorder":
            ansorder = val
        elif key == "question":
            statement = val
        elif key == "hint":
            hint = val
        elif key in ("help", "latex"):
            help_text = val
        elif key == "solution":
            solution = val
        elif _VAL_BOILERPLATE_RE.match(key):
            pass  # skip val1-val5 (WIMS session variables)
        elif any(key.startswith(p) for p in _REPLY_PREFIXES):
            _collect_indexed_field(reply_fields, key, val, _REPLY_PREFIXES)
        elif any(key.startswith(p) for p in _CHOICE_PREFIXES):
            _collect_indexed_field(choice_fields, key, val, _CHOICE_PREFIXES)
        else:
            var_instr.append(instr)

    return (
        meta,
        var_instr,
        reply_fields,
        choice_fields,
        ansorder,
        statement,
        hint,
        help_text,
        solution,
    )


def _collect_indexed_field(
    fields: dict, key: str, val: str, prefixes: tuple[str, ...]
) -> None:
    for prefix in prefixes:
        if key.startswith(prefix):
            field_name = prefix.split("reply", 1)[-1].split("choice", 1)[
                -1
            ]  # e.g. 'type', 'name'
            n_str = key[len(prefix) :]
            if n_str.isdigit():
                fields[(int(n_str), field_name)] = val
            return


def _build_indexed_meta(fields: dict, prefixes: tuple[str, ...]) -> list[dict]:
    """Build a list of dicts from (n, field_name) → value dict."""
    by_n: dict[int, dict] = {}
    for (n, field_name), val in fields.items():
        by_n.setdefault(n, {"n": n})[field_name] = val.strip()
    return [by_n[n] for n in sorted(by_n)]


# ── Instruction parser ────────────────────────────────────────────────────────


def _parse_instructions(lines: list[str], start: int) -> tuple[list, int]:
    """Parse lines[start:] into instructions. Returns (instructions, next_i).

    Stops (returning WITHOUT consuming) at: !else, !endif, !next, !exit,
    !goto stat, or end of lines.
    """
    instructions: list = []
    i = start

    while i < len(lines):
        raw = lines[i]
        line = raw.strip()

        # Empty lines and comments
        if not line or line.startswith("#"):
            i += 1
            continue

        # Section labels — shouldn't appear here, but guard
        if line.startswith(":") and not line.startswith("$()"):
            break

        # Block terminators — return without consuming
        if (
            line.startswith("!else")
            or line.startswith("!endif")
            or line.startswith("!next")
            or line.startswith("!exit")
        ):
            break
        if line.startswith("!goto stat"):
            break
        if line.startswith("!goto"):
            i += 1
            continue

        # Skip !set (title already extracted separately)
        if line.lower().startswith("!set "):
            i += 1
            continue

        # !if / !ifval
        if line.startswith("!if ") or line.startswith("!ifval "):
            block, i = _parse_if(lines, i)
            if block is not None:
                instructions.append(block)
            continue

        # !for
        if line.startswith("!for "):
            loop, i = _parse_for(lines, i)
            instructions.append(loop)
            continue

        # $() — output directive
        if line.startswith("$()"):
            html = raw.rstrip("\n")  # preserve the raw line (not stripped)
            html = html.lstrip()  # strip leading whitespace (indentation)
            html = html[3:]  # remove $()
            if html.startswith("\t"):
                html = html[1:]  # remove the conventional tab separator
            instructions.append(Output(html))
            i += 1
            continue

        # !insmath
        if line.startswith("!insmath"):
            expr = line[len("!insmath") :].strip()
            instructions.append(Insmath(expr))
            i += 1
            continue

        # !read oef/embed.phtml
        if "oef/embed.phtml" in line:
            args = re.sub(r".*oef/embed\.phtml\s*", "", line).strip()
            instructions.append(ReadEmbed(args))
            i += 1
            continue

        # !readproc
        if line.startswith("!readproc "):
            rest = line[len("!readproc ") :]
            parts = rest.split(None, 1)
            instructions.append(
                ReadProc(path=parts[0], args=parts[1] if len(parts) > 1 else "")
            )
            i += 1
            continue

        # key=value assignment (key must not start with !)
        if "=" in line and not line.startswith("!"):
            eq = line.index("=")
            name = line[:eq].strip()
            # Value is taken from the raw line to preserve spacing/tabs in value
            raw_eq = raw.index("=")
            value = raw[raw_eq + 1 :].rstrip("\n")
            if name:
                instructions.append(Assign(name=name, value=value))
            i += 1
            continue

        # Unknown !cmd — skip silently
        i += 1

    return instructions, i


def _parse_if(lines: list[str], i: int) -> tuple:
    """Parse an !if / !ifval block. Returns (IfBlock|None, next_i)."""
    line = lines[i].strip()
    if line.startswith("!ifval "):
        kind = "ifval"
        condition = line[len("!ifval ") :].strip()
    else:
        kind = "if"
        condition = line[len("!if ") :].strip()

    # Skip boilerplate session-variable conditions entirely
    if any(pat in condition for pat in _SKIP_CONDITIONS):
        depth = 1
        i += 1
        while i < len(lines) and depth > 0:
            s = lines[i].strip()
            if s.startswith("!if ") or s.startswith("!ifval "):
                depth += 1
            elif s.startswith("!endif"):
                depth -= 1
            i += 1
        return None, i

    then_body, i = _parse_instructions(lines, i + 1)
    else_body: list = []

    # Check for !else
    if i < len(lines) and lines[i].strip().startswith("!else"):
        else_body, i = _parse_instructions(lines, i + 1)

    # Consume !endif
    if i < len(lines) and lines[i].strip().startswith("!endif"):
        i += 1

    return IfBlock(
        kind=kind, condition=condition, then_body=then_body, else_body=else_body
    ), i


def _parse_for(lines: list[str], i: int) -> tuple[ForLoop, int]:
    """Parse a !for loop. Returns (ForLoop, next_i)."""
    line = lines[i].strip()
    for_args = line[len("!for ") :]

    # Syntax: "var =start to end" or "var=start to end" or "var =start..end"
    m = re.match(r"(\S+)\s*=\s*(.+)", for_args)
    if m:
        var = m.group(1).strip()
        range_expr = m.group(2).strip().replace("..", " to ")
    else:
        var = ""
        range_expr = for_args.replace("..", " to ")

    body, i = _parse_instructions(lines, i + 1)

    # Consume !next
    if i < len(lines) and lines[i].strip().startswith("!next"):
        i += 1

    return ForLoop(var=var, range_expr=range_expr, body=body), i
