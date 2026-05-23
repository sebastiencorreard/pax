\title{Question 0612 Durée}

\keywords{pbsolving,time}
\integer{h=randint(1,2)}
\integer{min= \h==1 ? 5*randint(7..10):5*randint(3..8)}
\integer{h1=randint(18..21)}
\integer{m1=5*randint(((65-\min)/5)..11)}
\integer{h2=\h1+\h+1}
\text{h2=(\h2==24)? 0:\h2}
\integer{m2=\min+\m1-60}
\text{m2=(\m2==5)? 05:\m2}
\integer{rep=\h}
\integer{repb=\min}
\text{enonce=Un film commence à \(\h1\, \text{h} \,\m1 \,min\) et se termine à \(\h2\, \text{h} \,\m2 \,min\). Combien de temps dure t-il?}
\text{enonceb=\(\text{h}\)}
\text{enoncec=\(min\)}
