\title{Question 0819 Abscisse ou ordonnée d'un point}
\keywords{mental_calculation,coordinates,plane,fraction}
\integer{pas=random(4,5)} %%%% graduations
\real{invpas=1/\pas}
\real{invpasdeb=-2*\invpas}

\text{A=random(A,B,C)}
\text{cas=random(ord,abs)}
\real{xA=\cas issametext abs ?-1/\pas:randint(1..\pas-1)/\pas}
\real{yA=\cas issametext ord ?-1/\pas:randint(1..\pas-1)/\pas}
\real{temp=0.15}
\real{xAb=\xA-\temp}
\real{yAb=\yA+\temp}


\text{repere=xrange -0.5,1.3
yrange -0.5,1.3

parallel -0.5,\invpasdeb,2,\invpasdeb,0,\invpas,10,grey
parallel \invpasdeb,-0.8,\invpasdeb,2,\invpas,0,10,grey
linewidth 2
segment -0.05,1,0.05,1,black
segment 1,-0.05,1,0.05,black
linewidth 1
arrow -1,0,1.3,0,10,black
arrow 0,-1,0,1.3,10,black
text black,-0.1,-0.05,medium,0 
text black,-0.15,1.05,medium,1 
text black,0.95,-0.1,medium,1 

}
\text{img=draw(180,180
\repere
linewidth 2
crosshairs black,\xA,\yA
text black,\xAb,\yAb,giant,\A 

)}

\integer{quest1=random(1,2)}%%% 1 abs 2 ord
\text{quest2=\quest1==1?abscisse:ordonnée}

\real{rep=\quest1==1?\xA:\yA}
\real{rep0819=\rep}
\text{enonce=<img src="\img" alt=""> <br>Quelle est l'\quest2 du point \A &#63;}
\text{enonceb=}
\text{feedback=Attention, il y a \pas graduations grises entre zéro et un. Chaque graduation représente donc \invpas.<br> Le point \A a pour coordonnées \(\left(\xA; \yA \right)\) son \quest2 est bien égale à \rep0819.}
