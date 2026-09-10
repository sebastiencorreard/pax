target=partfix

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{dist=random(3..10)}
\integer{parts=random(4..9)}
\integer{min=random(0..3)}
\integer{n=\dist+\min*\parts}
\text{order=randitem(\name_order)}
\integer{sol=binomial(\dist+\parts-1,\parts-1)}

\statement{\name_question[1;]
<div class="wimscenter">\(\n = n_1+n_2+...+n_(\parts))
</div>
\name_question[2;1] \min, \name_question[2;2] \order \name_question[2;3]?}

\answer{\name_answer}{\sol}
