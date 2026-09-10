target=Courses

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{b=random(2..8)}
\real{r=random(0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1)}
\real{m=random(0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5)}
\real{p=\r+\m}
\real{s=(\b*\p)-\m}
\text{n=randitem(\name_product)}

\statement{\name_statement[1;] \n.
  \name_statement[2;1] \b \name_statement[2;2]
  \name_statement[3;] \m \name_euro.
  \name_statement[4;] \r \name_euro.
<p>
\name_question[1;] \n? \name_question[2;]?
</p>
<div class="wims_instruction">\name_instruction \name_euro.</div>}
\answer{\name_answer1}{\p}{type=default}
\answer{\name_answer2}{\s}{type=default}
\latex{
\begin{statement}\name_statement[1;] \n.
  \name_statement[2;1] \b \name_statement[2;2]
  \name_statement[3;] \m \name_euro.
  \name_statement[4;] \r \name_euro.
\name_question[1;] \n? \name_question[2;]?
\end{statement}
}
