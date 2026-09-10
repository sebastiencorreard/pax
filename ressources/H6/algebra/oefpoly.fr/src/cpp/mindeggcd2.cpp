target=mindeggcd2

#include "header.inc"
#include "lang_titles.inc"

#include "lang.inc"

\integer{n1=random(1..8)*random(0,0,1)}
\integer{n2=random(1..4)*2}
\integer{excess=\n1=0? random(1..20)*2:random(2..40)}
\integer{coef=random(1..100)}
\integer{seuil=36}
\text{ctext=\coef>\seuil?\name_type_list[1]:\name_type_list[2]}
\integer{deg=\n1+\n2+\excess}
\integer{test=\excess-\n1-\n2}
\integer{ans=\test>=0?\test:0}

\statement{\name_statement[1] \(P(x)\) \name_statement[2] \(\deg\)
\name_statement[3] \ctext\comma \name_statement[4]
\(\n1\) \name_statement[5] \(\n2\) \name_statement[6].
\name_statement[7] \(P''(x)\) \name_derivative \(P(x)\).
\name_question
\(\name_gcd (P(x),P''(x))\)&nbsp;?}

\answer{\name_answer deg(\name_gcd)}{\ans}
\hint{\name_hint}
