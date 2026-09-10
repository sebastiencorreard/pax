\text{name_yesno=oui,non}
\text{name_none=aucune}
\text{name_hint=Pour s'aider, il est possible de tracer un segment.
  Il n'en sera pas tenu compte dans la notation.}
#if defined TARGET_trajet1
\text{name_enonce=Une caisse noire est munie de deux trous, une source lumineuse
  ponctuelle S est placée devant l'un des trous et l'observateur B
  regarde par l'autre trou. Dans la caisse, on a placé un objet blanc A
  et un cache opaque.}
\text{name_question=L'observateur B voit-il l'objet A?}
#endif
#if defined TARGET_ecran1
\text{name_enonce=L'observateur (B) peut-il voir la source lumineuse
  (point S) malgré l'écran opaque E}
#endif
#if defined TARGET_ecran2
\text{name_enonce=Quels sont les observateurs qui voient la source lumineuse
  (point S) malgré l'écran opaque E troué}
#endif
#if defined TARGET_ecran3
\text{name_enonce=Quelles sources lumineuses (points S1,S2,...) l'observateur
  (B) voit-il malgré l'écran opaque E troué}
#endif
#if defined TARGET_ecran4
\text{name_enonce=Par quelles sources chaque observateur est-il éclairé&nbsp;}
\text{name_obs=Observateur}
#endif
#if defined TARGET_ombre1 || defined TARGET_ombre2
\text{name_enonce=On éclaire une sphère avec une source lumineuse ponctuelle}
# if defined TARGET_ombre1
\text{name_question=Quelle est la source lumineuse qui permet d'obtenir
  l'ombre portée à l'endroit repéré sur l'écran&nbsp;}
\text{name_answer=Source lumineuse}
# endif
# if defined TARGET_ombre2
\text{name_choix=l'ombre portée,le cône d'ombre,les rayons limites,l'ombre propre}
\text{name_question=Tracer}
\matrix{name_feed=L'ombre portée est la région non éclairée sur l'écran.
Le cône d'ombre est l'ombre de forme conique portée par un objet sphérique éclairé par une source de lumière.
Les rayons limites xxx
L'ombre propre est la région du corps non éclairée.}
# endif
#endif
#if defined TARGET_tabouret
\text{rep1=ombre portée}
\text{name_enonce=On considère un tabouret de hauteur
  HHHH cm avec une assise circulaire de XXXX cm de diamètre.
  Sur la normale passant par le centre de l'assise,
  se trouve une source lumineuse ponctuelle placée au plafond soit
  à YYYY m du sol. Sous le tabouret se forme une zone sombre.
}
\matrix{name_question=Cette zone s'appelle
Son diamètre est}
\text{name_enonce2=La zone est un disque sombre (forme circulaire).}
text{name_reponse=Le diamètre de l'ombre portée est}
#endif
#if defined TARGET_ordphase1 || defined TARGET_ordphase2 || defined TARGET_ordphase1P || defined TARGET_ordphase1T
\text{name_enonce=Mettre dans l'ordre les phases de la Lune après la phase indiquée
  si l'on est dans l'hémisphère}
#endif
#if defined TARGET_ordphase1P || defined TARGET_date1P || defined TARGET_date2P ||defined TARGET_date1 || defined TARGET_date2 || defined TARGET_ordphase1 || defined TARGET_ordphase2 || defined TARGET_poslune
\text{name_nordsouth=Nord, Sud}
\text{name_where=On est dans l'hémisphère}
#endif
#if defined TARGET_date1 || defined TARGET_date2 || defined TARGET_date1P || defined TARGET_date2P
\matrix{name_enonce=Aujourd'hui, on voit la Lune comme cela&nbsp;
  Comment la verra-t-on dans, jours&nbsp;}
#endif
#if defined TARGET_qcm1
\text{name_choix=sources primaires de lumière,objets diffusants}
\text{name_question=Parmi les objets suivants, quels sont ceux qui sont des}
\matrix{data=le Soleil,1
l'écran de télévision en fonctionnement,1
le filament d'une lampe allumée,1
la flamme de la bougie,1
une étoile,1
un laser,1
une ampoule allumée,1
un ver luisant,1
la lave d'un volcan,1
la lune,2
la terre,2
les arbres,2
le mur de la classe,2
les planètes,2
un écran de cinéma pendant la projection,2
les planètes du système solaire,2
les yeux d'un chat la nuit,2
les bandes réfléchissantes sur les vêtements,2
}

\text{name_feed1=Un objet diffusant reçoit de la lumière et la rediffuse
dans toutes les directions.}
\text{name_feed2=Une source primaire produit sa propre lumière.}
#endif
#if defined TARGET_qcm2
\text{name_choix=Une source primaire de lumière,Un objet diffusant}
\text{list=produit sa propre lumière,reçoit de la lumière,et,la rediffuse
  dans toutes les directions}
\text{name_question=Former la définition&nbsp;}
#endif
#if defined TARGET_poslune
\text{choix_temps=toute la nuit,le matin,l'après-midi,le soir,
  en début de nuit,en fin de nuit,en deuxième moitié de nuit&#44; en fin de nuit et le matin,
  l'après-midi&#44; le soir et en début de nuit}
\text{choix_direction=du sud, de l'est,du nord,de l'ouest,
  du sud et de l'est,du sud et de l'ouest,du nord et de l'est, du nord et de l'ouest}
\matrix{name_lune=La pleine lune,la pleine lune,En fin de nuit, En début de nuit
Le premier croissant de lune, Le premier quartier de lune, La phase gibbeuse croissante de lune
La phase gibbeuse décroissante de lune, Le dernier quartier de lune, Le dernier croissant de lune}
\text{name_phrase=se voit,en direction}
#endif
#if defined TARGET_eclipse1 || defined TARGET_eclipse2
\text{name_choix1=une éclipse de soleil, une éclipse de Lune,ni l'un ni l'autre}
\text{name_question1=Ce schéma représente}
\text{name_question2=Elle est}
\text{name_question3=Dans la zone verte de la Terre, le Soleil est}
\matrix{name_choix2=entièrement masqué,partiellement masqué,vu comme un anneau autour de la Lune
  totale,partielle,pénombrale}
\text{name_warning=Le dessin n'est pas à l'échelle et la situation
 a été simplifiée.}
#endif
