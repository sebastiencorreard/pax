\title{Question 1009 Calcul de moyenne }
\keywords{mental_calculation,methodical_calculation,mean}
%%%%%%%%%Question 9 %%%%%%%%%%%%%%%%%%%%%%%
\integer{m9=random(80,100,100,120)}
\integer{som9=random(20,40)}
\integer{som9b=\m9-\som9}
\text{temp9=shuffle(3,4,2,1)}
\integer{temp91=\som9/2+\temp9[1]}
\integer{temp91b=\som9/2-\temp9[1]}
\integer{temp92=\som9b/2+\temp9[2]}
\integer{temp92b=\som9b/2-\temp9[2]}
\matrix{n9=\temp91,\temp92,\temp91b,\temp92b}
\real{rep=\m9/4}
\text{enonce=Moyenne des nombres : \(\n9[1]\) &#59; \(\n9[2]\) &#59; \(\n9[3]\) et \(\n9[4]\). Réponse : }
\text{enonceb=}
\text{feedback=Avant de faire la division par \(4\), il est efficace de regrouper les termes : \(\n9[1]+\n9[3]=\som9\) et \(\n9[2]+\n9[4]=\som9b\)}
