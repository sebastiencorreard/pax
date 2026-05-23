target=geometrie
#include "lang_titles.inc"
#include "author.inc"
\precision{10000}

\integer{pourcent=randint(2..20)}
\text{figure=randitem(carré,losange,rectangle,triangle,triangle équilatèral,triangle isocéle,parallélogramme)}
\text{name_enonce=On augmente la longueur de tous les côtés d'un \figure de}
\text{name_question=De quel pourcentage son périmètre augmente-t-il&nbsp;}
\statement{
\name_enonce \pourcent %.
<p>\name_question? </p>
<div>
<label for="reply1"><b>Votre réponse </b>:</label> \embed{r1,4} %.
</div>
}
\answer{Réponse}{\pourcent}{type=numexp}
\latex{
\begin{statement}
\name_enonce \pourcent \%.
\name_question? ------
\end{statement}
}
