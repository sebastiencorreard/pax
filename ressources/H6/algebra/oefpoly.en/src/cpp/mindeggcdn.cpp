target=mindeggcdn

#include "header.inc"
#include "lang_titles.inc"

#include "lang.inc"

\integer{n1=random(1..8)*random(0,0,1)}
\integer{n2=random(1..4)*2}
\integer{n=random(2..6)}
\integer{excess=\n1=0? random(\n..30)*2:random(2*\n..60)}
\integer{coef=random(1..100)}
\integer{seuil=36}
\text{ctext=\coef>\seuil?\name_type_list[1]:\name_type_list[2]}
\integer{deg=\n1+\n2+\excess}
\integer{test=\deg-\n*(\n1+\n2)}
\integer{ans=\test>=0?\test:0}


\statement{\name_statement[1] \(P(x)\) \name_statement[2] \deg
\name_statement[3] \ctext
\name_statement[4] \n1 \name_statement[5] \n2 \name_statement[6].
\name_statement[7] \(P^{(\n)}(x)\)
\name_derivative[1] \n \name_derivative[2] \(P(x)\).
\name_question
\(\name_gcd (P(x),P^{(\n)}(x))\)&nbsp;?}

\answer{\name_answer deg(\name_gcd)}{\ans}

