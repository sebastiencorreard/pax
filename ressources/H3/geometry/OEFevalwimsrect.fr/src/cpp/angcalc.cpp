target=angcalc2 angcalc3 angcalc4 angcalc5
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

#if defined TARGET_angcalc2
 \integer{ch=randint(1..2)}
 \real{re=randint(30..70)/100}
#endif
#if defined TARGET_angcalc3
 \integer{ch=randint(1..2)}
 \text{re=randint(2..9)}
 \text{re=\re/randint(\re+1...\re+9)}
#endif
#if defined TARGET_angcalc4
 \text{re=simplify(randint(2..15)/randint(17..45))}
#endif
#if defined TARGET_angcalc5
 \integer{ch=randint(1..2)}
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \text{re=randint(2..7)/(\v[1]+\v[2])}
#endif

\text{angle=wims(replace internal x by \re in \form)}
\integer{ch=randint(0..2)}
\text{arr=item(\ch+1,\name_precision)}
\real{rep=\angle/pi*180}
\real{rep=rint(\rep*10^\ch)/10^\ch}
\text{are=texmath(\re)}

\statement{
\name_question[1] \arr \name_question[2] \(\x\) \name_question[3]:
<div class="wimscenter">
 \(\tform = \are \).
</div>
<b>\name_answer</b>:
 <label for="reply1">\(\x \simeq \)</label> \embed{r1,5} °.}

\answer{\(\x\)}{\rep}{type=numexp}
