target=relrtdeg3

#include "header.inc"
#include "lang_titles.inc"

\range{0.2..5}

\integer{mm=random(2..10)*random(1,-1)}
\integer{nn=random(2..10)*random(1,-1)}
\integer{type=random(1,2,3)}
\text{m=\mm>0?+\mm:\mm}
\text{n=\nn>0?+\nn:\nn}
\text{c2=item(\type,\m,\m,+a)}
\text{c1=item(\type,\n,+a,\m)}
\text{c0=item(\type,+a,\n,\n)}
\real{cons1=item(\type,(\mm)^2-2*(\nn),(\mm)^2,2*(\mm))}
\function{ans1=item(\type,\cons1,\cons1-2*a,a^2-\cons1)}
\real{cons2=item(\type,-\nn,-\nn,-\mm/(\nn))}
\function{ans2=item(\type,\cons2/a,a/(\cons2),\cons2)}
\integer{qtype=random(1,2)}
\text{quest=item(\qtype,r_1^2+r_2^2+r_3^2,
	1/r_1+1/r_2+1/r_3)}
\text{ans=item(\qtype,\ans1,\ans2)}
\function{ans=\ans}

#include "lang.inc"

\statement{\name_statement1
<div class="wimscenter">
\(X^3 \c2 X^2 \c1 X \c0)&nbsp;,
</div>
\name_statement2
\(t = \quest)&nbsp;?
<div class="wims_instruction">\name_instruction \a.</div>}

\answer{\(t)}{\ans,a}{type=function}

