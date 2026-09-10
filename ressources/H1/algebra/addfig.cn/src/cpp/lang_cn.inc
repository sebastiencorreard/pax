#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=用已给对象填入图中方框, 使得每个彩色区域边界之和等于 \sum.}
\text{txtsum=}
\text{condpre=}
\text{condpost=&nbsp;区域}
\text{txtpost=之和}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3
\text{txtstatement=用已给对象填入图中方框,
  使得顶部方框里的数等于它的相邻下方两个方框里的数之和.}
#endif

#if defined TARGET_pentagram
\text{lname=直线}
\text{txtstatement=用已给对象填入图中方框,
  使得每条\lname之和等于 \sum.}
\text{txtsum=Sum of the}
\text{condpre=}
\text{condpost=&nbsp;\lname}
\text{txtpost=之和}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
\text{lname=边}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=直线}
# endif

\text{txtstatement=用已给对象填入图中方框, 使得每条\lname之和等于 \sum.}
\text{txtsum=}
\text{condpre=}
\text{condpost=&nbsp;\lname}
\text{txtpost=之和}
#endif
\text{txtbox=Box}
