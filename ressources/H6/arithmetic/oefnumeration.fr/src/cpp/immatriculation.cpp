target=immatriculation

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{b=26}
\text{a=999}
\text{c=wims(charcnt \a)}
\text{programme=pari((immat(a)  = local(c,u,g) ; c=divrem(a-1,\a)~ ; u=c[2]+1 ; a1 = c[1] ; g=[] ;
  for( s = 1,4 ,c = divrem(a1,\b)~; g=concat(c[2]+1,g) ; a1=c[1]) ; return ([g,u]) ;))}
\text{programme=pari((immatinv(a) = a[2] + \a*((a[1][1]-1)*\b^3 + (a[1][2]-1)*\b^2 + (a[1][3]-1)*\b + (a[1][4]-1))))}

\text{maxi=pari(immatinv([[\b,\b,\b,\b],\a]))}
\text{alphabet=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}

\text{voit=pari(c=random\(\maxi-4) ; c+4)}
\text{repnum=pari(\voit-1)}
\text{immatriculation=pari(immat(\voit))}
\text{chiffre=\immatriculation[2]}
\text{cn=wims(charcnt \chiffre)}
\text{chiffre=\cn < \c ? wims(makelist 0 for x = 1 to \c-\cn),\chiffre}
\text{chiffre=wims(items2words \chiffre)}
\text{chiffre=wims(nospace \chiffre)}

\text{lettre=\immatriculation[1]}
\text{lettre=wims(declosing \lettre)}
\text{Imat=\alphabet[\lettre[1]]\alphabet[\lettre[2]]-\chiffre-\alphabet[\lettre[3]]\alphabet[\lettre[4]]}

\text{voit2=pari(c=random\(\maxi-4) ; c+4)}
\text{immatriculation2=pari(immat(\voit2))}
\text{chiffre2=\immatriculation2[2]}
\text{cn=wims(charcnt \chiffre)}
\text{chiffre2=\cn < \c ? wims(makelist 0 for x = 1 to \c-\cn),\chiffre2}
\text{chiffre2=wims(items2words \chiffre2)}
\text{chiffre2=wims(nospace \chiffre2)}
\text{lettre2=\immatriculation2[1]}
\text{lettre2=wims(declosing \lettre2)}
\text{Imat2=\alphabet[\lettre2[2]]\alphabet[\lettre2[1]]-\chiffre-\alphabet[\lettre2[3]]\alphabet[\lettre2[4]]}
\text{N=randint(2..7)}
\text{annee=ceil(\maxi/\N*10^(-6))}

#include "lang.inc"

\text{instruction1=randomrow(\name_matrix_instruction1)}

\statement{<p>\name_statement1</p>

<ul><li>
  \name_matrix_statement[1;] ;
  </li><li>
  \name_matrix_statement[2;] ;
  </li><li>
  \name_matrix_statement[3;].
</li></ul>
 \name_statement2
<ul>
  <li>\name_matrix_statement[4;] ;
  </li><li>\name_matrix_statement[5;]
  </li><li>\name_matrix_statement[6;]
  </li><li>\name_matrix_statement[7;] ;
  </li><li>\name_matrix_statement[8;].
  </li>
</ul>

\instruction1
<div class="wimscenter">\embed{r1,12
default}</div>
<div>\name_instruction2 \embed{r2,12
default}
</div>
<p>\name_instruction3</p>
<div class="wimscenter">\embed{r3,5
default}</div>
}

\answer{}{\repnum}{type=case}{option=nospace}
\answer{}{\Imat2}{type=case}{option=nospace}
\answer{}{\annee}{type=numeric}{option=nospace}
\latex{
\begin{statement}
\name_statement1
\begin{enumerate}
  \item \name_matrix_statement[1;] ;
  \item \name_matrix_statement[2;] ;
  \item \name_matrix_statement[3;] ;
\end{enumerate}
\name_statement2
\begin{enumerate}
  \item \name_matrix_statement[4;] ;
  \item \name_matrix_statement[5;] ;
  \item \name_matrix_statement[6;] ;
  \item \name_matrix_statement[7;];
  \item \name_matrix_statement[8;].
\end{enumerate}

\begin{enumerate}
\item \instruction1
\item \name_instruction2
\item \name_instruction3
\end{enumerate}.
\end{statement}
}
