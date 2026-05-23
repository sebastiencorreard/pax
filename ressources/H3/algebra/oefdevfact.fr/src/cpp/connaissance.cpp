target=connaissance1 connaissance2 connaissance3 connaissance4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{sg1=randitem(-,+)}
\text{sg2=randitem(-,+)}

#if defined TARGET_connaissance1
 \text{enonce=k*(a \sg1 b)}
 \text{list=k,a,b,+,-}
#endif
#if defined TARGET_connaissance2
 \text{enonce=(a \sg1 b)*(c \sg2 d)}
 \text{list=a,b,c,d,+,-}
#endif
#if defined TARGET_connaissance3
 \text{enonce=(a \sg1 b)^2}
 \text{list=a,b,+,-,2,^}
#endif
#if defined TARGET_connaissance4
 \text{enonce=randitem((a+b)*(a-b),(a-b)*(a+b))}
 \text{list=a,b,+,-,2,^}
#endif

\text{size=20x30x12}

\text{Aenonce=texmath(\enonce)}
\text{sol=\enonce}
\statement{\name_enonce:
<div class="wimscenter"><label for="reply1">\(\Aenonce =)</label> \embed{r1,\size}.</div>}

\answer{\(\Aenonce =\)}{\rep;\list}{type=clickfill}

\text{rep=wims(items2words \rep)}
\text{rep=wims(rawmath \rep)}
\text{tst=simplify(\rep-(\sol))}
\condition{\name_cond?}{\tst=0}
