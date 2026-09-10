target=Sommetstriangl
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
\author{XIAO,Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"

\integer{x1=2*random(-20..20)}
\integer{y1=2*random(-20..20)}
\integer{x2=2*random(-20..20)}
\integer{y2=2*random(-20..20)}
\integer{x3=2*random(-20..20)}
\integer{y3=2*random(-20..20)}
\integer{x12=(\x1+\x2)/2}
\integer{x13=(\x1+\x3)/2}
\integer{x23=(\x2+\x3)/2}
\integer{y12=(\y1+\y2)/2}
\integer{y13=(\y1+\y3)/2}
\integer{y23=(\y2+\y3)/2}
\statement{\name_instruction:
<ul>
<li>\name_text[1] \(A B\) \name_text[2] (\x12,\y12).
</li><li>\name_text[1] \(B C\) \name_text[2] (\x23,\y23).
</li><li>\name_text[1] \(A C\) \name_text[2] (\x13,\y13).
</li></ul>
\name_question?
<div class="wims_instruction">\name_hint
\(A=(x_1, y_1)\),
\(B=(x_2, y_2)\),
\(C=(x_3, y_3)\).
</div>}


\answer{\(x_1\)}{\x1}
\answer{\(y_1\)}{\y1}
\answer{\(x_2\)}{\x2}
\answer{\(y_2\)}{\y2}
\answer{\(x_3\)}{\x3}
\answer{\(y_3\)}{\y3}
