\title{Question 0909 Multiplication de décimaux }
\keywords{mental_calculation,multiplication,decimals}
\text{decim=shuffle(3,7,4,6,8,9)}%%%eviter d'avoir un 2*5
\real{a0909=randint(1..9)+\decim[1]/10}
\real{b0909=randint(1..9)+\decim[2]/10}
\real{bad1=\a0909*\b0909*10}
\real{bad2=\a0909*\b0909/10}
\real{rep=\a0909*\b0909}
\text{enonce=Sélectionne le résultat de \a0909\( {}\times {} \)\b0909. }
\text{enonceb=}
\text{feedback=Rappel : \(\a0909\) possède une décimale, \(\b0909\) possède une décimale donc \(\a0909 \times \b0909\) a \(1+1=2\) décimales.}
