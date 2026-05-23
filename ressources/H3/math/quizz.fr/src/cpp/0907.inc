\title{Question 0907 Priorités }
\keywords{mental_calculation,priority_rule,addition,multiplication}
\integer{b0907=randint(5..9)}
\integer{c0907=randint(2..11-\b0907)}
\integer{a0907=\b0907*\c0907+randint(10..40)}
\integer{type0907=randint(-1,1)}
\integer{rep=\a0907+\type0907*\b0907*\c0907}
\text{enonce=\type0907=1? \(\a0907+\b0907 \times \c0907=\):\(\a0907-\b0907 \times \c0907=\)}
\text{enonceb=}
\text{feedback=Rappel : Priorité à la multiplication}
