\title{Question 108 T Calculs avec les décimaux }
\keywords{quizz,skill_calculate,fraction,decimals}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{n=randomitem(1,2)}
\text{m=randomitem(1,1,2)}
\text{puiss=shuffle(10,100,1000)}
\integer{p1=\puiss[1]}
\integer{p2=\puiss[2]}
\text{E=randomitem(T,P,E)}
\text{enonce=On considère <span class="nowrap">\(\E=\frac{\n}{\p1}+\frac{\m}{\p2}\).</span> On a&nbsp;&#58; }

\real{tempg=\n/\p1+\m/\p2}
\text{good=\(\E=\tempg\)}
\real{t1=\n+\m/\p2}
\text{bad1=\(\E=\t1\)}
\integer{t2=\n+\m}
\integer{t2b=\p1*\p2}
\text{bad2=\(\E=\frac{\t2}{\t2b}\)} 
\real{t4=randomitem(\tempg/10,\tempg*10)}
\text{bad3=\(\E=\t4\)} 
\text{bads= \bad1,\bad2,\bad3}

\text{finfeed=En effet&nbsp;&#58; <ul class="wims_nopuce"><li>\(\frac{1}{10}=0.1\)</li><li>\(\frac{1}{100}=0.01\)</li><li>\(\frac{1}{1000}=0.001\)</li><li>...</li></ul>}
\text{feedback=La bonne réponse est \good. <br>\finfeed }


 
