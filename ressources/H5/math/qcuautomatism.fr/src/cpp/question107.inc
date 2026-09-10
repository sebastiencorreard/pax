\title{Question 107 T Calculs avec les fractions }
\keywords{quizz,skill_calculate,fraction}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{n=randomitem(1,2,2)}
\text{m=randomitem(3,3,6)}

\text{enonce=On considère <span class="nowrap">\(T=\frac{\n}{1-\frac{\n}{\m}}\).</span> Que vaut \(T\)&nbsp;&#63; }

\rational{tempg=\n/(1-\n/\m)}
\text{good=\(\tempg\)}
\integer{t1=randomitem(-2,-1,0)}
\text{bad1=\(\t1\)}
\integer{t2=randomitem(9,7,8)}
\text{bad2=\(\t2\)} 
\text{bad3=\(\frac{\n}{\m}\)} 
\text{bads= \bad1,\bad2,\bad3}
\integer{nbis=\m-\n}
\text{finfeed=<span class="nowrap">\(T=\frac{\n}{1-\frac{\n}{\m}}=\frac{\n}{\frac{\nbis}{\m}}=\n \times \frac{\m}{\nbis}\).</span> <br>On utilise le fait que diviser par un nombre c'est multiplier par son inverse.}
\text{feedback=La bonne réponse est \good. <br>\finfeed }


 
