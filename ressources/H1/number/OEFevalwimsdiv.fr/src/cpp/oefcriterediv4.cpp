target=oefcriterediv4

#include "css.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\text{m=3,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97}
\text{m=shuffle(\m)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb1=2*\m[1]^\a*\m[2]^\b}
\text{unb1=wims(char -1 of pari(digits(\nb1,10)))}
\text{tnb1=slib(numeration/ecriturenombre \nb1,tex)}
\text{nb1=slib(numeration/ecriturenombre \nb1)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb2=5*\m[3]^\a*\m[4]^\b}
\text{unb2=wims(char -1 of pari(digits(\nb2,10)))}
\text{tnb2=slib(numeration/ecriturenombre \nb2,tex)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb3=10*\m[5]^\a*\m[6]^\b}
\text{unb3=wims(char -1 of pari(digits(\nb3,10)))}
\text{tnb3=slib(numeration/ecriturenombre \nb3,tex)}
\text{nb3=slib(numeration/ecriturenombre \nb3)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb4=\m[7]^\a*\m[8]^\b}
\text{tnb4=slib(numeration/ecriturenombre \nb4,tex)}
\text{nb4=slib(numeration/ecriturenombre \nb4)}

\text{rep=2,5,10,Aucun}
\text{list=\nb1,\nb2,\nb3,\nb4}

\statement{
Relier un nombre avec un diviseur possible de la liste :
<div class="wimscenter"> \embed{r1}</div>
}

\answer{}{\list;\rep}{type=correspond}
\solution{
<ul>
<li>\solu[1;1]<p>\(\tnb1\) \solu[1;2] \(\unb1\) \solu[1;3] \(\tnb1\) \solu[1;4]</p></li>
<li>\solu[2;1]<p>\(\tnb2\) \solu[2;2] \(\tnb2\) \solu[2;3]</p></li>
<li>\solu[3;1]<p>\(\tnb3\) \solu[3;2] \(\tnb3\) \solu[3;3]</p></li>
</ul>
\solu[4;1] \(\tnb4\) \solu[4;2]
}
