target=intersection intersection2 intersection3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{tot=random(15..40)}

#if defined TARGET_intersection
\integer{sol=binomial(\tot,2)}
#endif
#if defined TARGET_intersection2
\integer{par=randint(3..8)}
\integer{sol=binomial(\tot,2)-binomial(\par,2)}
\text{dir=randitem(\name_dir)}
#endif
#if defined TARGET_intersection3
\integer{coinc=randint(3..8)}
\integer{sol=binomial(\tot,2)-binomial(\coinc,2)+1}
#endif
\statement{\name_enonce<p>
\name_question[1] \tot \name_question[2]
#if defined TARGET_intersection
?
#endif
#if defined TARGET_intersection2
\name_question1[1] \par \name_question1[2] \dir
\name_question1[3]?
#endif
#if defined TARGET_intersection3
\name_question1[1] \coinc \name_question1[2]?
#endif
</p>}

\answer{\name_answer}{\sol}
