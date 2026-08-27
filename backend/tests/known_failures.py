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
XFAIL_RENDER_STRUCTURE = {
    # Rien à rendre, et ce n'est pas le moteur : le `.def` de `medicament` ne
    # comporte **aucune** section — pas de `:question`, donc pas d'énoncé. Il
    # est identique, octet pour octet, à celui de `wims/public_html/modules/`,
    # si bien que WIMS n'en tire pas davantage. C'est le filtre qu'applique
    # déjà `corpus_state.py`, et un travail sur le corpus, pas sur le code.
    'H4~stat~oefstatistiques.fr~src~medicament',
}

# test_correct_answer_scores_1 : la bonne réponse ne donne pas 1
#
# Les deux `range` ci-dessous s'y sont ajoutés le 2026-08-05, en implémentant
# `anstype/range`. Ils ne passaient qu'en apparence : le type retombait sur une
# comparaison de texte, et le test leur soumettait leur propre `expected`, si
# bien qu'une chaîne se comparait à elle-même. Leur attendu est cassé **en
# amont** — `moho1` porte un `NaN`, `ConnexionInt2` un `rint(…print(Mat(…`
# jamais évalué (la famille des sept attendus non évalués). Aucune borne
# numérique n'en sort, donc aucune réponse ne peut tomber dedans.
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
# Restent les `bound`, qui testent l'appartenance à une région d'un GIF par
# remplissage : sans l'image, rien à calculer.
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
# Les deux `equation` suivants s'y sont ajoutés le 2026-08-25, pour la même
# raison et en implémentant `anstype/equation`. Leur attendu est cassé en
# amont, sans qu'aucun checker puisse y remédier : `ConnexionInt4` reprend le
# `rint(/*100)` — division inachevée — de son frère `ConnexionInt2`, déjà listé
# ci-dessous. Une expression trouée n'est l'équation de rien : elle ne se
# comparait à elle-même que faute de checker.
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
XFAIL_CORRECT_SCORE = {
    'H4~stat~oefseriestat2var.fr~src~ConnexionInt2',
    'H4~stat~oefseriestat2var.fr~src~ConnexionInt4',
    'H3~analysis~OEFevalwimspuis.fr~src~produit5',
    'H3~geography~oefdepregfr.fr~src~clickcap',
    'H3~geography~oefdepregfr.fr~src~clickcode',
    'H3~geography~oefdepregfr.fr~src~clickdept',
    'H3~geography~oefdepregfr.fr~src~clickrcap',
    'H3~geography~oefdepregfr.fr~src~clickreg',
    'H3~geometry~oefpolygon.fr~src~quadrilatere',
    'H3~math~quizz.fr~src~T1110',
    'H4~algebra~h4droites.fr~src~ordoneeOrign',
    'H4~chemistry~chemavance1.fr~src~Tableaudavance',
    'H4~chemistry~chemavance1.fr~src~TableaudavanceBis',
    'H4~chemistry~mole.fr~src~masse_molaire1',
    'H4~chemistry~mole.fr~src~masse_molaire_avec_solution',
    'H4~chemistry~mole.fr~src~nb_moles_avec_solution',
    'H4~chemistry~moles.fr~src~masse1',
    'H4~chemistry~moles.nl~src~masse1',
    'H4~physics~temps.fr~src~periodefrequence',
    'H4~stat~descriptives.fr~src~pdfctstat',
    'H4~stat~oefseriestat2var.fr~src~ConnexionInt1',
    'H4~stat~oefseriestat2var.fr~src~ConnexionInt5',
}

# test_wrong_answer_scores_less_than_1 : une réponse fausse est acceptée
XFAIL_WRONG_SCORE: set[str] = set()
# Vide : les trois exercices qui y figuraient acceptaient une réponse « fausse »
# de 999 supérieure à la bonne — sous la tolérance relative de `\precision`, donc
# à bon droit. C'est le générateur du test qui a été corrigé, pas le moteur.
