target=oefmentaldiv1 oefmentaldiv2 oefmentaldiv3 oefmentaldiv4 oefmentaldiv5

\keywords{division, mental_calculation}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"

#if defined TARGET_oefmentaldiv1
\integer{nb1=randint(2..5)}
\integer{nb2=randint(3..9)}
#endif
#if defined TARGET_oefmentaldiv2
\integer{nb1=randint(6..9)}
\integer{nb2=randint(3..9)}
#endif
#if defined TARGET_oefmentaldiv3
\integer{nb1=2}
\integer{nb2=randint(0..4)*100+randint(4..9)*10+randint(1..9)}
#endif
#if defined TARGET_oefmentaldiv4
\integer{nb1=randint(3..6)}
\integer{nb2=randint(12..100/\nb1)}
#endif
#if defined TARGET_oefmentaldiv5
\integer{nb1=random(3,5)}
\if{\nb1=3}{\integer{nb2=200+randint(1..9)*10+randint(2..9)}}
{\integer{nb2=100+randint(1..9)*10+randint(2..9)}}
#endif

\integer{res=\nb1*\nb2}
\text{reply_class=euler_quest_nobg}

\statement{
<div class="\reply_class">
  \name_question:
  <div class="wimscenter">
     <label for="reply1">\(\res \div \nb1 =\)</label> \embed{r1}
  </div>
</div>}

\answer{}{\repel}

\text{repel=wims(replace internal * by in \repel)}
\text{repel=wims(replace internal , by . in \repel)}
\real{repel=pari(\repel)}

\condition{\name_cond}{\repel issametext \nb2}
\if{\repel=\nb2}{\text{reply_class=euler_rep_good_nobg tick}}{\text{reply_class=euler_rep_bad_nobg cross"}}
\solution{\(\res \div \nb1 =\nb2\)}
