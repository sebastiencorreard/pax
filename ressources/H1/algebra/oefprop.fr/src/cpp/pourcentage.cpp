target=Pourcentages

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{\c=random(800..950)}
\integer{\n=random(100..290)}
\real{\a=round((\n/\c)*1000)/10}
\integer{\e=random(200..400)}
\real{\p=round((\e/\c)*10000)/100}
\statement{<p>
\name_statement[1;1] \c \name_statement[1;2], \a% \name_statement[2;].
\name_question1?</p>
<p>\e \name_statement[3;].
\name_question2?</p>
}

\answer{\name_answer1}{\n}{type=default}
\answer{\name_answer2}{\p}{type=default}
\latex{
\begin{statement}
\begin{itemize}
\item \name_statement[1;1] \c \name_statement[1;2], \a\% \name_statement[2;].
\name_question1?
\item
\e \name_statement[3;]. \name_question2?
\end{itemize}
\end{statement}
}
