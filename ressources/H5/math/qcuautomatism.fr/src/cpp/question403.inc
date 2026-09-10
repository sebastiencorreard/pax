\title{Question 403 T Prix après évolution}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-specialité-2_0.pdf publié sur EDUSCOL en juin 2025 }

\text{pinit=300,500,200,400}
\text{pourcentages=20,30,40,40}
\text{q=randint(1..items(\pinit))}
\text{pinit=\pinit[\q]}
\text{p=\pourcentages[\q]}
\text{evol=randomitem(+,-)}

\text{verbe=\evol issametext -?diminue:augmente}
\text{mot1=\evol issametext -?diminution:augmentation}
  
\text{enonce=Une tablette coûte \pinit euros. <br>Son prix \verbe de <span class="nowrap">\(\p \%\).</span><br> Le prix après cette \mot1 est&nbsp;&#58;}
\integer{p1=\pinit*(1 \evol \p/100)}
\integer{bad1=\pinit \evol \p}
\integer{bad2=\pinit \evol \p/10}
\integer{bad3=\pinit \evol \pinit/100*\p/10}

\text{good=\( \p1 \) euros}
\text{bads=\( \bad1 \) euros,\(\bad2 \) euros,\( \bad3 \) euros}
%%% feed %%
\real{pdec=\p/100}
\integer{evolbrut=\pinit*\p/100}

\text{feedback=La bonne réponse est  \good  puisque le coefficient multiplicateur est <span class="nowrap">\( 1 \evol \frac{\p}{100}=1 \evol \pdec\).</span><br> Le calcul à produire est donc <span class="nowrap">\(\pinit\evol\pdec\times\pinit=\pinit\evol\evolbrut\).</span> }
  
