\title{MF qui effectue une opération de base}
\integer{aa=randitem(+1,-1)*randint(1..100)}
\integer{bb=randitem(+1,-1)*randint(1..100)}

\text{nff=somme}
\text{prob=MF afin de s'approprier son fonctionnement.}
\text{enonce=PPP de calculer la somme de deux nombres. IFI "\nff" avec deux arguments \(a\) et \(b\).}

 
\integer{alea=randint(1..2)}
\text{operation=difference,produit}
\text{ope=-,*}
\text{opee=-,\times}

\integer{xO=\aa \ope[\alea] \bb}

\text{inst=print(\operation[\alea](2,5))}

\text{question=MLFI "\nff" ayant pour paramètre
 les valeurs de \(a\) et \(b\) en une fonction intitulée "\operation[\alea]".
 Cette fonction "\operation[\alea]" doit effectuer l'opération suivante : \(a \opee[\alea] b\).}

\text{code=
def \nff(a,b):
  return a+b
\#Test#
print(\nff(2,5))
}

\text{post='@@@@'+'\eva1'+'=\operation[\alea](\aa,\bb)'}
\text{rtest=[\eva1,[\xO]]}
