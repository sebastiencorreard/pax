target=airelaterale1 airelaterale2 airelaterale3 airelaterale4 airelaterale5

#include "author.inc"
\keywords{area, measurement}

\text{unit=randitem(m,cm,dm)}
\text{unit=\mathrm{\unit}}
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_airelaterale1
 \text{c=randint(5..9)}
 \text{enonce=\name_enonce \c \(\unit\)&nbsp;}
 \text{rep=6*\c^2}
#endif
#if defined TARGET_airelaterale2
 \integer{L=randint(7..11)}
 \integer{l=randint(2..5)}
 \integer{h=randint(3..7)}
 \text{enonce=\name_enonce[1] \L \(\unit\), \name_enonce[2] \l \(\unit\) \name_enonce[3]
  \h \(\unit\)&nbsp;}
 \text{rep=2*(\L*\l+\L*\h+\l*\h)}
#endif
#if defined TARGET_airelaterale3
 \integer{c=randint(3..9)}
 \text{enonce=\name_enonce \c \(\unit\)&nbsp;}
 \text{rep=sqrt(3)*\c^2}
#endif
#if defined TARGET_airelaterale4
 \integer{c=randint(3..9)}
 \text{enonce=\name_enonce \c \(\unit\)&nbsp;}
 \text{rep=\c^2+sqrt(3)*\c^2}
#endif
#if defined TARGET_airelaterale5
 \integer{c=randint(3..9)}
 \integer{h=randint(11..19)}
 \text{enonce=\name_enonce[1] \c \(\unit\) \name_enonce[2] \h \(\unit\)&nbsp;}
 \text{rep=sqrt(3)*\c^2/2+3*\h*\c}
#endif

\integer{ch=randint(1..3)}
\text{prec=item(\ch,\name_prec)}
\real{rep=rint((\rep)*10^(\ch-1))/10^(\ch-1)}

\statement{
\enonce?
<div class="spacer">
<label for="reply1"><b>\name_youranswer</b></label> : \embed{r1,5} \(\unit^2).
</div>
<div class="wims_instruction">\name_inst[1], \name_inst[2] \prec.</div>}

\answer{}{\rep}{type=numexp}
