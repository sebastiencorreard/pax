\title{Pixel Art 08}

\text{prob=Pixel Art et Python}
\text{lii=Galaxy_Game_1971_first_arcade_game.jpg}
\text{nomi=Galaxy Game !}

\text{enonce= En 1971, Bill Pits et Hugh Tuck sortent le tout premier jeu d'arcade:
 Galaxy Game. Il s'agit en fait du jeu Spacewars qui a été reprogrammé sur des
 ordinateurs PDP-11 en borne d'arcade, dans le but de le commercialiser.
 <a href="https://fr.wikipedia.org/wiki/Galaxy_Game" target="_blank" >Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=\nc}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for}

\integer{cc=randint(2..\nc-1)}
\integer{scc=randint(2..\nc-1)}
\text{DD=pari(m=matrix(\nc,\nc,i,j,if(j==\cc || i==\scc,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\if{\kj==\cc or \kk==\scc}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme pour qu'il effectue <b>sans erreur</b> la représentation
 donnée à droite ou ci-dessous.}
