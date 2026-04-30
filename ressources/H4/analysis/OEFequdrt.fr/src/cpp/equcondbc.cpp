target=equcondbc1 equcondbc2 equcondbc3 equcondbc4
#include "author.inc"
#include "lang_titles.inc"

\text{d=randitem(d,p,D)}
#include "lang.inc"
\integer{a=randint(-10..10)}
\integer{b=randitem(1,-1)*randint(1..10)}

#if defined TARGET_equcondbc1
 \integer{c=randint(1,-1)*randint(1..10)}
 \integer{c=\c=\b?\c-1}
 \integer{f=0}
 \integer{e=\c}
 text{equation=y=maxima(expand(\a*x +\b);)}
 \text{equation=y=pari(\a*x +\b)}
 text{rep=maxima(expand(\a*x +\c);)}
 \text{rep=pari(\a*x +\c)}
#endif
#if defined TARGET_equcondbc2
 \integer{c=randint(1,-1)*randint(1..10)}
 \integer{c=\c=\b?\c-1}
 \integer{f=randint(1,-1)*randint(1..10)}
 \integer{e=\a*(\f) +\c}
 text{equation=y=maxima(expand(\a*x +\b);)}
 \text{equation=y=pari(\a*x +\b)}
 text{rep=maxima(expand(\a*x +\c);)}
 \text{rep=pari(\a*x +\c)}
#endif
#if defined TARGET_equcondbc3
 \integer{a=\a=0?randint(1,-1)*randint(1..10)}
 \integer{c=randint(1,-1)*randint(1..10)}
 \integer{c=\c=\b?\c-1}
 \integer{f=0}
 \integer{e=\c}
 text{equation=y=maxima(expand(\a*x +\b);)}
 \text{equation=y=pari(\a*x +\b)}
 \text{rep=maxima(expand(-1/\a*x +\c);)}
#endif
#if defined TARGET_equcondbc4
 \integer{a=\a=0?randint(1,-1)*randint(1..10)}
 \integer{c=randint(1,-1)*randint(1..10)}
 \integer{c=\c=\b?\c-1}
 \integer{f=randint(1,-1)*randint(1..3)*\a}
 \integer{e=-1/\a*(\f) +\c}
text{equation=y=maxima(expand(\a*x +\b);)}
 \text{equation=y=pari(\a*x +\b)}
 \text{rep=maxima(expand(-1/\a*x +\c);)}
#endif

\statement{
\name_introdroite:
<div class="wimscenter">\(\equation\).</div>
\question (\f,\e).
<p><b>\name_answer:</b></p>
  \name_question: <label for="reply1">\(y\) =</label> \embed{r1,7}.}

\answer{}{\rep}{type=algexp}
