# Portage du moteur WIMS du C vers Python

> Document rédigé le 2026-05-12, après exploration du code source WIMS 4.28
> installé dans `~/pax/wims/`. La version figée de référence est le tag **v0.1**.

---

## Contexte : deux moteurs de rendu dans PAX

PAX comporte déjà un moteur de rendu des fichiers `.def` entièrement écrit en
Python (`backend/core/oef/def_engine/`). Ce moteur a été construit par
tâtonnements et corrections successives, **sans lire le code C de WIMS**. Il
couvre la grande majorité des exercices H4 mais présente des lacunes
découvertes au fil de l'usage (commandes manquantes, comportements légèrement
différents de ceux de WIMS).

La question posée : vaut-il mieux (a) continuer à corriger l'émulation Python
au fil de l'eau, (b) appeler le binaire WIMS comme sous-processus, ou (c)
porter méthodiquement le cœur du moteur C vers Python ?

---

## Architecture du moteur WIMS

WIMS est un **binaire C CGI** (`wims`) qui s'exécute sous Apache. Il n'est pas
conçu comme une bibliothèque : c'est une application web complète avec sessions
disque, variables d'environnement HTTP, et sortie HTML.

### Fichiers sources du cœur

| Fichier | Lignes utiles¹ | Rôle |
|---|---|---|
| `src/exec.c` | ~1 400 | Flux de contrôle : `!if`, `!while`, `!for`, `!goto`, `!read`, génération de formulaires HTML |
| `src/calc.c` | ~1 600 | Les ~60 commandes `!cmd` : `!randint`, `!replace`, `!translate`, `!append`… |
| `src/compare.c` | ~120 | Évaluation des conditions `!if` / `!ifval` |
| `src/variables.c` | ~1 200 | Stockage des variables, sessions, substitution dans `.phtml` |
| `src/var.c` | ~200 | Tables bas-niveau de variables (get/set, pools mémoire) |
| `src/rawmath.c` | ~50 | Tables de noms mathématiques (Greek letters, constantes) |

¹ Lignes non-triviales, hors commentaires et blancs.

**Total pertinent pour PAX : ≈ 4 570 lignes C → ≈ 2 500 lignes Python estimées.**

La différence vient de l'utilisation de constructions Python de haut niveau
(dict, list comprehensions, re, subprocess) là où le C utilise des buffers
fixes, des bsearch manuels et des appels système.

### Ce que PAX n'a PAS besoin de porter

- `src/wims.c` (1 318 lignes) : point d'entrée CGI, gestion des sessions HTTP,
  routing des requêtes → **inutile pour PAX** (on est stateless, JSON)
- `src/variables.c` dans sa partie `.phtml` et session : PAX n'a pas de session
  WIMS sur disque
- `src/Mathml/` (36 000 lignes générées) : rendu MathML → PAX utilise KaTeX
  côté frontend
- `src/Misc/` (canvasdraw, checkmol…) : outils spécialisés hors-sujet

---

## Analyse de portabilité fichier par fichier

### `compare.c` — Score 5/5 ⭐

**202 lignes, zero dépendance externe.**

C'est le moteur d'évaluation des conditions `!if` et `!ifval`. Il implémente
un parseur récursif descendant qui gère :

- Les opérateurs relationnels : `=`, `!=`, `<>`, `<`, `>`, `<=`, `>=`
- Les opérateurs logiques **top-level** : `and`, `or`
- Les opérateurs sémantiques : `isin`, `notin`, `wordof`, `notwordof`,
  `isitemof`, `lineof`, `varof`, `sametext`, `samecase`
- La gestion des parenthèses extérieures (strip avant évaluation)
- La précision numérique configurable via `wims_compare_precision`

Notre `_eval_condition` actuelle a été construite sans lire ce fichier et
présente plusieurs lacunes découvertes en production :

| Bug trouvé | Cause dans notre code | Correct dans compare.c |
|---|---|---|
| `($A=1) and ($B=+)` ignoré | `and` non géré | Split récursif sur `and`/`or` |
| `$val48<>$val36` toujours False | `<>` inconnu de Python | `<>` → `!=` dès le début |
| `(+=+)` évalué False | Parenthèses non strippées | Strip avant toute évaluation |
| `isitemof` non implémenté | Oubli | Dans `relation_type[]` |

**Recommandation : réécrire `_eval_condition` depuis `compare.c`. Effort : 1–2 jours.**

### `var.c` — Score 5/5 ⭐

**438 lignes (200 non-triviales).** Stockage bas-niveau des variables avec un
système de pools mémoire à 10 niveaux (1 à 64 Ko). La logique métier intéressante
est le `get`/`set` avec tags (read-only, noexport, internal), la protection par
trust bits, et la recherche par dichotomie.

En Python, tout cela se réduit à un `dict[str, str]` avec quelques règles de
permission. **C'est déjà ce qu'on fait.** La portabilité est maximale.

### `rawmath.c` — Score 5/5 ⭐

**825 lignes dont ~50 non-triviales.** Tables de noms mathématiques (lettres
grecques, fonctions, constantes) pour la normalisation d'expressions. En Python :
des dictionnaires statiques. Rien à faire d'intéressant.

### `variables.c` — Score 4/5

**1 666 lignes.** Contient deux choses très différentes :

1. La gestion de session / module / confparms (inutile pour PAX)
2. Le moteur de substitution de variables dans les `.phtml` (partiellement utile)

La partie utile est le comportement de substitution : ordre des passes,
traitement des `$var`, `$(var)`, `$(var[n])`, etc. Notre implémentation actuelle
couvre 95 % de ces cas. Le reste concerne des variables de session
(`$wims_session`, `$wims_user`) que PAX n'a pas.

### `exec.c` — Score 3/5

**2 176 lignes, ~1 400 non-triviales.** Implémente :

- `!for` (3 syntaxes : `var=n to m`, `var=n to m step k`, `var in list`)
- `!while` / `!endwhile` avec pile de boucles
- `!goto` / labels avec compteur anti-boucle-infinie (`GOTO_LIMIT = 500 000`)
- `!if` / `!else` / `!endif`
- `!read`, `!readproc` (inclusion de fichiers)
- Génération de formulaires HTML (inutile pour PAX)
- Gestion des liens HTTP (inutile pour PAX)

Ce qu'on a déjà porté : tout le flux de contrôle. **Ce qui reste :**

- Les 3 syntaxes de `!for` (on gère `n to m` mais pas `var in list` complètement)
- Le compteur `executed_gotos` (on l'a, mais la limite pourrait différer)
- Les `!read` complexes avec paramètres multi-niveaux

### `calc.c` — Score 2/5

**2 467 lignes, ~1 600 non-triviales.** C'est le fichier le plus complexe.

La table de dispatch `calc_routine[]` liste **~60 commandes**. Les plus
délicates :

- `calc_exec()` : exécute un sous-processus via `select()` / pipes avec timeout
  3 s. Notre `_call_maxima` et `_call_pari` remplacent ça par SymPy + subprocess.
- `calc_replace()` : fait appel à `sed` pour les remplacements regex. Notre
  implémentation utilise `re` Python.
- `calc_translate()` : fait appel à `tr` pour les translations complexes.
- `calc_randperm()` (= `!shuffle`) : Fisher-Yates + tracking de parité.
- `_blockof()` : extraction de plages (`i..j`) avec indices négatifs.

État actuel de notre portage de `calc.c` : **~70 % des commandes** sont
implémentées. Les manquantes sont découvertes au fil de l'exécution d'exercices
(`UNKNOWN_CMD:xxx`).

---

## Comparaison des approches

### Option A — Continuer l'émulation Python (approche actuelle)

Corriger les bugs au fil de l'eau, en s'aidant maintenant du code C comme
référence.

- **Pour** : pas de refactoring massif, chaque fix est localisé, tests continus
- **Contre** : risque d'angle mort sur des commandes rares jamais testées
- **Probabilité de couverture finale** : ~90–95 % des exercices H4

### Option B — Appeler le binaire `wims` en subprocess CGI

Créer un wrapper qui simule l'environnement CGI, lance `wims`, scrape l'HTML produit.

- `wims` requiert `libcrypt.so.1` absent sur Fedora 44 (remplacé par libxcrypt)
- Nécessite un répertoire de session par requête, des variables d'env HTTP
- La sortie est une page HTML complète, pas du JSON → scraping fragile
- **Durée estimée** : 3–5 semaines pour un résultat acceptable
- **Probabilité de succès robuste** : ~70 %

### Option C — Faire tourner Apache + WIMS et appeler via HTTP

WIMS tel qu'il est conçu, avec une vraie instance Apache.

- Installation Apache, configuration VirtualHost, gestion des sessions
- Scraping de pages HTML WIMS pour extraire les données d'exercice
- **Durée estimée** : 6–10 semaines
- **Probabilité de succès robuste** : ~85 %
- **Maintenabilité** : très faible (deux stacks à maintenir)

### Option D — Port "bourrin" : traduire les fichiers C clés vers Python

Lire chaque fichier C pertinent et le traduire fidèlement en Python, en
remplaçant les constructions système (pipes, select, buffers) par des
équivalents Python.

- **Pour** : sémantique exacte de WIMS, liste exhaustive des commandes,
  supprime les angles mort, un seul stack
- **Contre** : effort concentré sur 2–4 semaines, risque de régression sur
  les exercices déjà fonctionnels
- **Probabilité de succès** : ~88 %

---

## Plan de portage recommandé

Le port "bourrin" le plus utile est **ciblé** : on ne porte pas `wims.c` ni
`variables.c` (session/CGI), mais on s'appuie sur le C comme **spécification
authoritative** pour les parties déjà portées.

### Phase 1 — `compare.c` (1–2 jours)

Réécrire `_eval_condition` en suivant fidèlement le parseur de `compare.c`.
Gain immédiat : tous les bugs de conditions résolus en une fois.

Algorithme à porter :
```
compare(p, numeric, lvl=0):
  strip outer parens
  scan for top-level 'or' → recurse on both sides
  scan for top-level 'and' → recurse on both sides
  scan for relational op (<, >, =, !=, <>) → evaluate numerically or as string
  scan for semantic ops (isin, wordof, isitemof…) → dispatch to helpers
```

### Phase 2 — Exhaustivité de `calc.c` (1–2 semaines)

Utiliser la table `calc_routine[]` comme checklist :

1. Lister les ~60 commandes
2. Pour chacune : vérifier si notre implémentation existe et est fidèle
3. Porter les manquantes en priorité sur celles apparaissant dans le corpus

Commandes probablement absentes de notre moteur (à vérifier) :
`!isitemof`, `!lineof`, `!varof`, `!select`, `!rows2lines`, `!lines2items`,
`!items2lines`, `!words2items`, `!charof`, `!columnof`, `!singlespace`,
`!distribute`, `!bound`, `!advance`, `!reset`, `!default`.

### Phase 3 — Scan du corpus `.def` (0.5 jour)

Exécuter le scanner sur tous les `.def` du corpus H4 et collecter les
`UNKNOWN_CMD` restants. Créer une liste priorisée par fréquence d'apparition.

---

## Ce que PAX fait différemment de WIMS (et c'est intentionnel)

### `!read oef/embed.phtml`

Dans WIMS, `embed.phtml` est un script de ~250 lignes qui se comporte
différemment selon le mode (`$cmd`) :

- **Mode "new/reply"** : génère le champ de saisie HTML
- **Mode "solution/correction"** : affiche la réponse élève en couleur avec
  la correction
- **Mode "print"** : affiche les labels et numéros de questions

Notre `_render_embed()` ne gère que le mode "new" (génération d'un
`<span class="oef-input">` ou d'un `<cf-slot>`). La correction couleur
est entièrement reconstruite côté frontend PAX à partir des `checkResult`.

C'est un choix **délibéré** : on ne veut pas reproduire le rendu WIMS de la
correction (qui est côté serveur dans des `<div class="oef_indgood">`), mais
utiliser notre propre UI React/Vue.

### Confparms et variables de session

`$confparm1` à `$confparm8` sont des paramètres qu'un enseignant configure
quand il crée une feuille. Ils permettent de varier la difficulté ou le type
d'un exercice. Exemple pour `eqfactorcom1` :

| Variable | Confparm | Effet |
|---|---|---|
| `val2` | `$confparm1` | Nombre de termes (défaut : 3) |
| `val3` | `$confparm2` | Type de facteur A/B/C/D/E |
| `val4` | `$confparm3` | Entiers ou rationnels |
| `val5` | `$confparm4` | Contrainte sur les signes/magnitude |

Dans PAX, les confparms sont toujours vides → les exercices utilisent leur
comportement par défaut. C'est fonctionnel, mais PAX **ne peut pas exploiter
les variantes de difficulté** — elles demanderaient une UI pour que
l'enseignant les configure.

Les variables de session WIMS (`$status`, `$wims_session`, `$wims_user`,
`$imagedir`, etc.) sont soit ignorées, soit mockées avec des valeurs par défaut.
Les seules qui comptent pour PAX sont `$seed` (géré ✓) et `$m_step` (géré ✓
pour les dynsteps).

---

## État au moment du tag v0.1

| Composant | État |
|---|---|
| Flux de contrôle (`!if`, `!for`, `!while`, `!goto`) | ✓ Fonctionnel, quelques edge-cases corrigés |
| Conditions composées (`and`, `or`, `<>`) | ✓ Corrigé récemment |
| Commandes `!cmd` (~40/60) | ✓ Porté, ~20 commandes non confirmées |
| Substitution de variables `$var`, `$(var[n])` | ✓ Fonctionnel |
| `!exec pari` / `!exec maxima` | ✓ Émulé via Pari/GP et SymPy |
| `!read oef/embed.phtml` | ✓ Mode "affichage" uniquement |
| `!read oef/draw.phtml` (flydraw) | ✓ Rendu SVG inline |
| Confparms | Toujours vides (comportement par défaut) |
| Variables de session | Mockées ou ignorées |
| Opérateurs `isitemof`, `lineof` | ✗ Non implémentés |
| Commandes `!distribute`, `!bound`, `!advance` | ✗ Probablement absentes |

---

## Références

- Code C WIMS 4.28 : `~/pax/wims/src/`
- Moteur Python actuel : `backend/core/oef/def_engine/`
- Table des commandes C : `~/pax/wims/src/calc.c`, ligne 2247 (`calc_routine[]`)
- Parseur de conditions C : `~/pax/wims/src/compare.c`
- Script embed WIMS : `~/pax/wims/public_html/scripts/oef/embed.phtml`
- Script de session OEF : `~/pax/wims/public_html/scripts/oef/var.proc`
