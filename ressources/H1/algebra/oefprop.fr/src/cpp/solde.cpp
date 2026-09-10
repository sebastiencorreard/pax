target=Solde
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{\r=random(20,25,40,50)}
\integer{\e=random(10..60)}
\real{\p=(100/\r)*\e}

\statement{\name_statement[1;1] \r% \name_statement[1;2],
  \name_statement[2;1] \e \name_statement[2;2].
  <p>\name_question?</p>}

\answer{\name_answer}{\p}{type=default}
\latex{
\begin{statement}
\name_statement[1;1] \r\% \name_statement[1;2],
  \name_statement[2;1] \e \name_statement[2;2].
  <p>\name_question?</p>
\end{statement}
}
