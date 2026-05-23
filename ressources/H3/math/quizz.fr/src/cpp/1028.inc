\title{Question 1028 Théorème de Thalès}
\keywords{mental_calculation,proportionality}
%%%%%%%%%%% question 13 %%%%%%%%%%%

\integer{choix13=randitem(1,2)} #choix11=1 : question sur FC, sinon sur EC
\text{data13=randomrow(6.5,4,13,2
7.5,4,10,3
8,3,6,4
6,4,8,3
5,6,10,3)}
\real{rep=\data13[1]}
\text{FC13=\choix13==1 ? FC : \data13[4]}
\text{EC13=\choix13==1 ? \data13[4] : EC }
\text{AC13=\choix13==1 ? \data13[3] : \data13[2]}
\text{BC13=\choix13==1 ? \data13[2] : \data13[3]}
\text{quest=\choix13==1 ? \FC13 : \EC13}

\text{ajout13=\choix13==1 ? text black,85,135,medium,\EC13 : text black,100,60,medium,\FC13 }

\text{fig13=draw(230,115
xrange 0,200
yrange 0,200
line 20,80,180,120,black
line 90,30,110,170,black
line 20,80,90,30,black
line 180,120,110,170,black
text black,100,90,medium,C
text black,10,75,medium,A
text black,55,90,medium,\AC13
text black,90,25,medium,F
text black,100,200,medium,E
text black,185,150,medium,B
text black,140,110,medium,\BC13
\ajout13)}
\text{fig13=<img src="\fig13" alt="">}

\text{enonceb=</td></tr></table>}
\text{enonce= <table><tr><td>\fig13 </td><td>Les droites (AF) et (EB) sont parallèles.<br>Déterminer \quest &#58; }
\text{enonceb=</td></tr></table>}
\text{feedback=On doit avoir (d'après le théorème de Thalès) : \(CE/CF = CB/CA\) ce qui nous donne ici : \({{\EC13}\over{\FC13}} = {{\BC13}\over{\AC13}}\). On calcule la réponse par proportionnalité.}
