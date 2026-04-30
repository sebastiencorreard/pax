\title{Équation cartésienne d'une droite }

\text{prob=Déterminer une équation cartésienne parmi tant d'autres d'une droite \((d )\) passant par 2 points}

\integer{x_A=randint(-5..5)}
\integer{y_A=randint(-5..5)}
\integer{x_B=randint(-5..5)}
\integer{y_B=randint(-5..5)}
\while{(\x_A==\x_B) and (\y_A==\y_B)}{\integer{x_B=randint(-5..5)}
\integer{y_B=randint(-5..5)}}

\integer{xming=-6}
\integer{xmaxg=6}
\integer{yming=-6}
\integer{ymaxg=6}

\matrix{zzzz=}
\integer{eqa=}
\integer{eqb=}
\integer{eqc=}

\text{enonce=<p>Soit une droite \((d)\) passant par les points \(A(\x_A;\y_A)\)
 et \(B(\x_B;\y_B)\). On recherche une équation cartésienne de cette droite de la forme :
 \(a x+by+c=0 \).</p>}

\text{titregraph=Représentation graphique des points \(A\), \(B\) en rouge et de la
 droite créée en vert}

\text{DD=pari(default(format, "f.8");
xa=\x_A;
ya=\y_A;
xb=\x_B;
yb=\y_B;
mmli=[];
xxli=[xa*1.0,xb*1.0];
yyli=[ya*1.0,yb*1.0];
if(xa==xb && ya==yb,,mmli=[ya-yb,xb-xa,xa*(yb-ya)+ya*(xa-xb)];);
)}
\#debug
  a=y_A-y_B
  b=x_B-x_A
  c=x_A*(y_B-y_A)+y_A*(x_A-x_B)
\text{code=\#Initialisation des variables\#
x_A=\x_A
y_A=\y_A
x_B=\x_B
y_B=\y_B
\#Initialisation des listes\#
x_list=[x_A,x_B]
y_list=[y_A,y_B]
\#Coeur du programme\#
if (x_A==x_B) & (y_A==y_B):
  print('Les 2 points sont confondus donc il existe une infinité de droite')
else:
  a=??
  b=??
  c=??
  print('La droite (d) a pour équation cartésienne de droite : '+str(a)+'x+'+str(b)+'y+'+str(c)+'=0.')
}

\text{coefi=a=Sk.ffi.remapToJs(Sk.globals["a"]);
b=Sk.ffi.remapToJs(Sk.globals["b"]);
c=Sk.ffi.remapToJs(Sk.globals["c"]);}

\text{coefr=for(var jj = 0; jj < xlen; jj=jj+1) {
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});}
brd.create('line', [c, a, b], {strokeWidth: 2,Color: "green"});}
\text{instruction_code=instruction=[print(f(??))]}
