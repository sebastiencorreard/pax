\title{Question 1204 Somme qui contient des puissances de 10}
\keywords{mental_calculation,decimals,addition,power,exponent}
%%% sj a+b*10^-p
\text{quest=shuffle(2,3,4,5,6,7,8,9)}
\integer{a=\quest[1]}
\integer{b=\quest[2]}
\integer{p=randint(1..3)}
\real{temp01=10^-\p}
\real{rep=\a+\b*10^(-\p)}
\text{enonce=\(\a + \b \times 10 ^{-\p}={}\) }
\text{enonceb=}
\text{feedback=Rappel : \(10 ^{-\p}=\frac{1}{10^\p}=\temp01\)}
