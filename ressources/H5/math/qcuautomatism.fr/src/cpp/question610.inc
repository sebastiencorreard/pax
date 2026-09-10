\title{Question 610 NS rôle du coefficient directeur}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }
\keywords{quizz,direction,line}
%%% CD %%%%
\integer{yA=randint(1..7)*randitem(1,1,-1)}
\real{m=randint(1..9)/10*randitem(-\yA/abs(\yA),-\yA/abs(\yA),\yA/abs(\yA))}

\text{enonce=Dans un repère du plan&#44; on considère la droite \(d\) de coefficient directeur \(\m\) et
passant par le point \(A(0 ; \yA)\).<br>
On note \(B\) le point de la droite \(d\) dont l’abscisse est égale à \(1\).<br>
L’ordonnée du point \(B\) est égale à &nbsp;&#58;}

\real{g=\yA+\m}
\real{bad1=\yA-\m}
\real{bad2=\yA+1}
\real{bad3=(\yA+\m)/2}

\text{good=\g}
\text{bads=\bad1,\bad2,\bad3}
\text{feedback=La bonne réponse était \g.<br> En effet&#44; par propriété du coefficient directeur&#44; comme l'abscisse augmente de 1 entre celle de \(A\) et celle de \(B\) alors 
l'ordonnée évolue de \(\m\) entre celle de \(A\) et celle de \(B\).}
