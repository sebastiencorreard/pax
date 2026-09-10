target=couples

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{couple=random(3..5)}
\integer{man=random(\couple..7)}
\integer{woman=random(\couple..7)}
\integer{sol=factorial(\man)/factorial(\couple)/factorial(\man-\couple)*factorial(\woman)/factorial(\woman-\couple)}

\statement{\name_question[1] \couple \name_question[2]
  \man \name_question[3] \woman \name_question[4]?}

\answer{\name_answer}{\sol}
