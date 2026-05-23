\title{Question 1026 Multiplication par un décimal}
\keywords{mental_calculation,multiplication,decimals,methodical_calculation}

%%%%%%%%%%% question 11 %%%%%%%%%%%

\integer{choix11=randitem(1,1,2)} #1 -> 1.25 sinon -> 0.75
\integer{a11=randitem(12,16,20,24)}
\real{m11=\choix11=1 ? 1.25 : 0.75}
\real{temp11=\a11*\m11}
\real{rep=\temp11}
\text{enonce=\(\m11 \times \a11 ={}\)}
\text{enonceb=}
\integer{b11=\a11/4}
\text{feedback111=\(1.25 \times \a11=1 \times \a11+0,25 \times \a11\)\({}=\a11+\frac{1}{4} \times \a11 = \a11 + \b11 = \temp11\)}
\text{feedback211=\(0.75 \times \a11=\frac{3}{4} \times \a11=\frac{\a11 \times 3}{4} \)\({}= \frac{\a11 }{4}\times 3=\b11 \times 3 = \temp11\)}

\text{feedback=\choix11=1 ? \feedback111 : \feedback211}
