\title{Question 0630 Aire}
\keywords{geometry,area}

\integer{x1=randint(0..3)}
\integer{y1=randint(1..3)}
\integer{x2=randint(4..6)}
\integer{y2=randint(4,5)}

\integer{choixua=randint(1,2,3)}%% 1 -> 1/4 carreau, 21 -> 1/2 carreau, 3 -> 2 carreaux %%%

\if{\choixua=1}{\text{trait1=5,6,5.5,5.5,black}
\text{trait2=6,6,5.5,5.5,black}
\text{polyg=5,5,6,5,5.5,5.5}
\real{rep=(\x2-\x1)*(\y2-\y1)*4}
\text{feedback=Une case a une surface de 4 unités d'aire.}
}

\if{\choixua=2}{\text{trait1=0,0,0,0,grey}
\text{trait2=0,0,0,0,grey}
\text{polyg=5,5,6,5,5,6}
\real{rep=(\x2-\x1)*(\y2-\y1)*2}
\text{feedback=Une case a une surface de 2 unités d'aire.}
}

\if{\choixua=3}{\text{trait1=0,0,0,0,grey}
\text{trait2=0,0,0,0,grey}
\text{polyg=4,5,6,5,6,6,4,6}
\real{rep=(\x2-\x1)*(\y2-\y1)/2}
\text{feedback=Une case a une surface de 0,5 unités d'aire.}
}

%%% modif MB séparation du draw et du contenu %%%
\text{instrdession=xrange -0.2,6.2
yrange -0.2,6.2
parallel 0,0,0,6,1,0,7,grey
parallel 0,0,6,0,0,1,7,grey
fpoly blue,\polyg
segment \trait1
segment \trait2
linewidth 3
segment \x1,\y1,\x2,\y1,black
segment \x1,\y1,\x1,\y2,black
segment \x2,\y1,\x2,\y2,black
segment \x2,\y2,\x1,\y2,black}
\text{dessin=draw(250,250
\instrdession)}
%%% fin modif MB %%%%%
\text{fig30=<img src="\dessin" alt="">}


\text{enonce=<table><tr><td>\fig30</td></tr><tr><td> Quelle est l'aire du rectangle noir &#63; <br> L'unité est l'aire de la figure bleue. </td></tr></table> }
\text{enonceb=unités d'aire}
