# Fonctions CAS dans le corpus `.def` — plan d'implémentation

Inventaire des fonctions appelées via `!exec maxima` et `!exec pari` dans les 2272 fichiers `.def` de `ressources/`.

## Fonctions Maxima (`!exec maxima`)

| Fonction | Occurrences | Statut | Équivalent SymPy |
|---|---|---|---|
| `fullratsimp` | 990 | ✅ | `sympy.simplify` |
| `expand` | 147 | ✅ | `sympy.expand` |
| `op` | 48 | ❌ | retourne l'opérateur principal (`op(3*x^2)` → `*`) — pas d'équivalent direct |
| `args` | 48 | ❌ | retourne les arguments (`args(3*x^2)` → `[3, x^2]`) — `expr.args` en SymPy |
| `factor` | 19 | ✅ | `sympy.factor` |
| `diff` | 18 | ✅ | `sympy.diff(expr, x[, order])` |
| `subst` | 6 | ✅ | `expr.subs(var, val)` (Maxima ordre `subst(val, var, expr)`) |
| `ordergreat` | 4 | ❌ | ordonnancement de variables — probablement ignorable |
| `cardinality` | 4 | ✅ | `len({…})` après dédoublonnage |
| `setdifference` | 4 | ❌ | `sympy.FiniteSet` ou opération sur ensembles |
| `hipow` | 1 | ✅ | `sympy.Poly(expr, x).degree()` |
| `coeff` | 1 | ✅ | `sympy.Poly(expr, x).nth(n)` |
| `limit` | 1 | ✅ | `sympy.limit(expr, x, val)` |
| `ev` | 1 | ✅ | alias de `subst` (`ev(expr, var=val)` → `expr.subs(var, val)`) |

## Fonctions PARI (`!exec pari`)

| Fonction | Occurrences | Statut | Implémentation Python |
|---|---|---|---|
| `print` | 3022 | ✅ | unwrappé avant `eval()` |
| `concat` | 121 | ✅ | `"".join(str(a) for a in args)` |
| `polcoeff` | 42 | ✅ | `sympy.Poly(expr, x).nth(n)` |
| `poldegree` | 29 | ✅ | `sympy.Poly(expr, x).degree()` |
| `matrix` | 26 | ✅ | `sympy.Matrix(rows)` |
| `divrem` | 25 | ✅ | `divmod` (entiers) ou `sympy.div` (polynômes) |
| `expand` | 24 | ✅ | `sympy.expand` |
| `vector` | 19 | ✅ | liste Python |
| `denominator` | 15 | ✅ | `sympy.fraction(sympy.together(x))[1]` |
| `vecmax` | 14 | ✅ | `max(vec)` |
| `forstep` | 12 | ❌ | boucle PARI avec pas — complexe à eval() |
| `vecmin` | 10 | ✅ | `min(vec)` |
| `matdet` | 6 | ✅ | `sympy.Matrix(rows).det()` |
| `subst` | 6 | ✅ | `expr.subs(var, val)` |
| `heron` | 6 | ❌ | fonction custom (aire triangle par formule de Héron) |
| `numerator` | 5 | ✅ | `sympy.fraction(sympy.together(x))[0]` |
| `core` | 5 | ✅ | partie sans carré (signe préservé) via `sympy.factorint` |
| `ffp` | 2 | ❌ | corps fini — rare, probablement ignorable |
| `isprime` | 1 | ✅ | `1 if sympy.isprime(n) else 0` |
| `matsize` | 1 | ❌ | dimensions d'une matrice |

## Priorités suggérées

### Implémenté (mai 2026)
PARI : `concat`, `expand`, `denominator`, `numerator`, `vecmax`, `vecmin`,
`polcoeff`, `poldegree`, `divrem`, `matdet`, `isprime`, `subst`, `matrix`,
`vector`, `core`. Maxima : `diff`, `subst`, `coeff`, `hipow`, `limit`,
`cardinality`, `ev`. Les littéraux entiers sont auto-enrobés en `sympy.Integer`
pour que `3/4` produise `Rational(3, 4)` (sémantique PARI), et les identifiants
inconnus deviennent automatiquement des `sympy.Symbol`.

### Restant à implémenter
- `op` / `args` (48 Maxima) — manipulation symbolique sans équivalent direct
- `forstep` (12 PARI) — boucle PARI avec pas
- `heron` (6 PARI) — fonction custom (aire par Héron)
- `setdifference` / `ordergreat` (4 Maxima) — rares
- `ffp` / `matsize` (≤2 PARI) — très rares
