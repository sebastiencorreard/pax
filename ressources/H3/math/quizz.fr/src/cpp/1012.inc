\title{Question 1012 Multiplication réfléchie}
\keywords{mental_calculation,multiplication,methodical_calculation}
%%%%%%%%%%%%% question 12 %%%%%%%%%%%%%
\matrix{quest12=4,0.25;
0.2,10;
0.2,5;
0.5,20}
\text{quest12=randomrow(\quest12)}
\matrix{quest12b=12.2,10;
13.4,10;
11.2,10;
10,4.5}
\text{quest12b=randomrow(\quest12b)}
\integer{cas12=random(1,2)}
%%%%%% 1 : on laisse l'ordre sinon on inverse
\text{a12=\cas12=1?\quest12[1]:\quest12[2]}
\text{b12=\cas12=1?\quest12b[1]:\quest12b[2]}
\text{c12=\cas12=2?\quest12[1]:\quest12[2]}
\text{d12=\cas12=2?\quest12b[1]:\quest12b[2]}
\integer{rep=\a12*\b12*\c12*\d12}
\text{enonce= \(\a12 \times \b12 \times \c12 \times \d12=\)}
\text{enonceb=}
%%%% feedback %%%%
\integer{k12=\quest12[1]*\quest12[2]}
\integer{k12b=\quest12b[1]*\quest12b[2]}
\text{feedback=Il faut regrouper les termes pour faciliter l'opération. Ici : \(\quest12[1] \times \quest12[2]=\k12\) et \(\quest12b[1] \times \quest12b[2]=\k12b\).}
