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
text \color[6],5,-0.5,medium,I
text \color[7],8,5.5,medium,J
text \color[8],0.5,2.5,medium,K
text \color[9],11.8,2.5,medium,L
text \color[10],4,3,medium,M
text \color[11],9,3,medium,N
text \color[12],11,7.2,medium,O
text \color[13],5,7,medium,P
linewidth 5
points blue,0,0,10,0,13,5,3,5,8,8
points green,5,0,8,5,1.5,2.5,11.5,2.5,4,4,9,4,5.5,6.5,10.5,6.5
linewidth 3
\dessin
}
