target=perp2
#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"

\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{c1=random(-\range..\range)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{c2=random(-\range..\range)}
\integer{v1=\b1*\c2-\c1*\b2}
\integer{v2=\c1*\a2-\a1*\c2}
\integer{v3=\a1*\b2-\b1*\a2}
\integer{c=random(1..2*\range)*random(-1,1)}
\real{ratio=\c/\v3}
\real{a=\v1*\ratio}
\real{b=\v2*\ratio}
\statement{\name_enonce[1]
<div class="wimscenter">
\(v_1 = (\a1,\b1,\c1)),
\(v_2 = (\a2,\b2,\c2))
</div>
\name_enonce[2] \(v=(a,b,\c)) \name_enonce[3] \(v_1) \name_enonce[4] \(v_2).
}

\answer{\(a\)}{\a}
\answer{\(b\)}{\b}

\hint{\name_hint}
