target=subsets
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{tot=random(10..25)}
\integer{first=random(3..6)}
\integer{binom=binomial(\tot,\first)}

\statement{\name_enonce[1] \binom \name_enonce[2] \first \name_enonce[3]?}
\answer{|\(S\)|}{\tot}
