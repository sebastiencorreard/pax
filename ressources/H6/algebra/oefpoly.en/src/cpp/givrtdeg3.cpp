target=givrtdeg3

#include "header.inc"
#include "lang_titles.inc"

\real{re=random(-1,1)*randint(2..40)/10}
\real{im=random(-1,1)*randint(12..40)/10}
\text{iM=\im>0?+\im:\im}
\text{rr=\re\iM i}
\real{r=random(-1,1)*randint(20..300)/100}
\integer{type=random(1,2,3)}
\real{c1=-(2*(\re)+\r)}
\real{c2=2*(\r)*(\re)+(\re)^2+(\im)^2}
\real{c3=-(\r)*((\re)^2+(\im)^2)}
\text{C1=\c1>=0?+\c1:\c1}
\text{C2=\c2>=0?+\c2:\c2}
\text{C3=\c3>=0?+\c3:\c3}
\text{coef1=item(\type,\C1,+a,+a)}
\text{coef2=item(\type,+a,\C2,+b)}
\text{coef3=item(\type,+b,+b,\C3)}
\real{ansa=item(\type,\c2,\c1,\c1)}
\real{ansb=item(\type,\c3,\c3,\c2)}

#include "lang.inc"

\statement{\name_statement[1]
<div class="wimscenter">
\(P(x) = x^3 \coef1 x^2 \coef2 x \coef3\)
</div>
\name_statement[2] \(a) \name_and \(b) \name_statement[3]
\(\rr\) \name_statement[4].}

\answer{\(a\)}{\ansa}
\answer{\(b\)}{\ansb}
\answer{\name_answer}{\r}
