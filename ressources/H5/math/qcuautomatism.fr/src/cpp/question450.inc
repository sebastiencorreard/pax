\title{Question 450 S Proportion de proportions}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-specialite-2.pdf publié sur EDUSCOL en juin 2025 }
\text{prop=le quart,la moitié,le dixième,le cinquième}
\text{cm=0.25,0.50,0.10,0.20}
\text{pourcent=25,50,10,20}
\text{temp=shuffle(4)}
\text{prop1=\prop[\temp[1]]}  
\text{prop2=\prop[\temp[2]]}
\text{enonce=Dans un lycée&#44; \prop1 des élèves sont internes&#44; parmi eux&#44; \prop2 sont des filles.<br>La proportion des filles internes par rapport à l’ensemble des élèves du lycée est égale à&nbsp;&#58;}

\real{good=\cm[\temp[1]]*\cm[\temp[2]]*100}
\text{good=\good &#37;}
\text{temp0=randomitem(4,7,8)}
\text{bads=\pourcent[\temp[1]] &#37;,\pourcent[\temp[2]]  &#37;,\temp0 &#37;}



\text{feedback=La bonne réponse est  \good  puisque le coefficient multiplicateur est égal à <span class="nowrap">\( \cm[\temp[1]]\times\cm[\temp[2]]\).</span> }
  
