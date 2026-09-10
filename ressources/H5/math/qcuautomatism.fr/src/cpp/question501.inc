\title{Question 501 S Interpréter un coeff. mult.}
\keywords{quizz,percentage,percents,decimals}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
\real{evol=randomitem(-1,1)*randomitem(2.5,3.5,1.5,4.5,0.2,0.3)}
\text{verbevol=\evol<0?baisse:hausse}
\text{badverbevol=\evol>0?baisse:hausse}
\integer{p1=randint(1..9)*10}
\real{p1decim=\p1/100}

\real{cmdecim=1+\evol/100}
\real{evolabs=abs(\evol)}
  
\text{enonce=Le prix d’un article est multiplié par <span class="nowrap">\(\cmdecim\).</span><br>Cela signifie que le prix de cet article a connu&nbsp;&#58;}

\text{good=une \verbevol de \(\evolabs\%\)}
\real{badevolabs=10*\evolabs}
\text{bad1=une \verbevol de \(\badevolabs\%\)}
\text{bad2=une \badverbevol de \(\evolabs\%\)}
\text{bad3=une \badverbevol de \(\badevolabs\%\)}

\text{bads=\bad1,\bad2,\bad3 }
\text{sgn1=\cmdecim<1?&lt;:&gt;}
\text{calcul1=\cmdecim<1?1-\cmdecim:\cmdecim-1}
\real{result1=\cmdecim<1?1-\cmdecim:\cmdecim-1}
\real{pourcent1=\result1*100}
\text{endfeed=<br>Puisque \(\cmdecim \sgn1 1\) c'est une \verbevol.<br>Calcul du taux&nbsp;&#58; \(\calcul1=\result1\) soit \(\pourcent1 \%\)}

\text{feedback=La bonne réponse est  \good. \endfeed  }
  
