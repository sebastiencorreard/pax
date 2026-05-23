\title{Question 1214 Calcul de discriminant}
\keywords{mental_calculation,equations}
x^2-2sqrt(3)x+d
x^2 + c a sqrt(b)x+d c-1 ou 1
x^2 +\c*\a*\sqrt{\b}*x+\d

\text{quest=shuffle(2,3,5)}
\integer{a=\quest[1]}
\integer{a2=\a*\a}
\real{b=\quest[2]}

\text{ctxt=random(-,+)}
\integer{c=\ctxt issametext -?-1:1}
\integer{d=randint(1,1,1,2)}

\real{rep=\a*\a*\b-4*\d}
\text{enonce=Discriminant de <br>\( x^2 \ctxt \a \sqrt{\b} x+\d \) <br> Réponse &#58; }
\text{enonceb=}
\text{feedback= \(\left( \ctxt \a \sqrt{\b}\right)^2\a =  \a2  \times \b\)}
