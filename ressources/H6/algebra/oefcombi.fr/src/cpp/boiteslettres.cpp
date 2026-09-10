target=boiteslettres
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{letters=random(3..7)}
\integer{boxes=random(3..8)}
\integer{methods=\boxes^\letters}
\statement{\name_question[1] \letters \name_question[2] \boxes \name_question[3]?}

\answer{\name_answer}{\methods}
