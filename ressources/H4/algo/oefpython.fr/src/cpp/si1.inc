\title{Instruction si n°1}

\integer{c1=randint(5..9)}##valeur pour condition 1##
\integer{c2=randint(10..15)}##valeur pour condition 2##
\integer{x=randint(1..5)}##valeur dans test 1##
\integer{y=randint(6..10)}##valeur dans test 2## MB : pbm si x=y, donc changement de valeurs pour y
\integer{cas=randint(1..4)}##1: deux tests vérifiés, 2: 1er vérifié, 3: 2ème vérifié, 4: aucun vérifié##

\matrix{donnees=\c1+randint(1..5),\c2+\x+randint(1..5)
\c1+randint(1..5),\c2+\x-randint(1..5)
\c1-randint(1..5),\c2+randint(1..5)
\c1-randint(1..5),\c2-randint(1..5)}
\integer{a=\donnees[\cas;1]}
\integer{b=\donnees[\cas;2]}
\integer{s1=\b-\x+\y}
\integer{s2=\b-\x}
\integer{s3=\b+\y}
\matrix{rep=\s1,\s2,\s3,\b
\s2,\s1,\s3,\b
\s3,\s2,\s1,\b
\b,\s1,\s2,\s3}

\matrix{datatrue=asis(
 \rep[\cas;1]
 )}
\matrix{datafalse=asis(
\rep[\cas;2]
\rep[\cas;3]
\rep[\cas;4])
}

\text{explain0=Que vaut la valeur finale de b dans ce programme écrit en langage Python ?}
\text{explain=
a=\a
b=\b
if a>\c1:
   b=b-\x
if b>=\c2:
   b=b+\y
}

\text{feedback_generalpre=En langage naturel le programme est :}

\text{feedback_program=
\(a) prend la valeur \a
\(b) prend la valeur \b
Si \(a > \c1) alors
  \(b) prend la valeur \(b-\x)
Fin du si
Si \(b \ge \c2) alors
  \(b) prend la valeur \(b+\y)
Fin du si
}
\text{feedback_generalpost=À la fin de l'exécution, \(b) vaut \rep[\cas;1].}
