target=oefairedisq2
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\keywords{area}
\langage{fr}
\format{html}
\precision{1000000}

\integer{d=randint(2..24)*2}
\integer{res1=\d*\d/4}
\statement{
\name_enonc \d cm.
<div class="spacer">\name_question[1] :
<label for="reply1">\name_question[2] \(\times\) \name_question[2]</label> = \embed{r1,7}
</div>
}

\answer{}{\res1}{type=numeric}
