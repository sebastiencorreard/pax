\title{Question 212 NS Double distributivité}
\keywords{quizz,literal_calculation}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{a=randint(3..9)*randitem(1,-1)}
\integer{b=(abs(\a)+randitem(1,-1))}
\integer{b=(\a>0)? -\b:\b*randitem(1,1,-1)}

\function{f=maxima((x+\a)(x+\b))}

\text{enonce=La forme développée de \(\f\) est&nbsp;&#58;}



\function{gd=maxima(x^2+(\a+\b)*x+\a*\b)}
\function{bad1=maxima(x^2+(\a+\b)*x-\a*\b)}
\function{bad2=maxima(x^2-(\a+\b)*x+\a*\b)}
\function{bad3=maxima(x^2-(\a+\b)*x-\a*\b)}
\text{bads=\(\bad1\),\(\bad2\),\(\bad3\)}
\text{good=\(\gd\)}


\integer{aabs=abs(\a)}
\integer{babs=abs(\b)}
\text{as=(\a>0)? +\aabs:-\aabs}
\text{bs=(\b>0)? +\babs:-\babs}
\integer{aabs=abs(\a)}
\integer{babs=abs(\b)}
\text{ps=(\a*\b)>0? +\aabs\times \babs:-\aabs\times \babs}


\text{feedback=La bonne réponse est \good. En effet, pour tout réel \(x\), \(\f=x\times x\as\times x\bs\times x\ps=\gd\).  }
