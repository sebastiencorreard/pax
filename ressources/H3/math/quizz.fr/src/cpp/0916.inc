\title{Question 0916 Mesure d'un angle}
\keywords{mental_calculation,division,fraction,angles}
\integer{type=randint(3,4)} nbr de découpe du cercle
\text{rayons=line 120,0,-120,0,black}
\if{\type=3}{\text{rayons=\rayons
line 0,0,simplify(120*cos(2/3*PI)),simplify(120*sin(2/3*PI)),black
line 0,0,simplify(120*cos(1/3*PI)),simplify(120*sin(1/3*PI)),black}
\text{codages=arc 0,0,50,50,0,60,black
arc 0,0,60,60,60,120,black
arc 0,0,50,50,120,180,black}}
\if{\type=4}{\text{rayons=\rayons
line 0,0,simplify(120*cos(1/4*PI)),simplify(120*sin(1/4*PI)),black
line 0,0,simplify(120*cos(2/4*PI)),simplify(120*sin(2/4*PI)),black
line 0,0,simplify(120*cos(3/4*PI)),simplify(120*sin(3/4*PI)),black}
\text{codages=arc 0,0,50,50,0,45,black
arc 0,0,60,60,45,90,black
arc 0,0,50,50,90,135,black
arc 0,0,60,60,135,180,black
}}
\text{angle=simplify(PI-randint(1..\type-1)/\type*PI)}
\text{coorB=simplify(120*cos(\angle)),simplify(120*sin(\angle))}
\text{fig1=draw(300,170
xrange -150,150
yrange -20,150
line 120,0,-120,0,black
arc 0,0,240,240,0,180,black
\rayons
\codages
text black,0,-5,large,O
text black,-120,-5,large,A
text black,120,-5,large,I
text black,\coorB[1],\coorB[2]+20,large,B
)}
\text{fig1=<div class="wimscenter"><img src="\fig1" alt=""></div>}
\text{enonce=\fig1 I, O et A sont alignés, quelle est la mesure de l'angle de la rotation qui transforme A en B ?}
\text{enonceb= °.}
\integer{rep=simplify(180-\angle/PI*180)}
\text{feedback=Rappel : l'angle plat \(\widehat{IOA}\) mesure \(180^\circ\).}
