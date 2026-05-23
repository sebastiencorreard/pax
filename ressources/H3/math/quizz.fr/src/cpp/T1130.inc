\title{Question T1130 Aire}
\keywords{mental_calculation,area,circle,rectangles}
%%%%%%%%%%%%%% Question 30 %%%%%%%%%%%%

\integer{taille30=200}
\integer{c30=2*randint(2..5)}
\integer{r30=\c30/2}
\integer{\sqc30=\c30^2}
\integer{\sqr30=\r30^2}
\text{temp30=\sqc30-\sqr30,pi}
\integer{diampx=6*\taille30/8}
\text{fig30=draw(\taille30,\taille30
xrange -1,7
yrange -1,7
polygon black,0,0,6,0,6,6,0,6
hatchfill 3,3,10,10,black

fcircle 3,3,\diampx,white
circle 3,3,\diampx,black
crosshair 3,3,5,black
text black,3.5,3.5,giant,O
text black,-0.5,6.5,giant,A
text black,6.5,6.5,giant,B
text black,6.5,-0.2,giant,C
text black,-0.5,-0.2,giant,D
)
}

\text{fig30=<img src="\fig30" alt="">}

\text{enonce=Sur la figure ci-dessous, le disque blanc de centre O est inscrit dans le carré ABCD de côté \(\c30\) cm.<br>Exprimer en fonction de \(pi)&#44; l'aire de la partie hachurée en \(cm^2\) :<br> }
\text{enonceb= cm² <br>\fig30<div class="wims_instruction">Saisir 3pi si la réponse est \(3\pi\).</div>}
\text{rep=wims(replace internal ,pi by *pi in \temp30)}
\text{feedback=L'aire du rectangle est égale à \(\c30^2\) auquel il faut enlever l'aire du disque de rayon \(\c30 \div 2\).<br> L'aire d'un disque de rayon \(r\) est \(\pi r^2\).}
\integer{size=8}
