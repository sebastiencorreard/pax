target=nn
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{tot=random(10..30)}
\integer{first=random(3..\tot-3)}
\integer{binom=binomial(\tot,\first)}

\statement{\name_enonce \(C_n^\first)=\binom. \name_question[1] \(n\)&nbsp;?}

\answer{\(n\)}{\tot}
