\title{Question 121 NS Le plus grand }
\keywords{quizz,skill_calculate,fraction,decimals}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }
%%CD%%
AF : plus de cas aléatoires + feedback (donner l'écriture fractionnaire en 1/n )
\matrix{donnees=(1/5)^2,(1/2)^5,0.05,(1/3)^3,3,2,1,4,1/25,1/32,1/20,1/27
(1/5)^2,(1/2)^5,1/15,(1/3)^3,3,2,1,4,1/25,1/32,1/15,1/27
(1/6)^2,(1/2)^6,1/16,(1/3)^3,3,2,1,4,1/36,1/64,1/16,1/27
(1/6)^2,(1/2)^6,1/60,(1/3)^3,4,2,1,3,1/36,1/64,1/60,1/27
(1/3)^2,(1/2)^3,0.04,(1/4)^4,2,4,1,3,1/9,1/8,1/25,1/256
(1/3)^2,(1/2)^3,0.01,(1/4)^4,2,4,1,3,1/9,1/8,1/100,1/256
(1/5)^2,(1/2)^5,1/5,(1/4)^4,3,4,1,2,1/25,1/32,1/5,1/256
(1/5)^2,(1/2)^5,0.02,(1/4)^4,1,4,2,3,1/25,1/32,1/50,1/256
} %%% liste des nombres, pos du max, pos du min, mauvaises pos, écriture fractionnaire en 1/n des nombres%%
\integer{cas=randint(1..rows(\donnees))}
\text{d=\donnees[\cas;]}
\text{minmax=randomitem(grand,petit)}
\integer{k=\minmax issametext grand?5:6}
\text{dtxt=E,F,G,H}
\text{enonce=Voici quatre nombres&nbsp;&#58;<div class="wimscenter">\(E=\d[1]\)\(\;\)\(F=\d[2]\)\(\;\)\(G=\d[3])\(\;\)\(H=\d[4]\)</div>Le plus \minmax de ces quatre nombres est&nbsp;&#58; }

\text{good=\d[\k]}
%%%%%%%%%% 
\text{bad1=\d[11-\k]}
\text{bad2=\d[4+7]}
\text{bad3=\d[4+8]} 
\text{bads=\bad1,\bad2,\bad3}


\text{finfeed=En effet en utilisant l'écriture fractionnaire de chaque nombre on obtient&nbsp;&#58; <ul class="wims_nopuce"><li>\(E=\d[9]\)</li><li>\(F=\d[10]\)</li><li>\(G=\d[11]\)</li>
<li>\(H=\d[12]\)</li></ul>}
\text{feedback=La bonne réponse est \(\dtxt[\d[\k]]\). <br>\finfeed <br> On utilise ensuite le fait que si \(0<a<b\) alors \(\frac{1}{b}<\frac{1}{a}\).}
