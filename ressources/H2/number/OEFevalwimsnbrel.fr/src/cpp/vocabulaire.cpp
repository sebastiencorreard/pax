target=vocabulaire1 vocabulaire2 vocabulaire3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_vocabulaire1
 \text{zone=circle,220,220,8}
#endif
#if defined TARGET_vocabulaire2
 \text{zone=rectangle,0,215,215,225|rectangle,225,215,440,225}
#endif
#if defined TARGET_vocabulaire3
 \text{zone=rectangle,215,0,225,215|rectangle,215,225,225,440}
#endif

\text{dessin=slib(draw/repere 440,440,20,-5,5,-5,5,1,1,black,grey)}
\text{figure=draw(440,440
\dessin
text black,255,225,medium,1
text black,210,225,medium,0
text black,210,175,medium,1)}

 \statement{
\name_enonce[1] \enonce \name_enonce[2]:
<div class="wimscenter">\embed{r1}</div>}
 \answer{}{\figure;\zone}{type=coord}
