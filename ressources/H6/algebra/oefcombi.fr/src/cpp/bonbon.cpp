target=bonbon
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{girls=random(2..6)}
\integer{boys=random(2..6)}
\integer{children=\girls+\boys}
\integer{type=random(1..8)}
\integer{girlmin=item(\type,1,0,1,1,2,2,2,3)}
\integer{boymin =item(\type,0,1,1,2,1,2,3,2)}
\integer{correct=\girlmin*\girls+\boymin*\boys}
\text{method=item(\type, \name_method)}
\integer{dist=random(3..7)}
\integer{bonbons=\correct+\dist}
\integer{sol=binomial(\dist+\children-1,\dist)}

\statement{\name_question[1] \bonbons \name_question[2] \girls \name_question[3]
  \boys \name_question[4] \method&nbsp;?}

\answer{\name_answer}{\sol}
