target=Poids

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{\c=random(8,10)}
\integer{\s=random(4,5)}
\integer{\p=random(8..12)}
\real{\v=\p/\c}
\integer{\t=\p*\s}
\statement{\name_statement[1] \c \name_statement[2] \s fois \name_statement[3]
<p> \name_statement[4] \p \name_statement[5], \name_statement[6]</p>}

\answer{\name_answer1}{\v}{type=default}
\answer{\name_answer2}{\t}{type=default}
\latex{
\begin{statement}
\name_statement[1] \c \name_statement[2] \s fois \name_statement[3] \p
\name_statement[4], \name_statement[5]
\end{statement}
}
