\title{Question 0721 Pourcentage d'un entier 3}
\keywords{mental_calculation,proportionality,percents,percentage}
%%% de 0811 %%%
\integer{a=randomitem(1,1,2)*10+randomitem(0,5,5)}
\integer{b=randomitem(2,3,4)*10+100}
\real{temp=simplify(\b*\a/100)}
\real{rep=\temp}
\text{enonce=\(\a \%\) de \(\b\) }
\text{enonceb=}
\real{ab=\a/100}
\text{feedback=Rappel : Il faut effectuer l'opération \( \ab \times \b = \temp \) pour obtenir \(\a \%\) de \(\b\). }
