\title{Question 0817 Calcul avec des fractions}
\keywords{mental_calculation,skill_reasoning,fraction,addition,subtraction,multiplication}

\integer{a0817=randint(3,4,5,6,7)}
\integer{b0817=randint(1..\a0817-1)}
\real{rep=0}
\text{enonce0=shuffle(\left(1-\frac{\b0817}{\a0817}\right),\left(1-\frac{\a0817}{\a0817}\right))}
\text{enonce=Calcule &#58; \(\enonce0[1] \enonce0[2]\) <br> Réponse &#58;}
\text{enonceb=}
\text{feedback=\( 1-\frac{\a0817}{\a0817} = 0 \) le produit est donc nul. }
