\title{Question T1118 Droite}
\keywords{segment,segment_equations}
%%%%%%%%%%%%%% Question 18 %%%%%%%%%%%%


#include "T11repere01.inc"

\integer{p18=randint(-4..4)}
\if{\p18>2}{\integer{m18=randint(-4..0)}}
\if{\p18<-2}{\integer{m18=randint(1..4)}}
\if{(\p18>=-2) and (\p18<=2)}{\integer{m18=randint(1..4)}}
\function{f18=\m18*x+\p18}

\integer{taille18=300}
\text{fig18=draw(\taille18,\taille18
\repere
plot blue,\f18)}

\text{fig18=<img src="\fig18" alt="">}

\text{enonce=<table><tr><td>\fig18 </td><td> L'équation de la droite tracée est :  }
\text{enonceb= </td></tr></table>}
\text{rep=y=\f18}
\text{feedback=}
\integer{size=8}
