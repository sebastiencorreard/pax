\title{Question 0319 Combien de fois}
\keywords{mental_calculation,division,multiplication}
\matrix{quest=45,5;20,5;35,5;24,6;12,3;27,3;36,4;54,6}
\text{quest=randomrow(\quest)}
\integer{a=\quest[1]}
\integer{b=\quest[2]}
\integer{rep=\a/\b}
\text{enonce=Dans \(\a\), combien de fois \(\b\) &#63;}
\text{enonceb=}
\text{feed1=random(\(\a=\b \times \c\),\(\a \div \rep = \c\))}
\text{feedback= On a bien \feed1}
