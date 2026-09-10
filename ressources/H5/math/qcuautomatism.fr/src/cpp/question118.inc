\title{Question 118 NS Conversion de durée}
\keywords{quizz,time,conversion}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }

\matrix{duree=75,5/4,3/4,0.25,1.5
80,4/3,0.8,1.2,5/8
90,1.5,1.3,0.9,2/3
120,2,1.2,1.6,1.12
100,5/3,2,1.4,4/3
105,7/4,1.45,9/4,1.05
135,2.25,1.35,2.15,11/4
140,7/3,8/3,1.4,2.2
150,2.5,1.5,11/6,7/6
160,8/3,1.6,2.4,7/3
200,10/3,2,4/3,3.2}


\text{temps=randomrow(\duree)}
\text{unite=(\temps[1]>=120)? heures:heure}
\integer{e=floor(\temps[1]/60)}
\integer{reste=\temps[1]-60*\e}


\text{enonce=Une durée de \temps[1] minutes correspond à&nbsp;&#58; }
\text{good=\(\temps[2]\) \unite}
\text{bads=\(\temps[3]\) \unite,\(\temps[4]\) \unite,\(\temps[5]\) \unite}

\text{feedback=La bonne réponse est \good.<br> En effet&#44; 1h=60 min donc \temps[1] minutes correspondent à \e \unite et \reste minutes.}
