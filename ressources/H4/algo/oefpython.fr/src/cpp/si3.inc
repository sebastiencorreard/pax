\title{Instruction si n°3}
:\author{Cyrille, Douriez}##d'après un exercice de David Rousseau##
:\email{david.rousseau@ac-amiens.fr}
:\credits{}
:Nombre de choix à présenter. Au plus 10.
Vous devez définir suffisamment de choix. Sinon l'exercice affichera seulement ce qui est disponible.
\integer{tot=5}
\integer{c1=randint(8..20)}##condition 1##
\integer{c2=randint(2..(\c1-3))}##condition 2##
\integer{ecart=\c1-\c2}
\integer{x=randint((\ecart+1)..(\ecart+15))}##valeur dans test 1##
\integer{cas=randint(1,1,2,2,3)}##1: deux tests vérifiés, 2: 1er vérifié, 3: 1er non vérifié##
                   
\matrix{donnee=randint(\c1..(\c2+\x)),randint((\c2+\x+1)..(\c2+\x+10)),randint(1..(\c1-1))}
\integer{y=randint(1..(\x-1))}
\integer{a=\donnee[\cas]}
\integer{s1=\a-\x+\y}
\integer{s2=\a-\x-\y}
\integer{s3=\a}
\integer{s4=\a+\x-\y}
\matrix{rep=\s1,\s2,\s3,\s4
\s2,\s1,\s3,\s4
\s3,\s2,\s1,\s4
}
\text{explain0=asis(Que vaut la valeur finale de a dans
  ce programme écrit en langage Python ?)}

\text{explain=
a=\a
if a>=\c1:
  a=a-\x
  if a<=\c2:
    a=a+\y
  else:
    a=a-\y
}

\matrix{datatrue=asis(
 \rep[\cas;1]
 )}
\matrix{datafalse=asis(
\rep[\cas;2]
\rep[\cas;3]
\rep[\cas;4]
)}

\text{feedback_generalpre=En langage naturel le programme est :}
\text{feedback_program=
\(a) prend la valeur \a
Si \(a \ge \c1) alors :
  \(a) prend la valeur \(a-\x)
  Si \(a \le \c2)
    Alors \(a) prend la valeur \(a+\y)
    Sinon \(a) prend la valeur \(a-\y)
  Fin du si
Fin du si
}
\text{feedback_generalpost=A la fin de l'exécution, \(a) vaut \rep[\cas;1].}
