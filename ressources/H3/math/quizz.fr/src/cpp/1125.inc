\title{Question 1125 Utiliser une équation de droite}
\keywords{mental_calculation,line,equations}


\integer{xM=randint(2,3,4)*randint(-1,1)}
\integer{m=randint(2,3,4)*randint(-1,1)}
\integer{p=randint(2,3,4)*randint(-1,1)}
\function{f=\m*x+\p}
\integer{yM=evalue(\f,x=\xM)}
\text{ftxt=pari(\f)}
\text{ptxt=\p<0?\p:+\p}
\real{rep=\xM}

\text{enonce=M est un point d'ordonnée \yM de la droite D d'équation \(y = \ftxt\) <br>M&#40; }
\text{enonceb= &#59; \yM&#41;}
\text{feedback=Il faut résoudre : \(\yM=\m x_M \ptxt\)}
