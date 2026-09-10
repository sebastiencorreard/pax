target=DensitII2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{\d=random(5..15)*10}
\integer{\s=random(40..70)*10}
\real{\p=\s*\d/1000}
\statement{\name_statement[1] \s 000 \(\textrm{km}^2\)
\name_statement[2] \d \(\name_statement[3]{/}\textrm{km}^2\).
<p>
\name_question?
</p>}

\answer{\name_answer}{\p}{type=default}
\latex{
\begin{statement}
\name_statement[1] \s 000 \(km^2\)
\name_statement[2] \d \(\name_statement[3]{/}\textrm{km}^2\).
<p>
\name_question?
</p>
\end{statement}
}
