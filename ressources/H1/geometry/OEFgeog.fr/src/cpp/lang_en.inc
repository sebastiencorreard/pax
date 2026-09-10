\text{correct=Is your figure correct}
\text{penalty=Your score has been decreased because you did not give the good names to some objects.}
\text{Point=Point}
\text{Cercle=Circle}
 
#if defined TARGET_point2 ||defined TARGET_cercle4 ||defined TARGET_cercle5 
\text{aide=To change the name of an object, click on it with the right mouse button and choose "rename".}
#else
\text{aide=}
#endif

#if defined TARGET_point1 
\text{name_instruction=Draw a point A.}
#endif

#if defined TARGET_point2 
\text{name_instruction=Draw a point B.}
#endif

#if defined TARGET_ligne1 
\text{name_instruction=Draw a line (AB).}
#endif

#if defined TARGET_ligne2 
\text{name_instruction=Draw a segment [AB].}
#endif

#if defined TARGET_ligne3 
\text{name_instruction=Draw a semiline &#91;AB&#41;.}
#endif

#if defined TARGET_cercle1 
\text{name_instruction=Draw a circle with center \A going through a point \B.}
#endif

#if defined TARGET_cercle2 
\text{name_instruction=Draw a circle with center A and radius \choix}
#endif

#if defined TARGET_cercle3 
\text{name_instruction=Draw a circle with center A and diameter \choix}
#endif

#if defined TARGET_cercle4 
\text{name_instruction=Draw three points A, B and P.<br />Draw a circle going through the three points A, B and P.}
#endif

#if defined TARGET_cercle5 
\text{name_instruction=Draw a circle of center C and of ray [CA].}
#endif
