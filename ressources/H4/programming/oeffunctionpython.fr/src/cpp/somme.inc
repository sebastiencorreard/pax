\text{nff=somme}
\text{prob=Modifier la fonction afin qu'elle calcule la somme \des}
\text{enonce=PPP d'afficher une liste contenant les nombres de 0 à \(N\).
 IFI "somme" avec un argument \(N\).}
\text{inst=print(\nff(4))}
 
\text{question=MLFI "\nff" de paramètre \(N\) afin
 qu'elle réalise la somme \des.
 <br>
 <strong> Exemples :</strong> &emsp; \(\exx\)
}

\text{code=
def \nff(N):
  S=[]
  for i in range(N+1):
    S.append(i)
  return S
\#Test#
\inst
}

\text{post='@@@@'+'\eva1'+'=\nff(\NN)'}
\text{rtest=[\eva1,[\xO]]}
