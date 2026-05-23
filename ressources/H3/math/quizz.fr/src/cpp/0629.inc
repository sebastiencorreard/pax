\title{Question 0629 Problème}
\keywords{pbsolving,proportionality}

\matrix{data=4,6,8,12,2
6,12,9,18,3
8,12,16,24,4
10,4,5,20,15}
\integer{choix29=randint(1..rows(\data))}
\integer{a=\data[\choix29;1]}
\integer{h=2*randint(6..15)}
\integer{b=\data[\choix29;randint(2..5)]}
\real{rep=\h*\b/\a}
\text{enonce=\(\a\) cubes identiques empilés ont une hauteur totale de \(\h\) cm. Quelle est la hauteur de \(\b\) cubes empilés ?}
\text{enonceb=cm}
\text{feedback=}
