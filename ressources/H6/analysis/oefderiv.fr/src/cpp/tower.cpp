target=tower
#include "xiao.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\format{html}
\precision{10000}

\real{speed=randint(11..25)/10}
\integer{height=randint(100..200)}
\integer{dist=randint(100..300)}
\real{sol=\speed*\dist/sqrt(\dist^2+\height^2)}

\statement{\name_enonce[1]
\speed \name_enonce[2] \name_question[1] \height \name_question[2] ,
\name_question[3] \dist \name_question[4] ?
}

\answer{\name_answer m/s}{\sol}
