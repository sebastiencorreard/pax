#if defined TARGET_combi || defined TARGET_combi2 || defined TARGET_combi4
\text{name_enonce=Soient, NUM vecteurs dans l'espace. Calculez le vecteur}
#endif
#if defined TARGET_angle
\text{name_enonce=Nous avons trois points dans l'espace&nbsp;}
\text{name_question=Calculer l'angle \(\widehat{B A C}\) (en degrés, compris entre 0 et 180)}
\text{name_answer=L'angle}
\tex{name_hint=Utiliser la relation entre le produit scalaire de deux vecteurs et leur angle.}
#endif
#if defined TARGET_combifind || defined TARGET_combifind2
\text{name_enonce=Soit,NUM vecteurs dans l'espace.}
\text{name_question=Exprimer \(v=(\A, \B, \C)\) comme combinaison linéaire de}
#endif
#if defined TARGET_voltetra
\text{name_enonce=Calculer le volume du tétraèdre dans l'espace cartésien dont les 4 sommets sont}
\text{name_hint1=Un tétraèdre est un polyèdre dans l'espace avec 4 sommets.}
\text{name_hint2=Si l'on prend 4 sommets adjacents d'un parallélépipède, le tétraèdre
  engendré par ces 4 sommets a un volume qui est 1/6 celui du parallélépipède.}
\text{name_hint3=Le volume du parallélépipède se calcule par le produit mixte des vecteurs.}
\text{name_answer=Volume}
#endif
#if defined TARGET_airetriang
\text{name_question=Calculer l'aire du triangle dans l'espace euclidien dont les 3 sommets sont}
\text{name_answer=Aire}
\text{name_hint=Le produit vectoriel de deux vecteurs donne l'aire d'un parallélogramme,
  et la moitié d'un parallélogramme est un triangle.}
#endif
#if defined TARGET_airellelo
\text{name_question=Calculer l'aire du parallélogramme dans l'espace euclidien dont les 4 sommets sont}
\text{name_hint=L'aire du parallélogramme est la longueur du produit vectoriel
  des deux vecteurs représentant deux côtés adjacents du parallélogramme.}
\text{name_answer=Aire}
#endif
#if defined TARGET_givenscale
\text{name_enonce=Soient,
  trois vecteurs dans l'espace. Trouvez le vecteur \(v\) ayant les produits
  scalaires suivants&nbsp;}
#endif
#if defined TARGET_givenvec
\text{name_enonce=Soit, un vecteur dans l'espace. Déterminez le vecteur,
  tel que le produit vectoriel \(u \wedge v) soit égal à }
#endif
#if defined TARGET_lenvec
\text{name_enonce=Soit , un vecteur dans l'espace. Soit un vecteur \(v\)
  perpendiculaire à \(u\). Etant donné que la longueur de \(v\)
  est égale à, quelle est la longueur du produit vectoriel \(u\wedge v\)&nbsp;}
\text{name_answer=Longueur}
#endif
#if defined TARGET_parallelo
\text{name_enonce=Nous avons un parallélogramme \(A B C D) dans l'espace cartésien,
  dont les 3 premiers sommets sont de coordonnées}
\text{name_question=Calculez les coordonnées du quatrième sommet \(D\).}
#endif
#if defined TARGET_perp2
\text{name_enonce=Soient, deux vecteurs dans l'espace. Trouvez un vecteur,
  qui est perpendiculaire à la fois à,et à}
\text{name_hint=Le produit vectoriel de \(v_1\) et \(v_2\) est
  perpendiculaire à la fois à \(v_1\) et à \(v_2\).}
#endif
#if defined TARGET_perpvec
\text{name_enonce=Soit,
  un vecteur dans l'espace. Trouvez le vecteur \(v\) perpendiculaire à \(u\)
  tel que leur produit vectoriel \(u\wedge v\) soit égal à}
#endif
#if defined TARGET_rellin
\text{name_enonce=Nous avons 4 vecteurs dans l'espace&nbsp;}
\text{name_question=Trouver 4 entiers \(a\), \(b\), \(c\), \(d\)
  qui ne soient pas tous tous nuls et tels que}
\text{name_cond1= sont des entiers non tous nuls}
\text{name_cond2=La somme algébrique des vecteurs est zéro}
#endif
#if defined TARGET_volpara
\text{name_enonce=Calculer le volume du parallélépipède dans l'espace cartésien
  ayant un sommet, et dont les 3 sommets adjacents à \(A\) sont}
\text{name_answer=Volume}
\text{name_hint=Le volume du parallélépipède se calcule par le produit mixte
  des vecteurs.}
#endif
#if defined TARGET_vecscal
\text{name_enonce=Soit, un vecteur dans l'espace. Trouvez le vecteur
  \(v\) connaissant son produit scalaire et son produit vectoriel avec \(u\)&nbsp;}
#endif
#if defined TARGET_lenvec2
\text{name_enonce=Soit, un vecteur dans l'espace. Soit un vecteur \(v\) de longueur ,
  Étant donné que le produit scalaire \(\langle u,v \rangle\) est égal à ,
  quelle est la longueur du produit vectoriel}
\text{name_answer=Longueur}
\text{name_hint=Décomposez \(v\) en somme de deux vecteurs \(v_1\) et \(v_2\),
  où \(v_1\) est perpendiculaire à \(u\), et \(v_2\) est proportionnel à \(u\).}
#endif
#if defined TARGET_sumvect1 || defined TARGET_sumvect
\text{name_instruction1=La figure ci-dessus est une vue en perspective de six cubes de même dimension.}
\matrix{name_feedback=On a,relation de Chasles
  La bonne réponse est donc le point
  est un parallélogramme
  le quadrilatère
  Donc, les vecteurs
  sont égaux
  Donc}
\text{name_and=et}
\text{name_hint=Par les propriétés des cubes}
# if defined TARGET_sumvect
\text{name_instruction2=Complétez l'égalité suivante par un point de la figure
  pour que l'égalité suivante soit vraie.}
\text{name_answer=Point demandé}
\text{name_pointille=(en pointillés bleus),(en pointillés verts)}
# endif
# if defined TARGET_sumvect1
\text{name_instruction2=Tracer la représentation géométrique du vecteur, dont l'origine
  est }
\text{name_answer=}
\text{name_pointille=}
\text{name_orig=L'origine du vecteur que vous avez tracé n'est pas correcte,L'extrémité du vecteur que vous avez tracé n'est pas correcte}
\text{name_long=La longueur du vecteur que vous avez tracé n'est pas correcte,
  La longueur du vecteur que vous avez tracé est correcte}
\text{name_direction=Le vecteur que vous avez tracé n'a pas la bonne direction.,
  Le vecteur que vous avez tracé a la bonne direction.}
# endif
#endif

