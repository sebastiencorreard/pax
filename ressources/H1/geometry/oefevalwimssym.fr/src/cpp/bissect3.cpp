target=oefbissect3
#include "author.inc"
#define NUM 3
#include "lang_titles.inc"
#include "lang.inc"
\keywords{angle_bisector}
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}

#include "dessinbiss2.inc"

\text{fig=\biss1,\biss2,\biss3}

\text{reps=<img src="\fig[1]" alt="">,<img src="\fig[2]" alt="">,<img src="\fig[3]" alt="">}
\text{affich=shuffle(\reps)}
\integer{rep=positionof(\reps[1],\affich)}

\statement{
\enonc \(\widehat{\nom[3]\nom[1]\nom[2]}\):
<div class="wimscenter">\embed{r1}.</div>
}

\answer{}{\rep;\affich}{type=click}
