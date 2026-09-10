target=ppower01 ppower02
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{nb=\confparm1 iswordof 1 2 3 4 5? \confparm1:3}
\text{A=wims(makelist x for x=2 to 10)}
\text{A=shuffle(\A)}
\text{A=\A[1..\nb]}
#if defined TARGET_ppower01
\observation{nombres inférieurs à 10, puissance de 2 uniquement}
\text{B=wims(makelist 2 for x=1 to \nb)}
#endif
#if defined TARGET_ppower02
\observation{nombres inférieurs à 9, puissance de 2, 3 ou 4 selon la taille du nombre}
\text{B=}
\for{i=1 to \nb}{
  \text{b=\A[\i]<4 ? randint(2..4):randint(2..3)}
  \text{b=\A[\i]>5 ? 2}
  \text{B=wims(append item \b to \B)}
}
#endif
\text{N=pari(A=[\A]; B=[\B]; vector(\nb,i,A[i]^B[i]))}
\text{STEP=wims(makelist r x for x=1 to \nb)}
\steps{\STEP}
\statement{ \name_statement:
<ul>
\for{j=1 to \nb}{
<li>
<label for="reply\j">\(\A[\j]^\B[\j] \) =</label> \embed{r \j,5}
</li>
}
</ul>
}

\answer{}{\N[1]}{type=numexp}
\answer{}{\N[2]}{type=numexp}
\answer{}{\N[3]}{type=numexp}
\answer{}{\N[4]}{type=numexp}
\answer{}{\N[5]}{type=numexp}
\answer{}{\N[6]}{type=numexp}
\answer{}{\N[7]}{type=numexp}
