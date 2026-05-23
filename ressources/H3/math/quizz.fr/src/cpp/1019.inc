\title{Question 1019 Evolution des prix}
\keywords{mental_calculation,proportionality,percents}
%%%%%%%%%%% question 4 %%%%%%%%%%%

\integer{i4=randint(5..9)*10}
\integer{b4=randint(1..5)*10}
\real{cm4=1-\b4/100}
\real{temp4=\i4*\cm4}
\real{rep=\temp4}
\text{enonce=Le prix d'un manteau est \i4 &euro;. Il baisse de \b4 %.<br>Quel est son nouveau prix  &#63;<br>Réponse :  }
\text{enonceb=&euro;}
\integer{f14=\i4/10}
\integer{f24=\cm4*10}
\text{feedback=Il faut multiplier le prix par le coefficient multiplicateur, qui est égal ici à \(\cm4\). <br>\(\i4 \times \cm4 = \f14 \times \f24 = \temp4\).}
