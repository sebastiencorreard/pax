\title{Question 0605 Heure}
\keywords{time,conversion,mental_calculation}
\integer{cas=randitem(1,2)}
\rational{q=randitem(1/4,1/4,1/2,3/4,3/4)}
\integer{h=randitem(1,2,3)}
\integer{min=10*randint(1..5)}
\integer{rep=(\cas==1)? \q*60:\h*60+\min}
\text{enonce=(\cas==1)? \(\q\) h= :\(\h\) h \(\min\) min= }
\text{enonceb=min.}
\text{feedback=}
