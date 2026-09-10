\title{Question 551 T Prix après évolution}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{n=randint(2..9)}
\integer{pinit=\n*100}
\integer{p1=randint(1..9)*10}
\real{p1decim=\p1/100}

\text{evol=randomitem(+,-)}
\real{cmdecim=1\evol\p1decim}
\integer{pfinal=\pinit*(1\evol\p1decim)}
\text{verbe=\evol issametext -?baisse:augmente}
  
\text{enonce=Un article coûte \pinit euros. Le prix \verbe de de <span class="nowrap">\( \p1 \%\).</span><br> Le nouveau prix est&nbsp;&#58;}

\text{good=\pfinal euros}
\text{badevol=\evol issametext -?+:-}

\real{cmdecimbad=1 \badevol \p1decim}

\integer{bad1=\pinit\evol\p1}
\integer{bad2=\pinit*(1\badevol\p1/100)}
\integer{temp3=ceil(\pfinal/100)*100}
\integer{bad3=\temp3=\pfinal?\pfinal+100:\temp3}
\text{bads= \bad1 euros, \bad2 euros,\bad3 euros }
\text{mots=\evol issametext +?l'augmentation:la baisse}
\text{mots2=\evol issametext +?l'addition:la soustraction}
\integer{temp25=\p1*\n}
\text{endfeed=<br>On peut remarquer que \(\pinit=100\times \n\) ainsi \mots sera de <span class="nowrap">\(\p1 \times \n=\temp25\).</span> Il reste à faire \mots2 <span class="nowrap">\(\pinit\evol\temp25\).</span>}
\text{feedback=La bonne réponse est  \good. \endfeed  }
