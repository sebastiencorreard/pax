\title{Question 550 T Evolution réciproque}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }
\text{cas=randomitem(1,-1,-1,-1)}

\if{\cas==-1}{
  \text{voc=diminue,augmentation}
  \integer{p1=randomitem(50,20,80)}
  \integer{p2=100*(100/(100-\p1)-1)}

  \integer{p3=\p1=50?150:2*\p1}
  \integer{p4=\p1=50?250:3*\p1}
  
  %%% feedback %%%%
  \real{c1=1-\p1/100}
  \real{d1=1/\c1}
  \real{c2=\d1-1}
  \real{psol=\c2*100}
  \text{feedback=La bonne réponse est \( \p2 \% \) puisque&nbsp;&#58; <ul> <li>Réduire un nombre de \(\p1 \% \)&#44; c'est le multiplier par \(1-0.\p1= \c1\)</li>  <li>Pour retrouver le prix initial il faut donc <b>diviser</b> par \(\c1 \) ou <b>multiplier</b> par \(\frac{1}{\c1}=\d1\)</li><li>Puisque \(\d1=1+\c2\)&#44; cela revient à faire une augmentation de \(\psol \%\)</li></ul>}
  }
  \if{\cas==1}{
  \text{voc=augmente,baisse}
  \integer{p1=randomitem(100,150)}
  \integer{p2=\p1==100?50:60}

  \integer{p3=2*\p1}
  \integer{p4=3*\p1}
  %%% feedback %%%%
  \real{c1=1+\p1/100}
  \real{p1b=\p1/100}
  \real{d1=1/\c1}
  \real{c2=1-\d1}
  \real{psol=\c2*100}
  \text{feedback=La bonne réponse est \( \p2 \% \) puisque&nbsp;&#58; <ul> <li>Augmenter un nombre de \(\p1 \% \)&#44; c'est le multiplier par \(1+\p1b= \c1\)</li><li>Pour retrouver le prix initial il faut donc <b>diviser</b> par \(\c1 \) ou <b>multiplier</b> par \(\frac{1}{\c1}=\d1\)</li><li>Puisque \(\d1=1-\c2\)&#44; cela revient à faire une baisse de \(\psol \%\)</li></ul>}
  }
  
\text{enonce=Un prix \voc[1] de <span class="nowrap">\(\p1 \% \).</span> Pour retrouver le prix initial&#44; il faut une \voc[2] de&nbsp;&#58;}

\text{good=\( \p2 \% \)}
\text{bads=\(\p1 \%\),\(\p3 \%\),\(\p4 \%\)}
