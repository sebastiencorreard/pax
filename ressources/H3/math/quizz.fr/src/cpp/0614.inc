\title{Question 0614 Changement d'heure}

\keywords{pbsolving,clock,addition}
\integer{h=randint(7..20)}
\integer{a=5*randint(4..9)}
\integer{choix14=randitem(1,2)}
\text{action=(\choix14==1)? enlève:ajoute}
\integer{m=(\choix14==1)? 5*randint(1..(\a/5-1)):5*randint((13-\a/5)..11)}
\integer{rep=(\choix14==1)? \h-1:\h+1}
\integer{repb=(\choix14==1)? 60+\m-\a:\a+\m-60}
\text{m=(\m==5)? 05:\m}
\text{enonce=Si on \action \(\a\) min à \(\h\, \text{h} \,\m \,min\). Quelle heure obtient-on ?<br>}
\text{enonceb=\(\text{h}\)}
\text{enoncec=\(min\)}
