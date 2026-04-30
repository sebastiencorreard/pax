\title{MF qui calcule des images}
\integer{aa=randitem(+1,-1)*randint(1..100)}
\integer{bb=randitem(+1,-1)*randint(1..100)}
\integer{xx=randitem(+1,-1)*randint(1..100)}
\text{fct=pari(\aa *x + \bb)}


\text{prob=MF afin de s'approprier son fonctionnement.}
\text{enonce=Soit une fonction affine de la forme \(f(x)=a x + b\). PPP
 de calculer l'image de \(x\) par la fonction \(f\). Il utilise une fonction intitulée "f" 
 possédant un argument \(x\).}
\text{inst=print(f(5))}
 
\integer{xO=\aa * \xx + \bb}

\text{question=MLFI "f" ayant pour paramètre
 la valeur de \(x\) en une fonction "f" associée à la fonction affine suivante : \(f(x)= \fct \).}

\text{code=
def f(x):
  return 3*x-2
\#Test#
\inst
}

\text{post='@@@@'+'\eva1'+'=f(\xx)'}
\text{rtest=[\eva1,[\xO]]}
