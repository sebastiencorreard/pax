target=Regtriangle
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{sides=random(5..17)}
\integer{sol=\sides*(\sides-1)*(\sides-2)/6}

\statement{\name_enonce[1] \sides \name_enonce[2].
<p>\name_question?</p>}

\answer{\name_answer}{\sol}
