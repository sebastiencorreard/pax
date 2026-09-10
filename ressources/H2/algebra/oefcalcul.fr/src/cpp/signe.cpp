target=signe
#define NUM
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{n=randint(5..20)}
\integer{m=randint(3..\n)}
\text{choix=random(1,2)}
\text{sol=\name_sol}
\text{negatif=item(\choix,\name_negpos)}
\integer{rep=\choix=1 ? \m: \n-\m}
\text{reponse=(-1)^(\rep)=1? item(1,\sol): item(2,\sol)}
\statement{
\name_statement[1] \n \name_statement[2] \m \name_statement[3] \negatif
\name_statement[4] \embed{choice 1}.
}
\choice{\name_answer}{\reponse}{\sol}

\latex{
\begin{statement}
\name_statement[1] \n \name_statement[2] \m \name_statement[3] \negatif
\name_statement[4] \(\dots\dots\)
\end{statement}
}
