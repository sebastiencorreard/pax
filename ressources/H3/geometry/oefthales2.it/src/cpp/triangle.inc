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

\text{dessin=line 20,20,180,130,black
line 20,20,50,180,black 
line 180,130,50,180,red
line 35,100,100,75,red
text black,10,10,medium,\X1
text black,190,135,medium,\X3
text black,35,185,medium,\X2
text black,25,100,medium,\X4
text black,115,70,medium,\X5 }