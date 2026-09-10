\title{Question 652 S Calculer un coefficient directeur}
\keywords{quizz,equations,affine_function,reference_function}
\observation{Question du sujet zéro sujet-specialite-2.pdf publié sur EDUSCOL en juin 2025 }

\integer{m=randint(2..5)*randomitem(-1,1)}
\integer{p=randint(2..5)*randomitem(-1,1)}
\text{x=shuffle(0,randint(1..3)*randomitem(-1,1))}
\integer{xA=\x[1]}
\integer{yA=\m*\xA+\p}
\integer{xB=\x[2]}
\integer{yB=\m*\xB+\p}

\text{enonce= Le plan est muni d’un repère orthogonal. <br>On note \(d\) la droite passant par les points
\(A(\xA &#59; \yA)\) et <span class="nowrap">\(B(\xB &#59; \yB)\).</span> <br>Le coefficient directeur de la droite \(d\) est égal à&nbsp;&#58; }

\text{good= \(\m\)}
\integer{mbad=\m+randomitem(-1,1)}
\text{bad1= \(\mbad\)}
\integer{mabs=abs(\m)}
\text{signe=\m>0?-:}
\text{bad2= \(\signe \frac{1}{\mabs}\)}
\integer{mbadabs=abs(\mbad)}
\text{signe2=\signe issametext -?:-}
\text{bad3= \(\signe2 \frac{1}{\mbadabs}\)}
\text{bads=\bad1,\bad2,\bad3}
%%%% feedback %%%%%%%
\text{xBtx=\xB<0?(\xB):\xB}
\text{yBtx=\yB<0?(\yB):\yB}

\text{feedback=La bonne réponse est \good. <br>On utilise la formule \(\frac{y_A-y_B}{x_A-x_B}\)<span class="nowrap">\({}=\frac{\yA-\yBtx}{\xA-\xBtx}=\m\).</span>}
