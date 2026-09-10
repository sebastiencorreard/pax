target=EchelleII

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{\e=random(15,20,25,50,100,200,250,500)*1000}
\integer{\a=random(3..15)}
\real{\d=(\a*\e)/100000}

\statement{\name_statement 1/\e.
\name_question[1] \d \(\textrm{km}\), \name_question[2]?
}

\answer{\name_answer}{\a}{type=default}
\latex{
\begin{statement}
\name_statement 1/\e.
\name_question[1] \d \(\textrm{km}\), \name_question[2]?
\end{statement}
}
