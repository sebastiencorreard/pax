target=maxmod

#include "common.inc"
#include "lang_titles.inc"

\integer{a=random(-20..20)}
\integer{b=random(2..20)*random(-1,1)}
\real{mod=sqrt((\a)^2+(\b)^2)}
\integer{modz=random(1..99)}
\integer{type=random(1,2)}
\real{sol=item(\type,\mod+\modz,abs(\mod-\modz))}

#include "lang.inc"

\text{mum=item(\type,\name_list_maxmin)}

\statement{\name_statement[1] \mum \name_statement[2] \(|\a+\b*i+z |\),
  \name_statement[3] \(|z|= \modz\\)&nbsp;?}

\answer{\mum \name_answer}{\sol}
