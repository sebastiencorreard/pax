target=equ_dr0

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{a=random(-15..15)}
\integer{bm=random(1..10)}
\integer{bp=random(1..2)}
\integer{b=\bm*(-1)^\bp}
\integer{c=random(-10..10)}

\function{equ=maxima(expand(simplify(\a*x + \b*y + \c)))}
\text{eq0=texmath(\equ)}


\function{m=simplify((-1)*\a/\b)}
\function{p=simplify((-1)*\c/\b)}

\function{eqr=maxima(expand(simplify(\m*x+\p)))}
\text{eqr0=texmath(\eqr)}


#include "lang.inc"

\statement{\name_statement[1;] \(\math_droite\) \name_statement[2;]
<div class="wimscenter">
 \(\eq0 = 0\)
</div>
\name_statement[3;] \(\math_droite\).
}

\answer{\name_answer1}{\m}{type=default}
\answer{\name_answer2}{\p}{type=default}

\solution{\name_solution \(\math_droite\) \name_is \(y = \eqr0\)}
