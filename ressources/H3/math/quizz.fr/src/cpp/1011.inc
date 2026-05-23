\title{Question 1011 Ecriture scientifique}
\keywords{mental_calculation,multiplication,scientific_notation,power}
\integer{a11=randint(2..9)}
\integer{b11=randint(2..9)*10}
\integer{c11=randint(2..9)*100}
\integer{exp11=randint(21..35)}
\integer{cas11=random(1,2)}
\integer{q11=\cas11=1?\a11+\b11:\a11+\b11+\c11}
\real{dec11=simplify(\q11/10^\cas11)}
\integer{exp11rep=\exp11+\cas11}
\text{rep=\dec11*10^\exp11rep}
\text{bad111=\dec11*10^\exp11}
\text{bad211=\q11*10^\exp11}
\integer{temp11=\exp11-\cas11}
\text{bad311=\dec11*10^\temp11}
\text{enonce=Ecriture scientifique de \(\q11 \times 10^\exp11 \) }
\text{enonceb=}
\text{feedback=Rappel : \(\q11=\dec11 \times 10^\cas11\). }
