\title{Question 1111 Volume d'un pavé droit}
\keywords{mental_calculation,volume}
\matrix{a=2,5,7;3,4,5;3,5,6;4,5,7}
\text{l=randomrow(\a)}
\text{pave=draw(250,180
xrange -45,490
yrange -30,200
rect 0,0,300,100,black
polyline black,0,100,150,180,450,180,300,100
polyline black,300,0,450,80,450,180
dsegment 0,0,150,80,black
dsegment 150,80,150,180,black
dsegment 150,80,450,80,black
text black,-45,50,small,\l[1] m
text black,120,-5,small,\l[2] m
text black,60,70,small,\l[3] m
)}
\integer{rep=\l[1]*\l[2]*\l[3]}
\text{enonce=<img src="\pave" alt=""><br>Quel est le volume en \(m^3\) de ce pavé droit &#63;}
\text{enonceb= \(m^3\)}
\text{feedback=}
