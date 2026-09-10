\title{Question 112 S Quotient de puissances}
\keywords{quizz,power,calculation,division}
\observation{Question du sujet zéro sujet-specialite-2_0.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randomitem(7,8,9)}
\integer{m=\n-randomitem(2,3)}
\integer{p=randomitem(2,5,5)}
\text{enonce=On considère le nombre <span class="nowrap">\(N=\frac{10^\n}{\p^\m}\).</span> On a&nbsp;&#58;}

%%%%
\integer{q1=\p=2?5:2}
\integer{n1=\n-\m}
\integer{q1bis=10^\n/(\p^\m)}
\text{q1bis=slib(numeration/ecriturenombre \q1bis,tex)}
\integer{q2=10^\n1}
\integer{k=randint(1..3)}
\text{good=item(\k,\(N= \q1^\n \times \p^\n1\),\(N=\q1^\m \times 10^\n1\),\(N=\q1bis\))}
%%% feed
\text{endfeed1=\(\frac{10^\n}{\p^\m}\)<br>\({}=\frac{(\p \times \q1)^\n}{\p^\m}\)<br>\({}=\frac{\p^\n \times \q1^\n}{\p^\m}\)<br>\({}=\p^{\n-\m} \times \q1^\n\)<br>\({}=\p^{\n1} \times \q1^\n\)}
\text{endfeed2=\(\frac{10^\n}{\p^\m}=\frac{10^\m \times 10^\n1}{\p^\m}\)<br>\({}=\left(\frac{10}{\p}\right)^\m \times 10^\n1\)<br>\({}=\q1^\m \times 10^\n1\)}
\integer{q3=(\q1)^\m}
\text{endfeed3=\endfeed2 <br>\({}=\q3 \times \q2\)<br>\({}=\q1bis\)}
\text{endfeed=item(\k,\endfeed1,\endfeed2,\endfeed3)}
\text{bad1=\(N=\q1^{\n1}\)}
\integer{q3=\q1*10^\n1}
\text{q3=slib(numeration/ecriturenombre \q3,tex)}
\text{bad2=\(N=\q3\)}
\text{bad3=\(N=\frac{1}{10^\n1}\)}
\text{bads=\bad1,\bad2,\bad3}

\text{feedback=La bonne réponse est \good.<br>En effet&nbsp;&#44; \endfeed}
