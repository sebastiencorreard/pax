target=sumroot
\keywords{roots}
#include "common.inc"
#include "lang_titles.inc"

text{i=<i>i</i>}
\integer{n=random(6,6,3,5,7)}
\integer{minus=\n-1}
\integer{denom=\n=6?3:\n}
\integer{a=\n=3?random(2,4)}
\integer{a=\n=5?random(2,4,6,8)}
\text{a=\n=6?random(,-,5,7)}
\integer{a=\n=7?random(2,4,6,8,10,12)}
\integer{b=random(1..10)}
\text{b1=\b>1?\b:}
\integer{b2=\b+1}
\integer{b3=\b+2}
\integer{b4=\b+3}
\integer{b5=\b+4}
\integer{b6=\b+5}
\integer{b7=\b+6}
\text{sum=\n=3?w^{\b1}+w^{\b2}+w^{\b3}}
\text{sum=\n=5?w^{\b1}+w^{\b2}+w^{\b3}+w^{\b4}+w^{\b5}}
\text{sum=\n=6?w^{\b1}+w^{\b2}+w^{\b3}+w^{\b4}+w^{\b5}+w^{\b6}}
\text{sum=\n=7?w^{\b1}+w^{\b2}+w^{\b3}+w^{\b4}+w^{\b5}+w^{\b6}+w^{\b7}}
\text{addit=\n=3?X^2 +X+1:X^\minus +....+X+1}

#include "lang.inc"

\statement{\name_statement[1] \(w=\cos{\a\pi\over \denom}+i\sin{\a\pi\over \denom}\).
\name_statement[2]
<div class="wimscenter">\(S=\sum\) ? </div>}

\answer{\(Re(S)\)}{0}
\answer{\(Im(S)\)}{0}
\hint{\(w\) \name_hint \(X^\n -1 = (X-1)(X^\minus +....+X+1)\).}
