\text{name_answer=Réponse}
#if defined TARGET_CORreduction || defined TARGET_CORdistribution
# if defined TARGET_CORreduction
\text{name_complement=développées et réduites correspondantes}
# endif
# if defined TARGET_CORdistribution
 \text{name_complement=développées correspondantes}
# endif
\text{name_enonce=Faire correspondre les expressions avec parenthèses avec les expressions
  \name_complement}
#endif
#if defined TARGET_distrired
\text{name_enonce=Développer et réduire l'expression}
#endif
#if defined TARGET_connaissance1 || defined TARGET_connaissance2 || defined TARGET_connaissance3 || defined TARGET_connaissance4
\text{name_enonce=Compléter l'identité remarquable suivante en utilisant les étiquettes fournies&nbsp;}
\text{name_cond=Réponse correcte&nbsp;}
#endif
#if defined TARGET_correspondance1 || defined TARGET_correspondance2
\text{name_enonce=Faire correspondre chaque expression factorisée avec une expression développée égale.}
#endif
#if defined TARGET_tabdeve1 || defined TARGET_tabdeve2
\text{name_instruction=Chaque résultat doit être simplifié.}
\text{name_enonce=Compléter le tableau suivant&nbsp;}
\text{name_enonce2=En vous aidant du tableau précédent, développer et
  réduire l'expression suivante&nbsp;}
#endif
#if defined TARGET_simplifier || defined TARGET_simplifier2 || defined TARGET_simplifier3
\text{name_enonce=Simplifier, si possible, l'expression}
#endif
#if defined TARGET_reduire || defined TARGET_reduire2
\text{name_enonce=Réduire, si possible, l'expression}
#endif
#if defined TARGET_factor1 || defined TARGET_factor2 || defined TARGET_factor3 || defined TARGET_factor4 || defined TARGET_factor5
\text{name_enonce=Factoriser l'expression}
#endif
#if defined TARGET_facteur1 || defined TARGET_facteur2
\text{name_instruction=Vous ne devez utiliser que des coefficients entiers.}
\text{name_enonce=Écrire un facteur commun de l'expression ci-dessous&nbsp;,
  Un facteur commun est }
#endif
#if defined TARGET_completer1 || defined TARGET_completer2 || defined TARGET_completer3
\text{name_enonce=Compléter la factorisation ci-dessous&nbsp;}
\text{name_instruction=Vous devez écrire un résultat simplifié et réduit.}
#endif
#if defined TARGET_deve1 || defined TARGET_deve2 || defined TARGET_deve3 || defined TARGET_deve4 || defined TARGET_deve5 || defined TARGET_deve6 || defined TARGET_deve7 || defined TARGET_deve8
\text{name_enonce=Développer et réduire l'expression}
\text{name_enonce0=On vous propose de résoudre l'exercice en vous guidant.
  Complétez les différentes étapes de calcul qui vous sont proposées.
}
\text{name_instruction=Utiliser les étiquettes pour compléter le calcul.}
\text{name_enonce1=en respectant les couleurs proposées,
  utiliser l'identité,
  pour développer l'expression.}
\text{name_enonce2=simplifier chacun des termes de la somme}
\text{name_enonce3=réécrire l'expression en la simplifiant si possible.}
\text{name_step=Étape}
#endif
#if defined TARGET_etapedev1
\text{name_enonce=Simplifier les expressions suivantes&nbsp;}
\text{name_enonce2=Développer et réduire l'expression suivante&nbsp;}
\text{goodanswer=Bonne réponse}
#endif
#if defined TARGET_completer
\text{name_enonce=Compléter l'égalité suivante&nbsp;}
#endif
