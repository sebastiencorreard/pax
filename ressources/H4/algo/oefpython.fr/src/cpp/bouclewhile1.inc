\title{Boucle while n°1}

\integer{minfalse=0}
\integer{t=randint(10..20)}
\real{cm=1+\t/100}
\real{rep=floor(ln(2)/ln(\cm))+1}
\real{rep2=floor(ln(2)/ln(\cm))}
\real{rep3=\cm^(floor(ln(2)/ln(\cm))+1)}
\text{explain0=asis(Qu'affiche le programme suivant écrit en langage Python ?)}
\text{explain=asis(
n=1
while \cm**n<2:
  n = n+1
print(n))}
\text{reppp_list= wims(values \cm^x for x = 1 to \rep)}
\text{list_i= wims(values x for x = 1 to \rep)}
\text{entete1=\(n\)}
\text{entete2=condition \(\cm^n \)}
\integer{max_list=\rep}
\matrix{datatrue=asis(\rep
Le plus petit entier \(n) tel que \(\cm^{n} \ge 2 \)
 )}
\matrix{datafalse=asis(Rien car il ne s'arrête pas
\rep2
\rep3
Tous les entiers tels que \(\cm^n<2 \)
Le plus grand entier \(n) tel que \(\cm^{n} \ge 2 \)
)}
\text{feedback_generalpre=En langage naturel le programme est :}
\text{feedback_program=
\(n\) prend la valeur 1
Tant que \(\cm^{n}<2 \) faire :
  \(n\) prend la valeur \(n+1\)
Fin du tant que
Afficher la valeur de \(n\)
}
\text{feedback_generalpost=Le programme affiche donc \rep.}
