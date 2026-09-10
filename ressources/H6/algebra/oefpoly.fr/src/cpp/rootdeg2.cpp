target=rootdeg2

#include "header.inc"
#include "lang_titles.inc"

\integer{mm=random(2..4)*random(1,-1)}
\integer{a=random(1..6)*random(-1,1)}
\integer{b=random(1..6)*random(-1,1)}
\integer{c2=\mm*(\a)^2}
\integer{c1=2*(\mm)*(\a)*(\b)}
\integer{move=random(1..30)*sign(\c2)}
\integer{c0=\mm*(\b)^2-(\move)}
\text{b=\c1>=0?+\c1:\c1}
\text{c=\c0>=0?+\c0:\c0}
\text{t1=\c1=0?:\b\X}

#include "lang.inc"

\statement{\name_statement1 \(r_1\),
\(r_2\) \name_statement2 <div class="wimscenter">
\(\c2 X^2 \t1 \c\).
</div>
<div class="wims_instruction">
\name_instruction</div>}

\answer{\(r_1\)}{\root1}
\answer{\(r_2\)}{\root2}

\condition{\(r_1\) \name_condition1}
{(\c2)*(\root1)^2+(\c1)*(\root1)=-(\c0)}
\condition{\(r_2\) \name_condition1}
{(\c2)*(\root2)^2+(\c1)*(\root2)=-(\c0)}
\condition{\name_condition2}
{-(\c2)*(\root1+(\root2))=\c1 and \c2*(\root1)*(\root2)=\c0}

