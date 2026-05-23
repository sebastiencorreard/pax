#if defined TARGET_classer1 || defined TARGET_classer2 || defined TARGET_classer3 || defined TARGET_classer4
\text{name_enonce=Classer les fonctions suivantes suivant leur nature}
\text{name_type=Fonctions linéaires,
  Fonctions affines,
  Fonctions non affines,
  non linéaires}
#endif
#if defined TARGET_eqdroite
\matrix{name_enonce=La droite \(d\) passe par les points, et
Puisque, la droite \(d\) a une équation de la forme}
\text{name_question=Compléter l'équation de}
\text{name_answer=Expression}
#endif
#if defined TARGET_imagecoord1 || defined TARGET_imagecoord2
\text{name_feed=Voici la réponse}
# if defined TARGET_imagecoord1
\text{name_enonce=Voici une représentation  graphique de la fonction \(g\).
  Sur l'axe des ordonnées, cliquer sur le point d'ordonnée}
# endif
# if defined TARGET_imagecoord2
\text{name_enonce=Voici une représentation  graphique de la fonction \(f\).
  Sur l'axe des abscisses, cliquer sur le point d'abscisse \(x\) tel que}
# endif
#endif
#if defined TARGET_qcmfonct
\text{name_question=Quelle est la fonction \(f\) dont la représentation graphique
  est ci-dessous ? Donner une expression de \(f(x)\).}
#endif
#if defined TARGET_qcmequa
\text{name_question=Quelle est l'équation réduite de la droite tracée ci-dessous&nbsp;}
#endif
#if defined TARGET_CORequa3 || defined TARGET_CORfonct3 || defined TARGET_CORequa4|| defined TARGET_CORfonct4 || defined TARGET_CORequa5 || defined TARGET_CORfonct5
\text{co=red;#;rouge,green;#;vert,yellow;#;jaune,purple;#;violet,blue;#;bleu,black;#;noir}
\text{name_question1=Mettre en correspondance chaque fonction avec la couleur de sa représentation graphique dans le repère ci-contre.}
\text{name_question2=Mettre en relation chaque équation avec la couleur de la droite correspondante dans le repère ci-contre.}
\text{name_answer=Réponse}
#endif
#if defined TARGET_graphima || defined TARGET_graphant
\text{name_enonce=La représentation graphique de la fonction affine,
  est la suivante&nbsp;}
\text{name_answer=Votre réponse}
# if defined TARGET_graphima
\text{name_question=Quelle est l'image de,par}
\text{name_ans=L'image de,par la fonction,est}
\text{name_sol1=L'image de, par la fonction, est par définition
  <b>l'ordonnée</b> du point sur la droite dont l'abscisse est}
\text{name_sol2=On place donc le point de la droite dont l'abscisse est,
  puis on lit son ordonnée.}
# endif
# if defined TARGET_graphant
\text{name_question=Quel nombre a pour image,par la fonction }
\text{name_ans=Le nombre qui a pour image,par la fonction,est}
\text{name_sol1=Le nombre qui a pour image, par la fonction, est par définition
  <b>l'abscisse</b> du point sur la droite dont l'ordonnée est}
\text{name_sol2=On place donc le point de la droite dont l'ordonnée est,
  puis on lit son abscisse.}
\text{name_cond=Image}
# endif
#endif
#if defined TARGET_fnctaff1
\text{name_enonce=L'image de, par la fonction affine , est ,
  et l'image de, par la même fonction est}
\text{name_enonce2=La fonction, peut s'écrire sous la forme }
\text{name_question=Quelle est cette écriture}
\text{name_answer=Expression}
#endif
#if defined TARGET_fnctaff2
\text{bad=Oui,Non}
\matrix{name_enonce=Le tableau suivant donne l'image de trois nombres par la fonction FFFF
Le tableau suivant donne l'image par la fonction FFFF de trois nombres}
\text{name_question=peut-elle être une fonction affine}
\text{name_answer=Votre réponse}
#endif
#if defined TARGET_fnctaff3 || defined TARGET_fnctaff4
\text{name_don=L'image par, de, est}
\text{name_enonce=est une fonction affine telle que l'image de,
  est, et l'image de, est}
\text{name_aim=Le but est de trouver l'expression de la fonction,
  La fonction est affine, il faut donc trouver deux nombres \(a\) et
  \(b\) tels que,pour tous nombres}
# if defined TARGET_fnctaff3
\text{name_inst=Vous pouvez vous aider de la solveuse
  en cliquant sur son lien en bas de cette page.}
\text{name_resolv=Pour résoudre cet exercice, répondez aux questions suivantes}
\text{name_and=et}
\text{name_quest=Question,Votre réponse,Traduire la phrase,
  par une équation faisant intervenir}
\text{name_sentence=L'image par, de, est}
\text{name_question=Résoudre le système d'équations d'inconnues \(a\) et \(b\)
  formé par les deux équations des questions précédentes.}
\text{name_answer=Première équation,Deuxième équation}
# endif
# if defined TARGET_fnctaff4
\text{name_resolv=Pour résoudre cet exercice, répondez aux questions suivantes}
\text{name_and=et}
\text{name_quest=Question,Votre réponse}
\text{name_question=Pour une fonction affine,
  le quotient, pour \(u\) et \(v\) deux nombres quelconques mais différents,
  est égal au coefficient directeur de la fonction,
  En déduire la valeur de \(a\).}
\text{name_deduc=On déduit donc que la formule de la fonction,
  est de la forme}
\text{name_question2=Déduire une équation du premier ordre d'inconnue \(b\) de la phrase}
\text{name_question3=Trouvez la valeur de \(b\) en résolvant l'équation de la question 2.}
\text{name_answer=Équation}
# endif
#endif
