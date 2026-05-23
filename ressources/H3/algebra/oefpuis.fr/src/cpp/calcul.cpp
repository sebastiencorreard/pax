target=quotient10 produit10 inverse10 quprin10 puispuis10

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_quotient10
\text{type=quotient}
#endif
#if defined TARGET_quprin10
\text{type=quotient,inverse,produit}
#endif
#if defined TARGET_produit10
\text{type=produit}
#endif
#if defined TARGET_puispuis10
 \text{type=puissance}
#endif
#if defined TARGET_inverse10
\text{type=inverse}
#endif
\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>5?5}

\text{lteno=}
\text{ltsol=}
\text{st=}
\for{i=1 to \confparm1}{
  \text{choix=randitem(\type)}
  \text{don=slib(calcpuis \choix,8)}
  \text{enonce=item(1,\don)}
  \text{rep=item(2,\don)}
  \text{lteno=wims(append item \enonce to \lteno)}
  \text{ltsol=wims(append item \rep to \ltsol)}
  \text{st=wims(append item r\i to \st)}
}

\steps{\st}
\statement{
\if{\confparm1=1}{
 \name_question[1]:
  <div class="wimscenter">
  <label for="reply1">\(\lteno = 10\)</label><sup>\embed{r1,2}</sup>.</div>
  }{
  \name_question[2]:
<ul>
 \for{k=1 to \confparm1}{
  <li><label for="reply\k">\(\lteno[\k] = 10\)</label><sup>\embed{r\k,3}</sup>.</li>
  }
</ul>}
}


\answer{\(\lteno[1]\)}{\ltsol[1]}{type=numexp}
\answer{\(\lteno[2]\)}{\ltsol[2]}{type=numexp}
\answer{\(\lteno[3]\)}{\ltsol[3]}{type=numexp}
\answer{\(\lteno[4]\)}{\ltsol[4]}{type=numexp}
\answer{\(\lteno[5]\)}{\ltsol[5]}{type=numexp}
