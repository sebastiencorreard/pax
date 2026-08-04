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
XFAIL_RENDER_STRUCTURE = {
    'H3~algebra~oefdevfact.fr~src~deve7',
    'H3~algebra~oefdevfact.fr~src~deve8',
    'H3~geometry~oefpolygon.fr~src~nompolygone',
    'H3~number~OEFevalwimsnbrel.fr~src~calcprod3',
    'H3~number~OEFevalwimsnbrel.fr~src~signeprod2',
    'H3~number~OEFevalwimsnbrel.fr~src~signequot2',
    'H4~algebra~oeffctref.fr~src~racequ2',
    'H4~analysis~OEFevalwimsordre.fr~src~solveineq3',
    'H4~analysis~OEFevalwimsordre.fr~src~solveineq5',
    'H4~geometry~OEFevalwimscoord.fr~src~longueur4',
    'H4~geometry~OEFevalwimscoord.fr~src~longueur5',
    'H4~language~mathelexikon1.fr~src~corriger_fonctions',
    'H4~language~mathelexikon1.fr~src~gauss_summe',
    'H4~physics~oefpression.fr~src~0703',
    'H4~programming~oefechpython.fr~src~franccarreau1',
    'H4~stat~oefstatistiques.fr~src~medicament',
}

# test_correct_answer_scores_1 : la bonne réponse ne donne pas 1
XFAIL_CORRECT_SCORE = {
    'H3~algebra~OEFlittcollege.fr~src~oeffac3b',
    'H3~algebra~OEFlittcollege.fr~src~oeffac4b',
    'H3~algebra~OEFlittcollege.fr~src~oeffactir3',
    'H3~algebra~oefdevfact.ca~src~distrired',
    'H3~algebra~oefdevfact.nl~src~deve6',
    'H3~algebra~oefvitesse.fr~src~astron2',
    'H3~algebra~oefvitesse.fr~src~astron3',
    'H3~analysis~OEFevalwimspuis.fr~src~produit5',
    'H3~analysis~oefaffif.ca~src~fnctaff1',
    'H3~analysis~oefaffif.ca~src~fnctaff3',
    'H3~coding~oefbin.nl~src~calcbase',
    'H3~geography~oefdepregfr.fr~src~clickcap',
    'H3~geography~oefdepregfr.fr~src~clickcode',
    'H3~geography~oefdepregfr.fr~src~clickdept',
    'H3~geography~oefdepregfr.fr~src~clickrcap',
    'H3~geography~oefdepregfr.fr~src~clickreg',
    'H3~geometry~oefcoord.fr~src~somvect',
    'H3~geometry~oefcoord.fr~src~vectgraph',
    'H3~geometry~oefpolygon.fr~src~quadrilatere',
    'H3~geometry~oefpytha.fr~src~avion',
    'H3~geometry~oefpytha.fr~src~moho0',
    'H3~math~quizz.fr~src~T1110',
    'H3~number~OEFnbredeccollege.fr~src~oefpyramid1',
    'H3~number~OEFnbredeccollege.fr~src~oefpyramid2',
    'H3~number~OEFnbredeccollege.fr~src~oefpyramid3',
    'H3~number~OEFnbredeccollege.fr~src~oefpyramid4',
    'H4~algebra~h4droites.fr~src~ordoneeOrign',
    'H4~chemistry~chemavance1.fr~src~Tableaudavance',
    'H4~chemistry~chemavance1.fr~src~TableaudavanceBis',
    'H4~chemistry~mole.fr~src~masse_molaire1',
    'H4~chemistry~mole.fr~src~masse_molaire_avec_solution',
    'H4~chemistry~mole.fr~src~nb_moles_avec_solution',
    'H4~chemistry~moles.fr~src~concentration1',
    'H4~chemistry~moles.fr~src~masse1',
    'H4~chemistry~moles.fr~src~massevolumique',
    'H4~chemistry~moles.nl~src~concentration1',
    'H4~chemistry~moles.nl~src~masse1',
    'H4~chemistry~moles.nl~src~massevolumique',
    'H4~geometry~OEFevalwimsvect1.fr~src~reperpt3',
    'H4~geometry~OEFevalwimsvect1.fr~src~reperpt4',
    'H4~geometry~OEFevalwimsvect1.fr~src~reperpt5',
    'H4~geometry~droiteplanrep.fr~src~tracredstep',
    'H4~math~quizzautomat.fr~src~fct4',
    'H4~physics~mouvrel.fr~src~vitesse0',
    'H4~physics~oefpression.fr~src~0704',
    'H4~physics~oefpression.fr~src~0705',
    'H4~physics~oefpression.fr~src~0706',
    'H4~physics~oefpression.fr~src~0707',
    'H4~physics~oefpression.fr~src~0708',
    'H4~physics~oefpression.fr~src~0710',
    'H4~physics~temps.fr~src~periodefrequence',
    'H4~probability~oefpenney.it~src~pairs4',
    'H4~programming~oefalgopython.fr~src~balayage3',
    'H4~programming~oefalgopython.fr~src~balayage4',
    'H4~programming~oefalgopython.fr~src~balayage5',
    'H4~programming~oefalgopython.fr~src~balayage6',
    'H4~programming~oefalgopython.fr~src~dichotomie1',
    'H4~programming~oefalgopython.fr~src~euler1',
    'H4~programming~oefalgopython.fr~src~euler2',
    'H4~programming~oefalgopython.fr~src~heron1',
    'H4~programming~oefalgopython.fr~src~heron2',
    'H4~programming~oefalgopython.fr~src~tangente1',
    'H4~stat~descriptives.fr~src~pdfctstat',
    'H4~stat~oefseriestat2var.fr~src~ConnexionInt1',
    'H4~stat~oefseriestat2var.fr~src~ConnexionInt5',
    'H4~stat~oefstatistiques.fr~src~histocap',
    'H4~stat~oefstatistiques.fr~src~histogramme',
    'H4~stat~oefstatistiques.fr~src~moustache',
}

# test_wrong_answer_scores_less_than_1 : une réponse fausse est acceptée
XFAIL_WRONG_SCORE = {
    'H3~math~quizz.fr~src~0619',
    'H4~algebra~contribution.fr~src~lebrun4',
    'H4~geometry~evalwimssections.fr~src~airecoeff5',
}
