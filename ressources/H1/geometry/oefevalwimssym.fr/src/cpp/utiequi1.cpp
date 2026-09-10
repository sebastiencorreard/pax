target=oefutiequi1
#define NUM 1
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry,perpendicular_bisector}
\text{dessinmod=segment -100,-55,-100,-45,black
text black,10,140,medium,(d)
segment -100,-50,0,80,black
segment 100,-50,0,80,black
text black,15,95,medium,C}
#include "dessinutiequi.inc"

\text{t1=Le point C appartient à la médiatrice du segment [AB].}
\text{t2=Donc le point C est à égale distance des deux extrémités du segment.}
\text{t3=J'en déduis que AC = BC.}
\text{t4=Conclusion : Le triangle ABC est un triangle isocèle de sommet C.}
\text{size=520x40}
\statement{
#include "stat_utiequi.inc"
}

\answer{}{\t1}{type=dragfill}
\answer{}{\t2}{type=dragfill}
\answer{}{\t3}{type=dragfill}
\answer{}{\t4}{type=dragfill}
