\title{Question 1115 Arrondi}
\keywords{mental_calculation,decimals}
\integer{a0=randint(1..9)}
\integer{a1=randint(1..9)}
\integer{a2=randint(1..9)}
\integer{a3=randint(1..8)}
\integer{a4=randint(1..9)}
\integer{a5=randint(1..9)}
\integer{a6=randint(1..9)}
\text{quest=\a0.\a1\a2\a3\a4\a5\a6}
\integer{a3b=\a4>4?\a3+1:\a3}
\real{rep=\a0.\a1\a2\a3b}
\text{enonce=Arrondi au millième de \quest.}
\text{enonceb=}
\text{feedback=\a0.\a1\a2\a3\a4\a5\a6 est-il plus proche de \a0.\a1\a2\a3 ou de \a0.\a1\a2\a3b &#63;}
