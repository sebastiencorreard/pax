\title{Question 207 S Isoler une variable}
\keywords{quizz,literal_calculation}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
\text{sgn=randomitem(+,+,-)}
\text{enonce=On considère \(x\)&#44; \(y\)&#44; \(u\) des réels non nuls tels que <span class="nowrap">\(\frac{1}{x}\sgn\frac{1}{y}=\frac{1}{u}\).</span><br>On peut affirmer que&nbsp;&#58;}

\text{good=\sgn issametext +?\(u=\frac{x y}{x+y}\):\(u=\frac{x y}{y-x}\)}
\text{bad1=\sgn issametext +?\(u=\frac{x+y}{x y}\):\(u=\frac{x y}{x-y}\)}
\text{bad2=\sgn issametext +?\(u=xy\):\(u=-x y\)}
\text{tbad3=randomitem(\(u=x-y\),\(u=y-x\))}
\text{bad3=\sgn issametext +?\(u=x+y\):\tbad3}
\text{bads=\bad1,\bad2,\bad3}

\text{txtf1=\sgn issametext +?\frac{x+y}{x y}:\frac{y-x}{x y}}
\text{endfeed=<br> On peut remarquer que <span class="nowrap">\(\frac{1}{u}=\frac{1}{x}\sgn\frac{1}{y}=\txtf1\).</span> <br>Par passage à l'inverse&#44; on obtient <span class="nowrap">\(u\).</span>}
\text{feedback=La bonne réponse est \good. \endfeed}
