target=FractionsI
#define NUM I
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"

\precision{10000}

\integer{a=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10)}
\integer{c=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10)}
\integer{b=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,2,3,4,5,6,7,8,9,10)}
\integer{d=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,2,3,4,5,6,7,8,9,10)}
\text{rep=maxima(expand(\a/\b+\c/\d);)}
\text{denom=maxima(abs(\b*\d/gcd(\b,\d));)}
\statement{<div class="wims_instruction"><strong>\name_instruction</strong></div>
 \name_statement:
<div class="wimscenter">
\((\a)/(\b) + (\c)/(\d)\)
</div>}

\hint{\name_hint \denom.}
\answer{\name_answer}{\rep}{type=numexp}

\latex{
\begin{statement}
\name_statement:
\begin{center}
\((\a)/(\b) + (\c)/(\d)\)
\end{center}
\end{statement}
}
