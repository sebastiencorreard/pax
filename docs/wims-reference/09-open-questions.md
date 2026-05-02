# 09 — Open Questions and Ambiguities

This document records aspects of the WIMS OEF system that were unclear, contradictory, or not fully documented in the source files examined. Each item follows the format: context, what the source shows, what is unclear, and where to look next.

---

## Q1: Exact seed assignment mechanism for `cmd=new`

**Context:** Understanding how a fresh random seed is generated and stored when a student requests a new exercise instance.

**What the source shows:** `var.proc` handles the case where `seed=<value>` appears in `module_init_parm` (line 8-13), applying it with `!setseed`. `exo.init` references `$seed` in the context of counting seed attempts (`testseedscore.phtml`). The `!setseed` call itself is documented as a WIMS built-in command.

**What's unclear:** The source code for `wims.cgi` (the C CGI binary that interprets `.def` files) is not in the examined files. It is unknown exactly when and how `wims.cgi` generates and stores the initial seed for a new `cmd=new` request, and whether the seed is stored in a session file, a database, or in the URL.

**Where to look next:** `WIMS/src/wims.cgi` or the WIMS core source (likely in `WIMS/src/Clib/` or similar), specifically the `!setseed` implementation and session management.

---

## Q2: The `!rawmath` built-in — what it does

**Context:** `pt_func` variables are compiled to `val$n=!rawmath expr`. The `algexp` answer type uses `!rawmath` to parse both the correct and student answers.

**What the source shows:** `!rawmath` appears extensively in the compiled output for `pt_func`, `pt_rat`, `pt_complex` types, and in `anstype/algexp`. It is a WIMS built-in command (`!rawmath`).

**What's unclear:** The exact parsing and normalisation rules of `!rawmath` are not in the examined sources. Specifically: what CAS it uses internally, whether it calls Maxima/PARI or has its own parser, and what expression syntax it accepts.

**Where to look next:** The `rawmath` implementation is likely in `WIMS/src/rawmath.c` or a similar core file. The `WIMS/src/Clib/` directory may contain it.

---

## Q3: `\embed{}` — full semantics

**Context:** `\embed{id}` inside `\statement` places an answer field inline in the text.

**What the source shows:** `_matchit1()` in `outexec.c` (line 133-146) detects `\embed{id}` and emits `!read oef/embed.phtml id`. The `embedcnt` counter is incremented and stored in the `.def` stat section. `var.proc` checks `if $embedcnt>0` to set `hasembedding=yes`.

**What's unclear:** The exact format of the `id` argument (is it a reply number, a variable name, or free text?) and how `embed.phtml` uses it to render the appropriate form field. The file `WIMS/public_html/scripts/oef/embed.phtml` was not examined.

**Where to look next:** `WIMS/public_html/scripts/oef/embed.phtml`.

---

## Q4: `\special{}` — what kinds of specials exist

**Context:** `\special{arg1}{arg2}` is detected by `_matchit1()` in `outexec.c` (line 201) and emits `!read oef/special.phtml arg1 arg2`.

**What the source shows:** The directive exists and routes to `oef/special.phtml`. It is used in the `\statement` context.

**What's unclear:** What categories of specials exist (graphics, interactive widgets, etc.), what arguments they accept, and which are still in active use vs. deprecated.

**Where to look next:** `WIMS/public_html/scripts/oef/special.phtml` and the module help documentation.

---

## Q5: `\img{}` and `\audio{}` — exact syntax

**Context:** `_matchit2()` handles `\img{src}{alt}` and `\audio{src}{options}` inside text sections.

**What the source shows:** Both are detected and routed to `!read oef/img.phtml src alt` and `!read oef/audio.phtml src options` respectively (`WIMS/src/OefMsg2wims/outexec.c:197-198`). The second argument to `_matchit2` is optional.

**What's unclear:** The exact URL resolution for `src` (relative to what base?), and whether image paths are relative to the exercise or to the server root.

**Where to look next:** `WIMS/public_html/scripts/oef/img.phtml`.

---

## Q6: `\slib{}` inside text — format of `slib` functions

**Context:** `\slib{fn}{args}` inside `\statement` is handled by `_matchit2()` → `!read oef/slib.phtml fn args`.

**What the source shows:** This is the runtime text-section version of the `slib(fn, args)` expression function. The routing is clear.

**What's unclear:** The complete catalogue of available `slib` functions, their argument formats, and return values. The `slib/` directory was not enumerated.

**Where to look next:** `WIMS/public_html/scripts/slib/` directory and `WIMS/public_html/modules/help/oefdoc/cmd/slib.phtml`.

---

## Q7: `\mdef{}` — conditions for activation

**Context:** `\mdef{name}{value}` is a module-defined variable that is only accepted when `name` appears in the `oef2wims_mdef` environment variable.

**What the source shows:** The compiler checks `wordchr(mdef, p)` where `mdef = getenv("oef2wims_mdef")` (`WIMS/src/OefMsg2wims/oef2wims.c:426`). Only listed names are accepted.

**What's unclear:** Which modules set `oef2wims_mdef`, what names they expose, and whether there is a catalogue of standard `mdef` names.

**Where to look next:** The module build scripts and any `Makefile` or `.conf` files that set `oef2wims_mdef` before invoking the compiler.

---

## Q8: Score computation — `freepower` and `scorepower`

**Context:** The final score formula uses `freepower` and `scorepower` exponents.

**What the source shows:**
```
allgot = (freegot + qcmgot)
allgot = (allgot/alltot)^freepower * alltot
score = min(10, rint(100 * (allgot/max(1,alltot))^scorepower / 10))
```
(`WIMS/public_html/scripts/oef/var.proc:474-485`)

These powers are set from `qcmlevel` via lookup tables in `exo.init` (e.g. `freepower=!item $qcmlevel of 1,1.5,2,2.5,…`).

**What's unclear:** The pedagogical rationale for the non-linear scoring (`freepower > 1` penalises partial credit more severely at higher levels). Also unclear is whether the `precweight * precgood` contribution is documented anywhere for exercise authors.

**Where to look next:** WIMS documentation for teachers, and the `exo.init` default table.

---

## Q9: The `\draw{}{}` and `canvasdraw{}{}` directives — `$val1/` stripping

**Context:** In `_matchit3()` for `\draw`, there is special handling:
```c
case 0: while((pt=strstr(pp2,"$val1/"))!=NULL) ovlstrcpy(pt,pt+strlen("$val1/")); break;
```
(`WIMS/src/OefMsg2wims/outexec.c:100-101`)

**What the source shows:** `$val1` is `$imagedir`. In `draw` data (argument 2), occurrences of `$val1/` are stripped. In `canvasdraw` (type=0), this stripping is applied; in `draw` (type=1), it is not.

**What's unclear:** Why `canvasdraw` strips `$val1/` from its data argument while `draw` does not. This might relate to how each rendering engine resolves image paths.

**Where to look next:** `WIMS/public_html/scripts/oef/canvasdraw.phtml` and `WIMS/public_html/scripts/oef/draw.phtml`.

---

## Q10: `computeanswer=yes` — exact effect on numeric answers

**Context:** The `\computeanswer{yes}` directive and the `computeanswer` variable in `anstype/numeric`.

**What the source shows:** `p_computeanswer()` emits `computeanswer=no` if the argument is not `"yes"`, or `computeanswer=yes` if it is (`WIMS/src/OefMsg2wims/process.c:39-46`). In `anstype/numeric`, if `computeanswer!=yes`, the student's answer is rejected if it contains arithmetic operators (`+`, `-`, `*`, `^`, `(`) beyond a leading sign (`WIMS/public_html/scripts/anstype/numeric:24-31`).

**What's unclear:** Whether `computeanswer=yes` also enables full CAS evaluation (Maxima/PARI) of the student's input, or only WIMS arithmetic. The `numeric` script calls `!rawmath` and then `$[…]` but not Maxima.

**Where to look next:** The `anstype/numeric` script in full, and the WIMS `!rawmath` documentation.

---

## Q11: `\reply` vs `\answer` — any behavioural difference?

**Context:** Both `\reply` and `\answer` are listed in `directives[]` with the same handler `p_answer()`.

**What the source shows:** `WIMS/src/OefMsg2wims/oef2wims.c:61, 99` — both map to `p_answer`. They are fully identical at the compiler level.

**What's unclear:** Whether there is any runtime distinction (e.g. different rendering via `answerr.phtml` vs. a different form template). The runtime uses `ansorder=r,r,c…` where `r` marks both `\answer` and `\reply`.

**Where to look next:** `WIMS/public_html/scripts/oef/formr.phtml` and `WIMS/public_html/scripts/oef/answerr.phtml`.

---

## Q12: `\feedback{condition}{text}` — `\choice` references

**Context:** `p_feedback()` uses `cmpstr="ifval"` by default, but switches to `cmpstr="if"` when `$m_choice` is found in the condition (`WIMS/src/OefMsg2wims/process.c:661-663`).

**What the source shows:** The distinction is that choice conditions are strings (`$m_choice<n>=good`) rather than numeric values, requiring `!if` rather than `!ifval`.

**What's unclear:** The exact syntax for referencing choices in feedback conditions — specifically whether `\choice` in a feedback condition refers to the choice item text or its index.

**Where to look next:** `repsubst()` in `WIMS/src/OefMsg2wims/oeflines.c:111-142`, which replaces `\choice` with `$m_choice`.
