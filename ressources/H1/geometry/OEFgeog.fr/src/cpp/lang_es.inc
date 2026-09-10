\text{correct=La figura es correcta}
\text{penalty=La nota se ha reducido porque el nombre de algún objecto no es correcto.}
\text{Point=Punto}
\text{Cercle=Circulo}

#if defined TARGET_point2 ||defined TARGET_cercle4 ||defined TARGET_cercle5 
\text{aide=Para cambiar el nombre de un objeto, haga clic con el botón derecho del ratón y elija "Renombra".}
#else
\text{aide=}
#endif

#if defined TARGET_point1 
\text{name_instruction=Dibujar un punto A.}
#endif

#if defined TARGET_point2
\text{name_instruction=Dibujar un punto B.}
#endif

#if defined TARGET_ligne1 
\text{name_instruction=Dibujar una recta (AB).}
#endif

#if defined TARGET_ligne2
\text{name_instruction=Dibujar un segmento [AB].}
#endif

#if defined TARGET_ligne3 
\text{name_instruction=Dibujar una semirecta &#91;AB&#41;.}
#endif

#if defined TARGET_cercle1 
\text{name_instruction=Dibujar una circunferencia con centro en un punto \A y que pase por otro punto \B.}
#endif

#if defined TARGET_cercle2 
\text{name_instruction=Dibujar una circunferencia con centro en un punto A y de radio \choix.}
#endif

#if defined TARGET_cercle3 
\text{name_instruction=Dibujar una circunferencia con centro en un punto A y de diámetro \choix.}
#endif

#if defined TARGET_cercle4 
\text{name_instruction=Dibujar tres puntos A, B y P.<br />Dibujar una circunferencia que pase por los tres puntos A, B y P.}
#endif

#if defined TARGET_cercle5 
\text{name_instruction=Dibujar una circunferencia con centro en un punto C y de radio [CA].}
#endif
