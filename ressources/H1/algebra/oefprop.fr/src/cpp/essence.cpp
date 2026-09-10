target=Essence

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
\precision{10000}

\integer{\l=random(8,10,12,14,16)}
\integer{\k=random(4*\l..7*\l)}
\real{\a=(\k/\l)*100}
\statement{\name_statement[1] \l \name_statement[2] \(\textrm{km}\). \name_statement[3]
  \k \name_statement[4].
 <p>\name_question?</p>
}

\answer{\name_answer}{\a}{type=default}
\latex{
\begin{statement}
\name_statement[1] \l \name_statement[2] \(\textrm{km}\). \name_statement[3]
  \k \name_statement[4]
 <p>\name_question?</p>
\end{statement}
}
