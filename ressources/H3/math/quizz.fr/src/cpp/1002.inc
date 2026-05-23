\title{Question 1002 Somme entier fraction}
\keywords{mental_calculation,addition,subtraction,integers,fraction}
\integer{a=randint(2..9)}
\integer{b=randint(3,4,6,7)}
\text{op=random(+,-)}
\rational{temp2=\op issamecase +?simplify(\a+1/\b):simplify(\a-1/\b)}
\rational{rep=\temp2}
\text{enonce=\op issamecase +?\(\a + \frac{1}{\b}={}\):\(\a - \frac{1}{\b}={}\)}
\text{enonceb=}
%%%% feedback %%%%
\integer{k2=\a * \b}
\text{feedback=Rappel : \(\a=\frac{\a \times \b}{\b}\) donc \enonce \(\frac{\k2 \op 1}{\b}={}\)
\(\temp2 \).}
