\title{Question 208 S Développer un carré}
\keywords{quizz,literal_calculation,trinomial}
\observation{Question du sujet zéro sujet-specialite-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{x=randomitem(x,n,t)}
\text{m=2,4,10}
\text{p=0.5,0.5,randomitem(0.4,0.6)}
\integer{k=randomitem(1,2)}
\integer{m=\m[\k]}
\real{p=\p[\k]}
\function{f=(\m*x + \p)^2}
\integer{af=\m^2}
\integer{bf=2*\m*\p}
\real{cf=\p^2}

\text{enonce=L’expression développée de \((\m \x + \p)^2\) est&nbsp;&#58;  }

\text{good=\(\af*\x^2+\bf*\x+\cf\)}
%%% 
\integer{bf1=\m*\p}
\text{bad1=\(\af*\x^2+\bf1*\x+\cf\)}
%%%
\integer{bf2=2*\af}
\text{bad2=\(\af*\x^2+\bf2*\x+\cf\)}
%%%
\integer{cf1=2*\p}
\text{bad3=\(\af*\x^2+\bf*\x+\cf1\)}
%%%
\text{bads=\bad1,\bad2,\bad3}

\text{feedback=La bonne réponse est \good. <ul class="wims_nopuce"><li> Soit on développe <span class="nowrap">\((\m \x + \p)(\m \x + \p)\).</span><i>(double distributivité)</i></li><li>Soit on utilise l'identité remarquable <span class="nowrap">\((\m \x + \p)^2=(\m \x)^2+2\times\p\times\m\times \x+\p^2\).</span></li></ul> On rappelle que&nbsp;&#58;<br> \((\m \x)^2=\m \x \times \m \x\)<br>\({}=\m^2 \x^2\)<br><span class="nowrap">\({}=\af \x^2\).</span> }
