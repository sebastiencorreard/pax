target=oefformpave3 oefformpave4

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

#if defined TARGET_oefformpave3
\integer{lo=randint(2..9)}
\integer{la=randint(2..\lo)}
\integer{h=randint(2..9)}
\integer{res=\lo*\la*\h}
#endif
#if defined TARGET_oefformpave4
\integer{lo=randint(14..99)}
\integer{la=randint(11..\lo)}
\integer{h=randint(11..99)}
\integer{res=\lo*\la*\h}
#endif
\text{enonc1=wims(replace internal XXXX by \lo in \name_enonce)}
\text{enonc1=wims(replace internal YYYY by \la in \enonc1)}
\text{enonc1=wims(replace internal ZZZZ by \h in \enonc1)}

\statement{
\enonc1
<div class="wims_question">
<label for="reply1">\name_enonce2</label>
<div class="wimscenter">\embed{r1,7} \(\textrm{cm}^3).</div>
</div>
<div class="wims_instruction">
\name_voc[1]=\name_voc[2] \(\times) \name_voc[3] \(\times) \name_voc[4]
</div>

}

\answer{}{\res}{type=numeric}
