\text{tria=draw(200,200
triangle 80,60,170,140,30,140,black
text black,70,50,medium,A
text black,20,130,medium,B
text black,175,130,medium,C
segment 80,10,80,190,red
)}
\text{triarecta=draw(200,200
triangle 30,50,30,130,170,130,black
square 30,120,10,red
segment 10,90,190,90,red
text black,20,40,medium,A
text black,20,130,medium,B
text black,170,130,medium,C
)}
\text{triarectb=draw(200,200
triangle 30,50,30,130,170,130,black
square 30,120,10,red
segment 100,10,100,190,red
text black,20,40,medium,A
text black,20,130,medium,B
text black,170,130,medium,C
)}
\text{triarectiso=draw(200,200
triangle 60,40,60,140,160,140,black
square 60,130,10,red
segment 20,180,180,20,red
segment 97,145,103,135,red
segment 100,145,106,135,red
segment 55,91,65,97,red
segment 55,94,65,100,red
text black,50,30,medium,A
text black,50,140,medium,B
text black,165,140,medium,C
)}
\text{triaiso=draw(200,200
triangle 100,30,60,150,140,150,black
segment 100,10,100,190,red
segment 125,91,115,97,red
segment 127,94,117,100,red
segment 75,91,85,97,red
segment 73,94,83,100,red
text black,90,20,medium,A
text black,50,150,medium,B
text black,145,150,medium,C
)}
\text{triaequia=draw(200,200
triangle 100,48,40,152,160,152,black
segment 100,10,100,190,red
text black,90,38,medium,A
text black,30,152,medium,B
text black,165,152,medium,C
)}
\text{triaequib=draw(200,200
triangle 100,48,40,152,160,152,black
segment 20,70,190,170,red
text black,90,38,medium,A
text black,30,152,medium,B
text black,165,152,medium,C
)}
\text{carrea=draw(200,200
square 50,50,10,red
square 140,50,10,red
square 50,140,10,red
square 50,50,100,black
segment 100,10,100,190,red
text black,40,40,medium,A
text black,155,40,medium,B
text black,155,150,medium,C
text black,40,150,medium,D
)}
\text{carreb=draw(200,200
square 50,50,10,red
square 140,50,10,red
square 50,140,10,red
square 50,50,100,black
segment 10,10,190,190,red
text black,40,40,medium,A
text black,155,40,medium,B
text black,155,150,medium,C
text black,40,150,medium,D
)}
\text{recta=draw(200,200
square 30,50,10,red
square 160,50,10,red
square 30,140,10,red
rect 30,50,170,150,black
segment 10,100,190,100,red
text black,20,40,medium,A
text black,175,40,medium,B
text black,175,150,medium,C
text black,20,150,medium,D
)}
\text{rectb=draw(200,200
square 30,50,10,red
square 160,50,10,red
square 30,140,10,red
rect 30,50,170,150,black
segment 0,30,200,170,red
text black,20,40,medium,A
text black,175,40,medium,B
text black,175,150,medium,C
text black,20,150,medium,D
)}
\text{losangea=draw(200,200
poly black,100,30,150,100,100,170,50,100
segment 100,10,100,190,red
segment 122,130,128,140,red
segment 120,134,126,144,red
segment 72,60,78,70,red
segment 70,64,76,74,red
segment 80,130,74,140,red
segment 76,130,70,140,red
segment 120,70,126,60,red
segment 124,70,130,60,red
text black,90,20,medium,A
text black,155,100,medium,B
text black,90,170,medium,C
text black,40,100,medium,D
)}
\text{losangeb=draw(200,200
poly black,100,30,150,100,100,170,50,100
segment 10,100,190,100,red
segment 122,130,128,140,red
segment 120,134,126,144,red
segment 72,60,78,70,red
segment 70,64,76,74,red
segment 80,130,74,140,red
segment 76,130,70,140,red
segment 120,70,126,60,red
segment 124,70,130,60,red
text black,90,20,medium,A
text black,155,100,medium,B
text black,90,170,medium,C
text black,40,100,medium,D
)}
\text{cerfa=draw(200,200
poly black,100,20,150,100,100,150,50,100
segment 100,10,100,190,red
circle 124,126,8,red
segment 68,60,74,70,red
segment 66,64,72,74,red
circle 76,126,8,red
segment 126,70,130,60,red
segment 128,74,132,64,red
text black,90,10,medium,A
text black,155,100,medium,B
text black,90,150,medium,C
text black,40,100,medium,D
)}
\text{cerfb=draw(200,200
poly black,100,20,150,100,100,150,50,100
segment 10,100,190,100,red
circle 124,126,8,red
segment 68,60,74,70,red
segment 66,64,72,74,red
circle 76,126,8,red
segment 126,70,130,60,red
segment 128,74,132,64,red
text black,90,10,medium,A
text black,155,100,medium,B
text black,90,150,medium,C
text black,40,100,medium,D
)}
\text{quelc=draw(200,200
poly black,50,50,130,30,170,150,30,150
segment 100,10,100,190,red
text black,40,40,medium,A
text black,135,20,medium,B
text black,175,150,medium,C
text black,20,150,medium,D
)}
\matrix{fig=\tria,triangle quelconque,2
\triarecta,triangle rectangle,2
\triarectb,triangle rectangle,2
\triarectiso,triangle rectangle et isocèle,1
\triaiso,triangle isocèle,1
\triaequia,triangle équilatéral,1
\triaequib,triangle équilatéral,1
\carrea,carré,1
\carreb,carré,1
\recta,rectangle,1
\rectb,rectangle,2
\losangea,losange,1
\losangeb,losange,1
\cerfa,cerf volant,1
\cerfb,cerf volant,2
\quelc,quadrilatère quelconque,2}

