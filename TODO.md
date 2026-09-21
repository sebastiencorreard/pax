# I. Moteur def

## 1. Comprendre mieux

Les deux inventaires sont faits. Ils ne sont pas figés dans ce fichier — un
relevé recopié à la main pourrit — mais tenus par un test et par une sonde
qu'on rejoue. Chiffres du **2026-09-05**, corpus de 4278 exercices, cache vidé.

- [x] **Les types de réponse.** `tests/core/answer/test_types_non_portes.py`
  est l'inventaire vivant : il énumère les types, mesure lesquels retombent sur
  `check_text`, et échoue si la liste bouge dans un sens comme dans l'autre. Le
  catalogue narratif — à quoi chaque type correspond — est dans
  [`docs/types-exercices-reponses.md`](docs/types-exercices-reponses.md).

  | | |
  |---|---|
  | Types connus (WIMS + `anstype/` des modules) | 68 |
  | Employés par au moins un `.def` du corpus | 44 |
  | Jamais employés | 24 |
  | **Atteignant `check_text` sur un champ noté** | **0** |

  Les 24 inemployés (`chessgame`, `crossword`, `flashcard`, `clock`,
  `puzzle`, `keyboard`…) ne coûtent rien tant qu'aucun exercice ne les appelle :
  les porter serait du travail sans effet mesurable. Cinq types employés
  n'atteignent jamais le dispatch — le moteur les intercepte en amont
  (`_DETTE_INTERCEPTEE`) ; c'est voulu, et le test le vérifie séparément pour
  qu'une interception qui tomberait se voie.

  Les noms que les auteurs inventent — `rational` (24), `integer` (8),
  `fonction` (7), `formula`, `real`, `equations` — ne sont pas une dette : comme
  chez WIMS, un type inconnu devient `default`, donc une comparaison
  mathématique.

- [x] **Ce qui manque au moteur.** Mesuré en rendant tout le corpus, pas en
  lisant les sources — la lecture sur-rapporte, à chaque fois.

  | | |
  |---|---|
  | Exercices rendus sans exception | 4278 / 4278 |
  | Occurrences de `UNKNOWN_CMD` | **0** |
  | Exercices n'exposant aucune réponse | 3 |
  | Exercices touchant une primitive de figure non traitée | 23 |

  **Aucune commande ne manque.** Le relevé statique en désignait 19 (`!let`,
  `!href`, `!header`, `!tail`, `!insplot`, `!filewrite`…), mais aucune
  n'apparaît dans un `.def` : toutes vivent dans les `.phtml` et `.proc` des
  pages de module, que le moteur d'exercices n'exécute pas. Le « ~70 % de
  `calc.c` » de [`wims-c-to-python-port.md`](docs/wims-c-to-python-port.md)
  mesurait le fichier C, pas le besoin du corpus.

  Rappel de méthode : **zéro exception ne veut pas dire zéro défaut.** Le moteur
  ne lève pas — il rend une chaîne vide, un `NaN`, un énoncé sans question. Les
  trois compteurs ci-dessous sont là pour ça, et c'est encore l'œil humain qui
  attrape le reste.

### Ce que ces mesures laissent ouvert

- [ ] **23 exercices touchent une primitive de figure non traitée**
  (`[FLYDRAW-UNHANDLED]`, journalisée sur stderr — jamais levée). Trois familles
  bien distinctes, à ne pas traiter ensemble :

  - *Vraies primitives flydraw absentes* — `ftriangle`, `fillrect`, `fcircles`,
    `dashed`, et les transformations `translate` / `affine` / `killaffine` /
    `rotate` / `translation` / `killrotate` / `killtranslate` / `animate`.
    Une dizaine d'exercices : `oefpytha/etagere1`, `oeftranslation/translation1`
    et `translation4`, `oefmolecule/cramform1`, `oefaffine/droiteanim`,
    `gensuitefig/slin`, `OEFevalwimsequat/resoudre2`.
  - *Options JSXGraph, pas du flydraw* — `axis`, `axisnumbering`, `grid`,
    `legend`, `linegraph`, `strokecolor`, `xlabel`, `ylabel`, `snaptogrid`,
    `snaptopoints`, `opacity`, `latex`. Elles remontent sous la même étiquette
    alors qu'elles relèvent d'un autre sous-système : `unitefonct/1`,
    `oefvectgraph/comblin`, `evolmeth/evolmeth1`.
  - *Bruit d'analyse* — `toto`, `new`, `centre`, `arete`, `polygone`,
    `vecteurs`, `abcah` et des nombres nus (`0`, `1`, `2`, `20`, `400`). Ce ne
    sont pas des commandes : le découpage prend des noms de variables ou des
    étiquettes pour des opérations. À instruire avant de porter quoi que ce
    soit — il se peut qu'il n'y ait rien à porter.

- [ ] **Trois exercices n'exposent aucune réponse** : `oefspeed.nl/trajet`,
  `equilibrium.fr/methode`, `anglesCercleTrigo.fr/definitions`. Ils sont écartés
  *avant collecte* par `_get_testable_exercises`, donc invisibles aux tests —
  ni échec, ni skip. Le commentaire de `tests/test_exercises_check.py` en
  annonçait 24, dont 11 avec des champs visibles ; c'était vrai avant les
  corrections d'août.

- [x] **377 exercices sont notés par leur section `:test`**, et `_check_all` n'y
  passait jamais : il appelait `check_answer` champ par champ. Corrigé le
  2026-09-05 — `_check_all` reprend la bifurcation d'`api/routes/check.py`, à la
  lettre, pour éprouver ce que l'élève subit et non une notation inventée pour
  le test.

  Le chiffre de 224 annoncé plus haut le 2026-09-05 était un sous-compte : il
  ne voyait que les champs `answer_type == "analyze"`, alors que la route
  bascule aussi sur les champs portant `analyze_var` — des widgets
  (clickfill, radio, menu) qui s'affichent normalement mais se notent par
  `:test`.

  Les deux tests ne couvrent pas la même part, et c'est structurel :

  | | |
  |---|---|
  | Tous les champs `analyze` portent un attendu | 107 |
  | Attendu partiel | 38 |
  | **Aucun attendu — la bonne réponse n'est écrite nulle part** | **232** |

  `test_correct_answer_scores_1` demande une vérité de référence : il ne peut
  atteindre que les 107. `test_wrong_answer_scores_less_than_1` n'en demande
  aucune — il suffit qu'une réponse absurde ne vaille pas 1 — et couvre donc
  les 377. C'est lui qui attrape le défaut le plus grave de cette famille : une
  section `:test` qui conclut `good` quoi qu'on lui soumette.

  **Le branchement a produit 68 échecs sur des exercices que la suite déclarait
  sains.** Aucun n'était une régression : ils étaient cassés depuis toujours, et
  rien ne les regardait. 35 ont été réparés par deux correctifs, 33 restent
  consignés dans `known_failures.py` avec leur famille.

- [ ] **La forme affichée au lieu de la forme rangée** (`OEFevalwimsgeplan`).
  Le `:test` compare `$val9 issametext $(val7[1])` — la forme que l'exercice
  range, `\(A') … \((d))` — quand l'élève renvoie celle qu'on lui montre,
  `\(A'\) … \left(d\right)`, math refermé pour KaTeX et délimiteurs
  développés. `_forme_brute` savait faire la conversion, mais on ne la lui
  demandait que pour `m_reply<n>`, jamais pour les `val<N>` d'un `?analyze`.
  Corrigé le 2026-09-05 : trois des six sont partis. Restent `deduction3`,
  `deduction4` et `thmpte5`, dont le `:test` demande encore autre chose.

- [x] **Ce qui suit `?analyze N;` est une configuration, pas une réponse**
  (`oefstatistiques` et 5 autres) — corrigé le 2026-09-05. Pour un `jsxgraph`
  c'est la liste des objets à lire (`\jsq1;\jsme;\jsq3;\jsmax`), pour une
  `reaction` les dimensions du dessin (`40,1000,6,1000`) ; le moteur en faisait
  un attendu, et l'affichait à l'élève comme corrigé. Ces deux types rejoignent
  `clickfill`/`checkbox`/`mark`, dont le `rest` était déjà traité comme tel.
  Effet de bord bienvenu : un champ texte parasite (`Entrez votre réponse :` +
  `<input name="reply1">`) disparaît de quatre exercices où la figure porte
  déjà la réponse.

- [x] **Le chronomètre de `type=reaction` est porté** (2026-09-05). Ces trois
  exercices sont interactifs : l'élève appuie sur GO, attend un délai qu'il ne
  peut pas anticiper, frappe STOP le plus vite possible, et recommence quarante
  fois ; la série de temps ainsi mesurée est la donnée que les cinq étapes
  suivantes dépouillent. Le `.input` du module monte ce chronomètre en
  JavaScript inline — inerte une fois injecté par le `v-html` du front. PAX
  n'affichait donc que « Réaliser 40 tests. » et un champ vide, sans dire quoi y
  écrire : l'exercice était **inutilisable depuis le début**, et son défaut de
  notation n'en était que la conséquence.

  Composant `ReactionTest.vue`, marqueur `pax-reaction` côté moteur. Vérifié au
  navigateur : mesure enregistrée, essai rejeté au-delà du seuil, tableau
  récapitulatif alimenté.

- [x] **`total_steps` valait 1 alors que ces exercices en ont six** — corrigé le
  2026-09-05, et le remède n'est pas de mieux deviner.

  `total_steps` est une **estimation faite au rendu**, avant que l'élève ait
  répondu. `_resolve_nextstep` rejoue `:postdef` à vide pour la produire, et sur
  50 exercices ce rejeu n'aboutit pas : il tourne en rond
  (`OEFpythagore2/rectangle` répète la même étape 31 fois), épuise son budget
  (`histocap`), ou ne trouve aucun `\nextstep`. Le repli annonçait alors une
  seule étape, et l'élève restait bloqué sur la première.

  WIMS ne devine rien : `nextstep.proc` rejoue `:postdef` **après** la réponse,
  avec `m_step` déjà avancé, et regarde si `$nextstep` est vide. C'est ce que
  fait maintenant `etape_suivante_existe`, appelée par la route de correction,
  dont la réponse porte un `has_next_step`. Le front ne s'en sert que pour
  *ajouter* une étape que l'estimation avait manquée — jamais pour en retirer —
  et `null` (l'exercice n'a pas de `\nextstep`) laisse le comportement d'avant
  intact.

  **Chiffre rectifié le 2026-09-06 : 13 exercices débloqués, non 79.** Le
  premier relevé comptait tous ceux dont `has_next_step` répondait « oui », y
  compris les 66 où il répondait oui *à tort* — le piège de l'étape annoncée
  identique à l'étape en cours, corrigé depuis. Treize, c'est la mesure faite
  une fois ce piège écarté : `OEFpythagore2/{enchainement,rectangle,rectangle2}`
  en fr et nl, `oefstatistiques/{histocap,histogramme,moustache}`, et quelques
  autres.

  L'étiquette suit : elle n'annonce plus un total qu'on sait faux (« Étape 2 / 1 »
  s'affichait dès la première étape franchie), seulement « Étape 2 ».

- [x] **La propriété manquante est posée** (2026-09-06).
  `test_score_depends_on_the_answer` soumet quatre copies — la meilleure
  dérivable, une absurde, une vide, et une de forme décimale — et exige que la
  note **bouge**. Elle comble le trou entre les deux autres tests, qui
  l'éprouvaient par le haut et par le bas sans jamais vérifier qu'elle dépend
  de la réponse. Trois exercices sur 4271 y tombent : les `oefstatistiques`
  ci-dessous.

  Quatre autres y tombaient au premier jet, et **aucun n'était en faute** ; ils
  ont servi à régler le test. `oefpytha/rugby` accorde 1 point sur 11 à toute
  réponse écrite sans point ni barre de fraction, `quizz/0412` demande un
  nombre égal à 9/10 *écrit autrement* — deux conditions opposées — et
  `oefpenney/partita` note 1/200001, ses conditions obligatoires pesant 100000
  chacune. D'où la quatrième copie, et un seuil exprimé sur la note **telle que
  l'élève la voit** : sur dix, au dixième.

- [ ] **`histocap`, `histogramme`, `moustache` : le score ignore la réponse.**
  0,9388 pour la bonne réponse, pour `__FAUX__` et pour une réponse vide — 46
  conditions sur 49. Ces trois-là ne sont **pas** réparés, et le plus gênant
  est ailleurs :

  ils sont désormais **vus** par `test_score_depends_on_the_answer`, et
  consignés dans `XFAIL_CONSTANT_SCORE`. Reste à les réparer : leur `:test` ne
  regarde pas le tracé de l'élève.

- [x] **`$[…]` rendait du symbolique là où WIMS rend `NaN`** (`OEFequdrt`, 4) —
  corrigé le 2026-09-05. Le `:test` demandait `NaN notin $val19`, où
  `val19 = $[fullratsimp(…)]` porte la réponse de l'élève ; PAX rendait
  `-__faux__ - 7*x + 5`, que la garde laissait passer. Ces quatre exercices
  **validaient tout**.

  Le correctif a d'abord été posé au mauvais endroit, et la mesure l'a dit :
  appliquer la règle au rendu changeait 19 exercices, aucun en mieux —
  `OEFspectres/spectre3` écrivait `width="nan"` dans son SVG, là où il y avait
  un nombre. La règle finale sépare **afficher** de **noter** : au rendu, une
  expression que le moteur ne sait pas calculer se montre telle quelle (c'est
  le moindre mal, et `10*8 step 10` est une spécification d'axe, pas un calcul
  raté) ; à la correction, elle vaut `NaN` et ne valide rien. `check_analyze`
  lève le drapeau `_strict_arith`.

- [x] **`!exec chemeq`** (2026-09-02, commit 3faae8d3 ; entrée rectifiée le
  2026-09-20). Ce point a longtemps dit « non implémenté, `!exec` ne connaît que
  maxima et pari » — c'était vrai jusqu'au 2026-09-02 et faux depuis.
  `_cmd_exec` reconnaît aujourd'hui `maxima|pari|units-filter|chemeq|canvasdraw|
  moneyprint|float_calc|lceb` (`def_engine/__init__.py:2854`), l'équilibreur vit
  dans `def_engine/chemeq.py`, et `chemeq` lit son option dans `chemeq_option`
  (c'est ainsi que `slib/chemistry/chemeq_mass` demande une masse molaire et
  `chemeq_tex` un rendu LaTeX). Les 7 exercices d'`equilibrium` / `chemavance1`
  se rendent avec leurs réponses ; seul `equilibrium.fr/methode` n'en expose
  aucune, pour une cause distincte déjà consignée plus haut.
  Reste ouvert : `chemeq_el` et `chemeq_rev` (redox, piles — 12 appels, voir
  « Ce que le portage des slibs ne règle pas »).

- [ ] **`!exec pari` sur un vecteur** — `oefpytha/etagere2` écrit
  `!exec pari [$val25]/10.` et récupère la chaîne brute. Un seul exercice.

- [ ] **Variables de session laissées vides à dessein** — `wims_firstname` (le
  rendu est anonyme), `wims_ref_name` / `session` (pas d'endpoint `getfile`),
  `ins_filename` (PAX rend du SVG, WIMS un GIF — cause connue de l'échec de
  `oefpolygon/quadrilatere`). Chacune est justifiée dans
  [`exercise-parameters.md`](docs/exercise-parameters.md) ; aucune n'est un
  oubli, mais deux changeraient de statut le jour où le rendu connaîtrait
  l'élève ou servirait des fichiers de session.

## 2. paramétrage des exercices

- [x] **Les `confparm` du module sont lus.** `_module_confparm_defaults`
  (`def_engine/__init__.py`) ouvre l'`introhook.phtml` du module — le bloc que
  WIMS insère dans sa page d'accueil, où l'enseignant règle ses paramètres — et
  verse ses `!default confparm1=…` / `!set confparm1=…` dans le ctx avant tout
  le reste. Sans cette lecture, `$confparm1` se substituait en chaîne vide :
  `H3~algebra~oefpuis.nl~src~{decalage,decalage2,decimal,puisdiv}` bouclent sur
  `!for val11 =1 to $val2` où `val2=$confparm1`, et se rendaient **sans une
  seule question**. 8 modules du corpus posent ainsi une valeur — 7 par
  `!default`, `droiteplanrep.fr` par `!set` ; `!set` l'emporte s'ils
  coexistent, comme chez WIMS où il écrase une valeur déjà posée.

- [x] **Surcharger ces valeurs par défaut.** Ce que lit PAX n'est que la
  première moitié du dispositif WIMS : l'`introhook` pose une valeur, puis un
  `!formselect` / `!formradio` laisse l'enseignant en choisir une autre. Nous
  servons donc à tout le monde le réglage d'usine. Ce qui manque n'est pas la
  lecture du paramètre, c'est l'**objet qui porte le choix**.

  - La **feuille d'exercice** (cf. II.1) est le porteur naturel : c'est là que
    WIMS lui-même attache la configuration, et le modèle le prévoit déjà —
    `Attempt` et `Grade` portent un `sheet_id`. Un même exercice pourrait ainsi
    être posé deux fois avec deux réglages, sans dupliquer le `.def`.
  - Ordre de priorité à tenir : défauts du module → réglage de la feuille →
    paramètre d'URL (essai ponctuel, pratique pour déboguer un exercice).
  - Côté moteur, le travail est mince : il suffit de verser les valeurs dans le
    ctx après `_module_confparm_defaults`, qui applique déjà la bonne règle de
    précédence. L'essentiel est en amont — stockage sur la feuille, écran de
    réglage côté enseignant, et route de rendu qui transmet.
  - **Piège à ne pas manquer** : la clé du cache de rendu est
    `pax:render:{path}:{seed}:{m_step}{replies}` (`render_cache.cache_key`) et
    ignore les `confparm`. Deux réglages d'un même exercice se serviraient
    mutuellement leur rendu. La clé devra les inclure le jour où ils varient.

  **Fait le 2026-09-10, dans cette forme.** `sheet_exercises.confparm`
  (JSONB) et `.qcmlevel` portent le choix, par exercice posé — un même
  exercice peut donc l'être deux fois sous deux réglages. `api/reglages.py`
  résout la priorité pour le rendu **et** la correction, qui doivent rendre
  sous les mêmes réglages ; `RenderOut.reglages` revient tel quel au `/check`.
  La clé du cache les inclut (`…:{m_step}|confparm1=3;qcmlevel=7{replies}`),
  et une valeur de `confparm` ne peut contenir aucun de ses séparateurs.
  L'écran de la feuille propose ce que l'`introhook` propose
  (`confparm_du_module` : menus, invites, saisie libre) ; le bouton *Essayer*
  ouvre l'exercice sous ses réglages (`?sheet_item=`). Seul `qcmlevel` a un
  paramètre d'URL, réservé aux enseignants.
  Mesuré au passage : **45 modules** exposent un `confparm` réglable (25 en
  H3, 20 en H4), dont 7 paramètres en saisie libre ; 41 posent une valeur
  d'usine. Ce que le lecteur ne peut pas résoudre hors session WIMS — un
  libellé `$name_conf`, une liste `$menu_list` — sort vide ou en saisie libre.
  Reste le **parcours élève** (cf. II.1) : le réglage ne sert encore qu'à
  l'aperçu enseignant.

## 3. Conformité WIMS (réf. docOEF4, audit 2026-06-12)

### a) Notation / précision (prioritaire)

- [x] **Brancher `\precision{M}`** : injecté par `def_engine._wims_precision` (borné 20..1e8, défaut 10000) dans `options["precision"]`, consommé par `check_numeric/numexp/unit/fset`. Formule exacte de `compare.c` : `|d1-d2|*prec ≤ |d1+d2| + 1/prec`, avec 2ᵉ passage à `sqrt(prec)` → crédit partiel 0.5 (« bonne à précision près »). Option `absolute` gérée. (`checkers.py` `_wims_num_equal`)
- [x] **`numexp` formel** : réécrit en comparaison **rationnelle exacte** (`_parse_exact_rational` → `Fraction`) — rejette `2/8` pour `1/4` (non réduit, sauf option `noreduction`), `0.333` pour `1/3` (pas de tolérance), les expressions composées (`nocompute`) et le mélange `/`+`.` (`badform`). Repli flottant (précision WIMS) quand un côté n'est pas un rationnel simple (attendu composé/non évalué). Cohérence corpus vérifiée : 3475/3573 `expected` round-trip ; les 98 restants ont un `expected` malformé (listes, `rint(GCD())` non évalué, `NaN`) — bugs d'évaluation préexistants, pas de régression.
- [x] **`\condition` multiples** : **déjà géré dans le chemin live** (le `engine.py:622` du constat était le pipeline legacy, mort pour le corpus compilé). Les `\condition{}` compilent vers la section `:test` (`condtestN`/`condweightN`/`condnameN`) ; `check_analyze`/`run_analyze` évaluent **chaque** condition et notent `Σ(condtestN·condweightN)/ΣcondweightN` (fraction pondérée, cf. test `test_cant_irreducible_fraction_scoring` → 0.75). L'affichage par condition passe par la section `:feedback` (exécutée par `render_feedback`). Reste différé : `\conditions{}` (sélection dynamique, 1 usage corpus) et le flag `hide`. NB : 14 exos `conditioncnt≥2` ne routent pas vers run_analyze mais c'est un problème distinct (0 réponse extraite : widgets jsxgraph/canvas/runcode), pas d'extraction de condition.
- [x] **`option=default=xxx`** : réponse vide → substituée par xxx puis vérifiée (WIMS `step.proc`). Couvre `default=vide` (fset : vide = ensemble ∅, cf. oefresolalg synth*) et `default=$valN`. **Bug corrigé au passage** : l'ancien `default=vide` excluait de la notation *toutes* les réponses le portant — donc les vrais ensembles-solutions des synth n'étaient pas notés, et eqalgpara/ineqalgpara (brouillon `default=empty`) étaient insolubles (run_analyze forcé, bonne réponse → 0).
- [x] **Type `draft` (brouillon) + marqueur `options["ungraded"]`** : champs `type=draft` (et `analyze`+`default=vide` sans `:test`, ex. dev2fact) désormais ni notés ni obligatoires, keyés sur le TYPE et non sur la chaîne `default=vide`. Consommé par `check.py` (exclusion) et le front (`allFilled`). Corrige synth1deg/2deg/synthquot, eqalgpara1-5, ineqalgpara1-5 ; préserve dev2fact1/2.
- [x] `\computeanswer{no}` : injecté dans `options`, refuse une réponse `numeric` composée (`5*5` pour `25`) via `_wims_has_compound_arith` (règle exacte d'`anstype/numeric` : opérateurs `+-*^(` ou `.`+`/`) ; `computeanswer=yes` autorise le calcul. Fractions simples/décimaux acceptés.
- [~] `sc_reply` : « bonne à précision près » → 0.5 fait pour numeric/numexp (2ᵉ passage sqrt) ; reste le « partiellement juste » d'autres types

### b) Types litexp / algexp / formal (§1.4.5, testés)

PAX rabat les trois sur `check_algexp` (SymPy) + pré-checks de forme :

- [x] **`formal`** : retiré de l'auto-classification développé/factorisé → équivalence CAS pure (`(x+1)(x-1)` accepté pour `x^2-1`, `2*(x+3)` pour `2*x+6`). Options explicites `polexpand`/`polfactor` toujours honorées. (12/428 self-checks échouent encore = limites CAS sympy sur formules physiques `sqrt`, préexistant.)
- [x] **`litexp`** : `check_litexp` = égalité CAS + forme **rawmath conforme** (`_rawmath_normalize` : nospace + `*` implicite + `**`→`^`, sans simplification). `6/4`/`x*x+3`/`1.5` → `badform` ; `2x+3`=`2*x+3` OK ; alternatives virgulées gérées. Options explicites `expand`/`polfactor` gardent la voie check_algexp. Corpus : 268 formes stockées, 0 régression.
- [x] **`algexp`** : équivalence **rationnelle** (`check_algexp(rational_only=True)` → `cancel`, sans trig) → `sin²+cos²` refusé pour `1`/`x²+1` ; retiré de l'auto-classification de forme → coefficients non simplifiés acceptés (`(24+4)*x-53`, `2*x+3*x` pour `5*x`, `x*x` pour `x²`). Options explicites `expand`/`polfactor` gardent la voie check_algexp. Corpus : 204 formes, 19 refus tous préexistants (expected malformés `print(print(...`, matrices `f=c in`, edge polfactor).
- [x] **Fonctions maxima `coeff`/`hipow` imbriquées** : fournies à sympy (`cas.py:_sympify_arg`) → `coeff(P,b,2)*(b^2)` s'évalue au lieu de fuir. Répare `developper.def` (litexp expected `coeff(...)` non évalué → `c e f f o \left(` mangé).

### c) Autres types de réponse

- [~] **Le trou d'`oef/formr.phtml` : un widget que PAX ne sait poser qu'embarqué.**
  WIMS ne décide pas autrement selon que l'auteur a embarqué son champ ou non —
  `formr.phtml` tient en cinq lignes : `!if r$i isitemof $embedded → !exit`,
  sinon `!read anstype/$(replytype$i).input`, qui monte le widget complet. PAX,
  lui, construisait certains widgets **uniquement** dans la branche `\embed` de
  `_render_embed` ; faute d'embed, le repli par réponse posait une boîte de
  texte. Relevé du 2026-09-20 sur les types qui ont une branche d'embed mais ne
  figurent pas dans la liste d'exclusion de `text_replies` :

  | type | réponses touchées | ce que l'élève subit |
  |---|---|---|
  | `checkbox`/`multipleclick` | **17** | **corrigé le 2026-09-20** (6c98a43a) |
  | `clickfill`/`dragfill` | 31 | dégradé, **soluble** (voir la nuance ci-dessous) |
  | `coord` | 1 | insoluble |
  | `draw` | 0 | rien à faire |

  **`clickfill` n'est pas urgent et c'est mesuré** : les champs de secours
  portent le bon nom, l'attendu est un chiffre, et la notation marche
  (`oefaddition1` : juste 1.0, faux 0.0). L'élève tape le chiffre au lieu de le
  glisser — c'est l'ergonomie qui est perdue, pas l'exercice. À porter pour la
  qualité, pas pour le déblocage.

  **Nuance ajoutée le 2026-09-20** (866996c7) : le *nombre d'emplacements*
  d'un `clickfill`, lui, était faux — et là c'était bloquant. `fill.inc`
  écarte la ligne `?analyze` **avant** de compter, si bien que la première
  ligne devient le vivier ; PAX comptait avant et lisait `?analyze 23` comme
  un item unique. Et la taille se lit en quatre nombres que `x`, virgule ou
  **blanc** séparent indifféremment, quand PAX ne coupait que sur `x`. Douze
  exercices étaient insolubles, cent trente rendaient leurs cases sans
  largeur. Ce qui reste ouvert sur `clickfill` est donc bien l'ergonomie
  seule : taper au lieu de glisser.

  **`coord` est un vrai défaut, mais un seul exercice** —
  `OEFpdtscalTS/cnstbary1` : son attendu est une *zone*
  (`rectangle,540.2,0,549.8,64`) qu'aucun élève ne tapera, et le checker veut
  un **point** cliqué dedans. Il cumule d'ailleurs un second défaut, distinct :
  l'énoncé dit « on a représenté ci-dessous un segment [AB] » et **ne rend
  aucune image** (0 `<img>`, 0 `<svg>`, 0 `<canvas>`). Rendre le champ cliquable
  ne suffirait pas ; il n'y a rien à cliquer.

- [ ] **Les types sans aucune branche d'embed** — un trou plus large, à ne pas
  confondre avec le précédent : PAX ne les rend widget ni embarqués ni en
  repli. Restent `reorder` (glisser-déposer bâti sur `compose.css`, 3 champs),
  `crossword` (5), `clicktile` (14). `compose`/`textcomp` en sont **sortis le
  2026-09-20** (75fdaee3, zone libre).

  Vérifié contre leur `.input`, qui fait foi — et **trois faux positifs à ne
  pas rouvrir**, parce qu'un relevé plus ancien les comptait à tort :

  - `chset` (21 champs) est un simple `<input list="emptylist" size=18>` ;
  - `complex` (31) un champ numérique générique (`anstyle=numeric`, size 20) ;
  - `matrix` (4) **n'est pas une grille de champs** — contrairement à ce que
    cette entrée a d'abord dit. `matrix.input` tient en 31 lignes et pose un
    seul `<textarea rows×cols>` entre deux grandes parenthèses
    (`$m_leftpar4` / `$m_rightpar4`) : l'élève y tape la matrice, une rangée
    par ligne. Trois des quatre se rendent **déjà** en `textarea` `RxC`
    (`4x8`, `2x5`, `3 x 10`) ; seul `sommemat` retombe sur un champ d'une
    ligne, sa taille n'étant pas de la forme `RxC` — là où WIMS prendrait ses
    défauts (5 lignes × 25 colonnes). Un champ, pas un chantier.

  Pour ces trois-là, le rendu de PAX est déjà juste ou presque ; seuls
  manquent le `datalist` de `chset` et les parenthèses de `matrix`, tous deux
  cosmétiques.

- [x] **Le séparateur des palettes** (2026-09-21). `wims/src/html.c`,
  `_form_menus` : `if(i<itemcnt-1 && itemcnt>2 && (hmode==NULL || *hmode==0))`.
  WIMS met une **virgule**, pas un `;`, mais seulement au-delà de deux
  propositions — PAX joignait toujours par `", "`, d'où une virgule parasite
  sur 15 exercices (`OEFevalwimsnumber/oefordre*` : « ☐ 478, ☐ 470 »).
  Corrigé sur les deux chemins à la fois (`_joindre_cases`).
  La troisième condition, `wims_html_mode` vide, **n'est pas portée parce
  qu'elle est morte** : la variable n'apparaît ni dans les 4 300 `.def` du
  corpus, ni dans les scripts WIMS rapatriés.

- [ ] **Six `oeffonctionsverbe/gramfonclic*` au `replygood` vide.** Leurs 40
  réponses `clickfill` n'ont **aucune** étiquette : `replygood1` se réduit à
  `;`. Le rendu leur pose désormais leurs 40 emplacements (c'est ce que fait
  `formr.phtml`), mais sans vivier ils restent insolubles.

  **Ce n'est PAS la tranche indexée**, contrairement à ce que cette entrée a
  d'abord dit en les rattachant à `evolmeth1/2` et `geo6`. Vérifié le
  2026-09-21 sur huit formes : `$(m[1;])` rend bien `a,b,c`, `$(m[;1])` rend
  `a,d,g`, `$(m[1;$liste])` rend `a, c`. Le découpage fonctionne ; les
  variables sont vides **avant** lui.

  Ce qui est établi, pour ne pas refaire le chemin :

  - la chaîne de vides remonte à `val2=$confparm1` et `val3=$confparm2`
    (l. 23-24 du `.def`) ;
  - le module ne pose **aucun défaut** pour eux : son `introhook.phtml`
    commente sa seule déclaration (`!! !formradio confparm1 from 1 to 3`), et
    son `var.proc` n'en parle pas ;
  - mais fournir `confparm1`/`confparm2` par `reglages` ne change rien — le
    vivier reste vide aux valeurs 1, 2 et 3.

  Donc la cause est **encore en amont**, et l'hypothèse `confparm` ne suffit
  pas. Piste non explorée : la source OEF écrit `\text{file0=randitem(\file)}`
  et `wims(embraced randitem …)`, or `randitem` est une **fonction du
  calculateur** chez WIMS (`calc.c:2396`, table `calc_list`) au même titre
  qu'`imgrename` — que PAX a dû porter en août pour la même raison
  (`_eval_value` applique `calc_imgrename` à toute valeur calculée). Vérifier
  si `randitem(…)` en position d'expression est évalué serait le prochain pas.

- [x] **`nocase`** : `check_nocase` — match exact après normalisation (ponctuation→espace, accents/casse/espaces ignorés) contre toute alternative `|`. Self-check corpus 40/0.
- [x] **`atext`** : `check_atext` — normalisation nocase + **suppression des mots vides** (articles, via `atext.dic`) + **racinisation pluriel/genre** (via `suffix.<lang>`, algorithme WIMS : mot inversé, plus longue clé-préfixe remplacée) + alternatives `|`. « les triangles » = « un triangle » = « triangle » ; « carrés » = « carré ». Dictionnaires WIMS copiés dans `backend/core/answer/data/atext/` (fr/nl/en). Self-check 39/0.
- [x] **`dragfill`** (132 exercices, pas ~25) : `help/anstype/clickfill.phtml` décrit `clickfill` et `dragfill` comme **un seul widget**, à une différence près — une étiquette resservable dans le premier, à usage unique dans le second. Faute de reconnaître le nom, PAX ne voyait qu'un type inconnu et lisait la taille `HxVxLxT` comme un `textarea` : les 132 exercices s'ouvraient sur **une zone de texte libre géante** (80 lignes) à la place du glisser-déposer, sans la moindre étiquette affichée — insolubles, pas seulement mal notés. `dragfill` est désormais replié sur `clickfill` (`_normalize_reply_type`, aux trois points de lecture du type), la contrainte voyageant à part en `options["single_use"]`. **La palette ne se compose pas comme celle d'un clickfill** (`anstype/fill.inc`) : ligne 1 (la réponse) **puis** le complément des lignes suivantes (`!listcomplement`), et **sans `!listuniq`** — un mot dont une lettre revient a besoin d'une carte par occurrence. D'où deux conséquences : un vivier absent est licite (la palette est alors la réponse mélangée — les anagrammes de `oefdeutsch`, où l'on rassemble « Hamburg » lettre à lettre, n'avaient aucune autre source d'étiquettes), et le front doit **garder ses doublons** (`prepareChoicesHtml` dédoublonnait) en grisant autant de cartes que d'exemplaires posés. Le mélange suit `dragfill.after` (tri alphabétique au-delà de 12 étiquettes). Option **`noorder`** (3 fichiers) branchée sur `check_clickfill` : comparaison des multiensembles, ce qui rend notables les exercices « classer par propriétés ». **124/132 rendent une case, une palette et une réponse atteignable** (vérifié étiquette par étiquette, en tenant compte des doublons). Les 8 restants relèvent d'autres bugs : `oeftrigo2/vocabulaire3` attend `imagefill` (ci-dessus) ; `evolmeth1/2` et `geo6` ont un `replygood` vide, leurs `$(val12[1;$val17])` (tranche de matrice indexée par une liste) ne s'évaluant pas — **bug distinct à traiter** ; `arithtable` a la même maladie sur son vivier. **Vérifié dans le navigateur** : `vocabulaire1` pose son étiquette et note 100 % ; `geo4` tire *Stuttgart*, dont la palette porte bien **quatre cartes `t`** — le dédoublonnage le rendait insoluble — et en grise exactement trois quand trois sont posées, la quatrième restant active. Console sans erreur.
- [x] **`units`** : moteur `sympy.physics.units` (zéro dépendance) — `_unit_to_si` couvre préfixes, puissances, unités **dérivées** (N, J, Ω…) et **non-métriques** (h, min, °). Accepte `36 km/h`=`10 m/s`, `90 min`=`5400 s`, `1 kOhm`=`1000 Ohm`, `400 dm²`=`4 m²`. Comparaison valeur+dimension+précision WIMS conservée. **Bugs corrigés** : notation scientifique (`3.34e-26 kg` : split valeur/unité, `_parse_number`, et `_wims_has_compound_arith` qui prenait le `-` de l'exposant pour un calcul). 101 unités corpus parsées ; 30 refus = expected malformés préexistants (HTML/rint).
- [x] `click` : **déjà fonctionnel** — mappé vers `clickfill` (matching par contenu du choix, pas par position `~k`). formule1-5 et compTrinomeSign* notent correctement (self-check OK). La note « non câblé » était obsolète.
- [x] **`raw`** : `check_raw` — comparaison exacte de chaîne après filtres pilotés par option (`nospace`, `nocase`, `deaccent`, `nodigit`, `nopunct`, `noparenthesis`, `nomathop`, `noquote`). Routé depuis le dispatch. 585 tests core.
- [ ] **Sept types réveillés par l'import de H1, H2, H5 et H6 (2026-09-10).** Ils atteignent `check_text` sur des champs **notés** : l'élève n'y est juste qu'en recopiant l'écriture exacte de la référence, et rien ne le signale — le test « la bonne réponse donne 1 » passe, puisqu'il soumet justement la référence. Déclarations dans les `.def` : `complex` 63 (H5/H6 : `oefcomplexes`, `cplxcalc`, `cplxgeom`…), `chset` 21 (`OEFangle`), `clicktile` 15 (`oefratio`, `oeffrieze`), `compose` 9, `matrix` 7 (intercepté en H3/H4 par `?analyze`, pas en H5/H6), `crossword` 5, `reorder` 3. Recensés dans `_DETTE_ATTEINTE` (`tests/core/answer/test_types_non_portes.py`), à porter un par un selon la méthode de la mémoire *dette des types de réponse* — `complex` d'abord. `vector`, `equation` et `flashcard` restent sans usage.

### d) Étapes, rendu, moteur

- [ ] **Trois défauts relevés à la vérification manuelle des ports (2026-09-03), non instruits.** Aucun n'est une régression : tous préexistaient, et le travail sur les types de réponse les a seulement rendus visibles. (1) `oefseconddegree/sdvar1` à `sdvar4` — l'étape 1 de ces `course` n'est notée par personne : leur `:test` est vide et `conditioncnt` vaut 0, si bien que le champ est désormais marqué `ungraded` plutôt que compté faux. WIMS ne le note pas davantage ; reste à savoir si l'exercice est incomplet ou si l'étape est délibérément libre. (2) `oefpression/mathml` — seul exercice du corpus dont une réponse notée n'a aucun champ de saisie ; il n'a pas de `.def`, vit hors de `src/` et charge `ASCIIMathML.js` : sans doute un fichier de démonstration, à écarter du corpus plutôt qu'à réparer. (3) `oefalgopython/balayage1|2` (en `xfail`) — leur `replygood` sort du moteur avec un `$(val63[pas,[…]])` **non résolu** : l'auteur y indexe `val63` par du texte, ni rang ni rangée. Le moteur laisse la référence en clair et l'attendu devient inutilisable. À trancher : défaut d'exercice, ou indexation textuelle que WIMS sait résoudre et pas nous.

- [~] **`\nextstep`** (étapes dynamiques selon réponses, §4.3.3-4) : le moteur rejoue la section `:postdef` pour retrouver la fin de l'exercice. Trois points établis en lisant le source WIMS : (a) **le total d'étapes n'existe nulle part dans le `.def`** — `scripts/oef/nextstep.proc` relit `$nextstep` après chaque étape et s'arrête dès qu'il est vide, donc l'ancienne heuristique (deviner via `val62`/`val71`/`cnt`) ne pouvait pas marcher ; (b) `step.proc` fait `!advance oefstep` puis `m_step=$oefstep` **avant** d'appeler `nextstep.proc`, si bien que `:postdef` s'exécute avec `m_step` pointant l'étape *à venir* (d'où les `!ifval ($m_step==2 …)`) ; (c) le déclencheur est `postvarcnt>0` — 202 exercices sur les 636 qui contiennent `nextstep`. **26 exercices conditionnent l'étape suivante à la justesse d'une réponse** (`oefechpython.fr/de4` : `!ifval ($m_step==2 and $m_sc_reply1==1)` ; `oeffunctionmod.fr/mr1` : seconde chance si `$m_sc_reply1=0`) : leur total est structurellement inconnaissable avant que l'élève réponde, `total_steps` reste alors `None` plutôt qu'un chiffre faux. La détection ne regarde que les affectations de la variable désignée par `\nextstep`, si bien qu'`heron1` — qui lit les scores pour un feedback mais pas pour piloter la progression — garde un total exact. Quand le rejeu n'aboutit pas (`$nextstep` constant, `arithtable.*/table2x2`), les heuristiques de repli reprennent la main. Corpus : 4296 OK / 0 fail, rendu inchangé ; 36 `total_steps` corrigés (14 `0→1` aberrants, 17 totaux réels découverts, 6 surestimations dont `BoucleWhile` 19→1), 12 passages à `None` tous justifiés. **Reste** : option `nonstop` non gérée ; `heron1` plafonne à 1 étape parce que son `val58` vaut `rint(na)` — expression non évaluée, bug distinct.
- [~] **`\special`** : `mathmlinput` (100 usages) + désormais **`tooltip`** (35), **`help`** (84) et **`expandlines`** (15). Le silence des specials non gérés ne se contentait pas de perdre un widget : il **supprimait le texte de l'énoncé** quand le special en porte — `\special{help fscient, format scientifique}` rendait le vide au milieu d'une phrase. `tooltip` est un port de la branche CSS de `tooltip.phtml` (`span`, ou `div` si le texte est balisé ; la variante `DURATION` s'appuie sur `wz_tooltip.js`, absent, et retombe sur la même structure CSS) ; `help` rend le libellé en `disabled_link`, comme WIMS le fait déjà en mode examen, faute de pages d'aide par module côté PAX. **Le CSS était indispensable** : sans `.wims_tooltip > .wims_tooltiptext {visibility:hidden}` (ajouté dans `frontend/assets/css/main.css`), le texte de l'infobulle s'afficherait en clair au milieu de l'énoncé. 27 exercices rendent à nouveau du contenu perdu. **`editarea`** (13) ajouté ensuite : `editarea.phtml` n'est qu'un `<textarea readonly>` dimensionné sur le contenu, pas un widget — et son absence rendait `oefpython.fr/liste_portee1` **insoluble** (l'énoncé demande la valeur finale d'un script Python qu'il n'affichait pas). Reste ignoré : `codeinput` (6) — mécanisme faisable (identique à `mathmlinput`), mais son contenu vient de `slib/function/tabsignes` qui ne produit encore rien d'exploitable ; **`glossary`** (4) implémenté depuis : les 26 fiches de `mathematics/statistics` (112 Ko) sont vendorées dans `ressources/wims-scripts/data/glossary/`, l'ancre reste dans la phrase et la définition s'ouvre au survol dans la même structure `.wims_tooltip` que `\special{tooltip}`. Là encore le special silencieux emportait **l'ancre** : la solution de `descriptives.fr/ecarttype` s'ouvrait sur « est la racine carré de la . ». NB : `oefstatistiques` référence `cumulate_frequency1`, coquille pour `cumulative_` — fiche absente y compris dans WIMS, l'ancre est rendue seule.
- [x] **`slib_out` écrasé par les commandes sans résultat** : dans `_run_script_lines`, toute commande `!xxx` isolée stockait son retour dans `slib_out`. `slib/function/tabsignes` assemble son tableau dans `slib_out` puis termine par le `!reset` de ses variables de travail — qui renvoie `""` et **emportait le tableau avec lui**. Structurel : tout slib finissant par un nettoyage perdait sa sortie. Désormais seul un résultat non vide écrase.
- [x] **`!replace` avec un motif vide** : `"ab".replace("", "X")` vaut `"XaXbX"` en Python alors que WIMS ne remplace rien. `tabsignes` écrit `!replace internal $empty by \qquad \qquad in $slib_cel` pour espacer ses cellules vides, ce qui hachait tout le reste : son marqueur `reply1` ressortait en `\qquad r\qquad e\qquad p\qquad l\qquad y…`.
- [x] **`!itemcnt` ignorait les cases vides** : `"f'(x),,reply4,,reply5,,reply6"` était compté 4 au lieu de 7. Or entre virgules un trou porte du sens — les colonnes sans signe d'un tableau de variation en sont — et `tabsignes` bâtissait 4 colonnes au lieu de 6. Entre **tabulations** au contraire, ce sont des lignes : une ligne blanche n'est pas un item, et chaque `,<TAB>` fabriquerait un fantôme (le tirage de `oefsuites1S/cvgequot` tombait alors sur un énoncé vide). Deux fausses pistes écartées en chemin, toutes deux invisibles au rendu et rattrapées par le diff des 9991 `expected` : aligner le découpage sur celui de `!item` protège les crochets, et `[0,4,3.5]` compté 1 au lieu de 3 cassait les moyennes de `oefstat/mean` et `bergamo5/6`. **Gains** : 14 `expected` corrigés — les 4 masses molaires de `mole.fr` retrouvent le début de leur formule (`0+U*238.03+F4*227.0278` et non `+F4*227.0278`), et les 5 intervalles de fluctuation leurs deux bornes distinctes (`0.025` / **`0.975`**, identiques auparavant) débarrassées de leur `UNKNOWN_CMD`.
- [x] **`\special{codeinput}`** (6 usages) : un bloc de code dont chaque marqueur `replyN` devient le champ de la réponse N — le principe de `mathmlinput`, appliqué à du texte. Les marqueurs longs passent d'abord (`reply10` avant `reply1`, ce que WIMS obtient en triant ses lignes à l'envers), et les délimiteurs math sont absorbés avec le marqueur : `tabsignes` place les siens en `\(reply1\)`, et les laisser donnerait du HTML à composer à KaTeX. Les 6 exercices rendent désormais leurs champs. Le chemin d'affichage existait déjà : un champ dans une `<table>` est volontairement laissé en `<input>` natif dans le segment html (`engine.py:388`), lié côté front par délégation d'événements.
- [x] **Helpers PARI et valeurs de l'interpréteur** : `_wrap_helper` ne convertissait que les *sorties*. `matsize` ne reconnaissait donc pas un `PMat` et retombait sur son `[1,1]` par défaut — `tabsignes` lisait 1 seule position de réponse au lieu de 6. La conversion est désormais bidirectionnelle.
- [x] **`!distribute items` et les crochets englobants** : une paire entourant *toute* la chaîne est la notation de liste, pas une protection de virgules. `[[1,2;1,4],[2]]` (positions puis rang de départ, tel que `tabsignes` les reçoit) arrivait en un seul item. **Bug corrigé au passage** : `oefoperpython/permlist` attendait la liste *inchangée* comme résultat d'une permutation circulaire — un élève qui ne faisait rien avait bon ; l'attendu est maintenant la liste décalée.
- [x] **Interpréteur PARI — fonctions utilisateur et listes** : `f(x)=corps` (y compris entouré de parenthèses, forme de `slib/stat/histo`), `local()`, et le type mutable `List` avec `listinsert`/`Vec`/`vecsort`. Débloque le `matsort` de `tabsignes` : ses positions de réponses étaient extraites sous forme de **source PARI brute** (`slib_pos_rep_1 = 'matsort(mat)=A=[mat];L=List([])…'`), elles valent maintenant `1;2`, `1;4`, `1;6`, `2;3`, `2;4`, `2;5`. Ces constructions n'apparaissent nulle part dans les 4135 `!exec pari` des `.def` — seulement dans 3 slib (`tabsignes`, `stat/histo`, `stat/binomial`), dont les deux derniers ne laissaient rien fuir dans le rendu. Corpus : 0 `expected` modifié, statuts identiques.
- [x] **`isitemof` et `!positionof item` découpaient sans protéger les crochets** : un `split(",")` naïf faisait de `[1,2],[3,4]` quatre morceaux. `slib/function/tabsignes` teste `[ligne,colonne] isitemof <liste de couples>` puis cherche `positionof item [ligne,colonne]` pour numéroter la réponse — le premier était donc toujours faux, le second toujours 0, et **toutes les cellules recevaient le même numéro** (`0 + rang - 1`). Les espaces de présentation sont désormais ignorés de part et d'autre, GP écrivant `[1, 2]` là où le `.def` compose `[1,2]`. Corpus : 0 `expected` modifié sur 9991 malgré 516 usages d'`isitemof` et 1011 de `positionof`.
- [x] **Indices en liste dans `$(var[ligne;colonne])`** : `calc.c` (`_blockof`, branche « sinon ») accepte pour un indice une **liste séparée par des virgules**, évalue chaque terme et **ignore** ceux hors bornes au lieu d'échouer. PAX ne gérait que l'indice simple et la plage `a..b` (`_select_cols`), si bien que `$(m[1;2,4])` retombait sur la chaîne vide. C'est la notation de tout brassage de matrice : `arithtable` écrit `val6=1,0;0,0` puis `$(val6[$val9;$val10])` avec deux permutations tirées au sort. La sélection vide, **aucune case n'était marquée « déjà remplie »** et les 16 réponses déclarées recevaient toutes un champ — quelle que soit la taille du tableau. Les 21 `arithtable` rendent maintenant exactement R×C cases (4, 6, 8, 9, 12 ; les variantes `partial` moins). La branche « liste de lignes » passe par le même sélecteur, `[liste;liste]` ne rendant rien auparavant ; une ligne dont la sélection est vide compte quand même, `calc_columnof` ajoutant un séparateur par ligne sans condition. Corpus : 4296 OK / 0 fail, **6 `expected` corrigés** (`evolmeth1` ` ;` → `Ongles` ; `evolmeth3/5` et `cramnom2`/`cramform2` retrouvent un compte 7 et 3 au lieu de 0 ; `11LigneTrigoUniteEtape` 1 → 3) et 344 réponses fantômes supprimées (342 = les champs surnuméraires d'`arithtable`, 2 = `cramnom1`/`cramform1`, tributaires d'`imagefill` et non fonctionnels dans les deux états).
- [x] **Plages et listes d'indices pour `!row` et `!word`** : `calc.c` route `item`, `line`, `row`, `word` et `char` par le **même** `_blockof` — tous acceptent donc un indice, une plage (`3 to -1`, `2..3`) ou une liste (`1,3`). PAX avait bien ce sélecteur générique, mais seuls `!item` et `!line` s'y branchaient ; `!row` et `!word` ne géraient que l'indice simple et rendaient vide sur tout le reste. `arithtable` lit ses données par `val33=!record N of src/data_<lang>` puis en extrait la liste de nombres par `!row 3 to -1` : la plage rendant vide, aucune valeur n'était tirée et les cellules affichaient `expand((f = s \in) + ())`. Les 21 exercices sont désormais **entièrement jouables** (vérifié dans le navigateur : `table2x2` tire `2 2 5 3`, sommes 4/8 et 7/5, notation 100 %). `!row` ressort les lignes avec leur séparateur d'entrée, comme `calc_rowof`. Corpus : 4296 OK / 0 fail, **160 `expected` corrigés**, aucune réponse ajoutée ni perdue — 138 pour `arithtable`, 21 pour `oefcountries`/`oefdepregfr` dont les colonnes de pays étaient vides, 1 pour `photosynthesis`.
- [x] **`!rename` — drapeaux d'`oefcountries`** (14 exercices) : dans WIMS (`calc_rename`) la commande pose un lien symbolique de session et renvoie une URL `getfile/rename-<aléa>`, pour servir un fichier sans exposer son chemin. PAX servant `ressources/` par `/api/static`, la traduction suffit — ni lien ni aléa. Non reconnue, elle ressortait **dans l'attribut `src`** (`<img src=UNKNOWN_CMD:rename>`) : images cassées. La liste blanche de chemins de `calc_rename` est reprise, complétée par son refus des `..` — l'argument vient du `.def` et rien ne doit pointer hors de `ressources/`. Les 256 `-lgflag.gif` (1,5 Mo) sont vendorés dans `ressources/wims-gifs/flags/`, le miroir que `_find_wims_gifs_dir` connaît déjà. **Deux corrections front étaient nécessaires** : `prefixStaticUrls` exigeait un guillemet après `src=` (l'OEF écrit `<img src=$val14>` sans), et les colonnes d'un `correspond` sont rendues telles quelles par le composant, donc hors du chemin des segments `html` — elles n'étaient pas préfixées. Vérifié dans le navigateur : les 5 drapeaux s'affichent. Corpus inchangé (les images sont à l'affichage, pas dans les `expected`).
- [x] **`\special{imagefill}`** (14 exercices) : des champs `clickfill`/`dragfill` posés sur une grande image. WIMS empile des calques DynAPI à des coordonnées absolues ; en CSS cela se réduit à un conteneur `position:relative` et des cases `position:absolute` — c'est tout le mécanisme, et c'est ce qui rendait ce special « tributaire de dragfill » une fois celui-ci fonctionnel. Non reconnu, il affichait l'image **sans la moindre case** : insoluble. Deux points de portage non évidents : `imagefill.phtml` traduit les tabulations en `;` **puis** découpe sur `;`, donc les deux séparateurs sont équivalents — `oefmolecule` livre ses champs en `;` et rendait 0 case tant que je ne découpais que sur tabulation ; et le conteneur doit être **exclu de la segmentation** (`_unsplittable_ranges`, généralisation de `_table_ranges`), sans quoi les cases sortent en segments et perdent leur positionnement. **9/14 vraiment exploitables** (`lewis` affiche ses 15 cases mais n'en note que 3, cf. ci-dessous) (6 au premier jet, puis 4 de plus une fois les bugs amont ci-dessous corrigés). Vérifié dans le navigateur sur `vocabulaire3` : cases aux positions exactes déclarées par le `.def`, étiquettes posées **sur l'image**, retour par case en rouge/vert après correction, notation conforme. Corpus : 4296 OK / 0 fail ; **+15 réponses**, toutes dans ces 14 fichiers — leurs `replyN` n'étaient référencés par aucun widget et se faisaient filtrer. Les 4 restants ne tiennent pas au special : `cramnom2`/`cramform2` sont en `type=click`, que l'`imagefill` de WIMS ignore aussi (`iswordof clickfill dragfill`), et `unitecell/2`-`3` gardent un défaut d'évaluation propre.
- [x] **Quatre bugs d'évaluation en amont, trouvés en remontant la chaîne d'`imagefill`** — c'est la « cause commune » soupçonnée derrière `arithtable`, `evolmeth` et `unitecell` : (a) **`!embraced <op>`** ne choisissait rien de juste. `calc_embraced` ne prend pas un item dans la liste : il remplace **chaque groupe `{…}` sur place** par `op` appliqué à son seul contenu, en laissant le texte autour intact. C'est ce qui permet à `unitecell` d'écrire `232,197;Membrane,{coords…};Cytoplasme,{coords…}` et de récupérer le squelette avec une coordonnée par ligne — taille en ligne 1, un organite par ligne ensuite. PAX concaténait le contenu de tous les groupes et jetait le reste (le code le disait : « *a bit of a guess* »). 168 usages. (b) **`!randitem` ne protégeait pas les crochets** : `[227,13],[18,120]` valait quatre items au lieu de deux, d'où des coordonnées coupées en `13]`. Invisible dans le `.def`, l'argument étant presque toujours une variable. (c) **Plage de lignes `$(m[2..-1;])`** non gérée par `_resolve_indexed2` — même famille que `!row 3 to -1`, corrigé plus haut. (d) **`isitemof` ne découpait qu'aux virgules**, jamais aux tabulations : il était donc **toujours faux** sur une liste tabulée. `mathelexikon` garde ses champs actifs dans un `r 1<TAB>r 2<TAB>…` et son `!if r $m_k isitemof $val105` ne passait jamais, si bien qu'**aucun `\embed` n'était émis** — ses 15 exercices s'affichaient sur un énoncé vide, leurs 40 champs venant du seul filet de repli, avec des attendus vides. Ils rendent désormais leur contenu et le bon nombre de champs (13 pour `Declinaisons`). **Bilan corpus** : 4296 → **4299 énoncés rendus, 0 vide** (contre 3) ; 36 fichiers changent de nombre de réponses, −505 au total — ce sont des champs fantômes qui disparaissent, le compte s'alignant sur les champs réellement affichés.
- [~] **Découpage en items : `listuniq` et `listcomplement` corrigés, `itemcnt` bloqué en amont.** `find_item_end` vaut `strparstr(p, ",")` (`liblines.c`) : la virgule ne sépare qu'à profondeur zéro, les paires `()`/`[]`/`{}` protégeant leur contenu — et il n'y a **aucun déballage** de la paire englobante. Cinq commandes l'ignoraient (`listuniq` 480 usages, `itemcnt` 1392, `shuffle` 3702, `listcomplement` 170, `sort items` 34), après `isitemof`/`positionof`/`randitem`/`distribute` déjà corrigés. `listuniq` et `listcomplement` sont alignés : **corpus strictement inchangé** (0 fichier modifié), et `lewis` gagne un attendu. **`itemcnt` est en revanche à laisser tel quel pour l'instant** : la protection ne gagne que `lewis` (15 → 5 champs) et **casse `oefstat/mean`**, dont la moyenne passe de `3.97368421053` à un `print((…)` non évalué — sa ligne arrive encore entourée de crochets côté PAX là où WIMS l'a déjà déballée. Le correctif est donc **le déballage amont**, pas `itemcnt`. Piège de mesure à retenir : le nombre de réponses ne bougeait pas, seule leur *valeur* changeait — comparer les `expected`, pas les comptes. **`itemcnt` et `makelist` sont corrigés — mais seulement ensemble.** Pris isolément, chacun casse : `itemcnt` protégeant les crochets fait passer `slib/stat/dataproc` dans sa branche **pondérée** (la bonne), mais celle-ci reçoit un `slib_weight` tabulé, invalide en PARI, et `oefstat/mean` ressort son `print((…)` en clair ; `makelist` joignant par virgules (`_values` : `if(pp>p) *pp++=','`) corrige ce `slib_weight` mais pas la garde `!if $slib_datacnt=1`. Appliqués **conjointement**, la moyenne est juste. **Bilan corpus** : une seule valeur perdue (dans `lewis`, en cours de restructuration), **16 récupérées depuis du vide** (`sdsigne3/5/6/7`…), 42 autres corrigées — les menus de `symax2`/`symcen2`/`rota2` passent d'**1 option** à leurs 20, `bouclefor`/`bouclewhile` retrouvent le bon rang de bonne réponse (vérifié contre leur masque `val44`), et `lewis` perd ses 10 champs fantômes. Deux pièges de méthode à retenir : comparer les `expected`, pas les comptes (aucun des deux effets ne se voyait sur les comptes) ; et un `expected` qui rétrécit n'est pas une perte — celui de `symax2` contenait tout son vivier, parti depuis dans `options.choices`, où il devait être. **La suite est cadrée par [`docs/refactor-item-splitting.md`](docs/refactor-item-splitting.md)** : analyse complète des primitives C (`liblines.c`), axiome central (la tabulation n'est **jamais** un séparateur dans WIMS — toutes les branches tab de PAX sont des compensations en paires producteur/consommateur), inventaire des 11 découpeurs + 26 `re.split`, programme en 5 phases (socle `wims_lists.py` → producteurs → consommateurs → suppression des compensations → nettoyage) et protocole de validation avec exercices sentinelles. Débloque à terme `lewis` (18 étiquettes), `moles`/`mouvrel` sans hack, et probablement `geo6`/`evolmeth2`.
- [~] **`lewis` (`oefmolecule`, « Représentation de Lewis »)** : de 15 champs fantômes à **7 champs pour 7 cellules réelles**, et sa palette affiche enfin ses symboles de liaison (traits parallèles : simple, double, triple). Quatre bugs levés en remontant sa chaîne : `listuniq` déchiquetait `val26` ; `itemcnt`+`makelist` ont supprimé les champs fantômes ; **le découpage des colonnes ne protégeait pas les parenthèses**, si bien que la grille de la molécule était lue sur une ligne au lieu de trois ; et **la tabulation interne réduite à une espace** fusionnait les commandes flydraw d'un même symbole, d'où des zigzags à la place des traits (devenue saut de ligne). **Reste** : la palette compte 10 entrées là où WIMS en montre 18 — il **manque les atomes et leurs doublets non liants**. Cause identifiée : `val24`, la liste des directions, s'écrit `0,r,u,…,rru,<TAB>ull,lld,…` avec une tabulation cosmétique ; `_split_items` la prend pour un séparateur et n'y voit que 2 items, donc `!positionof` échoue et aucune entrée d'atome n'est produite. Faire primer la virgule (le comportement de WIMS) **rend les 18 entrées** mais casse `moles.fr`, `moles.nl` et `mouvrel.fr` : leur `val14` passe de `5` à un `rint(rint(…))` non évalué et 30 `expected` se vident. Même mur que `itemcnt`/`makelist` — à reprendre avec ces trois modules.
- [~] **Figures dans les palettes et les attendus** : le marqueur interne `<img src="/api/render/svg/…">` — choisi pour survivre aux découpages de listes WIMS — n'était incorporé que dans l'énoncé, pas dans `options["choices"]` ni dans `expected`. Il **ne peut pas sortir tel quel** : le cache SVG vit en mémoire du backend, et un rendu resservi par Redis laisse l'URL sans image (le backend répond 404 sur sa propre URL). `oefmolecule/lewis` affichait ainsi **10 étiquettes vides** là où il faut choisir des liaisons. Palette et attendu sont traités ensemble — ce sont deux chaînes comparées l'une à l'autre. 25 fichiers concernés, 12 `expected` modifiés, corpus par ailleurs inchangé. **Reste** : 41 URL non résolues dans 15 fichiers (`bergamo4` 11, `patrons3` 8, `baton` 6, `oefmecanics`, `Ocean*`…) — leur clé n'est jamais générée pendant le rendu, donc le dessin correspondant n'est pas produit. Cause distincte, à chercher du côté des valeurs `?analyze` et des `ins_url` réutilisés d'une étape à l'autre.
- [x] **`slib/function/tabsignes` — fonctionne**. Les 6 exercices rendent leur tableau de signes avec les champs aux bonnes cellules et la bonne numérotation (`reply2…reply7` pour un rang de départ 2) : 31 champs contre 20, et **plus aucun marqueur `replyN` affiché en clair**. Restent deux limites bénignes : `reply6` hors d'atteinte sur `ederive` — mais `nbcol` vient de la ligne 1 (6 éléments) quand la ligne 2 en a 7, c'est le `.def` qui est déséquilibré et WIMS se comporterait pareil — et une indexation multiple `$(slib_content[[1;2;1;4;…]])` non évaluée en fin de sortie.
- [x] **Commentaires `!!` dans les slib** : `_run_script_lines` sautait `#` et `:` mais pas `!!`, le commentaire WIMS. Chaque ligne de commentaire partait dans le dispatch de commandes et en revenait avec `UNKNOWN_CMD:!`, qui **écrasait `slib_out`** — `slib/function/tabsignes` ne renvoyait que son bandeau de version (`!!!! tabsignes v1.22`, ligne 1). 9 artefacts `UNKNOWN_CMD` étaient **visibles dans les énoncés** (`oeffluctuation.fr` ×5, `oefpolynet.fr` ×4) ; il n'en reste aucun dans le corpus. Trouvé en cherchant pourquoi `codeinput` restait vide.
- [x] **`\embed` lignes supplémentaires** : `anstype/inputcss.inc` découpe le paramètre de taille en lignes — la **première est la taille**, les suivantes des attributs HTML du champ (`\embed{reply 1,30 autofocus}` compile en `r1,30<TAB>autofocus`). PAX prenait la chaîne entière pour la taille : non numérique, elle retombait sur le défaut, et **95 champs du corpus étaient rendus à la mauvaise largeur** (la plupart à 10 au lieu de 6). Les attributs eux-mêmes transitent désormais en `data-attrs` (JSON) → segment `attrs` → `v-bind` sur le champ ; **331 exercices** en portent. La liste blanche (`_parse_input_attributes`) est le point important : la queue est du contenu d'exercice, et un `on…` posé par `v-bind` s'exécuterait. `_SEGMENT_PATTERN` avale l'attribut de façon non capturante (`[^>]*`) et le relit depuis le groupe 0, sans décaler les numéros de groupe. **Le corpus n'y gagne rien de visible** : ses deux seuls attributs sont déjà appliqués sans condition par le front — `autocomplete="off"` en dur sur chaque champ, et `autofocus` par le focus automatique du premier champ texte à chaque chargement (`BaseExerciseStatement.vue`). Vérifié : les 355 `autofocus` du corpus portent **tous** sur le premier champ. Le watcher préfère malgré tout le champ marqué quand il y en a un (l'attribut HTML seul ne focalise pas un élément inséré après le parsing du document), et `maxlength`/`placeholder`/`readonly`… fonctionneront le jour où un exercice en posera. Le mot-clé `default` → `class="wims_oef_input"` a 0 usage corpus.
- [ ] `exec` : maxima/pari seulement ; `octave`/`gap`/`float_calc` → vide silencieux (§2.5) — **0 usage corpus** (`!exec` n'apparaît qu'en `pari` ×4135, `maxima` ×3907, `canvasdraw` ×5), donc différé au même titre que flydraw
- [x] **PARI impératif** : mini-interpréteur `core/oef/def_engine/pari_prog.py` — séquence `;`, affectations (scalaires et indexées), `for`/`while` bornés, `if` paresseux (instruction *et* expression), `print`/`print1` accumulant la sortie, `sum`/`prod` à variable liée, vecteurs/matrices **1-indexés**, transposée `~`, `concat` vectoriel, constantes `true`/`false`. **Session partagée** entre les `!exec pari` d'un même exercice (`DefEngine.pari_session`) : WIMS pilote un unique `gp`, si bien qu'`oefforpython.fr` définit `l=vector(n);for(…)` dans un appel et l'affiche par `print(l)` dans le suivant. Sortie post-traitée comme `wims/src/Interfaces/pari.c` (une ligne par `print`, crochets englobants retirés). Hors périmètre (`f(x)=…`, `local()`, `List()`) → `PariProgramError` et repli sur l'évaluation d'expression, exécution atomique vis-à-vis de la session. Corrige `liste_portee1/2` (`'i'`/`'='`/`'1+1'` → valeurs), les 18 `oefforpython.fr` (`'l'` → la liste), `BoucleWhile` (30 réponses vides → les 7 étapes de la boucle), `permlist`, `quadrilatere` (coordonnées au lieu de la source). Les ~28 exos de biologie/géographie en `divrem(a,b)~` calculent enfin leur **pagination** (`val67 = q+1`) : ils exposent la page réelle au lieu de la totalité des `?analyze` — ils restent néanmoins non fonctionnels faute d'`imagefill` (0 champ rendu, cf. `\special` ci-dessus). Corpus : 4296 OK / 0 fail, inchangé. **Bug corrigé au passage** : `_pari_concat` concaténait *textuellement* (`concat(5,1)` → `"51"`) alors que les 36 fichiers du corpus l'utilisent pour accumuler des listes.
- [x] **`!translate` — délimiteurs `$…$` sur la cible** : `_cmd_translate` ne déballait `$…$` que sur la source, si bien que `!translate internal ; to $\<LF>$` (dans `slib/stat/dataproc`) remplaçait `;` par un `$` littéral. Données et effectifs restaient collés (`1,4,6,7,8,12$2,3,3,7,6,2`), `slib_weight` vide → **toute statistique pondérée basculait silencieusement dans la branche non pondérée**, avec un effectif faux. WIMS applique `substit()` aux trois opérandes de la même façon (`calc.c:calc_translate`). Corrige `ecarttype2` (écart-type 2.21 → **2.59**, exact), `meanw` (4.96 → **291/35**, exact), `ConnexionInt2` (source `rint(rint(/*100)…)` non évaluée → `698-200,698+200,698`). C'est le seul appelant de la branche pondérée de `slib/stat/variance` — donc le seul cas du corpus qui exerce réellement le mini-interpréteur PARI ci-dessus. Corpus inchangé (4296 OK / 0 fail), 3 `expected` modifiés, tous vers la valeur juste.
- NB : contrairement à ce qui était noté ici, `bergamo6` **n'a pas de bug** — il appelle `slib/stat/variance` avec un seul argument (branche non pondérée, sans PARI) et ses valeurs sont exactes (moyenne −1, variance 50/17 → 2.9). Les `!endif` annotés (`!endif weight`) sont gérés depuis longtemps, côté parser (`def_parser.py`, `startswith("!endif")`) comme côté slib (`slib.py`, `re.match(r"!endif\b")`).
- [ ] Flydraw : manquent `levelcurve`, `affine`, `copyresized`, `plotjump`/`plotstep`, `filltoborder`, `diamondfill`/`dotfill`, `rays` — 0 usage corpus → différé
- [x] Corriger `docs/types-exercices-reponses.md:82` : `symbols=` n'est pas « variables autorisées de formal » mais une option d'UI transverse (palette de boutons insérant au caret, cf. `wims/.../anstype/symbols.inc`) — 0 usage corpus, l'implémentation reste à faire côté front si le besoin apparaît

- [ ] **Facteur 1 explicite dans les produits rendus en LaTeX** : PAX construit des `Mul(1, …, evaluate=False)`, que sympy imprimait `1 \cdot \frac{1}{x}` en 1.12 et imprime `1 \frac{1}{x}` depuis 1.14 — soit, pour un élève, un nombre mixte (« 1 et 1/x »). Le `\cdot` ne corrigeait rien, il rendait le défaut supportable : **ce facteur 1 n'a pas lieu d'être**, et c'est à la construction de l'expression qu'il faut le supprimer, pas à l'affichage. Repéré en mesurant la montée sympy 1.12 → 1.14 (PR #41) : 25 des 178 rendus modifiés sur 12 897 en viennent, dont `oefordrevabs.fr/deducencad2`, `OEFevalwimsfctref.fr/assocgr1` et `OEFevalwimsfnctg.fr/chforme5` (où il touche une palette de QCM). Le point de construction reste à localiser — vraisemblablement côté `cas.py`/`_sympify_arg`, là où un coefficient est appliqué à une expression déjà formée.

Conforme (vérifié) : opérateurs compare.c, indices négatifs/tranches, `\for`/`\while`, alias `r1`/`reply1`/`rep1`, `\feedback` + `sc_reply`/`m_reply`, bonnes réponses multiples, `case` avec `|`, `correspond`+`split`, virgule décimale, `\hint`/`\help`/`\solution`, `\css`.

### e) Audit de fidélité du 2026-09-06 (réf. `docs/wims-reference/introProgOEF.pdf` §1.3 + `anstype/*`)

Les 28 exemples chiffrés du manuel ont été rejoués tels quels contre
`check_answer` : **25/28 au départ, 28/28 à l'arrivée**. Les trois écarts, et
ce que la source d'`anstype/` a appris :

- [x] **`case` mettait tout en minuscules** — sa docstring l'avouait « faute
  d'un cas du corpus ». `anstype/case` compare par `!if $dd=$g` : `Dollar` est
  faux pour `dollar`, c'est `nocase` qui l'accepte (§1.3.3).
- [x] **`algexp` acceptait `(x+1)(x-1)` pour `x^2-1`** — l'équivalence
  rationnelle seule ne suffit pas. `anstype/algexp` exige `ratsimp(good-dd)=0`
  **et** `$t2 isitemof $t1`, la forme *imprimée* par Maxima : elle replie les
  coefficients (`(24+4)*x-53` = `28*x-53`) mais ne développe pas un produit.
  Refusé désormais en `badform`, comme pour `numexp`.
- [x] **`function` était une comparaison symbolique** : `5*x+0.000001` ne
  valait pas `5*x` (§1.3.5.1). `anstype/function` échantillonne dans
  `\range` (`leftrange`/`rightrange`, défaut `-5,5`) et juge l'écart moyen à
  `1/precision` (juste) puis `1/sqrt(precision)` (juste à `precweight` près) ;
  une variable hors de celles de l'attendu — `5*t` pour `5*x` — est refusée.
  Après la fonction, `\answer{}{\g,x,t}` liste les **variables** permises,
  pas des alternatives : `function` sort du découpage en `|`/`,`. **Hypothèse
  consignée** : `$testnum`, le nombre de points, n'est défini nulle part dans
  l'arbre WIMS que nous avons ; PAX en tire 20 d'une graine fixe.
- [x] **Tailles par défaut des champs** : sans second argument à `\embed`,
  PAX rendait 10 partout. Chaque `anstype/<type>.input` borne `inputsize` et
  pose son défaut (`numeric` 20, `algexp`/`atext`/`case` 40, `numexp` 20,
  `reorder` 10…) — repris dans `_TAILLE_DEFAUT`. C'est la seule source de
  diff sur les snapshots de cette passe : 3978 fichiers, largeur seule.
- [x] **`scorepower` et `penalty` ont bien un consommateur** — cf. §6 ci-dessous.
- [x] **Un seul moteur de rendu.** Le couple `core/oef/parser.py` +
  `evaluator.py` (Lark, 1927 lignes, plus `strategies/condition.py` et leurs
  tests) ne servait plus qu'au repli de `load_and_render` quand un `.oef`
  n'avait pas de `.def` — et **4277/4277** en ont un. Supprimé ; un `.oef`
  orphelin lève `FileNotFoundError` au lieu de rendre autre chose que ce que
  WIMS rendrait. L'import (`scripts/import_exercises.py`) et le corpus de test
  lisent le `.def` eux aussi : l'import y gagne 51 titres (mojibake) et 87
  langues (`moles.nl` était étiqueté `fr`), et ses mots-clés — stockés
  jusqu'ici **lettre par lettre** (`{l,i,t,e,r,a,l,…}`) — une vraie liste.
  **La base en profite depuis le 2026-09-06** : l'import, jusque-là purement
  additif, actualise désormais les lignes existantes (`rafraichir`), et n'efface
  jamais un champ que le `.def` ne porte pas. 869 lignes corrigées — 800 listes
  de mots-clés, 86 langues (42 exercices catalans étiquetés `fr`, 20 portant la
  chaîne littérale `\lang`), 55 titres (traductions et mojibake `cp1252`).
  Effet de bord vu au passage : le corpus compte 42 exercices en `ca` et 82 en
  `it`, deux langues à virgule décimale absentes de `COMMA_DECIMAL_LANGS`
  (`core/oef/i18n.py`) — cf. §3 f) ci-dessous.
- [x] **Doublons de découpage** : sept copies locales de « couper au
  séparateur hors parenthèses » et deux de « ôter les parenthèses
  englobantes » (`checkers`, `pari_prog`, `presentation`, `cas`, `slib`,
  `_cmd_declosing`) rabattues sur `wims_lists.split_top_level`,
  `split_top_level_args` et `declosing`, bâtis sur `strparstr` — la primitive
  de `liblines.c` déjà portée.

**Divergences qui restent, connues et assumées** :

- `\choice` : PAX note par `choiceweight` là où `var.proc` compte `qcmgot` en
  boucle ; identique sur une bonne réponse par menu, à vérifier si un menu
  porte plusieurs bonnes réponses (cf. la « limite assumée » de §6).
- Les gardes d'affichage sur `seedcnt` (rejouer le même tirage) ne sont pas
  modélisées : PAX n'a pas de graine de session.
- Les commentaires HTML des énoncés traversent tels quels — WIMS les laisse
  aussi, mais son `answer.phtml` en retire certains marqueurs.

### f) Catalan et italien : la virgule décimale leur manque

- [ ] `COMMA_DECIMAL_LANGS` (`core/oef/i18n.py`) ne contient que `fr` et `nl`,
  alors que le corpus porte **42 exercices en `ca`** (`oefdevfact.ca`) et **82
  en `it`**, deux langues qui écrivent `3,14`. Ces exercices affichent donc
  leurs décimales à l'anglaise, et un élève qui saisit `3,14` n'est pas lu
  comme WIMS le lirait. Le point d'extension est prévu pour ce cas — ajouter
  les deux codes ne change rien d'autre — mais il demande d'abord de vérifier
  contre le WIMS de référence, comme la sévérité l'a été : un module catalan
  peut très bien avoir été écrit avec des points.

### g) Le point aveugle des tests : un attendu faux passe inaperçu

- [x] **Une sonde le cherche désormais** (`backend/scripts/sonde_attendus.py`,
  2026-09-07). `test_exercises_check` vérifie que l'attendu est *accepté* par
  le correcteur — ce qui reste vrai quand l'attendu lui-même est faux. C'est
  ainsi que `quizz/course12_2step` a pu attendre `1/2` pour un coefficient
  directeur valant `-1/2` pendant que les 21 017 tests passaient au vert : seul
  un signalement d'usage l'a révélé.

  La sonde confronte l'attendu à la seule autre source de vérité de
  l'exercice — son corrigé, déclenché en soumettant une réponse fausse. Elle
  est validée : sur le moteur d'avant le correctif, elle retrouve bien
  `course12_2step`.

  Premier passage sur le corpus, 3 graines : **990 attendus confrontés, 6
  signalements, tous faux positifs** — un corrigé qui pose l'équation sans la
  résoudre (`1125`), qui ne cite que des valeurs approchées (`1211`), ou qui
  donne un terme intermédiaire négatif (`pdtreel5`). Aucun défaut restant sur
  ce critère.

- [ ] **Élargir la couverture.** 990 attendus sur ~21 000 : la sonde n'examine
  que les réponses numériques d'exercices dont le `:feedback` affiche des
  nombres. Les autres familles restent sans second témoin. Pistes : les
  exercices dont le corrigé énonce la réponse en toutes lettres, et les types
  non numériques.

### h) Ce que l'import de H1, H2, H5 et H6 réclame (relevé du 2026-09-10)

Mesuré **au rendu** sur les 9 698 exercices (graine 42, sans cache —
`backend/scripts/sonde_manques.py`), puis comparé à H3/H4 : rien de ce qui
suit ne touchait le corpus d'avant l'import. Le moteur ne lève rien dans aucun
de ces cas, d'où la mesure plutôt que la lecture des sources.

- [x] **Les 29 slibs portées** (2026-09-10) — copiées dans
  `ressources/wims-scripts/` avec ce qu'elles lisent : `slib/circuits/drawcomp`,
  `slib/data/columnsort`, `oef/special/tooltip.phtml`, et les 81 fichiers de
  `data/circuits/` (lus par `!record`, que le premier relevé ne suivait pas).
  Copier ne suffisait pas : cinq défauts du moteur les empêchaient de rendre,
  corrigés d'après la source WIMS (`tests/core/oef/test_commandes_slibs.py`) :
  - `!sort` ne posait pas `wims_sort_order` (`calc.c:133`) et ignorait
    `nocase` — `columnsort` rendait vide, `drawtree` un arbre sans sommet ;
  - `!text delete|drop|remove` manquait (`text_remove`) — `drawcomp` ne
    tirait pas le nom de ses composants ;
  - `!default` substituait sa valeur sans l'évaluer (`exec_default`) —
    `balloon` posait le texte `!randint 1,1000` dans son CSS ;
  - `!slashsubst` manquait (`lines.c:806`) — l'infobulle de `tooltip`
    affichait `UNKNOWN_CMD:slashsubst` ;
  - un `!read` fait **depuis une slib** était ignoré s'il ne visait pas
    `slib/` — `drawcomp` ne chargeait pas `data/circuits/compdata`. Il se
    résout désormais comme une slib, et seulement pour les slibs.
  Trois autres sont apparus en vérifiant les sorties — une sortie non vide ne
  prouvait pas une sortie juste :
  - `!lines2rows` / `!rows2lines` joignaient et découpaient par
    **tabulations**, une paire producteur/consommateur restée hors de
    `wims_lists` après la refonte du découpage. `!row`, lui, ne coupe pas sur
    une tabulation : `columnsort` rendait sa table sans la trier ;
  - `!sort` sur une liste vide triait le mot `items` ;
  - `!makelist` / `!values` arrondissaient leurs bornes et ignoraient `step`
    (`cutfor`), et `!values` substituait sa variable en texte — `-1*x^2` en
    `x=-2` valait 4. `slib/function/bounds` rendait donc `items,items`, et
    l'attendu d'`oefintegrale/aire1` à `aire4` était faux ; le test « la bonne
    réponse donne 1 » passait quand même, puisqu'il soumettait ce même texte.
  Sur les 203 exercices qui les appellent, plus aucun `UNKNOWN_CMD` visible.
- [ ] **Ce que le portage des slibs ne règle pas.**
  - `chemistry/chemeq_el` et `chemeq_rev` (12 appels, `redox.fr`, `piles.fr`) :
    le port Python de `chemeq` rend `""` sur `,équation` et sur
    `H -> H ~ équation` ; `chemeq_tex`, déjà vendorisée, aussi. À étendre
    (`def_engine/chemeq.py`) d'après `wims/src/Misc/chemeq`.
  - `graph/graphviz` et `draw/graphvizpoints` (10 appels, `oeflceb`,
    `oefadsubrel`) : `!exec graphviz` suppose le binaire `dot`, absent de
    l'image. Ajouter `graphviz` au Dockerfile, ou dessiner le graphe dans le
    navigateur.
  - `text/crossword` (5 appels, `oefvocmarine`, `oefsolaire`) : `!exec
    crossword` est un binaire WIMS (`wims/src/Misc/crossword/crossword.c`,
    1 128 lignes) ; la grille sort vide.
  - `geo3D/threeD` (`OEFvocSolides/pave`) produit une applet Java, qu'aucun
    navigateur n'exécute plus.
  - ~~`intnum` non émulé~~ — la vraie cause était en amont :
    `integrate(f, x, a, b)`, l'intégrale **définie** de Maxima, repartait
    telle quelle (SymPy veut `integrate(f, (x, a, b))`), si bien que
    `function/integrate` se rabattait sur `intnum`. Corrigé dans
    `_call_maxima` : `aire1` à `aire3` rendent `21` et `111/4`, et se notent.
    `aire4` a suivi une fois `e` lu comme la constante (voir plus bas).
    `intnum` lui-même reste non émulé.
  - `utilities/tooltip` rend l'infobulle en CSS pur (`wims_tooltip`) : vérifier
    que le front porte ces classes.
  - L'idiome du `$` nu. WIMS efface un `$` suivi d'un blanc (`substit`,
    `evalue.c:57`) ; PAX le garde, et il reste dans le TeX de `text/matrixtex`
    comme dans les commandes de `circuits/draw`. Une règle posée dans `_subst`
    a cassé 10 tests : PAX substitue à d'autres moments que WIMS, et parfois
    deux fois — la correction se fera là où l'idiome est lu, pas en bloc.
    **Premier cas réglé (2026-09-11)** : l'affectation `nom=$ $` d'une slib
    vaut une espace (`_dollars_nus`, `slib.py`), seule forme où la valeur
    n'est faite que de `$` et de blancs. `ecriturenombre` écrit ainsi son
    séparateur de milliers : les étiquettes d'`OEFevalwimsope/oefgrandeur*`
    montraient `8$ $000`, et leur somme `$[8$ $000+9$ $000]` ne s'évaluait pas
    (réponse 80 000 au lieu de 20 000). Restent `matrixtex`, `circuits/draw`
    et `oef/embed.phtml`, où le `$` nu est au milieu d'un texte.
- [ ] ~~**29 slibs WIMS absentes de `ressources/wims-scripts/`.**~~ Relevé
  d'origine, conservé pour mémoire : `_run_slib` ne les trouvait pas et
  rendait la main sans rien produire. Les plus appelées :
  `function/integrate` (78 rendus), `text/balloon` (70), `circuits/draw` (46),
  `draw/drtgraduee` (26), `stat/multinomial` (26), `data/randline` (21),
  `chemistry/chemeq_add|el|components|rev` (31 à elles quatre),
  `polynomial/random` (13). Toutes existent dans `wims/public_html/scripts/slib/`,
  mais les copier ne suffira pas toujours : trois lisent un fichier lui aussi
  absent du sous-ensemble vendorisé (`slib/circuits/drawcomp`,
  `slib/data/columnsort`, `oef/special/tooltip.phtml`), `graph/graphviz` appelle
  `!exec graphviz`, et `text/balloon`, `utilities/tooltip`, `geo3D/threeD`
  produisent du HTML/JS à éprouver dans le front. `utilities/env` (74 rendus,
  `OEFevalwimsope.fr`) n'existe nulle part, pas même dans WIMS.
- [ ] **`UNKNOWN_CMD:changeto` s'affiche dans l'énoncé de 81 exercices**
  (H1 6, H2 2, H5 31, H6 42) — symptôme des slibs absentes. Une slib
  introuvable laisse `slib_out` tel quel ; il porte alors ce que le `var.proc`
  du module y a laissé, et la dernière ligne de ce fichier,
  `!changeto oef/var.proc`, est une commande que l'exécuteur de scripts ne
  connaît pas. Deux corrections, indépendantes du port des slibs : vider
  `slib_out` quand la slib manque, et traiter `!changeto` comme la fin du
  script courant.
- [x] **Programmes `!exec` portés** (2026-09-10, `def_engine/programmes.py`) :
  `moneyprint` (`moneyprint.c`, arrondi d'une liste), `float_calc` (le sous-
  ensemble de `bc` des changements de base d'`oefnumeration.fr`), `lceb`
  (`lceb_dynopt.c`, bizarreries du C comprises, plafonné pour tenir le budget
  de rendu — moins de 0,05 s sur `oeflceb.fr`).
- [ ] **`graphviz`** reste non géré (6 rendus, et 2 en H4) : il suppose le
  binaire `dot` (voir plus bas).
- [x] **Synonymes de commandes WIMS** (`wims/src/calc.c`), ramenés à leur
  commande à l'entrée de `_eval_cmd` : `items`, `itemcount`, `position`,
  `listunique` ; et `evalsubst` (`mathsubst` puis `evalue`). `derivzoom.fr`
  n'affiche plus `UNKNOWN_CMD:evalsubst`, et son attendu
  `y=a*b*e*l*s**2*t*u*unknown_cmd*v…` est redevenu une droite.
- [x] **L'intégrale définie de Maxima** (`integrate(f, x, a, b)`) : SymPy
  voulait `integrate(f, (x, a, b))`. Faute de quoi `function/integrate` se
  rabattait sur `intnum`, non émulé — les attendus d'`oefintegrale` (3),
  `oefprobtes` (5) et `oefintts` restaient des `intnum(…)`.
- [x] **Trois attendus faux qui passaient à vide** (2026-09-10) — le test « la
  bonne réponse donne 1 » soumet l'attendu, fût-il du texte :
  - `e` est la constante d'Euler pour Maxima (l'en-tête de
    `src/Interfaces/maxima.c` pose `e:%e`) ; SymPy le lisait comme un
    symbole, et `e^(-x-3)` s'intégrait en `Piecewise(… /log(e) …)`
    (`patternPrimitives/primExpo`, `primPuissEnt`, `oefintegrale/aire4`) ;
  - `subst(x=a, F)`, la forme à équation de Maxima (20 `.def`), repartait
    telle quelle : `oefinteg1/Calculintgral3` attendait la chaîne
    `subst(x=-3,…)-subst(x=-4,…);` ;
  - dans la foulée, l'infini `inf` des bornes de `limit`/`integrate`
    (`oefprobtes/loiexpo1`, espérance lue `…f*i*n…` ; `limpolfrac`, qui attend
    `minf` en sortie) — mais **symbole** partout ailleurs, comme chez Maxima :
    le poser en `sympy.oo` partout a cassé 7 inéquations de H4, dont le
    `:postdef` calcule `fullratsimp(-inf-(-inf))` et attend 0 — et le symbole
    libre, que Maxima rend tel quel (`vide` d'`OEFexpalgTS/eqexpo1` sortait
    `d*e*i*v`) ;
- [x] **`fullratsimp` d'une équation**, simplifiée membre à membre
  (`OEFequdrt/point4`, `oefderivee1S`, `OEFbarypdtsc`, `OEFgeospace`) ;
  - rendu juste, `Calculintgral3` refusait encore son attendu : `check_numeric`
    lisait la réponse par `_parse_number`, sans fonctions, là
    qu'`anstype/numeric` fait `$[…]`. Il passe par `_eval_scalar`, et le détour
    `default` → `numeric` applique désormais le garde de
    `\computeanswer{no}`, comme le `!changeto` de WIMS.
- [x] **Des nombres à espace lus comme des produits** (2026-09-11).
  `oefsolaire/kepler3a` évalue `$[(4*pi^2*(1000*384 000)^3)/…]` ; PAX gardait
  l'espace, l'évaluation échouait, et la règle des zéros de tête finissait
  l'attendu en `384 0`. `strevalue` (`Lib/evalue.c`) fait
  `substitute(buf); nospace(buf);` : `_eval_arith` retire désormais toutes les
  espaces. `kepler3a` et `OEFevalwimsnumber/oefecrit103` (`1000`) se notent
  pour de bon. Deux garde-fous se sont imposés à la mesure :
  - un calcul qui **échoue** retombe sur l'expression avec ses espaces — PAX
    l'affiche faute de mieux, et `oefsequence/calcul_terme_suite` montrait
    `forn:1thru5` au lieu du programme `for n:1 thru 5` ;
  - la taille d'un `\embed` suit le `!bound inputsize between integer 1 and
    100 default N` des `anstype/*.input` : `h4droites/equationDe2pts`
    (`reply 1,20 6`) passait de 10 — l'ancien repli — à 206, là où WIMS
    retombe sur le défaut d'`equation`, 40.
- [x] **~~`\(…\)` dans une liste de réponses~~** — faux diagnostic :
  `OEFgeospace/interobjplan` n'avait plus d'anomalie une fois
  `fullratsimp(… = 0)` simplifié ; le contrôle qui la disait persistante lisait
  le cache Redis, non purgé. Retiré du `xfail`.
- [x] **`default` exigeait une forme sur un attendu numérique** (2026-09-11) :
  `anstype/default` aiguille vers `numeric` (`nn=$[…]`) avant toute question de
  forme ; la forme devinée par PAX ne s'applique plus qu'à un attendu qui ne
  s'évalue pas, et `_eval_scalar` connaît les constantes d'`evalue.c` (`e`, `E`,
  `pi`, `Pi`, `PI`). `2*exp(1)` vaut `2*e` sous `\computeanswer{yes}` ; sans,
  WIMS comme PAX refusent le calcul — `2*e` compris.
- [x] **L'écriture des réels suit `float2str`** (2026-09-11). `$[…]`,
  `!values`, `!makelist` et les variables de `!for` passaient par
  `format_wims_float` — 12 chiffres, tout entier en entier —, présentée comme
  l'impression de WIMS. `float2str` (`src/evalue.c`) écrit un entier en entier
  seulement entre -10⁶ et 10⁶, tout le reste en `%.<print_precision>g`, et
  `oef/var.proc` pose `print_precision=8` pour chaque OEF (aucun `.def` ne le
  change). Portée par `numfmt.wims_float2str` ; `format_wims_float` reste pour
  ce que PAX affiche lui-même. `kepler3a` affiche `6.0215118e+24`.
  Mesure : 419 exercices sur 9 770 changent, classés — arrondi à 8 chiffres,
  sa propagation (WIMS garde ses variables en chaînes : `clamed4` voit sa
  fréquence cumulée finir à `0.99999999`), et un nombre à 9 chiffres qui perd
  le dernier (`oefpower/decimal`, fidèle : `evalue` relit `3.6295063e+08` par
  `strtod`). Une régression, corrigée : `_expected_as_fraction` comparait la
  fraction au calcul à 10⁻⁹ près, et `quizz`, `oeflinsys`, `OEFpolynome`…
  perdaient leur attendu fractionnaire ; la tolérance suit `print_precision`.
- [ ] **Procédures de module jamais exécutées** : `_cmd_readproc` ignore tout
  fichier qu'il ne connaît pas. `!read my_var.proc` (depuis le `var.proc` de
  `oefvocmarine`, `OEFCalcLimLnExp`, `OEFexpalgTS`… 151 rendus),
  `methods.$lang` (`oefohm`, où `$lang` n'est même pas substitué alors que
  `methods.fr` existe), `notation_lang.proc` (10).
- [ ] **Types de réponse définis par les modules** (dossier `anstype/`) :
  `equation2`, `mynumexp`, `geogebra111`, `geogebra2`, `jmolstr`. Absents de
  `_WIMS_KNOWN_TYPES` comme de `_MODULE_ANSTYPES`, ils sont ramenés à
  `default` sans que le garde-fou de I.3 c les voie.
- [x] **16 exercices plantaient sur `re.PatternError: bad escape`** — corrigé
  le 2026-09-10 par un remplacement par fonction :
  `_eval_loop_expr` (sous `!makelist`) passe la valeur, qui contient du LaTeX
  (`\infty`, `\sqrt`…), comme *chaîne de remplacement* à `re.sub`. Un
  remplacement par fonction suffit. `oefgraphprob/matrice` et `stable` lèvent
  à part `could not convert string to float: '\poids1'`.
- [ ] **Rendus au-delà du budget de 8 s** (`backend/scripts/sonde_budget.py`,
  poste au repos) : `OEFevalwimssecdeg/coefracine2` et `coefracine3` (28 s,
  tronqués partout), `oefSpectroscopie/Infra-rouge5` (9 s). Passé le budget, le
  moteur poursuit avec l'état partiel sans rien signaler : **le rendu dépend de
  la vitesse de la machine**. `Infra-rouge5` rendait son widget en CI et pas
  sur un poste, si bien que son snapshot a fait tomber la CI ; il a été retiré.
  `Infra-rouge1` et `3` tiennent en 6,2 s, à la merci d'un runner plus lent.
  Relever le budget est une décision de produit : un élève attendrait autant.
- [ ] **Comprendre pourquoi ces cinq exercices sont si lents — c'est anormal.**
  Sur 9 698 exercices, 9 693 rendent en moins de 4 s ; `coefracine2|3`
  (28 s), `Infra-rouge5` (9 s), `Infra-rouge1|3` (6,2 s) sont hors de toute
  proportion. Chercher le motif qui coûte (boucle, lecture de données, appel
  CAS répété) avant de toucher au budget : c'est plus probablement un défaut
  du moteur qu'une exigence des exercices.

## 4. Notation des exercices à étapes — vérifier contre WIMS

- [x] **Le crédit d'une étape est proportionnel** (2026-09-06). Une étape dont
  deux champs sur trois sont justes ne vaut plus zéro. `oefdevfact/deve7`
  notait 33 % (une étape sur trois) là où WIMS en donne six sur dix ; il donne
  maintenant **56 %**, soit (1 + 2/3 + 0)/3 — l'étape non atteinte comptant
  pour zéro.

  **Le modèle est confirmé, sur deux mesures WIMS indépendantes.** Un second
  essai — une seule réponse juste sur trois à la deuxième étape — donne 4/10
  chez WIMS, là où la formule prédit (1 + 1/3 + 0)/3 = 44,4 %. Un modèle qui
  compterait les *réponses* aurait donné 5 justes sur 8, soit 62,5 %, affiché
  « 6 » : les deux modèles étaient indiscernables sur le premier cas, celui-ci
  les sépare.

  | copie | PAX | WIMS |
  |---|---|---|
  | 2 réponses justes sur 3 à l'étape 2 | 56 % | 6/10 |
  | 1 réponse juste sur 3 à l'étape 2 | 44 % | 4/10 |

  Les deux mesures fixent aussi l'arrondi : 5,56 → « 6 » et 4,44 → « 4 » ne
  s'accordent qu'avec un arrondi au plus proche. Une troncature aurait donné
  « 5 » dans le premier cas.

- [ ] **Vérifier la notation sur les autres formes.** `deve7` est un `course`
  à trois étapes. Restent à éprouver contre WIMS : un `course` long
  (`quizz/course04_1step`, 15 étapes), un `dynsteps` dont le nombre d'étapes
  n'est pas connu d'avance (`histocap`), et le cas d'un exercice interrompu par
  une erreur dès la première étape.

## 5. `\choice` — les menus déroulants d'OEF

- [x] **Rendus et notés** (2026-09-06). `\choice{titre}{bonne}{mauvaises}` est
  une construction distincte de `\answer` : elle produit un menu déroulant, et
  346 exercices en posent au moins un. `\embed{c1}` rendait un champ de saisie
  libre où l'élève devait deviner la phrase attendue au lieu de la choisir.

  La palette suit `oef/var.prep` : mauvaises réponses purgées de celles qui
  figurent aussi parmi les bonnes, puis **tri** — mélange seulement si l'auteur
  écrit `shuffle`. Le type suit `oef/formc.phtml` : boutons radio quand
  l'exercice n'a qu'un choix et aucune réponse, menu déroulant sinon.

- [x] **Le niveau de sévérité de WIMS est repris** (2026-09-06). L'enseignant
  qui pose un exercice sur une feuille WIMS choisit un `qcmlevel` de 1 à 9, et
  ce curseur commande dix réglages (`oef/exo.init`). Deux touchent les
  palettes :

      qcmpresent = !item $qcmlevel of 3,3,4,5,5,6,7,8,8   ← options montrées
      qcmgood    = !item $qcmlevel of 1,1,1,1,0,0,0,0,0   ← bonne réponse garantie ?

  PAX prend le défaut de WIMS — niveau 1, donc trois propositions — et un
  `.def` qui pose ses propres valeurs les garde. **142 palettes** du corpus
  sont réduites, et zéro bonne réponse n'est perdue : c'est le rôle de
  `qcmgood`, qui place la bonne réponse en tête *avant* la troncature.
  Au-dessus du niveau 4 elle peut manquer, et « Aucune de ces réponses »
  apparaît alors — l'échappatoire est implémentée mais aucun exercice du
  corpus ne l'atteint au niveau 1.

- [x] **Les dix réglages du niveau sont posés** (2026-09-06). `severite()` rend
  le vecteur complet, `qcmlevel` faisant foi et chaque réglage restant
  écrasable isolément — comme les `!default` d'`exo.init`. Sept sont consommés
  par le moteur d'exercice :

  | réglage | effet | où |
  |---|---|---|
  | `qcmpresent` | taille de la palette | `_prepare_choices` |
  | `qcmgood` | bonne réponse garantie | idem |
  | `precweight` | crédit d'une réponse juste à la précision près | `check_numeric` |
  | `givesol` | le corrigé est-il rendu | route de correction |
  | `givefeed` | le commentaire est-il rendu | idem |
  | `givegood` | l'attendu est-il révélé | idem |
  | `givehint` | l'indication est-elle servie | route de rendu |

  `precweight` remplace un 0,5 figé qui ne venait de nulle part : au niveau 1
  une réponse juste à la précision près vaut **0,9**. À vérifier contre WIMS,
  comme la notation par étapes l'a été.

- [x] **`freepower` est l'exposant de la note** — corrigé le 2026-09-06, après
  avoir écrit l'inverse le matin même. La recherche par `grep` ne trouvait
  aucun lecteur de `freepower` dans `scripts/oef/` et j'en avais conclu qu'il
  ne servait pas ; le consommateur est dans le moteur C, invisible à cette
  recherche. **Deux mesures sur WIMS l'ont établi** — cf. `check_numeric`.

- [x] **Le niveau 3 est le défaut de PAX** (2026-09-06). Trois mesures sur le
  WIMS de référence l'établissent, et la troisième — une réponse juste et une
  fausse — a confirmé la prédiction du modèle avant d'être faite :

  | copie | prédit | WIMS |
  |---|---|---|
  | deux approchées | 0,7² = 4,9 | 4,9/10 |
  | une juste, une approchée | 0,85² = 7,2 | 7,2/10 |
  | une juste, une fausse | 0,5² = 2,5 | 2,5/10 |

  `oef/default` donne 1, mais c'est le défaut du *menu* de création d'une
  feuille, non celui des feuilles réelles. Effet sur le corpus : 142 palettes
  reprennent une proposition (3 → 4), et les notes partielles sont rabattues
  par l'exposant.

## 6. Réglages du niveau de sévérité — les exposer

- [ ] **Reprendre le dispositif de WIMS, dans sa forme.** Les dix réglages y
  sont accessibles de deux façons, et les deux méritent d'exister ici :

  - un **curseur unique**, `qcmlevel` de 1 à 9, qui les déduit tous
    (`oef/exo.init`, branche non experte). C'est ce que l'enseignant règle en
    posant l'exercice sur une feuille, et c'est ce qu'il faut d'abord ;
  - un **mode expert** (`intro_expert=yes`) où chacun se pose isolément —
    `intro_qcmpresent` borné entre 2 et 8, `intro_sol`, `intro_feed`,
    `intro_sepow`, `intro_expow`, `intro_precw`, et les cases `introcheck` pour
    `qcmgood` et `penalty`.

  Le moteur est prêt : `DefEngine.severite()` lit `qcmlevel` puis laisse chaque
  réglage être écrasé isolément, exactement comme les `!default` d'`exo.init`.
  Il ne manque que le porteur — la feuille — et l'écran qui va avec. Même
  chantier que la surcharge des `confparm` (cf. I.2) : les deux réglages vivent
  au même endroit chez WIMS et devraient y vivre ici.

  WIMS montre par ailleurs à l'enseignant un tableau des neuf niveaux
  (`oef/helpseverity`) : neuf colonnes, dix lignes. Il vaut d'être repris, car
  un curseur de 1 à 9 sans ce tableau ne dit rien de ce qu'il commande.

  **Curseur et tableau faits le 2026-09-10** (page de la feuille,
  `SheetsSeverityTable`, table servie par `/api/sheets/severite` depuis
  `_SEVERITE` pour qu'elle n'existe qu'à un endroit). Reste le mode expert,
  ci-dessous.

- [x] **`penalty` et `scorepower` ont un consommateur : `oef/var.proc`**, le
  script qui calcule la note, et non `answer.phtml`. Ligne 431 : chaque menu
  `\choice` faux (et différent de « je ne sais pas ») retire `cc/(n-cc)`
  quand `$penalty>0` ; ligne 469 : `freegot = condgot+freegot+gotadjust+
  precweight*precgood` ; ligne 476 : `allgot = (allgot/alltot)^freepower*
  alltot` ; ligne 485 : `score = min(10, rint(100*(score_got/score_should)
  ^scorepower)/10)` — mais `exo.init` :67 ne pose `scorepower` qu'au-delà
  d'un exercice par travail (`$qnum>1`), sinon 1. PAX applique les trois
  premiers dans `api/routes/check.py` (pénalité restreinte aux champs `c<n>`
  des `\choice`) ; `scorepower` attend les feuilles, où un travail pourra
  grouper plusieurs questions. La leçon de
  `freepower` tenait : le consommateur n'était pas là où on le cherchait.

- [x] **Exposer `qcmlevel` sur la feuille d'exercice** (2026-09-10). Colonne
  `sheet_exercises.qcmlevel` (NULL = niveau 3, `_NIVEAU_DEFAUT`), réglée par
  exercice posé depuis la page de la feuille. Rendu et correction la lisent
  par `?sheet_item=` via `api/reglages.py`. `?qcmlevel=` permet l'essai
  ponctuel, **réservé aux enseignants** : un élève (403) baisserait sinon la
  sévérité d'une feuille notée en retouchant l'adresse. Même porteur que les
  `confparm` (I.2).

- [ ] **Le parcours élève des feuilles** (cf. II.1). Le réglage ne sert encore
  qu'à l'aperçu enseignant : aucune classe ne voit de feuille, et seul le
  bouton *Essayer* envoie un `sheet_item`. Deux points à tenir ce jour-là :
  `attempts.sheet_id` et `grades.sheet_id` n'ont **pas de cascade**, si bien
  qu'une feuille ayant des tentatives d'élèves ne pourra pas être supprimée ;
  et la tentative d'un enseignant n'est volontairement pas rattachée à la
  feuille (`check.py`). `scorepower` et les seuils `seedcnt` attendent aussi
  ce parcours (`qnum`).

- [ ] **Mode expert** (`intro_expert=yes`) : chaque réglage posé isolément.
  Le moteur l'accepte déjà — `severite()` laisse chaque clé écraser le
  niveau — ; il manque les colonnes et l'écran.

- [ ] **Une limite assumée.** `choicegood` est une liste chez WIMS ; PAX garde
  la bonne réponse **entière**, parce que plusieurs exercices y écrivent une
  seule option qui contient une virgule (`oefanglais/Verbesirrgulie4`,
  `oefstatproba/bergamo1`). Un choix à plusieurs bonnes réponses serait donc
  mal traité — aucun n'a été rencontré.

# II. Fonctionnalités PAX

## 1. Feuilles ?

- [x] Côté enseignant : créer une feuille, y poser des exercices, les régler
  (`qcmlevel`, `confparm`, cf. I.2 et I.6) et les essayer. Supprimer une
  feuille non vide répondait **500** — l'ORM détachait ses exercices au lieu
  de laisser la cascade SQL les emporter (`passive_deletes`, 2026-09-10).
- [ ] Côté élève : rien. Relier feuilles et classes ; une vue élève de la
  feuille (statut, ouverture et fermeture, prérequis) ; transmettre
  `sheet_item` au rendu et à la correction pour noter.

## 2. Statistiques d'utilisation du site

## 3. Clavier virtuel mathématique

Barre en bas d'écran, masquable, compacte (touches de base + extension), mobile et desktop.
Contrainte : les réponses sont des `<input>` texte brut (syntaxe WIMS, virgule décimale) — un clavier produisant du LaTeX ne se branche pas directement.

Options :
- [ ] **Composant maison** (recommandé) — mini-clavier Vue (~150 lignes) insérant des tokens au caret de l'input focalisé ; zéro dépendance, KaTeX déjà là pour les étiquettes
- [ ] **simple-keyboard** (hodgef) — léger, layout custom, insère dans les inputs existants ; mais layout math à construire soi-même, dépendance peu justifiée pour ~20 touches
- [ ] **MathLive** — clavier intégré excellent (layouts compact/minimalist, politique manual) mais couplé aux `<math-field>` (valeur LaTeX) → conversion LaTeX→WIMS à écrire, bundle lourd ; à considérer seulement si on veut la saisie WYSIWYG 2D
- [ ] **MathQuill** — écarté : jQuery, maintenance sporadique, pas de clavier intégré

# III. Mentions légales

## 1. Créer des CGU

## 2. Page sur les licences

## 3. Manifeste et remerciements à WIMS

# IV. Sécurité

## 1. Retirer la possibilité de créer des user admin et super-admin depuis l'API

## 2. Supprimer les scripts de création d'utilisateurs + reset mdp ?


# V. Décisions en attente

Quatre questions posées puis laissées en suspens. Elles n'ont longtemps vécu
que dans les `prompt-reprise-*.txt`, que git ne suit pas : chacune a été
formulée nettement, aucune n'a été tranchée, et deux ont été redécouvertes
d'un autre angle faute d'avoir un domicile. Elles sont ici pour qu'une session
qui les croise sache qu'elles attendent **une décision**, pas un diagnostic.

## 1. L'ampleur du port de l'intitulé et du libellé de champ

*Posée le 2026-09-03 (commits 39f4da8b, 6382caa8). Code en place, jamais
retranché.*

PAX ne portait pas les `anstype/<type>.input`, qui décident de la présentation
du champ. Trois manques comblés d'un coup : l'intitulé (`$name_enterreply`,
« Entrez votre réponse : », posé par `oef/form.phtml` s'il reste une réponse non
embarquée), le libellé (**tous** les `.input` l'écrivent ; PAX ne le montrait
que s'il y avait plusieurs champs), et les accolades (`set`/`aset` les posent
comme `fset`). Le `=` après le libellé dépend du type, **relevé** sur l'arbre
WIMS et non deviné (`_EGAL_APRES_LABEL`, 17 types).

Le point à trancher est l'**ampleur** : le repli sert beaucoup plus large qu'il
n'y paraît, car beaucoup d'auteurs n'embarquent aucun champ. **401 exercices**
gagnent l'intitulé, **421 champs** un libellé, **402 instantanés** ont été
régénérés. Vérifié avant livraison : aucun libellé ne fait doublon avec un
intitulé déjà présent dans l'énoncé, aucune réponse ne disparaît, aucun test de
notation ne bouge.

À décider : garder tel quel (position actuelle, et la plus fidèle à WIMS), ou
restreindre — par exemple l'intitulé seulement à partir de deux champs. Le
revert est immédiat tant qu'on ne l'a pas empilé.

## 2. Le filtre sur l'`expected` vide dans `_check_all`

*Posée le 2026-09-03, redécouverte par un autre angle le 2026-09-18. Toujours
en place :* `tests/test_exercises_check.py:208`.

`_check_all` ignore tout champ dont l'`expected` est vide. Un champ `analyze`
non éprouvé n'est donc testé ni en bonne ni en mauvaise réponse : la suite lente
était verte sur les cinq `OEFevalwimsgrph/eqalghyper*`, qui étaient
**insolubles** (cf. I.3 d). Le filtre est la raison pour laquelle personne ne
l'a vu.

Le 2026-09-18 a buté sur la même limite depuis l'autre bout : **820 exercices
`analyze` sans référence** qu'« aucun test ne peut éprouver, faute de savoir
quoi soumettre ». C'est le même filtre, nommé deux fois à quinze jours
d'intervalle sans que le lien soit fait.

À décider : lever le filtre ou le garder. Le lever ferait entrer 100+ exercices
dont on ne sait pas encore ce qu'ils valent — c'est le coût, et c'est
précisément ce qu'on ignore aujourd'hui. Mesure préalable : rejouer la suite
lente filtre levé, et classer les nouveaux échecs par famille avant de décider
quoi que ce soit.

## 3. Le lien « ← Retour aux exercices »

*Ajouté de ma propre initiative le 2026-09-07 (`frontend/pages/exercise/[id].vue:10`).*

La page d'un exercice ouverte en direct n'offrait aucun retour vers la liste :
la barre du layout `default` ne mène qu'à l'accueil et au compte. La clé i18n
`exercise.back` existait pourtant, orpheline, dans les trois locales — d'où
l'ajout. Ce n'était pas demandé.

À décider : valider ou retirer.

## 4. Les deux layouts de la page d'exercice

*Relevée le 2026-09-07, non touchée — c'est un choix produit.*

`/exercise` utilise le layout `dashboard`, `/exercise/[id]` le layout `default`.
L'utilisateur voit donc deux barres différentes selon qu'il prévisualise un
exercice ou qu'il l'ouvre, et le compteur d'étoiles ne vit que sur la première.

À décider : unifier, ou assumer les deux barres.
