target=vitesse
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"
\integer{t1=10*randint(1..6)}
\integer{t2=10*randint(1..6)}
\integer{v1=randint(1..6)*5}
\integer{v2=randint(1..6)*5}
\real{vm=floor(10*(\t1*\v1+\t2*\v2)/(\t1+\t2))/10}
\integer{t3=10*randint(1..6)}
\integer{v3=randint(1..6)*5}
\real{vm3=floor(10*(\t1*\v1+\t2*\v2+\t3*\v3)/(\t1+\t2+\t3))/10}

\steps{reply1
reply2}

\statement{\name_enonce[1] \t1 min
  \name_enonce[2] \v1 km/h \name_enonce[3] \t2 min \name_enonce[4] \v2 \name_hkm[3].
  \if{\step=1}{\name_question1? }

  \if{\step=2}{<p>\name_enonce2[1] \t3 min. \name_enonce2[2] \vm3 \name_hkm[3]. \name_enonce2[3]?</p>}
  <div class="wims_instruction">\name_instruction \name_hkm[3].</div>}

\answer{\name_answer[1]}{\vm}{type=numeric}{option=absolute precision=10 comma}
\answer{\name_answer[2]}{\v3}{option=absolute precision=10 comma}
