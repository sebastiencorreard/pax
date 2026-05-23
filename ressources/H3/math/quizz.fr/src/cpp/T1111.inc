\title{Question T1111 Opération en mots}
\keywords{mental_calculation }
%%%%%%%%%%%%%% Question 11 %%%%%%%%%%%%
\integer{a11=randint(2..9)*randitem(-1,1)}
\integer{b11=randint(2..9)}
\text{operation1110=wims(shuffle double,triple)}
\text{operation1111=wims(shuffle somme,différence)}
\text{prov11=(\a11>0)? \a11:(\a11)}
\text{temp110=(\operation1110[1] issametext double)? 2*\prov11:3*\prov11}
\text{temp11=(\operation1111[1] issametext somme)? \temp110+\b11:\temp110-\b11}
\text{enonce=La \operation1111[1] du \operation1110[1] de \(\a11\) et de l'inverse de \(\frac{1}{\b11}\) : }
\text{enonceb=}
\integer{rep=\temp11}
\text{feedback=Il faut effectuer l'opération \( \temp11 \) pour obtenir la \operation1111[1] du \operation1110[1] de \(\a11\) et de l'inverse de \(\frac{1}{\b11}\). }
\integer{size=6}
