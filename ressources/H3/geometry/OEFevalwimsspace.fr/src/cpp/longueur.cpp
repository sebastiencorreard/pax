target=longueur2 longueur3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{unit=randitem(m,cm,dm)}
\text{unit=\mathrm{\unit}}
\keywords{length, measurement}

#if defined TARGET_longueur2
 \text{c=randint(5..9)}
 \text{enonce=\name_enonce \c \(\unit\)&nbsp;&#63;}
 \text{rep=sqrt(3)*\c}
#endif

#if defined TARGET_longueur3
 \integer{c=randint(3..9)}
 \text{enonce=\name_enonce \c \(\unit\)&nbsp;&#63;}
 \text{rep=sqrt(2)/2*\c}
#endif

\integer{ch=randint(1..3)}
\text{prec=item(\ch,\name_prec)}
\real{rep=rint((\rep)*10^(\ch-1))/10^(\ch-1)}

\statement{
\enonce
<div class="spacer">
<label for="reply1"><b>\name_youranswer</b> :</label> \embed{r1,5} \(\unit\).
</div>
<div class="wims_instruction">\name_inst[1], \name_inst[2] \prec.</div>}

\answer{}{\rep}{type=numexp}
