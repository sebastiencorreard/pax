\text{name_introdroite=Soit \((\d)\) la droite d'équation&nbsp;}
\text{name_answer=Réponse&nbsp;}
#if defined TARGET_equcond1
\text{question=Écrire l'équation d'une droite parallèle à la droite \((\d))}
#endif
#if defined TARGET_equcond2
\text{question=Écrire l'équation d'une droite perpendiculaire à la droite \((\d))}
#endif
#if defined TARGET_equcond21 || defined TARGET_equcond22
\text{name_inst=Vous devez écrire votre équation sous la forme}
\text{name_equation=Une équation est}
#endif
#if defined TARGET_equcond21
\text{question=Écrire une équation d'une droite parallèle à la droite \((\d))}
 \text{name_cond=L'équation est bien celle d'une droite parallèle}
 \text{name_feed=C'est l'équation de la même droite ! Il n'y a pas assez de droites parallèles à}
#endif
#if defined TARGET_equcond22
\text{question=Écrire une équation d'une droite perpendiculaire à la droite \((\d))}
 \text{name_cond=L'équation est bien celle d'une droite perpendiculaire}
#endif
#if defined TARGET_equcondbc1 || defined TARGET_equcondbc2 || defined TARGET_equcondbc3 || defined TARGET_equcondbc4
\text{name_question=L'équation est&nbsp;}
# if defined TARGET_equcondbc1
 \text{question=Écrire l'équation de la droite parallèle à la droite \((\d))
 et passant par le point de coordonnées}
# endif
# if defined TARGET_equcondbc2
\text{question=Écrire l'équation de la droite parallèle à la droite \((\d))
 et passant par le point de coordonnées}
# endif
# if defined TARGET_equcondbc1 || defined TARGET_equcondbc2
\text{question=Écrire l'équation de la droite parallèle à la droite \((\d))
 et passant par le point de coordonnées}
# endif
# if defined TARGET_equcondbc3 || defined TARGET_equcondbc4
\text{question=Écrire l'équation de la droite perpendiculaire à la droite \((\d))
  et passant par le point de coordonnées}
# endif
#endif
#if defined TARGET_equcondbc21
 \text{question=Écrire une équation de la droite parallèle à la droite \((\d))
  et passant par le point de coordonnées}
#endif
#if defined TARGET_equcondbc22
\text{question=Écrire une équation de la droite parallèle à la droite \((\d))
  et passant par le point de coordonnées}
#endif
#if defined TARGET_equcondbc23
\text{question=Écrire une équation de la droite perpendiculaire à la droite \((\d))
  et passant par le point de coordonnées}
#endif
#if defined TARGET_equcondbc24
\text{question=Écrire une équation de la droite perpendiculaire à la droite \((\d)\)
 et passant par le point de coordonnées}
#endif
#if defined TARGET_lectequ1 || defined TARGET_lectequ3 || defined TARGET_lectequ5
 \text{question=Quel est le coefficient directeur de la droite \((\d))}
#endif
#if defined TARGET_lectequ2 || defined TARGET_lectequ4 || defined TARGET_lectequ6
 \text{question=Quelle est l'ordonnée à l'origine de la droite \((\d))}
#endif
#if defined TARGET_point1
 \text{question=Donner les coordonnées d'un point appartenant à la droite \((\d)\)}
#endif
#if defined TARGET_point2
 \text{question=Donner les coordonnées d'un point appartenant à la droite \((\d)\)
 mais n'appartenant pas à l'axe des ordonnées}
#endif
#if defined TARGET_point3
 \text{question=Donner les coordonnées d'un point appartenant à la droite \((\d)\)}
#endif
#if defined TARGET_point4
 \text{question=Donner les coordonnées d'un point appartenant à la droite \((\d)\)
  mais n'appartenant pas à l'axe des ordonnées}
#endif
\text{name_yesno=Oui,Non}

#if defined TARGET_sontelles1 || defined TARGET_sontelles2 || defined TARGET_sontelles3 || defined TARGET_sontelles4 || defined TARGET_sontelles5 || defined TARGET_sontelles6
\text{name_enonce=Soient,et, les deux droites d'équation&nbsp;}
\text{name_question=Les droites, et , sont-elles}
# if defined TARGET_sontelles2 || defined TARGET_sontelles1
 \text{propriete=parallèles}
# endif
# if defined TARGET_sontelles3 || defined TARGET_sontelles4
 \text{propriete=sécantes}
# endif
# if defined TARGET_sontelles5 || defined TARGET_sontelles6
 \text{propriete=perpendiculaires}
# endif
#endif
#if defined TARGET_equcondbc21 || defined TARGET_equcondbc22 || defined TARGET_equcondbc23 || defined TARGET_equcondbc24
\text{name_condition=L'équation est correcte}
\text{name_inst=Vous devez écrire votre équation sous la forme}
\text{name_equation=Une équation est}
#endif
#if defined TARGET_equcond1 || defined TARGET_equcond2
\text{name_equation=L'équation de la droite choisie est&nbsp;}
# if defined TARGET_equcond1
\text{name_feed=C'est l'équation de la même droite ! Il n'y a pas assez de droites parallèles à }
\text{name_condition=L'équation est bien celle d'une droite parallèle}
# endif
# if defined TARGET_equcond2
\text{name_condition=L'équation est bien celle d'une droite perpendiculaire}
# endif
#endif
#if defined TARGET_equcondbc1 || defined TARGET_equcondbc2 || defined TARGET_equcondbc3 || defined TARGET_equcondbc4
\text{name_question=L'équation est&nbsp;}
#endif
#if defined TARGET_lectequ2 || defined TARGET_lectequ4 || defined TARGET_lectequ6
 \text{reponse=L'ordonnée à l'origine}
#endif
#if defined TARGET_lectequ1 || defined TARGET_lectequ3 || defined TARGET_lectequ5
 \text{reponse=Le coefficient directeur}
#endif