target=Ordinat1 Ordinat2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}
#if defined TARGET_Ordinat1
\integer{computers=random(8..12)}
\integer{students=random(ceil(\computers/2)..\computers-3)}
\text{distr=pari(binomial(\computers,\students)*
  truncate(factorial(\students)))}
#endif
#if defined TARGET_Ordinat2
\integer{group=randint(2..3)}
\integer{computers=randint(3..12/\group)}
\integer{students=\computers*\group}
\integer{pro=factorial(\students)}
\integer{gro=item(\group,1,2,6)}
\integer{ddd=\gro^\computers}
\integer{distr=\pro/\ddd}
#endif

\text{enonce=wims(replace internal XXXX by \computers in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \students in \enonce)}
\text{question=wims(replace internal ZZZZ by \group in \name_question)}

\statement{\enonce <p>\question?</p>}

\answer{\name_answer}{\distr}
