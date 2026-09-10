target=voltetra
#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"
\integer{mid=5}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{c1=random(-\range..\range)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{c2=random(-\range..\range)}
\integer{a3=random(-\range..\range)}
\integer{b3=random(-\range..\range)}
\integer{c3=2*random(-\mid..\mid-2)+1}
\integer{x1=random(-\range..\range)}
\integer{y1=random(-\range..\range)}
\integer{z1=random(-\range..\range)}
\integer{x2=\x1+\a1}
\integer{y2=\y1+\b1}
\integer{z2=\z1+\c1}
\integer{x3=\x1+\a2}
\integer{y3=\y1+\b2}
\integer{z3=\z1+\c2}
\integer{x4=\x1+\a3}
\integer{y4=\y1+\b3}
\integer{z4=\z1+\c3}
\real{d1=\a1*\b2-\a2*\b1}
\real{d2=\b1*\c2-\b2*\c1}
\real{d3=\c1*\a2-\c2*\a1}
\real{vol=abs(\a1*\b2*\c3+\a2*\b3*\c1+\a3*\b1*\c2
	 -\a1*\b3*\c2-\a2*\b1*\c3-\a3*\b2*\c1)/6}
\statement{
  \name_enonce
  <div class="wimscenter">
    \(A) = (\x1,\y1,\z1),
    \(B) = (\x2,\y2,\z2),
    \(C) = (\x3,\y3,\z3),
    \(D) = (\x4,\y4,\z4).
  </div>
}

\answer{\name_answer}{\vol}

\hint{
  \name_hint1
  <p>
  \name_hint2
  </p><p>
  \name_hint3
  </p>
}

