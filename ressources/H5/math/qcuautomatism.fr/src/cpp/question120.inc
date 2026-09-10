\title{Question 120 NS Classer par ordre croissant }
\keywords{quizz,skill_calculate,fraction,decimals}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }
%%%MB
\text{rep120=E<F<G,E<G<F,F<E<G,G<F<E,F<G<E,G<E<F}
\integer{temp10=randomitem(18,19)}%%% plus petit que 1/5
\integer{temp11=randomitem(21,22)}%%% plus grand que 1/5
\integer{temp20=randomitem(21,22,23,24)}%%% plus petit que 1/4
\integer{temp21=randomitem(26,27)}%%% plus grand que 1/4
\integer{temp30=randomitem(48,49,49,49,48,24,19,21,22)}%%% plus petit que 1/2
\integer{temp31=randomitem(51,52,51,53)}%%% plus grand que 1/2
\matrix{donnees=1/5,\temp10/100,0.\temp11,3
1/5,0.\temp10,\temp11/100,3
1/5,0.\temp11,\temp10/100,6
1/5,\temp11/100,0.\temp10,6
1/5,22/100,0.21,2
1/4,\temp20/100,0.\temp21,3
1/4,0.\temp20,\temp21/100,3
1/4,0.\temp21,\temp20/100,6
1/4,\temp21/100,0.\temp20,6
1/4,19/100,0.21,5
1/4,26/100,0.24,6
1/2,4/10,0.2,4
1/2,\temp30/100,0.\temp31,3
1/2,0.\temp30,\temp31/100,3
1/2,\temp31/100,0.\temp30,6
1/2,0.\temp31,\temp30/100,6
1/2,0.51,47/100,6} %%% liste des nombres, pos de la bonne réponse dans reps
\integer{cas=randint(1..rows(\donnees))}
\text{d=\donnees[\cas;]}
\integer{k=\d[4]}
\if{\k=1}{\text{ksbis=2,randomitem(3,5),randomitem(4,6)}}
\if{\k=2}{\text{ksbis=1,randomitem(3,5),randomitem(4,6)}}
\if{\k=3}{\text{ksbis=5,randomitem(1,2),randomitem(4,6)}}
\if{\k=4}{\text{ksbis=6,randomitem(1,2),randomitem(3,5)}}
\if{\k=5}{\text{ksbis=3,randomitem(1,2),randomitem(4,6)}}
\if{\k=6}{\text{ksbis=4,randomitem(1,2),randomitem(3,5)}}

\text{enonce=Voici trois nombres&nbsp;&#58;<ul class="wims_nopuce"><li>\(E=\d[1]\)</li><li>\(F=\d[2]\)</li><li>\(G=\d[3]\)</li></ul> }


\text{temp=\rep120[\k]}
\text{good=\(\temp\)}
%%%%%%%%%%

\text{bad1=\(\rep120[\ksbis[1]]\)}
\text{bad2=\(\rep120[\ksbis[2]]\)}
\text{bad3=\(\rep120[\ksbis[3]]\)} 
\text{bads=\bad1,\bad2,\bad3}
%%% écrit decimale de E, F et G
\real{Edec=\d[1]}
\real{Fdec=\d[2]}
\real{Gdec=\d[3]}

\text{finfeed=En effet en utilisant l'écriture décimale de chaque nombre on obtient&nbsp;&#58; <ul class="wims_nopuce"><li>\(E=\Edec\)</li><li>\(F=\Fdec\)</li><li>\(G=\Gdec\)</li></ul>}
\text{feedback=La bonne réponse est \good. <br>\finfeed }


 
