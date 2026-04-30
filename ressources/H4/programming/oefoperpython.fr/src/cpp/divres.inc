\observation{Dans cet exercice, l'élève doit coder un programme du type "tant que a est supérieur à b,
 on lui retire b et on ajoute 1 à une variable m si on besoin du quotient".}

\integer{b=(\alea==1)?randint(100..200):randint(400..1000)}

\integer{q=randint(11..50)}
\integer{r=randint(51..90)}
\integer{num=randint(91..200)}
\integer{a=(\alea==1)?\num*\q+\r:\num}
\integer{b=(\alea==1)?\num:\num*\q+\r}

\text{rr=(\alea1==1)?le quotient:le reste}

\if{\alea1==1}{
\integer{cc=pari(floor(\a \ \b))}
\integer{ccc=pari(floor(\b \ \a))}
\text{tc=(\alea==1)?\frac{a}{b}:\frac{b}{a}}
}{\integer{cc=\a%\b}
\integer{ccc=\b%\a}
\text{tc=(\alea==1)?a\%b:b\%a}
}
\integer{result=(\alea==1)?\cc:\ccc}

\text{num=(\alea==1)?a=\a,b=\b:b=\b,a=\a}
\text{pr=divisions,division euclidienne  de \(\num[1]\) par \(\num[2]\),\tc}

\text{instruction_code=instruction=[a=\a,b=\b,m=0,while a>b:,while b>a:,a=a-b,b=b-a,m=m+1,m=m-1,print(a),print(b),print(m),&#32;&#32;]}
