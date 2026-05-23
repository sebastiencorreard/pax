target=avion
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{a=randint(100..200)}
\text{b=randint(100..200)}
\text{pyth=pari(pyth(A,B,lim)={for(a=A+B,A+lim+B, for(b=a,a+lim,N=sqrt(a^2+b^2); if(floor(N)==N, return([a,b,floor(N)]))))})}
\text{bca=pari(lim=25; pyth(\a,\b,lim))}
\text{bca=\bca[1]==0? pari(lim1=100; pyth(\a,\b+lim,lim1))}
\text{bca=\bca[1]==0? erreur}
\text{pyth=wims(sort item \bca)}
\text{pyth=pari([\pyth]/10.)}

\text{enonce=wims(replace internal XXXX by \ville in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \pyth[2] in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \pyth[3] in \enonce)}
\text{question=wims(replace internal XXXX by \ville in \name_question)}
\statement{\enonce
<div><label for="reply1">\question?</label> \embed{r1,6} km.</div>}

\answer{}{\pyth[1]}{type=numeric}
