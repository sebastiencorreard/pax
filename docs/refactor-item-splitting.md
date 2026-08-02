# Découpage des listes WIMS : analyse et programme de refactorisation

*Établi le 2026-08-02, à partir de la lecture de `wims/src/Lib/liblines.c`,
`wims/src/calc.c` et `wims/src/compare.c`, et de l'inventaire complet des
découpeurs de `backend/core/oef/`.*

## 1. Le constat qui motive la refactorisation

Le moteur PAX compte aujourd'hui **11 fonctions de découpage nommées** et
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

| Découpeur | Où | Sémantique actuelle | Verdict |
|---|---|---|---|
| `_split_items` | `__init__.py:1915` | **tab d'abord**, sinon virgules protégées | → `cutitems` (l'axiome supprime la branche tab) |
| `_split_wims_items` | `:1052` | virgule/`;` + entités HTML | fusionner ; le `;` n'est **pas** une frontière d'item dans WIMS (c'est `rows2lines`) — auditer les appelants |
| `_split_list_items` | `:1045` | délègue | fusionner |
| `_list_items` | `:2304` | `_split_items` sur commandes ensemblistes | → `cutitems` |
| `_split_protected` | `:136` | virgule+tab protégées, `_split_protected(r, ";,")` pour colonnes | remplacer : colonnes = `rows2lines` puis items |
| `_split_rows` | `:2011` | `\n` > `;` > **tab** | branche tab = compensation `makelist` ; → `rows2lines` |
| `_split_rows_by_semi` | `:1159` | port fidèle de `rows2lines` ✓ | **socle à conserver** (déplacer) |
| `_split_items_protected` | `compare.py:45` | tab d'abord (correctif `mathelexikon`) | compensation morte → `itemchr` |
| `_split_top_level_commas` | `slib.py:772` + `evaluator.py:747` (dupliqué !) | virgules profondeur 0 | → `find_item_end` (ajouter le repli `strstr`) |
| `_split_correspond_column`, `_split_records` | locaux | spécifiques | garder tels quels |
| 26 `re.split` ad hoc | partout | dont 6× `,(?![^(]*\))` (demi-protection fausse : ne regarde que la parenthèse suivante), 3× `[;\n\r\t]+`, 2× `,|\t` | à remplacer un à un quand ils modélisent des items ; garder les vrais locaux (tailles `LxH`…) |

Compensations identifiées à supprimer *en fin de programme seulement* :
priorité tab de `_split_items`/`_split_rows`, filtre « ligne blanche » du
`itemcnt` tabulé, branche tab de `compare.py`, `\t→\n` de `_eval_value`
(be6c2938), **le cas spécial `_COMMA_VARLIST_RE` tout entier** (WIMS n'a
aucun équivalent : `substit` ne réécrit rien).

## 3bis. État d'avancement (2026-08-02)

| Phase | État | Effet corpus (12 897 rendus, 3 graines) |
|---|---|---|
| 0 — socle `wims_lists` + 53 tests | ✅ | 0 différence |
| 1a — `listuniq`, `listintersect`, `listcomplement` | ✅ | 0 valeur, 6 énoncés |
| 1b — `nonempty`, `append`, `sort` | ✅ | 383 valeurs, 1 vidée (déjà fausse) |
| 1c — `shuffle` | ✅ | 470 valeurs, 9 palettes remplies |
| 1d — `randitem` | ✅ | 116 valeurs, 0 perte |
| 2 — `_split_items`, `_resolve_indexed1`, chute de la priorité tab + compensation `_eval_value` | ✅ | 579 valeurs, **46 remplies, 0 vidée** |
| 3 — compensations restantes (`compare.py`, `_split_rows`, `_split_wims_items`) | ⏳ | |
| 4 — fusion des découpeurs, `re.split` résiduels | ⏳ | |

**Cible atteinte pour `lewis`** : 18 étiquettes (8 atomes, 6 doublets non
liants, les liaisons), 7 attendus sur 7 champs — la composition exacte du
rendu WIMS de référence. Sentinelles toutes vertes ; `concentration1` passe
de `0 Ohm` à `0 mol`.

**Angle mort de l'instrument, constaté** : `corpus_state.py` compare les
valeurs (attendu, palette) et une empreinte d'énoncé, mais ne détecte ni la
disparition d'un segment (un tableau JSXGraph évanoui) ni un HTML déséquilibré
— seuls deux tests unitaires l'ont vu. À compléter avant la phase 3 :
compter les segments par type et vérifier l'appariement `group-open`/
`group-close`.

**Piège d'édition à éviter** : remplacer une méthode en scannant jusqu'au
prochain `    def ` avale le décorateur `@staticmethod` de la méthode
suivante. Ça a produit 53 échecs de tests attribués à tort à la sémantique.

## 4. Programme de refactorisation

Chaque phase = un commit, avec le protocole de validation du §5 exécuté
avant/après. Ne **jamais** mélanger deux phases dans un commit : c'est
l'enseignement des trois annulations.

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
Mettre à jour `docs/def-engine-commands.md`.

## 5. Protocole de validation (leçons payées cette session)

1. **Comparer les valeurs, jamais les comptes.** Deux régressions (moyenne de
   `mean.def`, `val14` de `concentration1`) étaient invisibles au nombre de
   réponses. Référence = dump `{fichier#reply: expected}` + `options.choices`
   + hash du `statement_html`, sur **au moins 3 graines** (42, 1135432845,
   586627288).
2. **Un `expected` qui rétrécit n'est pas une perte** : celui de `symax2`
   contenait son vivier, parti à sa place dans `options.choices`. Toujours
   regarder où le contenu est allé avant de conclure.
3. **Exercices sentinelles** à vérifier nommément après chaque phase :
   `oefstat/mean` (3.97368421053), `transform/symax2` (menu à 20 options),
   `oefpython/bouclefor1` (rang 3, masque `val44`), `moles.fr/concentration1`
   (`val14`=5), `mathelexikon/Declinaisons` (13 champs),
   `oefmolecule/lewis` (7 champs, **18 étiquettes** attendues à terme),
   `oefsuites1S/cvgequot`, `oefstat/baton`, `geo6`/`evolmeth2` (re-tester :
   leurs `replygood` vides relèvent peut-être de cette famille).
4. **Après tout changement moteur** : `docker compose restart backend` +
   purge `pax:render:*` avant le moindre contrôle navigateur (deux faux
   verdicts cette session).
5. Tests : `pytest tests/core/oef/` ≥ 703 ; les tests qui figent une
   invention de PAX (séparateur tabulé de `makelist`, ancien `itemcnt`) se
   réécrivent avec référence C en docstring, comme déjà fait.

### 5.1 Points ouverts à trancher pendant la phase 1

- La table HTML de `slib/triplerelation/tabular` générée par PAX
  contient-elle des virgules de profondeur 0 que celle de WIMS n'a pas ?
  (Si oui, c'est *elle* qu'il faut corriger, pas le join.)
- Le blob JSXGraph cité par le commentaire de `_COMMA_VARLIST_RE` : comment
  WIMS s'en sort-il ? (Probablement : il ne s'en sort pas mieux — vérifier
  l'exercice d'origine avant de supposer un besoin.)
- `wims_shuffle_order` / `wims_sort_order` : implémenter ou documenter
  l'absence (usages corpus à mesurer).

## 6. Estimation

Phases 0–1 : le gros du risque (producteurs = tirages aléatoires déplacés,
donc gros diff de graine à trier). Phases 2–3 : mécaniques si la 1 est
complète. Le gain attendu : ~10 découpeurs → 1 module, disparition des
paires producteur/consommateur, et déblocage connu de `lewis` (18
étiquettes), `moles`/`mouvrel` (sans hack), probablement `geo6`/`evolmeth2`.
