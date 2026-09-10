target=CDRom
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

passage en euros par F. Guerimand

\integer{c=random(2..10)}
\integer{u=random(10..25)}
\integer{l=random(25..60)}
\integer{t=(\c*\u)+\l}
\statement{
\name_statement[1] \t \name_statement[2] \c \name_statement[3] \u \name_statement[4]
<p>\name_question?</p>}

\answer{\name_answer}{\l}{type=numexp}
\latex{
\begin{statement}
\name_statement[1] \t \name_statement[2] \c \name_statement[3] \u \name_statement[4]
\par
\name_question?
\end{statement}
}
