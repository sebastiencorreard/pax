\title{Question 1121 Résolution graphique}
\keywords{mental_calculation,functions,coordinates,equations}
#include "11202122.inc"
\text{img=draw(250,300
\repere
)}

\integer{k=(\y0+\y1)/2}
\text{ptsol=solve(\f=\k,x=-0.1..3.1)}
%%% img sol
\text{solution=linewidth 5
crosshairsize 5
crosshairs red,\ptsol[1],\k,\ptsol[2],\k,\ptsol[3],\k,\ptsol[3],\k
linewidth 2
dsegment -0.1,\k,3,\k,red
}
\text{img=draw(250,300
\repere
)}
\text{imgsol=draw(250,300
\repere
\solution
)}

\integer{rep=items(\ptsol)}
\text{enonce=\intro <br><img src="\img" alt="représentation graphique"> <br> Quel est le nombre de solutions de f (x) = \k &#63;<br>}
\text{enonceb=solutions}
\text{feedback=<img src="\imgsol" alt="représentation graphique"><br> \rep solutions.}
