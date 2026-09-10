\title{Question 114 NS Vitesse moyenne}
\keywords{quizz}
\observation{Question du sujet zéro sujet-specifique-3_0.pdf publié sur EDUSCOL en juin 2025 }

\matrix{donnees=5,1,1,1,1.5,1.5
6,1,1,1.5,2,2
10,1.5,2,2,2.5,3
15,2,2,2.5,3,4
12,1.5,2,2,3,3
20,2,3,4,5,6
30,4,5,6,7,8}
\text{course=randomrow(\donnees)}
\integer{c=randint(2..6)}
\integer{v=\course[\c]*60/\course[1]}
\integer{bad1=\v-2}
\integer{bad2=\v+2}
\integer{bad3=\v+randitem(-4,4,4)}

\text{enonce=Un coureur parcourt \course[\c] km en \course[1] min. Quelle est sa vitesse moyenne&nbsp;&#63; }
\text{good=\v km/h}
\text{bads= \bad1 km/h,\bad2 km/h,\bad3 km/h}
\integer{coef=60/\course[1]}
\text{feedback=La bonne réponse était \good.<br> En effet&#44; 1h=60 min=\coef \({}\times{}\) \course[1] min  donc le coureur en une heure parcourt \course[\c]\({}\times{}\)\coef=\good. }
