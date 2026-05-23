\title{Question 0820 Calculs}
\keywords{mental_calculation,fraction,division,decimals,subtraction}
\integer{a=randint(3..9)}
\integer{d=randint(4,5)}
\integer{bc=randint(2,3,4)*\d}
\integer{bcd=\bc/\d}
\real{b=randint(1..\bc-2)+randint(1..9)/10}
\real{c=\bc-\b}
\real{rep=\a-(\b+\c)/\d}
\real{rep0820=\rep}
\text{enonce=Calcule &#58; <br> \(\a-\frac{\b+\c}{\d}={}\)}
\text{enonceb=}
\text{feedback=Voici les étapes &#58;<ul><li>\(\b+\c=\bc\)</li><li>\(\frac{\bc}{\d}=\bcd\)</li><li>\(\a-\bcd=\rep0820\)</li></ul>}
