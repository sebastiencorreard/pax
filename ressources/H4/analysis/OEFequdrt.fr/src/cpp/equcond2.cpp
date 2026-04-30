target=equcond21 equcond22
#include "author.inc"
#include "lang_titles.inc"
\text{d=randitem(D,d,m,p,q)}
#include "lang.inc"
\text{l=wims(values v for v=-10 to 10)}
\text{l=shuffle(\l)}

#if defined TARGET_equcond21
 \text{m1=pari(\l[1]*x+\l[2]*y)}
 \text{m2=pari(\l[2]*y+\l[1]*x)}
 \text{equation=randitem(texmath(\m1)=\l[3],texmath(\m2)=\l[3]) }
#endif
#if defined TARGET_equcond22
 \text{l=wims(listcomplement 0 in \l)}
 \text{m1=pari(\l[1]*x+\l[2]*y)}
 \text{m2=pari(\l[2]*y+\l[1]*x)}
 \text{equation=randitem(texmath(\m1)=\l[3],texmath(\m2)=\l[3]) }
#endif
\statement{
\name_introdroite:
<div class="wimscenter"> \(\equation\). </div>
\question.
<p><b>\name_answer:</b></p>
  <label for="reply1">\name_equation</label>: \embed{r1,7}
  <label for="reply2">=</label> \embed{r2,4}.
<div class="wims_instruction">\name_inst \(a x+b y=c\).</div>}

\answer{}{\eq1}{type=auto}
\answer{}{\eq2}{type=auto}

\text{t1=wims(rawmath \eq1)}
\integer{t2=wims(rawmath \eq2)}
#if defined TARGET_equcond21
 \real{rep=simplify((\t1)/(\l[1]*x + \l[2]*y))}
 \condition{\name_cond}{NaN notin \rep\t2 and \rep*\l[3]!=\t2}
 \feedback{\rep*\l[3]=\t2}{\name_feed (\d) ???}
#endif
#if defined TARGET_equcond22
 \real{rep=simplify((\t1)/(-1*(\l[2])*x + \l[1]*y))}
 \condition{\name_cond}{NaN notin \rep\t2}
#endif
