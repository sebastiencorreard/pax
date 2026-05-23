target=formuleaire1 formuleaire2 formuleaire3 formuleaire4 formuleaire5
#include "author.inc"
\keywords{area, measurement}

#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_formuleaire1
 \text{c=randitem(c,a,b)}
 \text{enonce=\name_enonce \(\c\)&nbsp;}
 \text{rep=\c^2}
#endif
#if defined TARGET_formuleaire2
\ \text{enonce=\name_enonce}
 \text{rep=A*B}
#endif
#if defined TARGET_formuleaire3
 \text{enonce=\name_enonce}
 \text{rep=pi*r^2}
#endif
#if defined TARGET_formuleaire4
 \text{enonce=\name_enonce}
 \text{rep=b*h/2}
#endif
#if defined TARGET_formuleaire5
 \text{A=shuffle(A,B,C,D,E,F)}
 \text{enonce=\name_enonce[1] \(\A[1]\) \name_enonce[2] \(\A[2]\)&nbsp;}
 \text{rep=\A[1]*\A[2]}
#endif

\statement{
\enonce?
<div class="spacer">
<label for="reply1"><b>\name_youranswer</b> :</label> \embed{r1,5}
</div>
<div class="wims_instruction">
\name_inst[1] <span class="tt">pi</span> \name_inst[2] \(\,\pi\).</div>}

\answer{}{\rep}{type=algexp}
