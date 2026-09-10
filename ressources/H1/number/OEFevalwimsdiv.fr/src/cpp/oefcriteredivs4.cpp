target=oefcriteredivs4

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\precision{10000}

\text{m=5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97}
\text{m=shuffle(\m)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb1=3*\m[1]^\a*\m[2]^\b}
\text{tnb1=slib(numeration/ecriturenombre \nb1,tex)}
\text{nb1=slib(numeration/ecriturenombre \nb1)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb2=4*\m[3]^\a*\m[4]^\b}


\text{tnb2=slib(numeration/ecriturenombre \nb2,tex)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb3=9*\m[5]^\a*\m[6]^\b}
\text{tnb3=slib(numeration/ecriturenombre \nb3,tex)}
\text{nb3=slib(numeration/ecriturenombre \nb3)}

\integer{a=randint(1..2)}
\integer{b=randint(0..1)}
\integer{nb4=\m[7]^\a*\m[8]^\b}
\text{tnb4=slib(numeration/ecriturenombre \nb4,tex)}
\text{nb4=slib(numeration/ecriturenombre \nb4)}

\text{digitnb1=pari(digits(\nb1,10))}
\text{sumnb1=pari(sumdigits(\nb1))}
\text{somnb1=wims(replace internal , by + in \digitnb1)}
\text{somnb1=\(\somnb1 = \sumnb1\)} 

\text{digitnb2=pari(digits(\nb2,10))}
\text{last2nb2=wims(char -3 of \digitnb2)}
\text{last1nb2=wims(char -1 of \digitnb2)}

\text{digitnb3=pari(digits(\nb3,10))}
\text{sumnb3=pari(sumdigits(\nb3))}
\text{somnb3=wims(replace internal , by + in \digitnb3)}
\text{somnb3=\(\somnb3 = \sumnb3\)} 

\text{rep=3,4,9,Aucun}
\text{list=\nb1,\nb2,\nb3,\nb4}

\statement{
\name_quest&nbsp;:
<div class="wimscenter"> \embed{r1}</div>
}

\answer{}{\list;\rep}{type=correspond}
\solution{
<ul>
<li>\solu[1;1]<p>\somnb1 \solu[1;2] \(\sumnb1\) \solu[1;3] \(\tnb1\) \solu[1;4]</p></li>
<li>\solu[2;1]<p>\(\tnb2\) \solu[2;2] \(\last2nb2\last1nb2\) \solu[2;3] \(\last2nb2\last1nb2\) \solu[2;4] \(\tnb2\) \solu[2;5]</p></li>
<li>\solu[3;1]<p>\somnb3 \solu[3;2] \(\sumnb3\) \solu[3;3] \(\tnb3\) \solu[3;4]</p></li>
</ul>
\solu[4;1]<p>\(\tnb4\) \solu[4;2]
}
