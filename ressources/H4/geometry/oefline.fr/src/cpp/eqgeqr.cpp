target=eqgeqr

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}
\integer{a=random(-1,1)*randint(1..20)}
\integer{b=random(-1,1)*randint(1..20)}
\integer{c=random(-1,1)*randint(1..20)}

\function{f=maxima(\a*x+\b*y+\c)}

\text{f=texmath(\f)}

\rational{cd=-\a/\b}
\rational{oo=-\c/\b}

\integer{r=random(1,2)}

#include "lang.inc"

\if{\r=1}{
\rational{rep=\cd}
}
\if{\r=2}{
\rational{rep=\oo}
}

\statement{\name_statement[1;] \(\math_droite\) \name_statement[2;]
 \(\f=0\). \name_statement[3;] 
 \name_question_list[\r] \name_statement[4;] \(\math_droite\).
<div class="spacer">
 \name_Question_list[\r] \name_statement[4;] \(\math_droite\)
 \name_is \embed{reply 1}.
</div>
}

\answer{\name_reponse}{\rep}{type=default}
