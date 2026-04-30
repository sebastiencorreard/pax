\title{E Compte à rebours}
\integer{nn=randint(20..30)}

\text{nff=compte}
\text{dnff=decompte}

\text{prob=E qui effectue un compte à rebours.}
\text{enonce=PPP d'afficher une liste des nombres de 0 à \(N-1\).
 IFI "\nff" avec un argument \(N\).}

\text{inst1=print(\nff(5))}
\text{inst=print(\dnff(5))}
 
\text{xO=}
\for{az=0 to \nn-1}{\integer{nna=\nn-\az-1}
\text{xO=wims(append item \nna to \xO)}
}

\text{question=MLFI "\nff" ayant pour paramètre
 la valeur de \(N\) en une fonction "decompte" afin qu'elle réalise une liste des nombres de \(N-1\) à 0.
  <br>
 <strong> Exemple :</strong> &emsp;<code>\inst</code> renvoie la liste : [4,3,2,1,0]}

\text{code=
def \nff(N):
  L=[]
  for i in range(N):
    L.append(i)
  return L
\#Test#
\inst1
}

\text{post='@@@@'+'\eva1'+'=\dnff(\nn)'}
\text{rtest=[\eva1,[\xO]]}
