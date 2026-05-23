\title{Question T1126 Comparaison}
\keywords{mental_calculation}
%%%%%%%%%%%%%% Question 26 %%%%%%%%%%%%
\integer{q1=randitem(7,8)}
\integer{q2=randitem(10,11)}
\integer{n1=randint(301..310)}
\integer{n2=randint(317..330)}
\integer{n3=(\q2>10)? randint(370..385):randint(340..355)}
\matrix{donnees26=pi,\sqrt{3},\frac{\q1}{3},\n1\times 10^{-2}
\frac{\q2}{3},pi,\sqrt{2},\n2\times 10^{-2}
\n3\times 10^{-2},pi,\frac{\q2}{3},\sqrt{3}}
\integer{choix26=randint(1..rows(\donnees26))}
\text{nombres26=\donnees26[\choix26;]}
\text{let26=a,b,c,d}
\text{mel26=wims(shuffle 1,2,3,4)}
\if{\mel26[1]==1}{\integer{temp26=1}}
\if{\mel26[2]==1}{\integer{temp26=2}}
\if{\mel26[3]==1}{\integer{temp26=3}}
\if{\mel26[4]==1}{\integer{temp26=4}}
\text{nombres26=\nombres26[\mel26[1]],\nombres26[\mel26[2]],\nombres26[\mel26[3]],\nombres26[\mel26[4]]}
\text{rep=\let26[\temp26]}

\text{enonce=Quel est le plus grand nombre parmi les nombres suivants ? <table class="wimsborder"><tr><td>a=\(\nombres26[1]\)</td><td>b=\(\nombres26[2]\)</td><td>c=\(\nombres26[3]\)</td><td>d=\(\nombres26[4]\)</td></tr></table>Le plus grand nombre est le nombre }
\text{enonceb=<div class="wims_instruction">Donner la lettre (minuscule) du nombre correspondant au nombre le plus grand.</div>}
\text{feedback=On peut le vérifier en prenant une valeur approchée des nombres.<br>Rappel : arrondis aux centièmes \(\pi\approx 3.14\), \(\sqrt{2} \approx 1.41\) et \(\sqrt{3} \approx 1.73\)}
\integer{size=3}
