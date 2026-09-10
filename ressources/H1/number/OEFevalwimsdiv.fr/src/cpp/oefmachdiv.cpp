target=oefmachdiv1 oefmachdiv2 oefmachdiv3 oefmachdiv4 oefmachdiv5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\precision(1000000)

#if defined TARGET_oefmachdiv1 || defined TARGET_oefmachdiv2
#if defined TARGET_oefmachdiv1
\integer{nb2=randint(11..99)}
\integer{q=randint(11..99)}
#endif
#if defined TARGET_oefmachdiv2
\integer{nb2=randint(110..990)}
\integer{q=randint(1100..9900)}
#endif
\integer{nb1=\nb2*\q}
\integer{res=\q}
\text{nb1=slib(numeration/ecriturenombre \nb1,comma tex)}
\text{nb2=slib(numeration/ecriturenombre \nb2,comma tex)}
\text{tres=slib(numeration/ecriturenombre \res,comma tex)}
\text{t=\name_t}
\text{enonc=\(\nb1 \div \nb2 =\)}
\integer{l=10}
\solution{\(\nb1 \div \nb2 = \tres\)}
#endif

#if defined TARGET_oefmachdiv3
\integer{nb2=randint(110..990)}
\integer{q=randint(1..9)*1000+randint(1..9)*100+randint(1..9)*10+randint(1..9)}
\integer{e=randint(1..5)}
\real{q=\q/10^\e}
\real{nb1=\nb2*\q}
\real{res=\q}
\text{nb1=slib(numeration/ecriturenombre \nb1,comma tex)}
\text{nb2=slib(numeration/ecriturenombre \nb2,comma tex)}
\text{tres=slib(numeration/ecriturenombre \res,comma tex)}
\text{t=\name_quot}
\text{enonc=\(\nb1 \div \nb2 =\)}
\solution{\(\nb1 \div \nb2 = \tres\)}
\integer{l=10}
#endif
#if defined TARGET_oefmachdiv4
\integer{nb2=randint(11..99)}
\integer{q=randint(11..99)}
\integer{plusq=\q+1}
\integer{r=randint(1..\nb2-1)}
\integer{nb1=\nb2*\q+\r}
\integer{temp1=\nb2*\q}
\integer{temp2=\plusq*\nb2}
\integer{res=\r}
\text{nb1=slib(numeration/ecriturenombre \nb1,tex)}
\text{nb2=slib(numeration/ecriturenombre \nb2,tex)}
\text{temp1=slib(numeration/ecriturenombre \temp1,comma tex)}
\text{temp2=slib(numeration/ecriturenombre \temp2,comma tex)}
\text{tq=slib(numeration/ecriturenombre \q,tex)}
\text{plusq=slib(numeration/ecriturenombre \plusq,tex)}
\text{t=\name_t[1] \(\nb1\) \name_t[2] \(\nb2\)}
\text{enonc=\name_enon[1] \(\nb1\) \name_enon[2] \(\nb2\) \name_enon[3]}
\integer{l=10}
#include "probsol.inc"
\solution{\name_sol}
#endif
#if defined TARGET_oefmachdiv5
\integer{nb2=randint(110..990)}
\integer{q=randint(1100..9900)}
\integer{r=randint(1..\nb2-1)}
\integer{plusq=\q+1}
\integer{nb1=\nb2*\q+\r}
\integer{temp1=\q*\nb2}
\integer{temp2=\nb2*\plusq}
\integer{res=\r}
\text{nb1=slib(numeration/ecriturenombre \nb1,tex)}
\text{nb2=slib(numeration/ecriturenombre \nb2,tex)}
\text{temp1=slib(numeration/ecriturenombre \temp1,comma tex)}
\text{temp2=slib(numeration/ecriturenombre \temp2,comma tex)}
\text{plusq=slib(numeration/ecriturenombre \plusq,tex)}
\text{tq=slib(numeration/ecriturenombre \q,tex)}
\text{t=\name_t[1] \(\nb1\) \name_t[2] \(\nb2\)}
\text{enonc=\name_enon[1] \(\nb1\) \name_enon[2] \(\nb2\) \name_enon[3]}
\integer{l=10}
#include "probsol.inc"
\solution{\name_sol}
#endif

\text{reply_class=euler_quest_nobg}
\statement{
<div class="\reply_class">
\name_question[1] \t \name_question[2]:
  <div class="wimscenter">
     <label for="reply1">\enonc</label> \embed{r1,\l}.
  </div>
</div>
}

\answer{}{\repel}
\text{repel=wims(replace internal * by in \repel)}
\text{repel=wims(replace internal , by . in \repel)}
\real{repel=pari(\repel)}

\condition{\name_cond}{\repel issametext \res}
\if{\repel=\res}{\text{reply_class=euler_rep_good_nobg tick}}{\text{reply_class=euler_rep_bad_nobg cross"}}
