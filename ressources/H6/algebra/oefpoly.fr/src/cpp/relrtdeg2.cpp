target=relrtdeg2

#include "header.inc"
#include "lang_titles.inc"


\integer{mm=random(2..20)*random(1,-1)}
\integer{type=random(1,2)}
\text{m=\mm>0?+\mm:\mm}
\text{c1=item(\type,\m,+a)}
\text{c0=item(\type,+a,\m)}
\integer{const=item(\type,(\mm)^2,2*(\mm))}
\function{ans=item(\type,\const-2*a,a^2-\const)}



#include "lang.inc"

\statement{\name_statement1
<div class="wimscenter">
\(X^2 \c1 X \c0)
</div>
\name_statement2
\(t=r_1^2+r_2^2)&nbsp;?
<div class="wims_instruction">\name_instruction \a.</div>}

\answer{\(t)}{\ans,a}{type=function}

\hint{\name_hint1 \(r_1^2+r_2^2 =
(r_1+r_2)^2-2r_1r_2). \name_hint2.}

