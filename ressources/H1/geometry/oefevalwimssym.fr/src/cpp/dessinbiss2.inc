\integer{ang1=randint(2..8)*10}
\integer{ang2=\ang1*2}
\text{biss1=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
arc 0,0,2,2,0,\ang1,red
arc 0,0,4,4,\ang1,\ang2,red
segment cos((\ang1/2)*pi/180)*0.7,sin((\ang1/2)*pi/180)*0.7,cos((\ang1/2)*pi/180)*1.3,sin((\ang1/2)*pi/180)*1.3,red
segment cos((\ang2*0.75)*pi/180)*1.6,sin((\ang2*0.75)*pi/180)*1.6,cos((\ang2*0.75)*pi/180)*2.4,sin((\ang2*0.75)*pi/180)*2.4,red
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
text black,cos((\ang2+4)*pi/180)*6,sin((\ang2+4)*pi/180)*6,medium,\nom[3]
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
segment 0,0,9,0,black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}
#if defined TARGET_oefbissect2 || defined TARGET_oefbissect3
\integer{ang1=randint(2..11)*10}
\integer{ang2=\ang1*1.5}
\text{biss2=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
arc 0,0,2,2,0,\ang1,red
arc 0,0,4,4,\ang1,\ang2,red
segment cos((\ang1/2)*pi/180)*0.7,sin((\ang1/2)*pi/180)*0.7,cos((\ang1/2)*pi/180)*1.3,sin((\ang1/2)*pi/180)*1.3,red
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
text black,cos((\ang2+4)*pi/180)*6,sin((\ang2+4)*pi/180)*6,medium,\nom[3]
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
segment 0,0,9,0,black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}
#endif
#if defined TARGET_oefbissect3
\integer{ang1=90}
\integer{ang2=randint(110..170)}
\text{biss3=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
arc 0,0,2,2,0,\ang1,red
arc 0,0,4,4,\ang1,\ang2,red
segment cos((\ang1/2)*pi/180)*0.7,sin((\ang1/2)*pi/180)*0.7,cos((\ang1/2)*pi/180)*1.3,sin((\ang1/2)*pi/180)*1.3,red
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
text black,cos((\ang2+4)*pi/180)*6,sin((\ang2+4)*pi/180)*6,medium,\nom[3]
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
segment 0,0,9,0,black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}
#endif
