\title{Question 101 Conversion minutes en heures}
\keywords{quizz,calculation,division}
\observation{Question du sujet zéro du DNB publié sur éduscol en décembre 2025 : sujet-zero-dnb-serie-generale-a-mathematiques }
%%% SC %%%
\integer{duree_h = randint(2..5)}
\integer{duree_min = \duree_h*60}

\text{enonce=Un film dure \duree_min min. Quelle est sa durée en heures&nbsp;&#63;}
\text{enonceb=}
\text{rep=\duree_h}
\text{typerep=numeric}
\text{feedalea=randomitem(Il faut diviser le nombre de minutes par 60 pour obtenir le nombre d'heures.,Rappel&nbsp;&#58; \(60\) minutes font une heure.)} 
\text{feedback=La bonne réponse est \(\duree_h\).<br>\feedalea}
