\title{Question 0827 Conversion cm^3 L}
\keywords{mental_calculation,conversion,volume}
%%%%%%%%%%% question 1 %%%%%%%%%%%

\integer{dm1=randint(50..200)*10} %%% L
\real{m1=\dm1/1000} %%% cm^3
\integer{choix=random(1,2)}
\text{unites1=\choix=1 ? L,cm^3 : cm^3,L}
\real{donnee1=\choix=1 ? \m1 : \dm1}
\real{rep=\choix=1 ? \dm1 : \m1}
\text{enonce= \(\donnee1 \) \(\unites1[1] ={} \)}
\text{enonceb=\(\unites1[2]\)}
\text{feedback=Il faut savoir que 1 \(L = {}\) 1 \(dm^3\) et que 1 \(dm^3 = 1000 cm^3\)}
