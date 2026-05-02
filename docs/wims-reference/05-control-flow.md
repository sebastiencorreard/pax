# 05 — Conditions and Loops

This document describes how `\if`, `\ifval`, `\for`, `\while`, and the ternary `?:` operator work in OEF, including exact syntax, how conditions are evaluated, and nesting rules.

---

## `\if{condition}…[\else{…}]\endif`

### Syntax
```oef
\if{condition}{
  true branch
}
\if{condition}{
  true branch
}{\else
  false branch
}
```

The braces after the condition are mandatory for the true branch. The `\else` block is optional and is enclosed in a second `{…}` block.

### How the compiler processes it

`p_if()` calls `_p_if(p, 0)` (`WIMS/src/OefMsg2wims/process.c:512`), which:
1. Copies the condition to `vbuf` and calls `subst()` to expand variable references.
2. If in post-statement context, also calls `repsubst()` to expand `\reply`, `\result` etc.
3. Calls `parmprep()` to pre-compile any special functions in the condition.
4. Emits `!if <condition>`.

The body braces are handled earlier by `process()` during the parse phase: the closing `}` of the true branch is replaced by `elsechar` (if a second `{` follows) or `endifchar` (`WIMS/src/OefMsg2wims/oef2wims.c:248-256`).

### Compiled output
```
!if <condition>
  <true branch>
!else          ← only if \else present
  <false branch>
!endif
```

### Condition evaluation

Conditions are evaluated by the WIMS `!if` command, which tests whether the condition string is non-empty and not equal to `$empty`. String comparisons use the WIMS `=` / `!=` operators. Complex comparisons are supported with `and`/`&&`, `or`/`||`, and relation keywords (see below).

---

## `\ifval{condition}…[\else{…}]\endif`

`\ifval` is identical to `\if` in syntax, but compiles to WIMS's `!ifval` command instead of `!if`. The `!ifval` command performs numeric comparison.

Handler: `p_ifval()` → `_p_if(p, 1)` (`WIMS/src/OefMsg2wims/process.c:513`).

Compiled output:
```
!ifval <condition>
  <true branch>
!endif
```

---

## Condition Expression Syntax

Condition syntax is validated (not evaluated) by `check_compare()` / `_check_compare()` (`WIMS/src/OefMsg2wims/compare.c:128-136`).

### Relational operators
- Numeric: `<`, `<=`, `>`, `>=`, `=`, `==`, `!=`, `<>`
- String-relational keywords (preceded by `is` or `not`):

| Keyword | Meaning |
|---|---|
| `sametext` | case-insensitive string equality |
| `samecase` | case-sensitive string equality |
| `in` | substring test |
| `wordof` | value is a word of a space-separated list |
| `itemof` | value is an item of a comma-separated list |
| `lineof` | value is a line of a newline-separated list |
| `varof` | value is a variable name in a list |
| `variableof` | alias for `varof` |

Defined in `WIMS/src/OefMsg2wims/compare.c:20-23`:
```c
char *relation_type[]={
  "sametext","samecase",
  "in",  "wordof","itemof","lineof","varof","variableof"
};
```

Examples:
```oef
\if{\a is wordof 1 2 3 4 5}{ \a is small }
\if{\b not itemof \mylist}{ \b is not in the list }
```

### Logical operators (in priority order, lowest to highest)
- `or` / `||`
- `and` / `&&`
- unary comparisons (no explicit grouping operator beyond parentheses)

Nesting with parentheses is supported. `_check_compare()` recursively validates the structure (`WIMS/src/OefMsg2wims/compare.c:27-126`).

### Ternary `?:` operator

Inside variable expression values (not in `\if` but in `\real` etc.), a ternary can be written:
```oef
\real{x}{condition ? true_value : false_value}
```
Detected by `strparchr(vbuf, '?')` in `parm()` (`WIMS/src/OefMsg2wims/process.c:459`). Compiled to `!ifval`/`!else`/`!endif` blocks. For this to be recognised as a ternary rather than a `?` in text, `check_compare()` must return true (i.e., the text before `?` must be a valid condition).

---

## `\for{var=start..end}…\next`

### Syntax
```oef
\for{i=1..10}{
  body using \i
}
```

Or iterating over a list:
```oef
\for{x=item1,item2,item3}{
  body using \x
}
```

### Compilation

`p_for()` (`WIMS/src/OefMsg2wims/process.c:540-562`):
1. Extracts the loop variable name and registers it in `param[]` as `pt_real` if not already defined.
2. The range/list part (`p2` onwards) is substituted and passed through `parmprep()`.
3. Emits `!for val<n> <range>`.

The body's closing `}` was replaced by `nextchar` (`\003`) in `process()` (`WIMS/src/OefMsg2wims/oef2wims.c:260-261`). When the stored sentinel is encountered during `_out()`, it emits `!next`.

### Compiled output
```
!for val<n> 1..10
  <body>
!next
```

### Loop variable scoping
The loop variable occupies a permanent slot in `param[]` and retains its last value after the loop ends. There is no stack-based scoping.

---

## `\while{condition}…\endwhile`

### Syntax
```oef
\while{\i < 10}{
  body
}
```

### Compilation

`p_while()` (`WIMS/src/OefMsg2wims/process.c:526-533`):
1. Substitutes and pre-compiles the condition.
2. Emits `!while <condition>`.

The body `}` was replaced by `whilechar` (`\004`) during parse. Encountered during output, it emits `!endwhile`.

### Compiled output
```
!while <condition>
  <body>
!endwhile
```

---

## `\if` Inside Text Sections (`out_exec`)

When `\if`, `\ifval`, and `\for` appear inside a `\statement`, `\hint`, `\help`, or `\solution` block (i.e., processed by `out_exec()`), they use the inline form:

```
\if{condition}{true body}
\if{condition}{true body}{false body}
\for{var}{body}
```

These are handled by `exec_if()`, `exec_ifval()`, and `exec_for()` in `WIMS/src/OefMsg2wims/outexec.c:26-66`. They require both the condition and body to be in `{…}` braces (two mandatory braces). The compiled output is the same WIMS `!if`/`!for` syntax, but inline within the rendered content.

---

## Nesting Rules

- `\if` blocks may be nested to arbitrary depth. The sentinel-based approach handles this because each `}` is replaced by a sentinel only at the point where it closes the directly enclosing block.
- `\for` loops may be nested. Each loop variable gets its own slot.
- `\while` loops may be nested.
- You can nest `\if` inside `\for` and vice versa, because sentinels only close the innermost open block.
- The maximum nesting depth is limited only by `MAX_DEFINE = 1024` total entries in the `define[]` array (`WIMS/src/OefMsg2wims/oef2wims.c:24`).

---

## See Also

- [Variables](03-variables.md)
- [Expressions](04-expressions.md)
- [Answer evaluation](06-answer-evaluation.md)
