target=volume1 volume2 volume3 volume4 volume5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\keywords{volume, measurement}
\text{unit=randitem(m,cm,dm)}
\text{unit=\mathrm{\unit}}
#if defined TARGET_volume1
 \text{c=randint(5..9)}
 \text{enonce=\name_enonce[1] \c \(\unit\)&nbsp;&#63;}
 \text{rep=\c^3}
#endif
#if defined TARGET_volume2
 \integer{L=randint(7..11)}
 \integer{l=randint(2..5)}
 \integer{h=randint(3..7)}
 \text{enonce=\name_enonce[1] \L \(\unit\),
  \name_enonce[2] \l \(\unit\) \name_enonce[3] \h \(\unit\)&nbsp;&#63;}
 \text{rep=\L*\l*\h}
#endif
#if defined TARGET_volume3
 \integer{c=randint(3..9)}
 \integer{h=randint(11..19)}
 \text{enonce=\name_enonce[1] \h \(\unit\) \name_enonce[2] \c \(\unit\)&nbsp;&#63;}
 \text{rep=\c^2*\h/3}
#endif
#if defined TARGET_volume4
 \integer{c=randint(3..9)}
 \integer{h=randint(11..19)}
 \text{enonce=\name_enonce[1]
  \h \(\unit\)
  \name_enonce[2]
  \c \(\unit\)&nbsp;&#63;}
 \text{rep=\c^2*sqrt(3)/4*\h}
#endif
#if defined TARGET_volume5
 \integer{r=randint(3..9)}
 \integer{h=randint(11..19)}
 \text{enonce=\name_enonce[1] \h \(\unit\) \name_enonce[2]  \r \(\unit\)&nbsp;&#63;}
 \text{rep=pi*\r^2*\h/3}
#endif
\integer{ch=randint(1..3)}
\text{prec=item(\ch,\name_prec)}
\real{rep=rint((\rep)*10^(\ch-1))/10^(\ch-1)}

\statement{
\enonce
<div class="spacer">
<label for="reply1"><b>\name_youranswer</b> :</label> \embed{r1,5} \(\unit^3\).
</div>
<div class="wims_instruction">\name_inst \prec.</div>}

\answer{}{\rep}{type=numexp}
