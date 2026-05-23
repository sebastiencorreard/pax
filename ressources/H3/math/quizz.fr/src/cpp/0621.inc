\title{Question 0621 Fraction}
\keywords{fraction,multiplication}

\matrix{data21=2,3,12,15,18,21,24,27
3,4,12,16,20,24,28,32
2,5,25,30,35,40,45,50
3,5,20,25,30,35,40,45
4,5,15,20,25,30,35,40
5,6,12,18,24,30,36,42
3,7,14,21,28,35,42,48}
\text{l21=randomrow(\data21)}
\integer{n21=randitem(\l21[3..-1])}
\integer{n22=\n21*randint(10,10,10,100)}

\integer{rep=\l21[1]*\n21/\l21[2]}
\text{enonce=Calcule \(\frac{\l21[1]}\l21[2]\) de \(\n21\)&euro; :}
\text{enonceb=&euro;}
\text{feedback=}
