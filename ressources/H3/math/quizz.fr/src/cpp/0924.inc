\title{Question 0924 Hausse de prix}
\keywords{mental_calculation,percentage,pbsolving}
\integer{p9=randint(2..5)*100}
\integer{b9=randint(25,30,40)}
\integer{type=random(-1,1)}
\text{action=\type=-1?baisse : augmente}
\real{rep=\p9*(1+\type*\b9/100)}
\text{enonce=Une console de jeu coûte \(\p9\) &euro;. Son prix \action de \(\b9 \%\). Quel est son nouveau prix ?}
\text{enonceb=&euro;.}
\real{temp9=\b9/100}
\real{tempb9=\b9/100*\p9}
\text{feedback=\type=-1? Montant de la baisse &#58; \(\temp9 \times \p9=\tempb9\), il reste à faire la soustraction.:Montant de l'augmentation &#58; \(\temp9 \times \p9=\tempb9\), il reste à faire l'addition.}
