target=FractionsIII

#define NUM II
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"

\precision{10000}
\integer{a=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10)}
\integer{c=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10)}
\integer{b=random(-6,-5,-4,-3,-2,2,3,4,5,6)}
\integer{d=random(-6,-5,-4,-3,-2,2,3,4,5,6)}
\integer{e=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10)}
\integer{f=random(-6,-5,-4,-3,-2,2,3,4,5,6)}
\integer{g=random(-10,-9,-8,-7,-6,-5,-4,-3,-2,2,3,4,5,6,7,8,9,10)}
\integer{h=random(-6,-5,-4,-3,-2,2,3,4,5,6)}
\text{rep=maxima(expand((\a/\b+\c/\d)/(\e/\f+\g/\h));)}
\statement{\name_statement:
<div class="wimscenter">
\(\frac{\frac{\a}{\b} + \frac{\c}{\d}}
{ \frac{\e}{\f} + \frac{\g}{\h} }\)
</div>}

\hint{\name_hint}
\answer{\name_answer}{\rep}{type=default}

\latex{
\begin{statement}
\name_statement:
\begin{center}
\(\frac{\frac{\a}{\b} + \frac{\c}{\d}}
{ \frac{\e}{\f} + \frac{\g}{\h} }\)
\end{center}
\end{statement}
}
