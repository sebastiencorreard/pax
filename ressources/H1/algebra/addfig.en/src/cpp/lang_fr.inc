#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=Remplissez le dessin par les objets donnés,
  de sorte que la somme des éléments bordant chaque région colorée
  soit égale à \sum.}
\text{txtsum=Somme pour la}
\text{condpre=région&nbsp;}
\text{condpost=}
\text{txtpost=}
\text{colorname=\colornamef}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3
\text{txtstatement=Remplissez le dessin par les objets donnés,
  de sorte que toute case d'un étage supérieur soit la somme des deux cases
  immédiatement au-dessous d'elle.}
#endif

#if defined TARGET_pentagram
\text{lname=ligne}
\text{txtstatement=Remplissez le dessin par les objets donnés,
  de sorte que la somme de chaque \lname soit égale à \sum.}
\text{txtsum=Somme de la}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
\text{colorname=\colornamef}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
\text{lname=côté}
\text{txtsum=Somme du}
\text{colorname=\colornamem}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=ligne}
\text{txtsum=Somme de la}
\text{colorname=\colornamef}
# endif
\text{txtstatement= Remplissez le dessin par les objets donnés,
  de sorte que la somme de chaque \lname soit égale à \sum.}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
#endif
\text{txtbox=Case}
