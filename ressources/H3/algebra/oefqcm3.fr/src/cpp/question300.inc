\title{Question 300 Médiane}
\keywords{quizz,median}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
%%% MB 
\integer{q1=randomitem(4,5,6,7,8,8,7)}
\integer{q2=\q1+randomitem(1,2,2)}
\integer{q3=\q2+randomitem(3,4)}%% mediane
\integer{q4=\q3+randomitem(3,4)}
\integer{q5=\q4+randomitem(3,4)}
\matrix{donnees=\q2 &#59; \q3 &#59; \q1 &#59; \q5 &#59; \q4
\q2 &#59; \q3 &#59; \q4 &#59; \q5 &#59; \q1
\q2 &#59; \q1 &#59; \q5 &#59; \q3 &#59; \q4
\q2 &#59; \q5 &#59; \q1 &#59; \q3 &#59; \q4
\q3 &#59; \q2 &#59; \q1 &#59; \q5 &#59; \q4
}
\text{d=randomrow(\donnees)}
\text{enonce=Les notes obtenues par un élève sont \d. <br>Que vaut la médiane de cette série de notes &nbsp;&#63;}
\text{enonceb=}
\text{rep=\q3}
\text{typerep=numeric}

\text{feedback=La bonne réponse est&nbsp;&#58; <span class="nowrap">\(\rep\).</span> <br>En effet&nbsp;&#58;
<ul class="wims_nopuce"><li> il faut classer
les cinq notes par ordre croissant (\q1 ; \q2 ; \q3 ; \q4 ; \q5)</li><li>la médiane est la troisième valeur.</li></ul>}
