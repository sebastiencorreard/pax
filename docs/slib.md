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
slib est censé en poser un : `slib/stat/dataproc` (40 « vides » sur 202
appels) n'en pose **aucun** — il alimente `slib_data` et `slib_weight`. Vérifier
`grep -c '^\s*slib_out=' <fichier>` avant de conclure, puis mesurer les
variables que le slib pose vraiment : c'est ce qui l'a innocenté.

**Et le vide peut être le rendu juste.** Avant de porter quoi que ce soit,
remonter à la source WIMS de la variable : les 12 derniers appels vides
d'`oef/env` viennent d'un `my_var.proc` que son module ne lit pas — WIMS rend
le vide lui aussi. Attention alors au `grep` : ces `.def` sont en ISO-8859, où
il se tait sans le dire ; `grep -a` les lit.

**Attention au cache.** Une instrumentation qui rejoue le corpus doit être
précédée d'un `redis-cli FLUSHDB`, faute de quoi les rendus sortent du cache
sans exécuter une ligne du moteur — un espion y compte zéro appel et le
silence se lit comme une absence.

### Ce qui reste, et pourquoi

Il n'en reste aucun. `basep`, `text/sigunits`, `lang/swac` et le trio
`geo2D/offdraw` · `polyoff` · `polynet` sont réparés ; `stat/dataproc` et
`oef/env` n'avaient jamais rien eu à réparer.

Attention au compteur pour `polyoff` : comme `stat/dataproc`, il ne pose
**aucun** `slib_out` — il alimente `slib_xyz` et `slib_ff`. Ses « 8 vides »
sur 8 appels ne mesurent rien.

**`geo2D/offdraw`** recevait `[W[1]],[W[2]]` non substitué, et le diagnostic
s'arrêtait à « chantier d'interpréteur PARI ». Il l'était, mais pas seulement,
et surtout pas d'abord : **la bibliothèque n'était jamais lue**.
`!readproc gp/spanning_tree.gp` tombait dans le « silently ignore » des procs
non-`slib/`, et les 177 polyèdres `.off` n'avaient pas été rapatriés. Tant que
ces deux-là tenaient, aucune limite de l'interpréteur ne pouvait se voir.

Ensuite seulement, huit constructions GP manquaient — lambdas `{v->…}`,
accolade terminant une instruction, commentaires `/* … */`, cardinal `#v`,
`my()` initialisant, `until()`, affectations composées / en chaîne /
multiples, tranches `v[a..b]` —, plus deux défauts qui ne levaient rien :
`my()` écrivait dans l'espace global (le `v` local de `deplacement_poly`
écrasait le paramètre `v` d'`etale`), et `matrix(…)` rendait une matrice
sympy indexée à partir de **0**. Voir `pari_prog.py` et
`tests/core/oef/test_pari_prog.py`.

**`lang/swac`** lit `!record 0 of data/swac/packs`, puis des index par paquet.
Ces données ont été rapatriées le 2026-08-31 depuis
`wims/public_html/scripts/data/swac` — le pointeur `packs`, les index allemands
et le paquet `eng-balm-verbs`, 568 Ko en tout ; l'audio lui-même reste distant,
servi depuis l'URL que porte `packs`.

Il a fallu quatre corrections pour que le slib s'en serve, et les deux
dernières valent d'être retenues parce que **le diagnostic tenu jusque-là était
faux**. On lisait « les mots demandés ne sont pas dans les index rapatriés » :
il n'y avait aucun manque de données.

- `!lookup` ne cherchait que dans le répertoire du module, quand un slib
  partagé lit ses données là où il vit : `_read_module_file` se replie
  désormais sur `wims-scripts/`.
- `!record 0` rendait le vide, alors que l'indice zéro est licite pour cette
  commande seule (calc.c:614) et désigne l'en-tête — ici l'hôte des fichiers
  audio.
- `!lookup` s'arrêtait à la première ligne physique. `_lookup` (calc.c:1883)
  prolonge l'enregistrement tant qu'une contre-oblique précède le saut de
  ligne, la remplace par une espace et garde le saut : c'est la forme des
  `sw_tags`, dont un enregistrement porte tous les mots-clés d'un fichier
  audio. Sans la suite, seul `swac_text` en revenait.
- `!getopt` découpait sur les blancs et gardait les délimiteurs. `calc_getopt`
  (calc.c:2051) borne la valeur par son `"`, `(`, `[` ou `{` et le **retire** :
  `swac_text="das Dreieck"` vaut `das Dreieck`, non `das`. C'est là qu'était
  toute l'affaire — les mots cherchés n'étaient pas absents, ils étaient
  tronqués à leur premier mot.

Le slib rend maintenant sa balise `<audio>` sur ses 23 appels, et
`geometrie_audio` retrouve le widget d'appariement qu'il ne rendait plus.

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

**`oef/env`** est clos : sur 556 appels, les 14 qui rendent encore le vide le
rendent **chez WIMS aussi**. Ses deux premiers cas, eux, étaient bien des
manques de PAX.

- `lang` — un effet de bord de l'exécution des `var.proc` : quatre modules y
  écrivent `oefenv_lang=$lang`, ce qui écrasait par du vide la valeur que
  `render` venait de poser. `$lang` est donc posée avant, avec la langue du
  module. `$presentgood` s'y prêterait, mais aucun `var.proc` du corpus ne le
  lit : on ne le pose pas.
- `year` — `quizzautomat.fr/var.proc` le tire de `$wims_now`, l'horloge que
  WIMS fige au début de chaque requête (`wims.c:1200`) et que PAX ne posait
  pas. Réparé : `pcent5` datait son énoncé « en -2 » et « en -1 ».
- `rename`, `user`, `list_error` (12 appels, `oefanglais.fr`) — ils ne sont
  posés que par `my_var.proc`, que le `var.proc` du module **ne lit pas** : la
  ligne est commentée (`!!read my_var.proc`), et le fichier s'ouvre lui-même
  sur `!!no more used`. `oefenv_user` y est de surcroît réservé au
  superviseur. Rien à réparer.
- l'argument vide (2 appels, `oefdeutsch.fr/geo3`) — la source écrit
  `slib(oef/env \presentgood)`, une *référence* de variable là où le nom
  littéral était voulu. WIMS y rend `$(oefenv_)`, soit le vide. Défaut
  d'auteur, reproduit fidèlement.

### Les procs qui ne sont pas des slib

`!readproc` sert aussi des procs hors de `slib/`. Ils étaient tous ignorés en
silence ; deux le sont encore, et c'est **mesuré**, pas déduit.

| proc | appels | état |
|---|---|---|
| `oef/steps.proc` | 635 | **exécuté** — il normalise `oefsteps`, et 189 réponses sont apparues |
| `gp/*.gp` | 8 | **exécuté** — une bibliothèque PARI, cf. `geo2D/polynet` |
| `oef/togetfile.proc` | 43 | **exécuté** — le magasin de fichiers de session dont Jmol tire ses modèles |
| `js/geogebra/test` | 12 | **exécuté** — il pose `geogebra_exists`, désormais vrai |
| `oef/drawtikz.phtml` | 5 | inerte : `!if $printlatex!=yes → !exit`, et PAX ne pose jamais ce drapeau |

Le détail de chaque cas est au point de chute de `_cmd_readproc`
(`def_engine/slib.py`). Le seul qui reste est mort-né : il ne sert que l'export
LaTeX, que PAX n'a pas.

### La chaîne Jmol

Sept exercices affichent une figure 3D au rendu de l'énoncé : quatre patrons de
polyèdre (`oefpolynet.fr`, par `slib/geo3D/polyhedra`) et trois molécules
(`oefmolecule.fr`, par `slib/chemistry/jmolshow`). Deux autres — `oefpolynet`
21 et 22 — n'appellent le slib que depuis `:postdef`, donc à la correction.

`jmolshow` a **trois branches**, et le corpus les emprunte toutes les trois.
C'est ce que dit la mesure, sur les neuf `.def` et les trois graines
sentinelles :

| branche | qui | ce qu'elle charge |
|---|---|---|
| jeton de session | les 4 polynet, 36 rendus | `off2jmol` calcule le `.xyz` (sommets) et le `.spt` (script de tracé), `togetfile.proc` les range, `jmolshow` les redéréférence |
| fichier du module | `structure`, 2 graines sur 3 | `data/benzene.pdb`, 1033 o déjà convertis et commités |
| identifiant préfixé | `isomerie` et `jmol`, 18 rendus | un SMILES (`@CCCCC`) : rien à lire sur disque, l'applet le fait résoudre par cactus.nci.nih.gov |

Trois pièges s'y sont logés, tous corrigés :

- **`$wims_ref_name` vide.** `variables.c:118` montre que WIMS y met une URL
  absolue, réécrite en `https:`. `jmolshow` s'en sert pour distinguer une URL
  d'un chemin (`!if __http isin __$slib_file`). Vide, le test échouait, le slib
  prenait l'URL que `togetfile` venait de rendre pour un chemin, n'y lisait rien
  et **ré-écrivait un fichier vide par-dessus** — 55 écritures vides sur les
  neuf exercices, les bons `.xyz`/`.spt` restant orphelins.
- **`!exec obabel.sh` non reconnu.** Le script de WIMS rend `-1` quand il
  échoue, et `jmolshow` teste exactement cela pour se replier sur cactus.
  Tombant dans le `return ""` du `!exec`, `"" != "-1"` faisait toujours prendre
  la branche « la conversion a réussi », avec un fichier vide : 18 rendus, 18
  molécules absentes. PAX n'embarque pas Open Babel — rendre `-1` dit la vérité
  dans les termes où le slib l'attend.
- **Le `<script>` inline.** Comme pour l'éditeur de code, un `<script>` injecté
  par le `v-html` du front ne s'exécute jamais. `_render_jmol_embed` intercepte
  donc le slib et émet un marqueur `pax-jmol` portant la configuration en JSON,
  que le composant Vue interprète — même dispositif que JSXGraph.

Côté front, `composables/useJsmol.ts` charge JSmol depuis
`chemapps.stolaf.edu` : la bibliothèque n'est **ni sur cdnjs ni sur jsdelivr**
(le paquet npm `jsmol` n'est qu'un chargeur de 1,4 Ko), et le mode HTML5 a
besoin qu'un hôte serve aussi son arbre `j2s/`. Tout tient dans la constante
`JSMOL_BASE` : vendoriser un jour — la LGPL le permet — se réduit à la changer.

Deux détails que seul l'essai au navigateur a révélés : l'applet s'initialise en
**asynchrone**, et tout script lancé avant son `readyFunction` se perd sans un
mot dans la console ; et `Jmol.loadInline` n'existe pas sur le namespace public
— le modèle passe par un bloc `load DATA "…" … end "…"` dans le script.

Enfin, les trois molécules d'`oefmolecule` vivent dans un `<table>`, qui reste
un seul segment HTML : leurs marqueurs sont hydratés après le rendu
(`hydrateJmolMarkers`), comme le sont déjà les champs et les cases en tableau.

### GeoGebra — l'affichage

`slib/geo2D/geogebra` s'arrêtait à sa deuxième ligne. Elle lit
`js/geogebra/test`, un fichier absent de l'arbre WIMS vendorisé, dont le rôle
est de poser `geogebra_exists` ; faute de drapeau, le slib rendait
l'avertissement de WIMS, « GeoGebra is not installed ». Le front chargeant
maintenant `deployggb.js`, la réponse est oui, et le proc pose le drapeau —
c'est sa seule lecture dans tout le corpus.

**Ce que cela ouvre, mesuré.** 65 `.def` mentionnent GeoGebra, 38 appellent le
slib. Au rendu de l'énoncé, à la configuration par défaut, **un seul** affiche
une applet : `oefprogpythag.fr/experim`. Les autres se répartissent ainsi :

| combien | qui | pourquoi |
|---|---|---|
| 34 | `OEFevalwimsgespa1.fr` | derrière `!if $val9==2`, où `val9` vient de `confparm1`. L'`introhook.phtml` du module fait `!set confparm1=1` et son `!formradio` propose « un dessin statique, Geogebra 3D » : **le module choisit le dessin statique**, GeoGebra est l'option de l'enseignant. Vérifié : à `confparm1=2`, les 34 rendent leur cube 3D. |
| 2 | `oefalgopython.fr` heron1/2 | l'appel est dans `:postdef`, et sa variable (`val79`) n'est lue nulle part |
| 1 | `oefqcm3.fr/q102` | même chose : `val39` est assignée puis jamais lue — mort chez WIMS aussi |

Contrairement à Jmol, on **ne réimplémente pas** le slib : il sait démêler les
options de l'applet des commandes GeoGebra, et parmi ces dernières les méthodes
de l'API (`setFixed('A',true)`, appelées telles quelles) des constructions
(`C=Intersect[r,s,1]`, qui passent par `evalCommand`). On le laisse s'exécuter
et on traduit ses variables — `_render_geogebra_embed`.

Deux pièges s'y sont logés :

- C'est `slib_parameters<N>` qu'il faut lire, **pas** `slib_data_param` : le
  slib n'ajoute le `filename` du `.ggb` qu'après avoir refermé le second dans
  le premier. À lire le mauvais, `experim` s'ouvrait sur une applet vide, sans
  sa figure ni sa perspective.
- Le slib écrit ses items par `!append item $\<retour>`, où le `$…$` de WIMS
  délimite un littéral ne contenant qu'un saut de ligne. PAX en laisse le `$`
  d'ouverture, d'où des séparateurs `,$\n` que JSON refuse ; on les normalise.

Le `.ggb` d'un module vit sous `images/` ; le slib le nomme `$imagedir/<x>`, et
`inline_pax_images` ne réécrit que les `<img>`. `_url_fichier_module` le résout
donc vers `/api/static`, que `useExerciseLogic` préfixe ensuite de l'API base.

Côté front, `deployggb.js` vient de `https://www.geogebra.org/apps/` : ce n'est
qu'un **chargeur** de 37 Ko, qui va chercher l'application sur
`cdn.geogebra.org` — on ne réhéberge rien, ce qui laisse la question de licence
où GeoGebra la met pour l'intégration. Le dépôt en garde une copie vendorisée
(`wims/public_html/scripts/js/geogebra/`), figée à la version de l'arbre WIMS ;
basculer dessus se réduit à changer `DEPLOYGGB` dans `composables/useGeogebra.ts`.

Comme pour Jmol, l'applet se charge en asynchrone : les commandes ne valent
qu'une fois `appletOnLoad` appelé, et c'est lui qui livre l'objet d'API. Les
commandes désignant l'applet par son nom (`ggbApplet0.evalCommand(…)`), on lie
ce nom-là à l'API reçue plutôt que d'attendre la globale que l'applet finit par
poser — `new Function(cfg.id, cfg.commands)(api)`.

**Reste la correction**, non faite : `anstype/geogebra` fait 1128 lignes de
scénarios, et 17 exercices portent `replytype=geogebra`.

Une observation de côté, depuis traitée : `_module_confparm_defaults` ne lisait
que `!default confparm<N>=…`, pas `!set`. Pour ce module-ci cela ne changeait
rien — `confparm1` restait vide et `val9` retombait sur 1, la valeur même que
le `!set` impose — mais 9 modules du corpus emploient cette forme, et
`oef-resoudre.fr` y déclare `!set confparm1=Z`. Ses cinq exercices tiraient
donc des nombres positifs là où le module demande des relatifs. Les deux formes
sont lues désormais, `!set` l'emportant.

### Ce qui a été fait depuis la version précédente de ce document

`chemeq_tex`, `chemeq_mass` et l'équilibrage (`chemeq_equilibrium`) sont portés
— cf. `core/oef/def_engine/chemeq.py`, dont les sorties sont confrontées au
binaire du dépôt. `!while` l'est également, ainsi que `units-filter` (arrondi),
`!increase`, `!varlist`, `!getdef` et le `!read` des slib.
