#if defined TARGET_twosqr || defined TARGET_threesqr || defined TARGET_foursqr || defined TARGET_tie || defined TARGET_cube || defined TARGET_house || defined TARGET_diag || defined TARGET_pizza3 || defined TARGET_pizza4
\text{txtstatement=Prazne kvadratke na sliki dopolnite s ¹tevili v modrih kvadratkih, tako
  da bo vsota vseh elementov na meji posameznega obarvanega obmoèja
  enaka \sum.}
\text{txtsum=Vsota obmoèja}
\text{condpre=}
\text{condpost=&nbsp;barve}
\text{txtpost=}
#endif

#if defined TARGET_pyramid1 || defined TARGET_pyramid1b || defined TARGET_pyramid1c || defined TARGET_pyramid1d || defined TARGET_pyramid2 || defined TARGET_pyramid2b || defined TARGET_pyramid3
\text{txtstatement=Dopolnite sliko s pripravljenimi ¹tevili,
  tako da bo vsako ¹tevilo zgoraj enako vsoti dveh ¹tevil pod njim.}
#endif

#if defined TARGET_pentagram
\text{lname=stranici}
\text{txtstatement=Pripravljena ¹tevila razporedite na ustrezna mesta v sliki,
  tako da bo vsota ¹tevil na vsaki \lname enaka \sum.}
\text{txtsum=Vsota na}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
#endif

#if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_cross || defined TARGET_stool || defined TARGET_IXI || defined TARGET_grill || defined TARGET_H || defined TARGET_M || defined TARGET_V || defined TARGET_W || defined TARGET_asterisk || defined TARGET_pentagon
# if defined TARGET_triangle || defined TARGET_bigsquare || defined TARGET_pentagon
\text{lname=stranici}
\text{txtsum=Vsota ob}
# endif
# if defined TARGET_cross || defined TARGET_V || defined TARGET_stool || defined TARGET_IXI || defined TARGET_H || defined TARGET_M || defined TARGET_W || defined TARGET_asterisk || defined TARGET_grill
\text{lname=premici}
\text{txtsum=Vsota ob}
# endif
\text{txtstatement=Dopolnite sliko z ustreznimi ¹tevili tako,
  da bo vsota ¹tevil ob vsaki \lname enaka \sum.}
\text{condpre=\lname&nbsp;}
\text{condpost=}
\text{txtpost=}
#endif
\text{txtbox=Box}
