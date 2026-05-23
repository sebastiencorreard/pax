#if defined TARGET_Trianglerectan
\text{name_enonce=mesure,et,Combien mesure,en}
#endif
#if defined TARGET_rugby
\text{name_data=À quelle distance du milieu des poteaux se trouve le ballon,
  À quelle distance du centre du terrain se trouve le ballon,
  L'entraîneur veut donner un conseil à son joueur. Quelle distance sépare le joueur de l'entraîneur}
\text{name_enonce=L'essai a été marqué à, mètres du poteau de corner. ,
  Le joueur décide de se placer à, mètres de la ligne d'essai.}
\text{name_answer=La distance en mètre est d'environ}
\text{name_cond1=Votre réponse est juste à 0.5 mètre près}
\text{name_cond2=Votre réponse est juste et respecte la consigne d'approximation}
\text{name_cond3=Votre réponse respecte la consigne d'approximation}
\text{name_feed=La bonne réponse est,mètres.}
\text{name_instruction=Donner la réponse (en mètres) sous forme de l'entier
  le plus proche.}
#endif
#if defined TARGET_Puits
\text{name_enonce=,mesure , le puits a une profondeur de ,et un diamètre de}
\text{name_question=À quelle distance le ballon se trouve-t-il de ,, en \(cm\)
  et arrondi à l'unité}
\text{name_answer=La distance}
#endif
#if defined TARGET_Mdiane
\text{name_enonce= est la médiane qui part du point \(A\) et touche le milieu de
  l'hypoténuse. Sachant que,  mesure, et, combien mesure, en}
\text{name_answer=Longueur de}
#endif
#if defined TARGET_Cerfvolant
\text{name_enonce=À quelle hauteur le cerf-volant plane-t-il,en}
\text{name_answer=La hauteur}
\text{name_sol1=Le cerf volant, sa hauteur et la droite horizontale partant des mains du personnage
forment un triangle rectangle, son hypoténuse étant le cerf-volant et sa corde.}
\text{name_sol2=On peut donc utiliser la formule du théorème de Pythagore pour calculer la hauteur à
  laquelle se situe le cert-volant.,On schématise le dessin du cerf-volant par&nbsp;}
\text{name_sol3=On note dans le triangle ABC rectangle en B&nbsp;,
  la longueur du cert-volant et de sa corde,
  la longueur entre les mains du personnage et le point culminant du cerf-volant,
  la hauteur du cerf-volant à déterminer.}
\text{name_sol4=Selon le théorème de Pythagore on a l'égalité suivante&nbsp;,
  D'où, Et,Finalement le cerf volant se situe à une hauteur de}
#endif
#if defined TARGET_Arbreabattu
\text{name_enonce=Un arbre a été abattu par la foudre. Quelle était sa hauteur avant, en}
\text{name_answer=La hauteur de l'arbre}
\text{name_sol1=La souche, le tronc et le sol forment un triangle rectangle,
  l'hypoténuse symbolisé par le tronc coupé.}
\text{name_sol2=On utilise le théorème de Pythagore.,On note&nbsp;,
  la hauteur du tronc coupé,
  la hauteur de la souche,
  la longueur au sol}
\text{name_sol3=On a alors la formule&nbsp;,
  D'où la hauteur de l'arbre est&nbsp;,}
#endif
#if defined TARGET_etagere1 || defined TARGET_etagere2
\text{name_enonce=Toto a posé une boule sur son étagère.
  Mais la planche n'est peut-être pas horizontale.}
\text{name_warning=Le dessin n'est pas à l'échelle.}
\text{name_long=Les dimensions de l'étagère sont}
\text{name_choix=La boule roule vers l'intérieur de l'étagère.,
  La boule reste en place.,
  La boule tombe par terre.}
# if defined TARGET_etagere1
\text{name_long1=Toto a mesuré que}
\text{name_question=Que va faire la boule&nbsp;}
# endif
# if defined TARGET_etagere2
\text{name_long1=Toto va mesurer }
\text{name_question=Que va-t-elle trouver parmi les choix suivants (en cm)&nbsp;}
# endif
#endif
#if defined TARGET_avion
\text{ville=Metropolis,Springfield, El Dorado}
\text{ville=randitem(\ville)}
\text{name_enonce=Un avion vole au dessus de XXXX.
Il doit atterrir dans un aéroport situé à YYYY km de la ville.
Pour descendre, il parcourt ZZZZ km.}
\text{name_question=À quelle altitude volait-il quand il était au dessus de la ville&nbsp;}
#endif
#if defined TARGET_bird
\text{name_enonce=Un oiseau posé au sol veut aller manger une cerise en haut
  d'un arbre. Le pied de l'arbre est à XXXX mètres de lui
  et l'arbre mesure YYYY mètres de haut.}
\text{name_question=Quelle distance l'oiseau doit-il parcourir&nbsp;}
#endif
#if defined TARGET_moho0 || defined TARGET_moho1
\text{name_enonce=Un léger séisme s'est produit.
  Voici la représentation des ondes sismiques directes et des ondes PmP se
  réfléchissant sur le Moho.}
\matrix{name_explanation=épicentre du séisme
  station où le séisme est enregistré
  foyer du séisme
  point de réflexion des ondes PmP
  temps d'arrivée des ondes directes P à la station S
  temps d'arrivée des ondes PmP à la station S
  différence entre temps d'arrivée à la station S des ondes PmP
  et des ondes P.}
\text{name_compute=Calculer}
\text{name_hint=Appliquer le théorème de Pythagore à des triangles
  convenables.}
# if defined TARGET_moho1
\text{name_enonce2=On cherche à évaluer la profondeur de la discontinuité de
  de Mohorovicic ou MOHO.}
# endif
\text{name_question=La vitesse des ondes P dans la croûte continentale
  à cet endroit est à peu près de VVVV km/s.
  La profondeur du foyer sismique est \(h=hhhh\) km,
  la distance entre E et S est \(D=DDDD\) km.}
# if defined TARGET_moho0
\text{name_question=\name_question
  La profondeur du Moho est \(H=HHHH\) km.}
# endif
# if defined TARGET_moho1
\text{name_question=\name_question
  Les temps d'arrivée des ondes en S sont}
\text{name_prec=On prendra l'entier le plus proche.}
# endif
#endif
#if defined TARGET_horizon1 || defined TARGET_horizon2 || defined TARGET_horizon3
\text{name_inst=Le dessin n'est pas à l'échelle et représente symboliquement
  la situation.}
# if defined TARGET_horizon1
\text{name_enonce=Sachant que le rayon de la terre est à peu près RRRR m,
  calculer la distance en m à l'horizon pour un observateur
  situé à une altitude  \(h\) de HHHH m.}
\text{name_answer=Distance à l'horizon, Distance}
# endif
# if defined TARGET_horizon2
\text{name_enonce=Calculer le rayon d'une planète imaginaire sachant que
  la distance en m à l'horizon pour un observateur
  situé à une altitude \(h\) de HHHH m est de YYYY m.}
\text{name_answer=Rayon de la planète,Rayon}
# endif
# if defined TARGET_horizon3
\text{name_enonce=Le mont A est à l'altitude HHHH m.
  Sachant que le rayon de la terre est à peu près RRRR m,
  calculer l'altitude minimum du sommet du mont B pour qu'on puisse le
  voir du mont A sachant qu'il est à une distance de YYYY m à vol d'oiseau du mont B.}
\text{name_answer=Altitude de B,Altitude}
# endif
#endif
