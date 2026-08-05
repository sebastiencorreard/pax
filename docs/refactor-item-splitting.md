# Découpage des listes WIMS : analyse et programme de refactorisation

*Établi le 2026-08-02, à partir de la lecture de `wims/src/Lib/liblines.c`,
`wims/src/calc.c`, `wims/src/compare.c`, `wims/src/evalue.c` et des scripts
`anstype/` de WIMS, avec l'inventaire complet des découpeurs de
`backend/core/oef/`.*

*Le programme est **terminé** (§3bis) : le §1 décrit l'état d'avant, gardé
parce qu'il dit pourquoi les retouches locales ne pouvaient pas converger.*

## 1. Le constat qui motive la refactorisation

Le moteur PAX comptait **11 fonctions de découpage nommées** et
**26 `re.split` ad hoc** rien que dans `def_engine/__init__.py`, plus des
variantes dans `compare.py`, `slib.py`, `engine.py` et `evaluator.py`. Chaque
bug corrigé cette session (`isitemof`, `positionof`, `randitem`,
`distribute`, `listuniq`, `itemcnt`, colonnes de matrices…) a ajouté sa
protection de crochets ou son cas spécial, sans faire converger l'ensemble.

Trois tentatives de correction « fidèle au source » ont été **annulées** parce
qu'elles cassaient ailleurs :

| Tentative | Juste en soi | Cassait | Pourquoi |
|---|---|---|---|
| `itemcnt` protège les crochets | oui (`find_item_end`) | `oefstat/mean` | recevait le `slib_weight` tabulé produit par `makelist` |
| `makelist` joint par virgules | oui (`_values`) | *(fausse alerte : `symax2` était une correction)* | — puis validée **avec** `itemcnt` |
| la virgule prime sur la tabulation | oui (`strparstr`) | `moles.fr/nl`, `mouvrel.fr` | reçoivent le `slib_out` tabulé produit par `_eval_value` |

Le motif est toujours le même : **les divergences vont par paires
producteur/consommateur**. Un producteur PAX émet des tabulations que WIMS
n'émettrait pas ; un consommateur PAX les redécoupe. Corriger un seul côté
casse l'autre. C'est pourquoi les retouches locales ont atteint leur limite.

## 2. La sémantique WIMS — vérité terrain

### 2.1 L'axiome central

> **La tabulation n'est jamais un séparateur dans WIMS.**

Aucune primitive de `liblines.c` ne mentionne `\t`. Les tabulations présentes
dans les valeurs des `.def` (elles y encodent les retours à la ligne du
source OEF — ce sont les fichiers *de WIMS lui-même*, qui les exécute tels
quels) sont des caractères ordinaires : conservées à l'intérieur d'un item,
élaguées à ses bords comme n'importe quel blanc par `fnd_item`.

Corollaire : **toute prise en compte de `\t` comme séparateur dans PAX est
une compensation**, apparue pour rattraper un producteur lui-même divergent.
La liste des directions d'`oefmolecule` (`0,r,u,…,rru,<TAB>ull,…`), le
`,<TAB>` des listes multi-lignes, la « ligne blanche qui n'est pas un item » :
tous ces cas se dissolvent d'eux-mêmes une fois l'axiome appliqué, parce que
la virgule découpe et que le trim d'item avale la tabulation résiduelle.

### 2.2 Les primitives (liblines.c)

| Primitive | Sémantique exacte | Pièges à reproduire |
|---|---|---|
| `find_matching(p, c)` | cherche `c` en maintenant **trois compteurs simultanés** `()[]{}` ; un fermant qui rend un compteur négatif doit être `c` avec les deux autres ≤ 0, sinon `NULL` | `[a)b]` → NULL dès `)` ; cas spécial `c='|'` (récursif) |
| `strparstr(p, sep)` | `sep` à profondeur 0, paires sautées via `find_matching` | **repli** : sur ouvrant non apparié → `strstr` naïf **depuis le début** ; rien trouvé → fin de chaîne |
| `find_item_end` | `strparstr(p, ",")` | l'unique définition d'une frontière d'item |
| `itemnum(p)` | compte par `find_item_end` ; `""` → 0 ; **les items vides comptent** (`a,,b` → 3, `a,` → 2) | |
| `fnd_item(p, n, bf)` | n-ième segment, **élagué des blancs aux deux bords** (`find_word_start` + trim arrière) | l'intérieur n'est pas touché : `[x<TAB>y]` garde sa tabulation |
| `cutitems` | `_cutit_(…, find_item_end, tag=3)` : tous les items, élagués | conserve les items vides |
| `itemchr(list, w)` | appartenance par **recherche de sous-chaîne** avec frontières : précédé de début-ou-virgule (blancs ignorés), suivi de fin-ou-virgule (blancs ignorés) | **sans** protection de crochets, **sans** égalité item-à-item — c'est `strstr` encadré |
| `linenum` / `fnd_line` | `\n` uniquement ; le `\n` final ne crée pas de ligne ; un `\n` initial crée une première ligne vide ; `fnd_line` **n'élague pas** | |
| `rows2lines(p)` | ne fait rien si un `\n` existe déjà ; sinon `;` de profondeur 0 → `\n`, en protégeant crochets **et entités HTML** (`&alpha` ≤ 14 lettres, `&#nnn` ≤ 6 chiffres) ; renvoie le nombre de conversions (0 ⇒ l'appelant retombe souvent sur les lignes) | déjà bien porté par `_split_rows_by_semi` |
| `lines2rows(p)` | chaque `\n` → `;`, sans protection | |
| mots | blancs (`find_word_start/end`) | |

### 2.3 Les producteurs : tous joignent par virgule

Vérifié un à un dans `calc.c` :

| Commande | Découpe l'entrée | Joint la sortie | Notes |
|---|---|---|---|
| `!makelist` / `!values` (`_values`) | — | `,` (`if(pp>p) *pp++=','`) | jamais de « lignes » : `v,-v for…` reste plat |
| `!shuffle` (`calc_randperm`) | liste ssi `find_item_end` trouve une virgule, sinon **`evalue`** → permutation de 1..n | `,` | conserve les items vides ; pose `wims_shuffle_order` (non implémenté dans PAX) ; options `even`/`odd` |
| `!sort` | items→`,` mots→` ` lignes/rows→`\n` (rows convertis d'abord) | idem entrée | pose `wims_sort_order` |
| `!listuniq` / `listintersect` / `listunion` / `listcomplement` | `cutitems` | `,` | ignorent les items **vides** ; dédoublonnage via `itemchr` (donc sous-chaîne encadrée, pas égalité) |
| `!nonempty items/lines/rows` | primitives idoines | `,` / `\n` / `;` | rows : si `rows2lines` rend 0 → bascule lignes |
| `!item N of` (`_blockof`) | `itemnum`/`fnd_item` | **`", "`** (virgule-espace) | plage `to`/`..`, liste d'indices, négatifs ; hors bornes ignorés |
| `!positionof item X in L` (`_pos`) | `fnd_item` | positions jointes par `,` (**toutes** les occurrences) | comparaison `strcmp` strict avec l'item élagué |
| `!append item X to L` | — | `,` | |
| `isitemof` (compare.c r=5) | `itemchr` | — | identique à la règle du dédoublonnage |
| concaténation `a=$x,$y` (`substit`) | — | — | **aucun traitement** : substitution textuelle pure, les tabulations internes survivent |

### 2.4 Ce que ça explique rétroactivement

- **`mathelexikon`** : `val105 = !makelist r x for…` → tabulé par PAX → le
  `isitemof` (aligné, lui) n'y trouvait rien. Producteur fautif, consommateur
  corrigé : la paire s'est déchirée. Résolu depuis que `makelist` joint par
  virgules — le correctif tab de `compare.py` est devenu une compensation morte.
- **`moles.fr` / `mouvrel.fr`** : `slib/triplerelation/tabular` finit par
  `slib_out= $slib_table, $slib_reply, $slib_replies, $slib_t` — concaténation
  par virgules. Le cas spécial de `_eval_value` (« un morceau contient `,` et
  `<` → joindre par tabulations ») la transforme, et le `!item N of $val8` du
  def ne retombe sur ses pattes que grâce à la priorité tabulation. **Dans
  WIMS, ce `!item` fonctionne parce que `$slib_table` ne contient pas de
  virgule de profondeur 0** — vérification à faire sur la table générée par
  PAX (point ouvert §5.1).
- **`lewis`** : la tabulation cosmétique de `val24` le privait de 8 entrées
  d'atomes ; l'espace substitué aux tabulations internes fusionnait ses
  commandes flydraw. Les deux disparaissent sous l'axiome (§2.1) : la virgule
  découpe, `fnd_item` élague le `<TAB>` de bord, l'interne est conservé tel
  quel pour flydraw.

## 3. Inventaire PAX et verdicts

*État au 2026-08-02, après les phases 3 et 4 : les onze découpeurs ont fondu
en un seul module. Le tableau garde la trace de ce que chacun est devenu.*

| Découpeur | Devenu | Note |
|---|---|---|
| `_split_items` | `wl.cutitems` | supprimé (phase 4a) |
| `_split_wims_items` / `_split_list_items` | `wl.cutitems` | supprimés ; le `;` n'était pas une frontière d'item |
| `_list_items` | `wl.cutitems` filtré | commandes ensemblistes |
| `_split_protected` | — | supprimé : les colonnes passent par `rows2lines` + `!item` |
| `_split_rows` | `wl.cutrows` | supprimé (phase 4a) |
| `_split_rows_by_semi` | `wl.rows2lines` | supprimé ; il coupait le `;` même en présence de `\n` |
| `_split_items_protected` (`compare.py`) | `wl.itemchr` | la branche tab était une compensation morte |
| `_split_top_level_commas` (×2) | `wl.cutitems` | dédupliqué (phase 4b) |
| `_split_correspond_column` | `wl.cutitems` non vides | l'heuristique `<img>` + tabulation n'a plus d'objet |
| `_select_rows` / `_select_cols` | `_blockof` | doublaient le sélecteur du C |
| `_blockof` | port fidèle | plages `to`/`..`, listes d'indices, négatifs, hors-bornes sautés |
| `re.split` ad hoc de sémantique liste | `wl.cutitems` | restent les vrais locaux (tailles `LxH`, `oefsteps`…) |

Compensations retirées, toutes mesurées : priorité tabulation de
`_split_items`/`_split_rows`/`_resolve_indexed2`, filtre « ligne blanche » de
`itemcnt`, branche tab de `compare.py`, `\t→\n` de `_eval_value`,
`_COMMA_VARLIST_RE`, `\t→,` de la médiane, `\t→` espace du blob JSXGraph,
priorité tabulation des `!for … in …` (moteur, slib, `!makelist`) et du
`\linkedranditem`.

## 3bis. État d'avancement (2026-08-02)

| Phase | État | Effet corpus (12 897 rendus, 3 graines) |
|---|---|---|
| 0 — socle `wims_lists` + 53 tests | ✅ | 0 différence |
| 1a — `listuniq`, `listintersect`, `listcomplement` | ✅ | 0 valeur, 6 énoncés |
| 1b — `nonempty`, `append`, `sort` | ✅ | 383 valeurs, 1 vidée (déjà fausse) |
| 1c — `shuffle` | ✅ | 470 valeurs, 9 palettes remplies |
| 1d — `randitem` | ✅ | 116 valeurs, 0 perte |
| 2 — `_split_items`, `_resolve_indexed1`, chute de la priorité tab | ✅ | 579 valeurs, 46 remplies, 0 vidée |
| 3a — sortie GP brute + `isitemof`/`positionof` sans normalisation | ✅ | 86 valeurs (les espaces inventés disparaissent) |
| 3b — `!itemcnt` = `itemnum` | ✅ | **0 différence** |
| 3c — lignes de matrice (`!row`, `!rowcnt`, `!randrow`) | ✅ | **0 différence** |
| 3d — `_split_wims_items`/`_split_list_items` = `cutitems` | ✅ | **54 segments `correspond` retrouvés** (18 exercices) |
| 3e — `$(v[l;c])` = `!row` + `!column` | ✅ | +26 et +14 champs (`wurzel2`, `gauss_summe`), −24 sur la famille `chemeq` |
| 3f — colonne de `correspond` sans heuristique | ✅ | 0 différence |
| 3g — `!makelist … for x in` = `cutfor` | ✅ | 0 différence |
| 3h — `!for … in` d'un slib = `cutfor` | ✅ | diff contenu dans la famille `chemeq` |
| 3i — dernières tabulations de `slib.py` | ✅ | 0 valeur ; 380 énoncés (blob JS) |
| 4a — fusion des découpeurs dans le socle | ✅ | 82 valeurs, palettes `clickfill` réparées |
| 4b — déduplication de `_split_top_level_commas` | ✅ | 0 différence |
| 4c — derniers `re.split` tabulés | ✅ | 0 différence |

**Le programme est terminé.** 762 tests, sentinelles vertes
(`scripts/sentinelles.py`), 0 réponse perdue et 0 valeur vidée hors famille
`chemeq` sur l'ensemble des phases 3 et 4.

**L'instrument a été complété d'abord** (le premier travail de la phase 3) :
`corpus_state.py` capture désormais le nombre de segments par type et
l'appariement `group-open`/`group-close`, et la comparaison en fait deux
verdicts bloquants. C'est lui qui a montré les 18 `correspond` évanouis, que
le hash d'énoncé signalait sans les nommer. Référence de branche : 60 rendus
au HTML déséquilibré (20 exercices × 3 graines), antérieurs au programme.

**Piège d'édition à éviter** : remplacer une méthode en scannant jusqu'au
prochain `    def ` avale le décorateur `@staticmethod` de la méthode
suivante. Ça a produit 53 échecs de tests attribués à tort à la sémantique.

## 4. Programme de refactorisation *(exécuté)*

Chaque phase = un commit, avec le protocole de validation du §5 exécuté
avant/après. Ne **jamais** mélanger deux phases dans un commit : c'est
l'enseignement des trois annulations — et ce qui a permis, à la phase 3e,
d'attribuer sans hésiter une régression au bon changement.

### Phase 0 — Module socle `def_engine/wims_lists.py`

Transcrire les primitives du §2.2, chacune avec sa référence C en docstring :
`find_matching`, `strparstr`, `find_item_end`, `itemnum`, `fnd_item`,
`cutitems`, `itemchr`, `linenum`/`fnd_line`, `rows2lines`/`lines2rows`.
Tests unitaires exhaustifs transcrits du C, y compris les pièges : repli
`strstr` sur crochets non appariés, items vides comptés, trim de bords
seulement, entités HTML de `rows2lines`, `\n` final/initial de `linenum`,
frontières `itemchr` (et son absence de protection). **Aucun appelant migré**
dans cette phase : le corpus doit être strictement inchangé.

### Phase 1 — Producteurs

Migrer vers la sortie virgule. **L'ordre suit les chemins de données, pas les
rôles** : `makelist` doit précéder `itemcnt`, et `shuffle` ne peut passer
qu'une fois les producteurs de tabulations qui l'alimentent déjà migrés. Un
producteur dont le consommateur n'est pas prêt casse le corpus — vérifié.

1. `listuniq`/`listintersect`/`listcomplement` : dédoublonnage par `itemchr`
   (aujourd'hui : égalité normalisée — divergence supplémentaire) ;
2. `nonempty`, `append item`, `sort items` ;
3. `shuffle` : virgule, **conservation des items vides**, décision
   liste/nombre par `find_item_end` + `evalue` (pas `.isdigit()`), suppression
   du `,(?![^(]*\))` ; poser `wims_shuffle_order` ;
4. ~~`_eval_value`~~ — **erreur de classement, corrigée à l'exécution** : ce
   n'est pas un producteur mais une **compensation** de la priorité tabulation
   de `_split_items`. Le retirer en phase 1 vide la palette de `lewis` et casse
   les tableaux JSXGraph de `cof` (`test_four_boards_in_inline_group`). Il ne
   peut tomber qu'en phase 3, après les consommateurs ;
5. auditer `slib.py` (`.split("\t")` ligne 624, `replace("\t", ",")` ligne
   442…) : chacun est soit un port fidèle d'un `!translate` du slib WIMS,
   soit une compensation.

### Phase 2 — Consommateurs

`itemcnt`, `item`, `randitem`, `randperm`, `positionof`, `isitemof`,
`embraced`, `distribute items`, l'indexation `$(var[n])` / `$(m[l;c])`
(`_resolve_indexed1/2`, `_select_cols`, `_select_rows`), `row`/`column`
(colonnes = `rows2lines` + items, comme `calc_columnof`). Chacun bascule sur
`wims_lists` ; la priorité tabulation ne tombe **qu'ici**, une fois tous les
producteurs passés.

### Phase 3 — Suppression des compensations

La liste du §3, une par une, corpus à l'appui. Une compensation qui ne peut
pas tomber signale un producteur oublié : revenir en phase 1, ne pas rustiner.

### Phase 4 — Nettoyage

Fusionner les 11 découpeurs dans `wims_lists`, dédupliquer
`_split_top_level_commas`, remplacer les `re.split` de sémantique liste.

Fait en trois commits (4a, 4b, 4c). `docs/def-engine-commands.md` n'a rien
demandé : c'est un tableau de couverture des commandes, sans sémantique de
séparateur.

## 5. Protocole de validation (leçons payées cette session)

**Reprendre le travail après une interruption** — capturer une référence
*avant* toute modification, puis comparer :

```bash
docker compose exec -T backend sh -c "cd /app && python3 scripts/corpus_state.py /tmp/ref.json"
# … modifications …
docker compose exec -T backend sh -c "cd /app && python3 scripts/corpus_state.py /tmp/apres.json && \
    python3 scripts/corpus_state.py /tmp/ref.json /tmp/apres.json"
```

Comptez ~3 minutes par capture (12 897 rendus, 3 graines). Ces fichiers vivent
dans le `/tmp` du conteneur : ils **disparaissent à chaque reconstruction
d'image**, il faut donc toujours en refaire un plutôt que se fier à un ancien.

La comparaison rend trois verdicts bloquants : une valeur **vidée**, un
**segment perdu** (un type de widget dont le compte recule — c'est ainsi que
les 18 `correspond` évanouis se sont montrés) et un **groupe déséquilibré**
(`group-open`/`group-close` mal appariés). Les sentinelles se lisent dans la
même capture :

```bash
docker compose exec -T backend python3 /app/scripts/sentinelles.py /tmp/apres.json
```

1. **Comparer les valeurs, jamais les comptes.** Deux régressions (moyenne de
   `mean.def`, `val14` de `concentration1`) étaient invisibles au nombre de
   réponses. Référence = dump `{fichier#reply: expected}` + `options.choices`
   + hash du `statement_html`, sur **au moins 3 graines** (42, 1135432845,
   586627288).
2. **Un `expected` qui rétrécit n'est pas une perte** : celui de `symax2`
   contenait son vivier, parti à sa place dans `options.choices`. Toujours
   regarder où le contenu est allé avant de conclure.
3. **Exercices sentinelles**, vérifiés par `scripts/sentinelles.py` :
   `oefstat/mean` (3.973684211), `transform/symax2` (menu à 20 options),
   `oefpython/bouclefor1` (rang 3), `moles.fr/concentration1` (`val14` en
   mol), `mathelexikon/Declinaisons` (13 champs), `oefmolecule/lewis`
   (7 champs, 18 étiquettes).
4. **Après tout changement moteur** : `docker compose restart backend` +
   purge `pax:render:*` avant le moindre contrôle navigateur (deux faux
   verdicts cette session).
5. Tests : `pytest tests/core/oef/` ≥ 762 ; les tests qui figent une
   invention de PAX (séparateur tabulé de `makelist`, ancien `itemcnt`) se
   réécrivent avec référence C en docstring, comme déjà fait.

### 5.1 Points ouverts (mis à jour à la fin du programme)

Tranchés en cours de route :

- le blob JSXGraph de `_COMMA_VARLIST_RE` : le cas spécial n'avait aucun
  équivalent WIMS, il est tombé sans dommage (phase 3e) ;
- la sortie de GP : WIMS ouvre `gp` sur `default(output,0)`
  (`src/Interfaces/pari.c`), donc **sans espace de présentation**. C'est la
  correction qui a permis à `isitemof` de redevenir `itemchr` (phase 3a).

Restent ouverts, hors périmètre du découpage :

- **`!exec chemeq` n'est pas implémenté** — `!exec` ne connaît que maxima et
  pari. Les 7 exercices de `equilibrium`/`chemavance1` qui en dépendent
  affichent une équation vide (`\(0\)`, `NaN`) quoi qu'on fasse ; tout diff
  corpus qui s'y limite est du bruit. Les porter suppose d'écrire un
  équilibreur d'équations chimiques.
- **`imgrename(...)` n'est pas implémenté** — 19 `.def` l'utilisent comme
  *fonction* dans une expression (`!makelist imgrename($val1/ttt width=…)
  for ttt in …`), là où PAX ne connaît rien de ce nom. Le contrôle navigateur
  l'a mis au jour sur `oefmolecule/corresnom` : son widget `correspond`
  réapparu affiche `imgrename(pax-img:_/ch4o/ch4o.png width=150)` en clair au
  lieu des modèles moléculaires. Défaut antérieur au programme, simplement
  rendu visible par la réparation du widget.
- **Le séparateur de sortie de `!item`** : `_blockof` joint par `", "`
  (virgule-espace, `calc.c`), nous par `","`. Sans effet sur un redécoupage
  (`fnd_item` élague), visible à l'affichage et dans les `expected`. À
  mesurer isolément.
- **`!positionof`** : `_pos` renvoie **toutes** les positions jointes par `,`
  et la chaîne **vide** quand l'item est absent ; nous renvoyons la première
  et `"0"`. Même remarque : une mesure isolée avant de bouger.
- `wims_shuffle_order` / `wims_sort_order` : toujours non implémentés.
- La table HTML de `slib/triplerelation/tabular` : la question des virgules de
  profondeur 0 n'a plus d'urgence depuis que `moles`/`mouvrel` passent sans
  hack, mais elle n'a pas été tranchée.

## 6. Bilan

Le gain visé est atteint : **onze découpeurs et deux copies d'un même
helper ont fondu en un module**, `def_engine/wims_lists.py`, chaque primitive
portant sa référence C. Les paires producteur/consommateur ont disparu avec
eux — c'est ce qui explique que dix des dix-huit étapes ne changent **rien**
au corpus : une compensation dont le producteur est déjà corrigé n'attrape
plus rien, et c'est la seule preuve solide qu'on pouvait la retirer.

Débloqués au passage : `lewis` (18 étiquettes), `moles`/`mouvrel` (sans hack),
18 exercices `correspond` qui n'affichaient aucun widget, `wurzel2_beweisen`
(26 champs) et `gauss_summe` (14), les palettes `clickfill` de
`OEFevalwimspyth`/`OEFpythagore2`, celles de `notation4`.
