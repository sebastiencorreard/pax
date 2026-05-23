\title{Question T1127 Proportion}
\keywords{mental_calculation,percents,proportionality}
%%%%%%%%%%%%%% Question 27 %%%%%%%%%%%%

\matrix{donnees27=10,20,20,30,30
20,10,15,25,30
25,12,16,20,24
50,14,16,18,20
75,12,16,20,24
}##en 1er le % et après les effectifs totaux ##
\integer{choix271=randint(1..rows(\donnees27))}
\integer{choix272=randint(2..5)}
\integer{n27=\donnees27[\choix271;\choix272]*\donnees27[\choix271;1]/100}
\integer{rep=\donnees27[\choix271;1]}
\text{enonce=Si \(\n27\) des \(\donnees27[\choix271;\choix272]\) classes du lycée participent au concours "La Course Aux Nombres", quel pourcentage de classes a participé &#63;<br>}
\text{enonceb=\(\%\).}
\text{feedback=\(\n27 \div \donnees27[\choix271;\choix272]=\rep \%\)}
\integer{size=6}
