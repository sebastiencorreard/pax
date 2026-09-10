target=tripledeg3b

#include "header.inc"
#include "lang_titles.inc"

\integer{c1=random(1..10)*random(1,-1)}
\integer{c2=random(2..10)*random(1,-1)}
\integer{c3=random(2..10)*random(1,-1)}
\text{C2=\c2>0?+\c2:\c2}
\text{C3=\c3>0?+\c3:\c3}
\real{tolerance=0.001}

#include "lang.inc"

\statement{\name_statement[1] \(a\) \name_and \(b\) \name_statement[2]
<div class="wimscenter">
\(P(X) = X^3 \C2 a X^2 \C3 b X +(\c1+ a+b)\)
</div>
\name_statement[3]?
<div class="wims_instruction">\name_instruction</div>}

\answer{\(a)}{\aa}
\answer{\(b)}{\bb}
\answer{\name_answer \(r\)}{\r}

\condition{\(r\) \name_condition}
{abs((\c2)*(\aa)+3*(\r))<\tolerance and
abs((\c3)*(\bb)-3*(\r)^2)<\tolerance and
abs(\c1+(\aa)+(\bb)+(\r)^3)<\tolerance}

