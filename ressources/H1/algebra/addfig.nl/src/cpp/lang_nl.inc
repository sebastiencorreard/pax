#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=Vul de tekening met de gegeven objecten, zodat de som van
  de elementen die ieder gekleurd gebied begrenzen gelijk is aan \sum.}
\text{txtsum=Som voor het}
\text{condpre=}
\text{condpost=&nbsp;gebied}
\text{txtpost=}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3
\text{txtstatement=Vul de tekening met de gegeven objecten, zodat ieder doosje
  op een gegeven niveau gelijk is aan de som van de twee doosjes direct eronder.}
#endif

#if defined TARGET_pentagram
\text{lname=lijn}
\text{txtstatement=Vul de tekening met de gegeven objecten zodat de som
  op iedere \lname gelijk is aan \sum.}
\text{txtsum=Som op de}
\text{condpre=}
\text{condpost=&nbsp;\lname}
\text{txtpost=}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
 \text{lname=zijde}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=lijn}
# endif
\text{txtstatement=Vul de tekening met de gegeven objecten, zodat
  de som op iedere \lname gelijk is aan \sum.}
\text{txtsum=Som op de}
\text{condpre=}
\text{condpost=&nbsp;\lname}
\text{txtpost=}
#endif
\text{txtbox=Box}
