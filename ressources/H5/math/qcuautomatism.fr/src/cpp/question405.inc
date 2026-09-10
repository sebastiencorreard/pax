\title{Question 405 NS prix multiplié}
\keywords{quizz,percentage,percents}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }

\matrix{c=doublé,100,2,200,50,2
triplé,200,3,300,100,3
quadruplé,300,400,4,40,4}


\text{cas=randomrow(\c)}
\text{pp=\cas[1]}
\integer{n=\cas[6]}

\text{enonce=un prix a \pp. Cela signifie que le prix a augmenté de&nbsp;&#58;}

\text{good=\( \cas[2] \% \)}
\text{bads=\( \cas[3] \% \),\( \cas[4] \% \),\( \cas[5] \% \)}
\text{feedback=La bonne réponse est \( \cas[2] \% \) puisque augmenter de \(\cas[2]\) équivaut à multiplier par \(1+\frac{\cas[2]}{100}=\n \).}
