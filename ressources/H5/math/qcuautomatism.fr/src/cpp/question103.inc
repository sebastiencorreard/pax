\title{Question 103 T Conversion temps}
\keywords{quizz,conversion,time}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{a=randomitem(60,60,120)}
\text{b=15}
\integer{quest=\a+\b}
\real{h=\quest/60}
\real{hbad1=floor(\h)+\b/100}
\real{hbad2=(\a-\b)/60}
\real{hbad3=floor(\h)+randomitem(-0.4,0.4)}
\text{enonce=Une durée de \quest minutes correspond à&nbsp;&#58;}
\text{good=\h>1?\h heures:\h heure}
\text{bad1=\hbad1>1?\hbad1 heures:\hbad1 heure}
\text{bad2=\hbad2>1?\hbad2 heures:\hbad2 heure}
\text{bad3=\hbad3>1?\hbad3 heures:\hbad3 heure}
\text{bads=\bad1,\bad2,\bad3}

\text{feedback=La bonne réponse était \good. <br>Rappel <br>60 minutes = 1 heure <br>et 15 minutes = 0.25 heure}
