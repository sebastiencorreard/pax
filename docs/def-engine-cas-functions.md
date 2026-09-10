# Fonctions CAS dans le corpus `.def` — plan d'implémentation

Inventaire des fonctions appelées via `!exec maxima` et `!exec pari` dans les 2272 fichiers `.def` de `ressources/`.

## Fonctions Maxima (`!exec maxima`)

| Fonction | Occurrences | Statut | Équivalent SymPy |
|---|---|---|---|
| `fullratsimp` | 990 | ✅ | `sympy.simplify` |
| `expand` | 147 | ✅ | `sympy.expand` |
| `op` | 48 | ✅ | `expr.func` en SymPy — table de correspondance `{Add:"+", Mul:"*", Pow:"^"}`, sinon `func.__name__` |
| `args` | 48 | ✅ | `expr.args` en SymPy — formaté `[a,b,c]` ; atome → `[]` |
| `factor` | 19 | ✅ | `sympy.factor` |
| `diff` | 18 | ✅ | `sympy.diff(expr, x[, order])` |
| `subst` | 6 + 20 `.def` | ✅ | `expr.subs(var, val)` (Maxima ordre `subst(val, var, expr)`) ; la forme à équation `subst(x=a, expr)` est réécrite en `_subst_eq(x, a, expr)` par `_reecrire_subst_equation`, à toute profondeur (`subst(x=b,F)-subst(x=a,F)`) |
| `integrate` | via `slib/function/integrate` | ✅ | `sympy.integrate(f, x)` ; à bornes, `integrate(f, x, a, b)` → `sympy.integrate(f, (x, a, b))`. Une intégrale que SymPy ne sait pas calculer repart telle quelle, et la slib passe à `intnum` (non émulé) |
| `ordergreat` | 4 | ✅ | ordonnancement de variables — ignoré (retourne `""`) |
| `cardinality` | 4 | ✅ | `len({…})` après dédoublonnage |
| `setdifference` | 4 | ✅ | `FiniteSet(A) - FiniteSet(B)` — retourne `{a,b,…}` ou `{}` |
| `hipow` | 1 | ✅ | `sympy.Poly(expr, x).degree()` |
| `coeff` | 1 | ✅ | `sympy.Poly(expr, x).nth(n)` |
| `limit` | 1 | ✅ | `sympy.limit(expr, x, val)` |
| `ev` | 1 | ✅ | alias de `subst` (`ev(expr, var=val)` → `expr.subs(var, val)`) |

**Noms réservés.** WIMS envoie à Maxima un en-tête (`src/Interfaces/maxima.c`)
qui pose `e:%e; pi:%pi; Pi:%pi; PI:%pi; I:%i; i:%i`. `_sympify_arg` lit donc
`e` comme `sympy.E` — lu comme un symbole, `e^(-x-3)` s'intégrait en
`Piecewise(… /log(e) …)`. `inf`/`minf`, eux, restent des **symboles** : le
simplificateur de Maxima ne fait pas d'arithmétique sur l'infini
(`fullratsimp(-inf-(-inf))` vaut 0, et `inequations/ineqlin1` en dépend) ; seules
les bornes de `limit` et d'`integrate` les lisent comme `±∞` (`_borne`), et un
infini calculé s'écrit `inf`/`minf` en sortie (`limpolfrac` teste
`!if $val12=minf`). Un **symbole
libre** seul (`vide`) est rendu tel quel, comme Maxima l'évalue, et non découpé
en `v*i*d*e` par la multiplication implicite.

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
- `op` / `args` (48 Maxima) — ✅ implémentés
- `forstep` (12 PARI) — boucle PARI avec pas
- `heron` (6 PARI) — fonction custom (aire par Héron)
- `setdifference` / `ordergreat` (4 Maxima) — rares ✅ setdifference implémenté, ordergreat ignoré
- `ffp` / `matsize` (≤2 PARI) — très rares
