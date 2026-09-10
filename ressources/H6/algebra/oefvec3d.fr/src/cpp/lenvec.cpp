target=lenvec
#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"

\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=random(1..\range)*random(-1,1)}
\integer{b1=random(1..\range)*random(-1,1)}
\integer{c1=random(1..\range)*random(-1,1)}
\integer{l=random(1..\range)}
\real{lon=\l*sqrt((\a1)^2+(\b1)^2+(\c1)^2)}

\statement{\name_enonce[1] \(u=(\a1,\b1,\c1) ) \name_enonce[2] \l, \name_enonce[3]?
}

\answer{\name_answer}{\lon}
