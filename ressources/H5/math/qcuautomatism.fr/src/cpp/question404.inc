\title{Question 404 NS Calcul de proportion}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }
%%% MB %%%

\text{pourcentages=20,25,75,50,10}
\text{fracpour=\frac{1}{5},\frac{1}{4},\frac{3}{4},\frac{1}{2},\frac{1}{10}}
\integer{q=randomitem(1,2,3,4,5)}
\text{p=\pourcentages[\q]}
\integer{pinit=randint(21..49)*10}
  
\text{enonce=L’opération qui permet de calculer \(\p \%\) de \(\pinit\) est&nbsp;&#58;}
\integer{k1=randomitem(1,2,3,3)}
\text{goods=\frac{\pinit \times \p}{100},\p \times \pinit \times 0.01,\fracpour[\q] \times \pinit}
\text{bad1=\frac{\pinit }{\p \times 100}}
\text{bad2=\p \times \pinit \times 0.1}
\text{bad3=\frac{\pinit \times 100}{\p}}
\text{good=\goods[\k1]}
\text{good=\(\good\) }
\text{bads=\(\bad1 \),\(\bad2 \),\( \bad3 \)}
%%% feed %%
\text{endfeeds=\({}=\frac{\p}{100} \times \pinit\)<br>\({}=\frac{\pinit \times \p}{100}\),\({}=\frac{\p}{100} \times \pinit\)<br>\({}=\frac{\pinit \times \p}{100}\)<br>\({}=\pinit \times \p \times \frac{1}{100}\),\({}=\frac{\p}{100} \times \pinit\)<br>\({}=\fracpour[\q] \times \pinit\)}
\text{endfeed=\endfeeds[\k1]}
\text{feedback=La bonne réponse est  <span class="nowrap">\good.</span><br> En effet il faut faire le calcul suivant \(0.\p \times \pinit\) \endfeed}
  
