target=tworoots2
\keywords{roots}
#include "common.inc"
#include "lang_title.inc"

#include "lang.inc"

\text{choices=\real,\impur,\zero,\nor}
\integer{c=random(2..8)*random(-1,1)}
\text{C=\c>0?+\c:\c}
\integer{type=random(1,2)}
\text{I=\type=2?i:1}
\integer{type2=random(1,2)}
\text{dir=\type2=1?{>}100:{<}-100}
\text{good=\type2=1?\impur:\real}

\statement{\name_statement[1] \(z_1), \(z_2) \name_statement[2]
\(P(X)=X^2+\c*\I*X+q), \name_statement[3]
\(q\dir\) \name_statement[4] ____________.}

\choice{}{\good}{\choices}
