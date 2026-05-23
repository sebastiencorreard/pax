\title{Question 0718 Calcul de longueur }
\keywords{circle,length}
\real{d=randomitem(3,4,5)}
\real{r=randomitem(1.3,1.4,1.6,1.7)}
\real{x=\d-\r}
\text{fig718=draw(300,300
xrange 0,10
yrange -5,5

segment 2,0,4,0,black
text black,1.8,-0.1,medium,E
segment 2,4,4,0,black
text black,4.1,-0.1,medium,F
segment 2,0,2,4,black
text black,2,4.5,medium,G
text black,2.3,2.5,medium,I
circle 2,0,120,black

arrow2 1.5,0,1.5,4,10,black
text black,1.2,2.4,medium,\d
arrow2 2,-0.5,4,-0.5,10,black
text black,2.8,-0.8,medium,\r
segment 2.5,0,2.5,0.5,black
segment 2.5,0.5,2,0.5,black

)}

\text{fig718=<div class="wimscenter"><img src="\fig718" alt="figure"></div>}
\text{enonce=La figure a été faite à main levée. <br><i> Le cercle est le cercle de centre \(E\) passant par \(F\). <br>\(I\) est sur le cercle.<br>\(I in [EG]\)</i> \fig718 Complète \(GI={}\)}
\text{enonceb=}

\real{rep=\x}
\text{feedback=\(GI+IE=\d\) et \(IE\) est un rayon. Ainsi \(GI+\r=\d\).}
