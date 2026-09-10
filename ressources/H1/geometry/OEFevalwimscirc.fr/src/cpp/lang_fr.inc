#if defined TARGET_oefconstcer1 || defined TARGET_oefconstcer2 || defined TARGET_oefconstcer3 || defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
\text{name_statement=Mettre dans l'ordre les phrases du programme de construction,
  permettant de tracer le dessin ci-contre.}
# if defined TARGET_oefconstcer1
\text{enonc=Tracer un segment [\nom[2]\nom[3]] de 12 cm de longueur.,
  Placer le point \nom[1]&#130 milieu du segment [\nom[2]\nom[3]].,
  Tracer le cercle de centre \nom[1] et passant par le point \nom[2].}
# endif
# if defined TARGET_oefconstcer2
\text{enonc=Placer deux points distincts \nom[2] et \nom[1].,
  Tracer le cercle (C1) de centre \nom[1] et passant par le point \nom[2].,
  Placer le point \nom[3] à l'intersection de la droite (\nom[1]\nom[2]) et du cercle (C1).,
  Tracer le cercle (C2) de centre \nom[3] et passant par le point \nom[2].}
# endif
# if defined TARGET_oefconstcer3
\text{enonc=Tracer un segment [\nom[2]\nom[1]] de 6 cm.,
  Tracer un cercle de centre \nom[1] et passant par le point \nom[2].,
  Tracer une corde [\nom[2]\nom[3]] de 6 cm.,
  Tracer une corde [\nom[3]\nom[4]] de 6 cm.,
  Tracer une corde [\nom[4]\nom[5]] de 6 cm.,}
# endif
# if defined TARGET_oefconstcer4
\text{enonc=Tracer un cercle de centre \nom[1] et de rayon \r cm.,
  Tracer deux diamètres [\nom[2]\nom[3]] et [\nom[4]\nom[5]] du cercle.,
  Tracer les segments [\nom[2]\nom[4]] et [\nom[4]\nom[3]].,
  Placer les points \nom[6] et \nom[7] respectivement les milieux des segments [\nom[2]\nom[4]] et [\nom[4]\nom[3]].,
  Tracer les segments [\nom[6]\nom[5]] et [\nom[7]\nom[5]].,}
# endif
# if defined TARGET_oefconstcer5
\text{enonc=Tracer un cercle de centre \nom[1] et de rayon \r cm.,
  Tracer un diamètre [\nom[2]\nom[3]] du cercle.,
  Placer le milieu \nom[4] du segment [\nom[2]\nom[1]].,
  Placer un point \nom[5] appartenant au cercle tel que le segment [\nom[4]\nom[5]] mesure \r cm.,
  Tracer les segments [\nom[4]\nom[5]] et [\nom[3]\nom[5]].,}
# endif
# if defined TARGET_oefconstcer3 || defined TARGET_oefconstcer4
\text{name_instruction=Vous pouvez faire une recherche au brouillon.}
# endif
# if defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
\text{name_stat2=Faire la construction et donner la mesure suivante&nbsp;}
# endif
# if defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
\text{name_cond=précision suffisante&nbsp;,mesure avec marge d'erreur&nbsp;}
# endif
#endif
#if defined TARGET_oefcercle3
\text{enonc=Le point \nom[1] est ,le centre, du cercle.
Le segment [\nom[5]\nom[6]] est ,une corde, du cercle.
Le segment [\nom[2]\nom[3]] est ,un diamètre, du cercle.
Le segment [\nom[1]\nom[4]] est ,un rayon, du cercle.
Le point \nom[1] est le centre ,du cercle, de diamètre [\nom[2]\nom[3]].}
\text{name_statement=Soit un cercle.
  Compléter la phrase sans oublier l'article&nbsp;}
#endif
#if defined TARGET_oefcercle2
\text{name_enonc1=Soit un cercle de centre}
\text{reps=cercle,centre,diamètre,rayon,corde,rond,trait,sommet,compas}
\text{name_statement=Placer les légendes&nbsp;}
#endif
#if defined TARGET_oefcercle1
\matrix{enonc=Tout point, qui appartient, à un cercle, est à une même, distance, du centre.
Un cercle, est l'ensemble de tous, les points du plan situés, à une même distance, d'un point appelé, centre.
Un cercle, de centre O, est une figure plane constituée, de tous les points situés, à la même distance, appelée rayon, du point O.
On appelle cercle, de centre O et, de rayon r, l'ensemble des points d'un plan situés, à la distance r, du point O.}
\text{name_statement=Placer les mots dans l'ordre pour faire une phrase correcte&nbsp;}
#endif
#if defined TARGET_oeftracecerc1
\matrix{quest=Le cercle de centre \nom[1] et passant par le point \nom[3] est le cercle ,1
Le cercle de centre \nom[1] et passant par le point \nom[2] est le cercle ,3
Le cercle de centre \nom[2] et passant par le point \nom[1] est le cercle ,2
Le cercle de centre \nom[2] et passant par le point \nom[3] est le cercle ,2
Le cercle de centre \nom[3] et passant par le point \nom[1] est le cercle ,3
Le cercle de centre \nom[1] et de rayon le segment [\nom[1]\nom[3]] est le cercle ,1
Le cercle de centre \nom[1] et de diamètre le segment [\nom[1]\nom[3]] est le cercle ,3
Le cercle de centre \nom[2] et de rayon le segment [\nom[2]\nom[3]] est le cercle ,2
Le cercle de centre \nom[2] et de rayon le segment [\nom[2]\nom[1]] est le cercle ,2
Le cercle de centre \nom[2] et de diamètre le segment [\nom[2]\nom[3]] est le cercle ,3
Le cercle de diamètre le segment [\nom[4]\nom[3]] est le cercle ,1
Le cercle de diamètre le segment [\nom[1]\nom[3]] est le cercle ,2
}
#endif
#if defined TARGET_oeftracecerc2
\matrix{quest=Le cercle de centre \nom[1] et de rayon \r cm est le cercle ,3
Le cercle de centre \nom[1] et de rayon \d cm est le cercle ,1
Le cercle de centre \nom[1] et de diamètre \d cm est le cercle ,3
Le cercle de centre \nom[1] et de diamètre \e cm est le cercle ,1
Le cercle de centre \nom[2] et de rayon \r cm est le cercle ,2
Le cercle de centre \nom[2] et de rayon \d cm est le cercle ,3
Le cercle de centre \nom[2] et de diamètre \r cm est le cercle ,3
Le cercle de centre \nom[2] et de diamètre \d cm est le cercle ,2
Le cercle de centre \nom[3] et de rayon \r cm est le cercle ,3
Le cercle de centre \nom[3] et de rayon \d cm est le cercle ,3
}
#endif
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\text{name_none=aucun des deux}
#endif
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\text{name_coche=Cocher la bonne réponse}
#endif
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\matrix{name_enonce=Soient deux cercles (C1) et (C2).
  Le segment, mesure}
#endif
#if defined TARGET_oeftracecerc3 || defined TARGET_oeftracecerc4 || defined TARGET_oeftracecerc5
\matrix{name_enonce=Soient trois cercles avec leurs points d'intersection&nbsp;
Un cercle de centre \nom[1] et de rayon
Un cercle de centre \nom[2] et de rayon
Un cercle de centre \nom[3] et de rayon
Les points \nom[9], \nom[3] et \nom[6] sont alignés.
}
#endif
#if defined TARGET_oeftracecerc3 || defined TARGET_oeftracecerc4
\text{name_enonce2=Le point,est à , du point,et à}
#endif
#if defined TARGET_oeftracecerc5
\text{name_enonce2=Donner la liste des points (séparés par une virgule) qui sont à ,
  du point ,et à ,du point}
#endif
#if defined TARGET_oefcercle4 || defined TARGET_oefcercle5
\text{reps=une corde,un rayon,un diamètre,un point}
\text{name_enonce=Soient trois cercles avec leurs points d'intersection.
  Les points \nom[9], \nom[3] et \nom[6] sont alignés.}
# if defined TARGET_oefcercle5
\text{name_inst=Compléter la phrase sans oublier l'article&nbsp;}
# endif
\text{name_quest=Le segment, est , du cercle de centre}
#endif
