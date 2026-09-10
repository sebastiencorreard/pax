target=oefsyminst1 oefsyminst2 oefsyminst3 oefsyminst4 oefsyminst5

#include "author.inc"
\keywords{symmetry}
\precision{1000}
#if defined TARGET_oefsyminst1
# define NUM 1
#endif
#if defined TARGET_oefsyminst2
# define NUM 2
#endif
#if defined TARGET_oefsyminst3
# define NUM 3
#endif
#if defined TARGET_oefsyminst4
# define NUM 4
#endif
#if defined TARGET_oefsyminst5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefsyminst1
\text{fig=draw(400,400
xrange -200,200
yrange -200,200
linewidth 2
rotate 0
segment -300,-300,300,300, black
text black,180,180,medium,(d)
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black
linewidth 1
segment -40,90,-40,-90,black
segment 40,90,40,-90,black
linewidth 2
rotate 180
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black)}

\text{rep1=2}
\text{rep2=1,2}
#endif
#if defined TARGET_oefsyminst2
\text{fig=draw(400,400
xrange -200,200
yrange -200,200
linewidth 2
rotate 0
segment -300,-300,300,300, black
text black,180,180,medium,(d)
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black
linewidth 1
segment -40,80,95,-55,black
segment 40,80,95,25,black
linewidth 2
rotate 270
translation 15,-15
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black)}

\text{rep1=2}
\text{rep2=2}
#endif

#if defined TARGET_oefsyminst3
\text{fig=draw(400,400
xrange -200,200
yrange -200,200
linewidth 2
rotate 0
segment -300,-300,300,300, black
text black,180,180,medium,(d)
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black
linewidth 1
segment -40,80,60,-60,black
segment 40,80,60,20,black
linewidth 2
rotate 270
translation -20,-20
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black)}

\text{rep1=2}
\text{rep2=1}
#endif

#if defined TARGET_oefsyminst4
\text{fig=draw(400,400
xrange -200,200
yrange -200,200
linewidth 2
rotate 0
segment -300,-300,300,300, black
text black,180,180,medium,(d)
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black
linewidth 1
segment -40,80,65,-25,black
segment 40,80,80,40,black
linewidth 2
segment 65,-25,80,40, black
segment 65,-25,140,-40, black
segment 80,40,140,40, black
segment 140,-40,180,0,black
segment 140,40,180,0,black)}

\text{rep1=2}
\text{rep2=2,3}
#endif

#if defined TARGET_oefsyminst5
\text{fig=draw(400,400
xrange -200,200
yrange -200,200
linewidth 2
rotate 0
segment -300,-300,300,300, black
text black,180,180,medium,(d)
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black
linewidth 1
segment -40,80,80,-40,black
segment 40,80,80,40,black
linewidth 2
rotate 270
segment -40,80,40,80, black
segment -40,80,-40,140, black
segment 40,80,40,140, black
segment -40,140,0,180,black
segment 40,140,0,180,black)}

\text{rep1=1}
\text{rep2=4}
#endif

\text{fig=<img src="\fig" alt="">}
\statement{
<div class="wims_columns">
  <div class="medium_size">
  \fig
  </div>
  <div class="medium_size">
  \enonc1
<ul><li>
  \name_construction[1;] : \embed{r1}
</li><li>
\name_construction[2;1]: <i>(\name_construction[2;2])</i>:
<ul><li>\embed{r2,1}</li>
<li>\embed{r2,2}</li>
<li>\embed{r2,3}</li>
<li>\embed{r2,4}</li></ul>
</li></ul>
</div>
</div>}

\answer{}{\rep1;\l1}{type=menu}
\answer{}{\rep2;\l2}{type=checkbox}
