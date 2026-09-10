target=combi3
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{mid=5}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{a3=random(-\range..\range)}
\integer{b3=random(-\range..\range)}
\integer{a=random(1..\range)*random(-1,1)}
\integer{b=random(1..\range)*random(-1,1)}
\integer{c=random(1..\range)*random(-1,1)}
\integer{A=\a1*\a+\a2*\b+\a3*\c}
\integer{B=\b1*\a+\b2*\b+\b3*\c}
\text{combi=\a*v1 + \b*v2 + \c*v3}

\statement{
  \name_instruction[1]
  <div class="wimscenter">\(v_1 = (\a1,\b1)), \(v_2 = (\a2,\b2) ), \(v_3 = (\a3,\b3)).
  </div>
  \name_instruction[2]
  <div class="wimscenter">
  	\(v = \combi).
  </div>
}

\answer{\(v)}{\A,\B}{type=vector}
