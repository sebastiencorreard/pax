target=chelle2

\language{fr}
\range{-5..5}

\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\matrix{m=
2,1
3,1
4,1
5,2
6,2
7,2
8,2
9,3
}
\text{ligne=randomrow(\m)}
\text{m=item(1,\ligne)}
\text{s=item(2,\ligne)}
\integer{r1=atan(\m/\s)*180/pi}
\real{r2=rint(10*sqrt(\m^2+\s^2))/10}
\statement{<div class="wimscenter">
\draw{150,250}{
xrange -15,15
yrange -25,25
segment -15,-24,15,-24,black
rect -14,24,0,-24,black
fill -5,0,grey
segment 0,15,14,-24,black
text black,7,0,medium,E
text black,-7,0,medium,B
text black,0.5,16.5,medium,C
text black,0.5,-21.5,medium,A
text black,12,-21.5,medium,B
}
</div>
\name_enonce[1] \(B\), \(A C\) \name_enonce[2] \m m \name_enonce[3],
\(A B\) \name_enonce[2] \s m \name_enonce[3].
\name_question[1;1] \(\widehat B\) (\name_question[1;2]) ?
\name_question[2;1] (\name_question[2;2]) ?}
\name_answer[1] \(\widehat B\) name_answer[2]
\answer{ \name_answer[1] B \name_answer[2]}{\r1}
\answer{\name_answer[3]}{\r2}
