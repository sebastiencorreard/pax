target=Mdiane
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\matrix{donne=
6,8,10,5
12,16,20,10
18,24,30,15
24,32,40,20
}
\text{ligne=randomrow(\donne)}
\text{ar=item(1,\ligne)}
\text{br=item(2,\ligne)}
\text{cr=item(4,\ligne)}
\statement{<div class="wimscenter">
\draw{200,200}{
xrange -15,15
yrange -15,15
triangle -13,-7,-13,7,13,-7,red
segment -13,-7,0,0,black
text black,-14,-7,medium,A
text black,-13.5,9,medium,B
text black,13.5,-6.5,medium,C
text black,0,2,medium,I
}
</div>
\([AI]\) \name_enonce[1] \(AC\) \name_enonce[2] \(\ar\ cm\)  \name_enonce[3] \(AI\)
\name_enonce[2] \(\cr \ cm\) ,
\name_enonce[4] \(AB\) (\name_enonce[5] \(cm\))?}

\answer{\name_answer \(AB)}{\br}{type=default}
