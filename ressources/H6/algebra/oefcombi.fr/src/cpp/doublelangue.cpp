target=Doublelangue
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{tot=random(10..26)}
\integer{english=random(ceil(\tot/2)..\tot-2)}
\integer{german=random(ceil(\tot/2)..\tot-2)}
\integer{both=\english+\german-\tot}
\integer{enonly=\english-\both}
\integer{geonly=\german-\both}
\integer{ans=\enonly*\german+\both*(\german-1)-\both*(\both-1)/2}
\statement{\name_enonce[1] \tot \name_enonce[2], \english \name_enonce[3],
\german \name_enonce[4]
<p>\name_question?</p>}
\answer{\name_answer}{\ans}
