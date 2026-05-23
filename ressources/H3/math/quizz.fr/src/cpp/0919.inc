\title{Question 0919 Reste de la division euclidienne}
\keywords{mental_calculation,division}
%%%% reste div euclid de b par a
\integer{a4=randint(2..9)}
\integer{b4=randint(11,13,17,19,23,29,31,37,41,43)}
\integer{temp0919=\b4%\a4}
\integer{rep=\temp0919}
\text{enonce=Quel est le reste de la division euclidienne de \(\b4\) par \(\a4\) ? }
\text{enonceb=}
\integer{q4=(\b4-\temp0919)/\a4}
\text{feedback= On a ici : \(\b4=\a4 \times \q4+\temp0919\). }
