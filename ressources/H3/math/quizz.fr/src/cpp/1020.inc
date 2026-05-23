\title{Question 1020 Calcul du coefficient directeur}
\keywords{mental_calculation,lines,affine_function,line}
\integer{deltax5=randitem(2,3,5)}
\integer{deltay5=\deltax5*randitem(2,3,4,5)}
\integer{xC5=randitem(1,2,3)}
\integer{yC5=randitem(1,2,3)}
\integer{xD5=\xC5+\deltax5}
\integer{yD5=\yC5+\deltay5}
\real{temp5=\deltay5/\deltax5}
\real{rep=\temp5}
\text{enonce=Dans un repère, on considère les points C(\xC5 ; \yC5) et D(\xD5 ; \yD5). Calculer le coefficient directeur de la droite (CD). <br> Réponse : }
\text{enonceb=}
\text{feedback=On utilise la formule \(m=\frac{y_D-y_C}{x_D-x_C}\). <br>Ici cela nous donne : \(m=\frac{\deltay5}{\deltax5}=\temp5\)}
