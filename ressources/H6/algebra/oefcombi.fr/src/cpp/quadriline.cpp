target=quadriline

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{l1=random(4..15)}
\integer{l2=random(4..15)}
\integer{tot=\l1+\l2}
\integer{sol=\l1*(\l1-1)*\l2*(\l2-1)/4}
\text{enonce=wims(replace internal XXXX by \l1 in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \l2 in \enonce)}

\statement{\enonce
<p>\name_question[1] \tot \name_question[2]?</p>}

\answer{\name_answer}{\sol}
