\title{Question 1003 Développer et simplifier}
\keywords{mental_calculation,literal_calculation}
%%%%%%%%%%%%%% Question 3

%%%%%(ax+b)(cx+a) 
\text{liste3=shuffle(2,3,5)}
\integer{a3=\liste3[1]}
\integer{b3=random(-1,1)}
\text{sign=\b3<0 ? : +}
\integer{c3=\liste3[2]}
\text{x3=random(a,x,y,n,b,m,p)}

\text{temp3=maxima(expand((\a3*\x3+\b3)*(\c3*\x3+\a3)))}
\text{bsol3=\b3<0?(\b3):\b3}
\text{rep=\temp3 }
\text{enonce= Développe et simplifie : \( (\a3 \x3 \sign \b3)(\c3 \x3 +\a3)={} \) }
\text{enonceb=}
\text{feedback=Rappel : \( (\a3 \x3+\bsol3)(\c3 \x3+\a3){}\)
<br>\({}=\a3 \times \c3 \x3^2+\a3 \times \a3 \times \x3+\bsol3 \times \c3 \times \x3+\bsol3 \times\a3 \). <br>Il suffit de réduire.}
