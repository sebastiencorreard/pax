target=Pyramide
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{\b=random(10..22)*10}
\integer{\h=random(5..13)*10}
\integer{\e=random(5..14)*100}
\real{\c=(\b*100)/\e}
\statement{\name_statement[1] \b \(\textrm{m}\) \name_statement[2] \h \(\textrm{m}\).
\name_statement[3] 1/\e.
<p>\name_question?</p>}

\answer{\name_answer}{\c}{type=default}
\latex{
\begin{statement}
\name_statement[1] \b \(\textrm{m}\) \name_statement[2] \h \(\textrm{m}\).
\name_statement[3] 1/\e.
<p>\name_question?</p>
\end{statement}
}
