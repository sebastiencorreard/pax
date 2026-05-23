\title{Question 0906 Addition de fractions décimales }
\keywords{mental_calculation,decimals,addition,fraction}
\integer{a0906=randint(11..30)}
\integer{b0906=randint(1..9)}
\integer{c0906=randint(1..9)}
\integer{type0906=randint(0,1)}
\integer{d0906=\type0906=0?10:100}
\real{rep=\a0906+\b0906/\d0906+\c0906/1000}
\text{enonce=Écriture décimale de : \(\a0906+\frac{\b0906}{\d0906}+\frac{\c0906}{1000}=\)}
\text{enonceb=}
%%%% feedback %%%%
\real{k0906=\b0906/\d0906}
\text{feedback=Rappel : \(\frac{\b0906}{\d0906} = \k0906\).}
