\title{Question 1108 Calcul d'expression pour une valeur donnée}
\keywords{mental_calculation,literal_calculation}
%%%%%%%%%Question 8 %%%%%%%%%%%%%%%%%%%%%%%
\integer{a8=randitem(1,1,2,3)}
\integer{n8=randint(1..3)*random(1,-1)}
\integer{m8=randint(-1,1,2,-2)}
\function{f8=pari(\a8*x^2+\m8*x+\n8)}
\integer{x8=random(-1,-2,-3)}
\real{rep=evalue(\f8,x=\x8)}
\text{enonce=Calculer l'expression \(\f8 \) pour \(x=\x8 \) &#58; }
\text{enonceb=}
\text{feedback=Attention au signe, le carré est toujours positif. \(x^2\) vaut \(1\) lorsque \(x=-1\).}
