target=3bottles

\author{XIAO,Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\range{-5..5}
\precision{1000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{v1=6*random(5..30)}
\integer{v2=6*random(5..30)}
\integer{v3=6*random(5..30)}
\integer{t1=random(2..4)}
\integer{t2=random(2..4)}
\integer{t3=1}
\real{det=(\t1)*(\t2)-1}
\real{r1=\v1*(\t1+1)}
\real{r2=\v2*(\t2+1)}
\real{r3=2*\v3}
\real{A=((\r1)*(\t2)*(\t3)+(\r2)*(\t3)+(\r3))/(\det)}
\real{B=((\r1)+(\r2)*(\t1)*(\t3)+(\r3)*(\t1))/(\det)}
\real{C=((\r1)*(\t2)+(\r2)+(\r3)*(\t1)*(\t2))/(\det)}

\statement{\name_instruction
<ul><li>
\name_text[1] \v1 cl \name_text[2] A \name_text[3] B, B \name_text[4] \t1 \name_text[5] A.
</li><li>
\name_text[1] \v2 cl \name_text[2] B \name_text[3] C, C \name_text[4] \t2 \name_text[5] B.
</li><li>
\name_text[1] \v3 cl \name_text[2] C \name_text[3] A, A \name_text[6] C.
</li></ul>
\name_question?}

\answer{\name_bottle A}{\A}
\answer{\name_bottle B}{\B}
\answer{\name_bottle C}{\C}
