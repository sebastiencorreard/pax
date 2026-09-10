\title{Question 101 T Masse et forme d'écriture}
\keywords{quizz,scientific_notation}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }
%%paramètres%%
\integer{p=randint(20..25)}
\real{x=randint(2100..8700)/1000}
\integer{pa=\p+1}
\integer{pb=\pa+1}
\integer{pc=\pb+1}
\text{puiss=\p,\pa,\pb,\pc}
\real{y=\x-randint(30..100)/1000}
\real{z=\x+randint(50..160)/1000}
\integer{ect=randitem(-1,1)}
\real{t=\x+\ect*randint(500..1200)/1000}
\text{ch=wims(shuffle 1,2,3,4)}
\real{xg=10^\ch[1]*\x}
\integer{pg=\p-\ch[1]}
\text{masseg=\xg \times 10^{\pg}}
\real{yb=10^\ch[2]*\y}
\integer{pyb=\p-\ch[2]}
\text{masseb1=\yb \times 10^{\pyb}}
\real{zb=10^\ch[3]*\z}
\integer{pzb=\p-\ch[3]-1}
\text{masseb2=\zb \times 10^{\pzb}}
\real{tb=10^\ch[4]*\t}
\integer{ptb=(\ect>0)? \p-\ch[4]-1:\p-\ch[4]}
\text{masseb3=\tb \times 10^{\ptb}}
\text{masse=wims(shuffle \masseg,\masseb1,\masseb2,\masseb3)}
\text{astre=Nur,Efros,Ramatis,Rill,Acamar,Aldea,Annaj,Bajor,Catulla,Lacerta,Acteon,Svoboda,Thalia,Lusus}
%%énoncé%%
\text{enonce=On donne la masse de 4 astres&nbsp;&#58;<ul><li> \astre[1] a une masse de \(\masse[1]\) kg </li><li> \astre[2] a une masse de \(\masse[2]\) kg </li><li>\astre[3] a une masse de \(\masse[3]\) kg </li><li> \astre[4] a une masse de \(\masse[4]\) kg. </li></ul>Lequel de ces astres a la plus grande masse&nbsp;&#63;}

%%Bonne réponse (proposition  good, lettre donnée par \g) et mauvaises réponses (\bads)%%
\integer{g=position(\masseg,\masse)}
\text{b=}
\for{k=1 to 4}{\if{\k==\g}{}{\text{b=\b,\k}}}
\text{b=\b[2..4]}
\text{good=\astre[\g]}
\text{bads=\astre[\b[1]],\astre[\b[2]],\astre[\b[3]]}
\text{feedback=La bonne réponse est \astre[\g].<br> Il suffit d'écrire les masses en écriture scientifique.}
