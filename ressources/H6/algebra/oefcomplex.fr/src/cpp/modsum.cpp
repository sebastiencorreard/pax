target=modsum

#include "common.inc"
#include "lang_title.inc"

\integer{type=random(1,2)}
\text{s1=item(\type,+,-)}
\text{s2=item(\type,-,+)}
\integer{n1=random(1..10)}
\integer{n2=random(\n1..\n1+10)}
\integer{judge=random(1,2)}

#include "lang.inc"

\text{good=item(\judge,\name_yesno)}
\integer{n3=item(\judge,random(\n2..\n1+\n2),random(\n1+\n2+1..\n1+\n2+6))}
\integer{perm=random(1..6)}
\text{m1=item(\perm,\n1,\n1,\n2,\n2,\n3,\n3)}
\text{m2=item(\perm,\n2,\n3,\n1,\n3,\n2,\n1)}
\text{m3=item(\perm,\n3,\n2,\n3,\n1,\n1,\n2)}

\statement{\name_statement
\(|z_1|=\m1\), \(|z_2|=\m2\), \(|z_1\s1 z_2|=\m3\)&nbsp;?}

\choice{\name_answer}{\good}{\name_yesno}
\hint{\name_hint}
