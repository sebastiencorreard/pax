\text{prob=Étude d'une pièce de monnaie}

\text{enonce2=<br>On associe les événements suivants :
<ul><li>P : la face visible de la pièce est sur pile. La valeur associée est 0.</li>
<li>F : la face visible de la pièce est sur face. La valeur associée est 1.</li>
</ul>
La méthode <code>\pp()</code> arrondit un nombre décimal à l'entier en coupant la partie
décimale donc en couplant ces deux méthodes, on simule l'expérience aléatoire
 de la pièce de monnaie.}

\text{rkh=nombre de points}
\text{rkh1=noirs dont l'ordonnée est supérieure ou égale à 1}
\text{rkh2=noirs dont l'ordonnée est strictement inférieure à 1}
\text{rkh3=bleus dont l'ordonnée est égale à 1}
\text{rkh4=bleus dont l'ordonnée est égale à 0}

\integer{ntt=randint(20..50)}

\text{code=\code
nt=??
pt=??
NPN_ysup1=NPN_yinf1=NPB_y1=NPB_y0=0
\#initialisation des listes\#
y_list=[]
y_list_arrondi=[]
\#################
for i in range(nt):
  issue=\ppp()+pt
  issue_arrondi=\pp(issue)
  y_list.append(issue)
  y_list_arrondi.append(issue_arrondi)
  if issue >=1 :
    NPN_ysup1=NPN_ysup1+1
  else :
    NPN_yinf1=NPN_yinf1+1
  if issue_arrondi==1 :
    NPB_y1=NPB_y1+1
  else :
    NPB_y0=NPB_y0+1
\#Affichage des 5 premiers termes des listes#
print(y_list[\:5])
print(y_list_arrondi[\:5])
print(NPN_ysup1,NPN_yinf1,NPB_y1,NPB_y0)}

\text{jsss3_1=y_liste_arrondi=Sk.ffi.remapToJs(Sk.globals["y_list_arrondi"]);
NPN_ysup1=Sk.ffi.remapToJs(Sk.globals["NPN_ysup1"]);
NPN_yinf1=Sk.ffi.remapToJs(Sk.globals["NPN_yinf1"]);
NPB_y1=Sk.ffi.remapToJs(Sk.globals["NPB_y1"]);
NPB_y0=Sk.ffi.remapToJs(Sk.globals["NPB_y0"]);}
\text{jsss3_2=for(var jj = 0; jj < ylen; jj=jj+1) {brd.create('point', [jj,y_liste_arrondi[jj]],{Color:'blue'});}
brd.create('line',[[0,0.5+ptt],[1,0.5+ptt]],{Color:'black'});}

\text{embb=reply2,[python,[\code]];[idtest2,theme=\theme canvas init \instruction_code,Jouer le code !]}
\text{variable=[nt,\ntt],[pt,0.5]}


\text{rep1=}
\text{rep2=}
\text{rep3=}
\text{rep4=}

\text{dq=}
\text{dq1=}
\text{dq2=}
\text{dq3=}
\text{dq4=}
