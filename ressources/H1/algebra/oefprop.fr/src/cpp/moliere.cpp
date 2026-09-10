target=Molire

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{\a=random(15..30)}
\real{\r=randint(1..5)*0.5}
\real{\f=randint(7..15)*0.5}
\real{\p=(\f*\a)-(\r*\a)}
\statement{\name_statement[1] \a \name_statement[2]
  \name_statement[3] \r &euro; \name_statement[4] \p &euro;.
  <p>\name_question?</p>}

\answer{\name_answer &euro;}{\f}{type=default}
\latex{
\begin{statement}
\name_statement[1] \a \name_statement[2]
  \name_statement[3] \r &euro; \name_statement[4] \p &euro;.
  <p>\name_question?</p>
\end{statement}
}
