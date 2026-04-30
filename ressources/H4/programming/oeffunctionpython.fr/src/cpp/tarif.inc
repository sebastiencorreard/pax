\title{Écrire une fonction pour déterminer le prix à payer}

\real{aa=randint(1..250)/1000}
\real{bb=randint(251..500)/1000}
\real{cc=randint(501..750)/1000}
\real{dd=randint(751..100000000)/1000}
\real{t1=4.95}
\real{t2=6.7}
\real{t3=7.6}
\text{t4=None}

\text{prob=Déterminer le prix à payer selon la masse du colis}
\text{enonce=On souhaite écrire une fonction Python qui détermine le prix à payer selon la
 masse du colis. Cette fonction a comme argument la variable \(m\) et renvoie le prix.}
\text{inst=print(tarif(0.1))}


\text{code=
def ...
...
...
\#Test#
\inst}

\text{question=E Python intitulée "tarif" ayant pour paramètre
 la valeur de la masse \(m\).
 Cette fonction "tarif" doit retourner un prix selon les valeurs de la masse:
 <ul><li>Si \(0 < m <= 0.25\) alors le prix est de 4.95 €</li>
<li>Si \(0.25 < m <= 0.5\) alors le prix est de 6.7 €</li>
<li>Si \(0.5 < m <= 0.75\) alors le prix est de 7.6 €</li>
<li>Si \(m > 0.75\) alors on sort de la zone tarifaire et la fonction doit retourner
 la valeur <code>"None"</code></li> 
</ul>}

\text{post='@@@@'+'\eva1'+'=tarif(\aa)'+'@@@@'+'\eva2'+'=tarif(\bb)'+'@@@@'+'\eva3'+'=tarif(\cc)'+'@@@@'+'\eva4'+'=tarif(\dd)'}
\text{rtest=[\eva1,[\t1]],[\eva2,[\t2]],[\eva3,[\t3]],[\eva4,[\t4]]}

def tarif(m):
  if 0< m and m<=0.25:
    T=4.95
  elif 0.25<m and m<=0.5:
    T=6.7
  elif 0.5 < m and m<= 0.75:
    T=7.6
  else :
    T="None"
  return T
