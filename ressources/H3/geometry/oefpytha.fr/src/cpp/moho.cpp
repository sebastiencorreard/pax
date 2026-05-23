target=moho0 moho1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
pour le dessin
\text{n1=6}
\text{m1=4}
\text{l1=10}
\text{h1=1}
\real{H1=2*\m1}
\text{D1=50}
\text{dessin=xrange -12,12
yrange -12,12
hline 0,\m1,black
text black,\n1+2,-\m1-2,small,Manteau
text black,\n1+2,-\m1+4,small,Croute
text black,\n1+2,-\m1+1,small,Moho
text black,\n1+2,\m1+1,small,Surface
text black, -\n1/2,\m1+1,small,Ondes directes
arrows black,\l1,-\n1,\m1-\h1,0,-\m1,0,-\m1,\n1,\m1
arrows black,\l1,-\n1,\m1-\h1,\n1,\m1
text black, -\n1/2,0,small,Ondes réfléchies (PmP)
arrow2 -\n1-2,-\m1,-\n1-2,\m1,\l1,black
text black, -\n1-3,0,small, H
segments black,-\n1,\m1-\h1,-\n1,-\m1
arrow2 -\n1,\m1+1,\n1,\m1+1,\l1,black
fcircles blue,-\n1,\m1,0.2
arrow2 -\n1,\m1-\h1,-\n1,\m1,\l1/2,red
text black, -\n1-0.5,\m1, small, h
text black, \n1,\m1+1, small, S
text black, 0,-\m1, small, B
text black, -\n1-1,\m1-\h1, small, F
text black, 0,-\m1-1, small, D
text black, -\n1,\m1+1, small, E
text black, 0,\m1+2,small, D}

\text{dessin2=\dessin
hline 0,-\m1,black
dvline -\n1,0,black
segments red,-\n1,-\m1-\H1+\h1,0,-\m1
text black,-\n1-1,-\m1-\H1+\h1,small,F'
-\n1-1,\m1-\h1}

\text{v=randint(610..627)}
\real{v=\v/100}
\text{h=randint(1..3)}
\text{H=randint(30..40)} entre 30 et 90
\text{D=randint(45..55)}
\real{FS=sqrt(\h^2+\D^2)}
\real{FBS=sqrt((2*\H-\h)^2 + \D^2)}
\integer{hour=randint(1..22)}
\real{t0=randint(19..22)*60+randint(4..55)}
\real{t1=\t0+\FS/\v} temps de trajet des ondes directes
\real{t2=\t0+\FBS/\v}
\real{dt=\t2-\t1}
\text{t1mn=pari(divrem(\t1,60)~)}
\text{t2mn=pari(divrem(\t2,60)~)}
\real{t1sec=rint(\t1mn[2])}
\real{t2sec=rint(\t2mn[2])}
\real{dt=\t2sec-\t1sec<0 ? \t2sec-\t1sec+60:\t2sec-\t1sec}

\real{H1=1/2*(\h+sqrt((\v*(\dt)+sqrt(\h^2+\D^2))^2-\D^2))}
\text{H2=pari(round(\H1))}

#if defined TARGET_moho0
\text{question=wims(replace internal VVVV by \v in \name_question)}
\text{question=wims(replace internal hhhh by \h in \question)}
\text{question=wims(replace internal DDDD by \D in \question)}
\text{question=wims(replace internal HHHH by \H in \question)}
#endif
#if defined TARGET_moho1
\text{question=wims(replace internal VVVV by \v in \name_question)}
\text{question=wims(replace internal hhhh by \h in \question)}
\text{question=wims(replace internal DDDD by \D in \question)}
#endif
\statement{
\name_enonce
#if defined TARGET_moho1
\name_enonce2
#endif
<div class="wims_columns">
  <div class="medium_size img_col">\draw{600,600}{\dessin2}</div>
  <div class="medium_size text_col">
<ul><li> E: \name_explanation[1;]
</li><li>S: \name_explanation[2;]
</li><li>F: \name_explanation[3;]
</li><li>B: \name_explanation[4;]
</li><li>t1: \name_explanation[5;]
</li><li>t2: \name_explanation[6;]
</li><li>\(\delta t\): \name_explanation[7;]
</li></ul>
<div class="wims_question">
#if defined TARGET_moho0
\question
<p>\name_compute</p>
<ul>
<li><label for="reply1">FS=</label>\embed{r1,4}</li>
<li><label for="reply2">FBS=</label>\embed{r2,4}</li>
<li><label for="reply3">\(\delta t\)=</label>\embed{r3,4}</li>
</ul>
#endif
#if defined TARGET_moho1
\question \(t_1=\hour\) h \(\t1mn[1]\) min \(\t1sec\) s,
\(t_2=\hour\) h \(\t2mn[1]\) min \(\t2sec\) s.
<div><label for="reply1">\name_compute \(H \sim\)</label> \embed{r1,5} km.</div>
<div class="wims_warning">\name_prec</div>
#endif
</div>
</div>
</div>
}
#if defined TARGET_moho0
\answer{}{\FS}{type=numeric}
\answer{}{\FBS}{type=numeric}
\answer{}{\dt}{type=numeric}
#endif
#if defined TARGET_moho1
\answer{}{\H1-1,\H1+1,\H2}{type=range}
#endif

\hint{\name_hint}
