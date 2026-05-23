\title{Question 0615 Dixièmes}
\keywords{decimals,addition}
\integer{type=randint(1,2)}
\real{a=randint(2..8)+0.9+randint(1..9)/100}
\real{b=(randint(1..9)*100+randint(1..9)*10+randint(1..9))/10}
\text{\at=wims(replace internal . by , in \a)}
\text{\bt=wims(replace internal . by , in \b)}
\text{enonce=(\type==1)? Ajoute un dixième à \(\at\) : Combien de dixièmes dans \(\bt\) ?}
\real{rep=(\type==1)? \a+0.1: simplify(10*\b)}
\text{enonceb=}
\text{feedback=}
