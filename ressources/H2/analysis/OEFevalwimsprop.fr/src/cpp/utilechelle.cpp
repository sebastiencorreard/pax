target=utilechelle2 utilechelle3 utilechelle4 utilechelle5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_utilechelle2
 \integer{E=randitem(100,200,250,400,500,1000)}
 \integer{l=randint(5..10)}
 \real{rep=\l*\E/100}
 \statement{\name_question:
<div class="wimscenter">\name_enonce[1] \(\frac{1}{\E}),
\l centimètres \name_enonce[2] \embed{r1,8} \name_enonce[3]</div>}
\answer{\name_answer[1]}{\rep}{type=numexp}
#endif
#if defined TARGET_utilechelle3
 \integer{E=randitem(100000,200000,250000,400000)}
 \integer{l=randint(5..10)}
 \real{rep=\l*\E/100000}
 \statement{
\name_question:
<div class="wimscenter">\name_enonce[1] \(\frac{1}{\E}), \rep
\name_enonce[2] \embed{r1,8} \name_enonce[3] </div>}
\answer{\name_answer[1]}{\l}{type=numexp}
#endif
#if defined TARGET_utilechelle4
 \text{name=slib(lang/fname boy,fr)}
 \integer{E=randitem(10,20,25,40)}
 \real{rep=randint(250/\E..450/\E)}
 \integer{l=\rep*\E}
\statement{
\name \name_enonce[1] \(\frac{1}{\E}) \name_enonce[2] \l \name_enonce[3]
<p>
\name_question?
</p>
<b>\name_answer[2]</b> : \embed{r1,5} cm.}
\answer{\name_answer[1]}{\rep}{type=numexp}
#endif
#if defined TARGET_utilechelle5
 \text{name=slib(lang/fname boy,fr)}
 \integer{E=randitem(50000,250000,200000,100000)}
 \integer{l=randint(15..25)}
 \real{rep=\l*\E/100000}
\statement{
\name \name_enonce \(\frac{1}{\E}).<p>
\name_enonce2[1] \name_enonce2[2] \l \name_enonce2[3]</p><p>
\name_question?</p>

<b>\name_answer[2]</b> : \embed{r1,5} Km.}
\answer{\name_answer[1]}{\rep}{type=numexp}
#endif
