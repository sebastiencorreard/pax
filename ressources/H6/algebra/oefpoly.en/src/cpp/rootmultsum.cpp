target=rootmultsum

#include "header.inc"
#include "lang_titles.inc"

#include "lang.inc"

\integer{r=random(-50..50)}
\integer{m1=random(2..20)}
\integer{t=random(1,2)}
\integer{m2=item(\t,\m1,random(2..20))}
\integer{type=random(1..4)}
\text{composed=item(\type,P(X)+Q(X),P(X)-Q(X),
			P(X)Q(X),P(X)Q(X))}
\integer{min=min(\m1,\m2)}
\integer{m=item(\type,\min,\min,\m1+\m2,\m1+\m2)}
\text{good=\type<=2 and \m1=\m2?\name_sup:\name_equ}

\statement{\name_statement1:
<div class="wims_question">
\name_statement2[1] \(\r\) \name_statement2[2] \(\m1\) \name_of \(P(X)\)
\name_statement2[3] \(\m2\) \name_of \(Q(X)\),
\name_statement2[4] \(\r\) \name_statement2[5] ________ \name_of
\(\composed\).
</div>
}

\choice{\name_choice}{\good}{\name_sup,\name_inf,\name_equ}
\answer{\name_answer m}{\m}
