target=secnico

#include "header.inc"
#include "lang_titles.inc"

\keywords{lines,linear_system}

\integer{m1=random(-10..10)}
\integer{p1=random(-10..10)}
\integer{m2=random(-10..10)}
\integer{p2=random(-10..10)}
\while{\m1==\m2}{
\m1=random(-10..10)
\m2=random(-10..10)}
\text{equ1=texmath(maxima(expand(\m1*x+\p1)))}
\text{equ2=texmath(maxima(expand(\m2*x+\p2)))}

#include "lang.inc"

\statement{\name_statement[1]. \name_statement[2] \( (\math_droite) \) \name_and \( (d') \)
\name_statement[3] \( y=\equ1 \) \name_and \( y=\equ2 \).
\name_statement[4] \( (\math_droite) \) \name_and \( (\math_droite') \) \name_statement[5]
\( A(x_A;y_A) \). \name_statement[6] \( A \).}
\answer{\name_answer1 \( A \): \( x_A \)}{(\p2-\p1)/(\m1-\m2)}{type=numeric}
\answer{\name_answer2 \( A \): \( y_A \)}{\m1*(\p2-\p1)/(\m1-\m2)+\p1}{type=numeric}
