target=Tourdumonde
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}
\integer{k=random(3..16)}
\integer{v=random(80,100,125,160)}
\rational{h=40000/\v}
\statement{\name_statement1[1], \name_statement1[2] \k \(\textrm{km}\) \name_statement2[1] \v
\(\textrm{km/h}\) \name_statement2[2]
<p>\name_question?</p>}

\answer{\name_answer}{\h}{type=default}
\latex{
\begin{statement}
\name_statement1[1], \name_statement1[2] \k \(\textrm{km}\) \name_statement2[1] \v
\(\textrm{km/h}\) \name_statement2[2]
<p>\name_question?</p>
\end{statement}
}
