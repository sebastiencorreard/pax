#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=Trascina nella figura i numeri in basso,
in modo che la somma dei numeri di ogni regione colorata sia
uguale a \sum.}
\text{txtsum=Somma della}
\text{condpre=regione&nbsp;}
\text{condpost=}
\text{txtpost=}
\text{colorname=\colornamef}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3

# if CONDITIONS > 1
\text{txtstatement=Trascina nella figura i numeri in basso,
in modo che il numero inserito in ogni riquadro in alto sia uguale alla
somma dei due numeri che gli stanno sotto.}
# else
\text{txtstatement=Trascina nella figura i numeri in basso,
in modo che il numero inserito nel riquadro in alto sia uguale alla
somma dei due numeri che gli stanno sotto.}
# endif
# if CONDITIONS > 5
\text{txtstatement=Trascina nella figura i numeri in basso,
in modo che il numero inserito in ogni riquadro sia uguale alla
somma dei due numeri che gli stanno sotto.}
# endif
#endif

#if defined TARGET_pentagram
\text{lname=linea}
\text{txtstatement=Trascina nella figura i numeri in basso,
in modo che la somma di ogni \lname colorata sia uguale a \sum.}
\text{txtsum=Somma della}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
\text{colorname=\colornamef}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
\text{lname=lato}
\text{ldesc=colorato}
\text{txtsum=Somma del}
\text{colorname=\colornamem}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=linea}
\text{ldesc=colorata}
\text{txtsum=Somma della}
\text{colorname=\colornamef}
# endif
\text{txtstatement=Trascina nella figura i numeri in basso,
in modo che la somma di ogni \lname \ldesc sia uguale a \sum.}

\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
#endif
\text{txtbox=Regione}
