\title{Variables n°1}
\integer{x=randint(1..8)}
\integer{y=randint(9..15)}
\text{rep=\(\y,\x\)}
\text{rep2=\(\x,\y\)}
\text{rep3=\(\x,\x\)}
\text{rep4=\(\y,\y\)}
\matrix{datatrue=asis(
 \rep
 )}
\matrix{datafalse=asis(
\rep2
\rep3
\rep4
)}
\text{explain=asis(
x,y=\x,\y
c=y
y=x
x=c
print(x,y)
)}
\text{feedback_generalpre=En langage naturel le programme est :}
\text{feedback_program=
\(x) prend la valeur \x
\(y) prend la valeur \y
\(c) prend la valeur \(y)
\(y) prend la valeur \(x)
\(x) prend la valeur \(c)
Afficher la valeur de \(x) , \(y)
}
\text{feedback_generalpost=
Le programme affiche donc \rep.
Plus généralement, il échange les valeurs des variables \(x) et \(y).
}
