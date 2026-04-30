\title{MF qui compare deux nombres}
\integer{aa=randitem(+1,-1)*randint(1..100)}
\integer{bb=randitem(+1,-1)*randint(101..200)}

\integer{alea=randint(1..2)}
\text{pg=petite,grande}
\text{ppg=grande,petite}
\text{ab=a,b}
\text{ba=b,a}

\text{prob=Comparaison de deux nombres.}
\text{enonce=PPP de déterminer la plus \pg[\alea] valeur
 entre deux nombres. IFI "comparaison" avec deux arguments
 \(a\) et \(b\).}

\text{nff=comparaison} 
 
\text{inst=print(\nff(5,8))}

\if{\alea==1}{\integer{xO=(\aa-\bb>0)?\aa:\bb}}
\if{\alea==2}{\integer{xO=(\aa-\bb>0)?\bb:\aa}}

\text{question=MLFI "\nff" ayant pour paramètres
 les valeurs de  \(a\) et \(b\) en une fonction "\nff"
 qui renvoie la plus \ppg[\alea] valeur.}

\text{code=
def \nff(a,b):
  if (a>b):
    return \ba[\alea]
  else:
    return \ab[\alea]
\#Test#
\inst
}

\text{post='@@@@'+'\eva1'+'=\nff(\aa,\bb)'}
\text{rtest=[\eva1,[\xO]]}
