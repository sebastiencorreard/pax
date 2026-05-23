target=2produit 2quotient 2quoprod 2produit2 2somme1 2somme2 2somme3 2somme4 2somquo1 2somquo2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_2produit
\text{type=produitcp}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_2somme1
\text{type=somme}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_2somme3
\text{type=somme}
\integer{nbfact=2}
\integer{div=2}
#endif
#if defined TARGET_2somme4
\text{type=somme}
\integer{nbfact=3}
\integer{div=0}
#endif
#if defined TARGET_2somme2
\text{type=somme}
\integer{nbfact=3}
\integer{div=2}
#endif
#if defined TARGET_2produit2
\text{type=produitcp}
\integer{nbfact=3}
\integer{div=0}
#endif
#if defined TARGET_2quotient
\text{type=quotientcp}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_2quoprod
\text{type=quotientcp,produitcp}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_2somquo1
\text{type=somquo}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_2somquo2
\text{type=somquo}
\integer{nbfact=2}
\integer{div=2}
#endif
\precision{10000}

\text{choix=randitem(\type)}
\text{don=slib(calcpuis \choix,8,10,100,\nbfact,\div)}
\text{eno=item(1,\don)}
\text{a=item(2,\don)}
\text{b=item(3,\don)}
\statement{\name_question:
<div class="wimscenter"><label for="reply1">\(\eno = \)</label>
  \embed{r1,10} <label for="reply2">\(\times 10\)</label><sup>\embed{r2,4}</sup></div>
}

\answer{\name_answer[1]}{\repa}{type=numexp}
\answer{name_answer[2]}{\repb}{type=numexp}

\real{test1=(\a)*10^((\b)-(\repb))-(\repa)}
\text{badform=/ isin \repa or * isin \repa or + isin \repa?yes:no}

\condition{\name_cond}{\test1=0 and \badform issametext no}

\solution{\(\eno = \a \times 10^{\b}\).}
