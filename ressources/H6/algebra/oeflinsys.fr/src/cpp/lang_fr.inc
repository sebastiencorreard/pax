#if defined TARGET_triangular
\text{name_question=Déterminez la valeur de \(x_1\) dans la solution du système
  linéaire suivant de \(n\) équations et \(n\) inconnues, pour \(n \ge 3\).}
#endif

#if defined TARGET_typesol
\text{yes=Oui}
\text{no=Non}
\matrix{name_question=Soit un système de,en
  Parmi les propositions suivantes, lesquelles sont vraies&nbsp;}
\text{name_choice=Le système peut ne pas avoir de solution.,
  Le système peut avoir une solution unique.,
  Le système peut avoir une infinité de solutions.}
\text{name_instruction=On suppose qu'au moins une variable apparait
  effectivement dans chaque équation.}
\text{name_gene=homogènes,homogène}
\text{name_nonnul=non nulles,non nulle}
\text{name_not=non}
\text{name_Equ=équations linéaires,équation linéaire}
\text{name_Var=variables,variable}
\text{name_prompt=est vraie}
#endif
#if defined TARGET_Sommetstriangl
\text{name_instruction=Nous avons un triangle \(A B C\) dans le plan cartésien, tel que&nbsp;}
\text{name_question=Quelles sont les coordonnées des 3 sommets \(A\), \(B\), \(C\) du triangle&nbsp;}
\text{name_hint=Pour donner votre réponse, on suppose}
\text{name_text=Le milieu du côté,est}
#endif
#if defined TARGET_quadrilat
\text{name_question=Les quatre sommets \(A\), \(B\), \(C\), \(D\) d'un quadrilatère
  dans le plan cartésien vérifient&nbsp;}
\text{name_question2=Le milieu du côté,est}
\text{name_question3=Quel est le milieu \((x,y)) du côté \(D A\)&nbsp;}
#endif
#if defined TARGET_Quatreentier3 || defined TARGET_Quatreentiers || defined TARGET_Quatreentier2 || defined TARGET_Troisentiers || defined TARGET_sixentiers
\text{name_instruction=Soient \N entiers,tels que}
\text{name_mean=La moyenne de, et de, est}
# if defined TARGET_Quatreentiers || defined TARGET_Troisentiers || defined TARGET_Quatreentier3
\text{name_question=Quels sont ces \N entiers}
# endif
# if defined TARGET_Quatreentier2 || defined TARGET_sixentiers
\text{name_question=Quelle est la moyenne de}
#   if defined TARGET_Quatreentier2
\text{name_hint=Pour quelle valeur de \(t\) le système linéaire suivant
  a-t-il une solution&nbsp;}
#   endif
# endif
#endif
#if defined TARGET_Intersectiondr
\text{name_instruction=Considérons deux droites dans le plan cartésien, définies respectivement
  par les équations}
\text{name_question=Déterminer le point d'intersection \(p = (x,y)) des deux droites.}
#endif
#if defined TARGET_Distancesgales
\text{name_question=Trouver les coordonnées du point \(p = (x,y)\) dans le plan
  cartésien, tel que}
\text{name_question2=La distance entre,et, égale celle entre}
\text{name_hint=L'ensemble de points à distance égale vers deux points
  \(q_1\) et \(q_2\) forment une droite. Trouvez d'abord l'équation de cette droite
  en fonction de coordonnées de \(q_1) et \(q_2).}
#endif
#if defined TARGET_circleeq
\text{name_instruction=Tout cercle dans le plan cartésien peut être décrit par une
  équation de la forme}
\text{name_instruction1=où \(a\), \(\b\), \(\c\) sont des nombres réels.
  Trouvez l'équation du cercle \(C\) passant par les trois points}
\text{name_instruction2=en donnant les valeurs de}
\text{name_condition=contient}
#endif
#if defined TARGET_centercircle
\text{name_question=Trouvez le centre,du cercle passant par les trois points}
\text{name_hint1=Le centre du cercle est le point qui est à distance égale vers les
  trois points donnés.}
\text{name_hint2=Un point M est à égale distance des deux points A et B si et seulement si la
  somme vectorielle AM + BM est perpendiculaire au vecteur AB, ce qui se traduit
  par une équation linéaire en les coordonnées de M.}
\text{name_condition= est à distance égale vers les 3 points}
#endif
#if defined TARGET_almostdiag
\text{name_instruction=Déterminez la valeur de \(x_1\) de la solution du système
linéaire suivant de \(n\) équations et \(n\) inconnues, pour \(n\ge 3\).}
\text{name_hint=La solution est une fonction de \(n\), qui dépend de la parité de \(n\).}
\text{name_parite=impair,pair,si}
#endif
#if defined TARGET_alloy3
\text{name_instruction=Une usine produit un alliage à partir de trois types de métaux
de récupération. Les compositions des trois métaux récupérés sont comme suit.}
\text{name_question=L'usine a reçu une commande de \ton tonnes d'alliage avec
  \x0% de fer, \y0% de nickel et \z0% de cuivre. Combien de tonnes de chaque
  type de métal récupéré faut-il prendre pour satisfaire cette commande&nbsp;}
\text{name_table=type,fer,nickel,cuivre,métal}
\text{name_help=Donner les valeurs en gardant 4 chiffres significatifs.}
\matrix{name_feed0=Il faut au total
  tonnes d'un alliage des 3 métaux et non
  tonnes}
\matrix{name_feed=En utilisant
  du métal A
  du métal B et
  du métal C, on obtient
  d'un alliage dont les proportions en fer, nickel et cuivre ne sont pas celles voulues&nbsp;
  on obtient un alliage composé de
  de fer
  de nickel et
  de cuivre}
\text{name_solution1=Notons \(a\), \(b\) et \(c\) respectivement les quantités  des métaux A,
  B et C (exprimées en tonnes) nécessaires pour satisfaire la commande.
  Ces quantités sont solutions du système linéaire suivant}
\text{name_solution2=Ce système a une unique solution qui est}
\matrix{name_solution3=Donc avec
  du métal A
  du métal B et
  du métal C
  on peut obtenir
  d'un alliage composé de
  de fer
  de nickel et
  de cuivre
}
#endif
#if defined TARGET_3bottles
\text{name_instruction=Trois bouteilles contiennent chacune une certaine quantité d'eau.}
\text{name_text=Si l'on verse,d'eau de la bouteille, à la bouteille,a,
  fois plus d'eau que,a la même quantité d'eau que}
\text{name_question=Combien d'eau y a-t-il dans chaque bouteille (en centilitres)&nbsp;}
\text{name_bottle=Bouteille}
#endif
#if defined TARGET_solution
\matrix{name_choix=cations,de cations
  anions,d'anions}
\matrix{name_choix=calcium,magnésium,sodium,potassium
  chlorure,sulfate,nitrate,nitrite,carbonate}
\text{name_header=Type,Solution}
\text{name_instruction=Trois solutions ont des teneurs en ppm (partie par million),
  données par le tableau ci-dessous.}
\text{name_question=Nous voulons former,
  centilitres d'une solution avec,
  ppm de,
  en mélangeant les 3 solutions. Combien de centilitres devons-nous prendre de
  chacune&nbsp;}
#endif
#if defined TARGET_homo3x4 || defined TARGET_homo2x3
\text{name_instruction=Trouvez une solution non nulle du système homogène suivant.}
\text{name_hint=Les valeurs \list de votre solution doivent être des entiers.}
\text{name_cond=entiers non nuls,Équation,satisfaite}
#endif
#if defined TARGET_solve3x3 || defined TARGET_solve2x2
  \text{name_question=Trouvez la solution du système suivant.}
#endif
#if defined TARGET_achat
\title{Au marché}
\text{name_vegetable=légume,légumes}
\text{name_names_veg=haricots, concombres, tomates, poivrons, aubergines, chou}
\text{name_fruit=fruit,fruits}
 \text{name_names_fruit=pommes, poires, oranges, clémentines, bananes, melons}
\text{name_deplus=euros de plus sur les,que sur les,autant d'argent sur les}

\text{name_instruction=Un restaurateur se fournit au marché. Il a acheté,
  kilogrammes de , à ,euros le kilo,pour,euros au total}
\text{name_question=Sachant qu'il a dépensé,combien de kilogrammes a-t-il acheté de chaque type de,
  combien a-t-il dépensé pour chaque type de}
\text{name_prompt= en kilogramme}
#endif
#if defined TARGET_ages
\text{name_party=une party, une réception, une rencontre, une réunion,
	un dîner, une fête de famille}
\text{name_discover=découvre, constate, dit, sait}
\text{name_mean=la moyenne des âges,la somme des âges}
\text{name_plusmoins1=qu'il a XXXXX ans de plus que YYYYY,
	que YYYYY a XXXXX ans de moins que lui,
	que YYYYY est né XXXXX ans après lui,
	qu'il est né XXXXX ans avant YYYYY,
	qu'il avait XXXXX ans quand YYYYY était né}
\text{name_plusmoins2=qu'il a XXXXX ans de moins que YYYYY,
	que YYYYY a XXXXX ans de plus que lui,
	que YYYYY est né XXXXX ans avant lui,
	qu'il est né XXXXX ans après YYYYY,
	que YYYYY avait XXXXX ans quand il était né
}
\text{name_instruction=Trois messieurs ayant le même jour d'anniversaire discutent de leurs âges
  pendant}
\text{name_question=Quand, atteindra, ans,de,et de, sera}
\text{name_instruction1=La somme des trois âges est,Quand,est né,était,
  Quel est l'âge de chacun&nbsp;}
\text{name_age=Âge de}
#endif
