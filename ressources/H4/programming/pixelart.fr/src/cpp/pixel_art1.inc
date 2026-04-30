\title{Pixel Art 01}

\text{prob=Pixel Art et Python}
\text{lii=Bombe-rebuild.jpg}
\text{nomi=Réplique de la Bombe}

\text{enonce=Pendant la seconde Guerre mondiale, les premiers ordinateurs analogiques
 font leur apparition afin de contribuer à l'effort de guerre. Selon plusieurs historiens,
 le travail du mathématicien Alan Turing pour déchiffrer le code des transmissions allemandes
  permet de raccourcir la Seconde Guerre mondiale de deux ans.
 <a href="https://fr.wikipedia.org/wiki/Alan_Turing" target="_blank" >Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=1}
\text{nll=\nc}
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
