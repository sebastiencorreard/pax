target=combifind combifind2
#if defined TARGET_combifind
# define NUM 3
#endif
#if defined TARGET_combifind2
# define NUM 2
#endif

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{mid=5}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{c1=2*random(-\mid..\mid)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{c2=2*random(-\mid..\mid)}
\integer{a3=random(-\range..\range)}
\integer{b3=random(-\range..\range)}
\integer{c3=2*random(-\mid..\mid-2)+1}
\integer{a=random(1..\range)*random(-1,1)}
\integer{b=random(1..\range)*random(-1,1)}
\integer{c=random(1..\range)*random(-1,1)}
#if defined TARGET_combifind
\integer{A=\a1*\a+\a2*\b+\a3*\c}
\integer{B=\b1*\a+\b2*\b+\b3*\c}
\integer{C=\c1*\a+\c2*\b+\c3*\c}
#endif
#if defined TARGET_combifind2
\integer{A=\a1*\a+\a2*\b}
\integer{B=\b1*\a+\b2*\b}
\integer{C=\c1*\a+\c2*\b}
#endif
\statement{\name_enonce[1]
  <div class="wimscenter">
  \(v_1 = (\a1,\b1,\c1)\),
  \(v_2 = (\a2,\b2,\c2)\),
#if defined TARGET_combifind
  \(v_3 = (\a3,\b3,\c3)\)
#endif
  </div>
  \name_enonce[2]
  \name_question \(v_1\), \(v_2\)
  #if defined TARGET_combifind
  , \(v_3\)
  #endif
  <div class="wimscenter">
#if defined TARGET_combifind
  \(v = a v_1 + b v_2 + c v_3\).
#endif
#if defined TARGET_combifind2
\(v = a v_1 + b v_2\).
#endif
  </div>
}

\answer{\(a\)}{\a}
\answer{\(b\)}{\b}
\answer{\(c\)}{\c}

