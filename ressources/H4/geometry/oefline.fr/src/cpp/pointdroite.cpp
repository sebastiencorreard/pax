target=pointdroite

#include "header.inc"
#include "lang_titles.inc"

\keywords{lines}
\integer{a=random(1,-1)*randint(2..5)}
\integer{b=randint(1..8)}
\rational{x=randint(-100..100)/10}
\rational{y=simplify(\a*\x+\b)}

#include "lang.inc"

\statement{\name_statement[1;]
    \(y=\a x + b\).
    \name_statement[2;]
    \((\x,\y)\)
    \name_statement[3;]?}

\answer{\(b\)= }{\b }{type= numeric}
