target=vocabulaire4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{M=randitem(A,B,C,D,E,F,M,N)}
\text{size=150x20x1}
\text{p=wims(values v,-v for v=1 to 10)}
\text{p=shuffle(\p)}

\statement{
\name_enonce:
<div class="wims_question">\name_phrase[1],
\name_phrase[2] \embed{r1,\size}.
<br>
\name_phrase[3] \M \name_phrase[4] \embed{r2,\size} (\p[1];\p[2]).
\name_phrase[5], \p[1] \name_phrase[6] \embed{r3,\size}
\name_phrase[7] \p[2] \name_phrase[8] \embed{r4,\size}.
</div>
}
\answer{\name_answer[1]}{\name_mot[1]}{type=clickfill}
\answer{\name_answer[2]}{\name_mot[2]}{type=clickfill}
\answer{\name_answer[3]}{\name_mot[3]}{type=clickfill}
\answer{\name_answer[4]}{\name_mot[4]}{type=clickfill}
