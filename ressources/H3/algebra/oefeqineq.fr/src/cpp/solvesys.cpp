target=solvesys
\text{name_question=Résoudre le système d'équations suivant&nbsp;}

#include "author.inc"
\precision{10000}
#define NUM
#include "lang_titles.inc"
#include "lang.inc"

\integer{prixA=random(7..30)}
\integer{prixB=random(7..30)}
\if{\prixA=\prixB}{
\integer{prixA=7}
\integer{prixB=12}
}

\integer{nbA1=random(2..7)}
\integer{nbA2=random(2..7)}
\integer{nbB1=random(2..7)}
\integer{nbB2=random(2..7)}

\text{let=randrow(x,y
u,v
a,b)}
\text{x=item(1,\let)}
\text{y=item(2,\let)}
\text{sg1=randitem(+,-)}
\text{sg2=randitem(+,-)}

\real{total1=\nbA1*\prixA \sg1 \nbB1*\prixB}
\real{total2=\nbA2*\prixA \sg2 \nbB2*\prixB}

\text{lb=wims(char 1 to 2 of \{})}
\text{enonce=\left\lb\begin{array}{ccccc}
\nbA1 \x & \sg1 & \nbB1 \y & = & \total1\\\
\nbA2 \x & \sg2 & \nbB2 \y & = & \total2
\end{array}\right.}
\statement{
 \name_question:
<div class="wimscenter">\(\enonce\)</div>}

\reply{\(\x\)}{\prixA}{type=numexp}
\reply{\(\y\)}{\prixB}{type=numexp}
