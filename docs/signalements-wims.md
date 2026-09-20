# Signalements à WIMS

Registre des défauts qui vivent **chez WIMS**, non chez nous : une faute dans
une source OEF du corpus, ou dans un script de la distribution. PAX les
**reproduit fidèlement** — c'est la règle du projet — et ne les corrige pas.
Deux raisons : on n'édite jamais un `.def` à la main (le fichier est compilé,
la retouche serait emportée au prochain import), et rendre un exercice
« utilisable » là où WIMS ne le rend pas serait s'éloigner de la référence, non
s'en rapprocher.

Ce fichier sert à deux choses : garder le dossier prêt entre deux sessions, et
empêcher qu'un futur passage sur le corpus reprenne le diagnostic à zéro puis
conclue à un bug de PAX.

Chaque entrée porte son état : **à signaler**, **signalé le …**, ou **corrigé
en amont le …**.

---

## 1. Sept exercices portent un `\` de trop dans leur `\embed{}` — *à signaler*

*Relevé le 2026-09-18, vérifié le 2026-09-20.*

### Les fichiers

| Source OEF | Ligne | Écrit | Cible déclarée |
|---|---|---|---|
| `H5/analysis/demarrer1ereS.fr/src/expression1.oef` | 40 | `\embed{\reply1}` | `\answer{}` l. 42 |
| `H5/analysis/demarrer1ereS.fr/src/expression2.oef` | 47 | `\embed{\reply1}` | `\answer{}` |
| `H5/analysis/demarrer1ereS.fr/src/expression3.oef` | 48 | `\embed{\reply1}` | `\answer{}` |
| `H5/analysis/demarrer1ereS.fr/src/expression5.oef` | 49 | `\embed{\reply1}` | `\answer{}` |
| `H5/analysis/oeftablvar.fr/src/TVF2.oef` | 327 | `\embed{\choice 1}` | `\choice{}` l. 335 |
| `H5/analysis/oeftablvar.fr/src/TVF22.oef` | 329 | `\embed{\choice 1}` | `\choice{}` |
| `H6/physics/OEFradioactivite.fr/src/radioactivite2.oef` | 51 | `\embed{\reply1}` | `\choice{}` l. 53 |

Chacun ne déclare qu'**une** réponse, et elle existe bien : la référence ne
pointe pas dans le vide, elle est seulement mal écrite.

### Pourquoi WIMS n'affiche rien

`oef/embed.phtml` résout la référence en quatre temps, et le `\` la fait sortir
dès le premier :

```
l.   4   !set parm=!replace internal \ by $$m_ in $wims_read_parm
l.   7   !set t_=!item 1 of $parm
l. 112   !set n_=!char 2 to -1 of $t_
l. 113   !set t_=!char 1 of $t_
l. 118   !if $t_ notitemof r,c or $n_=$empty
l. 119     !exit
```

La ligne 4 remplace le `\` par `$m_` : `\reply1` devient `$m_reply1`. La ligne
113 ne garde que le **premier caractère** pour en faire le type de référence —
c'est désormais `$`, ni `r` ni `c` —, et la ligne 118 sort sans rien afficher.
Le champ n'est jamais posé, et l'exercice reste sans widget chez WIMS.

Le compilateur, lui, ne s'en émeut pas : il recopie la faute telle quelle dans
le `.def` (`!read oef/embed.phtml \reply1`) et compte quand même l'embed
(`embedcnt=1`). Rien n'avertit l'auteur.

### C'est bien une faute, recopiée

`demarrer1ereS/expression4`, voisin immédiat des quatre autres dans le même
module, écrit la forme correcte :

```
\embed{reply 1,\taille}
```

La faute s'est donc propagée par copie d'un fichier à l'autre, à l'intérieur
d'un module puis d'un module à l'autre.

**Deuxième faute sur `radioactivite2`** : le fichier écrit `\embed{\reply1}`
alors que sa cible est un `\choice{}`. Même sans le `\`, `reply1` ne désignerait
rien — il faudrait `choice 1` (ou `c1`, que `embed.phtml` accepte aussi, ne
lisant que la première lettre et les chiffres du reste). Corriger le `\` seul ne
suffirait pas pour celui-là.

### Ce que PAX en fait aujourd'hui

PAX **ne sort pas** comme WIMS : il pose un widget dont le nom porte le `\`.

```
expression1      énoncé: input '\reply1' (30) + input 'reply1' (14)   answers: reply1 (checkbox)
TVF2             énoncé: input '\choice1' (30)                        answers: reply1 (radio)
radioactivite2   énoncé: input '\reply1' (30)                         answers: reply1 (radio)
```

Ce champ ne figure dans aucune `answers` : le front ne peut ni l'indexer ni le
faire noter — c'est un **widget orphelin**. Les sept sont consignés à ce titre
dans `backend/tests/known_failures.py` (`WIDGETS_ORPHELINS`), avec le même
diagnostic ; `tests/test_exercises_widgets.py` les laisse donc passer en xfail.

Deux suites possibles, **à ne pas engager sans décision** :

- s'en tenir là (position actuelle) : WIMS n'affiche rien, PAX affiche un champ
  mort — l'écart existe mais il n'induit personne en erreur sur la note ;
- s'aligner vraiment sur `embed.phtml` en n'émettant aucun widget quand le
  premier caractère de la référence n'est ni `r` ni `c`. C'est un changement de
  moteur, à mesurer sur tout le corpus : il toucherait potentiellement d'autres
  références mal formées que le relevé du 18-09 n'a pas isolées.

### État du dossier

Prêt à envoyer. Il manque le canal et l'envoi.

---

## 2. Trois templates appellent une slib inexistante — *signalé le 2026-09-11*

Des modules réclament `slib/utilities/env` ou `slib/oefenv` — deux chemins qui
n'existent nulle part, pas même dans la distribution WIMS — là où la slib réelle
est `slib/oef/env` (l'accès à `$(oefenv_<arg>)`). L'appel échoue silencieusement
chez WIMS comme il échouait ici.

Cause racine : les templates `oef.en` et `oef.es`, qui sèment `oefenv` dans tout
module créé à partir d'eux — d'où sa présence jusque dans des modules récents.
`utilities/env` est un idiome plus ancien, hérité d'un module.

Côté PAX, réglé par un alias de chemin (`_ALIAS_SLIB`, commit b13bd76d,
`backend/core/oef/def_engine/slib.py`) : l'appel est réacheminé vers `oef/env`
plutôt que de rester muet. La correction reste à faire en amont, dans les
templates.
