target=oefcriterediv1

#include "css.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}



\matrix{reps=2,2
5,2
10,2}

\text{k=randint(1..3)}
\text{quest=item(1,row(\k,\reps))}
\text{rep=item(2,row(\k,\reps))}
\text{reply_class=euler_quest_nobg}
\statement{
<div class="\reply_class">\name_quest[1] \reps[\k;1], \name_quest[2] \embed{r1}.</div>
}

\answer{}{\rep;\name_props}{type=menu}
\integer{test=1-\sc_reply1}
\if{\test>0}{\text{reply_class=euler_rep_bad_nobg cross}}
            {\text{reply_class=euler_rep_good_nobg tick}}
