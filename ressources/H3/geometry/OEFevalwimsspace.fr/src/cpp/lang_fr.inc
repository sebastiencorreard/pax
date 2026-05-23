\text{name_youranswer=Votre réponse}
#if defined TARGET_longueur1 || defined TARGET_longueur2 || defined TARGET_longueur3 || defined TARGET_longueur4 || defined TARGET_longueur5 || defined TARGET_volume1 || defined TARGET_volume2 || defined TARGET_volume3 || defined TARGET_volume4 || defined TARGET_volume5 || defined TARGET_airelaterale1 || defined TARGET_airelaterale2 || defined TARGET_airelaterale3 || defined TARGET_airelaterale4 || defined TARGET_airelaterale5
\text{name_prec=à l'unité,au dixième,au centième}
\text{name_inst=Si nécessaire, donner l'arrondi}
#endif
#if defined TARGET_volume1 || defined TARGET_volume2 || defined TARGET_volume3 || defined TARGET_volume4 || defined TARGET_volume5
# if defined TARGET_volume1
\text{name_enonce=Quelle est la mesure du volume d'un cube dont les arêtes mesurent}
# endif
# if defined TARGET_volume2
\text{name_enonce=Quelle est la mesure du volume d'un pavé dont la longueur mesure,
 la largeur,et la hauteur}
# endif
# if defined TARGET_volume3
\text{name_enonce=Quelle est la mesure du volume d'une pyramide de hauteur,
  et dont la base est un carré de côté}
# endif
# if defined TARGET_volume4
\text{name_enonce=Quelle est la mesure du volume d'un prisme droit de hauteur,
  et dont la base est un triangle équilatéral de côté}
# endif
# if defined TARGET_volume5
\text{name_enonce=Quelle est la mesure du volume d'un cône de révolution de hauteur,
  et dont la base est un disque de rayon}
# endif
#endif
#if defined TARGET_parallel1 || defined TARGET_parallel2 || defined TARGET_parallel3 || defined TARGET_parallel4 || defined TARGET_parallel5 || defined TARGET_perpendiculaire1 || defined TARGET_perpendiculaire2 || defined TARGET_perpendiculaire3 || defined TARGET_perpendiculaire4 || defined TARGET_perpendiculaire5
\text{name_question=Parmi les propriétés suivantes, lesquelles sont vraies}
# if defined TARGET_parallel1 || defined TARGET_parallel3 || defined TARGET_perpendiculaire1 || defined TARGET_perpendiculaire2
\text{name_enonce=est un cube dont la représentation en perspective cavalière est donnée ci-contre.}
# endif
# if defined TARGET_parallel2 || defined TARGET_parallel4 || defined TARGET_perpendiculaire3 || defined TARGET_perpendiculaire4
\text{name_enonce=est un pavé droit dont la représentation en perspective cavalière est donnée ci-contre.}
# endif
# if defined TARGET_perpendiculaire5 || defined TARGET_parallel5
\text{name_enonce=est une pyramide régulière de sommet S, de hauteur (SO) et dont la base est
  un carré de centre O. La représentation en perspective cavalière de
  cette pyramide est donnée ci-contre.}
# endif
#endif
#if defined TARGET_airelaterale1 || defined TARGET_airelaterale2 || defined TARGET_airelaterale3 || defined TARGET_airelaterale4 || defined TARGET_airelaterale5
# if defined TARGET_airelaterale1
\text{name_enonce=Quelle est la mesure de l'aire de la surface totale d'un cube
  dont les arêtes mesurent}
# endif
# if defined TARGET_airelaterale2
\text{name_enonce=Quelle est la mesure de l'aire de la surface totale d'un pavé dont
  la longueur mesure, la largeur, et la hauteur}
# endif
# if defined TARGET_airelaterale3
\text{name_enonce=Quelle est la mesure de l'aire de la surface totale d'une pyramide
  à base triangulaire dont toutes les faces sont des triangles équilatéraux
  dont les côtés mesurent}
# endif
# if defined TARGET_airelaterale4
\text{name_enonce=Quelle est la mesure de l'aire de la surface totale d'une pyramide
  à base carrée dont toutes les arêtes mesurent}
# endif
# if defined TARGET_airelaterale5
\text{name_enonce=Quelle est la mesure de l'aire de la surface totale d'un prisme droit dont
  la base est un triangle équilatéral de côté,
  et dont la hauteur mesure}
# endif
#endif
#if defined TARGET_formuleaire1 || defined TARGET_formuleaire2 || defined TARGET_formuleaire3 || defined TARGET_formuleaire4 || defined TARGET_formuleaire5 || defined TARGET_formulevolume1 || defined TARGET_formulevolume2 || defined TARGET_formulevolume3 || defined TARGET_formulevolume4 || defined TARGET_formulevolume5
\text{name_inst=Tapez, pour}
#endif
#if defined TARGET_formuleaire1 || defined TARGET_formuleaire2 || defined TARGET_formuleaire3 || defined TARGET_formuleaire4 || defined TARGET_formuleaire5
# if defined TARGET_formuleaire1
\text{name_enonce=Quelle est la mesure de l'aire d'un carré dont les côtés mesurent}
# endif
# if defined TARGET_formuleaire2
\text{name_enonce=Quelle est la mesure de l'aire d'un rectangle de longueur \(A\)
  et de largeur \(B\)&nbsp;}
# endif
# if defined TARGET_formuleaire3
\text{name_enonce=Quelle est la mesure de l'aire d'un disque de rayon \(r\)&nbsp;}
# endif
# if defined TARGET_formuleaire4
\text{name_enonce=Quelle est la mesure de l'aire d'un triangle dont un côté mesure \(b\)
  et dont la hauteur relative à ce côté mesure \(h\)&nbsp;}
# endif
# if defined TARGET_formuleaire5
\text{name_enonce=Quelle est la mesure de l'aire d'un parallélogramme dont la mesure
  de deux côtés opposés est,et dont la distance entre ces deux côtés mesure}
# endif
#endif
#if defined TARGET_formulevolume1 || defined TARGET_formulevolume2 || defined TARGET_formulevolume3 || defined TARGET_formulevolume4 || defined TARGET_formulevolume5
# if defined TARGET_formulevolume1
\text{name_enonce=Quelle est la mesure du volume d'un cube dont les arêtes mesurent}
# endif
# if defined TARGET_formulevolume2
\text{name_enonce=Quelle est la mesure du volume d'un pavé droit de longueur,
 de largeur, et de hauteur}
# endif
# if defined TARGET_formulevolume3
\text{name_enonce=Quelle est la mesure du volume d'une pyramide de hauteur \(h\)
  et dont la base est,d'aire \(B\)&nbsp;}
# endif
# if defined TARGET_formulevolume4
\text{name_enonce=Quelle est la mesure du volume d'un cône de révolution
  de hauteur \(h\) et dont la base est un disque de rayon \(r\)&nbsp;}
# endif
# if defined TARGET_formulevolume5
\text{name_enonce=Quelle est la mesure du volume d'un prisme droit de hauteur \(h\)
  et dont la base est, d'aire \(B\)&nbsp;}
# endif
# if defined TARGET_formulevolume3 ||  defined TARGET_formulevolume5
\text{name_base=un triangle,un rectangle,un carré,un losange,un pentagone,un parallélogramme}
# endif
#endif
#if defined TARGET_longueur1 || defined TARGET_longueur2 || defined TARGET_longueur3 || defined TARGET_longueur4 || defined TARGET_longueur5
# if defined TARGET_longueur1
\text{name_enonce=est un parallélépipède rectangle dont les dimensions sont,
  Quelle est la mesure de la diagonale de la face }
# endif
# if defined TARGET_longueur2
\text{name_enonce=Quelle est la longueur de la diagonale d'un cube dont
  les arêtes mesurent}
# endif
# if defined TARGET_longueur3
\text{name_enonce=Quelle est la mesure de la hauteur d'une pyramide régulière
  à base carrée dont toutes les arêtes mesurent}
# endif
# if defined TARGET_longueur4
\text{name_enonce=est un cube dont les arêtes mesurent,
  Le point O est le centre de la face,
  Quelle est la mesure de l'arête, de la pyramide}
# endif
# if defined TARGET_longueur5
\matrix{name_enonce=est un parallélépipède rectangle dont les dimensions sont
  Les points,et,sont deux points respectivement des segments,tels que
  Le point,est le point de la droite,tel que,et,sont parallèles.
  De même, est le point de la droite,tel que ,et ,sont parallèles.
  La face, du prisme droit, ainsi obtenu est un rectangle.}
\text{name_question=Quelle est la mesure de la largeur de ce rectangle&nbsp;}
# endif
#endif
#if defined TARGET_patron1
\text{name_enonce=Parmi les figures suivantes, lesquelles
  sont des patrons de solides&nbsp;}
#endif
#if defined TARGET_patron2
\text{name_enonce=Mettre en correspondance chaque nom de solide avec son patron.}
\text{data=Cube,Pavé droit, Pyramide à base carrée,Pyramide à base triangulaire}
#endif
#if defined TARGET_patron3
\text{name_enonce=Parmi les figures suivantes, lesquelles
  sont des patrons de cubes&nbsp;}
#endif
#if defined TARGET_patron4
\text{name_enonce=Parmi les figures suivantes, lesquelles sont des
  patrons de pyramides&nbsp;}
#endif
#if defined TARGET_patron5
\text{name_enonce=Parmi les figures suivantes, lesquelles sont des patrons
  de pavés droits&nbsp;}
#endif
