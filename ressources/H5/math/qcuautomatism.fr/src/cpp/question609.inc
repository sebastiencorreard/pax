\title{Question 609 NS calcul du coefficient directeur}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }
\keywords{quizz,direction,line}
%%% CD %%%%
\rational{m=randomitem(0.5,0.2,0.25,0.1,2,4,5,10)*randitem(1,-1)}
\integer{k=(\m>1)? 1:(1/\m)*randitem(1,-1,2,-2,3,4)}
\integer{xA=\k*randint(-4..4)}
\integer{xB=\k*(\xA+randint(1..6))}
\integer{yA=randint(2..7)}
\integer{yB=\yA+\m*(\xB-\xA)}

\text{enonce=Dans un repère du plan&#44; on considère les points \(A(\xA; \yA)\) et \(B(\xB ; \yB)\).<br>
Le coefficient directeur de la droite \((AB)\) est&nbsp;&#58;}

\real{bad1=1/\m}
\real{bad2=-1/\m}
\real{bad3=-\m}

\text{good=\m}
\text{bads=\bad1,\bad2,\bad3}
\text{feedback=La bonne réponse était \m.<br> Le coefficient directeur de la droite \((AB)\) se calcule avec la formule &nbsp;&#58; \(\frac{y_B-y_A}{x_B-x_A}\).}
