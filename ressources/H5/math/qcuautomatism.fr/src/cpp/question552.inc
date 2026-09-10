\title{Question 552 T Coeff. mult. après évolution}
\keywords{quizz,quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randomitem(20,30,10)}
\real{ndecim=\n/100}
\text{var=randomitem(+,-)}
\real{cm=1 \var \ndecim}
\text{mot1=\var issametext +?augmentations:baisses}

\real{cmfinal=\cm*\cm}  
\text{enonce=Le prix d’un article est noté <span class="nowrap">\(P\).</span><br> Il connait deux \mot1 de <span class="nowrap">\(\n\%\).</span><br> Le prix après ces \mot1 est&nbsp;&#58;}

\text{cas=randomitem(form,dev)}
\text{good=\cas issametext form?\(P \times \cm^2\):\(P \times \cmfinal\)}
\text{badvar=\var issametext +?-:+}
\text{bad1= \(P \times \left(1\badvar\left(\frac{\n}{100}\right)^2\right)\)}
\real{cmdouble=1 \var 2*\n/100}
\text{bad2= \(P \times \cmdouble\)}
\text{bad3= \(\frac{P}{\cmfinal}\)}
\text{bads= \bad1, \bad2,\bad3}
\text{finfeed2= \cas issametext \dev?=\cmfinal:}
\text{mot2=\var issametext +?l'augmente:le baisse}
\text{mot3=\var issametext +?augmenter:baisser}
\text{endfeed=<br>Pour \mot3 le prix \(P\) de \(\n\%\) on le multiplie par <span class="nowrap">\(1 \var \frac{\n}{100}=\cm\).</span><br>Si on \mot2 deux fois de \(\n\%\) il faut donc le multiplier par <span class="nowrap">\(\cm \times \cm =\cm^2 \finfeed2\).</span>}
\text{feedback=La bonne réponse est  \good.<br> \endfeed  }
