\title{Construction de la courbe par la méthode des tangentes}

\text{prob=Construction d'une courbe \(f\) en effectuant l'enveloppe des tangentes}

\text{enonce=<p>Soit \(f\) une fonction définie par \(f(x)=\ft\) et dérivable
 sur l'intervalle \(\lbracket\xmin;\xmax\rbracket\).</p>
<p>On souhaite construire la représentation graphique de la fonction \(f\).</p>}


\text{DD=pari(default(format, "f.8");
vd=\xmin;
va=\xmax;
pn=\nn;
ph=(va-vd)/pn;
xxli=[];
yyli=[];
mmli=[];
ppli=[];
forstep(x=vd,va,ph,xxli=concat(xxli,x*1.00);
yyli=concat(yyli,f(x)*1.0);
ctt=ffp(x)*1.0;
mmli=concat(mmli,ctt);
ppli=concat(ppli,f(x)*1.0-ctt*x);
);
)}
\#debug
a=\xmin
b=\xmax
n=\nn
h=(b-a)/n
x=a+h*i
m=fp(x)
p=f(x)-x*fp(x)
\text{code=\#Initialisation des variables\#
a=??
b=??
n=??
h=??
\#Initialisation des listes\#
x_list=[]
y_list=[]
m_list=[]
p_list=[]
\#Définition d'une fonction\#
def f(x):
  return \fpyth
\#Définition de la dérivée associé à la fonction\#
def fp(x):
  return ??
\#Coeur du programme\#
for i in range(n+1):
  x=??
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  m=??
  m_list.append(m)
  p=??
  p_list.append(p)
\#Affichage des listes\#
print(x_list)
print(y_list)
print(m_list)
print(p_list)}

\text{titregraph=Représentation graphique de \(C_f\) aves les points et les tangentes créées.}

\text{coefi=m_liste=Sk.ffi.remapToJs(Sk.globals["m_list"]);
p_liste=Sk.ffi.remapToJs(Sk.globals["p_list"]);}

\text{coefr=var c1=brd.create('functiongraph', [function(x){ return \fjs;}, \xmin, \xmax], {strokeWidth: 2});
for(var jj = 0; jj < xlen; jj=jj+1) {
let p=p_liste[jj];
let m=m_liste[jj];
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});
brd.create('functiongraph', [function(x){ return m*x+p;}, \xmin, \xmax], {strokeWidth: 2,Color: "green"});}}
\text{instruction_code=instruction=[print(f(??))]}
