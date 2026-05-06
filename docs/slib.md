# Slib — état et plan d'implémentation

Les **slib** (shared libraries) sont des sous-scripts WIMS appelés par `!readproc` ou `!read`
depuis les `.def`. Chaque slib reçoit ses paramètres via `$wims_read_parm`, produit son
résultat dans `slib_out`, et partage le contexte (`ctx`) de l'exercice appelant.

---

## Architecture du moteur PAX

Le dispatch est dans `_cmd_readproc` (mixin `_SlibMixin`, `core/oef/def_engine/slib.py`) :

```
!readproc <path> <args>
           │
           ├─ oef/draw.phtml  → flydraw_to_url() (built-in Python) ✅
           ├─ slib/stat/median → _compute_weighted_median() (built-in Python) ✅
           ├─ slib/<name>     → _run_slib() → cherche le script, l'exécute via _run_script_lines()
           └─ autres          → ignoré silencieusement
```

`_run_slib` cherche le script dans l'ordre :
1. `<module_dir>/<slib_path>` — slib locale au module (ex. `numeration.fr/slib/char2item`)
2. `<module_dir>/slib/local/<name>` — override local WIMS
3. `<wims_scripts_dir>/<slib_path>` — via `_find_wims_scripts_dir()`

`_find_wims_scripts_dir` remonte l'arbre depuis `def_path` en cherchant
`<dir>/wims/public_html/scripts`. **En Docker, cette recherche échoue** car seul
`/ressources/` est monté (pas le répertoire WIMS hôte).

---

## Inventaire H4/ — toutes les cibles `!readproc`

| Cible | Occ. H4 | Statut | Exercices concernés |
|---|---|---|---|
| `oef/draw.phtml` | 21 | ✅ built-in | `evalwimstrigo.fr`, `espcube.fr`, `oefline.it`… |
| `slib/triplerelation/tabular` | 2 | ⚠️ vendoring requis | `moles.nl` (concentration, masse volumique) |
| `slib/chemistry/chemeq_tex` | 2 | ❌ binaire externe | `moles.nl` (masse1, masse2) |
| `slib/chemistry/chemeq_mass` | 2 | ❌ binaire externe | `moles.nl` (masse1, masse2) |
| `slib/utilities/mathcalc` | 1 | ⚠️ display only | `docbinaire.fr` doc |
| `slib/text/matrixhtml` | 1 | ⚠️ vendoring requis | `htmlinput.def` (log/) |
| `slib/oef/env` | 1 | ⚠️ vendoring requis | `htmlinput.def` (log/) |
| `slib/matrix/non0` | 1 | ⚠️ vendoring requis | `oefline.it/sys3.def` |
| `slib/char2item` | 1 | ✅ locale | `numeration.fr` |
| `slib/basep` | 1 | ✅ locale | `numeration.fr` |

**Légende :** ✅ fonctionne · ⚠️ fonctionne si script accessible · ❌ nécessite du code Python

---

## Slib déjà fonctionnelles

### `oef/draw.phtml` ✅
Built-in Python. Convertit les commandes flydraw en SVG data-URI, stocke dans `ctx['ins_url']`.

### `slib/stat/median` ✅
Built-in Python. Calcule la médiane pondérée depuis un vecteur de valeurs.

### `slib/char2item` ✅
Script WIMS local à `numeration.fr/slib/char2item`. Décompose un mot en liste de caractères.
Trouvé par `_run_slib` via le chemin module-local.

### `slib/basep` ✅
Script WIMS local à `numeration.fr/slib/basep`. Convertit un entier de la base 10 vers la base p.
Trouvé par `_run_slib` via le chemin module-local.

---

## Problème de chemin en Docker

En production Docker, `_find_wims_scripts_dir` remonte depuis `/ressources/H4/...` et
ne trouve jamais `wims/public_html/scripts` (non monté dans le container).

**Deux solutions :**

### A — Variable d'environnement `WIMS_SCRIPTS_DIR` (recommandée)
Ajouter dans `config.py` :
```python
wims_scripts_dir: str = ""  # ex. /ressources/wims-scripts
```
Et dans `_find_wims_scripts_dir` : retourner `settings.wims_scripts_dir` en priorité si défini.
Monter `~/pax/wims/public_html/scripts` dans le container via `docker-compose.yml`.

### B — Vendoring dans `backend/scripts/slib/`
Copier les scripts WIMS purs (sans binaire externe) dans
`backend/scripts/slib/<domain>/<name>`. Modifier `_find_wims_scripts_dir` pour chercher
aussi `<app_root>/scripts` (là où `/app/scripts/slib/` serait dans le container).

---

## Slib à implémenter

### 1. Vendoring — scripts purs WIMS (priorité haute)

Ces scripts ne nécessitent aucun binaire externe. Il suffit de les rendre accessibles.

| Script | Source WIMS | Rôle |
|---|---|---|
| `slib/triplerelation/tabular` | `wims/public_html/scripts/slib/triplerelation/tabular` | Génère un tableau à double entrée (x, y, z=f(x,y)) avec cases à remplir |
| `slib/matrix/non0` | `wims/public_html/scripts/slib/matrix/non0` | Matrice aléatoire sans zéro via PARI |
| `slib/oef/env` | `wims/public_html/scripts/slib/oef/env` | Lit une variable d'environnement OEF (`oefenv_*`) |
| `slib/text/matrixhtml` | `wims/public_html/scripts/slib/text/matrixhtml` | Génère un tableau HTML depuis notation `[a,b;c,d]` |

**Plan :** activer l'une des deux solutions de chemin ci-dessus. Aucun code de parsing
supplémentaire n'est requis — `_run_script_lines` gère déjà le sous-ensemble WIMS utilisé
par ces scripts (`!if/!else/!endif`, `!for/!next`, `!distribute`, `!exec pari`, etc.).

À noter : `slib/triplerelation/tabular` est le plus important (2 exercices de chimie H4 —
`concentration1.def` et `massevolumique.def`). Il utilise `!exec pari` pour les calculs
matriciels et `!while` pour la convergence. **`!while/!endwhile` n'est pas encore géré
dans `_run_script_lines`** — c'est un prérequis à implémenter avant de vendre ce script.

---

### 2. `slib/chemistry/chemeq_tex` et `chemeq_mass` — Python built-in (priorité haute)

Ces slib appellent `!exec chemeq` (binaire C WIMS). Le script est trivial :

```wims
# chemeq_tex
chemeq_option=l
slib_out=!exec chemeq $wims_read_parm

# chemeq_mass
chemeq_option=M
slib_out=!exec chemeq $wims_read_parm
```

Le binaire `chemeq` fait deux choses :
- **option `l`** : formule chimique → LaTeX (`H2O` → `H_2O`, `Fe(CN)6^3-` → `Fe(CN)_6^{3-}`)
- **option `M`** : formule → masse molaire (`H2O` → `18.015`)

**Plan — deux approches :**

**A (simple) : implémenter en Python dans `slib.py`**

Ajouter deux cas dans `_cmd_readproc` avant le dispatch `slib/` :

```python
if path == "slib/chemistry/chemeq_tex":
    self.ctx["slib_out"] = _chemeq_to_latex(proc_args)
    return

if path == "slib/chemistry/chemeq_mass":
    self.ctx["slib_out"] = _chemeq_molar_mass(proc_args)
    return
```

`_chemeq_to_latex` : parser regex de formule chimique.
- `([A-Z][a-z]?)(\d*)` → groupe élément + coefficient
- parenthèses `(...)n` → répétition
- charges `^n+` / `^n-` → `^{n+}` / `^{n-}`
- `->` → `\rightarrow`
- `+` entre molécules → `+`

`_chemeq_molar_mass` : masses atomiques (dict) + parser pour sommer.

**B (robuste) : appeler le binaire chemeq si disponible**
Ajouter `!exec chemeq` dans `_cmd_exec` → tente `subprocess(["chemeq", ...])`.
Fallback sur le parser Python si binaire absent.

**Recommandation : A** — le binaire n'est pas dans le container, le parser Python couvre
les formules du corpus H4 (inorganique simple : H₂O, FeSO₄, Fe₂(SO₄)₃, HCO₃⁻…).

---

### 3. `oef/steps.proc` — ignoré pour l'instant (priorité basse)

Mécanisme de questions en plusieurs étapes (stepwise exercises). Affecte 3 exercices H4,
tous dans des modules de type documentation (`docbinaire.fr`). Complexe à implémenter
(gère `oefstep`, `dynstep`, compteurs de réponses). À faire si ces exercices sont jugés
importants.

---

### 4. `slib/utilities/mathcalc` — stub HTML (priorité basse)

Génère un bouton/lien ouvrant une popup calculatrice JavaScript. Sans impact sur la logique
de l'exercice. Implémenter comme stub retournant `""` ou un texte fixe
`[calculatrice non disponible]`.

---

## Résumé du plan

| Priorité | Action | Effort |
|---|---|---|
| 🔴 Haute | Activer accès scripts WIMS (var d'env ou vendoring) | 1h |
| 🔴 Haute | Implémenter `chemeq_tex` / `chemeq_mass` en Python | 2h |
| 🟡 Moyenne | Implémenter `!while/!endwhile` dans `_run_script_lines` (requis par `triplerelation/tabular`) | 1h |
| 🟢 Basse | Stub `oef/steps.proc` | 1h |
| 🟢 Basse | Stub `utilities/mathcalc` | 15min |
