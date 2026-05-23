target=formulevolume1 formulevolume2 formulevolume3 formulevolume4 formulevolume5
\keywords{volume, measurement}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_formulevolume1
 \text{c=randitem(c,a,b)}
 \text{enonce=\name_enonce \(\c\)&nbsp;}
 \text{rep=\c^3}
#endif
#if defined TARGET_formulevolume2
 \text{A=shuffle(A,B,C,D,E,F)}
 \text{enonce=\name_enonce[1] \(\A[1]\), \name_enonce[2] \(\A[2]\) \name_enonce[3]
  \(\A[3]\)&nbsp;}
 \text{rep=\A[1]*\A[2]*\A[3]}
#endif
#if defined TARGET_formulevolume3
 \text{base=randitem(\name_base)}
\text{enonce=\name_enonce[1] \base \name_enonce[2]}
 \text{rep=B*h/3}
#endif
#if defined TARGET_formulevolume4
 \text{enonce=\name_enonce}
 \text{rep=pi*r^2*h/3}
#endif
#if defined TARGET_formulevolume5
\text{base=randitem(\name_base)}
\text{enonce=\name_enonce[1] \base \name_enonce[2]}
 \text{rep=B*h}
#endif

\statement{\enonce?
<div class="spacer">
<label for="reply1"><b>\name_youranswer</b> :</label> \embed{r1,7}.</div>
<div class="wims_instruction">\name_inst[1] <span class="tt">pi</span> \name_inst[2] \(\,\pi\).</div>}

\answer{}{\rep}{type=algexp}
