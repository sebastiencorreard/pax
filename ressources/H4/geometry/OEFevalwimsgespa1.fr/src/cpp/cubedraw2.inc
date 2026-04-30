%%%%% dessin de l'objet
\text{cube=linewidth 3
polyline black,0,0,0,10,10,10,10,0,0,0
polyline black,0,10,2,13,12,13,10,10
dpolyline black,0,0,2,3,12,3
dsegment 2,3,2,13,black
polyline black,10,0,12,3,12,13
}

\text{cadre=
xrange -5,15
yrange -5,15
\cube
text \color[1],-0.4,-0.5,medium,A
text \color[2],10.1,-0.5,medium,B
text \color[4],2.6,3,medium,D
text \color[3],12.1,3,medium,C
text \color[5],-1,11,medium,E
text \color[6],10.7,10.8,medium,F
text \color[7],2.6,14.2,medium,H
text \color[8],12.1,14.2,medium,G
linewidth 5
points blue,0,0,0,10,10,10,10,0,2,13,12,13,2,3,12,3
linewidth 3
\dessin
}
