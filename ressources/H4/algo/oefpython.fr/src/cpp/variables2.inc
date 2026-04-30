\title{Variables n°2}

\integer{a=randint(3..9)}
\integer{a2=\a+\a}
\integer{ac=\a*\a}
\integer{x=randint(2..9)}
\real{rep=(\x+\a)^2}
\real{rep2=\a^2}
\real{rep3=\x^2+\a^2}
\real{rep4=\x+\a^2}
\matrix{datatrue=asis(
 \rep
 )}
\matrix{datafalse=asis(
\rep2
\rep3
\rep4
)}

\text{explain=asis(
x=\x
y=x+\a2
y=y*x
y=y+\ac
print(y)
)}
\text{feedback_generalpre=En langage naturel le programme est :}
\text{feedback_program=
\(x) prend la valeur \x
\(y) prend la valeur \(x)+\a2
\(y) prend la valeur \(y \times x)
\(y) prend la valeur \(y+\ac)
Afficher la valeur de \(y)
}
\text{feedback_generalpost=Le programme affiche donc \rep.}
