target=quotientdiv produitdiv inversediv quprindiv puispuissance

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_quotientdiv
\text{type=quotient}
#endif
#if defined TARGET_quprindiv
\text{type=quotient,inverse,produit}
#endif
#if defined TARGET_produitdiv
\text{type=produit}
#endif
#if defined TARGET_puispuissance
\text{type=puissance}
#endif
#if defined TARGET_inversediv
\text{type=inverse}
#endif

\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>5?5}

\text{listbase=wims(values v,-v for v=2 to 9)}
\text{listbase=shuffle(\listbase)}

\text{lteno=}
\text{ltsol=}
\text{ltbase=}
\text{st=}
\for{i=1 to \confparm1}{
  \text{choix=randitem(\type)}
  \integer{base=item(\i,\listbase)}
  \text{don=slib(calcpuis \choix,8,\base)}
  \text{enonce=item(1,\don)}
  \text{rep=item(2,\don)}
  \text{lteno=wims(append item \enonce to \lteno)}
  \text{ltsol=wims(append item \rep to \ltsol)}
  \text{base=\base<0?(\base)}
  \text{ltbase=wims(append item \base to \ltbase)}
  \text{st=wims(append item r\i to \st)}
}

\steps{\st}

\statement{
\if{\confparm1=1}{\name_question[1]:
<div class="wimscenter"><label for="reply1">
\(\lteno\)</label> = \(\ltbase\)<sup>\embed{r1,3}</sup>.</div>}{
  \name_question[2]:
<ul>
 \for{k=1 to \confparm1}{
  <li><label for="reply\k">\(\lteno[\k]\)</label> =
    \(\ltbase[\k]\)<sup>\embed{r\k,3}</sup>.</li>
  }
</ul>}
}

\answer{\(\lteno[1])}{\ltsol[1]}{type=numexp}
\answer{\(\lteno[2])}{\ltsol[2]}{type=numexp}
\answer{\(\lteno[3])}{\ltsol[3]}{type=numexp}
\answer{\(\lteno[4])}{\ltsol[4]}{type=numexp}
\answer{\(\lteno[5])}{\ltsol[5]}{type=numexp}
