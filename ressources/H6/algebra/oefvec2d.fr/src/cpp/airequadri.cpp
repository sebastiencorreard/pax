target=airequadri
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{min=5}
\integer{max=13}
\integer{x1=random(\min..\max)}
\integer{y1=random(\min..\max)}
\integer{x2=random(-\min..-\max)}
\integer{y2=random(\min..\max)}
\integer{x3=random(-\min..-\max)}
\integer{y3=random(-\min..-\max)}
\integer{x4=random(\min..\max)}
\integer{y4=random(-\min..-\max)}
\integer{u1=\x2-\x1}
\integer{v1=\y2-\y1}
\integer{u2=\x3-\x1}
\integer{v2=\y3-\y1}
\integer{u3=\x4-\x1}
\integer{v3=\y4-\y1}
\integer{a1=\u1*\v2-\u2*\v1}
\integer{a2=\u2*\v3-\u3*\v2}
\real{aire=0.5*abs(\a1+\a2)}
\integer{r=random(0,1)}
\text{B=\r=1?\x2,\y2:\x4,\y4}
\text{D=\r=1?\x4,\y4:\x2,\y2}

\statement{
<div class="float_left spacer">
\draw{200,200}{
 xrange -15,15
 yrange -15,15
 arrow -15,0,15,0,10,grey
 arrow 0,-15,0,15,10,grey
 linewidth 2
 polygon red,\x1,\y1,\x2,\y2,\x3,\y3,\x4,\y4
 linewidth 4
 points blue,\x1,\y1,\x2,\y2,\x3,\y3,\x4,\y4
}
</div>
\name_instruction
<div class="wimscenter">
 \(A) = (\x1,\y1), \(B) = (\B), \(C) = (\x3,\y3), \(D) = (\D).
</div>

}

\answer{\name_answer}{\aire}

\hint{\name_hint}

