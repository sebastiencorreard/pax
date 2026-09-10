target=posneg

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{pos=random(3..8)}
\integer{neg=random(3..8)}
\integer{tot=\pos+\neg}
\integer{type=random(1..4)}
\text{question=item(\type,\qlist)}
\text{slist=\pos*\neg,\pos*(\pos-1)+\neg*(\neg-1),
  2*\pos*\neg,2*(\pos*(\pos-1)+\neg*(\neg-1))}
\integer{sol=item(\type,\slist)}

\statement{\name_enonce[1] \pos \name_enonce[2]
\neg \name_enonce[3] \tot \name_enonce[4]
<p>
\name_question[1] \question \name_question[2]?
</p>}

\answer{\name_answer}{\sol}
