target=rectangle

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{hori=random(3..8)}
\integer{vert=random(3..8)}
\integer{tot=\hori+\vert}
\integer{sol=(\hori*\vert*(\hori-1)*(\vert-1))/4}
\text{enonce=wims(replace internal XXXX by \tot in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \hori in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \vert in \enonce)}

\statement{\enonce
  <p>\name_question[1] \tot \name_question[2]?</p>}

\answer{\name_answer}{\sol}
