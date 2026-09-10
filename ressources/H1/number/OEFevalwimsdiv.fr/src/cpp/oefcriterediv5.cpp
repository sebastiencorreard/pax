target=oefcriterediv5

#include "css.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{div=2,3,4,5,7,9,10,11,13,15,18}
\text{div=shuffle(\div)}
\integer{k=randint(1..3)}
\integer{nb1=1}
\for{i=1 to \k}
{\integer{nb1=\nb1*\div[\k]}}
\integer{test=500-\nb1}
\if{\test>0}
{\integer{nb1=\nb1*\div[4]}}
\integer{test=500-\nb1}
\if{\test>0}
{\integer{nb1=\nb1*\div[5]}}
\integer{test=500-\nb1}
\if{\test>0}
{\integer{nb1=\nb1+300}}
\text{unb1=wims(char -1 of pari(digits(\nb1,10)))}
\text{tnb1=slib(numeration/ecriturenombre \nb1,tex)}
\text{nb1=slib(numeration/ecriturenombre \nb1)}

\real{a1=\nb1/2}
\real{b1=ceil(\nb1/2)}
\real{a2=\nb1/5}
\real{b2=ceil(\nb1/5)}
\real{a3=\nb1/10}
\real{b3=ceil(\nb1/10)}

\if{\a1=\b1}{\integer{rep1=1}}{\integer{rep1=2}}
\if{\a2=\b2}{\integer{rep2=1}}{\integer{rep2=2}}
\if{\a3=\b3}{\integer{rep3=1}}{\integer{rep3=2}}

\statement{
\name_quest[1] \(\tnb1\) \name_quest[2]&nbsp;?
<table class="wimscenter wimsborder">
<tr><td>\name_quest[3] 2 </td><td>\name_quest[3] 5</td><td>\name_quest[3] 10</td></tr>
<tr><td>\embed{r1}</td><td>\embed{r2}</td><td>\embed{r3}</td></tr>
</table>}

\answer{}{\rep1;\name_rep}{type=menu}
\answer{}{\rep2;\name_rep}{type=menu}
\answer{}{\rep3;\name_rep}{type=menu}

\solution{
<ul>
  <li>\solu[1;1]<p>\(\tnb1\) \solu[1;2] \(\unb1\) \solu[1;3] \(\tnb1\) \benotbe[\rep1] \solu[1;4]</p></li>
  <li>\solu[2;1]<p>\(\tnb1\) \solu[2;2] \(\unb1\) \solu[2;3] \(\tnb1\) \benotbe[\rep2] \solu[2;4]</p></li>
  <li>\solu[3;1]<p>\(\tnb1\) \solu[3;2] \(\unb1\) \solu[3;3] \(\tnb1\) \benotbe[\rep3] \solu[3;4]</p></li>
</ul>
} 
