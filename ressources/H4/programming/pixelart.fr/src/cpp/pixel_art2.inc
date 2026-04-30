\title{Pixel Art 02}

\text{prob=Pixel Art et Python}
\text{lii=morpion.jpg}
\text{nomi=Tic-tac-toe ou Morpion}

\text{enonce=En 1950, le premier jeu connu Bertie the Brain est développé par Josef
 Kates dans le cadre de l'exposition nationale canadienne. La machine permet au public
 de jouer au morpion "Tic-tac-toe" face à une intelligence artificielle, avec différents
 niveaux de difficulté.
 <a href="https://fr.wikipedia.org/wiki/Tic-tac-toe" target="_blank">Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=??}
\text{nll=??}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for}

\text{DD=pari(m=matrix(1,\nc,i,j,0);)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,0.5],{color:'black'}); to \mjsx)}
}

\text{inst=Modifier cet algorithme pour qu'il effectue <b>sans erreur</b> la représentation donnée à droite ou ci-dessous.}
