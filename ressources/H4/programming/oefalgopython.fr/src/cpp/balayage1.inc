\title{Méthode par balayage classique (guidée)}

\text{prob=Méthode de balayage classique pour résoudre une équation de la forme \(f(x)=\k\)}

Le if p==1 est vraiment pouri
\text{DD=pari(default(format, "f.8");
vd=\xmin;
xxli=[];
yyli=[];
mli=[];
vfilp=[];
vfalp=[];
vdd=[];
vff=[];
for(p=1,4,
xli=[];
yli=[];
if(p==1,vf=vd+1.0*10^(-p+1);,vf=vd+1.0*10^(-p+1)-10^(-p););
forstep(x=vd,vf,1.0*10^(-p),xli=concat(xli,x*1.00);
yli=concat(yli,f(x)*1.0);
if(f(x) \ineq \k,vd=x;);
);
xxli=concat(xxli,[xli]);
yyli=concat(yyli,[yli]);
vfilp=concat(vfilp,f(vd));
vfalp=concat(vfalp,f(vd+10^(-p)));
vdd=concat(vdd,vd);
vff=concat(vff,vd+10^(-p));
);
)}

\text{code=\#Initialisation des variables\#
xmin=??
x=xmin
xmax=??
pas=??
\#Initialisation des listes\#
x_list=[]
y_list=[]
\#Définition d'une fonction\#
def f(x):
  return \fpyth
\#Coeur du programme\#
while x < xmax:
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  x=x+pas
\#Corrige le problème de mantisse\#
x_list=x_list[:10]
y_list=y_list[:10]
\#Affichage des listes et de l'image de l'abscisse maximale\#
print(x_list)
print(y_list)
print('f(',xmax,')=',f(xmax))
}
