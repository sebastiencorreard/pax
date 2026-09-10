\title{Question 555 S Comparer les prix après évolutions}
\keywords{quizz,percentage,percents,decimals}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randomitem(10,20,30,40)}
\text{verbesvol=shuffle(augmente,baisse)}
\real{txdecim=\n/100}

  
\text{enonce=Le prix d’un article est noté <span class="nowrap">\(P\).</span> Ce prix \verbesvol[1] de \(\n\%\) puis \verbesvol[2] de <span class="nowrap">\(\n\%\).</span><br>A l’issue de ces deux variations&#44; le nouveau prix est noté <span class="nowrap">\(P_1\).</span> On peut affirmer que &nbsp;&#58;}

\text{good=\(P_1 &lt;P\)}
\real{badevolabs=10*\evolabs}
\text{bad1=ça dépend de \(P\)}
\text{bad2=\(P_1=P\)}
\text{bad3=\(P_1 &gt;P\)}

\text{bads=\bad1,\bad2,\bad3 }

\text{endfeed=<br>\(P_1\) se calcule ainsi \(P_1=P\times (1-\txdecim)(1+\txdecim)\)<br>On reconnait \((1-\txdecim)(1+\txdecim)=1-\txdecim^2\) qui est plus petit que \(1)}

\text{feedback=La bonne réponse est  \good. \endfeed  }
  
