target=Tapis

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{f=random(20,25,30,35,40,45,50,55,60)*10}
\integer{s=random(10..40)}
\integer{t=random(1,2)}
\text{t1=item(\t,\name_incdec)}
\text{t2=item(\t,\name_incdec[2,1])}
\statement{
\name_statement[1;1] \f \name_statement[1;2], \name_statement[2;1] \t1 \name_statement[2;2] \s %
\name_statement[2;3], \name_statement[3;1] \t2 \name_statement[3;2] \s % \name_statement[3;3].
<p>\name_question?</p>
}

\choice{\name_answer}{\name_rep[1] \f \name_euro}{\name_rep[2] \f \name_euro, \name_rep[3]}
\latex{
\begin{statement}
\name_statement[1;1] \f \name_statement[1;2], \name_statement[2;1] \t1 \name_statement[2;2] \s \%
\name_statement[2;3], \name_statement[3;1] \t2 \name_statement[3;2] \s \% \name_statement[3;3].
<p>\name_question?</p>
\end{statement}
}
