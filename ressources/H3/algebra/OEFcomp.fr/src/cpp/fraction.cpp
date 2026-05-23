target=additionA,additionB,additionC,soustractionA,soustractionB,soustractionC

#include "header.inc"
#include "lang_titles.inc"

\text{v=wims(values v for v=2 to 15)}
\text{v=shuffle(\v)}

#if defined TARGET_additionA
 \title{TITLE A}
 \title_it{TITLE_it A}
 \title_es{TITLE_es A}
 \text{left=\v[1]/\v[2] + \v[3]/\v[4]}
 \text{right=\v[5]/\v[2] + \v[3]/\v[4]}
 \text{rep=\v[1]<\v[5]?1:2}
#endif

#if defined TARGET_additionB
 \title{TITLE B}
 \title_it{TITLE_it B}
 \title_es{TITLE_es B}
 \text{left=\v[2]/\v[1] + \v[3]/\v[4]}
 \text{right=\v[2]/\v[5] + \v[3]/\v[4]}
 \text{rep=\v[1]<\v[5]?2:1}
#endif

#if defined TARGET_additionC
 \title{TITLE C}
 \title_it{TITLE_it C}
 \title_es{TITLE_es C}
 \text{left=\v[1]/\v[2] + \v[3]/\v[4]}
 \text{right=\v[5]/\v[6] + \v[3]/\v[4]}
 \text{rep=\v[1]*\v[6]<\v[5]*\v[2]?1:2}
 \text{rep=\v[1]*\v[6]=\v[5]*\v[2]?3}
#endif

#if defined TARGET_soustractionA
 \title{TITLE A}
 \title_it{TITLE_it A}
 \title_es{TITLE_es A}
 \text{left=\v[1]/\v[2] - \v[3]/\v[4]}
 \text{right=\v[5]/\v[2] - \v[3]/\v[4]}
 \text{rep=\v[1]<\v[5]?1:2}
#endif

#if defined TARGET_soustractionB
 \title{TITLE B}
 \title_it{TITLE_it B}
 \title_es{TITLE_es B}
 \text{left=\v[2]/\v[1] - \v[3]/\v[4]}
 \text{right=\v[2]/\v[5] - \v[3]/\v[4]}
 \text{rep=\v[1]<\v[5]?2:1}
#endif

#if defined TARGET_soustractionC
 \title{TITLE C}
 \title_it{TITLE_it C}
 \title_es{TITLE_es C}
 \text{left=\v[1]/\v[2] - \v[3]/\v[4]}
 \text{right=\v[5]/\v[6] - \v[3]/\v[4]}
 \text{rep=\v[1]*\v[6]<\v[5]*\v[2]?1:2}
 \text{rep=\v[1]*\v[6]=\v[5]*\v[2]?3}
#endif

\matrix{sg=+,+
+,-
-,+
-,-}
\integer{chs=randint(1..4)}
\text{sg=row(\chs,\sg)}
\if{\rep!=3}{
 \text{rep=\chs=2?2}
 \text{rep=\chs=3?1}
 \text{rep=\chs=4?-\rep+3}
}
\text{left=\sg[1]\left}
\text{right=\sg[2]\right}

#include "lang.inc"

\text{list=<span class="larger"><</span>,<span class="larger">></span>,<span class="larger"2>=</span>}
\text{rep=item(\rep,\list)}
\text{eleft=texmath(\left)}
\text{eright=texmath(\right)}

\statement{
\tstatement
<div class="wimscenter">
 \(\eleft) \embed{r1,30x30x1} \(\eright)
</div>}

\answer{\tanswer}{\rep|\list}{type=clickfill}
