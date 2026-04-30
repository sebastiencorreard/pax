target=abscisse

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{x1=random(-10..10)}
\integer{x2=random(-10..10)}
\integer{x3=random(-10..10)}

\text{equation=maxima(expand(\x1*x+\x2))}
\text{equation=texmath(\equation)}

#include "lang.inc"

\statement{\name_statement[1]. \name_statement[2] \( (\math_droite) \)
\name_statement[3] \( y=\equation \) \name_and \( A \) \name_statement[4] \( \x3 \).
<div class="spacer">
\name_question
</div>}

\answer{\name_answer \( A \) \name_is \( x_A \)}{(\x3-\x2)/(\x1)}{type=numeric}
