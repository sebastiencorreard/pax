target=oefairedisq1
#include "lang_titles.inc"
#include "author.inc"
\keywords{area}
\precision{1000000}
#include "lang.inc"
\integer{r=randint(3..29)}
\integer{res1=2*\r}
\integer{res2=\r*\r}
\text{enonc=\name_enonc \r cm.}

\statement{
\enonc
<div class="spacer"> \name_question[1]: <label for="reply1">2 \(\times) \name_question[2] =</label>
\embed{r1,7}</div>
<div class="spacer"> \name_question[1]: <label for="reply2">\name_question[2] \(\times) \name_question[2] =</label>
\embed{r2,7}</div>
}

\answer{}{\res1}{type=numeric}
\answer{}{\res2}{type=numeric}
