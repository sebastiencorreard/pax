# 07 — Randomness and Reproducibility

This document describes how the random seed is initialised, how random functions in OEF expressions are compiled and executed, and how reproducible exercise instances are produced.

---

## Seed Origin

The WIMS runtime uses a per-exercise-instance seed (`$seed`) to make random values reproducible across page loads of the same exercise version.

### Seed from URL parameter

At the start of `var.proc` (`WIMS/public_html/scripts/oef/var.proc:8-13`):

```
!read getparm $module_init_parm seed
!if $get_seed!=$empty
  !setseed $get_seed
  module_init_parm=!replace internal seed=$get_seed by in $module_init_parm
  !reset get_seed
!endif
```

If the URL contains a `seed=<value>` parameter (embedded in `module_init_parm`), it is extracted with `!read getparm` and applied immediately with `!setseed`. The seed is then stripped from `module_init_parm` so it does not propagate further.

This means: loading an exercise URL with `seed=12345` will always produce the same random values.

### Seed from session (`cmd=new`)

When a student requests a new exercise instance (`cmd=new` or `cmd=renew`), the seed is assigned by the WIMS core. The session records the seed so that subsequent page loads (`cmd=reply`, `cmd=hint`) restore the same random values.

The seed-to-score mapping is tracked by `testseedscore.phtml` (`WIMS/public_html/scripts/oef/testseedscore.phtml`), which records how many distinct seeds (`seedcnt`) and how many attempts on the current seed (`seedlastcnt`) the student has used. This drives the `givesol`, `givefeed`, `givehint` policies.

### Supervisor/development mode

Comments in `var.proc` lines 14-16 show a disabled mechanism (`!!wseed=`, `!!!if …`) that would allow the supervisor to force a specific seed. This code is commented out.

---

## How `random(a..b)` is Compiled

`sp_random()` (`WIMS/src/OefMsg2wims/sp.c:193-210`) handles `random(a..b)`, `randint(a..b)`, `randitem(list)`:

```c
if(*p2==',') pr="randitem";
else {
  if(*p2=='.') {
    *p2=','; *(p2+1)=' ';     // replace .. with ,
  }
  if(ptype==pt_int) pr="randint"; else pr="random";
}
fprintf(outf,"%stmp%d=!%s %s\n\n", setpre,prepcnt,pr,buf);
```

The OEF expression is compiled to one of three WIMS runtime commands:

| OEF expression | Variable type | Compiled to |
|---|---|---|
| `random(a..b)` | `pt_real` | `!random a,b` |
| `random(a..b)` | `pt_int` | `!randint a,b` |
| `randint(a..b)` | any | `!randint a,b` (always integer) |
| `random(x,y,z)` | any | `!randitem x,y,z` |

The `..` to `,` conversion happens in-place in the buffer (`WIMS/src/OefMsg2wims/sp.c:204-205`).

---

## `shuffle(list)` — Reproducible Shuffle

`sp_shuffle()` (`WIMS/src/OefMsg2wims/sp.c:177-180`) compiles to:
```
tmp<n>=!shuffle <list>
```

`!shuffle` is a WIMS built-in that returns a shuffled copy of the list. When called with the same seed, it always returns the same permutation. The shuffle is seeded by the session seed.

### Exercise shuffling

At the exercise-set level, the list of exercises is shuffled in `exo.init`:
```
shuffle=!shuffle $nn
shufflelist=!item $shuffle of $exo
```
(`WIMS/public_html/scripts/oef/exo.init:17-18`)

This determines which exercise in a set is shown for each attempt. Since the shuffle is seeded, the same student session always encounters the exercises in the same order.

---

## `randitem(list)` — Random Item Selection

`sp_randitem()` (`WIMS/src/OefMsg2wims/sp.c:233-237`) compiles to:
```
tmp=!nonempty items <list>
tmp<n>=!randitem $tmp
```

The `!nonempty items` step filters out empty items from the list before selecting randomly.

`randomitem` is an alias for `randitem` and routes to the same handler.

---

## Reproducibility: Same Seed → Same Instance

The WIMS `!setseed` command initialises the pseudo-random number generator. All subsequent `!random`, `!randint`, `!randitem`, `!shuffle` calls draw from this seeded sequence in deterministic order.

Because the `.def` script always computes variables in the same order (output by the compiler in `output()`: `_out(t_def)` → variables in declaration order, `WIMS/src/OefMsg2wims/oef2wims.c:369-370`), the same seed always produces the same `val6`, `val7`, … values.

The seed is stored in the student session. When `status=waiting` (exercise already loaded, awaiting reply), `var.proc` re-reads the `.def` file without calling `!setseed` again — but the session state has already been restored by the WIMS core, so `val<n>` values are recovered from the session store (`vsavelist`) rather than recomputed.

---

## Seed Storage and Transmission

1. **Session store**: The WIMS session records the seed when assigned. The OEF module reads it back on every request.
2. **`vsavelist`**: The compiler emits `vsavelist=<n1>,<n2>,…` at the end of the `.def` (`WIMS/src/OefMsg2wims/oef2wims.c:396-403`). This tells WIMS which `val<n>` slots to save in the session for restoration on `status=waiting` requests.
3. **URL**: The seed can be embedded in the URL as `seed=<value>` in `module_init_parm`. This allows links to specific exercise instances (used by teachers and in shared exercise links).

---

## Precision Settings for Random Functions

`var.proc` sets defaults for CAS precision used in expression evaluation:

```
!default pari_precision=18
!default print_precision=8
!default maxima_precision=$print_precision
```
(`WIMS/public_html/scripts/oef/var.proc:72-75`)

These affect how `pari(...)`, `maxima(...)`, etc. format their results, which in turn affects how random rational/complex values are represented.

---

## See Also

- [Variables](03-variables.md)
- [Expressions](04-expressions.md)
- [Open questions](09-open-questions.md)
