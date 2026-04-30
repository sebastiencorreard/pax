\text{prob=Modifier la fonction afin qu'elle calcule la liste des multiples positifs d'un entier
non nul compris entre de \(0\) et \(N\).}
\text{enonce=PPP d'afficher les nombres de 0 à \(N\).
 IFI "list_multiple" avec un argument \(N\).}
 
\text{nff=list_multiple}
\text{inst=print(\nff(30,1))}
 
\integer{NN=randint(100..200)}
\integer{dd=randitem(2,3,5,7,11,13,17,19)*1} 

\text{question=MLFI "\nff" de paramètre \(N\) en une
 fonction "\nff" avec les paramètres \(N\) et \(d\). Le but est de créer la liste des
 multiples de \(d\) compris entre \(0\) et \(N\).
 <br>
 <strong> Exemples :</strong>
<ul><li>liste des multiples de 7 entre 0 et 30 : \(\lbrack{ 0,7,14,21,28 }\rbrack\)</li>
<li>liste des multiples de 11 entre 0 et 33 :  \(\lbrack{ 0,11,22,33} \rbrack\)</li>
</ul>
}


\text{xO=}
\for{az=0 to \NN-1}{\real{test=\az % \dd}
\if{\test==0}{\text{xO=wims(append item \az to \xO)}}}

\text{code=
def list_multiple(N,d):
  LM=[]
  for i in range(N+1):
    LM.append(i)
  return LM
\#Test#
\inst
}

\text{post='@@@@'+'\eva1'+'=\nff(\NN,\dd)'}
\text{rtest=[\eva1,[\xO]]}
