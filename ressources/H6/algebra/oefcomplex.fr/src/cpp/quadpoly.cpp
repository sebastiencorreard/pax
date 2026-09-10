target=quadpoly

#include "common.inc"
#include "lang_title.inc"

\real{re1=random(-1,1)*randint(2..50)/10}
\real{im1=random(-1,1)*randint(2..50)/10}
\real{re2=random(-1,1)*randint(2..50)/10}
\real{im2=random(-1,1)*randint(2..50)/10}
\real{rec1=-(\re1)-(\re2)}
\real{imc1=-(\im1)-(\im2)}
\real{rec2=(\re1)*(\re2)-(\im1)*(\im2)}
\real{imc2=(\re1)*(\im2)+(\re2)*(\im1)}
text{imC1=\imc1>=0?+\imc1:\imc1}
text{imC2=\imc2>=0?+\imc2:\imc2}

#include "lang.inc"

\statement{\name_statement
<div class="wimscenter">
\(P(X) = X^2 + (\rec1+\imc1*i)X + (\rec2+\imc2 *i)).
</div>
<div class="wims_instruction">
\name_instruction
</div>
}
\answer{\(Re(r1))}{\rer1}
\answer{\(Im(r1))}{\imr1}
\answer{\(Re(r2))}{\rer2}
\answer{\(Im(r2))}{\imr2}

\condition{\(r_1) \name_condition1}
{(\rer1=\re1 and \imr1=\im1) or (\rer1=\re2 and \imr1=\im2)}
\condition{\(r_2) \name_condition2}
{((\rer2=\re1 and \imr2=\im1) or (\rer2=\re2 and \imr2=\im2))
 and \rer1+\rer2=-(\rec1)}
