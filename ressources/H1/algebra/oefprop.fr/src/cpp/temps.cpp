target=Tempsdeparcour
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{t=random(60,66,72,84,90,96,102,108,114,120)}
\integer{v=random(62,70,80,92,100,110)}
\integer{d=\v*\t/60}
\statement{\name_statement[1;] \d \(\textrm{km}\) \name_statement[2;] \v \(\textrm{km/h}\).
<p>\name_question?</p>}

\answer{\name_answer \(\textrm{min}\)}{\t}{type=default}
\latex{
\begin{statement}
\name_statement[1;] \d \(\textrm{km}\) \name_statement[2;] \v \(\textrm{km/h}\).
<p>\name_question?</p>
\end{statement}
}
