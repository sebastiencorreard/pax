target=pythagorus
\keywords{complex_plane}
#include "common.inc"
#include "lang_titles.inc"

\text{l1=      1,      1,      2,3, 5, 7}
\text{l2=      1,      2,      2,4,12,24}
\text{l3=sqrt(2),sqrt(5),sqrt(8),5,13,25}
\integer{n=items(\l1)}
\integer{t=random(1..\n)}
\real{n1=item(\t,\l1)}
\real{n2=item(\t,\l2)}
\text{m3=item(\t,\l3)}
\integer{exchange=random(1,2)}
\text{m1=item(\exchange,\n1,\n2)}
\text{m2=item(\exchange,\n2,\n1)}
\integer{type=random(1,2)}
\text{s1=item(\type,+,-)}
\text{s2=item(\type,-,+)}

#include "lang.inc"

\statement{\name_statement[1] \(z_1\) \name_and \(z_2\) \name_statement[2]
\(|z_1|=\m1\), \(|z_2|=\m2\), \(|z_1 \s1 z_2 |=\m3\). \name_statement[3]
\(|z_1 \s2 z_2 |\)&nbsp;?}

\answer{\name_answer}{\m3}
\hint{\name_hint
\(Arg(z_1)\) \name_and \(Arg(z_2)\)&nbsp;?}
