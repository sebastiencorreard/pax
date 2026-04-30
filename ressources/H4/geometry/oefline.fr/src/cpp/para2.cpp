target=para2

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{m=random(-10..10)}
\integer{p=random(-10..10)}
\integer{xa=random(-10..10)}
\integer{ya=random(-10..10)}
\function{eq=simplify(\m*x+\ya-\m*\xa)}
\text{equation=texmath(maxima(expand(\m*x+\p)))}

#include "lang.inc"

\statement{\name_statement[1].
\name_statement[2] \( (\math_droite) \) \name_statement[3]: \( y=\equation \).
\name_statement[4] \( (\math_droite') \) \name_statement[5] \( (\math_droite) \)
\name_statement[6] \( A\;(\xa;\ya) \).}


\answer{\name_answer \( (d') : y \)}{\eq}{type=function}
\function{k=diff(\reply1,x)}
\feedback{1=1}{\name_feedback1 \(y=\eq\).}
\feedback{\k<>\m}{\name_feedback2 \((\math_droite)\).}
