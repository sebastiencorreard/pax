\title{Question 0606 Repérage}
\keywords{coordinates,mental_calculation}
%%% MB %%%
\integer{a2=randint(5..8)}
\integer{a20=\a2+1}
\integer{a21=\a20+1}
\integer{b2=simplify(\a2+0.5)}
\real{temp20=0.1*randint(2,3,4,6,7,8,9)+randint(1,0)}
\real{rep=\a2+\temp20}
%%%%%jusqu'où graduer ?
\integer{par1=3}
\integer{par2=6}
\integer{par3=30}
%%%
\real{n21=\a2-0.5}
\real{n22=\rep+1}
\integer{align2=-2}
\integer{temp2=0.2}
\integer{x2=simplify(\a2-\temp2)}
\integer{y2=simplify(\a20-\temp2)}
\integer{z2=simplify(\a21-\temp2)}

\integer{rangexMax=\a2+3.25}
%%%%% longueur axe
\text{fig2=draw(350,100
xrange \n21,\rangexMax
yrange -30,15
arrow \n21,0,\rangexMax,0,10,black
arrow \rep,-20,\rep,-5,10,black
segment \a2,-3,\a2,3,black

parallel \a2,-2,\a2,10,1,0,\par1,black
parallel \a2,-2,\a2,6,0.5,0,\par2,black
parallel \a2,-2,\a2,2,0.1,0,\par3,black
text black,\x2,-5,large, \a2
text black,\y2,-5,large, \a20
text black,\z2,-5,large, \a21

)}
\text{fig2=<div class="wimscenter"><img src="\fig2" alt=""></div>}
\text{enonce=\fig2 Complète }
\text{enonceb=}
%%% rq : pas possible de mettre un champ réponse intégré dans l'image à cause d'un bug sur la slib
\text{feedback=Les plus petites graduations sont des dixièmes.}
