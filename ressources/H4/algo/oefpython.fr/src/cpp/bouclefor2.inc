\title{Boucle for n°2}

\integer{minfalse=0}
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{c=randint(1..9)}
\integer{n=randint(20..30)}
\integer{p=\n+1}
\real{rep=\a*\n^2+\b*\n+\c}
\real{rep1=\a*\p^2+\b*\p+\c}

\text{explain0=On considère la fonction définie pour tout réel \(x)
 par \(f(x)=\a x^2+\b x+\c\).<br />
Déterminer la dernière valeur affichée par le programme suivant :}
\text{explain=asis(for i in range(1,\p):
  print(\a*i**2 + \b*i + \c))
}
\text{list_id= wims(makelist x for x = 1 to 5)}
\text{list_if= wims(makelist x for x = \p-5 to \p)}
\text{list_i=\list_id,...,\list_if}
\text{repp_list= wims(values \a*x*x+\b*x+\c for x = 1 to \n)}
\text{reppp_list=\repp_list[1..5],...,\repp_list[-5..-1]}
\text{entete1=\(i\)}
\text{entete2=print \(i\)}
\integer{max_list=11}
\matrix{datatrue=
 \( f( \n) \)
\rep
L'image de \n par \(f)
}

\matrix{datafalse=
\n
\p
\rep1
 \( f( \p) \)
L'image de \p par \(f)
}
\text{feedback_generalpre=asis(range(1,\p) désigne l'ensemble des entiers de 1 à \n.
En langage naturel le programme est :)}
<br />
\text{feedback_program=Pour \(i\) allant de 1 à \n faire :
  Afficher la valeur de \(\a*i**2+\b*i+\c)
Fin du pour
}
\text{feedback_generalpost=
La dernière valeur affichée est donc  \( f( \n) \)=\(\rep)}
