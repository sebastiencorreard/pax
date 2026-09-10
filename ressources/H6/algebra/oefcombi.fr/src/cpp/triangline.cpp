target=triangline

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{l1=random(4..15)}
\integer{l2=random(4..15)}
\integer{tot=\l1+\l2}
\integer{sol=\l1*\l2*(\l1+\l2-2)/2}
\text{enonce=wims(replace internal LLLL by \l1 in \name_enonce)}
\text{enonce=wims(replace internal MMMM by \l2 in \enonce)}
\text{question=wims(replace internal TTTT by \tot in \name_question)}
\statement{\enonce
<p>\question?</p>}

\answer{\name_answer}{\sol}
