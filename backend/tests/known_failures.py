"""
Exercices dont le test échoue pour des raisons préexistantes. Ils sont marqués
xfail pour qu'une vraie régression reste visible.

Ces listes sont **courtes à dessein**. Une première reconstruction en comptait
561 ; l'examen a montré que l'écrasante majorité venait des tests eux-mêmes —
`sqrt(` cherché dans tout le HTML alors qu'il n'est un défaut que dans une
formule (233 énoncés corrects signalés pour 5 vrais), et réponses attendues
soumises en bloc là où WIMS y range plusieurs écritures acceptables. Les tests
corrigés, il reste ce qui suit : des bugs à traiter, pas du bruit à tolérer.

Pour retirer un exercice : corriger le bug, puis relancer

    pytest tests/test_exercises_check.py tests/test_exercises_render.py -m slow

Les identifiants sont les slugs des routes. Les listes d'avant portaient les
entiers d'avant la migration `c1a2b3d4e5f6`, que plus rien ne désignait.
"""

# test_render_structure : anomalie dans le HTML rendu
#
# Quatorze sont partis le 2026-08-26, de seize entrées à deux, en trois
# familles.
#
# Sept tenaient à une expression que sympy ne lisait pas d'un bloc : elle
# repartait **telle quelle**, son `sqrt(` en clair. Trois portaient un « = » de
# premier niveau (`racequ2`, `corriger_fonctions`, `gauss_summe`), quatre une
# notation scolaire que sympy ne parse pas — l'encadrement
# `3.87 < sqrt(15) < 3.88` (`solveineq3`, `solveineq5`) et le couple de
# coordonnées à la française `( 5 ; 6*sqrt(2) )` (`longueur4`, `longueur5`).
#
# Cinq tenaient au closer de `_close_inline_math`, qui relit un HTML **déjà
# fermé par le moteur** et prenait pour sa fermeture un « ) » qui était du
# contenu : la parenthèse d'un trou à compléter (`deve7`, `deve8`,
# `calcprod3`, `signeprod2`, `signequot2`).
#
# Deux venaient du contrôle lui-même : `structural_issues` ne comptait que le
# texte, et jugeait vide l'énoncé posé par une image (`0703`) ou par le widget
# seul (`nompolygone`, qui fait apparier des noms de polygones à leurs
# figures). Il ne manquait rien à l'élève.
#
# Deux pièges à connaître avant de rouvrir cette liste :
#
# 1. `test_render_structure` appelle `pytest.xfail()` **impérativement**, ce
#    qui interrompt le test sur-le-champ. Un exercice réparé ne se signale
#    jamais par un XPASS — il faut le retirer d'ici et relancer, ou passer
#    `structural_issues` sur la liste.
# 2. `core.oef.engine.load_and_render` sert le **cache Redis** (`pax:render:*`).
#    Un contrôle mené sans l'avoir purgé mesure l'état d'avant la correction :
#    `signeprod2` a paru résister une fois le bug corrigé, pour cette seule
#    raison. `docker compose exec redis redis-cli FLUSHDB` avant toute mesure.
# Vide. `medicament` y figurait seul : son `.def` ne comporte **aucune**
# section — pas de `:question`, donc pas d'énoncé —, et son titre dit
# lui-même « (bug) ». Il rend pourtant quelque chose depuis que
# `oef/steps.proc` est exécuté : `oefsteps` normalisé, le repli « un champ par
# réponse déclarée » s'applique, et les six réponses qui portent un attendu
# (1.35, 1.56, 1.64, …) deviennent atteignables, étiquetées par leurs
# `replyname`. C'est le repli de WIMS lui-même, non une invention de PAX.
#
# Ce qui reste cassé est en amont et n'est pas du ressort du moteur : le `.def`
# annonce `replycnt=16` là où six réponses seulement se matérialisent, faute
# d'énoncé pour les porter.
XFAIL_RENDER_STRUCTURE: set[str] = set()

# test_correct_answer_scores_1 : la bonne réponse ne donne pas 1
#
# Les deux `range` ci-dessous s'y sont ajoutés le 2026-08-05, en implémentant
# `anstype/range`. Ils ne passaient qu'en apparence : le type retombait sur une
# comparaison de texte, et le test leur soumettait leur propre `expected`, si
# bien qu'une chaîne se comparait à elle-même. On les avait crus cassés **en
# amont**, `moho1` par son `NaN` et `ConnexionInt2` par un `rint(…print(Mat(…`
# jamais évalué : aucune borne numérique n'en sortait, donc aucune réponse ne
# pouvait tomber dedans. Ce diagnostic était faux dans les deux cas — le calcul
# n'avait simplement jamais eu lieu, faute d'un `divrem` réel pour l'un, d'une
# transposée de matrice sympy pour l'autre. Tous deux sont partis le
# 2026-08-28.
#
# Cinq sont partis le 2026-08-26 : sans `replytypeN`, PAX supposait `numeric`
# là où `replytype.proc` pose `default` — et `anstype/default` n'est pas un
# comparateur mais un aiguilleur, qui lit l'attendu avant de choisir. Une
# réponse algébrique non typée (`2*b`, `1-p`, `15*x/2 - 23/2`) était donc
# comparée numériquement, et notée fausse.
#
# Trois `analyze` d'`oefstatistiques` (`histocap`, `histogramme`, `moustache`)
# sont partis le 2026-08-27 sans qu'on ait rien corrigé au moteur : leur unique
# champ porte une réponse attendue **et** un poids nul — la note vient de la
# section `:test`. Le score global se divisait par un poids total nul et rendait
# 0. Le test les écarte désormais, comme il écartait déjà les exercices dont
# tous les attendus sont vides : exiger 1 de ce qui n'est pas noté n'a pas de
# sens.
#
# Sept `coord` sont partis le 2026-08-27, pour deux raisons qui se cumulaient.
# Les composantes d'une click-zone sont des **expressions** que `getvalue`
# (`Misc/clickzone.c`) passe au calculateur — `circle,110,80,30/3`,
# `circle,200,200-20*7,9` —, et n'en garder que les nombres purs laissait le
# cercle sans rayon. Et un `coord` n'attend pas une zone mais un **point** : le
# test lui soumettait la description de la cible au lieu d'un clic dedans.
#
# Les cinq derniers, les `bound` d'`oefdepregfr`, sont partis le 2026-08-30.
# Ils ne se calculent pas : `clickzone.c` remplit l'image par diffusion depuis
# le point cliqué et regarde si le point de référence de la zone a été atteint
# — deux points d'un même département de `dept.gif` communiquent, le tracé les
# sépare de leurs voisins. D'où un décodeur GIF (`def_engine/gif.py`, sans
# dépendance ajoutée) et la région 4-connexe qui va avec, confrontés au binaire
# `clickzone` du dépôt sur 136 clics — dont 120 tirés au hasard — sans un écart.
#
# Le même travail a montré que `check_coord` n'acceptait qu'**une** zone là où
# le moteur en joint plusieurs par `;`, et surtout que seule la **première**
# vaut bonne réponse : `anstype/coord` ne retient le rang rendu par `clickzone`
# que s'il vaut 1 (`!if $i_=1`), les suivantes servant à colorier la carte en
# diagnostic. Accepter n'importe laquelle aurait rendu ces exercices triviaux.
#
# `produit5` est parti le 2026-08-30, et le moteur n'y était pour rien : c'est
# le **test** qui soumettait la consigne au lieu de la réponse. Un `numexp`
# demande un nombre, jamais un calcul — `anstype/numexp` refuse `+ - * ^ (` —,
# et l'attendu stocké est pourtant une expression : `5*3` pour « 5³×3³, soit
# 15³ ». `_candidats` propose désormais aussi sa valeur, comme il propose déjà
# le milieu d'un `range`, l'arrondi d'un `sigunits` ou le clic d'un `coord`.
#
# Huit `sigunits` sont partis le 2026-08-27, et le checker n'y était pour rien :
# l'attendu se stocke `"<valeur> <unité> #N"`, où `#N` est la **consigne** —
# arrondir à N chiffres significatifs. Le test soumettait l'attendu tel quel,
# donc la valeur non arrondie, que `check_sigunits` refusait à bon droit. Le
# corrigé montré à l'élève souffrait du même mal (`74753832.77 km^2 #4` au lieu
# de `7.475e7 km^2`) : `sigunits_display_answer` sert désormais les deux.
#
# Les quatre `oefpyramid` sont partis le 2026-08-27 : ils fabriquent leurs
# nombres en concaténant des chiffres tirés au sort
# (`$[($(tmp0)$(tmp1)$(tmp2))/…]`), et un tirage de 0, 0, 2 donnait `$[(002)/1]`
# — que Python 3 refuse d'évaluer, zéros de tête interdits, là où le C les lit
# sans broncher. L'attendu restait la formule.
#
# Six sont partis le 2026-08-28, au bout d'une cascade de cinq corrections du
# moteur — interpréteur de slib rendu plat, corps liés de PARI, `!for … from`,
# `lg`/`ln` et `!while`, puis les `confparm` du module. Les quatre exercices
# `moles`/`mouvrel` reposent sur `slib/triplerelation/tabular`, qui arrondit
# aux chiffres significatifs par `rint(10^(prec-1-floor(lg(x)))*x)` : `lg`
# manquant, sa contrainte n'était jamais satisfaite et le slib rendait un
# message d'erreur à la place des valeurs.
#
# Trois factorisations sont parties le 2026-08-27. `slib/commutesom` pose son
# drapeau dès qu'on l'appelle, et PAX en marquait la réponse `expand` — donc
# « forme développée exigée ». Or `oeffac3b` s'en sert pour son énoncé mais
# attend `(2 y + 13)^2` : l'attendu se voyait refuser lui-même. Le marqueur ne
# vaut plus que si l'attendu est effectivement développé.
#
# Deux `equation` s'y étaient ajoutés le 2026-08-25, en implémentant
# `anstype/equation` : `ConnexionInt4` portait un `rint(/*100)` — division sans
# numérateur — et on l'avait dit cassé en amont, hors d'atteinte d'un checker.
# À tort, là encore. Ce trou était celui de `!column 1 to $val25 of`, forme que
# la commande ne savait pas lire : la plage lui rendait une chaîne vide, donc
# plus aucune donnée à moyenner. Parti le 2026-08-28.
#
# Les onze `programming` sont partis le 2026-08-27, en deux familles.
#
# Huit tenaient à la session PARI, qui ne portait ni les fonctions qu'un
# `!exec pari` y définit, ni le `default(format, …)` qu'il y pose — et cette
# dernière commande, faute d'être reconnue, faisait **abandonner le programme
# entier**, qui repartait alors en source brute. Les attendus gardaient donc le
# nom de la variable PARI (`llo`, `vv`, `mmli`) au lieu de sa valeur.
# `droitecar1` en faisait partie : son `mmli*x+*y+=0` n'était pas un attendu
# cassé par l'auteur, contrairement à ce qu'on avait conclu — juste un calcul
# jamais fait.
#
# Trois tenaient à la dérivée notée par une apostrophe (`f'(x_0)`, `euler1`,
# `euler2`, `tangente1`) : Python y lit le début d'une f-string, le parse
# échouait, et l'attendu se refusait lui-même. `_normalize_expr` en fait
# désormais un nom de fonction, comme WIMS qui n'a pas davantage d'opérateur
# apostrophe.
#
# Les trois Pythagore (`avion`, `moho0`, `moho1`) sont partis le même jour, et
# la même session PARI y était pour moitié : `pyth(A,B,lim)={…}` cherche un
# triplet par deux `for` imbriqués dont il sort par `return`, deux
# constructions que l'interpréteur ignorait — corps entre accolades et sortie
# anticipée. L'autre moitié tenait à `divrem` sur des réels, qui partait en
# division *polynomiale* : `moho0` y lit le reste pour convertir un temps de
# trajet en minutes et secondes, et n'obtenait que `NaN`. Trois autres
# exercices du même module (`bird`, `etagere1`, `etagere2`) y ont gagné leur
# énoncé, qui affichait jusque-là son propre code source.
#
# Deux derniers sont partis le 2026-08-27, chacun pour une raison isolée :
#
#   - `ordoneeOrign` appelle `ev($val26, x=0)`, la fonction Maxima qui évalue
#     une expression sous une substitution. Elle n'était reconnue qu'à trois
#     arguments, sur la signature de `subst(nouveau, ancien, expr)` — dont
#     l'ordre est pourtant l'inverse. La forme réelle repartait telle quelle,
#     et `ev(x^2+1)` se lisait même `e*v*(x^2+1)`, un produit par la constante
#     d'Euler.
#   - `T1110` demande « 30 % de 20 » et attend `6`, sous le `polfactor` que le
#     module pose pour toutes ses questions. Or une constante n'a pas de forme
#     factorisée *par opposition à* développée : elle est les deux. Le
#     pré-contrôle la disait développée — un nombre est un monôme — et la
#     refusait donc au titre de la factorisation exigée.
#
# Les quatre `ConnexionInt` sont partis le 2026-08-28, et leurs deux causes
# étaient l'une et l'autre en amont de tout checker :
#
#   - `slib/stat/sum` calcule sa somme pondérée par `Mat([data])*Mat([poids])~`.
#     La transposée postfixe se traduisait par l'opérateur `~` de Python, donc
#     par `__invert__` — que `PVec` et `PMat` définissent, mais **pas**
#     `sympy.Matrix`, ce que rendent justement les helpers de `cas`. Le slib
#     rendait alors son propre code source à qui l'appelait.
#   - `!column 1 to $val25 of` : la commande découpait ses indices aux virgules
#     *et aux espaces*, prenait donc le `to` d'une plage pour un indice, et
#     rendait une chaîne vide faute de savoir l'évaluer. Elle lit désormais
#     `_index_list`, la grammaire d'indices commune à `!item`/`!row`/`!line`.
#     C'est ce qui donne enfin à `ConnexionInt1` ses « 7 dernières semaines ».
#
# `moymanqte` et `C1` y ont gagné au passage, le premier son énoncé — il
# annonçait une moyenne égale à `print(rint(print(Mat([0,4,13,14])*…` et dit
# maintenant 303/28.
#
# `pdfctstat` était le cinquième `stat`, et rien n'était à corriger dans le
# moteur : ses attendus (`\eAD/\eA`) nommaient des effectifs que le `.oef` ne
# définissait jamais. Le préprocesseur les posait, mais sous une garde
# `#if defined defined TARGET_pdfctstat` — un `defined` de trop
# (`src/cpp/piecesdefct.cpp`, lignes 42, 86 et 172, seules occurrences du
# corpus). L'expression était fausse, les douze `\integer{eAD=…}` exclus de la
# génération, et le bloc suivant — dont la garde était correcte — les
# référençait quand même. Le mot en trop retiré, `.oef` et `.def` régénérés
# (cf. `docs/regenerer-un-oef.md`), l'exercice retrouve son tableau
# d'effectifs et ses trois fréquences. Parti le 2026-08-30.
#
# `periodefrequence` est parti le 2026-08-28 : son attendu ` s#2` avait perdu
# sa valeur, et n'en gardait que l'unité. `slib/text/sigunits` — que 70
# fichiers du corpus emploient — n'est qu'une enveloppe autour de
# `!exec units-filter`, le binaire de WIMS qui arrondit une quantité à N
# chiffres significatifs ; `!exec` ne connaissant que `maxima` et `pari`,
# l'appel rendait une chaîne vide. L'arrondi est désormais porté (`units_filter`
# dans `core/answer/checkers.py`) ; la **conversion** d'unité ne l'est pas, et
# un appel qui en réclame une rend toujours vide, plutôt qu'une valeur non
# convertie qui serait fausse sans le dire.
#
# Les deux `masse1` sont partis le 2026-08-30, avec `!exec chemeq` : le
# calculateur de chimie de WIMS, dont `slib/chemistry/chemeq_mass` tire les
# masses molaires et `chemeq_tex` le rendu LaTeX des équations. `_cmd_exec` ne
# connaissait que `maxima` et `pari`, si bien que l'attendu se réduisait à son
# unité (` g/mol`) et que les énoncés d'`equilibrium` annonçaient « Voici une
# équation de réaction chimique : \(\) ». Il est désormais émulé
# (`core/oef/def_engine/chemeq.py`), à l'image de Maxima et de PARI — le
# binaire du dépôt (`wims/other/bin/chemeq`) sert d'oracle, et
# `tests/test_chemeq.py` rejoue la comparaison sur les 65 entrées que le corpus
# lui soumet.
#
# Les trois `mole.fr` sont partis le 2026-08-30, et leur cause n'avait rien de
# chimique : `slib/chemistry/molecule` sépare le nombre d'atomes du symbole par
# deux `!replace` à **expression régulière** — `[0-9]` d'un côté, `[a-zA-Z]` de
# l'autre. Sans le préfixe `internal`, et dès qu'un motif porte un caractère de
# `\[^.*$`, WIMS ne remplace pas du texte : il lance sed (`calc.c`). PAX prenait
# `[0-9]` pour un littéral, ne trouvait rien, et le slib rendait un nombre
# d'atomes égal au symbole — d'où le `0+U*238.03+F4*` de la masse molaire.
# `by $` s'y lit « par rien » : un dollar seul nomme la variable de nom vide,
# que `substit` résout comme une autre.
#
# Les deux `chemavance1` sont partis le 2026-08-30, avec l'équilibrage
# (`chemeq -e` et `-C`, désormais portés) et deux corrections du moteur :
#
#   - `!randfile` et `!randrecord` sont **la même fonction** dans la table de
#     `calc.c` — les deux noms y pointent sur `calc_randfile` —, mais seul le
#     second était routé. Le `!randfile $val2.dat` de `chemavance1` rendait
#     donc le vide : son équation de réaction n'était jamais tirée.
#   - `!reset a, b, c` ne vidait que le dernier nom. `exec_reset` ouvre sur
#     `items2words` : la virgule sépare autant que l'espace. Or
#     `slib/chemistry/chemeq_equilibrium` ouvre sur un `!reset` de trente noms,
#     dont `slib_phrase` où il construit sa réponse — d'un appel au suivant,
#     la précédente y restait et les deux tableaux se concaténaient. La forme
#     `nom[N]`, qui vide la série `nom1`…`nomN`, manquait aussi.
#
# `Tableaudavance` passe d'un unique champ vide à cinq colonnes d'avancement
# vérifiables : pour Fe + 2H⁺ → Fe²⁺ + H₂ partant de 0.392 et 0.361 mol,
# l'avancement maximal vaut 0.361/2 = 0.1805, H⁺ limitant.
#
# `coefficients` et `coefficients2` **entrent** en échange dans les tests : ils
# en étaient écartés faute d'attendus, et leur tableau se construit désormais
# pour de bon — 11 champs pour NaCl → Na⁺ + Cl⁻ au lieu de 29 cases vides.
# Huit de leurs onze attendus étaient justes, trois gardaient un `*1/1`. Deux
# fausses pistes ont été mesurées puis annulées — le slib, dont les lignes
# `Charge_total` et `<élément>_total` se calculent bien, et `_rational_expand`,
# sans effet ici. La cause était en amont de tout cela : `!for v = a to b
# **step** s`. Rien ne lisait le mot `step`, la borne haute valait
# `$val16 step 2`, son évaluation échouait, et la boucle ne tournait pas —
# `val26` n'y recevait qu'une ligne sur trois. Réglé le 2026-08-30 ; 92
# fichiers du corpus emploient cette forme.
#
# Au passage, `corpus_state` a signalé « segments perdus » sur ces deux
# exercices — `input 29→0`. C'est un **faux positif** : leurs champs passent
# dans un `<table>`, où `_segment_statement` les réécrit en `<input>` natifs
# inline au lieu d'en faire des segments propres (c'est documenté dans sa
# docstring). Vérification faite, les onze champs restent atteignables et
# appariés à leurs `answers`.
# Vide. `oefpolygon/quadrilatere`, qui y figurait seul, est réparé : la voie
# retenue est celle de la géométrie, la seconde des deux que cette note
# envisageait. Trois manques se cachaient derrière, et le premier masquait les
# autres — le `plot` **paramétrique** n'était pas tracé, si bien que la figure
# des frontières ne portait que son cadre ; `$ins_filename` n'était pas posée,
# si bien que la zone arrivait sans figure à désigner ; et `oneline` n'était
# pas porté, si bien que le `|` de plusieurs régions acceptables n'était pas lu.
# Le remplissage bitmap de WIMS se reformule alors exactement : deux points
# sont dans la même région si le segment qui les joint ne croise aucune
# frontière tracée (cf. `_meme_region_svg`).
XFAIL_CORRECT_SCORE: set[str] = set()

# test_wrong_answer_scores_less_than_1 : une réponse fausse est acceptée
XFAIL_WRONG_SCORE: set[str] = set()
# Vide : les trois exercices qui y figuraient acceptaient une réponse « fausse »
# de 999 supérieure à la bonne — sous la tolérance relative de `\precision`, donc
# à bon droit. C'est le générateur du test qui a été corrigé, pas le moteur.
