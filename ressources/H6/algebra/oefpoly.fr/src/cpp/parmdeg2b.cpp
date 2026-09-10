target=parmdeg2b

#include "header.inc"
#include "lang_titles.inc"

\integer{a=random(1..10)*random(-1,1)}
\integer{b=random(1..10)*random(-1,1)}
\integer{c=random(1..10)*random(-1,1)}
\integer{r=random(-5..5)}
\integer{u=random(2..5)*random(-1,1)}
\integer{v=random(2..5)*random(-1,1)}
\integer{w=random(2..5)*random(-1,1)}
\integer{s=(\r)^2*(\u)+(\r)*(\v)+(\w)}
\if{\s = 0}{
 \integer{w=\w+sign(\w)}
 \integer{s=(\r)^2*(\u)+(\r)*(\v)+(\w)}
}
\text{A=\a>0?+\a:\a}
\text{B=\b>0?+\b:\b}
\text{C=\c>0?+\c:\c}
\real{mm=-((\r)^2*(\a)+(\r)*(\b)+(\c))/(\s)}

#include "lang.inc"

\statement{\name_statement[1] \(m\) \name_statement[2]
<div class="wimscenter">
\((\u m\A)X^2 + (\v m\B)X + (\w m\C)\)
</div>
\name_statement[3] \(\r\)&nbsp;? (\name_statement[4] \(\u{}m\A \ne 0\).)}

\answer{\(m)}{\mm}
