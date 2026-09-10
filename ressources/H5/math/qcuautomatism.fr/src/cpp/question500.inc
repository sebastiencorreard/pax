\title{Question 500 T Calcul nouveau prix}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{pinit=randint(11..17)*10}
\integer{p1=randint(1..9)*10}
\real{p1decim=\p1/100}

\text{evol=randomitem(+,-)}

\real{cmdecim=1\evol\p1decim}
\text{verbe=\evol issametext -?baissé:augmenté}
  
\text{enonce=Un sac coûte \pinit euros. Il a \verbe de <span class="nowrap">\( \p1 \%\).</span><br> Le nouveau prix est&nbsp;&#58;}

\text{good=randomitem(\( \pinit \times \cmdecim \),\(\pinit \times \left(1 \evol \frac{\p1}{100} \right) \))}
\text{badevol=\evol issametext -?+:-}

\text{evolbis=evol issametext -?-:}
\real{cmdecimbad=1 \badevol \p1decim}
\text{bad22=\good issametext \( \pinit \times \cmdecim \)?\(\pinit \times \left(1 \badevol \frac{\p1}{100}\right) \):\( \pinit \times \cmdecimbad \)}
\text{bads=\(\pinit \times \p1decim \),\(\pinit \times \left(\evolbis \frac{\p1}{100} \right) \) ,\bad22 }

\text{endfeed=\good issametext \( \pinit \times \cmdecim \)?<br>Le calcul à produire est \(\pinit \times \left(1 \evol \frac{\p1}{100}\right) \) <br>\({}=\pinit \times \left(1 \evol \p1decim\right)\) <br><span class="nowrap">\({}=\pinit \times \cmdecim\).</span>:}
\text{feedback=La bonne réponse est  \good. <br>\endfeed  }
  
