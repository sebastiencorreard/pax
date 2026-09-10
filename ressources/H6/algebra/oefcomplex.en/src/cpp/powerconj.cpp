target=powerconj

#include "common.inc"
#include "lang_titles.inc"

\integer{power=random(2..30)}
\integer{sol=\power+1}
\integer{ans=\sol+1}

#include "lang.inc"

\statement{\name_statement[1] \(z^\power\)
\name_statement[2]?}

\answer{\name_answer}{\ans}
\solution{\name_solution[1]
\(z^\power=w\) \name_solution[2] \(w=1/z\),
\name_solution[3]
\(X^{\sol} - 1\) \name_or 0.}
