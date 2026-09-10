target=rerootdeg2

#include "header.inc"
#include "lang_titles.inc"

\integer{c2=random(2..25)*random(1,-1)}
\integer{c1=random(2..25)*random(-1,1)}
\text{C1=\c1>0?+\c1:\c1}
\real{ans=-0.5*(\c1)/(\c2)}

#include "lang.inc"

\statement{\name_statement[1] \(P(X) = \c2 X^2 \C1 X + b\)
\name_statement[2]\comma \name_statement[3].
\name_statement[4] \(r\)&nbsp;?}

\answer{\(Re(r)\)}{\ans}

