\title{Question 1016 Conversion m^3 L}
\keywords{mental_calculation,conversion,volume}
%%%%%%%%%%% question 1 %%%%%%%%%%%

\integer{dm1=randint(50..200)*10}
\real{m1=\dm1/1000}
\integer{choix1=randitem(1,2)}
\text{unites1=\choix=1 ? L,m^3 : m^3,L}
\real{donnee1=\choix=1 ? \dm1 : \m1}
\real{rep=\choix=1 ? \m1 : \dm1}
\text{enonce= \(\donnee1 \) \(\unites1[1] ={} \)}
\text{enonceb=\(\unites1[2]\)}
\text{feedback=Il faut savoir que 1 \(L = {}\) 1 \(dm^3\) et que 1 \(m^3 = 1000 dm^3\)}
