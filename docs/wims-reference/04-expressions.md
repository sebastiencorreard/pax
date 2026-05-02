# 04 — Expression Engine

This document describes how OEF expressions are evaluated, the complete list of built-in special functions, and how each one is compiled to WIMS runtime directives.

---

## Two Expression Contexts

### Arithmetic context (numeric types)

For `pt_int` and `pt_real` variables, the expression is wrapped in WIMS's arithmetic evaluator `$[…]`:
```
val6=$[expr]        # pt_real
val6=$[rint(expr)]  # pt_int
```

`$[…]` is WIMS's inline numeric evaluator. It understands standard C-like arithmetic (`+`, `-`, `*`, `/`, `^`, `%`), standard math functions (`sin`, `cos`, `sqrt`, `abs`, `floor`, `ceil`, `log`, `exp`, etc.), and the special functions listed below after pre-compilation by `parmprep()`.

### Symbolic/function context

For `pt_func` (`\function`), `pt_rat` (`\rational`), `pt_complex` (`\complex`), and `pt_matrix` (`\matrix`), the expression is passed to WIMS's `!rawmath` engine or to external CAS tools (Maxima, PARI/GP). See `putval()` in `WIMS/src/OefMsg2wims/process.c:402-437`.

### Text context

For `pt_text` (`\text`), the expression is stored as-is (after variable substitution by `subst()`). No numeric evaluation is performed.

---

## `parmprep()` — Special Function Pre-compilation

Before emitting a variable assignment, `parmprep()` (`WIMS/src/OefMsg2wims/sp.c:351-383`) scans the expression for function calls:

```c
if(isalpha(*pp)) {
    // read identifier into namebuf
    // if followed by '(', look up in specialfn[]
    // if found: extract args, recurse on args, call specialfn[i].processor
    // replace the call site with $(tmp<n>) where n=prepcnt++
}
```

Each special function processor emits one or more WIMS lines that compute a result into `tmp<n>`. The original function call site is replaced with `$(tmp<n>)`. Multiple nested calls produce chains of `tmp0`, `tmp1`, … variables.

The `specialfn[]` table is defined in `WIMS/src/OefMsg2wims/sp.c:306-348` (sorted alphabetically for binary search).

---

## Complete List of Special Functions

### Randomness

| OEF function | Compiled to | Notes |
|---|---|---|
| `random(a..b)` | `!random a,b` (pt_real) or `!randint a,b` (pt_int) | `..` is replaced by `, ` (`WIMS/src/OefMsg2wims/sp.c:193-209`) |
| `randint(a..b)` | `!randint a,b` | Always integer; calls `sp_pickone` → `sp_random` with `pt_int` |
| `randitem(list)` | `tmp=!nonempty items list` then `!randitem $tmp` | Random item from a comma/space list (`WIMS/src/OefMsg2wims/sp.c:233-237`) |
| `randomitem(list)` | same as `randitem` | Alias |
| `pickone(list)` | same as `randint` dispatcher | Alias for `randint` |
| `shuffle(list)` | `!shuffle list` | Reproducible shuffle; see [randomness](07-randomness.md) |

The dispatch between `!random` (real) and `!randint` (integer) is based on the `ptype` argument passed to `parmprep`, which corresponds to the OEF variable type (`WIMS/src/OefMsg2wims/sp.c:207-208`).

### List Operations

| OEF function | Compiled to | Notes |
|---|---|---|
| `item(n, list)` | `!item n of list` | Returns the n-th item; `n..m` range is converted to `n to m` (`WIMS/src/OefMsg2wims/sp.c:217-226`) |
| `items(list)` | `!itemcnt list` | Count of items in the list |
| `row(n, matrix)` | `!row n of matrix` (after translating separators) | Extracts row n from a matrix |
| `rows(matrix)` | `!rowcnt matrix` | Count of rows |
| `randrow(matrix)` | `!nonempty rows …` then `!randrow …` | Random non-empty row |
| `column(n, matrix)` | `!column n of matrix` | Extracts column n |
| `positionof(item, list)` | `!positionof item X in list` | Position of item in list |
| `position(item, list)` | same | Alias |

### CAS Backends

| OEF function | Compiled to | Notes |
|---|---|---|
| `pari(expr)` | `t_=!replace internal \( by ( in expr` then `!exec pari $t_` | Calls PARI/GP for exact arithmetic (`WIMS/src/OefMsg2wims/sp.c:123-127`) |
| `maxima(expr)` | `!exec maxima $t_` after same `\(` replacement | Calls Maxima CAS (`WIMS/src/OefMsg2wims/sp.c:111-115`) |
| `yacas(expr)` | `!exec yacas $t_` | Calls Yacas CAS (`WIMS/src/OefMsg2wims/sp.c:117-121`) |
| `simplify(expr)` | `!exec maxima fullratsimp(expr);` after translating separators and lowercasing (`WIMS/src/OefMsg2wims/sp.c:129-135`) |
| `det(matrix)` | `!exec pari matdet([$matrix])` after translating separators | Matrix determinant via PARI |
| `determinant(matrix)` | same | Alias |

### Calculus

| OEF function | Compiled to | Notes |
|---|---|---|
| `diff(expr)` | `!exec maxima diff($tmp);` after translating and lowercasing (`WIMS/src/OefMsg2wims/sp.c:63-69`) |
| `deriv(expr)` | same | Alias |
| `derivative(expr)` | same | Alias |
| `int(expr)` | Uses `!readproc slib/function/integrate` via `sp_int` (`WIMS/src/OefMsg2wims/sp.c:80-93`) | `=` becomes `,`, `..` becomes `, ` |
| `integral(expr)` | same | Alias |
| `integrate(expr)` | same | Alias |
| `solve(fn=a..b)` | `!solve fn for var = val to b` | Simple root finding |
| `evaluate(fn, x=val)` | `!mathsubst x=(val) in fn` | Numeric evaluation at a point |
| `evalue(fn, x=val)` | same | Alias |

### Math Formatting

| OEF function | Compiled to | Notes |
|---|---|---|
| `texmath(expr)` | `!texmath expr` | Converts an arithmetic expression to LaTeX notation (`WIMS/src/OefMsg2wims/sp.c:106-109`) |
| `htmlmath(expr)` | `!htmlmath expr` | Converts to HTML math notation |
| `teximg(expr)` | `!readproc oef/teximg.phtml expr` | Renders LaTeX as an image |

### Graphics

| OEF function | Compiled to | Notes |
|---|---|---|
| `draw(spec, data)` | `!readproc oef/draw.phtml spec \\\ndata` | 2D drawing |
| `drawtikz(spec, data)` | `!readproc oef/drawtikz.phtml …` | TikZ drawing |
| `canvasdraw(spec, data)` | `!readproc oef/canvasdraw.phtml …` | Canvas drawing |

### Utility

| OEF function | Compiled to | Notes |
|---|---|---|
| `asis(expr)` | `!nosubst expr` | Emits expr literally without WIMS substitution |
| `slib(fnname, args)` | `!readproc slib/<fnname> args` | Calls a WIMS shared library function (`WIMS/src/OefMsg2wims/sp.c:137-145`) |
| `wims(cmd)` | `!cmd` or literal if starts with `ins` | Raw WIMS command (`WIMS/src/OefMsg2wims/sp.c:297-304`) |
| `mathexp_cut(type, expr)` | `!exec mathexp cut type\\\nexpr` | Math expression manipulation |

---

## `pari(expr)` — Exact Arithmetic

`pari(expr)` compiles to:
```
t_=!replace internal \( by ( in <expr>
tmp<n>=!exec pari $t_
```
(`WIMS/src/OefMsg2wims/sp.c:123-127`)

The `\(` replacement normalises potential WIMS math-mode markers left in the expression. The PARI/GP engine computes the exact result. This is used for rational arithmetic and all `pt_rat` type variables.

---

## `texmath(expr)` — Expression to LaTeX

`texmath(expr)` compiles to:
```
tmp<n>=!texmath <expr>
```
(`WIMS/src/OefMsg2wims/sp.c:106-109`)

The `!texmath` WIMS built-in converts an arithmetic expression (like `3*x^2 + 1/2`) into proper LaTeX notation (e.g. `3x^{2}+\frac{1}{2}`). The exact conversion rules are implemented in the WIMS core (`wims.cgi`), not in the OEF compiler.

---

## `item(n, list)` and Matrix Access

`item(n, list)`:
```
tmp<n>=!item <n> of <list>
```
Range syntax: `item(2..5, list)` is compiled with `..` converted to ` to ` (`WIMS/src/OefMsg2wims/sp.c:224`), yielding `!item 2 to 5 of list` which returns items 2 through 5.

`row(n, matrix)` and `column(n, matrix)` first translate the matrix's internal tab-separated rows to `;`-separated format with `!translate internal`, then call `!row n of` / `!column n of` (`WIMS/src/OefMsg2wims/sp.c:253-271`).

---

## `slib(function, args)`

`slib(fn, arg1 arg2 …)` compiles to:
```
!readproc slib/<fn> arg1 arg2 …
tmp<n>=$slib_out
```
(`WIMS/src/OefMsg2wims/sp.c:137-145`)

The first comma or semicolon after the function name is replaced by a space. The function name must consist only of non-whitespace, non-comma, non-semicolon characters.

---

## `wims(...)` Built-in Functions Exposed in OEF

The `wims(cmd)` special function (`WIMS/src/OefMsg2wims/sp.c:297-304`) passes an arbitrary WIMS built-in command as an expression:
- If the cmd starts with a letter (and not `ins`), it emits `!cmd`.
- Otherwise it emits the literal value.

This allows OEF authors to call WIMS string operations directly:
```
\text{t}{wims(uppercase \myvar)}
```
compiles to:
```
tmp0=!uppercase $val6
val7=tmp0
```

---

## See Also

- [Variables](03-variables.md)
- [Control flow](05-control-flow.md)
- [Randomness](07-randomness.md)
