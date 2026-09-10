target=typesol
#include "lang_titles.inc"

\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\range{-5..5}
\precision{10000}
#include "lang.inc"
\integer{min=random(1,1,2,3,4,5)}
\integer{max=random(\min+1..\min+5)}
\integer{type=random(1,2,3)}
\integer{equs=item(\type,\min,\min,\max)}
\integer{vars=item(\type,\min,\max,\min)}
\integer{homo=random(0,1)}

\text{gene=\equs>1?\name_gene[1]:\name_gene[2]}
\text{nonnul=\equs>1?\name_nonnul[1]:\name_nonnul[1]}
\text{Homo=\homo=1?\gene:\name_not \gene}
\text{Equ=\equs>1?\name_Equ[1]:\name_Equ[2]}
\text{Var=\vars>1?variables:variable}
\text{gooda=\homo=0 and \equs>1?\yes:\no}
\text{goodb=\equs>=\vars?\yes:\no}
\text{goodc=\vars>1?\yes:\no}

\statement{
\name_question[1;1] \equs \Equ \Homo \name_question[1;2] \vars \Var. \name_question[2;]?
<ul><li>
A. \name_choice[1]
</li><li>
B. \name_choice[2]
</li><li>
C. \name_choice[3]
</li></ul>

<div class="wims_instruction">
\name_instruction
</div>
}

\choice{A \name_prompt}{\gooda}{\yes,\no}
\choice{B \name_prompt}{\goodb}{\yes,\no}
\choice{C \name_prompt}{\goodc}{\yes,\no}
