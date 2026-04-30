target=equ_dr4

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{x1=random(-10..10)}
\integer{y1=random(-10..10)}
\integer{y2=random(-10..10)}
\integer{xm=random(1..6)}
\integer{xp=random(1..2)}
\integer{x2=\x1+\xm*(-1)^(\xp)}
\function{a=simplify((\y2-\y1)/(\x2-\x1))}
\function{b=simplify(\y1-\a*\x1)}
\function{eq=maxima(expand(simplify(\a*x+\b)))}
\text{eqa=texmath(\eq)}

#include "lang.inc"

\statement{\name_statement1:
\(A (\x1,\y1)) \name_and \(B(\x2,\y2)).
\name_statement2 \(\math_droite\) \name_is:
<div class="wimscenter"">
\(y ) = \embed{reply 1,6} \(x) + \embed{reply 2,6}
</div>
}

\answer{\name_answer1}{\a}{type=default}
\answer{\name_answer2}{\b}{type=default}

\solution{\name_solution \(\math_droite\) \name_is \(y = \eqa\)}
