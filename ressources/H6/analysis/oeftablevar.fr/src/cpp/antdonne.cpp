target=antdonne

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "values.inc"
#include "tablegen.inc"
#include "common.inc"
\integer{n=random(1,2,3,4)}
\text{zone=}
\text{point=}
\text{ante=\n = 1 ? \name_ant[1]:\name_ant[2]}
\statement{\intro

#include "table.inc"

\name_statement \n \ante.
<div class="wimscenter">
 \(y_0\) = \embed{reply1,15}
</div>
}

\answer{\(y_0\)}{\y0}{type=auto}

\integer{z=0}
\for{i=1 to \tabcnt}{
 \if{(\y0 > \YY[\i] and \y0 < \YY[\i+1]) or
     (\y0 < \YY[\i] and \y0 > \YY[\i+1])}{
  \integer{z=\z+1}
  \text{zone=\zone \i}
 }
 \real{vtest=simplify(\y0 - \YY[\i])}
 \if{\i>1 and \vtest=0}{
  \integer{z=\z+1}
  \text{point=\point \i}
  \text{minmax=\arrows[\i] issametext ne?Min:Max}
 }
}

\condition{\(\y0\) a exactement \n \ante}{\z=\n}

\text{zone=wims(words2items \zone)}
\integer{zonecnt=items(\zone)}
\text{point=wims(words2items \point)}

\feedback{\z!=\n}{
<div class="oef_indbad">
 Nombre d'antécédents de \(\y0\) : \z.
</div>
 \if{\z=0}{
  \(\y0\) est
  \if{\y0<\ys[2]}{au-dessous de}{au-dessus de}
  l'image de \(f\). Elle n'a donc aucun antécédent.
 }
 \if{\z=1}{
  \if{\point notsametext \empty}{
   \(\y0\) est égale à \minmax(\(f\)), atteint en \(x = \xs[\point]\).
  }{
   \(\y0\) a un unique antécédent dans l'intervalle
   \rightbrack\xshow[\zone],\xshow[\zone+1]\leftbrack.
  }
 }
 \if{\z>1}{
  \if{\zonecnt>1}{
   \(\y0\) a un antécédent dans chacun des intervalles suivants :
   <div class="wimscenter">
   \for{t in \zone}{
    \rightbrack\xshow[\t],\xshow[\t+1]\leftbrack &nbsp;&nbsp;
   }
   </div>
  }{
   \(\y0\) a un antécédent dans l'intervalle
   \rightbrack\xshow[\zone],\xshow[\zone+1]\leftbrack. <p>
  }
  \if{\point notsametext \empty}{
   Elle est aussi égale à \(f(\xs[\point])\).
  }
 }
}
