target=bird
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{a=randint(20..30)}
\text{b=randint(20..40)}
\text{pyth=pari(pyth(A,B,lim)={for(a=A+B,A+lim+B, for(b=a,a+lim,N=sqrt(a^2+b^2); if(floor(N)==N, return([a,b,floor(N)]))))})}
\text{bca=pari(lim=25; pyth(\a,\b,lim))}
\text{bca=\bca[1]==0? pari(lim1=100; pyth(\a,\b+lim,lim1))}
\text{bca=\bca[1]==0? erreur}
\text{pyth=wims(sort item \bca)}
\text{pyth=pari([\pyth]/10.)}

\text{enonce=wims(replace internal XXXX by \pyth[2] in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \pyth[1] in \enonce)}

\statement{\enonce
<div class="question">
<label for="reply1">\name_question?</label> \embed{r1,5} m
</div>}
\answer{}{\pyth[3]}{type=numeric}
