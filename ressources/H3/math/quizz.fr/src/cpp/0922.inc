\title{Question 0922 Produit&#44; quotient de puissances de 10}
\keywords{mental_calculation,multiplication,power,division}
%%%% question hors norme
%%% 10^a*10^b / 10^c= 10^??
\integer{c7=randint(4..5)}
\integer{a7=randint(6..7)}
\integer{b7=randint(2..3)}

%%%%%% fait par méthode spéciale \frac{10^\a7 \times 10^\b7}{10^\c7}=10^{...} %%%%
\text{enonce=Complète \(\frac{10^\a7 \times 10^\b7}{10^\c7}=10^{....}\) <br> Réponse :}
\text{enonceb=}
\integer{rep0922=\a7+\b7-\c7}
\integer{rep=\rep0922}
\text{feedback=Rappel : \(\frac{10^\a7 \times 10^\b7}{10^\c7}=10^{\a7+\b7-\c7}=10^\rep0922\)}
