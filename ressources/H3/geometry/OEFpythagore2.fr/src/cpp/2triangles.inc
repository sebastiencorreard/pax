\matrix{lettre=A,B,C,D
T,I,R,J
E,F,G,H
D,E,F,G}
\text{lettre=randrow(\lettre)}
\text{lettre=shuffle(\lettre)}
\text{X1=item(1,\lettre)}
\text{X2=item(2,\lettre)}
\text{X3=item(3,\lettre)}
\text{X4=item(4,\lettre)}

\integer{xrange=240}
\integer{yrange=140}

\integer{des_a=random(80..160)}

\text{dessin=segment 20,20,20,120,black
segment 20,120,220,120,black
segment 20,20,220,120,black
segment 20,20,\des_a,120,black
text black,10,125,medium,\X2
text black,10,10,medium,\X1
text black,225,125,medium,\X3
text black,\des_a,125,medium,\X4}

\if{\symbrect!=no}{
 \text{dessin=\dessin
segments 21,110,30,110,30,110,30,119}
}

