target=Cosinus
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ac=random(15..50)}
\integer{deg=random(30,45,50,60,20,15,40,35,55,65,75,80)}
\integer{\r=\ac*cos(\deg*pi/180)}
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
\(A B C\) \name_enonce[1] \(B\), \([A\ C]\) \name_enonce[2] \ac cm, \name_enonce[3]
\(\widehat{C}) \name_enonce[2] \deg&deg;. \name_enonce[4] \(B C\) \name_enonce[5].}

\answer{\name_answer[1] \(B C\) \name_answer[2] cm}{\r}{type=default}
