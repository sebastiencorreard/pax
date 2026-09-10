target=modsum2

#include "common.inc"
#include "lang_title.inc"

\integer{type=random(1,2)}
\text{sign=item(\type,+,-)}
\integer{m1=random(2..10)}
\integer{m2=random(2..10)}
\integer{ang=random(10..170)}
\real{\m3=sqrt(\m1^2+\m2^2\sign 2*\m1*\m2*cos(\ang*pi/180))}

#include "lang.inc"

\statement{\name_statement[1] \(z_1) \name_and \(z_2) \name_statement[2]
\(|z_1|=\m1), \(|z_2|=\m2) \name_and \(Arg(z_1/z_2)=\ang) \name_statement[3].
\name_statement[4]
\(z_1\sign z_2)&nbsp;.}

\answer{\(|z_1\sign z_2|)}{\m3}
\hint{\name_hint
<div class="wimscenter">
\(a^2=b^2+c^2-2b c\cos(A) ).
</div>}
