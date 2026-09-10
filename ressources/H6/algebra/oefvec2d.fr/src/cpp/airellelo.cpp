target=airellelo
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{mid=8}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{x1=random(-\range..\range)}
\integer{y1=random(-\range..\range)}
\integer{x2=\x1+\a1}
\integer{y2=\y1+\b1}
\integer{x3=\x1+\a2}
\integer{y3=\y1+\b2}
\integer{x4=\x2+\a2}
\integer{y4=\y2+\b2}
\integer{aire=abs(\a1*\b2-\a2*\b1)}

\statement{\name_instruction
<div class="wimscenter">
 (\x1,\y1) , (\x2,\y2) , (\x3,\y3) , (\x4,\y4).
</div>
}

\answer{\name_answer}{\aire}

\hint{\name_hint}

