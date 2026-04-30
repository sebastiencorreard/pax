\observation{Dans cet exercice, on demande la somme a+b ou alors la différence a-b.
 L'élève doit remarquer que a ou b est divisible par un certain nombre (par exemple 5)
 qui apparaît dans les instructions python disponibles. 
<br>Ensuite, il doit coder un programme du type "tant que a est positif, on lui retire 5
 et on ajoute ou on soustrait 5 à b".}

\integer{op=randint(1..2)}

\if{\op==2}{
\text{num=(\alea==1)?a=\a,b=\b:b=\b,a=\a}
\integer{result=(\alea==1)?\a-\b:\b-\a}
\text{tc=(\alea==1)?a-b:b-a}
\text{motop=différence entre \(\num[1]\) et \(\num[2]\)}}{
\integer{result=\a+\b}
\text{tc=a+b}
\text{motop=somme de \(a=\a\) et \(b=\b\)}
}

\text{pr=additions ou soustractions,\motop,\tc}

\integer{d=1}
\text{instruction_code=instruction=[a=\a,b=\b,while a>0:,while b>0:,a=a+\d,a=a-\d,b=b-\d,b=b+\d,print(a),print(b),print(-a),print(-b),&#32;&#32;]}
