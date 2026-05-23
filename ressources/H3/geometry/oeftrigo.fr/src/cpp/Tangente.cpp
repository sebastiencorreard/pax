target=Tangente
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{bc=random(5..15)}
\integer{\r=\bc*tan(pi/4)}
\statement{<div class="wimscenter">
\draw{200,200}{
xrange -20,20
yrange -20,20
triangle 15,15,15,-15,-15,-15,black
text black,14.5,17.5,medium,A
text black,16,-15,medium,B
text black,-16.5,-15,medium,C
}
</div>
\(A B C\) \name_enonce[1] \(B\), \([B\ C]\) \name_enonce[2] \bc cm, \name_enonce[3]
\(\widehat{C}) \name_enonce[2] 45&deg;. \name_enonce[4] \(A B\) \name_enonce[5].}

\answer{\name_answer[1] \(A B\) \name_answer[2] cm}{\r}{type=default}
