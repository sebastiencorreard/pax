target=oefcriterediv3

#include "css.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{nb1=randint(1..9)*100+(randint(0..4)*2+1)*10+randint(1..9)}
\integer{nb2=randint(1..9)*100+randint(1..49)*2}
\integer{nb3=randint(21..198)*5+randint(0..1)*randint(0..9)}
\text{unb1=wims(char -1 of pari(digits(\nb1,10)))}
\text{unb2=wims(char -1 of pari(digits(\nb2,10)))}
\text{unb3=wims(char -1 of pari(digits(\nb3,10)))}

#include "lang.inc"
\real{a1=\nb1/2}
\real{b1=ceil(\nb1/2)}
\real{a2=\nb2/5}
\real{b2=ceil(\nb2/5)}
\real{a3=\nb3/10}
\real{b3=ceil(\nb3/10)}
\text{reply_class=euler_quest_nobg,euler_quest_nobg,euler_quest_nobg}
\if{\a1=\b1}{\integer{rep1=1}}{\integer{rep1=2}}
\if{\a2=\b2}{\integer{rep2=1}}{\integer{rep2=2}}
\if{\a3=\b3}{\integer{rep3=1}}{\integer{rep3=2}}

\statement{
<ul class="wims_nopuce">
  <li class="\reply_class[1]">\name_quest[1] \(\nb1\) \name_quest[2] \(2\)&nbsp;? <span class="nowrap">\embed{r1}</span></li>
  <li class="\reply_class[2]">\name_quest[1] \(\nb2\) \name_quest[2] \(5\)&nbsp;? <span class="nowrap">\embed{r2}</span></li>
  <li class="\reply_class[3]">\name_quest[1] \(\nb3\) \name_quest[2] \(10\)&nbsp;? <span class="nowrap">\embed{r3}</span></li>
</ul>
}


\answer{}{\rep1;oui,non}{type=radio}
\answer{}{\rep2;oui,non}{type=radio}
\answer{}{\rep3;oui,non}{type=radio}

\text{score_reply=\sc_reply1,\sc_reply2,\sc_reply3}
\for{i=1 to 3}{\real{test=1-\score_reply[\i]}
                \if{\test>0}{\text{reply_class=wims(replace item number \i by euler_rep_bad_nobg cross in \reply_class)}}
                 {\text{reply_class=wims(replace item number \i by euler_rep_good_nobg tick in \reply_class)}}
              } 
\solution{
<ul>
  <li>\solu[1;1]<p>\solu[1;2] \(\nb1\) \solu[1;3] \(\unb1\) \solu[1;4] \(\nb1\) \benotbe[\rep1] \solu[1;5]</li>
  <li>\solu[2;1]<p>\solu[2;2] \(\nb2\) \solu[2;3] \(\unb2\) \solu[2;4] \(\nb2\) \benotbe[\rep2] \solu[2;5]</p></li>
  <li>\solu[3;1]<p>\solu[3;2] \(\nb3\) \solu[3;3] \(\unb3\) \solu[3;4] \(\nb3\) \benotbe[\rep3] \solu[3;5]</li>
</ul>
} 
