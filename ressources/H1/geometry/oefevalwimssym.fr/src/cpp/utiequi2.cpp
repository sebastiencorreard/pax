target=oefutiequi2
#define NUM 2
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry,perpendicular_bisector}
\text{dessinmod=text black,15,95,medium,C
segment -100,-55,-100,-45,black
text black,10,140,medium,(d)
segment -100,-50,0,80,black
segment 100,-50,0,80,black}

\text{med1=draw(300,300
xrange -150,150
yrange -150,150
rotate 40
segment 0,-150,0,150,black
segment -100,-50,100,-50,black
segment -48,-44,-52,-56,red
segment -52,-44,-56,-56,red
segment 48,-56,52,-44,red
segment 52,-56,56,-44,red
segment 100,-55,100,-45,black
segment 0,-40,10,-40,red
segment 10,-40,10,-50,red
text black,-110,-55,medium,A
text black,105,-55,medium,B
\dessinmod
)}

\text{fig=\med1}

\text{t1=Le point C appartient,à la médiatrice,du segment [AB].}
\text{t2=Donc le point C est,à égale distance,des deux extrémités du segment.}
\text{t3=J'en déduis,que AC = BC.}
\text{t4=Conclusion : Le triangle ABC,est un triangle isocèle,de sommet C.}
\text{size=200x40}
\statement{
#include "stat_utiequi.inc"
}

\answer{}{\t1}{type=dragfill}
\answer{}{\t2}{type=dragfill}
\answer{}{\t3}{type=dragfill}
\answer{}{\t4}{type=dragfill}
