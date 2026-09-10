target=oefcriteredivs5

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

\text{digitnb1=pari(digits(\nb1,10))}
\text{sumnb1=pari(sumdigits(\nb1))}
\text{somnb1=wims(replace internal , by + in \digitnb1)}
\text{somnb1=\(\somnb1 = \sumnb1\)} 
\text{last2nb1=wims(char -3 of \digitnb1)}
\text{last1nb1=wims(char -1 of \digitnb1)}
\text{tnb1=slib(numeration/ecriturenombre \nb1,tex)}
\text{nb1=slib(numeration/ecriturenombre \nb1)}

\real{a1=\nb1/3}
\real{b1=ceil(\nb1/3)}
\real{a2=\nb1/4}
\real{b2=ceil(\nb1/4)}
\real{a3=\nb1/9}
\real{b3=ceil(\nb1/9)}

\if{\a1=\b1}{\integer{rep1=1}}{\integer{rep1=2}}
\if{\a2=\b2}{\integer{rep2=1}}{\integer{rep2=2}}
\if{\a3=\b3}{\integer{rep3=1}}{\integer{rep3=2}}

\statement{
\name_quest[1] \(\tnb1\) \name_quest[2]&nbsp;?
<table class="wimscenter wimsborder">
<tr><td>\name_quest[3] 3 </td><td>\name_quest[3] 4</td><td>\name_quest[3] 9</td></tr>
<tr><td>\embed{r1}</td><td>\embed{r2}</td><td>\embed{r3}</td></tr>
</table>}

\answer{}{\rep1;\name_rep}{type=menu}
\answer{}{\rep2;\name_rep}{type=menu}
\answer{}{\rep3;\name_rep}{type=menu}

\solution{
<ul>
  <li>\solu[1;1]<p>\somnb1 \solu[1;2] \(\sumnb1\) \solu[1;3] \(\tnb1\) \benotbe[\rep1] \solu[1;4]</p></li>
  <li>\solu[2;1]<p>\solu[2;2] \(\tnb1\) \solu[2;3] \(\last2nb1\last1nb1\) \solu[2;4] \(\last2nb1\last1nb1\) \benotbe[\rep2] \solu[2;5]\(\tnb1\) \benotbe[\rep2] \solu[2;6]</p></li>
  <li>\solu[3;1]<p>\somnb1 \solu[3;2] \(\sumnb1\) \benotbe[\rep3] \solu[3;3] \(\tnb1\) \benotbe[\rep3] \solu[3;4]</p></li>
</ul>
}
