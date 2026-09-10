target=oefcriteredivs2

#include "css.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}


\text{reps=0,0,1,0,1,0,0,0,0,1,1,1,0,0,0,1,1,1}

\text{k=randint(1..6),6+randint(1..6),12+randint(1..6)}

\text{prop=}
\text{rep=}
\text{reply_class=}
\for{a=1 to 3}
      {\text{p=item(\k[\a],\props)}
      \text{prop=wims(append item \p to \prop)}
      \integer{r=item(\k[\a],\reps)}
      \text{rp= \r=1? 1:2}
      \text{rep=wims(append item \rp to \rep)}
      \text{reply_class=wims(append item euler_quest_nobg to \reply_class)}
}

\statement{
<strong>\name_quest</strong>
<ul>
<li class="wims_nopuce \reply_class[1]">\prop[1] : \embed{r1}</li>
<li class="wims_nopuce \reply_class[2]">\prop[2] : \embed{r2}</li>
<li class="wims_nopuce \reply_class[3]">\prop[3] : \embed{r3}</li>
</ul>
}


\answer{}{\rep[1];\name_rep}{type=menu}
\answer{}{\rep[2];\name_rep}{type=menu}
\answer{}{\rep[3];\name_rep}{type=menu}
\text{score=\sc_reply1,\sc_reply2,\sc_reply3}
\for{i=1 to 3}{\integer{test=1-\score[\i]}
                \if{\test>0}{\text{reply_class=wims(replace item number \i by euler_rep_bad_nobg cross in \reply_class)}}
                 {\text{reply_class=wims(replace item number \i by euler_rep_good_nobg tick in \reply_class)}}
                 }
\solution{
<ul>
<li>\props[3].</li>
<li>\props[10].</li>
<li>\props[16].</li>
</ul>
}
