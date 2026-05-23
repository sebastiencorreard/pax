\title{Question 1010 Calcul d'un pourcentage}
\keywords{mental_calculation,percentage,proportionality }
%%%%%%%%%%%%%% Question 10 %%%%%%%%%%%%
%%%% a10 % de b10
\integer{a10=randint(2..9)*10}
\integer{b10=randint(2..9)*10}
\integer{temp10=simplify(\b10*\a10/100)}
\text{enonce=\(\a10 \%\) de \(\b10\) : }
\text{enonceb=}
\integer{rep=\temp10}
\real{ab10=\a10/100}
\text{feedback=Rappel : Il faut effectuer l'opération \( \ab10 \times \b10 = \temp10 \) pour obtenir \(\a10 \%\) de \(\b10 \). }
