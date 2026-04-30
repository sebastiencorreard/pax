\title{Permuter trois variables}
\text{prob=Permutation circulaire de trois variables}

\integer{c=randint(10..50)}


\text{lnalgo=(\alea==1)?\(\begin{array}{|l}
& a  \longleftarrow  b \\\
& b  \longleftarrow  c \\\
& c  \longleftarrow  a 
\end{array}\)}
\text{lnalgo=(\alea==2)?\(\begin{array}{|l}
& a  \longleftarrow  c \\\
& b  \longleftarrow  a \\\
& c  \longleftarrow  b 
\end{array}\)}

\if{\alea==1}{\text{result=\b:\c:\a}}{\text{result=\c:\a:\b}}

\text{instruction=Écrire un script qui permet d'échanger la valeur des variables
 \( a=\a \) ; \( b=\b \) et \( c=\c \). En langage naturel, on écrit :
 \lnalgo}

\text{instruction_code=instruction=[a=\a,b=\b,c=\c,tmp=0,tmp=a,a=tmp,tmp=b,b=tmp,tmp=c,c=tmp,a=b,b=a,a=c,c=a,b=c,c=b]}
