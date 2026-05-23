\title{Question 0912 Écriture fractionnaire et pourcentage }
\keywords{mental_calculation,fraction,decimals,percents}
\integer{a12=random(25,50)}
\integer{b12=\a12=25?randint(1..24):randint(26..49)}
\text{temp0912=simplify(\b12/\a12*100)}
\text{rep=\temp0912}
\text{enonce=Complète \(\frac{\b12}{\a12} = \)}
\text{enonceb=\( \% \).}
\integer{a12b=\a12=25?\a12*4:\a12*2}
\integer{b12b=\a12=25?\b12*4:\b12*2}
\text{feedback=Rappel : on peut écrire \(\frac{\b12}{\a12} =\frac{\b12b}{\a12b} =\temp0912\% \)}
