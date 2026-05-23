#if defined TARGET_definition1 || defined TARGET_definition2 || defined TARGET_definition3 || defined TARGET_definition4
\text{name_bad=La droite perpendiculaire à (AAAA BBBB) et passant par le milieu de [AAAA BBBB],
  L'ensemble des points équidistants de AAAA et BBBB,
  La droite joignant AAAA au milieu du côté [BBBB CCCC],
  La droite passant par AAAA et perpendiculaire à (BBBB CCCC),
  La demi-droite qui partage l'angle \(\widehat{BBBB AAAA CCCC}\) en deux angles de même mesure}
\text{name_question=est un triangle. Voici une liste de propriétés.
  Lesquelles sont vérifiées par}
# if defined TARGET_definition1
\text{name_enonce=la médiatrice du segment}
# endif
# if defined TARGET_definition2
 \text{name_enonce=la médiane issue du sommet}
# endif
# if defined TARGET_definition3
 \text{name_enonce=la hauteur issue du sommet}
# endif
# if defined TARGET_definition4
 \text{name_enonce=la bissectrice issue du sommet}
# endif
#endif
#if defined TARGET_definition5
\text{bad=Intersection des médiatrices,Intersection des médianes,Intersection des hauteurs,Intersections des bissectrices}
\text{good=Centre du cercle circonscrit,Centre de gravité,Orthocentre,Centre du cercle inscrit}
\text{name_enonce=est un triangle quelconque. Ses trois médiatrices sont concourantes en un point.
  Il en est de même pour ses bissectrices, médianes et hauteurs.
  Pouvez-vous mettre en correspondance chacun de ces points avec son nom}
#endif
#if defined TARGET_distance1 || defined TARGET_distance2
\text{name_question=est une droite du plan et AAAA un point.}
# if defined TARGET_distance1
 \text{name_enonce=Quelle est la définition de la distance du point AAAA  à la droite (d)&nbsp;}
 \text{name_good=La longueur du plus petit segment joignant AAAA  à un point de la droite (d).}
 \text{name_bad=La longueur d'un segment joignant AAAA  à un point de la droite (d).,La longueur du plus grand segment joignant AAAA  à un point de la droite (d).}
# endif
# if defined TARGET_distance2
 \text{name_enonce=Quel est le plus petit segment joignant AAAA  à un point de la droite (d)&nbsp;}
 \text{name_good=Le segment joignant AAAA  au pied de la perpendiculaire à (d) passant par AAAA .}
 \text{name_bad=Le segment joignant AAAA  au pied de la parallèle à (d) passant par AAAA.,Peu importe tous les segments joignant AAAA  et un point de (d) sont de même longueur.}
# endif
#endif
#if defined TARGET_distance3 || defined TARGET_distance4 || defined TARGET_distance5
\text{name_answer=Votre réponse&nbsp;}
# if defined TARGET_distance3 || defined TARGET_distance5
\text{name_segment=Segment}
\text{name_color=rouge,bleu,vert,violet,marron}
\text{name_enonce=a mesuré tous les segments colorés ci-contre.
  Les résultats sont reportés ci-dessous&nbsp;}
\text{name_question=Pouvez-vous lui indiquer quelle est la distance entre
  le point AAAA et la droite noire&nbsp;}
#   if defined TARGET_distance5
\text{name_bad=Elle est inférieure à ,
  Elle est égale à ,
  Elle est supérieure à}
#   endif
# endif
# if defined TARGET_distance4
\text{name_question=Chaque carreau fait 0.5 cm.
  Quelle est la distance entre le point AAAA et la droite&nbsp;}
# endif
#endif
#if defined TARGET_calculd1 || defined TARGET_calculd2 || defined TARGET_calculd3 || defined TARGET_calculd4 || defined TARGET_calculd5
\text{name_answer=Votre réponse&nbsp;} ||
\text{name_inst=Si nécessaire arrondir votre résultat au dixième.}
\text{name_color=rouge,bleue,verte,violette,marron}
#endif
#if defined TARGET_calculd1 || defined TARGET_calculd4
\text{name_enonce=L'angle \(\widehat{CCCCBBBBAAAA}) mesure,
  degrés et la distance entre le point AAAA et le point BBBB est de}
\text{name_question=Quelle est la distance entre AAAA et la droite}
#endif
#if defined TARGET_calculd2
\text{name_enonce=Chaque carreau fait 0.5 cm.
  Quelle est la distance entre le point AAAA et la droite&nbsp;}
#endif
#if defined TARGET_calculd3
\text{name_enonce=Le triangle, est isocèle en AAAA. Les deux côtés de même longueur
   mesurent,et la base mesure}
\text{name_question=Quelle est la distance entre AAAA et la base du triangle}
#endif
#if defined TARGET_calculd5
\text{name_enonce=est un carré dont les côtés mesurent,
   Quelle est la distance entre le sommet AAAA
   et la diagonale représentée sur le dessin&nbsp;}
#endif
#if defined TARGET_deftangente1 || defined TARGET_deftangente2 || defined TARGET_deftangente3
 \text{bad=Oui,Non}
#endif
#if defined TARGET_deftangente4 || defined TARGET_deftangente5
\text{bad=Elles sont perpendiculaires,Elles ne sont pas perpendiculaires,Elles peuvent être perpendiculaires cela dépend,Elles sont parallèles,Elles ne sont pas parallèles,Elles peuvent être parallèles cela dépend}
#endif
#if defined TARGET_deftangente1 || defined TARGET_deftangente2 || defined TARGET_deftangente3 || defined TARGET_deftangente4 || defined TARGET_deftangente5
\text{name_color=bleue,verte,violette,marron}
# if defined TARGET_deftangente1 || defined TARGET_deftangente2
 \text{name_enonce=La droite XXXX semble-t-elle tangente au cercle&nbsp;&#63;}
# endif
# if defined TARGET_deftangente3
 \text{name_enonce=La droite XXXX semble-t-elle tangente au cercle de centre AAAA&nbsp;&#63;}
# endif
# if defined TARGET_deftangente4
\text{name_enonce=La droite XXXX et la droite YYYY se coupent en un point du cercle de centre AAAA. La droite XXXX est la tangente au cercle en ce point.}
# endif
# if defined TARGET_deftangente5
\text{name_enonce=La droite XXXX et la droite YYYY se coupent en un point du cercle de centre AAAA mais la droite XXXX n'est pas tangente au cercle.
  Que peut-on dire de la droite XXXX et de la droite YYYY&nbsp;&#63;}
# endif
#endif
-
