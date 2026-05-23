\title{Question T1113 Ecriture décimale}
\keywords{mental_calculation,decimals}
%%%%%%%%%%%%%% Question 11 %%%%%%%%%%%%
\integer{c13=randitem(10,100,100)}
\integer{a13=(\c13=10)? randitem(2,5):randitem(2,4,5)}
\integer{b13=\c13/\a13}
\integer{n13=(\c13=10)? randint(3..7):randitem(2,3,3,4,4)}
\real{temp13=(\b13^\n13)*(\a13^\n13)}
\text{enonce=L'écriture décimale de \(\b13^\n13 \times \a13^\n13\) : }
\text{enonceb=}
\integer{rep=\temp13}
\integer{c13=\a13*\b13}
\text{sol13=(\c13>10)? 100:10}
\for{i=2 to \n13}{\text{sol13=(\c13>10)? \sol13,00:\sol13,0}}
\text{sol13=wims(replace internal , by in \sol13)}
\text{feedback=\(\b13^\n13 \times \a13^\n13=\c13^\n13= \sol13 \). }
\integer{size=15}
