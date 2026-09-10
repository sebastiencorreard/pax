#if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat2 || defined TARGET_oefanglenat3 || defined TARGET_oefanglenat4 || defined TARGET_oefanglenat5
\text{nat=aigu,droit,obtus,plat}

# if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat2 || defined TARGET_oefanglenat5
\text{name_enonce=L'angle est }
# endif
# if defined TARGET_oefanglenat3
\text{name_enonce=L'angle qui mesure,est un angle }
# endif
# if defined TARGET_oefanglenat4
\text{name_enonce=Donner la mesure d'un angle}
# endif
#endif
#if defined TARGET_oefcodeangl1
\text{name_enonce=Cliquer sur les deux angles qui ont la même mesure.}
#endif
#if defined TARGET_oefcodeangl2
\text{name_enonce=Cliquer sur tous les angles qui ont la même mesure&nbsp;,
  Cliquer sur les angles qui ont la même mesure&nbsp;}
#endif
#if defined TARGET_oefcodeangl3
\text{name_enonce=Mettre en relation les angles qui ont la même mesure&nbsp;}
#endif
#if defined TARGET_oefcodeangl4
\text{enonc=Les triangles DFC et EBF ont des côtés avec les mêmes longueurs,
  Les triangles DFC et EBF ont des angles avec les mêmes mesures}
\text{reps=oui,non,peut-être}
#endif
#if defined TARGET_oefcodeangl5
\text{name_enonce=Nous avons les mesures suivantes&nbsp;,
  Donner la mesure de l'angle}
#endif
#if defined TARGET_oefcompangl1 || defined TARGET_oefcompangl2 || defined TARGET_oefcompangl3 || defined TARGET_oefcompangl4 || defined TARGET_oefcompangl5
\text{name_enonce=Comparer la mesure des angles&nbsp;}
#endif
#if defined TARGET_oefconstangl1 || defined TARGET_oefconstangl2 || defined TARGET_oefconstangl3
\text{rep=Le rapporteur est bien placé,Le rapporteur n'est pas bien placé}
\text{name_enonce=Nous voulons construire un angle \(\widehat{xAy}) de 46°.
  Nous avons tracé la demi-droite &#91;Ax&#41;.}
\text{name_enonce2=Comment ensuite placer le rapporteur ? }
#endif
#if defined TARGET_oefestangl3 || defined TARGET_oefestangl4 || defined TARGET_oefestangl5
\text{name_enonce=Donner la mesure de l'angle}
#endif
#if defined TARGET_oefestangl1 || defined TARGET_oefestangl2
\text{name_enonce=La mesure de l'angle est&nbsp;}
#endif
#if defined TARGET_oefmesangl5
\text{name_question=le sommet opposé au côté, est le sommet,
  le côté opposé au sommet,est le côté }
\matrix{name_enonce=Construire le triangle
  avec les bonnes dimensions sur le brouillon et donner les mesures entières des angles suivants du triangle}
#endif


#if defined TARGET_oefreprodangle5
\text{rep=Je trace une demi-droite avec la règle.,
Je trace un arc de cercle sur l'angle initial qui a pour centre le sommet de l'angle.,
Sur la reproduction &#44; je trace un arc de cercle qui a pour centre l'origine de la demi-droite.,
Avec le compas &#44; je mesure la longueur de l'arc de cercle contenu dans l'angle initial.,
Je reporte cette mesure sur l'arc de cercle tracé sur la demi-droite.,
Je trace la deuxième demi-droite qui passe par l'intersection des deux arcs de cercle pour représenter le deuxième angle.}
#endif
#if defined TARGET_oefreprodangle1
\text{list=Oui,Non,Je ne sais pas}
\text{name_enonce=Pour reproduire un angle&#44; je peux utiliser le compas&nbsp;}
#endif
#if defined TARGET_oefreprodangle2
\text{reps=Oui,Non,Je ne sais pas}
\text{name_enonce=Les deux angles, ont-ils la même mesure&nbsp;}
\text{name_hint=Pour répondre à la question, tu peux t'aider des intersections des arcs de cercle
  avec les côtés des angles.}
#endif
#if defined TARGET_oefreprodangle3 || defined TARGET_oefreprodangle4 || defined TARGET_oefreprodangle5
\text{name_step=Étape}
\text{name_head=Reproduction d'un angle sans rapporteur}
# if defined TARGET_oefreprodangle3
\text{name_enonce=Voici les différentes étapes de la reproduction d'un angle.
  Mettre les images dans le bon ordre des étapes de construction.}
# endif
# if defined TARGET_oefreprodangle4
\text{rep=Je trace une demi-droite avec la règle.,
  Je trace un arc de cercle sur l'angle initial qui a pour centre le sommet de l'angle.,
  Sur la reproduction &#44; je trace un arc de cercle qui a pour centre l'origine de la demi-droite.,
  Avec le compas &#44; je mesure la longueur de l'arc de cercle contenu dans l'angle initial.,
  Je reporte cette mesure sur l'arc de cercle tracé sur la demi-droite.,
  Je trace la deuxième demi-droite qui passe par l'intersection des deux arcs de cercle pour représenter le deuxième angle.}
\text{name_enonce=Voici les différentes étapes de la reproduction d'un angle.
  Placer le texte d'explication correct sous chaque dessin.}
# endif
# if defined TARGET_oefreprodangle4
\text{name_enonce=Choisir le texte expliquant les étapes correspondant à la construction
  présentée dans l'exercice précédent.}
# endif
#endif

#if defined TARGET_oefvocangle1
\text{name_enonce=Le nom de l'angle est}
#endif
#if defined TARGET_oefvocangle2
\text{name_enonce=Le nom d'un côté de l'angle est}
#endif
#if defined TARGET_oefvocangle3
\text{name_enonce=Le nom du sommet de l'angle est}
#endif
#if defined TARGET_oefvocangle4
\text{name_enonce=L'angle,a pour sommet , et pour côtés}
#endif
#if defined TARGET_oefvocangle5
\text{name_enonce=L',a pour, et pour}
#endif
#if defined TARGET_oefmesangl1 || defined TARGET_oefmesangl2 || defined TARGET_oefmesangl3 || defined TARGET_oefmesangl4
\text{name_enonce=Donner la mesure de l'angle}
#endif
#if defined TARGET_oefconstangl5
\matrix{name_enonce=Construire un angle, de,sur une feuille de brouillon.
  Placer le point B sur la demi-droite ,tel que
  Ensuite, placer le point C sur la demi-droite,tel que
  Donner la mesure du segment
}
#endif
#if defined TARGET_oefconstangl4
\matrix{name_enonce=doit construire un angle,de
  Elle a tracé la demi-droite
  Ensuite, elle a placé un trait en utilisant les graduations du rapporteur pour tracer la deuxième demi-droite.
  Le trait est-il bien placé}
\matrix{name_enonce2=Si , continue sa construction
  elle obtiendra un angle qui aura pour mesure: }
\text{name_ouinon=oui,non}
#endif
#if defined TARGET_oefcompangl1 || defined TARGET_oefcompangl2 || defined TARGET_oefcompangl3 || defined TARGET_oefcompangl4 || defined TARGET_oefcompangl5
\text{name_enonce=Comparer la mesure des angles&nbsp;}
#endif
