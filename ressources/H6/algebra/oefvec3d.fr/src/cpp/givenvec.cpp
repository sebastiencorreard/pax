target=givenvec
#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"

\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=random(1..\range)*random(-1,1)}
\integer{c1=random(1..\range)*random(-1,1)}
\integer{a2=random(1..\mid)*random(-2,2)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{c2=random(1..\range)*random(-1,1)}
\integer{v1=\b1*\c2-\c1*\b2}
\integer{v2=\c1*\a2-\a1*\c2}
\integer{v3=\a1*\b2-\b1*\a2}
\integer{scal=\a1*\a2+\b1*\b2+\c1*\c2}

\statement{\name_enonce[1] \(u=(\a1,\b1,\c1)\) \name_enonce[2]
  \(v=(\a2,b,c)\) \name_enonce[3]
  \name_enonce[4] (\v1,\v2,\v3).

}

\answer{\(b\)}{\b2}
\answer{\(c\)}{\c2}
