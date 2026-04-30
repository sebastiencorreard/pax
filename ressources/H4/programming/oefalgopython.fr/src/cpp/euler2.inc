\title{Construction de la courbe par la méthode d'Euler 2}

\text{prob=Construction de la courbe exponentielle par la méthode d'Euler}

\text{enonce=<p>On appelle la fonction exponentielle l'unique fonction dérivable sur
 \(\mathbb{R}\) définie telle que \( \left \lbrace \begin{array}{lcl}
f'(x)&=&f(x)& \\ \hline
f(0)&=&1&
\end{array}
\right.\)}

\integer{xmin=-6}
\integer{xmax=6}

\integer{xming=-6}
\integer{xmaxg=6}
\integer{yming=-1}
\integer{ymaxg=6}
\matrix{repere=\xming,\ymaxg,\xmaxg,\yming}

\integer{aalea=randint(-4..-1)}
\integer{balea=randint(1..4)}

\text{DD=pari(default(format, "f.8");
vd=\aalea;
va=\balea;
pn=\nn;
ph=(va-vd)/pn;
yy=(1+ph)^(vd/ph)*1.0;
xxli=[\aalea];
yyli=[yy];
forstep(x=vd+ph,va,ph,xxli=concat(xxli,x*1.00);
yy=(1+ph)^(x/ph)*1.0;
yyli=concat(yyli,yy);
);
)}
\#debug
a=\aalea
b=\balea
n=\nn
h=(b-a)/n
x=a
y=(1+h)**(x/h)
for i in range(n+1):
  x_list.append(x)
  y_list.append(y)
  x=x+h
  y=(1+h)**(x/h)
\text{code=\#Initialisation des variables\#
a=??
b=??
n=??
h=??
x=??
y=??

\#Initialisation des listes\#
x_list=[]
y_list=[]
\#Coeur du programme\#
for i in range(n+1):
  x_list.append(x)
  y_list.append(y)
  x=??
  y=??
\#Affichage des listes\#
print(x_list)
print(y_list)}

\text{coefi=}

\text{coefr=var c1=brd.create('functiongraph', [function(x){ return Math.exp(x);}, \xmin, \xmax], {strokeWidth: 2});
for(var jj = 0; jj < xlen; jj=jj+1) {
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});
if(jj!=xlen-1){brd.create('line',[[x_liste[jj],y_liste[jj]],[x_liste[jj+1],y_liste[jj+1]]],{straightFirst:false, straightLast:false,Color:'green',fixed:true});}
}}
\text{instruction_code=instruction=[print(f(??))]}
