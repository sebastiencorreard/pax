target=Hotellampe
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}

\integer{lamps=random(10..20)}
\integer{eteints=random(2..4)}
\integer{distr=binomial(\lamps-\eteints-1,\eteints)}
\statement{\name_enonce[1] \lamps \name_enonce[2]
\name_enonce2[1] \name_enonce2[2] \eteints \name_enonce2[3]
<p>
\name_question \eteints \name_lampe?
</p>}
\answer{\name_answer}{\distr}
