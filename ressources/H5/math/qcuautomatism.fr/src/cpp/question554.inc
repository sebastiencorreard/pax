\title{Question 554 NS evolution et relation de récurrence}
\keywords{quizz,percents,sequence}
\observation{Question du sujet zéro sujet-specifique-3.pdf publié sur EDUSCOL en juin 2025 }
\integer{p=randint(1..13)}
\real{coefgood=1-\p/100}
\real{coefbad=\p/100}

\text{enonce=Le volume d’un glacier diminue de \(\p \%\) chaque année. Si \(V_n\) désigne le volume du glacier pour l’année \(n\) on a&nbsp: }

\text{good=\(V_{n+1}=V_n \times \coefgood\)}
\text{bads=\(V_{n+1}=V_n - \coefgood \),\(V_{n+1}=V_n \times \coefbad\),\(V_{n+1}=V_n - \coefbad\)} 

\text{feed=Une diminution de \(\p \%\) équivaut à une multiplication par <span class="nowrap">\(1-\frac{\p}{100}=\coefgood\).</span> }

\text{feedback=La bonne réponse est "\good". <br>\feed}
