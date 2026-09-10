target=quadrilat
#include "lang_titles.inc"
\range{-5..5}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{1000000}

#include "lang.inc"
\integer{m1=random(-199..199)}
\integer{m2=random(-199..199)}
\integer{m3=random(-199..199)}
\integer{n1=random(-199..199)}
\integer{n2=random(-199..199)}
\integer{n3=random(-199..199)}
\integer{m4=\m1+(\m3)-(\m2)}
\integer{n4=\n1+(\n3)-(\n2)}

\statement{\name_question:
<ul><li>\name_question2[1] \(A B\) \name_question2[2] (\m1 , \n1).
</li><li>\name_question2[1] \(B C\) \name_question2[2] (\m2 , \n2).
</li><li>\name_question2[1] \(C D\) \name_question2[2] (\m3 , \n3).
</li></ul>
\name_question3?
}
\answer{\(x)}{\m4}
\answer{\(y)}{\n4}
