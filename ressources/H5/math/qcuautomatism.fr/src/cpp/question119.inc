\title{Question 119 NS Calculs avec les décimaux }
\keywords{quizz,skill_calculate,fraction,decimals}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }
%%%MB
\text{n=randomitem(1,2)}

\integer{n0=\n*10}
\text{fact=10,100,1000}
\integer{cas=randomitem(1,2)}
\if{\cas=1}{\integer{n1=10}
  \integer{n2=1000}
  \integer{\n3=100}}
\if{\cas=2}{\integer{n1=100}
  \integer{n2=1000}
  \integer{n3=10}} 
\integer{cas2=randomitem(1,2)}
\real{p10=\n/\n1}
\real{p20=\n/\n2}
\text{p1=item(\cas2,\p10,\frac{\n}{\n1})}
\text{p2=item(\cas2,\frac{\n}{\n2},\p20)}

\text{E=randomitem(T,P,E)}

\text{enonce=On considère <span class="nowrap">\(\E=\n0+\p1+\p2\).</span> On a&nbsp;&#58; }

\real{tempg=\n0+\p10+\p20}
\text{good=\(\E=\tempg\)}
%%%%%%%%%%
\text{t1=item(\cas2,\frac{\n}{\n2},\frac{\n}{\n1})}
\text{bad1=\(\E=\t1\)}
\integer{t2=2*\n0}
\integer{t3=max(\n1,\n2)}
\text{\t2=\frac{\t2^{-1}}{\t3}}
\text{bad2=\(\E=\t2\)}
\real{p3=\n/\t3}
\real{t4=\n0+\n/\n3+\p3}
\text{bad3=\(\E=\t4\)} 
\text{bads= \bad1,\bad2,\bad3}
\text{calcfeed=item(\cas,\frac{\n}{\n1}=\p10,\frac{\n}{\n2}=\p20)}
\text{calcfeed2=item(\cas,\E=\n0+\p10+\p2,\E=\n0+\p1+\p20)}
\text{finfeed=En effet&nbsp;&#58; \(\calcfeed\) <br>Donc <span class="nowrap">\(\calcfeed2\).</span>}
\text{feedback=La bonne réponse est \good. <br>\finfeed }


 
