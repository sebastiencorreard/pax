target=somalg1 somalg2 somalg3

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{sign=+,-,random(+,-),random(+,-),random(+,-)}
\text{sign=shuffle(\sign)}
\text{\s=\sign[1]}

#if defined TARGET_somalg1
\title{TITRE 1 (guidé)}
\text{ETAPE=r1,r2
r3}
\steps{\ETAPE}
\text{oper=random(+,+),random(+,+),random(+,+),random(+,+)}
\for{k=2 to 5}{
\if{\oper[\k-1]=\sign[\k]}{\text{\s=\s,+}}{\text{\s=\s,-}}}
\text{nb=shuffle(9)}
\text{res=\sign[1]\nb[1]}
\for{j=2 to 5}{\text{res=\res,\oper[\j-1](\sign[\j] \nb[\j])}}
\real{\rp=\res[1]+\res[2]+\res[3]+\res[4]+\res[5]}
\real{bilanpos=0}
\real{bilanmoins=0}
\text{solupos=}
\text{solumoins=}
\for{z=1 to 5}{
\if{\sign[\z]=+}{\real{bilanpos=\sign[\z]\nb[\z]+\bilanpos}
\text{solupos=\solupos,(\sign[\z]\nb[\z])}}
{\real{bilanmoins=\sign[\z]\nb[\z]+\bilanmoins}
\text{solumoins=\solumoins,(\sign[\z]\nb[\z])}}}
\text{solupos=wims(nonempty  item \solupos)}
\text{tsolupos=wims(replace internal , by \plus in \solupos)}
\text{solumoins=wims(nonempty  item \solumoins)}
\text{tsolumoins=wims(replace internal , by \plus in \solumoins)}

\statement{On veut calculer l'expression&nbsp;:
<p><span class="nowrap">\(A=\)
\for{i=1 to 5}{\(( \sign[\i] \nb[\i] ) \oper[\i]\)}.</span></p>

\if{\step=1}{<b class="underline">Étape 1&nbsp;:</b> Calculer les sommes suivantes&nbsp;:
<ul>
<li><label for="reply1">La somme des nombres positifs&nbsp;: </label>\embed{r1,3}.</li>
<li><label for="reply2">La somme des nombres négatifs&nbsp;: </label>\embed{r2,3}.</li>
</ul>}
\if{\step=2}{\( A = \left( + \bilanpos \right) + \left( \bilanmoins \right)\)
<p><b class="underline">Étape 2&nbsp;:</b> Conclure</p>
<label for="reply3">\( A=\)</label>\embed{r3,3}.}}

\solution{\(A=( \sign[1] \nb[1] ) \oper[1] ( \sign[2] \nb[2] ) \oper[2] ( \sign[3] \nb[3] ) \oper[3] ( \sign[4] \nb[4] ) \oper[4] ( \sign[5] \nb[5] )\)
<p>\(A=\tsolupos + \tsolumoins\)
<ul><li>La somme des nombres positifs est <span class="nowrap">\( \tsolupos = \bilanpos \).</span></li>
<li>La somme des nombres négatifs est <span class="nowrap">\( \tsolumoins = \bilanmoins \).</span></li></ul>
<p>Ainsi,</p>
\(A=( \sign[1] \nb[1] ) \oper[1] ( \sign[2] \nb[2] ) \oper[2] ( \sign[3] \nb[3] ) \oper[3] ( \sign[4] \nb[4] ) \oper[4] ( \sign[5] \nb[5] )\)
<p>\(A=\tsolupos + \tsolumoins\)</p>
\( A = ( + \bilanpos ) + ( \bilanmoins )\)
<p>\( A= \rp\)</p>}
#endif
#if defined TARGET_somalg2 || defined TARGET_somalg3
\text{oper=random(+,-),random(+,-),random(+,-),random(+,-)}
\for{k=2 to 5}{
\if{\oper[\k-1]=\sign[\k]}{\text{\s=\s,+}}{\text{\s=\s,-}}}
\text{nb=shuffle(9)}
\text{res=\s[1]\nb[1]}
\for{j=2 to 5}{\text{res=\res,\s[\j] \nb[\j]}}
\real{\rp=\res[1]+\res[2]+\res[3]+\res[4]+\res[5]}
\real{bilanpos=0}
\real{bilanmoins=0}
\text{tbilanpos=}
\text{tbilanmoins=}
\for{z=1 to 5}{
\if{\s[\z]=+}{\real{bilanpos=\res[\z]+\bilanpos}
\text{tbilanpos=\tbilanpos,(\res[\z])}}
{\real{bilanmoins=\res[\z]+\bilanmoins}
\text{tbilanmoins=\tbilanmoins,(\res[\z]),}}}
\text{tbilanpos=wims(nonempty  item \tbilanpos)}
\text{tbilanpos=wims(replace internal , by \plus in \tbilanpos)}
\text{tbilanmoins=wims(nonempty  item \tbilanmoins)}
\text{tbilanmoins=wims(replace internal , by \plus in \tbilanmoins)}
#endif
#if defined TARGET_somalg2
\title{TITRE 2 (guidé)}
\text{ETAPE=r1,r2,r3,r4,r5
r6,r7
r8}
\steps{\ETAPE}
\statement{On veut calculer l'expression&nbsp;:
<p>\(A=( \sign[1] \nb[1] ) \oper[1] ( \sign[2] \nb[2] ) \oper[2] ( \sign[3] \nb[3] ) \oper[3] ( \sign[4] \nb[4] ) \oper[4] ( \sign[5] \nb[5] )\)</p>
\if{\step=1}{<p><b class="underline">Étape 1&nbsp;:</b> Transformer chaque soustraction en addition de l'opposé.</p>
\special{mathmlinput [A=( reply1 ) + (reply2) + (reply3) + (reply4) + (reply5)], 3
reply1
reply2
reply3
reply4
reply5}}
\if{\step=2}{\(A=(\res[1])+(\res[2])+(\res[3])+(\res[4])+(\res[5])\)
<p><b class="underline">Étape 2&nbsp;:</b> Calculer les sommes suivantes&nbsp;:</p>
<ul>
<li><label for="reply6">La somme des nombres positifs&nbsp;: </label>\embed{r6,3}.</li>
<li><label for="reply7">La somme des nombres négatifs&nbsp;: </label>\embed{r7,3}.</li>
</ul>}
\if{\step=3}{\(A=(\res[1])+(\res[2])+(\res[3])+(\res[4])+(\res[5])\)
<p>\( A = ( + \bilanpos ) + ( \bilanmoins )\)</p>
<p><b class="underline">Étape 3&nbsp;:</b> Conclure</p>
<label for="reply8">\(A=\)</label> \embed{r8,3}.}}
\answer{}{\res[1]}{type=numexp}
\answer{}{\res[2]}{type=numexp}
\answer{}{\res[3]}{type=numexp}
\answer{}{\res[4]}{type=numexp}
\answer{}{\res[5]}{type=numexp}
#endif
#if defined TARGET_somalg3
\title{TITRE}
\statement{Calculer l'expression&nbsp;:
<p><span class="nowrap">\(A=\)
\for{i=1 to 5}{\(( \sign[\i] \nb[\i] ) \oper[\i]\)}.</span></p>
<div class="wims_instruction">Vous pouvez écrire des calculs intermédiaires sur une feuille.</div>
<label for="reply1">\( A=\)</label>\embed{r1,3}.}
#endif
#if defined TARGET_somalg1 || defined TARGET_somalg2
\answer{Somme des nombres positifs}{\bilanpos}{type=numexp}
\answer{Somme des nombres négatifs}{\bilanmoins}{type=numexp}
#endif
\answer{A}{\rp}{type=numexp}
#if defined TARGET_somalg2 || defined TARGET_somalg3
\solution{\(A=( \sign[1] \nb[1] ) \oper[1] ( \sign[2] \nb[2] ) \oper[2] ( \sign[3] \nb[3] ) \oper[3] ( \sign[4] \nb[4] ) \oper[4] ( \sign[5] \nb[5] )\)
<p>On transforme chaque soustraction en addition de l'opposé.</p>
\(A=(\res[1])+(\res[2])+(\res[3])+(\res[4])+(\res[5])\)
<p>On effectue la somme des nombres positifs et la somme des nombres négatifs.</p>
\(A = \tbilanpos + \tbilanmoins \)
<p>\( A = ( + \bilanpos ) + ( \bilanmoins )\)</p>
On conclut
<p>\( A= \rp\)</p>}
#endif
#if defined TARGET_somalg2 || TARGET_somalg3
\hint{Pour calculer une somme algébrique, on procède dans cet ordre&nbsp;:
<ol><li>On transforme chaque soustraction en addition de l'opposé.</li>
<li>On effectue la somme des nombres positifs et la somme des nombres négatifs.</li>
<li>On conclut.</li></ol>}
#endif
#if defined TARGET_somalg1
\hint{Pour calculer une somme algébrique, on effectue la somme des nombres positifs et la somme des nombres négatifs puis on conclut.}
#endif
