target=pgcd1 pgcd2 pgcd3 pgcd4 pgcd5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{100}

#if defined TARGET_pgcd1
 \integer{pgcd=randitem(2,3,5,10,11,13)}
#endif
#if defined TARGET_pgcd2
 \integer{pgcd=1}
#endif
#if defined TARGET_pgcd3
 \integer{pgcd=randitem(2,3,5,10,11)*randitem(2,3,5,11)}
#endif
#if defined TARGET_pgcd4
 \integer{pgcd=randint(23..65)}
 \integer{pgcd=0 isin \pgcd?23}
 \hint{\name_hint}
#endif
#if defined TARGET_pgcd5
 \integer{pgcd=randint(15..29)*randint(15..29)}
 \integer{pgcd=0 isin \pgcd?223}
 \hint{\name_hint}
#endif

\integer{a=random(7..19)}
\integer{b=random(7..19)}
\integer{g=gcd(\b,\a)}
\if{\g!=1}{
 \integer{a=7}
 \integer{b=15}
}
\integer{A=\a*\pgcd}
\integer{B=\b*\pgcd}
\statement{
  \name_question[1;1] \A \name_question[1;2] \B ?

<br class="spacer">
<b>\name_answer:</b>
  <label for="reply1">\name_question[2;1] \A \name_question[2;2]
  \B \name_question[2;3]</label> \embed{r1,6}.
}
\answer{PGCD}{\pgcd}{type=numexp}
