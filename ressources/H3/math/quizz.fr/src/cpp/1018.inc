\title{Question 1018 Vitesse, distance, durée}
\keywords{mental_calculation,proportionality,velocity}
%%%%%%%%%%% question 3 %%%%%%%%%%%
\integer{v3=randitem(120,80,160)}
\integer{h3=randitem(2,3,4)}
\integer{pm3=randitem(-1,1)}
\integer{h23=\pm3=1 ? \h3 : \h3-1}
\text{hm3=\pm3=1 ? \h23 h 15 min : \h23 h 45 min}
\real{temp3=\v3*\h3+\pm3*\v3/4}
\real{rep=\temp3}
\text{enonce=Quelle est la distance parcourue en \hm3 à \(\v3\) km/h  &#63;<br>Réponse :}
\text{enonceb=km}
\text{t13=\pm3=1 ? et : moins le }
\text{t23=\pm3=1 ? plus : moins}
\text{feedback=En \h3 heure \t13 quart, on parcourt \h23 fois \v3 km \t23 le quart de \v3 km, soit \temp3 km.}
