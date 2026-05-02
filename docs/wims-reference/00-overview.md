# 00 — WIMS OEF Pipeline: Global Overview

This document describes the complete processing pipeline from an HTTP request to the HTML response served to a student for an OEF (Online Exercise Format) exercise. It covers which binaries and scripts are involved, the two-phase architecture, and how the compiled `.def` script is structured.

---

## Two-Phase Architecture

OEF processing is split into two distinct phases that happen at different times:

### Phase 1 — Compile Phase (done once, offline)

The `OefMsg2wims` C binary (`WIMS/src/OefMsg2wims/oef2wims.c`) reads an `.oef` source file and produces a `.def` script file. This step is performed once when an exercise is installed or updated, not on every student request.

The binary:
1. Reads the entire `.oef` file into memory (`getinp()`, `WIMS/src/OefMsg2wims/oef2wims.c:142-163`).
2. Sanity-checks parentheses balance (`checkparentheses()`, `WIMS/src/OefMsg2wims/oeflines.c:216-249`).
3. Scans the buffer character by character, recognising `\directive{arg}` patterns and accumulating them in the `define[]` array (`process()`, `WIMS/src/OefMsg2wims/oef2wims.c:166-302`).
4. Writes a `.def` script using WIMS internal syntax (`output()`, `WIMS/src/OefMsg2wims/oef2wims.c:317-405`).

The compiler version string is `3.22` (`WIMS/src/OefMsg2wims/oef2wims.c:27`).

### Phase 2 — Runtime Phase (every HTTP request)

When a student loads or submits an exercise, `wims.cgi` interprets the `.def` script. The runtime entry point for OEF exercises is `WIMS/public_html/scripts/oef/var.proc`, which:
1. Reads the `.def` file to instantiate variables with random values.
2. Renders the question HTML (via `form.phtml`).
3. On submission: evaluates the student answer against the correct value (via `ans.proc` → `anstype/<type>`).
4. Computes and stores the score.

---

## Data Flow Diagram

```
 Author writes exercise
         |
         v
  .oef source file
  (text, UTF-8 or ISO-8859-1)
         |
         v
  ┌─────────────────────────────────────┐
  │  OefMsg2wims compiler               │
  │  (WIMS/src/OefMsg2wims/oef2wims)    │
  │                                     │
  │  1. getinp()   – read .oef into RAM │
  │  2. process()  – parse directives   │
  │     into define[] array             │
  │  3. output()   – emit .def script   │
  └─────────────────────────────────────┘
         |
         v
  .def script file
  (WIMS internal language: !set, !if,
   !for, !while, !exec, $[...], ...)
         |
    (stored on disk, read per request)
         |
         v
  HTTP request from student browser
         |
         v
  ┌─────────────────────────────────────┐
  │  wims.cgi  (CGI process)            │
  │                                     │
  │  Reads proc=oef from session;       │
  │  dispatches to                      │
  │  scripts/oef/var.proc               │
  └─────────────────────────────────────┘
         |
         |─── cmd=new / renew ──────────────┐
         |                                  v
         |                     Read .def    │
         |                     Instantiate  │
         |                     val1..valN   │
         |                     (random)     │
         |                          │
         |                          v
         |                    Render question HTML
         |                    (Main.phtml +
         |                     form.phtml)
         |                          │
         |                          v
         |                   Student browser
         |
         |─── cmd=reply ────────────────────┐
                                            v
                               Re-read .def (restore vars)
                               For each answer i:
                                 !readproc anstype/<type>
                                 → diareply$i = good|bad
                               Compute score
                               Render answer.phtml
                                            │
                                            v
                                     Student browser
```

---

## The `.def` Script Structure

The compiler's `output()` function (`WIMS/src/OefMsg2wims/oef2wims.c:317-405`) writes the `.def` in this fixed order:

### Header section
```
!set title=<exercise title>
!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!endif
oef2wims_version=3.22
<author>, <email>, <keywords>, <language>, etc.
ansorder=r,r,c,...    (r=reply, c=choice, in declaration order)
varcnt=N
prevarcnt=N
postvarcnt=N
replycnt=N
choicecnt=N
conditioncnt=N
feedbackcnt=N
format=html
val1=$imagedir
val2=$confparm1
val3=$confparm2
val4=$confparm3
val5=$confparm4
!if $testcondition=yes
 !goto test
!endif
!if $status=waiting
 !exit
!endif
```

### Variable definitions (tag 0 — pre-statement variables)
All `\integer`, `\real`, `\rational`, `\complex`, `\text`, `\function`, `\matrix` definitions compiled to `val6=...`, `val7=...`, etc.

### Answer/choice metadata
```
replytype1=numeric
replyname1=<prompt>
replygood1=$[<value>]
replytype2=algexp
replyname2=<prompt>
replygood2=<expr>
...
choicename1=<prompt>
choicegood1=<good items>
choicebad1=<bad items>
```

### Statement, hint, help, solution, latex (tag 1 — post-statement content)
```
question=__EXECUTED_1692754_EXERCISE__
hint=<text or __EXECUTED__>
help=<text or __EXECUTED__>
solution=<text or __EXECUTED__>
latex=...
```
If the content contains variable substitutions (detected by `\` in the text), the compiler writes the sentinel `__EXECUTED_1692754_EXERCISE__` as the value and emits the real content in an `:executed` section below, where WIMS `!insmath` and `$(var)` substitutions are applied at runtime (`WIMS/src/OefMsg2wims/outexec.c:149-232`).

### Jump to stat section
```
!goto stat
```

### Executed content sections
Named labels `question`, `hint`, `help`, `solution` where the phtml-style content (with `\(`, `\var`, `\embed{}`, etc.) is rendered at runtime.

### Post-definition section (optional)
```
!exit

:postdef
val<N>=...   (post-statement variables, when postvarcnt>0)
```

### Feedback section
```
!exit

:feedback
!ifval <condition>
 <feedback HTML>
!endif
```

### Condition-test section
```
!exit

:test
<condition evaluation code>
```

### Stat section
```
!exit

:stat
vsavelist=<comma-separated val indices>
embedcnt=N
```

The `vsavelist` records which `val` slots must be saved in the session so that `\result` and `\reply` references work in feedback and solution sections (`WIMS/src/OefMsg2wims/oef2wims.c:396-403`).

---

## Key Binaries and Scripts

| Component | Path | Role |
|---|---|---|
| OEF compiler | `WIMS/src/OefMsg2wims/oef2wims.c` | Translates `.oef` → `.def` |
| Runtime entry | `WIMS/public_html/scripts/oef/var.proc` | Orchestrates every request |
| Question form | `WIMS/public_html/scripts/oef/form.phtml` | Renders input form |
| Answer display | `WIMS/public_html/scripts/oef/answer.phtml` | Renders post-submission analysis |
| Reply-type routing | `WIMS/public_html/scripts/oef/replytype.proc` | Maps type names to scripts |
| Answer evaluators | `WIMS/public_html/scripts/anstype/<type>` | One file per answer type |

---

## See Also

- [File format](01-file-format.md)
- [Lexer/parser](02-lexer-parser.md)
- [Variables](03-variables.md)
- [Answer evaluation](06-answer-evaluation.md)
