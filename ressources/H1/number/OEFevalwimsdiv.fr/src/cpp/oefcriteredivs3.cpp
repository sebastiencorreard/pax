target=oefcriteredivs3

#include "css.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{nb1=randint(34..330)*3+randint(0..9)}
\integer{nb2=randint(1..9)*100+randint(1..49)*2}
\integer{nb3=randint(12..110)*9+random(0,3,5)}

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

\real{a1=\nb1/3}
\real{b1=ceil(\nb1/3)}
\real{a2=\nb2/4}
\real{b2=ceil(\nb2/4)}
\real{a3=\nb3/9}
\real{b3=ceil(\nb3/9)}

\if{\a1=\b1}{\integer{rep1=1}}{\integer{rep1=2}}
\if{\a2=\b2}{\integer{rep2=1}}{\integer{rep2=2}}
\if{\a3=\b3}{\integer{rep3=1}}{\integer{rep3=2}}

\text{reply_class=euler_quest_nobg,euler_quest_nobg,euler_quest_nobg}
\statement{
<ul class="wims_nopuce">
  <li class="\reply_class[1]">\name_quest[1] \(\nb1\) \name_quest[2] \(3\)&nbsp;? \embed{r1}</li>
  <li class="\reply_class[2]">\name_quest[1] \(\nb2\) \name_quest[2] \(4\)&nbsp;? \embed{r2}</li>
  <li class="\reply_class[3]">\name_quest[1] \(\nb3\) \name_quest[2] \(9\)&nbsp;? \embed{r3}</li>
</ul>
}

\answer{}{\rep1;\name_rep}{type=radio}
\answer{}{\rep2;\name_rep}{type=radio}
\answer{}{\rep3;\name_rep}{type=radio}

\text{score=\sc_reply1,\sc_reply2,\sc_reply3}
\for{i=1 to 3}{\real{test=1-\score[\i]}
                \if{\test>0}{\text{reply_class=wims(replace item number \i by euler_rep_bad_nobg cross in \reply_class)}}
                 {\text{reply_class=wims(replace item number \i by euler_rep_good_nobg tick in \reply_class)}}
                 } 
\solution{
<ul>
<li>\solu[1;1]<p>\solu[1;2] \(\nb1\) \solu[1;3] \somnb1 \solu[1;4] \benotbe[\rep1] \solu[1;5] \(\nb1\) \benotbe[\rep1] \solu[1;6]</p></li>
<li>\solu[2;1]<p>\solu[2;2] \(\nb2\) \solu[2;3] \(\last2nb2\last1nb2\) \solu[2;4] \benotbe[\rep2] \solu[2;5] \(\nb2\) \benotbe[\rep2] \solu[2;6]</p></li>
<li>\solu[3;1]<p>\solu[3;2] \(\nb3\) \solu[3;3] \somnb3 \solu[3;4] \benotbe[\rep3] \solu[3;5] \(\nb3\) \benotbe[\rep3] \solu[3;6]</p></li>
</ul>
}
