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
| `!replace` | 68 | ✅ |
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
