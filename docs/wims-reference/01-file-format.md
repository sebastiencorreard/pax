# 01 — Structure of an OEF File

An OEF file is a plain-text source that defines one exercise: its randomised variables, the question text, the expected answers, and optional feedback. The compiler (`OefMsg2wims`) transforms it into a `.def` runtime script.

---

## Top-Level Structure

An OEF file has no mandatory sections. It is a sequence of `\directive{...}` calls, in any order, interspersed with free text (which is ignored by the compiler at the top level — all content to be displayed must appear inside `\statement{}`, `\hint{}`, etc.).

Directives are parsed by `process()` (`WIMS/src/OefMsg2wims/oef2wims.c:166-302`). The complete list of recognised directives is in the `directives[]` table (`WIMS/src/OefMsg2wims/oef2wims.c:60-116`).

---

## Complete Directive Reference

Grouped by category, with the internal type tag and argument count from `WIMS/src/OefMsg2wims/oef2wims.c:60-116`.

### Metadata Directives

| Directive | Args | Notes |
|---|---|---|
| `\title{text}` | 1 | Exercise title; truncated to 80 chars (`WIMS/src/OefMsg2wims/oef2wims.c:20`) |
| `\title_fr{text}` | 1 | French title (also `_en`, `_nl`, `_de`, `_it`, `_es`, `_ca`, `_cn`, `_si`) |
| `\author{name}` | 1 | Author name; output as `author=name` in `.def` |
| `\email{addr}` | 1 | Author email; output as `email=addr` |
| `\keywords{words}` | 1 | Keywords; output as `keywords=words` |
| `\language{code}` | 1 | Exercise language; only stored when exactly 2 chars (`WIMS/src/OefMsg2wims/process.c:101-106`) |
| `\range{a..b}` | 1 | Numeric range for the exercise; stored as `leftrange` / `rightrange` (`WIMS/src/OefMsg2wims/process.c:89-99`) |
| `\precision{n}` | 1 | Default numeric precision (0–100000000) (`WIMS/src/OefMsg2wims/process.c:48-54`) |
| `\computeanswer{yes|no}` | 1 | Whether to allow computed expressions in numeric answers (`WIMS/src/OefMsg2wims/process.c:39-46`) |
| `\description{text}` | 1 | Exercise description; stored as `oefdescription` |
| `\observation{text}` | 1 | Observation (shown to teachers); stored as `oefobservation` |
| `\css{text}` | 1 | CSS injected into the page header; stored as `oefcss` |
| `\credits{name}{value}` | 2 | Attribution credits |
| `\format{html|tex}` | 1 | Output format (default `html`) |

### Variable Definition Directives

All variable directives accept the form `\type{name}{expression}` or the shorthand `\type{name=expression}` (the compiler splits on `=` when the second argument is empty; `WIMS/src/OefMsg2wims/oef2wims.c:267-272`).

| Directive | Type constant | Compiled to |
|---|---|---|
| `\integer{name}{expr}` | `pt_int` | `val$n=$[rint(expr)]` |
| `\int{name}{expr}` | `pt_int` | same as `\integer` |
| `\real{name}{expr}` | `pt_real` | `val$n=$[expr]` |
| `\rational{name}{expr}` | `pt_rat` | `t_=!rawmath expr` then `val$n=!exec pari print($t_)` |
| `\complex{name}{expr}` | `pt_complex` | via `!rawmath` + `!exec pari` + `!mathsubst I=i` |
| `\function{name}{expr}` | `pt_func` | `val$n=!rawmath expr` |
| `\text{name}{expr}` | `pt_text` | `val$n=expr` (literal) |
| `\matrix{name}{expr}` | `pt_matrix` | `tmp=!trim expr` then `val$n=!translate internal … to ;; in $tmp` |
| `\parameter{name}{expr}` | `pt_real` | same as `\real` (alias) |
| `\variable{name}{expr}` | `pt_real` | same as `\real` (alias) |

Source: `WIMS/src/OefMsg2wims/process.c:402-437` (`putval` function) and `WIMS/src/OefMsg2wims/oef2wims.c:60-116`.

### Statement Directives

| Directive | Notes |
|---|---|
| `\statement{text}` | Main question body. Compiled to `question=` in the `.def`. If content contains variable references (`\`), a sentinel is used and an `:question` section is emitted for runtime rendering (`WIMS/src/OefMsg2wims/process.c:108-126`). Only one `\statement` allowed per exercise. |
| `\instruction{text}` | Not in the compiler's directive table — use `\statement`. |
| `\consigne{text}` | Not in the compiler's directive table — use `\statement`. |
| `\embed{id}` | Inside `\statement`, embeds an answer field inline. Detected by `_matchit1()` in `out_exec()` (`WIMS/src/OefMsg2wims/outexec.c:200`). |
| `\wims{assignment}` | Raw WIMS directive (only `key=value` form without `!` is accepted; `WIMS/src/OefMsg2wims/process.c:68-76`). |

### Answer Directives

| Directive | Args | Notes |
|---|---|---|
| `\answer{prompt}{expected}{type=T}{option=O}{weight=W}` | up to 5 | Free-answer field. Arguments after the first two may appear in any order as `key=value` pairs. Source: `WIMS/src/OefMsg2wims/process.c:227-352`. |
| `\reply{…}` | same | Synonym for `\answer` (`WIMS/src/OefMsg2wims/oef2wims.c:99`). |
| `\choice{prompt}{correct}{wrong1,wrong2,...}{option=O}{weight=W}` | up to 5 | Multiple-choice field. Compiled to `choicename`, `choicegood`, `choicebad`. Source: `WIMS/src/OefMsg2wims/process.c:354-400`. |

### Feedback Directives

| Directive | Args | Notes |
|---|---|---|
| `\hint{text}` | 1 | Hint shown on request. Compiled to `hint=` in `.def`. |
| `\help{text}` | 1 | Longer help text. Compiled to `help=` in `.def`. |
| `\solution{text}` | 1 | Shown after reply. Compiled to `solution=` in `.def`. |
| `\feedback{condition}{text}` | 2 | Conditional feedback shown after answer. Compiled to `!ifval` block in `:feedback` section (`WIMS/src/OefMsg2wims/process.c:653-666`). |
| `\condition{label}{expr}` | up to 4 | Cross-answer condition. Compiled to `condtest$n` in `:test` section. |
| `\conditions{expr}` | 1 | Global condition expression referencing multiple conditions. |
| `\latex{text}` | 1 | LaTeX-renderable text block. |

### Control Flow Directives

| Directive | Notes |
|---|---|
| `\if{condition}` | Compiles to `!if <condition>`. Closing is auto-detected: the body is enclosed by `{…}` and the matching `}` is replaced by the `endifchar` sentinel (`\002`). (`WIMS/src/OefMsg2wims/oef2wims.c:248-256`). |
| `\else{…}` | Optional else branch inside `\if`. Detected by `elsechar` sentinel (`\001`). |
| `\endif` | Explicit end of `\if` — also emitted automatically by the sentinel. |
| `\ifval{condition}` | Like `\if` but compiles to `!ifval` (numeric comparison). |
| `\for{var=start..end}` | Loop; compiles to `!for val$n start..end`. (`WIMS/src/OefMsg2wims/process.c:540-562`). |
| `\for{var=item1,item2}` | Loop over a list. |
| `\next` | End of `\for` body. |
| `\while{condition}` | Compiles to `!while <condition>`. (`WIMS/src/OefMsg2wims/process.c:526-533`). |
| `\endwhile` | End of `\while` body. |

### Other Directives

| Directive | Notes |
|---|---|
| `\special{arg1}{arg2}` | Passes control to a special rendering phtml. Detected in `out_exec()` by `_matchit1()` (`WIMS/src/OefMsg2wims/outexec.c:201`). |
| `\plot{fn}{x=range}{y=range}` | Generates a function plot; sets `plot_fn`. (`WIMS/src/OefMsg2wims/process.c:569-593`). |
| `\steps{list}` | Defines exercise steps. (`WIMS/src/OefMsg2wims/process.c:669-701`). |
| `\nextstep{list}` | Dynamic steps. Sets `dynsteps=yes` then calls `p_steps`. |
| `\mdef{name}{value}` | Module-defined variable (only accepted when `oef2wims_mdef` env var lists the name). |
| `\header{…}` | Called `p_header` in the code — handles `author`, `email`, `keywords` etc. |

---

## Syntax Rules

### Basic directive syntax
```
\directive{arg1}{arg2}{arg3}
```
Arguments are delimited by `{…}`. The compiler reads them with `find_matching()` which tracks nested braces (`WIMS/src/OefMsg2wims/oef2wims.c:214-221`).

Up to `MAX_PARM=10` arguments are read per directive (`WIMS/src/OefMsg2wims/oef2wims.h:6`).

### Name=value shorthand
When a directive takes two arguments (name and expression), the author may write:
```
\integer{n = random(1..10)}
```
The compiler splits on the first `=` when the second argument block is empty (`WIMS/src/OefMsg2wims/oef2wims.c:267-272`). A `:=` form is also handled (the `:` before `=` is stripped, `WIMS/src/OefMsg2wims/oef2wims.c:269`).

### Math mode `\(`…`)`
Inside `\statement{}` and other text content, math expressions are delimited with `\(` and `)`:
```
The value is \(2*\n + 1).
```
The compiler's `out_exec()` function searches for `\(` then finds the matching `)` (or `\)` as alternative close) to extract the formula (`WIMS/src/OefMsg2wims/outexec.c:210-219`). The formula is then passed to `process_formula()` which emits `!insmath <formula>`.

An alternative syntax `\{…\}` is also supported for math mode (`WIMS/src/OefMsg2wims/outexec.c:221-229`).

The bare `)` convention: WIMS specifically searches for `\)` as an alternative closing delimiter to `\(`, allowing authors to write `\( expr \)` as well as `\( expr )`.

### Variable references in text
Inside text directives, `\varname` is substituted to `$val<n>` by `subst()` (`WIMS/src/OefMsg2wims/oeflines.c:65-109`). Dollar signs and exclamation marks are HTML-escaped (to `&#36;` and `&#33;`) so they do not interfere with WIMS's own `$var` and `!cmd` syntax.

### Indexed access
`\varname[expr]` is compiled to `$(val<n>[expr])` where `expr` is itself substituted (`WIMS/src/OefMsg2wims/oeflines.c:92-103`).

### Comments
Lines beginning with `%%` are OEF comments and are ignored by the compiler (the `%%` prefix is a WIMS convention; single `%` can appear in TeX math).

Actually, looking at the source, the compiler does not explicitly skip `%%` lines — all characters that are not `\` or `{` are simply skipped in the main scan loop (`WIMS/src/OefMsg2wims/oef2wims.c:172`). Comments therefore work by the fact that free text outside a directive is never processed.

### Character encoding
Historically OEF files used ISO-8859-1. The compiler makes no encoding assumptions — it works byte-by-byte. Files today are generally UTF-8. The WIMS runtime normalises the encoding when rendering HTML.

---

## Annotated Example OEF File

```oef
%% Linear equation exercise
\title{Linear equations}
\author{Gang Xiao}
\language{en}

%% Variable definitions
\integer{a = randint(2..9)}
\integer{b = randint(1..20)}

%% The question text
\statement{
  Solve the equation: \(a\)·x + \(b\) = 0.
  \embed{reply1}
}

%% Expected answer: -b/a as a real number
\answer{x =}{-\b/\a}{type=numeric}{option=absolute}

%% Hint shown on request
\hint{Isolate x by subtracting \(\b\) from both sides, then divide by \(\a\).}

%% Full solution shown after answering
\solution{
  a·x = −b, so x = \(-\b/\a).
}
```

- `\integer{a = randint(2..9)}` — defines variable `a` as a random integer 2–9.
- `\statement{…\embed{reply1}}` — embeds the answer input field inline in the question.
- `\answer{x =}{-\b/\a}{type=numeric}` — the correct answer is computed from variables `b` and `a`.
- `\(a\)` — inline math: renders the value of variable `a` as a math expression.

---

## See Also

- [Lexer/parser](02-lexer-parser.md)
- [Variables](03-variables.md)
- [Answer evaluation](06-answer-evaluation.md)
