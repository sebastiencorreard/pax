\title{Question T1120 Factorisation}
\keywords{mental_calculation,literal_calculation,factorization}
%%%%%%%%%%%%%% Question 20 %%%%%%%%%%%%

\integer{a20=randint(1..3)}
\integer{b20=randint(1..5)*randitem(1,-1)}
\integer{c20=randint(4..7)}
\integer{d20=randint(1..5)*randitem(1,-1)}
\integer{e20=randint(1..8)}
\integer{f20=randint(6..10)*randitem(1,1,-1)}
\function{f200=maxima((\a20*x+\b20)*(\c20*x+\d20)+(\a20*x+\b20)*(\e20*x+\f20))}
\function{f201=maxima(\a20*x+\b20)}
\function{f202=maxima(\c20*x+\d20)}
\function{f203=maxima(\e20*x+\f20)}
\function{f204=maxima((\c20*x+\d20)+(\e20*x+\f20))}
\function{temp20=maxima(factor((\a20*x+\b20)*((\c20+\e20)*x+(\d20+\f20))))}

\text{enonce=Factoriser l'expression \(\f200\) en termes du premier degré : }
\text{enonceb=}
\function{rep=\temp20}
\text{feedback=\(\f200\)<br>\({}=(\f201)\)\((\f202+\f203)\)<br>\({}=(\f201)\)\((\f204)\).}
\integer{size=10}
