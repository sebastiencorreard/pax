target=equcondbc21 equcondbc22 equcondbc23 equcondbc24
#include "author.inc"
#include "lang_titles.inc"

\text{d=randitem(d,p,D)}
#include "lang.inc"
\text{l=wims(values v,-v for v=1 to 10)}
\text{l=shuffle(\l)}
\text{equation=randitem(texmath(\l[1]*x + \l[2]*y)=\l[3],texmath(\l[2]*y + \l[1]*x )=\l[3]) }

#if defined TARGET_equcondbc21
 \integer{c=randint(1,-1)*randint(1..5)}
 \integer{c=\l[2]*\c=\l[3]?\c+1}
 \integer{f=0}
 \integer{e=\c}
#endif
#if defined TARGET_equcondbc22
 \integer{c=\l[4]}
 \integer{e=\l[5]}
 \integer{e=\l[4]*\l[1]+\l[2]*\l[5]=\l[3]?\e+1}
#endif
#if defined TARGET_equcondbc23
 \integer{c=\l[4]}
 \integer{f=0}
 \integer{e=\l[4]}
#endif
#if defined TARGET_equcondbc24
 \integer{f=\l[5]}
 \integer{e=\l[4]}
#endif
\statement{
\name_introdroite:
<div class="wimscenter"> \(\equation\).</div>
\question (\f,\e).
<p><b>\name_answer:</b></p>
  <label for="reply1">\name_equation</label> : \embed{r1,7}
  <label for="reply2">=</label> \embed{r2,4}.
<div class="wims_instruction">
  \name_inst \(a x+b y=c\).
</div>}

\answer{}{\eq1}{type=auto}
\answer{}{\eq2}{type=auto}

\text{t1=wims(rawmath \eq1)}
\integer{t2=wims(rawmath \eq2)}
#if defined TARGET_equcondbc21
 \real{rep=simplify((\t1)/(\l[1]*x + \l[2]*y))}
 \condition{\name_condition}{NaN notin \rep\t2 and \rep*\l[2]*\c=\t2}
#endif
#if defined TARGET_equcondbc22
 \real{rep=simplify((\t1)/(\l[1]*x + \l[2]*y))}
 \condition{\name_condition}{NaN notin \rep\t2 and \rep*(\l[1]*\c+\l[2]*\e)=\t2}
#endif
#if defined TARGET_equcondbc23
 \real{rep=simplify((\t1)/(-1*(\l[2])*x + \l[1]*y))}
 \condition{\name_condition}{NaN notin \rep\t2 and \rep*\l[1]*\l[4]=\t2}
#endif
#if defined TARGET_equcondbc24
 \real{rep=simplify((\t1)/(-1*(\l[2])*x + \l[1]*y))}
 \condition{\name_condition}{NaN notin \rep\t2 and \rep*(-1*(\l[2])*\l[5]+\l[1]*\l[4])=\t2}
#endif
