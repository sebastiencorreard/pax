# 02 — Tokenisation and Parsing

This document describes how the `OefMsg2wims` C compiler reads and tokenises an OEF source file, how directives are recognised, how arguments are extracted, and how the compiler dispatches to handlers.

---

## File Reading

The entire OEF file is read into a single in-memory buffer by `getinp()` (`WIMS/src/OefMsg2wims/oef2wims.c:142-163`):

1. The file is opened and its size is checked. The maximum accepted size is `MAX_FLEN = 199999` bytes (`WIMS/src/OefMsg2wims/oef2wims.c:25`).
2. The entire file is `fread` into `inpbuf`.
3. A sanitisation pass replaces CR (`\r`, ASCII 13) and any byte in the range 0–6 (except the four sentinel characters defined below) with a space (`WIMS/src/OefMsg2wims/oef2wims.c:160-162`). This keeps the buffer safe for C string operations.

The compiler never processes the file line by line — it operates on the flat buffer. Despite the file being called `oeflines.c`, that module contains string-level helpers, not a line-by-line reader.

---

## Sentinel Characters

Four control characters are used internally as low-level tokens, injected into the buffer during parsing to encode structure:

| Constant | Value | Meaning |
|---|---|---|
| `elsechar` | `\001` | `\else` body start |
| `endifchar` | `\002` | `\endif` / close of `\if` body |
| `nextchar` | `\003` | `\next` / close of `\for` body |
| `whilechar` | `\004` | `\endwhile` / close of `\while` body |

Defined in `WIMS/src/OefMsg2wims/oef2wims.h:8-11` and `WIMS/src/OefMsg2wims/msg2wims.h:1-4`.

---

## Parenthesis Balance Check

Before the main parse, `checkparentheses(inpbuf, 1)` is called (`WIMS/src/OefMsg2wims/oef2wims.c:431`). This performs a strong check: it walks the entire buffer and verifies that every `(`, `[`, `{` has a matching closing delimiter and that no closing delimiter appears without an opener (`WIMS/src/OefMsg2wims/oeflines.c:216-249`). On failure, it calls `oef_error()` with a pointer to the offending character, printing the line and column number.

The internal `find_matching2()` function (`WIMS/src/OefMsg2wims/oeflines.c:150-210`) handles nested pairs for `()`, `[]`, `{}`, and the special `|…|` delimiter.

---

## Main Parse Loop (`process()`)

`process()` (`WIMS/src/OefMsg2wims/oef2wims.c:166-302`) is the main scanner. It iterates over `inpbuf` one character at a time looking for:

### 1. Sentinel characters (bytes 1–4)
When a sentinel is encountered, it is looked up in the `directives[]` table by name (`"else"`, `"endif"`, `"next"`, `"endwhile"`) and appended to the `define[]` array. No argument extraction is done (`WIMS/src/OefMsg2wims/oef2wims.c:173-183`).

### 2. `{` — skip already-matched brace blocks
When the scanner hits `{`, it calls `find_matching(p+1, '}')` and advances past the block. This prevents false-positive directive detection inside brace content (`WIMS/src/OefMsg2wims/oef2wims.c:185-187`).

### 3. `\name{` — directive detection
When the scanner hits `\`, it reads the name (`[a-zA-Z0-9_]+`) up to the first non-alphanumeric/underscore character (`pe`). It then skips whitespace to find `pp = find_word_start(pe)`.

If `*pp != '{'`, the name is not a directive call (it is a variable reference in text — but at this level the text is not yet being interpreted, so it is just skipped).

If `*pp == '{'`, the name is looked up with `search_list()` in the sorted `directives[]` table (`WIMS/src/OefMsg2wims/oef2wims.c:197`). This is a binary search (`libwims.h: search_list`).

**Unknown directive with `mdef` match:** if the name is not in `directives[]` but appears in the `oef2wims_mdef` environment variable, it is stored as a `mdef` directive (`WIMS/src/OefMsg2wims/oef2wims.c:199-209`).

**Unknown directive:** the brace argument is skipped with `find_matching()` and the directive is ignored silently.

---

## Argument Extraction

For a recognised directive with `parmcnt = N`, the compiler extracts up to `N` brace-argument blocks:

```
for(j=0; j<N; j++, pp=find_word_start(pe+1)) {
    if(j>0 && *pp!='{') break;  // subsequent args are optional
    pe = find_matching(pp+1, '}');
    *pe = 0;                    // NUL-terminate the argument
    replace_newline(pp+1);      // convert \n to \t in arg text
    define[define_no].parm[j] = pp+1;
}
```

(`WIMS/src/OefMsg2wims/oef2wims.c:215-221`)

Key points:
- The first argument is mandatory (`{` required).
- Subsequent arguments (`j > 0`) are optional — if no `{` follows, extraction stops.
- Unused `parm[]` slots are set to `""` (`WIMS/src/OefMsg2wims/oef2wims.c:221`).
- `replace_newline()` replaces `\n` with `\t` and `\t` with ` ` in argument text (`WIMS/src/OefMsg2wims/oeflines.c:53-60`). This is why multiline argument content becomes tab-separated when stored.
- The buffer is modified in-place: NUL bytes are inserted at the `}` positions.

### Key=value argument parsing (`\answer`, `\choice`)
For directives like `\answer` and `\choice`, arguments may be named (`type=numeric`, `option=absolute`, `weight=2`). The handler (`p_answer`, `p_choice`) scans all 5 argument slots for `strncasecmp` matches against `"type"`, `"option"`, `"weight"` and extracts the value after `=`. Matched arguments are shifted out of the array (`WIMS/src/OefMsg2wims/process.c:237-289`).

### Name=value shorthand for variable definitions
For two-argument directives (t_def type), when `parm[1]` is empty, the compiler checks if `parm[0]` contains `=`:
```c
if(*(define[define_no].parm[1])==0 &&
   (pt=strchr(define[define_no].parm[0],'='))!=NULL) {
  if(*(pt-1)==':') *(pt-1)=0;  // strip optional ':'
  *pt=0; define[define_no].parm[1]=pt+1;
}
```
(`WIMS/src/OefMsg2wims/oef2wims.c:267-272`)

---

## Control Flow Argument Handling

The `\if`, `\ifval`, `\while`, and `\for` directives have `parmcnt < 2` in the table. After extracting the first `{…}` argument (the condition or range), the compiler looks at what follows:

For `\if` and `\ifval`:
- If a second `{` follows immediately, it is treated as the `\else` body. The second `}` is replaced by `elsechar`, and if a third `{` follows, the third `}` is replaced by `endifchar`.
- Otherwise the first `}` is replaced by `endifchar`.
(`WIMS/src/OefMsg2wims/oef2wims.c:248-256`)

For `\while`: the body `}` is replaced by `whilechar`.

For `\for`, `\function`, and other single-body directives: the `}` is replaced by `nextchar` and `varcnt` is incremented.

---

## The `define[]` Array

All parsed directives are stored in:
```c
struct {
  char *parm[MAX_PARM];   // up to 10 argument pointers
  short int type;          // index into directives[]
  short int tag;           // 0=pre-statement, 1=post-statement
} define[MAX_DEFINE];     // MAX_DEFINE = 1024
```
(`WIMS/src/OefMsg2wims/oef2wims.c:120-124`)

The `tag` field is set from `posttag`, which switches from 0 to 1 when a `\statement` directive is encountered (`WIMS/src/OefMsg2wims/oef2wims.c:282-284`). This determines whether a variable definition appears before or after `\statement` (affecting the `prevarcnt` / `postvarcnt` split).

---

## Dispatch to Handlers

The `output()` function calls `_out(type)` for each directive category in a fixed order (`WIMS/src/OefMsg2wims/oef2wims.c:370-383`):

```c
_out(t_def);       // variable definitions
_out(t_step);      // steps
_out(t_plot);      // plots
_out(t_ans);       // answer metadata
_out(t_choi);      // choice metadata
_out(t_main);      // statement
_out(t_hint);      // hint
_out(t_help);      // help
_out(t_sol);       // solution
_out(t_latex);     // latex
```

`_out(typ)` iterates the `define[]` array and calls `directives[t].processor(define[i].parm)` for each matching entry (`WIMS/src/OefMsg2wims/oef2wims.c:304-314`).

For `t_def`, only entries with the correct `tag` value are processed (pre-statement or post-statement).

---

## Variable Substitution in Argument Text

Before any output, argument text goes through `subst()` (`WIMS/src/OefMsg2wims/oeflines.c:65-109`), which:
1. HTML-escapes bare `$` → `&#36;` and `!` followed by alphanumeric → `&#33;` (preventing WIMS command injection).
2. Replaces `\varname` with `$val<n>` where `n` is the variable's slot index found by scanning `param[]`.
3. Replaces `\varname[expr]` with `$(val<n>[expr])`.
4. Replaces unknown `\name` with `$m_name` (module variable reference).

---

## `math` mode and `\(` parsing in output phase

When compiling the `\statement` body (and `\hint`, `\help`, `\solution`), `out_exec()` (`WIMS/src/OefMsg2wims/outexec.c:149-232`) performs a second scan on the already-substituted text. It handles:
- `\(…)` and `\(…\)` → `process_formula()` → `!insmath <formula>`
- `\{…}` and `\{…\}` → same as `\(`
- `\embed{id}` → `!read oef/embed.phtml id`
- `\img{src}{alt}` → `!read oef/img.phtml …`
- `\slib{fn}{args}` → `!read oef/slib.phtml …`
- `\draw{spec}{data}` → `!read oef/draw.phtml …`
- `\if{cond}{body}` inline → `!if cond` block
- `\for{var}{body}` inline → `!for …` block
- `\varname` not found in `param[]` → `$m_varname`

---

## Error Handling

`oef_error()` (`WIMS/src/OefMsg2wims/oeflines.c:25-44`) is called on any fatal parse error. It:
1. Computes the line and column number by counting `\n` characters from `inpbuf` to `badpar`.
2. Prints a formatted error with the offending character, line number, column, and surrounding context.
3. Calls `exit(1)`.

The `badpar` global pointer is set by `find_matching2()` when it detects an unmatched parenthesis (`WIMS/src/OefMsg2wims/oeflines.c:176, 199`).

---

## See Also

- [File format](01-file-format.md)
- [Variables](03-variables.md)
- [Expressions](04-expressions.md)
