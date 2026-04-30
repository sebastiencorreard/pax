type=question first
textarea="instruction datatrue datafalse explain"
asis="datatrue datafalse explain"
:\title{Boucle while  n°3}
:\author{David Rousseau}
:\email{david.rousseau@ac-amiens.fr}

\integer{minfalse=0}
\integer{a=randint(1..9)}
\integer{b=randint(1..9)}
\integer{c=randint(1..9)}
\integer{min=randint(-5..-1)}
\integer{decal=randint(10..20)}
\integer{max=\min+\decal}
\integer{nb=randint(3..7)}
\integer{xsol=\min+\nb -1}
\integer{xsol3=\xsol+1}
\real{rep1=\a*(\xsol)^2+\b*(\xsol)+\c}
\real{rep2=\xsol}
\real{rep3=\a*(\xsol+1)^2+\b*(\xsol+1)+\c}
\text{explain0=asis(On considère la fonction définie sur \(\ \RR\) par \(f(x)=\a x^2+\b x+\c\).
<br />Quel sera le \nb ème nombre affiché par le programme suivant écrit en langage Python ?)}
\text{explain=
x = \min
while x<=\max:
  print(\a*x**2+\b*x+\c)
  x = x+1
}
\text{repp_list= wims(values \a*x*x+\b*x+\c for x = \min to \max)}
\text{max_list=\decal}
\if{\decal<=10}{\text{list_i= wims(values x for x = \min to \max)}
\text{reppp_list=\repp_list}}
{\text{list_id= wims(makelist x for x = \min to \min+4)}
\text{list_if= wims(makelist x for x = \max-4 to \max+1)}
\text{list_i=\list_id,...,\list_if}
\text{reppp_list=\repp_list[1..5],...,\repp_list[-5..-1]}
\text{max_list=11}}
\text{entete1=\(x\)}
\text{entete2=print \(\a*x**2+\b*x+\c \)}
\matrix{datatrue=asis(\rep1
L'image de \xsol par \(f)
\(f(\xsol))
)}
\matrix{datafalse=asis(\rep2
\rep3
L'image de \nb par \(f)
L'image de \xsol3 par \(f)
Aucune de ces réponses
)}
\text{feedback_generalpre=En langage naturel le programme est :}

\text{feedback_program=
\(x\) prend la valeur \min
Tant que \(x \le \max \) faire :
  Afficher la valeur de \(\a*x**2+\b*x+\c \)
  \(x\) prend la valeur de \(x+1)
Fin du tant que
}
\text{feedback_generalpost=Le programme affiche donc \rep1, image de \xsol par \(f)}
