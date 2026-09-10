target=angle
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{c1=random(-\range..\range)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{c2=random(-\range..\range)}
\integer{x1=random(-\range..\range)}
\integer{y1=random(-\range..\range)}
\integer{z1=random(-\range..\range)}
\integer{x2=\x1+\a1}
\integer{y2=\y1+\b1}
\integer{z2=\z1+\c1}
\integer{x3=\x1+\a2}
\integer{y3=\y1+\b2}
\integer{z3=\z1+\c2}
\integer{prod=\a1*\a2+\b1*\b2}
\real{l1=sqrt((\a1)^2+(\b1)^2)}
\real{l2=sqrt((\a2)^2+(\b2)^2)}
\real{angle=acos(\prod/(\l1*\l2))*180/pi}

\statement{
  \name_instruction
  <div class="wimscenter">\(A(\x1,\y1)), \(B(\x2,\y2)), \(C(\x3,\y3)).</div>
  \name_instruction2
}

\answer{\name_answer}{\angle}
\hint{\name_hint}
