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
| `diff` | 18 | ❌ | `sympy.diff(expr, x)` |
| `subst` | 6 | ❌ | `expr.subs(x, val)` en SymPy |
| `ordergreat` | 4 | ❌ | ordonnancement de variables — probablement ignorable |
| `cardinality` | 4 | ❌ | `len(set(...))` |
| `setdifference` | 4 | ❌ | `sympy.FiniteSet` ou opération sur ensembles |
| `hipow` | 1 | ❌ | `sympy.Poly(expr, x).degree()` |
| `coeff` | 1 | ❌ | `sympy.Poly(expr, x).nth(n)` |
| `limit` | 1 | ❌ | `sympy.limit(expr, x, val)` |
| `ev` | 1 | ❌ | évaluation avec substitution — `expr.subs()` |

## Fonctions PARI (`!exec pari`)

| Fonction | Occurrences | Statut | Implémentation Python |
|---|---|---|---|
| `print` | 3022 | ✅ | unwrappé avant `eval()` |
| `concat` | 121 | ❌ | `str(a) + str(b)` |
| `polcoeff` | 42 | ❌ | `sympy.Poly(expr, x).nth(n)` |
| `poldegree` | 29 | ❌ | `sympy.Poly(expr, x).degree()` |
| `matrix` | 26 | ❌ | `sympy.Matrix(...)` |
| `divrem` | 25 | ❌ | `divmod(a, b)` |
| `expand` | 24 | ❌ | `sympy.expand` |
| `vector` | 19 | ❌ | liste Python |
| `denominator` | 15 | ❌ | `sympy.fraction(expr)[1]` |
| `vecmax` | 14 | ❌ | `max(vec)` |
| `forstep` | 12 | ❌ | boucle PARI avec pas — complexe à eval() |
| `vecmin` | 10 | ❌ | `min(vec)` |
| `matdet` | 6 | ❌ | `sympy.Matrix(...).det()` |
| `subst` | 6 | ❌ | `expr.subs(x, val)` |
| `heron` | 6 | ❌ | fonction custom (aire triangle par formule de Héron) |
| `numerator` | 5 | ❌ | `sympy.fraction(expr)[0]` |
| `core` | 5 | ❌ | partie sans carré d'un entier |
| `ffp` | 2 | ❌ | corps fini — rare, probablement ignorable |
| `isprime` | 1 | ❌ | `sympy.isprime(n)` |
| `matsize` | 1 | ❌ | dimensions d'une matrice |

## Priorités suggérées

### Priorité haute (fréquentes et faciles)
- `concat` (121 PARI) — simple concaténation de chaînes
- `diff` (18 Maxima) — `sympy.diff` prêt à l'emploi
- `denominator` / `numerator` (15+5 PARI) — `sympy.fraction()`
- `vecmax` / `vecmin` (14+10 PARI) — `max()` / `min()`

### Priorité moyenne (fréquentes mais complexes)
- `polcoeff` / `poldegree` (42+29 PARI) — nécessitent de parser le polynôme
- `divrem` (25 PARI) — `divmod()`
- `expand` (24 PARI) — même que Maxima expand

### Priorité basse (rares ou complexes)
- `op` / `args` (48 Maxima) — manipulation symbolique Maxima sans équivalent direct simple
- `matrix` / `vector` (26+19 PARI) — structures de données
- `forstep` (12 PARI) — boucle PARI complète
- `ordergreat` / `cardinality` / `setdifference` (4 Maxima chacun) — rares
