target=equaprod1 equaprod2 equaprod3 equaprod4 equaprod5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{v=wims(values v for v=2 to 9)}
\text{v=shuffle(\v)}
\text{x=randitem(x,y,z,t,u,v)}

#if defined TARGET_equaprod1
\text{v=\v[1]*\v[4]-\v[2]*\v[3]=0?pari(\v[1]+1),\v[2],\v[3],\v[4]}
\text{enonce=(\v[1]*\x+\v[2])(\v[3]*\x+\v[4])=0}
\text{rep=-\v[2]/\v[1],-\v[4]/\v[3]}
#endif
#if defined TARGET_equaprod2
 \text{enonce=(\v[1]*\x-\v[2])(\v[3]*\x+\v[4])=0}
 \text{rep=\v[2]/\v[1],-\v[4]/\v[3]}
#endif
#if defined TARGET_equaprod3
 \text{enonce=randitem(\x(\v[3]*\x+\v[4])=0,(\v[3]*\x+\v[4])\x=0)}
 \text{rep=0,-\v[4]/\v[3]}
#endif
#if defined TARGET_equaprod4
 \text{enonce=(\v[1]*\x-\v[2])(\v[3]*\x+\v[4])+(\v[1]*\x-\v[2])(\v[5]*\x+\v[6])=0}
 \text{rep=\v[2]/\v[1],pari(-(\v[4]+\v[6])/(\v[3]+\v[5]))}
#endif
#if defined TARGET_equaprod5
 \text{v=\v[1]*\v[5]*\v[6]-\v[2]*\v[3]*\v[4]=0?pari(\v[1]+1),\v[2],\v[3],\v[4],\v[5],\v[6]}
 \text{enonce=(\frac{\v[1]}{\v[2]}\x-\v[3])(\v[4]\x-\frac{\v[5]}{\v[6]})=0}
 \text{rep=pari(\v[2]*\v[3]/\v[1]),pari(\v[5]/(\v[6]*\v[4]))}
#endif
\statement{\name_enonce:
<div class="wimscenter">\(\enonce\).</div>
<b>\name_youranswer</b>:
  <label for="reply1">\name_reponse</label> \embed{r1,10}.
<div class="wims_instruction">
 \name_inst
  </div>}

\answer{\name_sol}{\rep}{type=fset}
