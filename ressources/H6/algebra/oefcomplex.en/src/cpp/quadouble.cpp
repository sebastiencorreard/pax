target=quadouble

#include "common.inc"
#include "lang_titles.inc"

\integer{re=random(1..10)*random(-1,1)}
\integer{im=random(2..10)*random(-1,1)}
\integer{a=-2*(\re)}
\integer{b=-2*(\im)}
\text{B=\b>0?+\b:\b}
\integer{Re=(\re)^2-(\im)^2}
\integer{Im=2*(\re)*(\im)}
\text{IM=\Im>=0?+\Im:\Im}
\text{iM=\im>=0?+\im:\im}

#include "lang.inc"

\statement{\name_statement[1]
<div class="wimscenter">
\(X^2+(\a+\B*i)*X+w\)
</div>
\name_statement[2]?}

\answer{\(w\)}{\Re\IM*i}
\answer{\name_answer}{\re\iM*i}
