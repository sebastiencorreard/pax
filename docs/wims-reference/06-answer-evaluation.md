# 06 — Answer Evaluation

This document describes how student answers are collected, routed to type-specific evaluators, graded, and how partial credit and cross-answer conditions work.

---

## The `\answer` Directive

```oef
\answer{prompt}{expected}{type=T}{option=O}{weight=W}
```

Arguments may appear in any order after the first two positional arguments (prompt and expected value). The compiler (`p_answer()` in `WIMS/src/OefMsg2wims/process.c:227-352`) parses all five argument slots, scanning for `type=`, `option=`, and `weight=` prefixes.

### Emitted `.def` lines

For each `\answer`, the compiler emits:
```
replytype<n>=<type>          ← if type= given
replyoption<n>=<opts>        ← if option= given (commas/semicolons → spaces)
replyweight<n>=<weight>      ← if weight= given
replyname<n>=<prompt>
replygood<n>=<expected>      ← or $[expected] for numeric types
```

where `<n>` is the answer sequence number (starting at 1).

### `\reply` — synonym

`\reply` is listed in `directives[]` at `WIMS/src/OefMsg2wims/oef2wims.c:99` and routes to the same `p_answer()` handler.

---

## The `\choice` Directive

```oef
\choice{prompt}{correct_item}{wrong1,wrong2,...}{option=O}{weight=W}
```

`p_choice()` (`WIMS/src/OefMsg2wims/process.c:354-400`) emits:
```
choiceoption<n>=<opts>
choiceweight<n>=<weight>
choicename<n>=<prompt>
choicegood<n>=<correct items>
choicebad<n>=<wrong items>
```

At runtime (`WIMS/public_html/scripts/oef/var.proc:397-442`), the `choice<n>` form value is compared against `choicegood<n>` to set `diachoice<n>=good|bad`.

The "I don't know" option: at runtime, choice items are numbered 1 to `choiceitems<n>+2`. Item `choiceitems<n>+1` is "none of the above" (`ch_none`); item `choiceitems<n>+2` is "I don't know" (`ch_noidea`). Selecting "I don't know" (`choiceitems<n>+2`) with an empty `choicegood<n>` is scored as correct (`WIMS/public_html/scripts/oef/var.proc:417-420`).

---

## Complete List of Answer Types

The `anstype[]` table in `WIMS/src/OefMsg2wims/process.c:169-223` maps OEF type names to internal type constants and canonical `.def` names. The `.def` canonical name is used by `replytype.proc` at runtime to load `anstype/<type>`.

### Type mapping table (from `anstype[]`, `WIMS/src/OefMsg2wims/process.c:173-223`)

| OEF name | Internal type | Canonical `.def` name | Evaluator script |
|---|---|---|---|
| `numeric`, `number` | `typ_num` | `numeric` | `anstype/numeric` |
| `algexp`, `expalg`, `numexp` | `typ_algexp` | `algexp` (or `numexp`) | `anstype/algexp` |
| `atext`, `chset` | `typ_atext` | `atext` | `anstype/atext` |
| `case`, `text` | `typ_case` | `case` | `anstype/case` |
| `nocase` | `typ_nocase` | `nocase` | `anstype/nocase` |
| `radio`, `menu`, `select`, `click`, `link`, `mark`, `checkbox` | `typ_menu` | `radio` / `menu` / `checkbox` | `anstype/<name>` |
| `formal` | `typ_formal` | `formal` | `anstype/formal` |
| `fset`, `aset`, `set` | `typ_set` | `fset` / `aset` | `anstype/fset` |
| `function`, `range`, `ranges` | `typ_func` | `function` / `range` | `anstype/function` |
| `matrix` | `typ_matrix` | `matrix` | `anstype/matrix` |
| `vector` | `typ_vector` | `vector` | `anstype/vector` |
| `equation` | `typ_equation` | `equation` | `anstype/equation` |
| `coord`, `coordinates` | `typ_coord` | `coord` | `anstype/coord` |
| `clickfill` | `typ_fill` | `clickfill` | `anstype/clickfill` |
| `dragfill` | `typ_fill` | `dragfill` | `anstype/dragfill` |
| `wlist` | `typ_wlist` | `wlist` | `anstype/wlist` |
| `compose`, `corresp`, `correspond`, `reorder`, `imgcomp`, `textcomp`, `wordcomp` | `typ_comp` | `correspond` / `reorder` etc. | various |
| `litexp` | `typ_litexp` | `litexp` | `anstype/litexp` |
| `symtext` | `typ_symtext` | `symtext` | `anstype/symtext` |
| `sigunits`, `unit`, `units` | `typ_units` | `sigunits` / `units` | `anstype/sigunits` |
| `chemeq` | `typ_chem` | `chemeq` | `anstype/chemeq` |
| `code` | `typ_src` | `code` | `anstype/code` |
| `javacurve` | `typ_java` | `javacurve` | `anstype/javacurve` |
| `raw` | `typ_raw` | `raw` | `anstype/raw` |
| `default` | `typ_default` | `default` | `anstype/default` |

For unrecognised types, the name is passed through variable substitution and stored as-is, allowing module-specific anstypes (`WIMS/src/OefMsg2wims/process.c:251-255`).

---

## Type-Specific Comparison Algorithms

### `numeric`

(`WIMS/public_html/scripts/anstype/numeric`)

1. Optional comma→dot normalisation (if `comma` option present).
2. `reply$i=!rawmath $(reply$i)` — parse the student's input.
3. Reject if the input contains arithmetic operators (unless `computeanswer=yes`): sets `test=NaN nocompute`.
4. `test=$[$(reply$i)]` — numeric evaluation.
5. `good=$[$(replygood$i)]` — numeric evaluation of expected answer.
6. Compute `tot=$[max(abs(test)+abs(good), 1/precision)]`.
7. Compute `diff=$[abs(test-good)]`.

**Relative comparison (default):**
```
if precision * diff <= tot → good
if sqrt(precision) * diff <= tot → precreply (near-miss)
```

**Absolute comparison (`absolute` option):**
```
if diff < 1/precision → good
if diff < 10/precision → precreply
```

The `precision` parameter defaults to 1000 if not set by `\precision{}`. A precision of 1000 means the tolerance is ~0.1%.

### `algexp`

(`WIMS/public_html/scripts/anstype/algexp`)

Algebraic expression comparison via Maxima:
1. `good=!rawmath $(replygood$i)` — parse expected answer.
2. `dd=!rawmath $(reply$i)` — parse student answer.
3. `!mathsubst I=i` — normalise imaginary unit.
4. Compute `test = good - dd` (or product of differences if multiple correct answers).
5. Call `!exec maxima print(good1); print(dd); print(ratsimp(test));`.
6. Three lines are returned: canonical form of expected, canonical form of student's answer, simplified difference.
7. `diareply$i=good` iff `ratsimp(test)=0` AND the student's answer is in the domain of the expected answer.

### `atext`

(`WIMS/public_html/scripts/anstype/atext`)

Text comparison with linguistic normalisation:
1. Normalise both expected and student answers: deaccent, lowercase, remove punctuation.
2. Apply suffix stripping via `!exec translator` with `suffix_dictionary=bases/sys/suffix.$module_language`.
3. Split the expected answer on `|` to get multiple acceptable forms.
4. Compare after normalisation: `diareply$i=good` if any form matches.
5. If `badwords` (lines 2+ of the expected answer) are given, unknown words in the student answer trigger `NaN unknownword`.

### `case` / `nocase`

Plain text matching. `case` is case-sensitive; `nocase` is case-insensitive. Both use simple string equality after trimming.

### `fset`

Formal set comparison: the student's answer is treated as an unordered comma-separated set of items. Both the student's and expected sets are sorted and compared item by item.

### `radio` / `menu` / `checkbox`

Multiple-choice types. The form field supplies the index; the runtime compares `choice$i` against `choicegood$i`. These types do not call `parmprep()` or special functions — the comparison is done by the `var.proc` loop directly (`WIMS/public_html/scripts/oef/var.proc:397-442`).

### `matrix` / `vector`

Compare matrices/vectors element by element. Typically delegate to `numeric` comparison per element.

### `clickfill` / `dragfill`

The student fills in slots by clicking/dragging items. The comparison checks whether each filled slot matches the expected item.

---

## Runtime Answer Processing Flow

`WIMS/public_html/scripts/oef/var.proc:298-395` loops over replies:

```
for i=1 to replycnt:
  r_ = trim(reply$i)
  apply default if empty
  if still empty → error=empty_data
  !read oef/ans.proc $i
  !read oef/screply.proc
  check diareply$i
```

`oef/ans.proc` reads `oef/replytype.proc` which:
1. Normalises old type aliases (e.g. `number` → `numeric`) via the `rt_names`/`rt_types` lists.
2. Checks if the type is in `rt_all` (the known set).
3. Loads `anstype/<type>.input` (for the form element definition) and `anstype/<type>` (the comparison script) (`WIMS/public_html/scripts/oef/replytype.proc`).

---

## Partial Credit and `weight=`

`freegot` is the accumulator for correct free-text answers. Each answer type increments it:
- `!advance freegot` → +1 (fully correct)
- No advance → 0 (wrong)
- Manual fractional `freegot=$[$freegot+0.5]` → partial

`precgood` accumulates answers that are "close" (within `sqrt(precision)` for numeric). At score computation:
```
freegot = condgot + freegot + gotadjust + precweight * precgood
```
(`WIMS/public_html/scripts/oef/var.proc:469`)

`replyweight<n>` adjusts the effective denominator: if weight is not 1, `weightadjust` is modified accordingly.

Final score computation:
```
allgot = (freegot + qcmgot)
score = (allgot/alltot)^freepower * 10
```
(`WIMS/public_html/scripts/oef/var.proc:480-485`)

---

## The `\condition` Directive

```oef
\condition{label}{expression}{option=O}{weight=W}
```

`p_condition()` (`WIMS/src/OefMsg2wims/process.c:596-642`) emits in the `:test` section of the `.def`:
```
!ifval <expression>
  condtest<n>=1
!else
  condtest<n>=0
!endif
condname<n>=<label>
```

At runtime, when `testcondition=yes`, the `.def` is re-read at the `:test` label, executing all condition blocks. Then `condtest<n>` values are summed with weights into `condgot` (`WIMS/public_html/scripts/oef/var.proc:447-465`).

The expression may reference `\reply` (compiled to `$m_reply<n>`) and `\result` (compiled to `$m_result<n>`).

### `\conditions{expr}`

`p_conditions()` emits `condlist=<expr>` in the `:test` section. If `condlist` is not set to `all`, only the listed condition indices are evaluated and counted (`WIMS/public_html/scripts/oef/var.proc:448-458`).

---

## `noidontknow` Option for `\choice`

When `noidontknow` is in `choiceoption<n>`, the "I don't know" item (index `choiceitems+2`) is suppressed from the rendered form. This is handled in the choice form rendering script, not in the compiler.

---

## See Also

- [Variables](03-variables.md)
- [Expressions](04-expressions.md)
- [Control flow](05-control-flow.md)
- [Open questions](09-open-questions.md)
