\title{Question 1114 Abscisse ou ordonnée d'un point}
\keywords{mental_calculation,coordinates,plane}
\text{pts=shuffle(A,B,C)}
\text{A=\pts[1]}
\text{B=\pts[2]}
\text{C=\pts[3]}
\matrix{coord=2,3,4,1,1,2,;4,3,3,1,1,2,;4,3,2,1,1,2}
\text{coord=randomrow(\coord)}
\integer{xA=\coord[1]}
\integer{yA=\coord[2]}
\integer{xB=\coord[3]}
\integer{yB=\coord[4]}
\integer{xC=\coord[5]}
\integer{yC=\coord[6]}
\real{temp=0.4}
\real{xAb=\xA}
\real{yAb=\yA+\temp}
\real{xBb=\xB+\temp}
\real{yBb=\yB}
\real{xCb=\xC-\temp}
\real{yCb=\yC}

\text{repere=xrange -1,5.5
yrange -1,4.5
parallel 0,0,5,0,0,1,6,grey
parallel 0,0,0,4,1,0,6,grey
parallel -0.2,1,0.2,1,0,1,4,black
parallel 1,-0.2,1,0.2,1,0,5,black
arrow -1,0,5,0,15,black
arrow 0,-1,0,4,15,black
text black,-0.3,-0.1,medium,0 
text black,-0.5,1.1,medium,1 
text black,-0.5,2.1,medium,2 
text black,-0.5,3.1,medium,3 
text black,-0.5,4.1,medium,4 
text black,0.9,-0.3,medium,1 
text black,1.9,-0.3,medium,2 
text black,2.9,-0.3,medium,3
text black,3.9,-0.3,medium,4
text black,4.9,-0.3,medium,5

}
\text{img=draw(250,300
\repere
linewidth 2
fpoly white,\xA,\yA,\xB,\yB,\xC,\yC,\xA,\yA
polyline black,\xA,\yA,\xB,\yB,\xC,\yC,\xA,\yA
crosshairs black,\xA,\yA,\xB,\yB,\xC,\yC
text black,\xAb,\yAb,giant,\A 
text black,\xBb,\yBb,giant,\B 
text black,\xCb,\yCb,giant,\C 
)}
\text{quest=\A,\xA,\yA,\B,\xB,\yB,\C,\xC,\yC}
\text{choix=random(1,4,7)}
\integer{quest1=random(1,2)}%%% 1 abs 2 ord
\text{quest2=\quest1==1?abscisse:ordonnée}
\integer{rep=\quest1==1?\quest[\choix+1]:\quest[\choix+2]}
\text{enonce=<img src="\img" alt=""> <br>Quel est l'\quest2 du point \quest[\choix] &#63;}
\text{enonceb=}
\text{feedback=Le point \quest[\choix] a pour coordonnées (\quest[\choix+1]&#59; \quest[\choix+2]) son \quest2 est bien égale à \rep.}
