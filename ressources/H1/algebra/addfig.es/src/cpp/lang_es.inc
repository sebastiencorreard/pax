#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=Rellenar la imagen con los objetos dados, de manera que la suma
  de los elementos que limitan cada región coloreada sea igual a \sum.}
\text{txtsum=Suma para la}
\text{condpre=región&nbsp;}
\text{condpost=}
\text{colorname=\colornamef}
\text{txtpost=}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3
\text{txtstatement=Rellenar la imagen con los objetos dados,
  de manera que cada caja de un nivel superior sea igual a la suma
  de las dos cajas inmediatamente inferiores.}
#endif

#if defined TARGET_pentagram
\text{lname=línea}
\text{txtstatement=Rellenar la imagen con los objetos dados,
  de manera que la suma de cada \lname sea igual a \sum.}
\text{txtsum=Suma de la}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
\text{colorname=\colornamef}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
\text{lname=lado}
\text{txtsum=Suma del}
\text{colorname=\colornamem}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=linea}
\text{txtsum=Suma de la}
\text{colorname=\colornamef}
# endif
\text{txtstatement=Rellenar la imagen con los objetos dados,
  de manera que la suma de los elementos que limitan cada región coloreada
  sea igual a \sum.}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
#endif
\text{txtbox=Caja}
