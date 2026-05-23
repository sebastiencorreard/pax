\title{Question 0415 Ecriture des nombres}
\keywords{mental_calculation,number_writing}

\integer{a1=randint(100,1000)}
\text{atxt=\a1=100?centaines:milliers}
\integer{a0=randint(3..8)}
\integer{a=\a0*\a1}
\text{rtxt=\a1=100?dizaines:randomitem(dizaines,centaines)}

\integer{rep=\rtxt issametext dizaines ? \a/10:\a/100}

\text{enonce=Combien de \rtxt dans \(\a0 \) \atxt &#63; }
\text{enonceb=}

\text{feedback= \(\a0 \) \atxt vaut \(\a\) soit \(\rep\) \rtxt }
