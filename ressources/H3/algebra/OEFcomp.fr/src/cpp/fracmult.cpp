target=mult1A,mult1B,mult1C,mult2A,mult2B,mult2C,div1A,div1B,div1C,div2A,div2B,div2C
#include "header.inc"
#include "lang_titles.inc"

\text{v=wims(values v for v=2 to 15)}
\text{v=shuffle(\v)}

#if defined TARGET_mult1A
 \title{TITRE 1A}
 \title_it{TITRE_it 1A}
  \title_es{TITRE_es 1A}
 \text{left=\frac{\v[1]}{\v[2]}\times\frac{\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[2]}\times\frac{\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?1:2}
 \text{test=0}
#endif

#if defined TARGET_mult1B
 \title{TITRE 1B}
 \title_it{TITRE_it 1B}
 \title_es{TITRE_es 1B}
 \text{left=\frac{\v[2]}{\v[1]}\times\frac{\v[3]}{\v[4]}}
 \text{right=\frac{\v[2]}{\v[5]}\times\frac{\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?2:1}
 \text{test=0}
#endif

#if defined TARGET_mult1C
 \title{TITRE 1C}
 \title_it{TITRE_it 1C}
 \title_es{TITRE_es 1C}
 \text{left=\frac{\v[1]}{\v[2]}\times\frac{\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[6]}\times\frac{\v[3]}{\v[4]}}
 \text{rep=\v[1]*\v[6]<\v[5]*\v[2]?1:2}
 \text{rep=\v[1]*\v[6]=\v[5]*\v[2]?3}
 \text{test=0}
#endif

#if defined TARGET_mult2A
 \title{TITRE 2A}
 \title_it{TITRE_it 2A}
 \title_es{TITRE_es 2A}
 \text{left=\frac{\v[1]}{\v[2]}\times\frac{-\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[2]}\times\frac{-\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?2:1}
 \text{test=1}
#endif

#if defined TARGET_mult2B
 \title{TITRE 2B}
 \title_it{TITRE_it 2B}
 \title_es{TITRE_es 2B}
 \text{left=\frac{\v[2]}{\v[1]}\times\frac{-\v[3]}{\v[4]}}
 \text{right=\frac{\v[2]}{\v[5]}\times\frac{-\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?1:2}
 \text{test=1}
#endif

#if defined TARGET_mult2C
 \title{TITRE 2C}
 \title_it{TITRE_it 2C}
 \title_es{TITRE_es 2C}
 \text{left=\frac{\v[1]}{\v[2]}\times\frac{-\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[6]}\times\frac{-\v[3]}{\v[4]}}
 \text{rep=\v[1]*\v[6]<\v[5]*\v[2]?2:1}
 \text{rep=\v[1]*\v[6]=\v[5]*\v[2]?3}
 \text{test=1}
#endif

#if defined TARGET_div1A
 \title{TITR2 1A}
 \title_it{TITR2_it 1A}
 \title_es{TITR2_es 1A}
 \text{left=\frac{\v[1]}{\v[2]} : \frac{\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[2]} : \frac{\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?1:2}
 \text{test=0}
#endif

#if defined TARGET_div1B
 \title{TITR2 1B}
 \title_it{TITR2_it 1B}
 \title_es{TITR2_es 1B}
 \text{left=\frac{\v[2]}{\v[1]} : \frac{\v[3]}{\v[4]}}
 \text{right=\frac{\v[2]}{\v[5]} : \frac{\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?2:1}
 \text{test=0}
#endif

#if defined TARGET_div1C
 \title{TITR2 1C}
 \title_it{TITR2_it 1C}
 \title_es{TITR2_es 1C}
 \text{left=\frac{\v[1]}{\v[2]} : \frac{\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[6]} : \frac{\v[3]}{\v[4]}}
 \text{rep=\v[1]*\v[6]<\v[5]*\v[2]?1:2}
 \text{rep=\v[1]*\v[6]=\v[5]*\v[2]?3}
 \text{test=0}
#endif

#if defined TARGET_div2A
 \title{TITR2 2A}
 \title_it{TITR2_it 2A}
 \title_es{TITR2_es 2A}
 \text{left=\frac{\v[1]}{\v[2]} : \frac{-\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[2]} : \frac{-\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?2:1}
 \text{test=1}
#endif

#if defined TARGET_div2B
 \title{TITR2 2B}
 \title_it{TITR2_it 2B}
 \title_es{TITR2_es 2B}
 \text{left=\frac{\v[2]}{\v[1]} : \frac{-\v[3]}{\v[4]}}
 \text{right=\frac{\v[2]}{\v[5]} : \frac{-\v[3]}{\v[4]}}
 \text{rep=\v[1]<\v[5]?1:2}
 \text{test=1}
#endif

#if defined TARGET_div2C
 \title{TITR2 2C}
 \title_it{TITR2_it 2C}
 \title_es{TITR2_es 2C}
 \text{left=\frac{\v[1]}{\v[2]} : \frac{-\v[3]}{\v[4]}}
 \text{right=\frac{\v[5]}{\v[6]} : \frac{-\v[3]}{\v[4]}}
 \text{rep=\v[1]*\v[6]<\v[5]*\v[2]?2:1}
 \text{rep=\v[1]*\v[6]=\v[5]*\v[2]?3}
 \text{test=1}
#endif


\matrix{sg=,
,-
-,
-,-}

\integer{chs=randint(1..4)}
\text{sg=row(\chs,\sg)}
\if{\test=0}{
  \text{rep=\chs=2?2}
  \text{rep=\chs=3?1}
}{
  \text{rep=\chs=2?1}
  \text{rep=\chs=3?2}
}
\text{rep=\chs=4 and \rep!=3?-\rep+3}
\text{left=\sg[1]\left}
\text{right=\sg[2]\right}

\text{list=<span class="larger"><</span>,<span class="larger">></span>,<span class="larger">=</span>}
\text{rep=item(\rep,\list)}

#include "lang.inc"

\statement{
\tstatement
<div class="wimscenter">
 \(\left) \embed{r1,30x30x1} \(\right)
</div>}

\answer{\tanswer}{\rep|\list}{type=clickfill}
