target=busetconducteu
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{num=random(3..6)}
\integer{distr=factorial(\num)^2}
\statement{\name_enonce[1] \num \name_enonce[2], \num \name_enonce[3]
  \num \name_enonce[4]. <p>\name_question?</p>}

\answer{\name_answer}{\distr}
