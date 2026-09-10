\title{Question 106 T Arrondis }
\keywords{quizz,skill_calculate}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randomitem(40,30)}
\text{sgn=randomitem(+,-)}
\integer{n1=\n*randomitem(-1,1)}
\integer{n2=\n1<0?\n:-\n}

\text{enonce=\(10^{\n1} \sgn 10^{\n2}\) est environ égal à&nbsp;&#58; }

\text{sgnbis=\sgn issametext -?-:}
\text{good=\n1<0?\(\sgnbis 10^{\n2}\):\(10^{\n1}\)}
\text{bad1=\(20^{\n}\)}
\text{bad2=0} 
\text{bad3=\(10^0\)} %%%% confusion moitié et double
\text{bads= \bad1,\bad2,\bad3}
\text{finfeed=En effet \(10^{-\n}\) est très petit&#44; très proche de zéro.}
\text{feedback=La bonne réponse est \good. \finfeed}
