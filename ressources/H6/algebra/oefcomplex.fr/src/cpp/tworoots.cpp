target=tworoots
\keywords{roots}
#include "common.inc"
#include "lang_title.inc"

#include "lang.inc"

\text{choices=\real,\impur,\zero,\nor}
\integer{type=random(1,2)}
\text{p=item(\type,\real,\impur)}
\text{good=item(\type,\impur,\real)}

\statement{\name_statement[1] \(z_1 ), \(z_2) \name_statement[2]
\(P(X)=X^2 + p X+ q), \name_statement[3] \p \name_statement[4] ____________.}

\choice{}{\good}{\choices}
