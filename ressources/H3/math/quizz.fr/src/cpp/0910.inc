\title{Question 0910 Multiplication de décimaux 2 }
\keywords{mental_calculation,multiplication,decimals}
%%%%%% objectif : faire apparaitre le 0,
\real{a0910=random(randint(1..9),randint(11..99))+randint(1..9)/10}
\real{b0910=\a0910>=10?0.01:0.1}
\real{rep0910=\a0910*\b0910}
\real{rep=\rep0910}
\text{enonce=\(\a0910 \times \b0910 =\) }
\text{enonceb=}
\text{feedback=Rappel : multiplier un nombre décimal par 0.1, 0.01 ou 0.001 c'est décaler la virgule de 1, 2 ou 3 chiffres vers gauche. Et ajouter des zéros si besoin.
Ici : \(\a0910 \times \b0910 =\rep0910\)}
