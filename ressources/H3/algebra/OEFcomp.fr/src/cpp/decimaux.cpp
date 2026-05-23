target=adddec,soudec,muldec2,divdec2,muldec1,divdec1
#include "header.inc"
#include "lang_titles.inc"
\real{v1=randint(101..999)/100}
\real{v2=randint(101..999)/100}
\real{v3=randint(1001..1999)/100}

#if defined TARGET_adddec
 \title{TITLE}
 \title_it{TITLE_it}
 \title_es{TITLE_es}
 \text{left=\v1 + \v3}
 \text{right=\v2 + \v3}
 \text{rep=\v1<\v2?1:2}
 \text{test=0}
#endif

#if defined TARGET_soudec
 \title{TITLE}
 \title_it{TITLE_it}
 \title_es{TITLE_es}
 \text{left=\v1 - \v3}
 \text{right=\v2 - \v3}
 \text{rep=\v1<\v2?1:2}
 \text{test=0}
#endif

#if defined TARGET_muldec1
 \title{TITRE 1}
 \title_it{TITRE_it 1}
 \title_es{TITRE_es 1}
 \text{left=\v1 * \v3}
 \text{right=\v2 * \v3}
 \text{rep=\v1<\v2?1:2}
 \text{test=0}
#endif

#if defined TARGET_muldec2
 \title{TITRE 2}
 \title_it{TITRE_it 2}
 \title_es{TITRE_es 2}
 \text{left=\v1 * (-\v3)}
 \text{right=\v2 * (-\v3)}
 \text{rep=\v1<\v2?2:1}
 \text{test=1}
#endif

#if defined TARGET_divdec1
 \title{TITLE 1}
 \title_it{TITLE_it 1}
 \title_es{TITLE_es 1}
 text{left=\v1 \char58 \v3}
 \text{left=\v1 \ : \ \v3}
 text{right=\v2 \char58 \v3}
 \text{right=\v2 \ : \ \v3}
 \text{rep=\v1<\v2?1:2}
 \text{test=0}
#endif

#if defined TARGET_divdec2
 \title{TITLE 2}
 \title_it{TITLE_it 2}
 \title_es{TITLE_es 2}
 text{left=\v1 \char58 (-\v3)}
 \text{left=\v1 \ : \ (-\v3)}
 text{right=\v2 \char58 (-\v3)}
 \text{right=\v2 \ : \ (-\v3)}
 \text{rep=\v1<\v2?2:1}
 \text{test=1}
#endif

\text{rep=\v1=\v2?3}
\matrix{sg=,
,-
-,
-,-}
\integer{chs=randint(1..4)}
\text{sg=row(\chs,\sg)}
\if{\rep!=3}{
 \if{\test=0}{
  \text{rep=\chs=2?2}
  \text{rep=\chs=3?1}
 }{
  \text{rep=\chs=2?1}
  \text{rep=\chs=3?2}
 }
 \text{rep=\chs=4?-\rep+3}
}
\text{left=\sg[1] \left}
\text{right=\sg[2] \right}
\text{list=<span class="larger"><</span>,<span class="larger">></span>,<span class="larger">=</span>}
\text{rep=item(\rep,\list)}
\text{eleft=texmath(\left)}
\text{eright=texmath(\right)}

#include "lang.inc"

\statement{
\tstatement
<div class="wimscenter">
 \(\eleft) \embed{r1,30x30x1} \(\eright)
</div>}

\answer{\tanswer}{\rep|\list}{type=clickfill}
