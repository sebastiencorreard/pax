target=givderiv

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
\integer{n1=random(1..4)}
\integer{n2=random(1..4)}
\integer{m1=\n1+1}
\integer{m2=\n2+1}
\integer{c=random(1..4)*random(-2,2)}
\text{N1=\n1=1?:^\n1}
\text{N2=\n2=1?:^\n2}
\function{sol=\c*(x+\a1)^\m1*(x+\a2)^\m2}
\real{r=random(0.5,1.5)*random(-1,1)}
\real{b=evalue(\sol,x=\r)}

#include "lang.inc"

\statement{\name_statement[1] \(P(X)) \name_statement[2]:
<ul>
 <li>\(\name_gcd (P(X),P'(X)) = (X\A1)\N1(X\A2)\N2)&nbsp;, \name_statement[3]
 	\(P'(X)) \name_statement[4] \(P(X))&nbsp;;
 </li><li>\(P(\r)=\b)&nbsp;;
 </li><li>\name_statement[5] \(P(X)) \name_statement[6].
 </li>
</ul>
<div class="wims_instruction">
\name_instruction[1].
\name_instruction[2] <span class="tt">x^3</span> \name_instruction[3] \(X^3), \name_andsoon.
</div>
}

\answer{\(P(X))}{\sol}
