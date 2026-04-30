\title{Méthode par balayage avec une fonction 1}
\integer{etp=\nn+1}

\text{code=
\#Initialisation des listes#
x_list=[]
y_list=[]


\#Définition d'une fonction#
def f(x):
  return \fpyth


\#Initialisation des listes#
def balayage(f,k,a,b,n):
  fa,fb=f(a),f(b)
  for i in range(1,n+1):
    h=10**(-i)
    x=a
    \# Cas où f est strictement croissante sur l'intervalle.
    if fa<fb:
      while f(x)<k:
        x_list.append(x)
        y_list.append(f(x))
        x=x+h
    else:
      \# Cas où f est strictement décroissante sur l'intervalle.
      while f(x)>k:
        x_list.append(x)
        y_list.append(f(x))
        x=x+h
    a=x-h
  return (print(round(x-h,n),round(x,n),f(round(x,n))))

\#Appel de la fonction balayage où les valeurs k, a, b et n sont à indiquer.
balayage(f,\versionk,??,??,??)
\#Affichage des listes#
print(x_list)
print(y_list)
}
