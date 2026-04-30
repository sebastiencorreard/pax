\title{Boucle for n°1}

\integer{n=randint(20..50)}
\integer{p=\n+1}
\integer{prem=pari(isprime(\n))}

\text{explain0=asis(Que dire du programme suivant écrit en langage Python ?)}
\text{explain=for i in range(1,\p) :
  if \n % i == 0 :
    print(i)
}
\text{list_id= wims(makelist x for x = 1 to 5)}
\text{list_if= wims(makelist x for x = \p-5 to \p)}
\text{list_i=\list_id,...,\list_if}
\text{rep_list=pari(for (i = 1, \n,if(\n % i == 0, print(i),print("/")));)}
\text{repp_list=wims(words2items \rep_list)}
\text{reppp_list=\repp_list[1..5],...,\repp_list[-5..-1]}
\text{entete1=\(i\)}
\text{entete2=print \(i\)}
\integer{max_list=11}

\matrix{datatrue=asis(Il affiche tous les diviseurs positifs de \n)}

\matrix{datafalse=asis(Il affiche tous les diviseurs positifs de \p
Il affiche tous les entiers inférieurs ou égaux à \n
Il affiche tous les entiers inférieurs ou égaux à \p
Il peut servir à tester si \p est un nombre premier
)}

\text{feedback_generalpre=En langage naturel le programme est :}

\text{feedback_program=
Pour \(i\) allant de 1 à \n faire :
  Si le reste de la division euclidienne de  \n par \(i\) est nul alors :
    afficher la valeur de \(i\)
  Fin du si
Fin du pour
}
\text{feedback_generalpost=(\prem=1)? 
Le programme affiche donc les diviseurs positifs de \n.
Seuls 1 et \n sont affichés, cela signifie donc que \n est un nombre premier.:Le programme affiche donc les diviseurs positifs de \n.
\n admet plus de deux diviseurs positifs, \n n'est donc pas un nombre premier.
}
