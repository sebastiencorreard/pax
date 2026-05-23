\title{Question 0925 Lire une abscisse}
\keywords{mental_calculation,fraction,pbsolving,number_line}
\integer{a10=randint(2..5)}
\integer{b10=simplify(\a10+1)}
\integer{n=randint(3,4)}
\text{temp0925=simplify((\b10*\n+1)/\n)}
\text{rep=\temp0925}
\real{pas10=1/\n}
%%%
\real{n1=\a10-1}
\real{n2=\temp0925+1}
\integer{n3=\n+2} %%% nbre de |
%%%%% longueur axe
\real{n1=\a10-1/\n}
\real{n2=\temp0925+2/\n}
\text{fig10=draw(250,100
xrange \n1,\n2
yrange -30,5
arrow \n1,0,\n2,0,10,black
arrow \temp0925,-20,\temp0925,-5,10,black
segment \a10,-3,\a10,3,black
segment \b10,-3,\b10,3,black
parallel \a10,-2,\a10,2,\pas10,0,\n3,black
text black,\a10,-5,large, \a10
text black,\b10,-5,large, \b10
)}
\text{fig10=<div class="wimscenter"><img src="\fig10" alt=""></div>}
\text{enonce=\fig10 Réponse : }
\text{enonceb=}
%%% rq : pas possible de mettre un champ réponse intégré dans l'image à cause d'un bug sur la slib
\text{feedback=L'unité est découpée en \(\n\), les graduations sont donc des \(\frac{1}{\n}\).}
