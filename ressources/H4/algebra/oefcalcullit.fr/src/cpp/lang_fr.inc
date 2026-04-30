#if defined TARGET_factdir1
\text{tintro=Factoriser l'expression}
\text{name_expr=Expression factorisée&nbsp;}
\text{name_solution=Le facteur commun est, Une factorisation possible attendue est }
#endif
#if defined TARGET_factorisat1 || defined TARGET_factorisat2
\text{name_answer=Choix,Facteur,Factorisation}
\text{name_hence=Donc}
\text{tintro=Nous voulons factoriser l'expression&nbsp;}
\text{name_tetape1=Première étape&nbsp;, Choix du facteur commun}
\text{name_regroup=Regroupement}
\text{name_reduction=En réduisant et en ordonnant le second facteur, on obtient}
\text{name_tetape2=Deuxième étape&nbsp;, Isolement du facteur commun dans chaque terme.}
\text{name_tetape=Dans le terme, le facteur commun, est multiplié par}
#endif
#if defined TARGET_dev1exp || defined TARGET_dev2exp || defined TARGET_dev2fact1 || defined TARGET_dev2fact2
\text{name_enonce=Développer l'expression suivante.}
# if defined TARGET_dev1exp
\text{name_answer=Forme développée}
# endif
# if defined TARGET_dev2exp
\text{name_instruction=La dernière expression sera réduite.}
# endif
# if (defined TARGET_dev2fact1 || defined TARGET_dev2fact2 )
\text{name_instruction=Choisir la lettre (a, b, c ou d) correspondant à la bonne réponse.}
\text{name_brou=Brouillon}
\text{name_hint=Lire ces instructions,Développer une expression de la forme,
  donne,Étudier ces exemples}
# endif
#endif
