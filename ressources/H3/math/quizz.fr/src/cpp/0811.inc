\title{Question 0811 Pourcentage d'un entier 2}
\keywords{mental_calculation,proportionality,percents,percentage}

\integer{a0811=randint(2,3,4)*10}
\integer{b0811=randint(1..9)*10+randint(1..7)}
\real{temp0811=simplify(\b0811*\a0811/100)}
\real{rep=\temp0811}
\text{enonce=\(\a0811 \%\) de \(\b0811\) }
\text{enonceb=}
\real{ab0811=\a0811/100}
\text{feedback=Rappel : Il faut effectuer l'opération \( \ab0811 \times \b0811 = \temp0811 \) pour obtenir \(\a0811 \%\) de \(\b0811\). }
