target=Hauteurdunarbr
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\matrix{m=
5,40,12,5
6,45,15,8}
\text{col=randomrow(\m)}
\text{OA=item(1,\col)}
\text{A1=item(2,\col)}
\text{A2=item(3,\col)}
\text{R=item(4,\col)}

\statement{
\name_enonce[1] \(B A H\) \name_enonce[2] \A1&deg;,
\name_enonce[3] \(H A C) \name_enonce[2] \A2&deg; \name_enonce[4] \OA m
\name_enonce[5]
<div class="wimscenter">
<img src="\imagedir/hauteurarbre.gif" alt="">
</div>
}

\answer{\name_answer}{\R}
