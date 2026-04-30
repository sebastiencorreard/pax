\title{Méthode par balayage avec seuil (guidée)}

\text{prob=Méthode de balayage avec seuil pour résoudre une équation de la forme \(f(x)=\k\)}

\text{DD=pari(default(format, "f.8");
vd=\xmin;
xxli=[];
yyli=[];
vfilp=[];
vfalp=[];
vdd=[];
vff=[];
x=vd;
for(p=1,4,
xli=[];
yli=[];
while(f(x) \ineq \k ,
xli=concat(xli,x*1.00);
yli=concat(yli,f(x)*1.0);
x=x+10^(-p););
xxli=concat(xxli,[xli]);
yyli=concat(yyli,[yli]);
vfilp=concat(vfilp,f(x-10^(-p))*1.0);
vfalp=concat(vfalp,f(x)*1.0);
vdd=concat(vdd,(x-10^(-p))*1.0);
vff=concat(vff,x*1.0);
x=x-10^(-p););
)}

\text{code=\#Initialisation des variables\#
xmin=??
x=xmin
pas=??
\#Initialisation des listes#
x_list=[]
y_list=[]
\#Définition d'une fonction#
def f(x):
  return \fpyth
\#Coeur du programme\#
while f(x) ?? \k :
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  x=x+pas
\#Affichage des listes#
print(x_list)
print(y_list)
print('f(',x,')=',f(x))
}