#if defined TARGET_Trianglerectan
\text{name_enonce=misura,e,Quanto misura,in}
#endif
#if defined TARGET_rugby
\text{name_data=A che distanza dal centro dei pali si trova la palla,
  A che distanza dal centro del campo si trova la palla,
  L'allenatore vuole dare consigli al giocatore. Qual è la distanza tra il giocatore e l'allenatore}
\text{name_enonce=La meta è stata assegnata a, metri dal bordo del campo.,
  Il giocatore decide di posizionarsi a una distanza di, metri dalla linea di metà.}
\text{name_answer=La distanza approssimativa in metri}
\text{name_cond1=La risposta data è approssimata a 0.5 metri}
\text{name_cond2=La risposta data è corretta e nel margine di approssimazione richiesto}
\text{name_cond3=La risposta data è effettivamente un'approssimazione come richiesto}
\text{name_feed=La risposta corretta è,metri.}
\text{name_instruction=Dare la risposta (in metri) approssimando all'intero più vicino.}
#endif
#if defined TARGET_Puits
\text{name_enonce=L'altezzza di,è , il pozzo ha una profondità di ,e un diametro di}
\text{name_question=A quale distanza da, si trova il pallone, in \(cm\)
  arrotondando all'unità}
\text{name_answer=Distanza}
#endif
#if defined TARGET_Mdiane
\text{name_enonce= è la mediana che congiunge il punto \(A\) al punto medio dell'ipotenusa \(I\). Sapendo che ,  misura, e, quanto misura, in}
\text{name_answer=Lunghezza di}
#endif
#if defined TARGET_Cerfvolant
\text{name_enonce=A quale altezza vola l'aquilone,in}
\text{name_answer=Altezza}
\text{name_sol1=L'aquilone, la sua altezza e la linea orizzontale dalle mani del personaggio formano un triangolo rettangolo, l'ipotenusa è il filo dell'aquilone.}
\text{name_sol2=Si può allora utilizzare il teorema di Pitagora per calcolare l'altezza alla  quale si trova l'aquilone.,
  Si può schematizzare con un disegno}
\text{name_sol3=Il triangolo ABC è rettangolo in B,
  è la lunghezza dell'aquilone e del filo dell'aquilone,
  è la distanza tra le mani del personaggio e il punto su cui si trova l'aquilone,
  è l'altezza dell'aquilone che si vuole determinare.}
\text{name_sol4=Per il teorema di Pitagora si ha la seguente eguaglianza,
  Da cui, Quindi,Si può concludere che l'aquilone è situato a una altezza di}
#endif
#if defined TARGET_Arbreabattu
\text{name_enonce=Un albero è stato abbattuto da un fulmine. Quale era la sua altezza,in}
\text{name_answer=L'altezza dell'albero}
\text{name_sol1=Il ceppo, il tronco e il terreno formano un triangolo rettangolo, la cui
  ipotenusa è il pezzo di tronco tagliato.}
\text{name_sol2=Utilizziamo il teorema di Pitagora.,Si ha,
  l'altezza del pezzo di tronco tagliato,
  l'altezza del ceppo,
  la distanza sul terreno}
\text{name_sol3=Si ha allora la formula,
  Da cui si ricava che l'altezza dell'albero era,}
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
