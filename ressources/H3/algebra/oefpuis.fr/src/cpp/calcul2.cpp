target=produit quotient quoprod produit2 somme1 somme2 somme3 somme4 somquo1 somquo2
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_produit
\text{type=produitcp}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_somme1
\text{type=somme}
\integer{nbfact=2}
\integer{div=0}
#endif
#if defined TARGET_somme3
\text{type=somme}
\integer{nbfact=2}
\integer{div=2}
#endif
#if defined TARGET_somme4
\text{type=somme}
\integer{nbfact=3}
\integer{div=0}
#endif
#if defined TARGET_somme2
\text{type=somme}
\integer{nbfact=3}
\integer{div=2}
#endif
#if defined TARGET_produit2
 \text{type=produitcp}
 \integer{nbfact=3}
 \integer{div=0}
#endif
#if defined TARGET_quotient
 \text{type=quotientcp}
 \integer{nbfact=2}
 \integer{div=0}
#endif
#if defined TARGET_quoprod
 \text{type=quotientcp,produitcp}
 \integer{nbfact=2}
 \integer{div=0}
#endif
#if defined TARGET_somquo1
 \text{type=somquo}
 \integer{nbfact=2}
 \integer{div=0}
#endif
#if defined TARGET_somquo2
 \text{type=somquo}
 \integer{nbfact=2}
 \integer{div=2}
#endif

\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>5?5}

\text{lteno=}
\text{ltsol=}
\text{ltpuis=}
\text{st=}
\text{st2=}
\for{i=1 to \confparm1}{
 \text{choix=randitem(\type)}
 \text{don=slib(calcpuis \choix,8,10,100,\nbfact,\div)}
 \text{enonce=item(1,\don)}
 \text{rep=item(2,\don)}
 \text{puis=item(3,\don)}
 \text{lteno=wims(append item \enonce to \lteno)}
 \text{ltsol=wims(append item \rep to \ltsol)}
 \text{ltpuis=wims(append item \puis to \ltpuis)}
 \text{st=wims(append item r\i to \st)}
 \integer{k=\i+5}
 \text{st2=wims(append item r\k to \st2)}
}

\steps{\st,\st2}
\statement{
\if{\confparm1=1}{\name_question1:
<div class="wimscenter"><label for="reply1">
\(\lteno[1] = \)</label> \embed{r1,10}
<label for="reply6">\(\times 10)</label><sup>\embed{r6,4}</sup></div>}
{\name_question2:
<ul>
  <li><label for="reply1">\(\lteno[1] = \)</label> \embed{r1,10}
    <label for="reply6">\(\times 10)<sup>\embed{r6,4}</sup>.</li>
  <li><label for="reply2">\(\lteno[2] = \)</label> \embed{r2,10}
    <label for="reply7">\(\times 10)<sup>\embed{r7,4}</sup>.</li>
\if{\confparm1>2}{
  <li><label for="reply3">\(\lteno[3] = \)</label> \embed{r3,10}
    <label for="reply8">\(\times 10)</label><sup>\embed{r8,4}</sup>.</li>}
\if{\confparm1>3}{
  <li><label for="reply4">\(\lteno[4] = \)</label> \embed{r4,10}
    <label for="reply9">\(\times 10)</label><sup>\embed{r9,4}</sup>.</li>}
\if{\confparm1>4}{
    <li><label for="reply5">\(\lteno[5] = \) </label>\embed{r5,10}
    <label for="reply10">\(\times 10)</label><sup>\embed{r10,4}</sup>.</li>}
</ul>}
}

\answer{1}{\ltsol[1]}{type=numexp}
\answer{2}{\ltsol[2]}{type=numexp}
\answer{3}{\ltsol[3]}{type=numexp}
\answer{4}{\ltsol[4]}{type=numexp}
\answer{5}{\ltsol[5]}{type=numexp}
\answer{1}{\ltpuis[1]}{type=numexp}
\answer{2}{\ltpuis[2]}{type=numexp}
\answer{3}{\ltpuis[3]}{type=numexp}
\answer{4}{\ltpuis[4]}{type=numexp}
\answer{5}{\ltpuis[5]}{type=numexp}
