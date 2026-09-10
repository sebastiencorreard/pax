\title{Question 452 NS Fréquence et effectif total}
\keywords{quizz,percents}
%% CD %%
%% MB modif 260115 %%%
\observation{Question du sujet zéro sujet-specifique-3.pdf publié sur EDUSCOL en juin 2025 }
\integer{total=100*randint(6..12)}
\integer{p=randomitem(4,5,8,10,20)} %% pourcentage
\integer{n=\p*\total/100}
\text{theme=randitem(étudient le latin,étudient le grec,font du théatre,suivent l'option musique)}

\text{enonce=Dans un lycée&#44; \(\n\) élèves \theme&#44; ce qui  représente \(\p \%\) du nombre
d’élèves inscrits dans ce lycée.<br> Le nombre d’élèves inscrits dans ce lycée est égal à&nbsp;&#58;}

\text{good=\(\total\)}
\integer{bad1=\p*\n/100}
\integer{bad2=\n*\n/(\p/2)}
\integer{bad3=\p*\n}
\text{bads=\(\bad1 \),\(\bad2\),\(\bad3\)} 
\real{pdeci=\p/100}
\text{feed=\(\p \%\) de l'effectif de total de ce lycée donne <span class="nowrap">\(\n\).</span> <br>L'effectif total est solution de l'équation&nbsp;&#58; <br>\(x \times \pdeci=\n\)<br> <span class="nowrap">\({}\Leftrightarrow x=\n  \div \pdeci\).</span>}

\text{feedback=La bonne réponse est "\good".<br> \feed}
