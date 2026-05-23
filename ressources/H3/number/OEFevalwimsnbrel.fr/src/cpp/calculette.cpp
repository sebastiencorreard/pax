target=calculette1 calculette2 calculette3 calculette4 calculette5
#define TITRE Calculette

\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}


\text{v=wims(values v/10 for v=11 to 99)}
\text{v=shuffle(\v)}
\text{A=randitem(A,B,C,D,E,F)}

#if defined TARGET_calculette1
 \title{TITRE 1}
 \text{calcul=(-\v[1])*(-\v[2])+\v[3]}
 \text{enonce=-\v[1]\times(-\v[2])+\v[3]}
#endif

#if defined TARGET_calculette2
 \title{TITRE 2}
 \integer{a=randint(2,4,5,8,10)}
 \text{calcul=(\v[1]-\v[2])*(\v[3]+\v[4]/\a)}
 \text{enonce=(\v[1]-\v[2])\times(\v[3]+\frac{\v[4]}{\a})}
#endif

#if defined TARGET_calculette3
 \title{TITRE 3}
 \integer{a=randint(2,4,5,8)}
 \real{b=\a*\v[1]}
 \text{calcul=(-\v[1])/(-\b)+\v[2]}
 \text{enonce=\frac{-\v[1]}{-\b}+\v[2]}
#endif

#if defined TARGET_calculette4
 \title{TITRE 4}
 \integer{a=randint(2,4,5,8)}
 \real{b=\a*\v[1]-\v[3]}
 \real{c=\v[1]*\v[2]}
 \text{calcul=(-\c)/(\b+\v[3])}
 \text{enonce=-\frac{\c}{\b+\v[3]}}
#endif

#if defined TARGET_calculette5
 \title{TITRE 5}
 \integer{a=randint(2,4,5,8)}
 \real{c=\v[1]*\v[2]}
 \text{calcul=(-\c)/(\a*\v[3])}
 \text{enonce=\frac{-\c}{\a\times\v[3]}}
#endif

\real{rep=\calcul}

\statement{
Utiliser la calculatrice pour trouver le résultat du calcul suivant :
<div class="wimscenter">\(\A = \enonce)</div>}

\answer{\A}{\rep}{type=numexp}
