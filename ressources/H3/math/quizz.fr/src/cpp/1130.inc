\title{Question 1130 Produit&#44; quotient d'exponentielles}
\keywords{mental_calculation,exponent,multiplication,power,division}

%%% e^a*e^b / e^c= 10^??
\integer{c7=randint(4..5)}
\integer{a7=randint(6..7)}
\integer{b7=randint(2..3)}

%%%%%% fait par méthode spéciale \frac{e^\a7 \times e^\b7}{e^\c7}=e^{...} %%%%
\text{enonce=Complète \(\frac{e^\a7 \times e^\b7}{e^\c7}=e^{....}\) <br> Réponse :}
\text{enonceb=}
\integer{rep=\a7+\b7-\c7}
\text{feedback=Rappel : \(\frac{e^\a7 \times e^\b7}{e^\c7}=e^{\a7+\b7-\c7}=e^\rep\)}
