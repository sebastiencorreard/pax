target=oefzeroinutile1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
%Paramètres de l'exercice%
\language{fr}
\format{html}

%Programmation%

\real{\nb=random(1..999999)/1000}
\text{\a=0,00,000,0000}
\text{\b=randomitem(\a)}
\text{\c=randomitem(\a)}
\statement{
\name_stat[1] \b\nb\c \name_stat[2]  : \embed{r1,10}
}

%Analyse de la réponse de l'élève%

\answer{}{\nb}{type=text}
