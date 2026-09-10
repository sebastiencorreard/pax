\text{name_warning=A faire sans calculatrice.}
\text{name_and=et}
#if defined TARGET_assocfctrep1 || defined TARGET_assocfctrep2 || defined TARGET_assocfctrep4
\text{name_instruction=Retrouver l'équation de chaque courbe sachant qu'elle est de la forme}
#endif
#if defined TARGET_assocfctrep3
\text{lsttxt= est l'image de la courbe de fonction carré par la translation de vecteur}
\text{name_instruction=Dans un repère orthonormé \((O;\vec{i},\vec{j})), on donne les courbes
  \(C) et \(\Gamma) d'équations respectives}
\text{name_question=Comment tracer ces courbes à partir de celle de la fonction carré&nbsp;}
#endif
#if defined TARGET_assocfctrep5
\text{lsttxt= est l'image de la courbe de fonction inverse par la translation de vecteur}
\text{lsttxt2= C est symétrique par rapport au point}
\text{name_instruction=Dans un repère orthonormé \((O;\vec{i},\vec{j})), on donne la courbe
  \(C) d'équation}
\text{name_question=Comment tracer la courbe \(C) à partir de celle de la fonction inverse&nbsp;,
  Quel élément de symétrie possède \(C)&nbsp;}
#endif

#if defined TARGET_exprcomp1 || defined TARGET_exprcomp2 || defined TARGET_exprcomp3 || defined TARGET_exprcomp4 || defined TARGET_exprcomp5
# if defined TARGET_exprcomp5
  \text{name_instruction1=On considère une fonction \(f) définie par}
  \text{name_instruction2= et on veut l'écrire sous
  la forme d'une composée \(f=u \circ v).
  Cocher le couple de fonctions \(u, v) pouvant convenir.}
# else
  \matrix{name_instruction=On considère les fonctions suivantes
  L'expression de la composée est-elle correcte ou incorrecte&nbsp;}
# endif
  \text{lstrep=Correcte, Incorrecte}
#endif

#if defined TARGET_majmin1 || defined TARGET_majmin2 || defined TARGET_majmin3 || defined TARGET_majmin4 || defined TARGET_majmin5
\text{listerep=un maximum,un minimum,un majorant,un minorant,une valeur quelconque}
#endif
