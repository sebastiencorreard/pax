target=fractionsimp1 fractionsimp2 fractionsimp3 fractionsimp4 fractionsimp5

\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{100}

#if defined TARGET_fractionsimp1
 \integer{div=randitem(2,5,10)}
#endif
#if defined TARGET_fractionsimp2
 \integer{div=randitem(3,11)}
#endif
#if defined TARGET_fractionsimp3
 \integer{div=randitem(4,9)}
#endif
#if defined TARGET_fractionsimp4
 \integer{div=randint(2..13)}
#endif
#if defined TARGET_fractionsimp5
 \integer{div=randitem(2,3,5)*randint(2..13)}
#endif

\integer{a=random(7..19)}
\integer{b=random(7..19)}
\integer{g=gcd(\b,\a)}
\if{\g!=1}{
 \integer{a=7}
 \integer{b=15}
}
\integer{A=\a*\div}
\integer{B=\b*\div}
\statement{
  \name_question \(\frac{\A}{\B}\) ?
\complement
<div class="spacer">
<b>\name_answer:</b>
\special{mathmlinput [\frac{\A}{\B} = \frac{reply1}{reply2}],2,noanswer
reply1
reply2
}
</div>
}
\answer{\name_numden[1]}{\a}{type=numexp}
\answer{\name_numden[2]}{\b}{type=numexp}
