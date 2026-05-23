target=Puits
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
text{nom=randitem(Romain,Marie,Anthony,Cécile,Michel,Nathalie,Alain,
Anne,Bertrand,Denise)}
\text{nom=slib(lang/fname )}
\matrix{donne=
120,135,40
125,140,44
130,145,47
135,150,51
140,155,54
145,160,57
150,170,60
155,175,65
160,180,70
165,185,75
170,190,80
175,195,85
180,200,90}
\text{ligne=randomrow(\donne)}
\text{n=item(1,\ligne)}
\text{p=item(2,\ligne)}
\text{l=item(3,\ligne)}
\integer{r=sqrt((\n+\p)^2+\l^2)}

\statement{<div class="wimscenter">
\draw{200,250}{
xrange -20,20
yrange -25,25
polyline black,-20,0,0,0,0,-20,10,-20,10,0,20,0
circle 8,-18,20,black
filledcircle 8,-18,18,red
polyline black,-4.5,8,-6,8,-6,14,-5,15,1,15,2,14,2,8,0.5,8
segment -4.5,13.5,-4.5,0,black
segment 0.3,13.5,0.3,0,black
polyline black,-2.25,0,-2.25,9,-1.75,9,-1.75,0
circle -2,17,20,black
dsegment 0,17,7,-16,black
text black,5,0,medium,?
}
</div>
\name_enonce[1] \nom \name_enonce[2] \(\n \ cm), \name_enonce[3] \(\p\ cm\) \name_enonce[4] \(\l \ cm\).
\name_question[1] \nom \name_question[2] (\name_question[3])?
}

\answer{\name_answer}{\r}{type=default}
