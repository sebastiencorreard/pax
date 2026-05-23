\title{Question 1127 Théorème de Thalès}
\keywords{mental_calculation,proportionality}

%%%(CE/CF = EB/AF) = k
\integer{k=randint(2,3)}
\text{quest=randint(11,7,13)}

\text{data13=\k*\quest,\k*,\quest,randint(2,3,4,5)}
\real{EB13=randint(2,3,4,5)}
\real{rep=\quest*\k}
\real{AF13=\quest}
\real{EC13=\EB13*\k}


\text{fig13=draw(230,115
xrange 0,200
yrange 0,200
line 20,80,180,120,black
line 90,30,110,170,black
line 20,80,90,30,black
line 180,120,110,170,black
text black,90,25,medium,F
text black,105,95,medium,C
text black,100,57,medium, ?
text black,90,140,medium,\EC13
text black,10,75,medium,A

text black,45,45,medium,\AF13
text black,100,200,medium,E
text black,185,150,medium,B
text black,145,170,medium,\EB13
)}
\text{fig13=<img src="\fig13" alt="">}
\text{enonce=<table><tr><td> \fig13 </td><td> (AF) // (EB) <br>Déterminer FC : }
\text{enonceb=</td></tr></table>}
\text{feedback=On doit avoir (d'après le théorème de Thalès) : \(CE/CF = EB/AF\) ce qui nous donne ici : \({{\EC13}\over{FC}} = {{\EB13}\over{\AF13}}\). On calcule la réponse par proportionnalité.}
