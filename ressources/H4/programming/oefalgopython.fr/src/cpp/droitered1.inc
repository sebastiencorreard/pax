\title{Équation réduite d'une droite 1}

\text{prob=Déterminer l'équation réduite d'une droite \((d )\) passant par 2 points}

\integer{xA=randint(-5..5)}
\integer{yA=randint(-5..5)}
\integer{xB=randint(-5..5)}
\integer{yB=randint(-5..5)}
\while{\xA==\xB}{\integer{xA=randint(-5..5)}}
\integer{xming=-6}
\integer{xmaxg=6}
\integer{yming=-6}
\integer{ymaxg=6}

\rational{am=(\yB-\yA)/(\xB-\xA)}
\text{bm=\am*x+p}
\rational{dm=\yA-(\yB-\yA)/(\xB-\xA)*\xA}
\text{em=\am*x+\dm}


\text{enonce=<p>Soit une droite \((d)\) passant par les points \(A(\xA;\yA)\)
 et \(B(\xB;\yB)\). On recherche l'équation réduite de cette droite de la forme :
 \(y=m x+p \).</p>}

\text{titregraph=Représentation graphique des points \(A\), \(B\) en rouge et de la
 droite créée en vert}

\text{DD=pari(default(format, "f.8");
xa=\xA;
ya=\yA;
xb=\xB;
yb=\yB;
pn=\nn;
xxli=[xa*1.0,xb*1.0];
yyli=[ya*1.0,yb*1.0];
mmli=(yb-ya)/(xb-xa)*1.0;
ppli=ya-mmli*xa;
)}
\#debug
m=(y_B-y_A)/(x_B-x_A)
p=y_A-m*x_A
\text{code=\#Initialisation des variables\#
x_A=??
y_A=??
x_B=??
y_B=??
\#Initialisation des listes\#
x_list=[x_A,x_B]
y_list=[y_A,y_B]
\#Coeur du programme\#
m=??
p=??
\#Affichage des listes\#
print(x_list)
print(y_list)
print('m=',m)
print('p=',p)}

\text{coefi=m=Sk.ffi.remapToJs(Sk.globals["m"]);
p=Sk.ffi.remapToJs(Sk.globals["p"]);}

\text{coefr=for(var jj = 0; jj < xlen; jj=jj+1) {
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});}
brd.create('functiongraph', [function(x){ return m*x+p;}, \xming, \xmaxg], {strokeWidth: 2,Color: "green"});
}
