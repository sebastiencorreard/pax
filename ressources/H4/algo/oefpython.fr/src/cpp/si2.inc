\title{Instruction si n°2}

\integer{tot=5}
\integer{x=randint(1..4)}##valeur dans test 1##
\integer{y=randint(1..4)}##valeur dans test 2##
\integer{cas=randint(1..4)}##1: deux tests vérifiés, 2: 1er vérifié, 3: 2ème vérifié, 4: aucun vérifié##


\matrix{donnees=randint(0..5),randint((10+\x)..17)
randint(10..15),randint(-15..-10)
randint(-10..-1),randint(10..15)
randint(-5..-1),randint(-17..(\x-10))}
\integer{a=\donnees[\cas;1]}
\integer{b=\donnees[\cas;2]}
\integer{s1=\a+\y}
\integer{s2=\a-\y}
\integer{s3=\b+\x}
\integer{s4=\b-\x}
\matrix{rep=\s1,\s2,\s3,\s4
\s2,\s1,\s3,\s4
\s1,\s2,\s3,\s4
\s2,\s1,\s3,\s4}

\matrix{datatrue=asis(
 \rep[\cas;1]
 )}
\matrix{datafalse=asis(
\rep[\cas;2]
\rep[\cas;3]
\rep[\cas;4])
}

\text{explain0=asis(Que vaut la valeur finale de a dans le programme suivant écrit
en langage Python ?)}
\text{explain=a=\a
b=\b
if a>=0:
  b=b-\x
else:
  b=b+\x
if b>0:
  a=a+\y
else:
  a=a-\y
}
\text{feedback_generalpre=En langage naturel, le programme est :}
\text{feedback_program=
\(a) prend la valeur \a
\(b) prend la valeur \b
Si \(a \ge 0) alors
  \(b) prend la valeur \(b-\x)
Sinon \(b) prend la valeur \(b+\x)
Fin du si
Si \(b > 0) alors
  \(a) prend la valeur \(a+\y)
Sinon \(a) prend la valeur \(a-\y)
Fin du si
}
\text{feedback_generalpost=À la fin de l'exécution, \(a) vaut \rep[\cas;1].}
