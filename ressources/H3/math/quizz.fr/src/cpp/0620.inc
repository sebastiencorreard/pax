\title{Question 0620 Longueur}
\keywords{geometry,length}

\integer{a=randint(3,4,5)}
\integer{b=\a+randint(1..(\a-1))}
\integer{xmax=2*\a+1.2}
\integer{xc=floor(\xmax)}

\text{dessin=draw(300,100
xrange -0.2,\xmax
yrange -0.2,3.2
parallel 0,0,0,3,1,0,\xc,grey
parallel 0,0,\xc,0,0,1,3,grey
linewidth 3
segment 1,3,1+\a,3,blue
text blue,2.5,2.8,large,1
segment 1,1,1+\b,1,black
fcircle 1,1,8,black
fcircle 1+\b,1,8,black
text black,1,1.7,large,A
text black,1+\b,1.7,large,B
)}

\text{fig20=<img src="\dessin" alt="">}

\rational{rep=\x}
\text{enonce=<table><tr><td>\fig20</td></tr><tr><td> Quelle est la longueur du segment [AB] &#63; </td></tr></table> }
\text{enonceb=unité(s)}
\rational{rep=\b/\a}
\text{feedback=Un carreau a une longueur égale à 1/\a d'unité. }
