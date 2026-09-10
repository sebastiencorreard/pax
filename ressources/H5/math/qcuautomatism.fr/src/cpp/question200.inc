\title{Question 200 T Programme de calcul}
\keywords{quizz,skill_modelling,literal_calculation}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDU SCOL en juin 2025 }
\text{cas=randomitem(1,2)}
\text{mot1=double,triple}
\text{mot1=\mot1[\cas]}
\text{x=randomitem(x,x,m,n,t,h)}
\text{qust=2,3}
\integer{q1=\qust[\cas]}
\integer{q=\qust[\cas]+1}
\integer{q1bad=\qust[\cas]}


\text{enonce=On additionne un nombre réel \(\x \)&#44; avec son \mot1 et son carré. Le résultat est égal à&nbsp;&#58;}

\text{good=\(\q\x+\x^2\)}
\text{bads=\((\x+\q1bad\x)^2\),\(\x+(\q1bad\x)^2\),\( 1+\q1bad \x^2\)}
\text{feedback=La bonne réponse est \good.<br> Le calcul à produire est <span class="nowrap">\(\x+ \q1\x+\x^2={}\)\good</span> après réduction.}
