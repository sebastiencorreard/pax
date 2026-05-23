\title{Question 1118 Pourcentage d'évolution}
\keywords{mental_calculation,percentage,percents,proportionality}
\real{cm=1+randint(21..37)/100*randint(-1,1)}
\integer{tx=abs(1-\cm)*100}
\text{evol=\cm<1?baisse:hausse}
\integer{rep=\tx}
\real{txbis=\tx/100}
\text{cmbis=\cm<1?1-\txbis:1+\txbis}
\text{enonce=On applique un coefficient multiplicateur de \cm.<br>À quelle \evol, en pourcentage, cela correspond-il &#63;<br>}
\text{enonceb= \(\%\)}
\text{feedback=Le coefficient multiplicateur s'écrit : \(\cm=\cmbis\).<br> Et \(\txbis=\tx \%\) }
