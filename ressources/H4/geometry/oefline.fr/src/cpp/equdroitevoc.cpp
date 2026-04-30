target=equdroitevoc

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{x1=random(-10..10)}
\integer{y1=random(-10..10)}
\text{equation= simplify(\x1*x +\y1)}
\text{equation=texmath(\equation)}


#include "lang.inc"

\statement{ \name_statement1 \( (O;I;J) \).
\name_statement2: \( y=\equation \).
<p>
\name_statement3.
</p>}

\answer{\name_answer1 \((\math_droite) \)}{\x1}{type=default}
\answer{\name_answer2 \((\math_droite) \)}{\y1}{type=default}
\feedback{\reply1=\y1 and \reply2=\x1}{
<span class="oef_indbad">\name_feedback!</span>}
