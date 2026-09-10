target=rootcnt

#include "header.inc"
#include "lang_titles.inc"


\text{X=<i>X</i>}
\text{i=<i>i</i>}
\integer{n1=random(1..8)*random(0,1)}
\integer{n2=random(1..4)*2}
\integer{excess=\n1=0? random(1..10)*2:random(2..20)}
\integer{deg=\n1+\n2+\excess}
\integer{coef=random(1..100)}
\integer{seuil=46}

#include "lang.inc"

\text{ctext=\coef>\seuil?\name_type_list[1]:\name_type_list[2]}

\statement{\name_statement[1] \(P(x)) \name_statement[2] \(\deg\)
\name_statement[3] \ctext\comma
\name_statement[4] \(P'(x)) \name_statement[5] \(P(x)).
\name_statement[6] \(\name_gcd (P(x),P'(x))\) \name_statement[7]
\(\excess\).
\name_question[1] <span class="wims_emph">\name_question[2]</span> \name_question[3] \name_of \(P(x))&nbsp;?
(\name_note)}

\answer{\name_answer}{\n1+\n2}
\hint{\name_hint}

