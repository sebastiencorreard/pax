target=party

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{couple=random(5..10)}
\integer{single=random(10..20)}
\integer{total=2*\couple+\single}
\integer{ans=(\total*(\total-1))/2-\couple}
\text{enonce=wims(replace internal XXXX by \couple in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \single in \enonce)}
\statement{\enonce <p>\name_question?</p>}

\answer{\name_answer}{\ans}
