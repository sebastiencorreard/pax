target=tablediner1 tablediner2 tablediner3 tablediner4
#include "author.inc"
\precision{1000000}
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_tablediner1
\integer{pairs=random(3..7)}
\integer{sol=2*factorial(\pairs)^2}
#endif
#if defined TARGET_tablediner2
\integer{pairs=random(3..8)}
\integer{sol=4*factorial(\pairs)}
#endif
#if defined TARGET_tablediner3
\integer{pairs=random(3..7)}
\integer{sol=2*factorial(\pairs)*2^\pairs}
#endif
#if defined TARGET_tablediner4
\integer{pairs=random(3,4)}
\integer{coef=item(\pairs-2,1,2)}
\integer{sol=2*factorial(\pairs)*\coef}
#endif
\integer{tot=2*\pairs}

\statement{\pairs \name_enonce[1]
\tot \name_enonce[2]
<p>\name_question
#if defined TARGET_tablediner3
\name_question2
#endif
?
</p>
}
\answer{\name_answer}{\sol}
