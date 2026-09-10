target=groupement

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{type=random(1..14)}
\integer{each=item(\type,2,4,3,2,5,2,6,3,4,2,7,3,5,8)}
\integer{grps=item(\type,4,2,3,5,2,6,2,4,3,7,2,5,3,2)}
\integer{tot=\each*\grps}
\integer{sol=factorial(\tot)/(factorial(\grps)*factorial(\each)^\grps)}

\statement{\name_question[1] \tot \name_question[2] \grps
  \name_question[3] \each \name_question[4]?}

\answer{\name_answer}{\sol}
