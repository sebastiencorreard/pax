\title{Question 109 S Calculs avec les fractions bis }
\keywords{quizz,skill_calculate,fraction}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
\text{F=randomitem(F,G,T,P)}
\text{coeff=shuffle(2,3,4)}
\integer{n=\coeff[1]}
\integer{n2=\n*randomitem(2,3)}
\integer{n3=\coeff[2]}
\integer{n4=randomitem(1,-1,-1)}
\text{enonce=On considère <span class="nowrap">\(\F=a+\frac{b}{c d}\).</span> <br>Lorsque \(a=\frac{1}{\n}\)&#44; \(b=\n3\)&#44; \(c=\n2\)&#44; \(d=\frac{\n4}{\n2}\)&#44; la valeur de \(\F\) est égale à&nbsp;&#58; }

\rational{tempg=1/\n+\n3/(\n2*(\n4/\n2))}
\text{good=\(\tempg\)}
\rational{t1=-\tempg}
\text{bad1=\(\t1\)}
\rational{t2=1/\n*\n3/(\n2*(\n4/\n2))}
\text{bad2=\(\t2\)} 
\text{bad3=\(-\t2\)} 
\text{bads= \bad1,\bad2,\bad3}
\integer{nbis=\n4=-1?1-\n*\n3:1+\n*\n3}

\text{sgn1=\n4=-1?-:+}
\integer{n34=\n3/\n4}
\text{n34txt=\n34<0?\n34:+\n34}
\integer{nn3=\n*\n3}
\text{finfeed=On a <span class="nowrap">\(cd=\n2\times\frac{\n4}{\n2}=\n4\).</span><br>\(\frac{b}{c d}=\frac{\n3}{\n4}=\n34\) <br>Ainsi il faut calculer <span class="nowrap">\(\frac{1}{\n}\n34txt=\frac{1}{\n}\sgn1\frac{\nn3}{\n}=\frac{\nbis}{\n}\).</span> }
\text{feedback=La bonne réponse est \good. <br>\finfeed }


 
