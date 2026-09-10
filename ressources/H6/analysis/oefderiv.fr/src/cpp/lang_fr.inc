#if defined TARGET_rectangle1 || defined TARGET_rectangle2 || defined TARGET_rectangle3 || defined TARGET_rectangle4 || defined TARGET_rectangle5 || defined TARGET_rectangle6
\text{name_direction=augmente,diminue}
\text{name_long=longueur,largeur}
\text{name_larg=la largeur,la longueur}
\text{name_la=la}
\text{name_sa=sa}
\text{name_constante=constante}
\text{name_constant=constant}
\text{name_cm=centimètres}
\text{name_cm2=centimètres carrés}
\text{name_area=son aire}
\text{name_area0=l'aire}
\text{name_sarea=son aire}
\text{name_peri=le périmètre}
\text{name_speri=son périmètre}
\text{name_answer=Vitesse}
\matrix{name_statement=Soit un rectangle dont
  à vitesse constante de
  centimètres par seconde, mais dont
  reste
  à
  À l'instant où
  égale
  quelle est la vitesse de changement de
  en}
#endif
#if defined TARGET_hyper || defined TARGET_hyper2 || defined TARGET_trigo || defined TARGET_trigo2 || defined TARGET_rat || defined TARGET_rat2 || defined TARGET_poly || defined TARGET_poly2
\text{name_enonce=Calculer la dérivée de la fonction \(f\) définie par}
#endif
#if defined TARGET_trigo3
\text{name_enonce=Calculer la dérivée de la fonction \(f\) définie par, au point}
#endif
#if defined TARGET_poly || defined TARGET_poly2
# if defined TARGET_poly
\text{name_sol=On a, donc}
\text{name_at=en}
# endif
#endif
#if defined TARGET_mult1 || defined TARGET_mult2 || defined TARGET_multmixt
# if defined TARGET_mult1
\text{name_question=Soit,Calculer la dérivée}
# endif
# if defined TARGET_multmixt
\text{name_question=Soit la fonction \(h\) définie par ,Calculer la dérivée}
# endif
# if defined TARGET_mult2
\text{name_question=Soit,Calculer la dérivée seconde}
# endif
# if defined TARGET_mult1 || defined TARGET_mult2
\text{name_enonce=Soit deux fonctions dérivables \(f\) et \(g\)
  dont certaines valeurs et valeurs de dérivées sont montrées dans le tableau suivant&nbsp;}
# endif
# if defined TARGET_multmixt
\text{name_enonce=Soit \(f\) une fonction dérivable
  dont certaines valeurs et valeurs de sa dérivée sont montrées dans le tableau suivant&nbsp;}
\text{name_hint=Calculer d'abord la valeur et la dérivée de la fonction,
  au point, puis appliquer la formule de multiplication.}
\text{name_sol=Soit,Nous avons, donc}
# endif
#endif
#if defined TARGET_comp1 || defined TARGET_comp2
# if defined TARGET_comp1
\text{name_enonce=Soient deux fonctions dérivables \(f\) et \(g\)
  dont certaines valeurs et valeurs de dérivées sont montrées dans le tableau suivant.}
\text{name_sol=On a, d'où,}
# endif
# if defined TARGET_comp2
\text{name_enonce=Soient 3 fonctions dérivables \(f\), \(g\) et \(h\),
dont certaines valeurs et valeurs de dérivées sont montrées dans le tableau suivant.}
# endif
\text{name_question=Soit \(s\) la fonction définie par,,
  Calculer la dérivée }
#endif
#if defined TARGET_compmixt
\text{name_enonce=Soit une fonction dérivable \(f\) définie de \(\mathbb{R}\) dans \(\mathbb{R}\).
  dont certaines valeurs et valeurs de dérivées sont montrées dans le tableau suivant.}
\text{name_question=Soit \(g\) la fonction définie sur \(\,\RR\) par,
  et soit \(s) la composée de \(g) et \(f) définie sur \(\mathbb{R}\) par,
  Calculer la dérivée }
#endif
#if defined TARGET_compvert1a || defined TARGET_compvert1b
\text{name_enonce=Soit \(f\) une fonction dérivable de dérivée \(f'\).
  Calculez la dérivée de la fonction \(g\) définie par}
\text{name_answer=Dérivée}
#endif
#if defined TARGET_circle || defined TARGET_circle2
\text{name_enonce=Soit un cercle dont le rayon augmente à une vitesse
  constante de, centimètres par seconde.}
\text{name_answer=Vitesse d'aire}
#endif
#if defined TARGET_circle3 || defined TARGET_circle4
\text{name_enonce=Soit un cercle dont l'aire augmente à une vitesse
  constante de, centimètres carrés par seconde.}
\text{name_answer=Vitesse de rayon}
#endif
#if defined TARGET_circle
\text{name_question=À l'instant où le rayon égale,centimètres,
  quelle est la vitesse d'augmentation de son aire}
#endif
#if defined TARGET_circle2
\text{name_question=À l'instant où son aire égale,centimètres carrés,
  quelle est la vitesse d'augmentation de son aire}
#endif
#if defined TARGET_circle3
\text{name_question=À l'instant où l'aire égale,centimètres carrés,
  quelle est la vitesse d'augmentation de son rayon}
#endif
#if defined TARGET_circle4
\text{name_question=À l'instant où son rayon égale,centimètres,
  quelle est la vitesse d'augmentation de son rayon}
#endif
#if defined TARGET_multvert1
\text{name_enonce=Soit \(f\) une fonction dérivable de dérivée \(f'\).
  Calculer la dérivée de la fonction \(g\) définie par}
\text{name_answer=Dérivée }
#endif
#if defined TARGET_div1
\text{name_enonce=Soient deux fonctions dérivables \(f\) et \(g\)
dont certaines valeurs et valeurs de dérivées sont montrées dans le tableau suivant&nbsp;}
\text{name_question=Soit \(h\) la fonction définie par, Calculer la dérivée}
#endif
#if defined TARGET_arcarg
\text{name_enonce=Établissez la correspondance entre les fonctions et leurs
  dérivées dans le tableau suivant.}
#endif
#if defined TARGET_divmixt
\text{name_enonce=Soit \(f\) une fonction dérivable
    dont certaines valeurs et valeurs de sa dérivée
    sont montrées dans le tableau suivant&nbsp;}
\text{name_question=Soit, la fonction définie par, Calculer la dérivée}
\text{name_hint=Calculer d'abord la valeur et la dérivée de la fonction,
  au point,puis appliquer la formule de division.}
\text{name_feed=Soit, On a, donc}
#endif
#if defined TARGET_righttriangle
\text{name_enonce=Soit un triangle droit comme suit, où,
et, à une vitesse constante de}
\text{name_question=Au moment où, quelle est la vitesse du changement de,
  en}
\text{name_answer=Vitesse de BC en}
\text{name_direction=augmente,diminue}
#endif
#if defined TARGET_tower
\text{name_enonce=Quelqu'un marche vers une tour à une vitesse constante de,
  mètres par seconde.}
\text{name_question=Si la hauteur de la tour est de,mètres,
  à quelle vitesse (en m/s) la distance entre lui et le sommet de la tour
  diminue-t-elle quand la distance entre lui et le pied de la tour est de, mètres&nbsp;}
\text{name_answer=Vitesse en}
#endif
#if defined TARGET_signenombre
\text{name_enonce=Constituez une étude du signe de,
  en choisissant quatre des phrases données plus bas.}
\text{name_posneg=positif,négatif}
\text{name_p1=D'abord,Pour commencer}
\text{name_p23=Ensuite,Puis}
\text{name_p4=Enfin,Donc,Par conséquent,Finalement,Pour conclure}
\matrix{name_step1=considérons la, on définit une, soit la
fonction}
\matrix{name_step2=calculons,on calcule
la dérivée}
\text{name_step3=on constate que,pour}
\matrix{name_step4=d'où,donc
est}
\matrix{name_bad1=considérons la, on définit une, soit la
 fonction}
\matrix{name_bad2=calculons,on calcule
la dérivée}
\text{name_bad3=on constate que ,pour}
\matrix{name_bad4=d'où,donc
est}
\text{name_answer=Étape}
\text{name_cond=Le raisonnement est bien construit}
\text{name_feed1=Logique en désordre :
  comment êtes-vous arrivé à calculer \(f'(x)\) avant même d'avoir défini}
\text{name_feed2=Erreur&nbsp;: pour avoir,il faut prendre, au lieu de}
\text{name_feed3=Erreur. Avez-vous bien calculé la dérivée de}
\text{name_feed4=Votre deuxième étape est prématurée.}
\text{name_feed5=Vous vous êtes trompé dans le calcul du signe de, Vérifiez}
\text{name_feed6=Vous avez mal compris le signe dans la dernière étape. Réfléchissez&nbsp;:
  si \(f '(x) XXXX 0\) pour \(x \in [a,b]\), \(f\) est-elle croissante ou
  décroissante ? Donc est-ce qu'on a \(f(a) XXXX f(b)\)&nbsp;}
\text{name_feed7=Mauvaise conclusion : la dernière étape ne donne même pas le signe de}
#endif
#if defined TARGET_reciproc
\text{name_enonce=Soit,la fonction définie par}
\text{name_enonce2=Vérifiez que \(f\) est bijective, elle a donc une fonction réciproque}
\text{name_question=Calculez la valeur,de sa dérivée en}
\text{name_instruction=Vous devez répondre avec une précision d'au moins 4 chiffres significatifs.}
#endif
