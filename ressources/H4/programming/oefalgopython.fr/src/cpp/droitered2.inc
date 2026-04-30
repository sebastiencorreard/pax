\title{Équation réduite d'une droite 2}

\text{prob=Déterminer l'équation réduite d'une droite \((d )\) passant par 2 points}

\integer{nch=randint(1..3)}

\if{\nch==1}{\integer{x_A=randint(-5..5)}
\integer{y_A=randint(-5..5)}
\integer{x_B=\x_A}
\integer{y_B=randint(-5..5)}
\while{\y_A==\y_B}{\integer{y_A=randint(-5..5)}}
\text{rep1=\x_A}
\text{rep2=Vide}
\matrix{nstep=r1,r2,r3}
}
\if{\nch==2}{\integer{x_A=randint(-5..5)}
\integer{y_A=randint(-5..5)}
\integer{x_B=randint(-5..5)}
\integer{y_B=\y_A}
\while{\x_A==\x_B}{\integer{x_A=randint(-5..5)}}
\text{rep1=Vide}
\text{rep2=\y_A}
\matrix{nstep=r1,r2,r4}
}
\if{\nch==3}{\integer{x_A=randint(-5..5)}
\integer{y_A=randint(-5..5)}
\integer{x_B=randint(-5..5)}
\integer{y_B=randint(-5..5)}
\while{\x_A==\x_B}{\integer{x_A=randint(-5..5)}}
\while{\y_A==\y_B}{\integer{y_A=randint(-5..5)}}
\rational{am=(\y_B-\y_A)/(\x_B-\x_A)}
\rational{dm=\y_A-(\y_B-\y_A)/(\x_B-\x_A)*\x_A}
\text{rep1=Vide}
\text{rep2=\am*x+\dm}
\matrix{nstep=r1,r2,r5}
}

\nextstep{\nstep}

\integer{xming=-6}
\integer{xmaxg=6}
\integer{yming=-6}
\integer{ymaxg=6}

\text{enonce=<p>Soit une droite \((d)\) passant par les points \(A(\x_A;\y_A)\)
 et \(B(\x_B;\y_B)\). On recherche l'équation réduite de cette droite de la forme :
 \(y=m x+p \) ou \(y=b \) ou \(x=c \).</p>}

\text{titregraph=Représentation graphique des points \(A\), \(B\) en rouge et de la
 droite créée en vert}

\text{DD=pari(default(format, "f.8");
xa=\x_A;
ya=\y_A;
xb=\x_B;
yb=\y_B;
pn=\nn;
xxli=[xa*1.0,xb*1.0];
yyli=[ya*1.0,yb*1.0];
if(xa!=xb,mmli=(yb-ya)/(xb-xa)*1.0;
ppli=ya-mmli*xa;);
)}
\#debug

\text{code=\#Initialisation des variables\#
x_A=??
y_A=??
x_B=??
y_B=??
\#Initialisation des listes\#
x_list=[x_A,x_B]
y_list=[y_A,y_B]
\#Coeur du programme\#
if x_A==x_B:
  if y_A==y_B:
    print('Les 2 points sont confondus donc il existe une infinité de droites')
  else:
    xv=??
    print('La droite (d) est verticale d équation : x='+str(xv)+'.')
elif y_A==y_B:
  yh=??
  print('La droite (d) est horizontale d équation : y='+str(yh)+'.')
else:
  m=??
  p=??
  print('La droite (d) est oblique d équation : y ='+str(m)+'x +'+str(p)+'.')
}

\text{coefi=xv=Sk.ffi.remapToJs(Sk.globals["xv"]);
yh=Sk.ffi.remapToJs(Sk.globals["yh"]);
m=Sk.ffi.remapToJs(Sk.globals["m"]);
p=Sk.ffi.remapToJs(Sk.globals["p"]);}

\text{coefr=for(var jj = 0; jj < xlen; jj=jj+1) {
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});}
if(x_liste[0]==x_liste[1]){brd.create('line', [-xv, 1, 0], {strokeWidth: 2,Color: "green"});}
if(y_liste[0]==y_liste[1]){brd.create('line', [-yh, 0, 1], {strokeWidth: 2,Color: "green"});}
if((x_liste[0]!=x_liste[1])&(y_liste[0]!=y_liste[1])){brd.create('functiongraph', [function(x){ return m*x+p;}, \xming, \xmaxg], {strokeWidth: 2,Color: "green"});}
}
