target=tripledeg3

#include "header.inc"
#include "lang_titles.inc"


\integer{c1=random(1..10)*random(1,-1)}
\integer{c2=random(2..20)}
\real{tolerance=0.001}

#include "lang.inc"

\statement{\name_statement[1] \(a\) \name_and \(b\) \name_statement[2]
<div class="wimscenter">
\(P(X) = X^3 + \c2 a X^2 + b X + (\c1-a)\)
</div>
\name_statement[3]&nbsp;?}

\answer{a}{\aa}
\answer{b}{\bb}
\answer{\name_answer \(r\)}{\r}

\condition{\(r\) \name_condition}
{abs(\c2*(\aa)+3*(\r))<\tolerance and
abs(\bb-3*(\r)^2)<\tolerance and
abs(\c1-(\aa)+(\r)^3)<\tolerance}

\hint{\name_hint1
<div class="wimscenter">\(\c2\a=-3 r\) (\name_where \(\a=-(3/\c2) r\)),
\(b=3 r^2\), \name_and
<p>
\(-r^3=\c1-\a=\c1+(3/\c2) r\).</p>
</div>\(r\) 
\name_hint2 \(\c1+(3/\c2)X+ X^3\).
}
