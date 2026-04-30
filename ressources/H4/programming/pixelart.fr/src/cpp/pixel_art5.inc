\title{Pixel Art 05}

\text{prob=Pixel Art et Python}
\text{lii=220px-Spacewar!-PDP-1-20070512.jpg}
\text{nomi=Spacewar !}

\text{enonce= En 1962, un groupe d'étudiants du MIT mené par Steve Russell programme un jeu
 nommé Spacewar! Deux vaisseaux spatiaux, chacun contrôlé par un joueur
 à l'aide de manettes créées pour l'occasion, sont capables de tirer des missiles.
 Au centre de l'écran, une étoile crée un champ gravitationnel et un danger
 supplémentaire. On considère qu'il s'agit du premier jeu vidéo largement diffusé et ayant
 eu une réelle influence. Techniquement, le jeu pesait 9 ko et tournait à 200 000
 instructions par seconde.
 <a href="https://fr.wikipedia.org/wiki/Histoire_du_jeu_vid%C3%A9o" target="_blank">Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=??}
\text{nll=??}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for}

\text{DD=pari(m=matrix(\nc,\nc,i,j,if(1==1,0));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}

\text{inst=Modifier cet algorithme pour qu'il effectue <b>sans erreur</b> la représentation donnée à droite
 ou ci-dessous.}
