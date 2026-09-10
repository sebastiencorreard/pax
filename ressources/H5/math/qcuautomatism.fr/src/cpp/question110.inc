\title{Question 110 NS Ordre de grandeur }
\keywords{quizz,skill_calculate}
\observation{Question du sujet zéro sujet-specifique3.pdf publié sur EDUSCOL en juin 2025 }
\integer{puis=randomitem(2,3,4)}
\integer{n=randomitem(1,2,3,4,5)}
\integer{a=-\n+10^\puis}
\integer{b=\n+10^\puis}
%%% pour écriture 3 par 3
\text{a=slib(numeration/ecriturenombre \a,tex)}
\text{b=slib(numeration/ecriturenombre \b,tex)}
%%%%
\integer{p=10^(\puis)}
\text{enonce=Un ordre de grandeur de \(\a \times \b\) est &nbsp;&#58;}

\integer{goodint=2*\puis}
\text{good=\(10^{\goodint}\)}
\integer{bad1=\goodint-1}
\integer{bad2=\goodint+1}
\integer{bad3=\n^2}
\text{bad1=\(10^{\bad1}\)}
\text{bad2=\(10^{\bad2}\)} 
\text{bad3=\(\n\times 10^{\puis}\)} 
\text{bads= \bad1,\bad2,\bad3}

\text{feedback=La bonne réponse est \good. <br>En effet&#44; \(\a \times \b=(\p-\n)(\p+\n)=\p^2-\n^2\) dont un ordre de grandeur est \good. }


 
