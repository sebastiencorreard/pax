target=DensitII

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{\d=random(5..15)*10}
\integer{\s=random(40..70)*10}
\real{\p=\s*\d/1000}
\statement{
\name_statement[1] \s 000 \(\textrm{km}^2\) \name_statement[2] \p millions.
<p>\name_question?</p>}

\answer{\name_answer}{\d}{type=default}
\latex{
\begin{statement}
\name_statement[1] \s 000 \(\textrm{km}^2\) \name_statement[2] \p millions.
<p>\name_question?</p>
\end{statement}
}
