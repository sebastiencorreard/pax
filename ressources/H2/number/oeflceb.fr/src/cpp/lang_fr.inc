#if defined TARGET_lceb1a || defined TARGET_lceb1b || defined TARGET_lceb2a || defined TARGET_lceb2b
\text{instruction1=Avec les nombres de la première ligne du tableau et les 4 opérations,
vous devez obtenir le nombre \N ; écrivez votre première opération et son résultat,
par exemple}
\text{instruction2=envoyez le résultat, puis continuez.}
\matrix{conditiontext=Vous avez utilisé les nombres donnés
Les opérations sont justes
Vous avez trouvé le résultat ou le résultat le plus proche
Votre nombre est compris entre \M1 et \M2}
\matrix{instruction0=Choisissez un nombre entre \M1 et \M2.
Vous n'avez pas joué le jeu ... }
\matrix{feedtext=Votre réponse
 Une réponse possible}
#endif

#if defined TARGET_graphe3
\text{instruction1=Le compte est bon ou presque bon}
\text{instruction2=compléter le graphe en mettant les opérations effectuées
  pour obtenir la solution trouvée&nbsp;}
#endif

#if defined TARGET_graphe0 || defined TARGET_graphe1 || defined TARGET_graphe2
\text{instruction=Voici un graphe permettant de résoudre ce problème de
  <i>le compte est bon</i> ou de trouver une solution proche.
  Écrire les équations correspondantes}
\text{name_condition=Les équations sont justes,
  Les équations sont celles demandées}
\text{name_feed=La suite des opérations est,
  Vous avez oublié des équations.}
#endif
