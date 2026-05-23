\matrix{lettre=A,B,C
T,I,R
E,F,G
D,E,F}
\text{lettre=randrow(\lettre)}
\text{lettre=shuffle(\lettre)}
\text{X1=item(1,\lettre)}
\text{X2=item(2,\lettre)}
\text{X3=item(3,\lettre)}

\integer{xrange=240}
\integer{yrange=140}

\matrix{chdes=\X1,\X3
\X3,\X1}
\text{chdes=randrow(\chdes)}
\text{Y1=item(1,\chdes)}
\text{Y2=item(2,\chdes)}
\text{dessin=line 20,20,20,120,black
line 20,120,220,120,black
line 20,20,220,120,black
line 21,110,30,110,red
line 30,110,30,119,red
text black,10,115,medium,\X2
text black,10,10,medium,\Y1
text black,230,115,medium,\Y2}
