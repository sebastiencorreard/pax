\title{Question T1122 Calcul et puissance}
\keywords{mental_calculation,exponent,power}
%%%%%%%%%%%%%% Question 22 %%%%%%%%%%%%

\integer{deg22=randitem(2,3,3)}
\integer{a22=(\deg22=2)? randint(2..5):randitem(2,2,2,3,3,4)}
\integer{b22=(\deg22=2)? (\a22^2)*randint(1..3):\a22^3}
\integer{a221=\a22^\deg22}
\integer{temp22=\b22/\a221}

\text{enonce=\(\b22 \times \left ( \frac{1}{\a22}\right ) ^\deg22\)=  }
\text{enonceb=}
\integer{rep=\temp22}
\text{feedback=\(\b22 \times \left ( \frac{1}{\a22}\right ) ^\deg22=\b22 \times \frac{1}{\a221}=\temp22\).}
\integer{size=8}
