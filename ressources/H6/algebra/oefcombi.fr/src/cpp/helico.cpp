target=helico

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{num=random(2..4)}
\integer{num2=2*\num}
\integer{pro=factorial(\num)}
\integer{ddd=item(\num,1,6,90,2520,113400)}
\integer{distr=\pro*\ddd}
\statement{\name_enonce[1] \num \name_enonce[2], \num \name_enonce[3]
\num2 \name_enonce[4]
<p>\name_question?</p>}

\answer{\name_answer}{\distr}
