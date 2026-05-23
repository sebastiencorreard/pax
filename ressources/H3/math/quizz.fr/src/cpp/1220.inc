\title{Question 1220 Coefficient directeur de la tangente}
\keywords{mental_calculation,derivative,tangent}

\integer{k=randint(1,2,3)*random(-1,1)}
\function{f=maxima(x^3+\k)}
\function{df=diff(\f,x)}
\integer{x0=randint(-1,1,-1,1,2,-2)}
\integer{rep=evalue(\df,x=\x0)}


\text{enonce=Coefficient directeur de la tangente au point d'abscisse \(\x0\) de la courbe d'équation \(y = \f \)<br> Réponse &#58; }
\text{enonceb=}
\text{feedback=La dérivée est égale à \(\df\), il suffit de prendre sa valeur pour \(x=\x0\).}
