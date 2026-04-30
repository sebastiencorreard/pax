\observation{Dans cet exercice, il est demandé : le produit a.b, le quotient de a par b
 ou alors le reste a%b.
<br>Par exemple, si c'est le quotient qui est demandé, l'élève doit coder un programme du type
 "tant que a est supérieur à b, on lui retire b et on ajoute 1 à une variable m".}

\integer{alea1=randint(1..3)}

\text{rr=(\alea1==1)?le produit}
\text{rr=(\alea1==2)?le quotient}
\text{rr=(\alea1==3)?le reste}

\if{\alea1==2 or \alea1==3}{
\if{\alea1==2}{
\integer{c=(\alea==1)?pari(floor(\a \ \b))}
\integer{c=(\alea==2)?pari(floor(\b \ \a))}
\integer{result=\c}
\text{tc=(\alea==1)?\frac{a}{b}}
\text{tc=(\alea==2)?\frac{b}{a}}}
\if{\alea1==3}{
\integer{result=(\alea==1)?\a%\b}
\integer{result=(\alea==2)?\b%\a}
\text{tc=(\alea==1)?a\%b}
\text{tc=(\alea==2)?b\%a}
}}

\integer{result=(\alea1==1)?\a*\b}
\text{num=(\alea==1)?a=\a,b=\b:b=\b,a=\a}

\text{pr1=multiplications ou divisions}
\text{pr=(\alea1==2 or \alea1 ==3)?\pr1,division de \(\num[1]\) par \(\num[2]\),\tc}
\text{pr=(\alea1==1)?\pr1,multiplication  de \(a=\a\) par \(b=\b\),a \times b}

\text{instruction_code=instruction=[a=\a,b=\b,m=0,while a>0:,while b>0:,while a>b:,while b>a:,a=a+1,a=a-1,a=a+b,a=a-b,b=b-1,b=b+1,b=b+a,b=b-a,m=m+a,m=m+b,m=m+1,m=m-1,print(a),print(b),print(m),&#32;&#32;]}
