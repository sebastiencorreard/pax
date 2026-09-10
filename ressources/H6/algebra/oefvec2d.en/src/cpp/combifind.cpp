target=combifind
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{a=random(1..\range)*random(-1,1)}
\integer{b=random(1..\range)*random(-1,1)}
\integer{A=\a1*\a+\a2*\b}
\integer{B=\b1*\a+\b2*\b}

\statement{\name_instruction[1;]
  <div class="wimscenter">\(v_1 = (\a1,\b1)), \(v_2 = (\a2,\b2)).</div>
  \name_instruction[2;] \(v=(\A,\B)) \name_instruction[3;]:
  <div class="wimscenter">\(v = a v_1 + b v_2 ).</div>
}

\answer{a}{\a}
\answer{b}{\b}
