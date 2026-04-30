\text{exx=1 \times 2 \times 3 \times 4 \times 5=\displaystyle \prod_{i=1}^{n=5} i=120}
\integer{NN=randint(20..50)}
\text{xO=pari((\NN)!)}

\text{prob=Modifier la fonction afin qu'elle calcule le produit des nombres de 1 à \(N\).}
\text{enonce=PPP d'afficher la liste des nombres de 1 à \(N\).
 IFI "factorielle" avec un argument \(N\).}
 
\text{nff=factorielle}
\text{inst=print(\nff(5))}
 
\text{question=MLFI "\nff" de paramètre \(N\) afin
 qu'elle réalise le produit des \(\N\) premiers nombres entiers non nul.
 <br>
 <strong> Exemple :</strong> &emsp; \(\exx\)
}

\text{code=
def factorielle(N):
  P=[]
  for i in range(1,N+1):
    P.append(i)
  return P
\#Test#
\inst
}

\text{post='@@@@'+'\eva1'+'=\nff(\NN)'}
\text{rtest=[\eva1,[\xO]]}
