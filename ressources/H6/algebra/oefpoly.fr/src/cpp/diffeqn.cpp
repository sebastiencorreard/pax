target=diffeqn

#include "header.inc"
#include "lang_titles.inc"

\range{-2..2}

\text{ll1=-2,-2,-2,-2,-1,-1,-1,+0,+0,+1}
\text{ll2=-1,+0,+1,+2,+0,+1,+2,+1,+2,+2}
\integer{ss=random(1,2)}
\text{l1=\ss=1?\ll1:\ll2}
\text{l2=\ss=1?\ll2:\ll1}
\integer{n=items(\l1)}
\integer{shuffle=random(1..\n)}
\text{a1=item(\shuffle,\l1)}
\text{a2=item(\shuffle,\l2)}
\text{A1=\a1=+0?:\a1}
\text{A2=\a2=+0?:\a2}
\integer{c3=random(1..10)*random(-1,1)}
\integer{c2=random(-10..10)}
\integer{c1=random(-10..10)}
\integer{c0=random(-10..10)}
\integer{d2=3*(\c3)*(\a1-(\a2))}
\integer{d1=3*(\c3)*((\a1)^2-(\a2)^2)+2*(\c2)*(\a1-(\a2))}
\integer{d0=\c3*((\a1)^3-(\a2)^3)+(\c2)*((\a1)^2-(\a2)^2)+(\c1)*(\a1-(\a2))}
\text{D1=\d1>=0?+\d1:\d1}
\text{D0=\d0>=0?+\d0:\d0}
\integer{r=random(-5..5)}
\integer{b=\c3*(\r)^3+(\c2)*(\r)^2+(\c1)*(\r)+(\c0)}
\function{\sol=\c3*x^3+\c2*x^2+\c1*x+\c0}

#include "lang.inc"

\statement{\name_statement[1] \(P( X)\) \name_statement[2]
<div class="wimscenter">
  \(P( X\A1)- P( X\A2) = \d2 X^2\D1 X\D0\)
</div>
\name_statement[3] \(P(\r)=\b\).
<div class="wims_instruction">\name_instruction[1] <span class="tt">x^3</span> \name_instruction[2] \(X^3\), \name_andsoon.</div>
}

\answer{ P( X)}{\sol}

