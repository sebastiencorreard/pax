target=degmult

#include "header.inc"
#include "lang_titles.inc"

text{X=X}
\text{i=i}
\integer{m1=random(2..8)}
\integer{m2=random(2..8)}
\integer{a1=random(1..10)*random(-1,1)}
\integer{b1=random(2..10)*random(-1,1)}
\text{B1=\b1>0?+\b1:\b1}
\integer{type=random(1,2,3,4)}
\integer{a2=\type=4?-\a1:random(1..10)*random(-1,1)}
\integer{a2=\type=2?\a1}
\integer{b2=\type=2?-\b1:random(2..10)*random(-1,1)}
\integer{b2=\type=4?\b1*random(-1,1)}
\integer{a2=\type!=1 and \a1=\a2 and \b1=\b2? \a2+sign(\a2)}
\text{B2=\b2>0?+\b2:\b2}
\text{r2=\type=1?\a2:\a2\B2\i}

\integer{d=\type=1?\m1*2+\m2:\m1*2+\m2*2}
\integer{d=\a1=\a2 and \b1=-(\b2) and \m1!=\m2?-1}
\integer{d=\a1=\a2 and \b1=-(\b2) and \m1=\m2?\m1+\m2}
\integer{coef=random(1..100)}
\integer{d=\coef<=35?\m1+\m2}

#include "lang.inc"

\text{ctext=\coef>35?\name_type_list[1]:\name_type_list[2]}

\statement{\name_statement[1] \(P(x)\) \name_statement[2] \ctext
	   \name_statement[3]:<ul>
 <li> \(\a1\B1\i\) \name_request1 \(\m1\)&nbsp;;</li>
 <li>\(\r2\) \name_request2 \(\m2\)&nbsp;?</li>
</ul>
<div class="wims_instruction">
\name_instruction[1] <span class="tt">-1</span> \name_instruction[2].
</div>}

\answer{\name_answer}{\d}
