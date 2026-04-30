\title{MF qui teste la divisibilité d'un nombre}
\integer{NN=randint(20..200)}
\integer{dd=randitem(3,5,7,11,13,17,19)*1}

\integer{xt0=randitem(23,29,31,37,41,43,47,53,59)*\dd}
\integer{xt1=randint(1..30)*\dd+1}

\text{prob=MF afin de s'approprier son fonctionnement.}
\text{enonce=PPP de déterminer si un nombre est divisible par
 2. Il utilise l'opérateur <code>%</code> qui renvoie le reste de la division euclidienne.
 <br>
<strong> Exemples :</strong>
<ul>
<li> 12%2=<strong>0</strong> car \(12=2 \times 6 + \bf{0}\)</li>
<li> 23%2=<strong>1</strong> car \(23=2 \times 11 + \bf{1}\)</li>
<li> 25%5=<strong>0</strong> car \(25=5 \times 5 + \bf{0}\)</li>
<li> 27%5=<strong>2</strong> car \(27=5 \times 5 + \bf{2}\)</li>
</ul>
}
\text{nff=divisibilite}

\text{inst=print(\NN,\nff(\NN),\dd)}

\text{question=MLFI "\nff" ayant pour paramètre
 la valeur de \(N\) afin qu'elle détermine si un nombre est divisible par \(\dd\).}

\text{code=
def \nff(N):
  if N%2==0:
    cdc='divisible'
  else:
    cdc='n est pas divisible par'
  return cdc  

\#Test#
\inst
}
\text{x0=divisible}
\text{x1=n est pas divisible par}

\text{post='@@@@'+'\eva1'+'=\nff(\xt0)'+'@@@@'+'\eva2'+'=\nff(\xt1)'}
\text{rtest=[\eva1,[\x0]],[\eva2,[\x1]]}
