target=angcalc1
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}
\text{x=randitem(A,B,C,D)}
\text{x=\widehat{\x}}
\text{form=arccos(x)}
\text{tform=cos(\x)}

\integer{ch=randint(1..2)}
\real{re=randint(30..70)/100}
\integer{ch=randint(0..2)}
\text{arr=item(\ch+1,\name_precision)}
\text{are=texmath(\re)}

\text{bad=<img src="\imagedir/cos.gif" alt="">,<img src="\imagedir/acos.gif" alt="">}

\statement{
\name_enonce[1] \arr \name_enonce[2] \(\x) \name_enonce[3]:
<div class="wimscenter">
 \(\tform = \are\).
</div>
\name_question?
<div class="wimscenter">\embed{r1,1} \embed{r1,2}.</div>}

\answer{}{2;\bad}{type=click}
