target=rootcoef
\keywords{roots}
#include "common.inc"
#include "lang_title.inc"

\integer{im=random(1..20)*random(-1,1)}
\integer{sq=(\im)^2}

#include "lang.inc"

\statement{\name_statement1 \(\im\). \name_statement2}

\answer{\(q)}{\sq+0.25*p^2}
\solution{\name_solution[1] \(z=a+\im*i), \name_solution[2] \(w=a-\im*i).
\name_solution[3] \(p=-2a), \name_solution[4] \(a=-0.5*p).
\name_solution[5] \(q=z*w=a^2+(\im)^2=(\im)^2+0.25*p^2).}
