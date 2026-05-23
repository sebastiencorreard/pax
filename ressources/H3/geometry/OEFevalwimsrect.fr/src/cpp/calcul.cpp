target=calcul2 calcul3 calcul4 calcul5
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{ft=cos}
\text{aft=\cos}

#if defined TARGET_calcul2
 \text{form=\ft(x)}
 \text{tform=texmath(\form)}
#endif
#if defined TARGET_calcul3
 \text{v=randint(2..9)}
 \text{form=\v/\ft(x)}
 \text{tform=\frac{\v}{\aft(x)}}
#endif
#if defined TARGET_calcul4
 \text{v=wims(values v for v=2 to 9)}
 \text{v=shuffle(\v)}
 \text{form=\v[1]*\ft(x)/\v[2]}
 \text{tform=\frac{\v[1]\aft(x)}{\v[2]}}
#endif
#if defined TARGET_calcul5
 \text{v=randint(2..9)}
 \text{form=\ft(x)*\v}
 \text{tform=\aft(x)\times\v}
#endif

\text{angle=randint(5..85)}
\text{affform=wims(replace internal x by \angle^\circ in \tform)}
\text{A=randitem(A,B,C,D,E,F,G,H)}
\integer{ch=randint(1..3)}
\text{arr=item(\ch,\name_precision)}
\real{rep=evalue(\form,x=\angle*pi/180)}
\real{rep=rint(\rep*10^\ch)/10^\ch}

\statement{
\name_question[1] \arr \name_question[2] :
<div class="wimscenter">
 <label for="reply1">\(\A = \affform = \)</label>\embed{r1,6}
</div>}

\answer{\A}{\rep}{type=numexp}
