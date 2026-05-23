target=3regles 3regles10 les3regles2
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_3regles || defined TARGET_3regles10
\text{type=quotient,inverse,produit,puissance}
\integer{confparm1=4}
#endif
#if defined TARGET_les3regles2
\integer{confparm1=3}
\text{type=quotient,inverse,produit}
#endif
\text{type=shuffle(\type)}
#if defined TARGET_3regles || defined TARGET_les3regles2
\text{listbase=wims(values v,-v for v=2 to 9)}
\text{listbase=shuffle(\listbase)}
#endif
\text{ltbase=}
\text{lteno=}
\text{ltsol=}
\text{st=}
\for{i=1 to \confparm1}{
  \text{choix=item(\i,\type)}
#if defined TARGET_3regles || defined TARGET_les3regles2
  \integer{base=item(\i,\listbase)}
  \text{don=slib(calcpuis \choix,8,\base)}
#endif
#if defined TARGET_3regles10
  \text{don=slib(calcpuis \choix,8)}
#endif
  \text{enonce=item(1,\don)}
  \text{rep=item(2,\don)}
  \text{lteno=wims(append item \enonce to \lteno)}
  \text{ltsol=wims(append item \rep to \ltsol)}
#if defined TARGET_3regles || defined TARGET_les3regles2
  \text{base=\base<0?(\base)}
  \text{ltbase=wims(append item \base to \ltbase)}
#endif
#if defined TARGET_3regles10
  \text{ltbase=wims(append item 10 to \ltbase)}
#endif
  \text{st=wims(append item r\i to \st)}
}
\steps{\st}
\statement{
\if{\confparm1=1}{\name_question[1]:
<div class="wimscenter"><label for="reply1">\(\lteno = \ltbase\)</label>
  <sup>\embed{r1,3}</sup>.</div>}
{\name_question[2]:
<ul>
 \for{k=1 to \confparm1}{
  <li><label for="reply\k">\(\lteno[\k] = \ltbase[\k])</label><sup>\embed{r\k,3}</sup>.</li>
  }
</ul>}
}
\answer{\(\lteno[1])}{\ltsol[1]}{type=numexp}
\answer{\(\lteno[2])}{\ltsol[2]}{type=numexp}
\answer{\(\lteno[3])}{\ltsol[3]}{type=numexp}
\answer{\(\lteno[4])}{\ltsol[4]}{type=numexp}
\answer{\(\lteno[5])}{\ltsol[5]}{type=numexp}
