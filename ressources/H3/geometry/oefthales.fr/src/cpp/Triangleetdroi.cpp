target=Triangleetdroi
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\matrix{donnee=
10,5,12,6
12,6,14,7
14,7,16,8
16,8,20,10
20,10,24,12}
\text{ligne=randomrow(\donnee)}
\text{AB=item(1,\ligne)}
\text{AD=item(2,\ligne)}
\text{BC=item(3,\ligne)}
\text{DE=item(4,\ligne)}
\text{dessin=xrange -20,20
yrange -20,20
triangle -5,12,-15,-10,16,-10,black
segment -15,-10,16,-10,red
segment -10,1,5.5,1,red
text black,-5.5,14.5,medium,A
text black,-17,-10,medium,B
text black,17,-10,medium,C
text black,-12,3,medium,D
text black,6.5,3,medium,E}
\text{dessintikz=drawtikz(200,200
\dessin)}

\statement{<p class="wimscenter">
\draw{200,200}{
\dessin}
</p>
\name_enonce
<p>
\([DE] \sslash [BC]\) ; \(AB = \AB\) \(cm\) ; \(AD = \AD\) \(cm\) ; \(BC = \BC\) \(cm\).
</p>
\name_question[1] \(DE\) (\name_question[2] \(cm\))?}

\answer{\name_answer \([DE]\)}{\DE}{type=default}
\hint{\name_hint}

\latex{\begin{statement}
\name_enonce
<p>
\([DE] \parallel [BC]\) ; \(AB = \AB\) \(cm\) ; \(AD = \AD\) \(cm\) ; \(BC = \BC\) \(cm\).
</p>
\name_question[1] \(DE\) (\name_question[2] \(cm\))?
\par
\dessintikz
\end{statement}
}
