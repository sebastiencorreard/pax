#if defined TARGET_oefenoncqua1 || defined TARGET_oefenoncqua2 || defined TARGET_oefenoncqua3 || defined TARGET_oefenoncqua4 || defined TARGET_oefenoncqua5
\text{name_question=Faire la figure sur une feuille de brouillon
  et donner la mesure de}
\text{name_mesure=Mesure de}
# if defined TARGET_oefenoncqua1
\text{name_enonc1=Soit un rectangle, tel que}
\text{name_enonc2=et}
\text{name_enonc3=la diagonale }
# endif
# if defined TARGET_oefenoncqua2
\text{name_enonc1=Soit un rectangle, tel que}
\text{name_enonc2=le côté, mesure , et la diagonale}
# endif
# if defined TARGET_oefenoncqua3
\text{name_enonc1=Soit un carré, tel que}
\text{name_enonc2=la diagonale mesure}
# endif
# if defined TARGET_oefenoncqua4 || defined TARGET_oefenoncqua5
\text{name_enonc1=Soit un losange, tel que}
# endif
# if defined TARGET_oefenoncqua4
\text{name_enonc2=les diagonales mesurent, et }
# endif
# if defined TARGET_oefenoncqua5
\text{name_enonc2=les côtés mesurent, et une diagonale mesure}
\text{name_enonc3= la deuxième diagonale}
# endif
#endif
#if defined TARGET_oefdemon1 || defined TARGET_oefdemon2 || defined TARGET_oefdemon3 || defined TARGET_oefdemon4 || defined TARGET_oefdemon5
\text{prop=Il a ses côtés opposés de même longueur.,
 Il a ses côtés opposés parallèles.,
Il a quatre angles droits.,
Il a tous ses côtés de même longueur.,
Il a ses diagonales de même longueur.,
Il a ses diagonales perpendiculaires.,
Ses diagonales ont le même milieu.}
\text{name_question=Trouver la (ou les) bonne(s) justification(s)}
# if defined TARGET_oefdemon1
\text{name_enonc=Soit un cercle de centre,
  et deux diamètres, et, du cercle}
\text{name_enonce=Le quadrilatère, est un rectangle.}
# endif
# if defined TARGET_oefdemon2
\text{name_enonc=Soit un cercle de centre,
  et deux diamètres ,et, perpendiculaires du cercle}
\text{name_enonce=Le quadrilatère, est un carré.}
# endif
# if defined TARGET_oefdemon3
\text{name_enonc=Soit un cercle de centre,
  avec un diamètre, et un deuxième cercle de centre, avec un diamètre,
  Les droites, et , sont perpendiculaires.}
\text{name_enonce=Le quadrilatère, est un losange.}
# endif
# if defined TARGET_oefdemon4
\text{name_enonc=Soit un losange,
  La droite , est perpendiculaire à la droite,
  La droite , est perpendiculaire à la droite}
\text{name_enonce=Le quadrilatère,est un rectangle.}
# endif
# if defined TARGET_oefdemon5
\text{name_enonc=Soient deux cercles de même rayon&nbsp;:
  un cercle de centre ,et un cercle de centre ,
 Les deux cercles sont sécants aux points ,et}
\text{name_enonce=Le quadrilatère, est un losange.}
# endif
#endif
#if defined TARGET_oefrepqua1 || defined TARGET_oefrepqua2 || defined TARGET_oefrepqua3 || defined TARGET_oefrepqua4 || defined TARGET_oefrepqua5
# if defined TARGET_oefrepqua1
\text{name_enonce=Soient deux carrés de mêmes mesures.}
\text{name_enonce2=Les côtés mesurent}
# endif
# if defined TARGET_oefrepqua2
\text{name_enonce=Soient quatre carrés de même mesure.}
\text{name_enonce2=Les côtés mesurent}
# endif
# if defined TARGET_oefrepqua3
\text{name_enonce=Soient trois rectangles de mêmes mesures.}
\text{name_enonce2=Largeur,Longueur}
# endif
# if defined TARGET_oefrepqua4 || defined TARGET_oefrepqua5
\text{name_enonce=Soient trois losanges de mêmes mesures.}
\text{name_enonce2=Les diagonales des losanges mesurent, et}
# endif
\text{name_question=Reproduire la figure avec les bonnes mesures sur une feuille de brouillon
  et donner la mesure du segment [AB]&nbsp;}
#endif
#if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc2 || defined TARGET_oefquadvoc3
\text{name_question=Cette figure est}
# if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc2
\text{nat=autre qu'un quadrilatère, un rectangle, un losange, un carré, un quadrilatère quelconque, un cerf-volant}
# endif
# if defined TARGET_oefquadvoc3
\text{nat= autre,un rectangle, un losange, un carré, un quadrilatère quelconque, un cerf-volant}
# endif
#endif
#if defined TARGET_oefquadvoc4 || defined TARGET_oefquadvoc5
\text{name_question=La figure géométrique, est}
#endif
#if defined TARGET_oefquadvoc4
\text{nat=autre, un rectangle, un carré, un losange, un cerf-volant}
#endif
#if defined TARGET_oefquadvoc5
\text{nat=un rectangle, un carré, un losange}
\text{name_question=Donner le nom d'}
#endif
#if defined TARGET_oefconstcompl1 || defined TARGET_oefconstcompl2 || defined TARGET_oefconstcompl3 || defined TARGET_oefconstcompl4 || defined TARGET_oefconstcompl5
\text{name_enonce=Reproduire sur une feuille la figure suivante avec les bonnes dimensions.,
 Mesurer la longueur}
#endif
#if defined TARGET_oefquadprop1 || defined TARGET_oefquadprop2 || defined TARGET_oefquadprop3 || defined TARGET_oefquadprop4 || defined TARGET_oefquadprop5
\text{nat= quadrilatère quelconque, rectangle, carré, losange}
# if defined TARGET_oefquadprop1 || defined TARGET_oefquadprop2 || defined TARGET_oefquadprop3 || defined TARGET_oefquadprop5
\text{name_question=Cliquer sur toutes les propriétés du}
\text{prop=Il a quatre côtés.,
Il a quatre angles.,
Il a ses côtés adjacents de même longueur.,
Il a deux angles égaux.,
Il a ses côtés opposés de même longueur.,
Il a ses côtés opposés parallèles.,
Il a trois angles droits.,
Il a tous ses côtés de même longueur.,
Il a ses angles opposés de même mesure.}
# endif
# if defined TARGET_oefquadprop3
\text{prop=wims(replace internal XXXX by quadrilatère in \prop)}
\text{name_question=Choisir la ou les figure(s) qui possède(nt) toujours
  la propriété suivante}
# endif
# if defined TARGET_oefquadprop4
\text{prop=J'ai quatre côtés.,
  J'ai quatre angles.,
  J'ai mes côtés opposés de même longueur.,
  J'ai mes côtés opposés parallèles.,
  J'ai trois angles droits.,
  J'ai tous mes côtés de même longueur.,
  J'ai mes angles opposés de même mesure.}
\text{name_question=Je suis un quadrilatère ayant exactement les propriétés suivantes
  (c'est-à-dire sans propriété supplémentaire), Je suis un }
# endif
# if defined TARGET_oefquadprop5
\text{name_question=Cliquer sur la ou les propriétés que possède le,
   et que ne possède pas le }
  \text{prop=wims(replace internal Le XXXX by Il in \prop)}
# endif
#endif
#if defined TARGET_oefquaddiag1 || defined TARGET_oefquaddiag2 || defined TARGET_oefquaddiag3 || defined TARGET_oefquaddiag4 || defined TARGET_oefquaddiag5
\text{nat= quadrilatère quelconque, rectangle, carré, losange}
# if defined TARGET_oefquaddiag1
\text{name_question=Cliquer sur toutes les propriétés du}
#endif
# if defined TARGET_oefquaddiag3
\text{prop=Il a deux diagonales.,
Il a ses diagonales de même longueur.,
Il a ses diagonales perpendiculaires.,
Ses diagonales ont le même milieu.}
\text{name_question=Choisir le ou les quadrilatère(s) qui possède(nt)
  toujours la propriété suivante&nbsp;:}
\text{name_quad=quadrilatère}
# endif
# if defined TARGET_oefquaddiag1 || defined TARGET_oefquaddiag2 || defined TARGET_oefquaddiag5
\text{prop=Il a deux diagonales.,
Il a ses diagonales de même longueur.,
Il a ses diagonales perpendiculaires.,
Il a ses diagonales parallèles.,
Ses diagonales ont le même milieu.}
# endif
# if defined TARGET_oefquaddiag2
\text{name_question=Cliquer sur toutes les propriétés d'un }
# endif
# if defined TARGET_oefquaddiag4
\text{prop=J'ai deux diagonales.,
  J'ai des diagonales qui ont le même milieu.,
  J'ai des diagonales de même longueur.,
  J'ai des diagonales perpendiculaires.}
\text{name_question=Je suis un quadrilatère qui vérifie exactement les propriétés suivantes
  (c'est-à-dire sans propriété supplémentaire), Je suis}
# endif
# if defined TARGET_oefquaddiag5
\text{name_quad=Il}
\text{name_question=Cliquer sur la ou les propriétés que possède le,
  mais que ne possède pas le}
\text{prop=wims(replace internal Le XXXX by \name_quad in \prop)}
# endif
#endif
#if defined TARGET_oefrecqua1 || defined TARGET_oefrecqua2 || defined TARGET_oefrecqua3 || defined TARGET_oefrecqua4
\text{name_nom=carré,rectangle,carré,losange,quadrilatère quelconque}
\text{name_enonce=Le centre du cercle est le point}
\text{name_question=Donner la nature du quadrilatère}
#endif
#if defined TARGET_oefrecqua5
\text{noms=rectangle,carré,quadrilatère quelconque,losange}
\text{name_coul=rouge,noir,bleu,vert}
\text{name_enonce=Nous avons deux cercles de même rayon.
Le point , est le centre du premier cercle
et le point,  est le centre du deuxième cercle.}
\text{name_question=Donner la nature des quadrilatères&nbsp;, Quadrilatère}
#endif
