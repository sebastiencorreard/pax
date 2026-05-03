Scan the `.def` corpus for unknown commands and CAS functions, then run the regression check. Use this after adding new `.def` files.

## Step 1 — Find unknown `!cmd` commands

Run:
```bash
find ressources/ -name "*.def" | while read f; do
  iconv -f ISO-8859-1 -t UTF-8 "$f" 2>/dev/null
done | grep -oP "=!\K\w+" | sort | uniq -c | sort -rn
```

Compare against `docs/def-engine-commands.md`. Report any command not in that file.

## Step 2 — Find new CAS functions

Run this Python script from the repo root:

```python
import glob, re, collections

CAS_FUNC_RE = re.compile(r'\b([a-zA-Z_]\w*)\s*\(')
SKIP = {'tmp0','tmp1','tmp2','tmp','t_','val','s','m','n','x','y','z',
        'rint','round','abs','max','min','sqrt','pow','sin','cos','tan',
        'asin','acos','atan','log','exp','floor','ceil','mod','gcd','lcm'}

maxima_funcs = collections.Counter()
pari_funcs = collections.Counter()

for path in glob.glob('ressources/**/*.def', recursive=True):
    try:
        text = open(path, encoding='latin-1').read()
    except:
        continue
    lines = text.splitlines()
    t_ = ''
    for line in lines:
        line = line.strip()
        m = re.match(r't_=!replace internal .+ in (.+)', line, re.I)
        if m:
            t_ = m.group(1).strip()
        m = re.match(r'(?:tmp\d*|val\w+)=!exec maxima (.+)', line, re.I)
        if m:
            expr = m.group(1).strip()
            if '$t_' in expr and t_:
                expr = expr.replace('$t_', t_)
            for fn in CAS_FUNC_RE.findall(expr):
                if fn not in SKIP:
                    maxima_funcs[fn] += 1
            t_ = ''
        m = re.match(r'(?:tmp\d*|val\w+)=!exec pari (.+)', line, re.I)
        if m:
            expr = m.group(1).strip()
            if '$t_' in expr and t_:
                expr = expr.replace('$t_', t_)
            for fn in CAS_FUNC_RE.findall(expr):
                if fn not in SKIP:
                    pari_funcs[fn] += 1
            t_ = ''

print("MAXIMA:", maxima_funcs.most_common(20))
print("PARI:",   pari_funcs.most_common(20))
```

Compare against `docs/def-engine-cas-functions.md`. Report any function not in that file — those are new and need to be added to `_MAXIMA_TO_SYMPY` or handled in `_call_pari`.

## Step 3 — Regression check

```bash
cd backend && source .venv/bin/activate && python3 -c "
import glob
from core.oef.def_engine import load_and_render

defs = glob.glob('../ressources/**/*.def', recursive=True)
ok, fail, empty = 0, 0, 0
failures = []
for path in sorted(defs):
    if b':question' not in open(path, 'rb').read(): continue
    try:
        r = load_and_render(path, seed=42)
        if r.statement_html.strip(): ok += 1
        else: empty += 1
    except Exception as e:
        fail += 1
        failures.append((path.split('ressources/')[-1], str(e)[:60]))
total = ok + fail + empty
print(f'OK: {ok}/{total} ({ok*100//total if total else 0}%)')
print(f'Empty: {empty}, Fail: {fail}')
for n, e in failures[:10]: print(f'  FAIL {n}: {e}')
"
```

Baseline: OK ≥ 2162/2172, Fail ≤ 1.

## Step 4 — Tests

```bash
cd backend && pytest tests/core/oef/ -q
```

Baseline: 233 tests pass.

## Step 5 — Report

Summarise:
- New `!cmd` commands found (with occurrence count)
- New CAS functions found (with occurrence count and suggested SymPy/Python equivalent)
- Regression delta vs baseline
- Suggested implementation priority following `docs/def-engine-cas-functions.md`
