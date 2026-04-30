\title{Construction de la courbe par la méthode de balayage en utilisant une boucle for}

\text{prob=Construction d'une courbe \(f\) par la méthode de balayage en utilisant une boucle for}

\text{enonce=<p>Soit \(f\) une fonction définie par \(f(x)=\ft\) sur l'intervalle \(\lbracket\xmin;\xmax\rbracket\).</p>
<p>On souhaite construire la représentation graphique de la fonction \(f\).</p>}

\text{DD=pari(default(format, "f.8");
vd=\xmin;
va=\xmax;
pn=\nn;
ph=(va-vd)/pn;
xxli=[];
yyli=[];
forstep(x=vd,va,ph,xxli=concat(xxli,x*1.00);
yyli=concat(yyli,f(x)*1.0););
)}

\#debug
a=\xmin
b=\xmax
n=\nn
h=(b-a)/n
x=a+h*i
\text{code=\#Initialisation des variables\#
a=??
b=??
n=??
h=??
\#Initialisation des listes\#
x_list=[]
y_list=[]
\#Définition d'une fonction\#
def f(x):
  return \fpyth
\#Coeur du programme\#
for i in range(n+1):
  x=??
  y=f(x)
  x_list.append(x)
  y_list.append(y)
\#Affichage des listes\#
print(x_list)
print(y_list)}

\text{titregraph=Représentation graphique de la courbe \(C_f\) avec les points créés}

\text{coefr=var c1=brd.create('functiongraph', [function(x){ return \fjs;}, \xmin, \xmax], {strokeWidth: 2});
for(var jj = 0; jj < xlen; jj=jj+1) {
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});}}
