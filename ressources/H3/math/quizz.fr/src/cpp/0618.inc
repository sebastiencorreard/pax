\title{Question 0618 Conversion}
\keywords{conversion,masse,length}

\matrix{unite=g,kg
m,km
kg,g
km,m}

\integer{choix18=randint(1..4)}
\integer{a=randint(11..75)*100}
\real{b=\a/1000}
\real{rep=(\choix18<=2)? \b:\a}
\text{enonce=(\choix18<=2)? Convertir &#58; \(\a\) \unite[\choix18;1]=:Convertir &#58; \(\b\) \unite[\choix18;1]=}
\text{enonceb=\unite[\choix18;2]}
\text{feedback=(\choix18<=2)? On rappelle que 1000 \unite[\choix18;1]=1 \unite[\choix18;2].:On rappelle que 1 \unite[\choix18;1]=1000 \unite[\choix18;2]. }
