target=ant

#include "header.inc"
#include "lang_titles.inc"
#include "values.inc"
#include "tablegen.inc"
#include "common.inc"
#include "lang.inc"
\text{yt=\infty isin \ys[1]?\ys[2..-1]:\ys}
\text{yt=\infty isin \yt[-1]?\yt[1..-2]:\yt}

\text{y0=random(0..10)>3?randitem(\yt,\xs[2..-2]):randitem(\values)}

\integer{n=0}
\text{zone=}
\text{point=}
\for{i=1 to \tabcnt}{
  \if{(\y0 > \YY[\i] and \y0 < \YY[\i+1]) or (\y0 < \YY[\i] and \y0 > \YY[\i+1])}{
    \integer{n=\n+1}
    \text{zone=\zone \i}
  }
  \if{\i>1 and \y0 = \YY[\i]}{
    \integer{n=\n+1}
    \text{point=\point \i}
    \text{minmax=\arrows[\i] issametext ne?Min:Max}
  }
}

\text{zone=wims(words2items \zone)}
\integer{zonecnt=items(\zone)}
\text{point=wims(words2items \point)}
\statement{\intro

#include "table.inc"

\name_statement[1] \(\y0\) \name_statement[2] \(f\) ?
\embed{reply1,3}
}

\answer{\name_answer \(\y0\)}{\n}{type=number}

\solution{
 \if{\n=0}{
  \(\y0) est
  \if{\y0<\ys[2]}{au-dessous de}{au-dessus de}
  l'image de \(f\). Elle n'a donc aucun antécédent.
 }
 \if{\n=1}{
  \if{\point notsametext \empty}{
   \(\y0\) est égale à \minmax(\(f\)), atteint en \(x = \xs[\point]\).
  }{
   \(\y0\) a un unique antécédent dans l'intervalle
   \rightbrack\xshow[\zone],\xshow[\zone+1]\leftbrack.
  }
 }
 \if{\n>1}{
  \if{\zonecnt>1}{
   \(\y0\) a un antécédent dans chacun des intervalles suivants :
   <div class="wimscenter">
   \for{t in \zone}{
    \rightbrack\xshow[\t],\xshow[\t+1]\leftbrack &nbsp;&nbsp;
   }
   </div>
  }{
   \(\y0\) a un antécédent dans l'intervalle
   \rightbrack\xshow[\zone],\xshow[\zone+1]\leftbrack.
  }
  \if{\point notsametext \empty}{
   <p>Elle est aussi égale à \(f(\xs[\point])\).</p>
  }
 }
}

\feedback{\reply1 = \n+1 and \y0 isitemof \ys[1,-1]}{
 <strong>Attention</strong>. \(\y0\) n'est que la limite de \(f\) quand \(x\)
 tend vers
 \if{\y0 issametext \ys[1]}{
  \(-\infty\). Elle n'a pas d'antécédent en \(-\infty\).
 }{
  \(+\infty\). Elle n'a pas d'antécédent en \(+\infty\).
 }
}
