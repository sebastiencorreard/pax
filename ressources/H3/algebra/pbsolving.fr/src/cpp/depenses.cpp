target=depenses

\language{fr}
\author{Jean-Baptiste, Frondas}
\email{jbfrondas@gmail.com}
\format{html}
\precision{10000}
\computeanswer{no}

\text{genre=random(girl,boy)}
%Genre dans le fichier de traduction

\text{prenom=slib(lang/fname, \genre )}

\integer{p1=random(1..7)}
\integer{pp1=\p1+1}
\integer{q1=random(\pp1..15)}

\integer{p2=random(1..6)}
\integer{pp2=\p2+1}
\integer{q2=random(\pp2..9)}

\rational{frac1=\p1/\q1}
\text{Frac1=\dfrac{\p1}{\q1}}
\rational{frac2=\p2/\q2}
\text{Frac2=\dfrac{\p2}{\q2}}

\integer{reste=random(1..9)*(\q1-\p1)*(\q2-\p2)}
\rational{part=(1-\frac1)*(1-\frac2)}
\rational{argent=(\reste)/(\part)}
#define NUM 4
#include "lang_titles.inc"
#include "lang.inc"
\statement{\enonce : \embed{reply1}
}
\answer { \rest }{ \reste }

\solution{}

\latex{
\begin{statement}
\enonce
\end{statement}

\begin{solution}
\end{solution}
}
