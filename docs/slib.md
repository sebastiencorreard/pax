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

## État des slib — mesuré au rendu du corpus

Chiffres relevés le 2026-08-31 en instrumentant `_cmd_readproc` sur les 4278
exercices, graine 42 : **84 slib appelés, 2784 appels**. C'est la seule mesure
qui vaille — compter les occurrences dans les sources surestime largement, et
l'absence d'un fichier dans `ressources/wims-scripts/` ne dit rien du portage
(`slib/commutesom`, `slib/runcode` et `slib/calcpuis` n'y sont pas et
fonctionnent, PAX les émulant en Python).

**Attention au critère.** Un `slib_out` vide ne signale une dette que si le
slib est censé en poser un : `slib/stat/dataproc` (55 « vides » sur 202
appels) n'en pose **aucun** — il alimente `slib_data` et `slib_weight`. Vérifier
`grep -c '^\s*slib_out=' <fichier>` avant de conclure.

### Ce qui reste, et pourquoi

| slib | appels vides | exercices | obstacle |
|---|---|---|---|
| `geo2D/offdraw` · `polyoff` · `polynet` | 22 / 26 | 6 | la variable PARI `W` |
| `lang/swac` | 13 / 23 | 6 | mots hors des index rapatriés |
| `oef/env` | 15 / 533 | 15 | `rename`, `user`, `list_error`, `year` |

`basep`, `text/sigunits` et `stat/dataproc` en sont sortis — les deux premiers
réparés, le troisième n'ayant jamais rien eu.

**`geo2D/offdraw`** reçoit `[W[1]],[W[2]]` non substitué. `W` vient de
`slib/geo2D/polynet`, qui charge `gp/spanning_tree.gp` par `!readproc` puis
appelle `etale(couv,ff,f2[1],matsize(xyz)[1])`. Cette bibliothèque emploie
`my()`, le cardinal `#f`, les lambdas `{v->…}` — que le mini-interpréteur PARI
ne connaît pas. C'est un chantier d'interpréteur pour huit exercices, en
comptant les deux `bound` d'`oefpolynet` qui butent sur le même `W`.

**`lang/swac`** lit `!record 0 of data/swac/packs`, puis des index par paquet.
Ces données ont été rapatriées le 2026-08-31 depuis
`wims/public_html/scripts/data/swac` — le pointeur `packs`, les index allemands
et le paquet `eng-balm-verbs`, 568 Ko en tout ; l'audio lui-même reste distant,
servi depuis l'URL que porte `packs`.

Il a fallu deux corrections pour que le slib s'en serve. `!lookup` ne cherchait
que dans le répertoire du module, quand un slib partagé lit ses données là où
il vit : `_read_module_file` se replie désormais sur `wims-scripts/`. Et
`!record 0` rendait le vide, alors que l'indice zéro est licite pour cette
commande seule (calc.c:614) et désigne l'en-tête — ici l'hôte des fichiers
audio. Le slib rend maintenant sa balise `<audio>`.

**`basep`** fonctionnait déjà ; ses appelants lui passaient `rint(NaN**4*0)`.
En remontant : `val5=$confparm4`, et `confparm4` est calculé par le **`var.proc`
du module** —

    basep=!randitem $confparm1
    confparm4=$basep

— fichier que PAX n'exécutait pas. Il ne lisait que les `!default confparmN=`
de `introhook.phtml` (cf. `_module_confparm_defaults`), ce qui suffit à
`confparm1`, `2` et `3` mais pas au quatrième, qui demande un calcul.

`_module_var_proc_lines` exécute désormais ce fichier avant chaque exercice,
comme WIMS qui le lit « for all valid calls to the module ». La crainte était
la portée : **340 modules portent un `var.proc`, et ils couvrent les 4301
exercices du corpus** — chaque rendu exécute donc un fichier jusque-là jamais
lu, et ces fichiers ne sont pas anodins (10 471 lignes, 659 `!if`, 68 `!for`,
61 `!readproc` qui en appellent d'autres).

La mesure a démenti la crainte. Sur les 12 900 rendus : **111 valeurs
modifiées, toutes dans `numeration.fr`, dont 22 passées du vide à une valeur,
aucune vidée** ; 0 segment perdu, 0 groupe déséquilibré, les six sentinelles
inchangées. Les 339 autres `var.proc` posent des variables que leurs exercices
n'utilisent pas ou que le `.def` réécrit : ils ne déplacent rien.

**`text/sigunits`** ne devait rien à la conversion d'unités, contrairement à ce
qu'affirmait la version précédente de ce document. Ses 55 appels vides venaient
tous d'un seul exercice, `mouvrel/vitesse1`, qui les enchaîne en boucle : son
`!randfile /data1` cherchait à la racine du disque, `os.path.join` prenant le
`/` initial pour un chemin absolu là où `find_module_file` concatène du texte.
Le module y perdait ses données, et l'exercice tout son contenu. Le slib, lui,
n'avait rien.

**`stat/dataproc`** est sain, et l'était déjà : il ne pose pas de `slib_out`,
d'où ses « 40 vides » au compteur. Ses seules sorties creuses sont onze
`slib_weight` sur 202, pour des séries **non pondérées** — une liste sans
seconde colonne, cas que le slib traite explicitement (`!if $slib_weight!=$empty`).
Vérifié sur les valeurs : `descriptives/ecarttype` rend `1.34` pour
`1;5;4;4;3;2`, soit l'écart-type de population, et `oefstat.nl/mean`
`3.97368421053`.

**`oef/env`** rend encore le vide sur quatre mots — `rename`, `user`,
`list_error`, `year` — qui sont des variables de session que PAX ne tient pas.
Son cinquième cas, `lang`, s'est révélé un effet de bord de l'exécution des
`var.proc` : quatre modules y écrivent `oefenv_lang=$lang`, ce qui écrasait par
du vide la valeur que `render` venait de poser. `$lang` est donc posée avant,
avec la langue du module. `$presentgood` s'y prêterait, mais aucun `var.proc`
du corpus ne le lit : on ne le pose pas.

### Ce qui a été fait depuis la version précédente de ce document

`chemeq_tex`, `chemeq_mass` et l'équilibrage (`chemeq_equilibrium`) sont portés
— cf. `core/oef/def_engine/chemeq.py`, dont les sorties sont confrontées au
binaire du dépôt. `!while` l'est également, ainsi que `units-filter` (arrondi),
`!increase`, `!varlist`, `!getdef` et le `!read` des slib.
