target=vocabulaire5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{M=randitem(A,B,C,D,E,F,M,N)}
\text{p=wims(values v,-v for v=1 to 10)}
\text{p=shuffle(\p)}
\integer{ch=randitem(1,2)}
\text{type=\ch=1?\name_type[1]:\name_type[2]}
\integer{rep=\ch=1?\p[1]:\p[2]}

\statement{
\name_enonce[1] \M \name_enonce[2] (\p[1];\p[2]) \name_enonce[3]
\name_question[1]\type \name_question[2] \M ?}

\answer{\type}{\rep}{type=numexp}
