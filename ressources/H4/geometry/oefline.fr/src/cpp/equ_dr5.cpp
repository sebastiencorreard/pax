target=equ_dr5

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{a=random(-1,1)*randint(1..10)}
\integer{b=random(-10..10)}
\integer{x2=random(-10..10)}
\integer{ym=random(1..6)}
\integer{yp=random(1..2)}
\integer{y2=\a*\x2+\ym*(-1)^\yp}
\rational{bp=\y2-\a*\x2}
\function{eq=maxima(expand(simplify(\a*x+\b)))}
\function{eqs=maxima(expand(simplify(\a*x+\bp)))}
\text{eqa=texmath(\eq)}
\text{eqsa=texmath(\eqs)}

#include "lang.inc"

\text{coord=randitem(\name_options_list)}
\if{\coord=\name_options_list[1]}{
\rational{x=-\bp/\a}
\rational{y=0}
}
\if{\coord=\name_options_list[2]}{
\rational{x=0}
\rational{y=\bp}
}

\statement{\name_statement[1;] \(\math_droite)
\name_statement[2;] \(y = \eqa) \name_and
\name_statement[3;] \(\math_droite'), \name_statement[4;] \(\math_droite), \name_statement[5;] \(A(\x2,\y2)).
<div class="wims_question spacer">
\name_question[1;] \(M) \name_question[2;] \(\math_droite')
\name_question[3;] \coord :
<div class="wimscenter">
\(M) (\embed{reply 1,5};\embed{reply2, 5})
</div>
</div>
}

\answer{\name_answer1}{\x}{type=default}
\answer{\name_answer2}{\y}{type=default}

\solution{\name_solution \(\math_droite') \name_is \(y = \eqs).}
