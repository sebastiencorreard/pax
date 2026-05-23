\title{Question 0812 Ecriture décimale d'une fraction}
\keywords{mental_calculation,decimals,fraction}
 a sur b
\integer{a=randint(1,2,3,4,6,7,8,9)}
\integer{b=5}

\real{rep=simplify(\a/\b)}
\text{repfeed=\rep}
\text{rep=\rep|wims(replace internal . by , in \rep)} %%% deux solutions avec ou sans la virgule
\integer{asol=2*\a}

\text{enonce=Ecriture décimale de \(\frac{\a}{\b}\) &#58; }
\text{enonceb=<div class="wims_instruction">Sans zéros inutiles</div>}
\text{feedback=Rappel :\(\frac{\a}{\b}=\frac{\asol}{10}=\repfeed\).}
%%%% anstype case
