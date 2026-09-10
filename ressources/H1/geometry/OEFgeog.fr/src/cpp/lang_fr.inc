\text{correct=Votre figure est-elle correcte}
\text{penalty=Votre score a été diminué car certains objets n'avaient pas le bon nom.}
\text{Point=Point}
\text{Cercle=Cercle}

#if defined TARGET_point2 ||defined TARGET_cercle4 ||defined TARGET_cercle5
\text{aide=Pour changer le nom d'un objet, cliquer dessus avec le bouton droit et choisir de le "renommer".}
#else
\text{aide=}
#endif

#if defined TARGET_point1 
\text{name_instruction=Placer un point A.}
#endif

#if defined TARGET_point2 
\text{name_instruction=Placer un point B.}
#endif

#if defined TARGET_ligne1 
\text{name_instruction=Tracer une droite (AB).}
#endif

#if defined TARGET_ligne2 
\text{name_instruction=Tracer un segment [AB].}
#endif

#if defined TARGET_ligne3 
\text{name_instruction=Tracer une demi-droite &#91;AB&#41;.}
#endif

#if defined TARGET_cercle1 
\text{name_instruction=Tracer un cercle de centre \A passant par un point \B.}
#endif

#if defined TARGET_cercle2 
\text{name_instruction=Tracer un cercle de centre A et de rayon \choix.}
#endif

#if defined TARGET_cercle3 
\text{name_instruction=Tracer un cercle de centre A et de diamètre \choix.}
#endif

#if defined TARGET_cercle4 
\text{name_instruction=Tracer trois points A, B et P.<br />Tracer un cercle passant par les trois points A, B et P.}
#endif

#if defined TARGET_cercle5 
\text{name_instruction=Tracer un cercle de centre C et de rayon [CA].}
#endif


