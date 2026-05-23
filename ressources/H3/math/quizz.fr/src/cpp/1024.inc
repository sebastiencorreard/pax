\title{Question 1024 Décomposition en facteurs premiers}
\keywords{mental_calculation,primes}
%%%%%%%%%%% question 9 %%%%%%%%%%%

\text{data9=shuffle(2,3,5,7)}
\integer{a9=\data9[1]==7 ? \data9[4] : \data9[1]}
\integer{b9=\data9[2]}
\integer{c9=\data9[3]}
\integer{d9=\a9^2*\b9*\c9}
\text{rep=\a9^2*\b9*\c9|[Alt:[Apick:3,[*],[*],\a9^2,\b9,\c9],[Apick:4,[*],[*],[*],\a9,\a9,\b9,\c9]]}
\text{enonce=Décomposer \d9 en produit de facteurs premiers. <br> Réponse : }
\text{enonceb=}
\integer{t19=\a9^2}
\integer{t29=\b9*\c9}
\text{feedback=On divise \(\d9 \), puis chacun de ses facteurs. On continue 
jusqu'à ne plus pouvoir diviser.<br>Par exemple : \( \d9= \t19 \times \t29 \)
\({} = \a9 \times \a9 \times \b9 \times \c9 \)
\({}= \a9^2 \times \b9 \times \c9\).}
%%%% type de réponse atext  avec otion=symtext
