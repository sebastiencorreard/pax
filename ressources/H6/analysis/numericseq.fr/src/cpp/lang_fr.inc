#if defined TARGET_calctersuite4
\text{name_statement=Soit \( (u_n) \) la suite de terme définie sur \(\,\NN\) par la relation}
#endif
#if defined TARGET_calctersuite1 || defined TARGET_calctersuite2 || defined TARGET_calctersuite3
\text{name_statement=Soit \( (u_n) \) la suite de terme initial,
  et définie pour tout entier naturel par la relation de récurrence}
#endif
#if defined TARGET_calctersuite1 || defined TARGET_calctersuite2 || defined TARGET_calctersuite3 || defined TARGET_calctersuite4
\text{name_calcul=Calculer les termes,et, de cette suite.}
\text{name_instruction=Arrondir les valeurs au centième.}
#endif
#if defined TARGET_calctersuite7
\matrix{name_statement=Soit \( (u_n) \) une suite arithmétique de premier terme \(u_0\) telle que
  Calculer sa raison \(r\) et son terme initial}
#endif
#if defined TARGET_calctersuite8
\matrix{name_statement=Soit \((u_n)\) une suite géométrique de premier terme \(u_0\) telle que
  Calculer sa raison \(q\) et son terme initial}
\text{name_instruction=Pour faire ces calculs, on utilisera tous les chiffres des nombres}
#endif
#if defined TARGET_calctersuite5SS || defined TARGET_calctersuite6SS || defined TARGET_calctersuite5AS || defined TARGET_calctersuite6AS
\text{name_pronom=Il,Elle}
\text{name_statement=Après une blessure, \prenom reprend son entrainement en natation. \name_pronom[\bg] met au point
  un programme d'entrainement qui va se dérouler sur \ns semaines.
  \name_pronom[\bg] décide de parcourir \u1 km la première semaine et d'augmenter ensuite
  chaque semaine la distance parcourue de \vrep.
  On note \( u_n \) la distance parcourue la \(n\)-ième semaine.
  Pour la première semaine, on a donc
}
\text{name_instruction=Arrondir les valeurs au centième.}
\text{name_statement1=Calculer les termes \(u_2\), \(u_3\) et \(u_\ns\) de cette suite.}
#endif
#if defined TARGET_calctersuite5AS || defined TARGET_calctersuite6AS
\text{name_statement2=Calculer la distance totale parcourue pendant ces \ns semaines}
\text{name_distancetotale=distance totale parcourue}
#endif
\text{name_and=et}
