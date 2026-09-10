#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=Fill the picture by the given objects,
such that the sum of elements bounding each colored region is
equal to \sum.}
\text{txtsum=Sum for the}
\text{condpre=}
\text{condpost=&nbsp;region}
\text{txtpost=}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3
\text{txtstatement=Fill the picture by the given objects,
such that each box at an upper level equals the sum of the two boxes
immediately below it.}
#endif

#if defined TARGET_pentagram
\text{lname=line}
\text{txtstatement=Fill the picture by the given objects,
such that the sum of each \lname is equal to \sum.}
\text{txtsum=Sum of the}
\text{condpre=}
\text{condpost=&nbsp;\lname}
\text{txtpost=}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
\text{lname=side}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=line}
# endif
\text{txtstatement=Fill the picture will the given objects,
such that the sum of each \lname equals \sum.}
\text{txtsum=Sum of the}
\text{condpre=}
\text{condpost=&nbsp;\lname}
\text{txtpost=}
#endif
\text{txtbox=Box}
