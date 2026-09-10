target=givenscale

#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"

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
\integer{A=\a1*\a+\b1*\b+\c1*\c}
\integer{B=\a2*\a+\b2*\b+\c2*\c}
\integer{C=\a3*\a+\b3*\b+\c3*\c}
\statement{\name_enonce[1]
  <div class="wimscenter">
  \(v_1 = (\a1,\b1,\c1)\),
  \(v_2 = (\a2,\b2,\c2)\),
  \(v_3 = (\a3,\b3,\c3)\)
  </div>
  \name_enonce[2]:
  <div class="wimscenter">
  	\(\langle v,v_1\rangle = \A \),
  	\(\langle v,v_2\rangle = \B \),
  	\(\langle v,v_3\rangle = \C \).
  </div>
}

\answer{\(v\)}{\a,\b,\c}{type=vector}

