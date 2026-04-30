\text{prob=Méthode de Monte-Carlo : Calcul du nombre \(pi\)}

\rational{xmin=-1.5}
\rational{xmax=1.5}
\rational{ymin=-1.5}
\rational{ymax=1.5}

\text{ineqe1=\(-1<x<1\)}
\text{ineqe2=\(-1<y<1\)}

\text{tre1=à l'intérieur du disque}

\text{virg=,}

\text{graphique=<img src="\imagedir/montecarlo1.png" style="width:600px" alt="Monte-carlo">}

\integer{nll=randint(500..1000)}

\integer{jal=randint(1..2)}
\text{tjal1=(\jal==1)?npi=??:}
\text{tjal2=(\jal==1)?:npi=??}
\text{tvide=}

\text{code=\code
nt=?? \#Nombre de points
npi= 0 \#Nombre de points à l'intérieur du disque
\#initialisation des listes\#
x_list_b = []
y_list_b = []
x_list_r = []
y_list_r = []
\#################
for i in range(nt):
    x = uniform(??,??)
    y = uniform(??,??)
    if ?? :
        x_list_b.append(x)
        y_list_b.append(y)
        \tjal1      
    else:
        x_list_r.append(x)
        y_list_r.append(y)
        \tjal2
  
pi = ??
\tvide    
  
print('Le rapport des aires du disque et du carré est égal à environ ', npi/nt)
print('pi est égal à environ ', pi)
}
Pas de var ni de let car elle passe en global
\text{jsss3_1= x_liste_b=Sk.ffi.remapToJs(Sk.globals["x_list_b"]);
y_liste_b=Sk.ffi.remapToJs(Sk.globals["y_list_b"]);
x_liste_r=Sk.ffi.remapToJs(Sk.globals["x_list_r"]);
y_liste_r=Sk.ffi.remapToJs(Sk.globals["y_list_r"]);
l_liste_b=x_liste_b.length;
l_liste_r=x_liste_r.length;
rppi=Sk.ffi.remapToJs(Sk.globals["pi"]);
rnpi=Sk.ffi.remapToJs(Sk.globals["npi"]);
}
\text{donne=}


\text{embb=reply7,[python,[\code]];[idtest7,theme=\theme canvas init \instruction_code,Jouer le code !]}
\text{variable=[nt,\nll]}
