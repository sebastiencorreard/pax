\title{Question 123 NS Masse de liquide }
\keywords{quizz,skill_calculate,conversion}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }
\matrix{liquide=d'huile,900
de miel,1400
de liquide vaisselle,1100
de sirop d'érable,1300
de kérosène,800
de sirop de grenadine,1200}

\text{l=randomrow(\liquide)}
\integer{p=randitem(randitem(250,750),randitem(200,400,600,800))}

\text{enonce=La masse d’un litre \l[1] est égale à \l[2] grammes.<br>
La masse de \p millilitres \l[1] est égale à&nbsp;&#58; }

\real{g1=\l[2]*\p/1000}
\real{g2=\g1/1000}
\integer{cg=randitem(1,2)}%%choix de l'unité de la bonne réponse : 1 en grammes, 2 en kg%%
\real{b1=\g1*10}
\real{b2=\g1/10}
\real{b3=\g1/100}

\text{good=(\cg==1)? \g1 g:\g2 kg}
%%%%%%%%%% 
\text{bad1=(\cg==1)? \g2 g:\g1 kg}
\text{bad2=(\cg==1)? \b3 kg:\b3 g}
\text{bad3=(\cg==1)? \b2 kg:\b1 g}
\text{bads=\bad1,\bad2,\bad3}

\text{feedback=La bonne réponse est \good. <br>En effet, la masse de 1000 mL d'\l[1] est égale à \l[2] g donc la masse de \p millilitres de liquide est égale à 
\l[2]&times\p/1000=\g1 g=\g2 kg. }
