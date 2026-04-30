\title{Permuter quatre variables}
\text{prob=Permutation circulaire de quatre variables}

\integer{c=randint(10..50)}
\integer{d=randint(51..99)}

\text{lnalgo=(\alea==1)?\(\begin{array}{|l}
& a  \longleftarrow  b \\\ 
& b  \longleftarrow  c \\\
& c  \longleftarrow  d \\\ 
& d  \longleftarrow  a 
\end{array}\)}
\text{lnalgo=(\alea==2)?\(\begin{array}{|l}
& a  \longleftarrow  d \\\
& b  \longleftarrow  a \\\
& c  \longleftarrow  b \\\
& d  \longleftarrow  c 
\end{array}\)}

\if{\alea==1}{\text{result=\b:\c:\d:\a}}
\if{\alea==2}{\text{result=\d:\a:\b:\c}}

\text{instruction=Écrire un script qui permet d'échanger la valeur des variables
 \( a=\a \) ; \( b=\b \) ; \( c=\c \) et \( d=\d \). En langage naturel, on écrit :
 \lnalgo}

\text{instruction_code=instruction=[a=\a,b=\b,c=\c,d=\d,tmp=0,tmp=a,a=tmp,tmp=b,b=tmp,tmp=c,c=tmp,tmp=d,d=tmp,a=b,b=a,a=c,c=a,a=d,d=a,b=c,c=b,b=d,d=b,c=d,d=c]}
