\title{Question 556 S Comparer les prix après évolutions bis}
\keywords{quizz,percentage,percents,decimals}
\observation{Question du sujet zéro sujet-specialite-2.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randomitem(40,50,50,60)}
\real{ndec=\n/100}
\real{ndec2=\ndec^2}
\text{mots=shuffle(réduction,augmentation)}
\real{cmfinal=(1+\n/100)*(1-\n/100)}
\real{poufinal=\cmfinal <1? (1-\cmfinal)*100:(\cmfinal-1)*100}

  
\text{enonce=Une \mots[1] de \(\n \%\) suivie d’une \mots[2] de \(\n \%\) équivaut à&nbsp;&#58;}

\text{good=Une baisse de \(\poufinal \%\)}
\text{bad1=Une augmentation de \(\poufinal \%\)}
\text{bad2=Une \mots[1] de \(\n \%\)}
\real{poufinalbad=\cmfinal*100}
\text{bad3=Une \mots[2] de \(\poufinalbad \%\)}
\text{bads=\bad1,\bad2,\bad3 }
\text{sgnevl=\mots[1] issametext réduction?-,+:+,-}
\text{endfeed=<br>Le coefficient multiplicateur après les deux évolutions se calcule ainsi \((1\sgnevl[1]\ndec)(1\sgnevl[2]\ndec)\)<br>On reconnait \((1-\ndec)(1+\ndec)=1-\ndec^2 = 1-\ndec2\) qui est plus petit que \(1). <br>C'est donc une baisse de <span class="nowrap">\(\poufinal\%\).</span> }

\text{feedback=La bonne réponse est  <b>" \good "</b>. \endfeed  }
  
