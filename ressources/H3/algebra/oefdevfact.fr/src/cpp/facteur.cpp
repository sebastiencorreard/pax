target=facteur1 facteur2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{listnombres=wims(values v,-v for v=2 to 20)}
\text{listnombres=shuffle(\listnombres)}
\integer{a=item(1,\listnombres)}
\integer{b=item(2,\listnombres)}
\integer{c=item(3,\listnombres)}
\integer{d=item(4,\listnombres)}
\integer{e=item(5,\listnombres)}
\integer{g=maxima(gcd(\a,\b);)}
\if{\g!=1}{
 \integer{a=2}
 \integer{b=3}
}
\integer{g=maxima(gcd(\c,\d);)}
\if{\g!=1}{
 \integer{c=5}
 \integer{d=-3}
}
\text{sg=randitem(+,-)}
\text{x=shuffle(x,y,a,b,z)}

#if defined TARGET_facteur1
 \matrix{donnees=\a*\x[1]+\a*\x[2],\a
\a*\x[1]+\a*\x[2],\a
\a*\x[1]+\b*\x[1],\x[1]
\a*\x[1]+\b*\x[1],\x[1]
\e*(\a*\x[1]+\b)\sg(\c*\x[1]+\d)*(\a*\x[1]+\b),\a*\x[1]+\b
(\c*\x[1]+\d)*(\a*\x[1]+\b)\sg\e*(\a*\x[1]+\b),\a*\x[1]+\b
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)(\c*\x[1]+\d),\a*\x[1]+\b
(\a*\x[1]+\b)*(\c*\x[1]+\d)\sg\e*(\a*\x[1]+\b),\a*\x[1]+\b
(\a*\x[1]+\b)^2\sg\e*(\a*\x[1]+\b),\a*\x[1]+\b
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)^2,\a*\x[1]+\b
(\a*\x[1]+\b)^2\sg(\c*\x[1]+\d)*(\a*\x[1]+\b),\a*\x[1]+\b
(\c*\x[1]+\d)*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)^2,\a*\x[1]+\b}
#endif
#if defined TARGET_facteur2
 \integer{ab=\a*\b}
 \integer{ac=\a*\c}
 \integer{bc=\b*\c}
 \matrix{donnees=\ab*\x[1]+\b,\b
\b+\ab*\x[1],\b
\ac*\x[1]+\bc,\c
\bc+\ac*\x[1],\c}
#endif
\text{don=randrow(\donnees)}
\text{enonce=item(1,\don)}
\text{rep=item(2,\don)}
\text{rep=simplify(\rep)}
\text{enonce=texmath(\enonce)}
\text{rep2=simplify(-1*(\rep))}

\statement{
  \name_enonce[1]:
<div class="wimscenter">\(\enonce).</div>
<div class="spacer">
<label for="reply1"> \name_enonce[2] </label>\embed{r1,20}.
</div>
<div class="wims_instruction">\name_instruction</div>
}

\answer{\lg_ans}{\rep,\rep2}{type=litexp}{option=polexpand}
