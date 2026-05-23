\title{Question 0604 Prix}
\keywords{proportionality,mental_calculation}
\integer{a=randitem(4,5,6)}
\if{\a==4}{\integer{p=randitem(3,5)}}
\if{\a==5}{\integer{p=randitem(4,6)}}
\if{\a==6}{\integer{p=randitem(4,5)}}\integer{cas=randitem(1,2)}
\integer{k=randint(2..6)}
\integer{b=\a*\k}
\integer{q=\p*\k}
\integer{rep=(\cas==1)? \q:\b }
\text{preambule=\(\a\) cahiers coûtent \(\p\)&euro;.<br>}
\text{enonce=(\cas==1)? \preambule\(\b\) cahiers coûtent :\preambule}
\text{enonceb=(\cas==1)? &euro;.: cahiers coûtent \(\q\)&euro;.}
\text{feedback=}
