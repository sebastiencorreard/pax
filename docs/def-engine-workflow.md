# Workflow — Ajout de nouveaux fichiers `.def`

Guide pour intégrer de nouveaux fichiers `.def` WIMS et implémenter les commandes ou fonctions CAS qu'ils introduisent.

## Étape 1 — Scanner les nouvelles commandes `!cmd`

```bash
# Lister toutes les commandes ! dans un nouveau répertoire
grep -rh "=!" ressources/nouveau_module/def/ | \
  iconv -f ISO-8859-1 -t UTF-8 2>/dev/null | \
  grep -oP "!\K\w+" | sort | uniq -c | sort -rn
```

Comparer avec la liste dans `docs/def-engine-commands.md`. Toute commande absente est nouvelle.

> **Encodage** : les `.def` sont en ISO-8859-1 — toujours passer par `iconv -f ISO-8859-1 -t UTF-8` pour les grep.

## Étape 2 — Scanner les nouvelles fonctions CAS

```bash
# Fonctions passées à !exec maxima
grep -rh "!exec maxima\|t_=!replace.*in " ressources/ --include="*.def" | \
  iconv -f ISO-8859-1 -t UTF-8 2>/dev/null | \
  grep -oP "\w+\s*\(" | sort | uniq -c | sort -rn

# Expressions passées à !exec pari
grep -rh "!exec pari" ressources/ --include="*.def" | \
  iconv -f ISO-8859-1 -t UTF-8 2>/dev/null | \
  grep -oP "pari \K.*" | sort | uniq -c | sort -rn
```

## Étape 3 — Vérifier le mapping SymPy

Le dict `_MAXIMA_TO_SYMPY` dans `backend/core/oef/def_engine.py` mappe les fonctions Maxima vers SymPy :

| Maxima | SymPy |
|---|---|
| `expand` | `expand` |
| `factor` | `factor` |
| `fullratsimp` | `simplify` |
| `ratsimp` | `simplify` |
| `cancel` | `cancel` |
| `radsimp` | `radsimp` |
| `printtex` | `latex` (retourne directement du LaTeX) |

Pour une nouvelle fonction Maxima, ajouter dans `_MAXIMA_TO_SYMPY` et vérifier avec :

```python
from core.oef.def_engine import _call_maxima
print(_call_maxima("nouvelle_fonction(x**2 - 1)"))
```

Références utiles pour des fonctions moins communes :
- `gcd(a,b)` → `sympy.gcd`
- `lcm(a,b)` → `sympy.lcm`
- `diff(expr,x)` → `sympy.diff`
- `integrate(expr,x)` → `sympy.integrate`
- `trigsimp(expr)` → `sympy.trigsimp`
- `subst(val,x,expr)` → implémentation custom avec `.subs()`

## Étape 4 — Implémenter une nouvelle commande `!cmd`

1. Ajouter le dispatch dans `DefEngine._eval_cmd` :
   ```python
   if cmd == "newcmd":
       return self._cmd_newcmd(args)
   ```

2. Implémenter `_cmd_newcmd(self, args: str) -> str`.

3. Pour comprendre la sémantique, inférer depuis les usages dans le corpus :
   ```bash
   grep -rh "!newcmd" ressources/ --include="*.def" | \
     iconv -f ISO-8859-1 -t UTF-8 2>/dev/null | head -20
   ```

4. Mettre à jour `docs/def-engine-commands.md`.

## Étape 5 — Vérifier la régression corpus

```bash
cd backend && source .venv/bin/activate
python3 -c "
import glob
from core.oef.def_engine import load_and_render

defs = glob.glob('../ressources/**/*.def', recursive=True)
ok, fail, empty = 0, 0, 0
failures = []
for path in sorted(defs):
    if b':question' not in open(path, 'rb').read():
        continue
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
for n, e in failures[:5]: print(f'  FAIL {n}: {e}')
"
```

**Baseline attendue** : OK ≥ 2162/2172, Fail ≤ 1 (seul `calfrac4.def` est connu en échec).

## Étape 6 — Tests

```bash
cd backend && pytest tests/core/oef/ -q
# Baseline : 233 tests
```

- **Tests unitaires** dans `tests/core/oef/test_def_engine_units.py` : tester la commande isolément.
- **Tests d'intégration** dans `tests/core/oef/test_def_pipeline.py` : ajouter un vrai `.def` comme fixture si la commande est non-triviale.

## Pièges connus

| Piège | Explication |
|---|---|
| Encodage ISO-8859-1 | Toujours `open(path, encoding='latin-1')` ou `errors='replace'` |
| `!translate` sans `internal` | C'est du tr-style (char par char), PAS du remplacement de chaîne |
| `!exec pari print(expr)` | `print()` en PARI retourne la valeur — unwrapper avant `eval()` |
| SymPy et `^` | Remplacer `^` → `**` avant `sympify()` |
| Registres `\r1`, `\r2`… | Variables internes WIMS (2 fichiers seulement, non prioritaire) |
| `!read` | Bloquant structurel — lit des fichiers WIMS non disponibles hors installation |
