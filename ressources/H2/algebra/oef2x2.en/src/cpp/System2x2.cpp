target=System2x2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}
\keywords{linear_system}
\integer{a1=3*random(-3..2)+random(1,2)}
\integer{b1=3*random(-3..2)+random(1,2)}
\integer{s=3*random(-3..2)+random(1,2)}
\integer{t=3*random(-3,-2,-1,1,2,3)}
\integer{v=random(0,1)}
\integer{a2=\v=0?\s:\t}
\integer{b2=\v=0?\t:\s}
\integer{x=random(-5..5)}
\integer{y=random(-5..5)}
\text{e1=texmath(\a1*x+\b1*y)}
\text{e2=texmath(\a2*x+\b2*y)}
\integer{c1=\a1*(\x)+(\b1)*(\y)}
\integer{c2=\a2*(\x)+(\b2)*(\y)}

\statement{\name_enonce[1] \(x\) \name_enonce[2] \(y\).
<div class="wimscenter">
	\(\left \lbrace \begin{array}{ccc}\e1&=&\c1
	\\\\
	\e2&=&\c2\end{array}\right .\)
</div>}

\answer{\(x\)}{\x}{type=default}
\answer{\(y\)}{\y}{type=default}

