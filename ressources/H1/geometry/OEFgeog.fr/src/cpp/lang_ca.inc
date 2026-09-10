\text{correct=La figura és correcta}
\text{penalty=La nota s'ha reduït perquè el nom d'algun objecte no és correcte.}
\text{Point=Punt}
\text{Cercle=Cercle}

#if defined TARGET_point2 ||defined TARGET_cercle4 ||defined TARGET_cercle5 
\text{aide=Per canviar el nom d'un objecte, feu-hi clic amb el botó dret del ratolí i trieu "Canvia de nom".}
#else
\text{aide=}
#endif

#if defined TARGET_point1 
\text{name_instruction=Dibuixar un punt A.}
#endif

#if defined TARGET_point2 
\text{name_instruction=Dibuixar un punt B.}
#endif

#if defined TARGET_ligne1 
\text{name_instruction=Dibuixar una recta (AB).}
#endif

#if defined TARGET_ligne2
\text{name_instruction=Dibuixar un segment [AB].}
#endif

#if defined TARGET_ligne3 
\text{name_instruction=Dibuixar una semirecta &#91;AB&#41;.}
#endif

#if defined TARGET_cercle1 
\text{name_instruction=Dibuixar una circumferència amb centre en un punt \A i que passi per un altre punt \B.}
#endif

#if defined TARGET_cercle2 
\text{name_instruction=Dibuixar una circumferència amb centre en un punt A i de radi \choix.}
#endif

#if defined TARGET_cercle3 
\text{name_instruction=Dibuixar una circumferència amb centre en un punt A i de diàmetre \choix.}
#endif

#if defined TARGET_cercle4 
\text{name_instruction=Dibuixar tres punts A, B i P.<br />Dibuixar una circumferència  que passi pels tres punts A, B i P.}
#endif

#if defined TARGET_cercle5 
\text{name_instruction=Dibuixar una circumferència amb centre en un punt C i de radi [CA].}
#endif
