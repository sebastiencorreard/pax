\text{Y=shuffle(\B,\C)}

\real{x=randint(4..16)/10}
\real{y=sqrt(1-(\x-1)^2)}
\real{N=sqrt(\x^2+\y^2)/0.1}
\real{N2=sqrt((2-\x)^2+\y^2)/0.1}
\real{x1=\x-\x/\N}
\real{y1=\y-\y/\N}
\real{x2=\x1+(2-\x)/\N2}
\real{y2=\y1-\y/\N2}
\real{x3=\x+(2-\x)/\N2}
\real{y3=\y-\y/\N2}
\text{dessin=range -0.2,2.2,-0.2,1.2
segment \x1,\y1,\x2,\y2,red
segment \x2,\y2,\x3,\y3,red
triangle 0,0,2,0,\x,\y,black
text black,\x,\y+0.14,medium,\A
text black,-0.05,0,medium,\Y[1]
text black,2,0,medium,\Y[2]}
