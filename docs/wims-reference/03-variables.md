# 03 — Variables and Substitution

This document describes the seven variable types, how they are stored, how their definitions are compiled to WIMS runtime directives, and how variable references are substituted at compile and runtime.

---

## The Seven Variable Types

Defined as an enum in `WIMS/src/OefMsg2wims/sp.h:37`:

```c
enum {pt_int, pt_rat, pt_real, pt_complex, pt_func, pt_text, pt_matrix};
```

| Constant | OEF directive | Description |
|---|---|---|
| `pt_int` | `\integer` / `\int` | Integer; expression rounded with `rint()` |
| `pt_rat` | `\rational` | Rational number; stored as a PARI/GP fraction |
| `pt_real` | `\real` / `\parameter` / `\variable` | Floating-point real |
| `pt_complex` | `\complex` | Complex number; `I` is mapped to `i` |
| `pt_func` | `\function` | Symbolic function expression (rawmath) |
| `pt_text` | `\text` | Literal text string |
| `pt_matrix` | `\matrix` | Matrix; rows/columns separated by `;` |

---

## Variable Slot Allocation

Each variable is assigned an integer slot index `n` starting from 6 (`start_varcnt = 6`, `WIMS/src/OefMsg2wims/oef2wims.c:440`). At runtime, the slot is the WIMS variable `val$n`.

### Reserved slots (1–5)

Slots 1–5 are hardwired at the top of every `.def` file (`WIMS/src/OefMsg2wims/oef2wims.c:357-361`):

```
val1=$imagedir
val2=$confparm1
val3=$confparm2
val4=$confparm3
val5=$confparm4
```

These are initialised at the start of every request. `val1` holds the image directory URL; `val2`–`val5` hold module configuration parameters passed via the URL.

The corresponding `param[]` entries are initialised in `main()` (`WIMS/src/OefMsg2wims/oef2wims.c:435-439`):
```c
param[1].name="imagedir"; param[1].type=pt_text;
param[2].name="confparm1"; param[2].type=pt_text;
...
```

### User variable slots (6–N)

User-defined variables are registered in `param[]` in declaration order by the `parm()` function (`WIMS/src/OefMsg2wims/process.c:439-486`). Slot indices are allocated by incrementing `varcnt` on each new variable.

The maximum number of variables is `MAX_PARAM = 1024` (`WIMS/src/OefMsg2wims/oef2wims.c:23`).

---

## How Variable Definitions are Compiled

The `parm()` function in `WIMS/src/OefMsg2wims/process.c:439-486` handles all variable types. For each definition:

1. The name is validated: must start with a letter and contain only `[a-zA-Z0-9_]`.
2. The expression in `parm[1]` is copied to `vbuf` and passed through `subst()` to expand other variable references.
3. In post-statement mode (`deftag=1`), `repsubst()` is also called to expand `\reply`, `\result`, `\choice`, `\step` references.
4. If the expression contains a ternary `?:` pattern (`condition ? trueval : falseval`), a `!ifval`/`!else`/`!endif` block is emitted.
5. Special functions in the expression are pre-compiled by `parmprep()` (see [expressions](04-expressions.md)).
6. The type-specific WIMS directive is emitted by `putval()`.

### `putval()` — type-to-WIMS mapping

(`WIMS/src/OefMsg2wims/process.c:402-437`)

| Type | Emitted WIMS code |
|---|---|
| `pt_int` | `val$n=$[rint(expr)]` |
| `pt_real` | `val$n=$[expr]` |
| `pt_func` | `val$n=!rawmath expr` |
| `pt_complex` | `t_=!rawmath expr` then `t_=!exec pari print($t_)` then `val$n=!mathsubst I=i in $t_` |
| `pt_matrix` | `tmp=!trim expr` then `val$n=!translate internal $\t\\\n$ to ;; in $tmp` |
| `pt_rat` | `t_=!rawmath expr` then `val$n=!exec pari print($t_)` |
| `pt_text` | `val$n=expr` (literal assignment) |

For `pt_complex` and `pt_rat`, the PARI/GP engine is used to canonicalise the result. For matrices, internal tab characters (which represent row separators after `replace_newline()`) are translated to `;;` separators.

---

## Pre-statement vs. Post-statement Variables

Variables defined before `\statement` are assigned tag 0 (pre-statement); those after are tag 1 (post-statement). The counts are reported as `prevarcnt` and `postvarcnt` in the `.def` header.

- Pre-statement variables are computed once when the exercise is loaded (`cmd=new`).
- Post-statement variables (tag 1) are computed after the answer is submitted, in the `:postdef` section emitted at the end of the `.def` (`WIMS/src/OefMsg2wims/oef2wims.c:389-391`). This lets post-statement variables depend on `\reply` and `\result`.

---

## Variable Substitution

### Compile-time substitution in argument text: `subst()`

(`WIMS/src/OefMsg2wims/oeflines.c:65-109`)

When the compiler processes argument text (e.g. the expression of a `\real` definition, the text of `\statement`), it calls `subst()`. This function:

1. Searches for `\name` sequences where `name` matches a registered variable name in `param[]`.
2. Replaces `\name` → `$val<n>` (the runtime slot reference).
3. Replaces `\name[expr]` → `$(val<n>[expr])` (indexed access).
4. Replaces unknown `\name` → `$m_name` (module variable reference).
5. Escapes bare `$` to `&#36;` to prevent WIMS substitution of literal dollar signs.
6. Escapes `!` followed by alphanumeric to `&#33;`.

Variable lookup is done in reverse order (`for(i=varcnt-1; i>=1; …)`) so the most recently defined variable shadows earlier ones with the same name.

### Marking variables as needing save: `param[i].save`

When `subst()` processes text in post-statement mode (`deftag=1`), it sets `param[i].save=1` for each variable it resolves (`WIMS/src/OefMsg2wims/oeflines.c:90`). At the end of compilation, the `vsavelist` in the `:stat` section lists all save-flagged slots (`WIMS/src/OefMsg2wims/oef2wims.c:396-403`). At runtime, the WIMS session machinery stores these values across the `cmd=new` → `cmd=reply` transition so that `\result`, `\reply`, and feedback can reference the original values.

### Runtime substitution in text sections

For text with `\` references that must be resolved at runtime (detected by the presence of `\` in the substituted text), the compiler sets `ex_statement > 0` and emits:
```
question=__EXECUTED_1692754_EXERCISE__
```
then writes the actual text in the `:question` execution section where `out_exec()` handles `\(`, `\varname` → `$m_name`, and embedded directives (`WIMS/src/OefMsg2wims/process.c:108-126`).

---

## Substitution Syntax Summary

| Syntax | Context | Meaning |
|---|---|---|
| `\varname` | OEF source | Reference to variable `varname` |
| `\varname[n]` | OEF source | n-th item of list variable `varname` |
| `\(expr)` | Text content | Math expression; rendered via `!insmath` |
| `\(expr\)` | Text content | Alternative close form for math mode |
| `\{expr}` | Text content | Another alternative for math mode |
| `$val<n>` | `.def` script | WIMS runtime slot reference |
| `$(val<n>[expr])` | `.def` script | Indexed runtime slot reference |
| `$m_name` | `.def` script | Module variable reference |
| `$[expr]` | `.def` script | WIMS arithmetic evaluation |

---

## Scope

All variables in an OEF exercise are global — there is no lexical scoping. A `\for` loop variable is registered in `param[]` with its own slot and persists after the loop. Variable names must be unique; if the same name is declared twice, the second declaration gets the same slot (lookup finds the existing entry; `WIMS/src/OefMsg2wims/process.c:455`).

---

## See Also

- [Expressions](04-expressions.md)
- [Control flow](05-control-flow.md)
- [Lexer/parser](02-lexer-parser.md)
