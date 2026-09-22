# Commandes WIMS `.def` — état d'implémentation

Analyse sur les 2270 fichiers `.def` du corpus PAX (`ressources/`).

| Commande | Occurrences | Statut |
|---|---|---|
| `!exit` | 369 | ✅ terminateur de section |
| `!insmath` | 226 | ✅ |
| `!endif` | 214 | ✅ |
| `!if` | 202 | ✅ |
| `!goto` | 127 | ✅ (ignoré / skip) |
| `!randint` | 115 | ✅ |
| `!read` | 107 | ❌ lit des fichiers du système WIMS (non disponibles) |
| `!exec` | 85 | ✅ maxima et pari |
| `!randitem` | 80 | ✅ |
| `!replace` | 68 | ✅ styles `word`/`item`/`line`/`char`, avec ou sans `number` (voir plus bas) |
| `!texmath` | 50 | ✅ (identité) |
| `!set` | 50 | ✅ (ignoré — titre déjà extrait) |
| `!translate` | 47 | ✅ |
| `!item` | 36 | ✅ |
| `!readproc` | 35 | ⚠️ placeholder vide |
| `!else` | 33 | ✅ |
| `!shuffle` | 29 | ✅ |
| `!next` | 25 | ✅ terminateur de boucle |
| `!for` | 25 | ✅ |
| `!append` | 24 | ✅ |
| `!lower` | 20 | ✅ |
| `!nonempty` | 17 | ✅ |
| `!rawmath` | 15 | ✅ (identité — toujours précédé de `!exec maxima`) |
| `!ifval` | 12 | ✅ |
| `!trim` | 11 | ✅ |
| `!random` | 9 | ✅ |
| `!itemcnt` | 8 | ✅ |
| `!row` | 7 | ✅ |
| `!values` | 6 | ✅ |
| `!nosubst` | 4 | ✅ |
| `!sort` | 2 | ✅ (fractions incluses) |
| `!randrow` | 2 | ✅ |
| `!positionof` | 1 | ✅ |
| `!listuniq` | 1 | ✅ |

## Commandes implémentées mais absentes du corpus local

Ces commandes ont été implémentées parce qu'elles apparaissent dans un corpus
WIMS plus large, mais sont rares ou absentes dans `ressources/` :

`!makelist`, `!mathsubst`, `!declosing`, `!nospace`, `!getopt`, `!getdef`,
`!embraced`, `!word`, `!column`, `!charcnt`

## Couverture

- **33/34 commandes implémentées** (97 %)
- **2115/2173 exercices compilés rendent correctement** (97,3 %)
- **Bloquant structurel** : `!read` — accès au système de fichiers WIMS
  (fichiers `.rec`, données tabulaires) non disponibles hors installation WIMS


## Nécessaire d'implémenter `!read` ?

`!read` est déjà partiellement implémenté — le moteur distingue trois variantes :


| Variante | Classe | Statut |
| :--- | :--- | :--- |
| `!read oef/embed.phtml reply1,…` | ReadEmbed | ✅ rend les champs de saisie |
| `!read oef/draw.phtml …` | ReadDraw | ✅ génère un graphique inline |
| `!read oef/special.phtml …` | ReadProc | ✅ effets de bord (ins_url, etc.) |
| `!read autrefichier.def` | — | ❌ non géré |
| `!read primitives.phtml …` | — | ❌ ignoré |

Répartition dans H4/ (les exercices importés)
| Cible | Occurrences | Situation |
| :--- | :--- | :--- |
| `oef/embed.phtml` | 104 | ✅ déjà géré |
| `primitives.phtml` | 2 | Module de doc (liens), pas un exercice — ignorable |
| `listeprol.def` | 1 | Seul cas d'inclusion .def dans .def |

Conclusion : 
Non, ce n'est pas nécessaire pour faire tourner les exercices H4/. Les 104 !read oef/embed.phtml sont traités. Il resterait un seul cas d'inclusion .def→.def dans tout H4/ (espcube.fr/var.def qui charge listeprol.def).                  

Plan si on voulait quand même l'implémenter
Ce serait l'inclusion de fichier .def dans le contexte courant (même ctx, même état d'exécution) :
1. Parser — reconnaître !read <path> quand la cible se termine par .def → nouveau type d'instruction ReadDef(path)
2. Résolution de chemin — relatif au répertoire du .def en cours d'exécution (self._def_path.parent / path), avec garde contre les inclusions circulaires (set de chemins déjà chargés)
3. Exécution — charger le fichier cible, le parser avec le même DefParser, puis passer ses instructions à _exec_block avec le ctx courant (les variables définies dans le fichier inclus sont visibles dans le parent, et vice-versa)
4. Limites — les labels (!goto) ne traversent pas les frontières de fichiers ; les sections question:/hint:/solution: du fichier inclus sont ignorées (seuls les blocs d'initialisation sont utiles)

Ça serait ~40 lignes dans __init__.py. Mais pour le corpus actuel, ça ne débloquerait qu'un seul exercice (espcube.fr), donc le rapport effort/impact est faible. Je recommande de ne l'implémenter que si tu constates que des exercices importants sont cassés à cause de ça.

## `!replace` — quatre styles, et le piège du `number`

`calc_replace` (`calc.c`) lit dans l'ordre : `internal`, puis un **style**
(`word`, `item`, `line`, `char`), puis `number`, puis `… by … in …`.

- sans style, c'est un remplacement de texte — et, sauf `internal`, un
  remplacement **sed** dès que l'un des motifs porte `\[^.*$` ;
- avec un style et sans `number`, ce sont les **occurrences** de l'objet
  cherché, frontières comprises (`itemchr`, `wordchr`, `linechr`) ;
- avec `number n`, c'est le n-ième objet, compté de 1, ou depuis la fin s'il
  est négatif ; hors bornes, le texte est rendu intact.

La zone remplacée d'un item va du caractère qui suit la virgule précédente
jusqu'à celui qui suit la suivante : `!replace item number 2 by X in a, b ,c`
rend `a,X,c`, blancs compris.

Porté le 2026-09-22 (`wims_lists.replace_objet`). Avant cela, la forme tombait
dans le remplacement de texte, qui cherchait littéralement `item number 1`
dans la cible : **591 `!replace item number` du corpus ne faisaient rien**, en
silence. `challenge2005b/triangle` proposait six étiquettes valant toutes `0`,
et les arbres d'`oefprobatree` n'avaient aucune branche.
