\title{Question 1117 Calcul de vitesse}
\keywords{mental_calculation,velocity}
\matrix{quest=20,3;10,6;15,4;30,2}
\text{quest=randomrow(\quest)}
\text{temp=\quest[1]}
\text{distance=random(10,20,30)}
\integer{rep=\distance/(\temp)*60}
\integer{feed1=\quest[2]}
\text{enonce=Si l'on parcourt \distance km en \temp minutes, alors la vitesse moyenne est &#58;<br>}
\text{enonceb= km/h}
\text{feedback=Il faut \feed1 fois \temp minutes pour faire une heure.}
