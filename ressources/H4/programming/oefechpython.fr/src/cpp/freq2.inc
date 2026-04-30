\text{prob=Étude d'une pièce de monnaie}

\text{enonce2=<br>On décale le nuage de points en ajoutant une valeur constante
 correspondant à la probabilité théorique.}

\integer{ntt=randint(20..50)}

\text{code=\code
pt=??
nt=??
\#initialisation des listes\#
y_list = []
y_list_pt=[]
\#################
for i in range(nt):
  issue=\ppp()
  issue_pt=issue+pt
  y_list.append(issue)
  y_list_pt.append(issue_pt)
\#Affichage des 5 premiers termes des listes#
print(y_list[\:5])
print(y_list_pt[\:5])}

\text{jsss3_1=y_liste_pt=Sk.ffi.remapToJs(Sk.globals["y_list_pt"]);}
\text{jsss3_2=for(var jj = 0; jj < ylen; jj=jj+1) {
brd.create('point', [jj,y_liste_pt[jj]],{Color:'blue'});}
brd.create('line',[[0,0.5],[1,0.5]],{Color:'black'});
brd.create('line',[[0,.5+ptt],[1,0.5+ptt]],{Color:'blue'});}

\text{embb=reply2,[python,[\code]];[idtest2,theme=\theme canvas init \instruction_code,Jouer le code !]}
\text{variable=[nt,\ntt],[pt,0.5]}

\integer{ep=randint(0..1)}
\text{ecol1=(\ep=1)?bleus:noirs}
\text{ecol2=(\ep=0)?bleus:noirs}
\real{en1=(\ep=1)?0.5:0}
\real{en2=(\ep=1)?1.5:1}
\real{en3=(\ep=0)?0.5:0}
\real{en4=(\ep=0)?1.5:1}
