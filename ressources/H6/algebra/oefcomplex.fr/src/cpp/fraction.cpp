target=fraction

#include "common.inc"
#include "lang_title.inc"

\integer{a1=random(-10..10)}
\integer{b1=random(2..10)*random(-1,1)}
\integer{a2=random(1..10)*random(-1,1)}
\integer{b2=random(2..10)*random(-1,1)}
\complex{z1=\a1+i*\b1}
\complex{z2=\a2+i*\b2}
\text{z1_t=texmath(\z1)}
\text{z2_t=texmath(\z2)}
\text{B1=\b1>=0?+\b1:\b1}
\text{B2=\b2>=0?+\b2:\b2}
\real{mod=(\a2)^2+(\b2)^2}
\real{re=(\a1*(\a2)+(\b1)*(\b2))/\mod}
\real{im=(\b1*(\a2)-(\a1)*(\b2))/\mod}

#include "lang.inc"

\statement{\name_statement:
<div class="wimscenter">\(\frac{\z1_t}{\z2_t}) </div>
}

\answer{\name_answer1}{\re}
\answer{\name_answer2}{\im}
