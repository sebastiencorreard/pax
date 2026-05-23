\title{Question 0722 Addition de décimaux}
\keywords{decimals,methodical_calculation}
\text{partent=randint(1..3)*10+randint(1..9),randint(4..5)*10+randint(1..9)} %%% part decim
\integer{d0=randint(1..3)*10+randint(1..9)}
\integer{d1=100-\d0}
\integer{dn=randint(4..5)*10+randint(1..9)}
\text{temp=shuffle(6)}
\real{n0=\temp[1]+\d0/100}
\real{m=\temp[2]+\dn/100}
\real{n1=\temp[3]+\d1/100}
\integer{cas=randint(1,2,1)} 
\real{a=\cas=1?\n0:\m}
\real{b=\cas=2?\n0:\m}
\real{c=\n1}
\real{ac=\n0+\n1}
\real{rep=\a+\b+\c}
\text{enonce=\(\a+\b+\c={}\)}

\text{feedback=On peut remarquer que \(\n0+\n1=\ac\). Il reste juste à ajouter \(\m\).}
