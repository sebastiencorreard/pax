target=pentaroot
\keywords{roots}
#include "common.inc"
#include "lang_title.inc"

\integer{type=random(1,2)}
\integer{power=\type=1?5*random(20..99)+random(1..4):5*random(20..99)}
\integer{sol=\type=1?-1:4}

#include "lang.inc"

\statement{\name_statement[1] \(z_1), \(z_2), \(z_3), \(z_4) \name_statement[2]
\(X^4 +X^3 +X^2 +X+1). \name_statement[3]
\(w=z_1^\power+z_2^\power+z_3^\power+z_4^\power) ?}

\answer{\(Re(w))}{\sol}
\answer{\(Im(w))}{0}
