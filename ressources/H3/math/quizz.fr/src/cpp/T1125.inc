\title{Question T1125 Somme de fractions}
\keywords{mental_calculation,addition}
%%%%%%%%%%% question 25 %%%%%%%%%%%

\matrix{coefs25=4,6,12
6,8,24
6,9,18
8,12,24
9,12,36}
\integer{choix25=randint(1..rows(\coefs25))}
\integer{den251=\coefs25[\choix25;1]}
\integer{num251=\den251+randitem(1,-1)}
\integer{den252=\coefs25[\choix25;2]}
\integer{num252=\den252+randitem(1,-1)}
\integer{den253=\coefs25[\choix25;3]}
\integer{num253=\num251*(\den253/\den251)}
\integer{num254=\num252*(\den253/\den252)}
\integer{num255=\num253+\num254}

\rational{rep=maxima(\num251/\den251+\num252/\den252)}
\text{enonce=Exprimer sous forme d'une fraction irréductible, la somme \(\frac{\num251}{\den251}+\frac{\num252}{\den252}\) : }
\text{enonceb=}
\text{feedback=Le plus petit dénominateur commun est \den253.<br>\(\frac{\num251}{\den251}+\frac{\num252}{\den252}=\frac{\num253}{\den253}+\frac{\num254}{\den253}=\frac{\num255}{\den253}\).}
\integer{size=6}
