\title{Question 104 Calcul d’un pourcentage d’une quantité}
\keywords{quizz,percentage}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-b-mathematiques.pdf du DNB publié sur éduscol en décembre 2025}

\text{x=randomitem(lunettes,lentilles,appareils dentaires, boucles d'oreilles)}
\integer{y=20*randint(5..50)}  %%définit le nombre d'élèves
\integer{z=randomitem(5,10,25,50,75)} %%définit le pourcentage
\real{zdec=\z/100} %% MB
\if{\z==5}{\text{\astuce=<u>Astuce &nbsp;&#58;</u> calculer \(\z&#37;) d'une quantité revient à la diviser par \(20). <br>En effet \(\zdec) = \(\z/100) = \(1/20)}}
\if{\z==10}{\text{\astuce=<u>Astuce &nbsp;&#58;</u> calculer \(\z&#37;) d'une quantité revient à la diviser par \(10). <br>En effet \(\zdec;) = \(\z/100) = \(1/10)}}
\if{\z==25}{\text{\astuce=<u>Astuce &nbsp;&#58;</u> calculer \(\z&#37;) d'une quantité revient à la diviser par \(4). <br>En effet \(\zdec) = \(\z/100) = \(1/4)}}
\if{\z==50}{\text{\astuce=<u>Astuce &nbsp;&#58;</u> calculer \(\z&#37;) d'une quantité revient à la diviser par \(2). <br>En effet \(\zdec) = \(\z/100) = \(1/2)}}
\if{\z==75}{\text{\astuce=<u>Astuce &nbsp;&#58;</u> calculer \(\z&#37;) d'une quantité revient à la diviser par \(4) puis multiplier par \(3). <br>En effet \(\zdec) = \(\z/100) = \(3/4)}}

\text{enonce=Dans un collège de \(\y) élèves&#44; \(\z &#37;) des élèves portent des \x.<br> Combien d'élèves portent des \x&nbsp;&#63;}
\text{enonceb=}

\integer{rep=\y*\z/100}
\text{typerep=numeric}
\text{feedback=Calculer \z &#37; de \y revient à effectuer : \(\zdec\times\y=\rep)<br>\astuce}
