\title{Question 401 T Coeff. Mult. Evolution}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }

\text{pinit=250,500,200,400}
\text{pf=200,400,250,500}

\text{q=randint(1..items(\pinit))}
\text{pinit=\pinit[\q]}
\text{pf=\pf[\q]}
\real{p1=\pf/\pinit}
\real{p2=\pinit/\pf}
\real{p3=2-\p1}
\real{p4=\pinit/\pf}
\real{p4=\p4<1?\p4+1:\p4-1}

\text{verbe=\pinit>\pf?baissé:augmenté}
  
\text{enonce=Le prix d’une tablette a \verbe&#44; il est passé de \pinit euros à \pf euros.<br> Cela signifie qu'il a été multiplié par&nbsp;&#58;}

\text{good=\( \p1 \)}
\text{bads=\( \p2 \),\( \p3 \),\( \p4 \)}



\text{feedback=La bonne réponse est  \good  puisque le coefficient multiplicateur est \( \frac{\pf}{\pinit}={}\) \good. }
  
