target=proprietaire
\language{fr}
\author{Jean-Baptiste, Frondas}
\email{jbfrondas@gmail.com}
\format{html}
\precision{10000}
\computeanswer{no}
\source{brevet Métropole 2003}

\text{fractions=1/2 , 1/3, 1/4, 1/5, 2/3, 2/5, 3/4, 3/5, 4/5, 5/6, 5/7, 5/8, 6/7, 7/8,}
% Mélange des expressions
\text{fractions=shuffle(\fractions)}

\rational{fraction1=\fractions[1]}
\rational{fraction2=\fractions[2]}
\rational{reste=(1-\fraction1)*(1-\fraction2)}

\integer{taille=random(1..10)*10}
\real{terre=\taille*\reste*100}
\integer{ter=\terre}
\real{terrain=\ter/100}

# define NUM 6
#include "lang_titles.inc"
#include "lang.inc"

\statement{\enonce
<ol>
<li><label for="reply1">\question1</label> \embed{reply1,5}</li>
<li><label for="reply2">\question2</label> \embed{reply2,5}</li>
</ol>
}

\answer { \rest }{ \reste }{ type = litexp}
\answer { \hectares }{ \terrain }

\solution{\solution}

\latex{
\begin{statement}
\enonce
\begin{enumerate}
	\item \question1
	\item \question2
\end{enumerate}
\end{statement}

\begin{solution}
\solution
\end{solution}
}
