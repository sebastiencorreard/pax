\title{Question 0822 Calcul réfléchi}
\keywords{mental_calculation,decimals,multiplication,methodical_calculation}
%%%% a*b*c un des trois est négatif, b est pair
\integer{c=random(-1,-1,-1,1)*random(3,5)}
\integer{cabs=abs(\c)}
\integer{b=\c<0?4:random(-1,1)*4}
\integer{bbabs=abs(\b/2)}
\integer{babs=abs(\b)}
\real{a=random(2,3,4)+0.5}
\real{a=\b*\c<0?\a:-1*\a}
\real{aabs=abs(\a)}
\real{a2=2*\a}
\real{a2abs=abs(\a2)}
\text{enon0=\a \times \b \times \c}
\if{\c<0}{\text{enon0=\a \times \b \times (\c)}}
\if{\b<0}{\text{enon0=\a \times (\b) \times \c}}

\real{rep=\a*\b*\c}
\real{rep0822=\rep}
\text{enonce=Calcule &#58; \(\enon0\) <br> Réponse &#58;}
\text{enonceb=}
%%%% feedback %%%%
\text{feedback=On sait que \(\a\times2=\a2 \) puis en remarquant que \(\babs=2 \times \bbabs \) cela facilite les calculs.
<br> \(\enon0= - \aabs \times 2 \times \bbabs \times \cabs=-\a2abs \times \bbabs \times \cabs=\rep0822\)}
