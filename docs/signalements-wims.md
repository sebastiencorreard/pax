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

**Un huitième fichier, à part.** `H6/chemistry/piles.fr/src/piles2.oef` l. 83
écrit `\embed{\(reply1 ,10x20)}` : l'auteur a enveloppé sa référence dans des
délimiteurs mathématiques. Même mécanisme, malformation différente. Il ne
figure pas dans le tableau ci-dessus parce qu'il n'y a rien à y réparer :
l'exercice ne déclare **aucune** réponse (`replycnt=` vide, pas un seul
`replytype`), et il fait partie des `piles`/redox qu'attend le portage de
`chemeq_el`. À mentionner dans le signalement, pas à compter dans les sept.

### Ce que PAX en faisait, et ce qu'il en fait depuis le 2026-09-20

**Avant.** PAX ne sortait pas comme WIMS : il posait un widget dont le `name`
portait le `\`, orphelin de toute `answers` — le front ne pouvait ni l'indexer
ni le faire noter.

```
expression1      énoncé: input '\reply1' (30) + input 'reply1' (14)   answers: reply1 (checkbox)
TVF2             énoncé: input '\choice1' (30)                        answers: reply1 (radio)
```

`_render_embed` reconnaît la référence par trois filtres successifs, et le `\`
les manquait tous les trois : le choix embarqué (`re.fullmatch(r"c[a-z]*(\d+)")`),
le préfixe de réponse (`startswith(("reply","rep","r"))`) et le type
(`^r(?:eply)?(\d+)$`). D'où `reply_type` vide, aucune branche par type ouverte,
`_touched_replies` jamais renseigné, et une chute dans le champ générique qui
écrit `ref` tel quel.

Le dégât n'était pas le même des deux côtés. Les trois `radio` gardaient leur
palette — elle vient de `choicelist<n>`, pas de l'embed — et restaient
répondables. Les quatre `checkbox` étaient **insolubles** : leur palette est
composée par la branche de l'embed, qui ne s'ouvrait jamais, si bien que
l'élève devait taper les rangs (`2,3,5,7,8`) d'une liste qu'on ne lui montrait
pas. Et la suite lente était verte dessus, le test soumettant l'attendu dans le
champ de secours.

**Depuis.** Deux gestes, mesurés sur tout le corpus :

1. **Le `!exit` d'`embed.phtml` est porté** : une référence dont la première
   lettre n'est ni `r` ni `c` (après `!lower` et `!translate a to r`) ne pose
   aucun champ. Sur les 18 947 `!read oef/embed.phtml` du corpus, seules les
   huit à `\` changent de comportement — les 314 références *calculées*
   (`$(val22[$m_t])`) se résolvent avant ce test, ce qui était le vrai risque
   et a été vérifié, non supposé.
2. **La palette d'un `checkbox` sort de la branche d'embed**
   (`_palette_checkbox`, `_case_a_cocher`) et le repli par réponse l'appelle —
   c'est le port de la décision que `oef/formr.phtml` prend en cinq lignes :
   embarqué ou non, il lit `anstype/<type>.input`, et `checkbox.input` y monte
   la palette entière depuis `replygood$i`.

Le second répare **17 réponses `checkbox`** du corpus, dont seulement 4 tenaient
à un `\` : les 13 autres n'ont aucun défaut de source, leur auteur n'avait
simplement pas embarqué la réponse (`oefoptics/qcm1` n'a pas un seul `\embed`).

```
qcm1          avant: input 'reply1' (texte)        après: 5 cases à cocher, 0 champ texte
expression1   avant: '\reply1' + 'reply1' (texte)  après: 10 cases à cocher, 0 orphelin
TVF2          avant: input '\choice1'              après: rien (la palette radio vient d'`options`)
```

Piège payé en chemin : les étiquettes portent du `\(2)`, `\(x -4)` — la forme
WIMS, où `\(` ouvre et une simple parenthèse ferme. `checkbox.input` n'échappe
que la *valeur* (`input_rg2`), jamais le prompt. KaTeX veut un `\)` explicite,
d'où le passage par `_close_inline_math`, comme le fait déjà la palette radio.
Sans lui, `expression1` sortait dix `\(` ouvrants pour zéro fermant — c'est
`test_render_structure` qui l'a dit, pas `corpus_state`, qui ne contrôle que
l'appariement des groupes de mise en page.

**La faute de source, elle, reste entière** : l'auteur voulait son champ *en
ligne*, à l'endroit précis de sa phrase, et il atterrit dans le formulaire du
bas. C'est exactement ce que WIMS fait aussi — donc rien à corriger ici, tout à
signaler là-bas.

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

## 3. `oefspeed.nl/trajet` affiche ses réponses dans l'énoncé — *à signaler*

*Relevé le 2026-09-22.*

`H3/algebra/oefspeed.nl/src/trajet.oef`, ligne 88 :

```
\if{\choix=1}{Het einde … Hoe laat komt ze aan?{Ze komt om \heure6 uur aan. …}
 \embed{reply 4, 8}}
```

Il manque une `}` avant `{Ze komt` : l'auteur voulait un `\if{…}{alors}{sinon}`,
et a écrit un bloc « alors » qui ne se referme pas. L'accolade manquante
reporte la fermeture du `\statement` au-delà des cinq `\answer` (l. 98-102),
qui deviennent du **texte d'énoncé**. Le `.def` compilé le montre :
`replycnt=0`, et la fin de `:question` porte
`$m_answer{Duur van de pauze :}{$val30 u}{type=units}`… — `$m_answer` étant
vide, l'élève lit `{Duur van de pauze :}{0.75 u}{type=units}`, soit **les cinq
bonnes réponses en clair**, sans aucun champ où répondre (les `\embed` pointent
vers des réponses qui n'existent pas).

PAX rend la même chose, fidèlement. L'exercice est à écarter d'une feuille
tant que la source n'est pas corrigée. Correction : `…aan?}{Ze komt …`.

## 4. `oefpscal.fr/cercle` : un `src="` qui ne se referme pas — *à signaler*

*Relevé le 2026-09-24.*

`H5/algebra/oefpscal.fr/src/cercle.oef` écrit `<img src="\cerct>` : le
guillemet ouvert n'est jamais fermé. Le navigateur prolonge alors la valeur de
l'attribut jusqu'au prochain `"` de la page, et la figure ne s'affiche pas —
chez WIMS comme chez PAX, qui ne la répare pas (`_IMG_SVG_RE`, dans
`core/oef/flydraw.py`, exige qu'un guillemet ouvert se referme). Correction :
`<img src="\cerct">`.

À ne pas confondre avec `<img src=\figure>` **sans** guillemets
(`oefrelat`, `solide6-5.nl`) : c'est du HTML valide, que PAX incorpore depuis
le 2026-09-24.

## 5. Trois exercices écrits pour un PARI plus ancien — *à signaler*

*Relevé le 2026-09-29, au banc PARI (`backend/scripts/banc_pari`).*

Deux fonctions de PARI ont changé de type de retour depuis que ces exercices
ont été écrits, et `output()` de `Interfaces/pari.c` ne déballe une sortie que
si elle **se termine** par `]` ou `)` :

- `numtoperm` rend un `Vecsmall` (`Vecsmall([1,3,5,2,4])`), non plus un
  vecteur. `H4/biology/evolmeth.fr/src/evolmeth4.oef` en passe un élément à
  `!declosing`, qui n'ôte que des parenthèses **englobantes**
  (`strip_enclosing_par`) : `Vecsmall(…)` traverse intact et sert d'index de
  lignes (`$(val18[$val16;])`). La matrice des caractères s'affiche en texte
  brut (`[,A,B,C,D,E;caract. 1,1,1;…`).
- `nfroots(,P)` rend une **colonne** (`[-2,6/7]~`). Le `~` final empêche le
  déballage, si bien que `$(val32[1])` vaut `[-2` et `$(val32[2])` `6/7]~`
  dans `H5/analysis/oefderivee1S.fr/src/tgte2pts.oef` et `tgte2ptstep.oef` :
  l'équation de la seconde tangente est illisible.

PAX rend ce que rend `gp` aujourd'hui, donc la même chose. Corrections :
`Vec(numtoperm(…))` et `nfroots(,P)~` — ou `polroots`, que `tgte2par.oef`
lit correctement en découpant `-7.0+0.0*I` aux `+`.

## 6. `oefseconddegree/sdvar1` à `sdvar4` : l'abscisse du sommet n'est jamais définie — *à signaler*

*Relevé le 2026-09-03, instruit le 2026-10-01.*

Les huit `sdvar*.oef` de `H4/algebra/oefseconddegree.fr` sortent du même
`cpp/sdvar.cpp` et posent à l'étape 1 la même question — « Quelle est
l'abscisse du sommet ? » — avec la même réponse :

```
\answer{réponse }{ \alpha}{type=auto}{option=nonstop}
```

`sdvar5` à `sdvar8` définissent `\alpha` (`\rational{alpha=-\b/(2*\a1)}`,
`\rational{alpha=(\x1+\x2)/2}`). **`sdvar1` à `sdvar4` ne le définissent
pas** : le sommet vaut 0 dans les deux premiers, et `sdvar3`/`sdvar4`
l'appellent `alpha1` (`\real{alpha1=randint(1..9)}`, `\function{f=\a1*( x -
\alpha1 )^2+\c}`).

Une variable inconnue dans un `\answer`, le compilateur OEF la traite comme
une variable **que la réponse remplit**, non comme un attendu : le `.def`
porte `replygood1=?analyze 15` (contre `replygood1=$val15` pour `sdvar5`),
`conditioncnt=0` et un `:test` vide. Deux conséquences, chez WIMS comme
chez PAX :

- l'étape 1 n'est **notée par personne** — toute réponse passe ;
- la réponse est **reprise comme α** dans la suite : l'étape 3 et la
  solution écrivent `]−∞ ; $val17]`. Sur `sdvar3` (graine 42, sommet en 4),
  un élève qui répond `42` lit à l'étape 3 « croissante sur ]−∞ ; 42] » et
  la solution le lui confirme, sans jamais donner 4 autrement que par `α`.

PAX marque ce champ `ungraded` (pas de `:test`, pas d'attendu) et rend le
report à l'identique. Corrections : `\real{alpha=0}` dans `sdvar1` et
`sdvar2` ; `\real{alpha=\alpha1}` dans `sdvar3` et `sdvar4` — ou, mieux, dans
`cpp/sdvar.cpp`, qui les engendre tous. D'ici là, ces quatre exercices sont
à écarter d'une feuille.
