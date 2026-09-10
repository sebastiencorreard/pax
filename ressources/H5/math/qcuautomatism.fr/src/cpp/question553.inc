\title{Question 553 NS Evolution inverse}
\keywords{quizz,percentage,percents}
\observation{Question du sujet zéro sujet-specifique-3_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{p=10*randint(1..8)}
\text{evol=shuffle(augmente,diminue)}
\real{p2=1-\p^2/10000}
 
\text{enonce=Un prix \evol[1] de \(\p \%\) puis \evol[2] de <span class="nowrap">\(\p \%\).</span> <br>Après ces deux évolutions&#44; on peut affirmer que&nbsp;&#58;}

\text{good=le prix est strictement inférieur au prix de départ}

\text{bad1=le prix est strictement supérieur au prix de départ}
\text{bad2=le prix est égal au prix de départ}
\text{bad3=on ne peut pas savoir car cela dépend du prix de départ}
\text{bads= \bad1, \bad2,\bad3}

\text{feedback=La bonne réponse est <b>\good</b>. <br>En effet le prix de départ est multiplié par \(\left( 1-\frac{\p}{100}\right)\left( 1+\frac{\p}{100}\right)=1-\left(\frac{\p}{100}\right)^2\)<br>\({}=\p2\) <br>et <span class="nowrap">\(\p2<1\).</span> }
