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
text \color[9],5,-0.5,medium,I
text \color[10],7,4.2,medium,J
text \color[11],1.4,1.8,medium,K
text \color[12],11.5,1.8,medium,L
text \color[13],5,9.5,medium,M
text \color[14],7,14.5,medium,N
text \color[15],0,12.2,medium,O
text \color[16],11.3,11.8,medium,P
text \color[17],-0.8,5.5,medium,Q
text \color[18],10.3,5.5,medium,R
text \color[19],12.3,8.5,medium,S
text \color[20],2.2,8.5,medium,T
linewidth 5
points blue,0,0,0,10,10,10,10,0,2,13,12,13,2,3,12,3
points green,5,0,7,3,1,1.5,11,1.5,5,10,7,13,1,11.5,11,11.5,0,5,10,5,2,8,12,8
linewidth 3
\dessin
}
