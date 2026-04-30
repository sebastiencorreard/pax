target=equcond1 equcond2
#include "author.inc"
#include "lang_titles.inc"
\text{d=randitem(d,p,D)}
#include "lang.inc"
\integer{a=randint(-10..10)}
\integer{b=randitem(1,-1)*randint(1..10)}

#if defined TARGET_equcond1
 text{equation=y=maxima(expand(\a*x +\b);)}
#endif
#if defined TARGET_equcond2
 \integer{c=randint(1,-1)*randint(1..10)}
 \integer{a=\a=0?randint(1,-1)*randint(1..10)}
 \integer{c=\c=\b?\c-1}
  text{equation=y=maxima(expand(\a*x +\b);)}
#endif
 \text{equation=y=pari(\a*x +\b)}
\statement{
\name_introdroite:
<div class="wimscenter">\(\equation\).</div>
\question.
<p><b>\name_answer:</b></p>
  \name_equation: <label for="reply1">\(y\) =</label> \embed{r1,7}.}

\answer{}{\eq}{type=auto}

\text{t=wims(rawmath \eq)}

#if defined TARGET_equcond1
 \real{rep=simplify(\a*x+(\b)-(\t))}
 \condition{\name_condition}{NaN notin \rep and \rep!=0}
 \feedback{\rep=0}{\name_feed (\d) ???}
#endif
#if defined TARGET_equcond2
 \real{rep=simplify(-1/\a*x+(\b)-(\t))}
 \condition{\name_condition}{NaN notin \rep}
#endif
