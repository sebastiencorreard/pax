\title{Question 111 NS Vitesse }
\keywords{quizz,skill_calculate}
\observation{Question du sujet zéro sujet-specifique3.pdf publié sur EDUSCOL en juin 2025 }
\matrix{donnees=1,5,5,6,10
2,10,10,12,12
3,10,12,15,20
4,15,15,20,20}
\text{course=randomrows(\donnees)}
\integer{choix=randint(2..4)}
\integer{distance=\course[1]}
\integer{temps=\course[\choix]}

\text{enonce=Une athlète parcourt \distance km en \temps min. Quelle est sa vitesse moyenne&nbsp;&#63; }

\integer{good=\distance*60/\temps}
\text{good=\(\good\)}
\integer{bad1=\good+4}
\integer{bad2=\good+2}
\integer{bad3=\good+randitem(-2,6)}
\text{bads= \(\bad1\),\(\bad2\),\(\bad3\)}
\integer{c=60/\temps}

\text{feedback=La bonne réponse est \good. En effet, 1h équivaut à 60 min et \(60=\temps \times \c\) donc la vitesse moyenne est \(\distance \times \c=\good\) km.h<sup>-1</sup>
}


 
