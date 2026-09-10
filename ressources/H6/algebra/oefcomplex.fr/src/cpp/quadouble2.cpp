target=quadouble2

#include "common.inc"
#include "lang_title.inc"

\text{aa=a}
\text{bb=b}
\integer{re=random(1..10)*random(-1,1)}
\integer{im=random(2..10)*random(-1,1)}
\integer{a=-2*(\re)}
\integer{b=-2*(\im)}
\text{B=\b>0?\b:\b}
\integer{Re=(\re)^2-(\im)^2}
\text{RE=\Re>=0?+\Re:\Re}
\integer{Im=2*(\re)*(\im)}
\text{IM=\Im>=0?+\Im:\Im}
\integer{type=random(1,2)}
\text{sola=item(\type,\b,\a)}
\text{a=item(\type,\a,\aa)}
\text{B=item(\type,\aa,\b)}
\text{iM=\im>=0?+\im:\im}

#include "lang.inc"

\statement{\name_statement[1] \(\aa\) \name_and \(\bb\)
\name_statement[2]
<div class="wimscenter">
\(X^2 +(\a+\B*i)X+\bb+\Im*i)
</div>
\name_statement[3]?
}

\answer{\(\aa)}{\sola}
\answer{\(\bb)}{\Re}
\answer{\name_answer}{\re\iM*i}

