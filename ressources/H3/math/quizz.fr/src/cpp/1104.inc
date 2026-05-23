\title{Question 1104 Ecriture décimale et puissance de 10}
\keywords{mental_calculation,decimals,power}
%%%%%%%% Question 4
\integer{a4=randint(2,3,4,5)}
\integer{b4=random(7..9)-\a4}
\integer{n4=randint(2,1,3)}
\integer{c4=randint(2,3,4,5)}
\integer{m4=randint(2,2,3)}
\real{rep=\c4*10^\m4+\a4+\b4*10^-\n4 }
\real{temp4=10^-\n4}
\real{temp4b=\c4*10^\m4}
\text{enonce=Ecriture décimale de \(\c4 10^\m4+\a4+\b4 10^-\n4\) : }
\text{enonceb=}
\text{feedback=Rappel : \(10^-\n4=\temp4\) et \(\c4*10^\m4=\temp4b\)}
