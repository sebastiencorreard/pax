target=oefecrit104
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\langage{fr}
\format{html}
\integer{n=randint(3..5)}
\text{chiffre=shuffle(9)}
\text{\chiff=}
\for{a=1 to \n}
     {\text{chiff=wims(append item \chiffre[\a] to \chiff)}}
\text{chiff=wims(append item 0 to \chiff)}
\text{chiff=shuffle(\chiff)}
\text{chiff=wims(append item \chiffre[\n + 1] to \chiff)}

\integer{rep1=0}
\for{i=2 to \n + 2}
{\integer{rep1=\rep1+\chiff[\i]*10^(\i-2)}}
\text{ord=shuffle(\n+1)}
\text{dix=1,10,100,1 000,10 000,100 000}
\integer{large=5}
\statement{
\name_statement:
<div class="wimscenter">
\for{b=1 to \n}
{\if{\chiff[\ord[\b]+1]<>0}{(\chiff[\ord[\b]+1] x \dix[\ord[\b]]) +}}
(\chiff[\ord[\n + 1]+1] x \dix[\ord[\n + 1]])
=
\embed{r1,\large}
</div>}

\answer{}{\rep1}{type=numeric}
