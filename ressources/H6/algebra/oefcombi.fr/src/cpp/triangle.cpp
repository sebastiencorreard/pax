target=triangle
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{line=random(7..15)}
\integer{orig=random(3..\line-3)}
\integer{vert=random(3..8)}
\integer{tot=\hori+\vert}
\integer{sol=\line*(\line-1)*(\line-2)/6-\orig*(\orig-1)*(\orig-2)/6}
\text{enonce=wims(replace internal XXXX by \orig in \name_enonce)}
\text{enonce=wims(replace internal LLLL by \line in \enonce)}

\statement{\enonce
<p>\name_question[1] \line \name_question[2]?</p>}

\answer{\name_answer}{\sol}
