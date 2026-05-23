\title{Question T1124 Recherche d'entiers}
\keywords{mental_calculation,equations,multiplication,subtraction}
\matrix{donnees24=40,20,10,8
48,16,12,8
60,15,12,10
80,20,16,10
100,50,25,20}##En premier le produit, ensuite plus grand des deux facteurs##
\integer{choix241=randint(1..rows(\donnees24))}
\integer{n24=\donnees24[\choix241;1]}
\integer{choix242=randint(2..4)}
\integer{n242=\donnees24[\choix241;\choix242]}
\integer{n241=\n24/\n242}
\integer{diff24=\n242-\n241}

\text{enonce=Si je choisis deux entiers naturels dont le produit est \n24 et la différence est \diff24, quels entiers ai-je choisis ?}
\text{enonceb= <div class="wims_instruction">On séparera les deux entiers par une virgule.</div>}
\text{rep=\n241,\n242}
\text{feedback=On peut écrire \n24 comme un produit de deux entiers et vérifier que la différence est bien égale à \diff24. }
\text{size=10}
\integer{size=6}
