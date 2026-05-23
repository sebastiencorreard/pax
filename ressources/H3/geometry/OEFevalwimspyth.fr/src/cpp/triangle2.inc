\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L,M,O,P,R,S)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}
\text{D=item(4,\lettres)}

 \integer{x=randint(-30..30)}
 \integer{y=randitem(1,-1)*sqrt(80^2-(\x)^2)}
 \integer{ty=\y>0?\y+15:\y-5}
 \integer{n1x=-80-\x}
 \integer{n1y=-\y}
 \real{N1=sqrt((\n1x)^2+(\n1y)^2)}
 \integer{n2x=80-\x}
 \integer{n2y=-\y}
 \real{N2=sqrt((\n2x)^2+(\n2y)^2)}
 \integer{ax=\x+10*\n1x/(\N1)}
 \integer{ay=\y+10*\n1y/(\N1)}
 \integer{vx=10*\n2x/(\N2)}
 \integer{vy=10*\n2y/(\N2)}
 \text{dessin=range -100,100,-100,100
triangle -80,0,80,0,\x,\y,black
text black,\x-5,\ty,medium,\A
text black,-90,-5,medium,\B
text black,85,-5,medium,\C
segment \ax,\ay,\ax+\vx,\ay+\vy,red
segment \ax+\vx,\ay+\vy,\x+\vx,\y+\vy,red}

