\matrix{sommet=A,B,C,D,E
E,F,G,H,I
M,N,O,P,Q}
\text{sommet=randrow(\sommet)}
\text{sommet=shuffle(\sommet)}

\text{X1=item(1,\sommet)}
\text{X2=item(2,\sommet)}
\text{X3=item(3,\sommet)}
\text{X4=item(4,\sommet)}
\text{X5=item(5,\sommet)}

\integer{xrange=200}
\integer{yrange=200}

\text{dessin=segment 20,80,180,120,black
segment 90,30,110,170,black
segment 20,80,90,30,red
segment 180,120,110,170,red
text black,110,90,medium,\X1
text black,5,70,medium,\X3
text black,100,25,medium,\X2
text black,95,170,medium,\X4
text black,185,120,medium,\X5}
