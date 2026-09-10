target=combi combi2 combi4
#if defined TARGET_combi
# define NUM 3
#endif
#if defined TARGET_combi2
# define NUM 2
#endif
#if  defined TARGET_combi4
# define NUM 4
#endif

\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
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
#if  defined TARGET_combi4
\integer{a4=random(1..\range)*random(-1,1)}
\integer{b4=random(1..\range)*random(-1,1)}
\integer{c4=random(1..\range)*random(-1,1)}
#endif
\integer{a=random(1..\range)*random(-1,1)}
\integer{b=random(1..\range)*random(-1,1)}
\integer{c=random(1..\range)*random(-1,1)}
#if defined TARGET_combi
\integer{A=\a1*\a+\a2*\b+\a3*\c}
\integer{B=\b1*\a+\b2*\b+\b3*\c}
\integer{C=\c1*\a+\c2*\b+\c3*\c}
\text{combi=\a*v1 + \b*v2 + \c*v3}
#endif
#if defined TARGET_combi2
\integer{A=\a1*\a+\a2*\b}
\integer{B=\b1*\a+\b2*\b}
\integer{C=\c1*\a+\c2*\b}
\text{combi=\a*v1 + \b*v2}
#endif
#if defined TARGET_combi4
\integer{d=random(1..\range)*random(-1,1)}
\integer{A=\a1*\a+\a2*\b+\a3*\c+\a4*\d}
\integer{B=\b1*\a+\b2*\b+\b3*\c+\b4*\d}
\integer{C=\c1*\a+\c2*\b+\c3*\c+\c4*\d}
\text{combi=\a*v1 + \b*v2 + \c*v3 + \d*v4}
#endif
\statement{\name_enonce[1]
  <div class="wimscenter">
  \(v_1 = (\a1,\b1,\c1)\),
  \(v_2 = (\a2,\b2,\c2)\),
#if defined TARGET_combi || defined TARGET_combi4
  \(v_3 = (\a3,\b3,\c3)\)
# if defined TARGET_combi4
\(v_4 = (\a4,\b4,\c4)\)
# endif
#endif
  </div>
  \name_enonce[2]
  <div class="wimscenter">
  \(v = \combi).
  </div>
}

\answer{\(v\)}{\A,\B,\C}{type=vector}
