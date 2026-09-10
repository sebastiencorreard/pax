target=oefmediat3

#include "lang.inc"
#define NUM 3
#include "lang_titles.inc"
#include "author.inc"
\keywords{perpendicular_bisector}
#include "dessinmediat.inc"

\text{fig=\med2,\med3,\med4,\med5,\med6}
\text{fig=shuffle(\fig)}

\text{reps=<img src="\med1" alt="">,<img src="\fig[1]" alt="">,<img src="\fig[2]" alt="">}
\text{affich=shuffle(\reps)}
\integer{rep=positionof(\reps[1],\affich)}

\statement{
\enonc [AB] :
<div class="wimscenter">\embed{r1}</div>
}

\answer{}{\rep;\affich}{type=click}
