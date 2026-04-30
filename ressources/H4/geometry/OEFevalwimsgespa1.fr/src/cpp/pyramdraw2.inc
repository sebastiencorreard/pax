%%%%% dessin de l'objet
\text{pyram=linewidth 3
polyline black,3,5,0,0,10,0,13,5,8,8,10,0
polyline black,0,0,8,8,3,5
dpolyline black,3,5,13,5
}

\text{cadre=
xrange -5,15
yrange -5,15
\pyram
text \color[1],-0.4,-0.5,medium,A
text \color[2],10.3,-0.5,medium,B
text \color[4],2,5,medium,D
text \color[3],13.2,5,medium,C
text \color[5],8,8.5,medium,S
linewidth 5
points blue,0,0,10,0,13,5,3,5,8,8
linewidth 3
\dessin
}
