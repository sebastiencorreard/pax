\title{Question 1122 Lecture du coefficient directeur de la tangente}
\keywords{mental_calculation,functions,coordinates,tangent,direction,line}
#include "11202122.inc"
\text{img=draw(250,300
\repere
)}
%%% img sol

\integer{temp1=evalue(\tang2,x=\x2+1)}
\integer{x3=\temp1>5.1?\x2-1:\x2+1}
\integer{y3=evalue(\tang2,x=\x3)}
\text{solution=linewidth 5
crosshairsize 5
crosshairs red,\x2,\y2,\x3,\y3
}
\text{img=draw(250,300
\repere
)}
\text{imgsol=draw(250,300
\repere
\solution
)}
\integer{rep=\z2}
\text{enonce=\intro <br><img src="\img" alt="représentation graphique"> <br> Quel est le coefficient directeur <i>a</i> de la tangente à (Cf) au point d'abscisse \x2 &#63;}
\text{enonceb=}
\text{feedback=<img src="\imgsol" alt="représentation graphique"><br>En utilisant les deux points marqués ci dessus \(\frac{\y2-\y3}{\x2-\x3}\)}
