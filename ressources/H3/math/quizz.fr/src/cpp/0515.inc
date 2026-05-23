\title{Question 0515 Dixièmes}
%%%%% issu de {Question 0615 Dixièmes 0}
\keywords{decimals,addition}
\integer{type=randint(1,2,2,2)}
\integer{a=randint(2..8)}
\integer{b=randint(2..8)}
\integer{k=randint(2..8)}
\text{enonce=(\type==1)? Ajoute \(\k\) dixième à \(\a\) unités : Combien de dixièmes dans \(\b\) unités ?}
\real{rep=(\type==1)? \a+0.1*\k: simplify(10*\b)}
\text{enonceb=}
\real{ksol=\k*0.1}
\text{feedback=\type=1?Rappel &#58; \(\k\) dixièmes est égal à \(\ksol\):Rappel &#58; une unité est égale à 10 dixièmes.}
