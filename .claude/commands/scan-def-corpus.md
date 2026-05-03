Scan the `.def` corpus for unknown commands and CAS functions, then run the regression check.

Steps:

1. List all `!cmd` commands used in `ressources/**/*.def` and compare against the known list in `docs/def-engine-commands.md`. Report any new ones.

2. List all Maxima functions passed to `!exec maxima` (via `t_=!replace...` patterns or direct calls). Check which ones are missing from `_MAXIMA_TO_SYMPY` in `backend/core/oef/def_engine.py`.

3. List all PARI expressions passed to `!exec pari`.

4. Run the regression corpus check:
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
   Baseline: OK ≥ 2162, Fail ≤ 1.

5. Run the test suite: `cd backend && pytest tests/core/oef/ -q`. Baseline: 233 tests.

6. Report: new commands found, new CAS functions found, regression delta vs baseline, and suggested next steps for each unknown item.
