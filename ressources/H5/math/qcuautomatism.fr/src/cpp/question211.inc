\title{Question 211 NS Développer un carré}
\keywords{quizz,literal_calculation,trinomial}
\observation{Question du sujet zéro sujet-specialite-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{x=randomitem(x,n,t)}
\text{p=randomitem(3,4,3,5,3,2)}
\function{f=(x - \p)^2}
\integer{af=1}
\integer{bf=2*\p}
\integer{cf=\p^2}

\text{enonce=L’expression développée de \(( \x - \p)^2\) est&nbsp;&#58;  }

\text{good=\(\x^2-\bf*\x+\cf\)}
%%% 
\text{bad1=\(\x^2+\cf\)}
%%%
\text{bad2=\(\x^2-\cf\)}
%%%
\text{bad3=randomitem(\(\x^2-\bf*\x-\cf\),\(\x^2+\bf*\x-\cf\))}
%%%
\text{bads=\bad1,\bad2,\bad3}

\text{feedback=La bonne réponse est \good. <ul class="wims_nopuce"><li> Soit on développe <span class="nowrap">\((\x - \p)(\x - \p)\).</span><i>(double distributivité)</i></li><li>Soit on utilise l'identité remarquable <span class="nowrap">\((\x - \p)^2=\x^2-2\times\p\times \x+\p^2\).</span></li></ul>  }
