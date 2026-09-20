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
dans `backend/tests/known_failures.py` (`WIDGETS_ORPHELINS`) ;
`tests/test_exercises_widgets.py` les laisse passer en xfail.

#### Par où le `\` échappe au moteur

`_render_embed` (`def_engine/__init__.py:5211`) reconnaît la référence par
**trois filtres successifs**, et le `\` les manque tous les trois :

| Filtre | Ligne | Motif | `\reply1` | `\choice1` |
|---|---|---|---|---|
| choix embarqué | 5270 | `re.fullmatch(r"c[a-z]*(\d+)", ref)` | — | **rate** (commence par `\`) |
| préfixe de réponse | 5289 | `ref.startswith(("reply","rep","r"))` | **rate** | rate |
| type de réponse | 5341 | `re.match(r"^r(?:eply)?(\d+)$", ref)` | **rate** | rate |

Trois conséquences enchaînées, toutes silencieuses :

1. `reply_type` reste la **chaîne vide** — donc aucune des branches par type
   (radio, checkbox, mark, draw…) ne s'ouvre ;
2. `self._touched_replies.add(...)` n'est jamais appelé : la réponse passe pour
   non embarquée ;
3. la fonction tombe dans le champ de saisie générique, qui écrit `ref` **tel
   quel** dans l'attribut `name` — `\` compris — et lui donne
   `_TAILLE_DEFAUT.get("", 30)`, d'où les 30 caractères observés.

#### Le dégât n'est pas le même selon le type de la réponse

C'est le point à retenir, et il sépare les sept en deux groupes.

**Les trois `radio` — `TVF2`, `TVF22`, `radioactivite2` : gênant, pas bloquant.**
Leur palette est composée ailleurs (`_prepare_choices`, à partir de
`choicelist<n>`) et voyage dans `answers[0].options["choices"]` ; le front la
rend sous l'énoncé. L'exercice reste **répondable et notable**. Le seul dégât
est un champ de saisie vide de 30 caractères posé au milieu de la phrase.

```
TVF2            options: {'choices': ['non', 'oui', 'Je ne sais pas']}
radioactivite2  options: {'choices': ['\(\text{beta}\)+', '\(\text{beta}\)-', '\(\text{alpha}\)', 'Je ne sais pas']}
```

**Les quatre `checkbox` — `expression1`, `2`, `3`, `5` : insolubles.**
Pour `checkbox`, la palette est construite **par la branche de l'embed
elle-même**, qui lit `replygood<n>` sous la forme `positions;choix…`. Cette
branche ne s'ouvre jamais. Résultat : `options` ne porte **aucun `choices`**, et
la liste à cocher n'existe nulle part.

```
expression1  type=checkbox  expected='2,3,5,7,8'  options={'option':'shuffle','precision':1000.0,'computeanswer':'yes'}
                                                  → pas de clé 'choices'
```

Et comme `reply1` n'a pas été marquée embarquée (conséquence 2 ci-dessus), le
repli par réponse d'`oef/form.phtml` s'ajoute par-dessus : un second champ, de
14 caractères, sous « Entrez votre réponse : ». L'élève voit donc **deux boîtes
de texte** et doit y taper `2,3,5,7,8` — les **positions** des bonnes
propositions dans une liste qu'on ne lui montre pas.

```
expression1  énoncé: input '\reply1' (30)  +  input 'reply1' (14) sous « Entrez votre réponse : »
```

**Et la suite lente est verte dessus.** Les quatre ne figurent dans aucun
ensemble d'échecs de notation — seulement dans `WIDGETS_ORPHELINS`, qui ne
couvre que le rendu. `test_correct_answer_scores_1` écrit `2,3,5,7,8` dans le
champ de secours, le checker l'accepte, le test passe :

```
PAX_TEST_CORPUS=H5/analysis pytest -m slow tests/test_exercises_check.py \
  -k 'expression1 or expression2 or expression3 or expression5 or expression4'
→ 15 passed
```

C'est le piège déjà nommé deux fois ailleurs (cf. `TODO.md` § V.2) : un test qui
soumet l'attendu dans un champ que l'élève ne peut pas remplir utilement passe
**à vide**. Il mesure le checker, pas l'exercice.

#### Trois suites possibles, à ne pas engager sans décision

- **S'en tenir là.** Défendable pour les trois `radio` — le champ mort est laid,
  rien n'est faussé. Intenable tel quel pour les quatre `checkbox`, qu'un élève
  ne peut pas résoudre.
- **S'aligner vraiment sur `embed.phtml`** : n'émettre aucun widget quand le
  premier caractère de la référence n'est ni `r` ni `c`. C'est la fidélité
  stricte, et elle supprime le champ mort — mais elle laisse les quatre
  `checkbox` sans palette, donc toujours insolubles (comme chez WIMS). Changement
  de moteur, à mesurer sur tout le corpus : d'autres références mal formées que
  le relevé du 18-09 n'a pas isolées pourraient basculer.
- **Consigner les quatre `checkbox` en `XFAIL_CORRECT_SCORE`**, quelle que soit
  la suite retenue. C'est indépendant du reste et ça ferme le faux vert : la
  suite ne doit pas déclarer sain un exercice qu'on sait insoluble.

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
