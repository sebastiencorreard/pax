target=heure

#include "header.inc"

\title{L'heure de la journée}

\matrix{frac=1,3
2,3
5,3
3,2
1,4
1,5
3,5
4,5
5,3
5,4
}
\text{frac=randomrow(\frac)}
\integer{p=\frac[1]}
\integer{q=\frac[2]}
\text{tt=24*\q/(\p+\q)}
\integer{h=floor(\tt)}
\integer{m=(60*\tt-60*\h)}

\statement{
On a demandé à Madmath l'heure qu'il était, et il a répondu :
"Il reste de la journée \p/\q de ce qui est déjà passé."
<p>
Quelle heure est-il ?
\embed{r1,3} h \embed{r2,3} min
</p>
(en 24 heures ; la journée commence à minuit = 0h).
}

\reply{Heure}{\h}
\reply{min}{\m}


