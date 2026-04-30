\title{Méthode par dichotomie}

\text{prob=Méthode par dichotomie pour résoudre une équation de la forme \(f(x)=\k\)}

\text{DD=pari(default(format, "f.8");
vd=\xmin;
vf=\xmax;
p=\nn;
while((vf-vd)>10^(-p-1),
m=(vf+vd)/2.0;
if (f(m) \ineq \k,vd=m,vf=m);
);
vv=m;
)}
\#debug
while (b-a)>10**(-\nn):
    m=(a+b)/2
    if f(m) \ineq \k:
        a=m
        x_list.append(a)
        y_list.append(f(a))
    else:
        b=m
        x_list.append(b)
        y_list.append(f(b))

\text{code=\#Initialisation des variables\#
a=??
b=??
\#Définition d'une fonction\#
def f(x):
  return \fpyth
\#Initialisation des listes\#
x_list=[a]
y_list=[f(a)]
\#Coeur du programme\#
while ?? :
    m=??
    if f(m) ?? \k:
        a=m
        x_list.append(a)
        y_list.append(f(a))
    else:
        b=m
        x_list.append(b)
        y_list.append(f(b))

\#Affichage des listes\#
print(x_list)
print(y_list)
}
