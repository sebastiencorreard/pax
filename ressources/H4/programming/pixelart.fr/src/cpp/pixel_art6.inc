\title{Pixel Art 06}

\text{prob=Pixel Art et Python}
\text{lii=Space_Travel_Screenshot.png}
\text{nomi=Space Travel !}

\text{enonce=À partir de 1965, Ken Thompson développe un système d'exploitation basé sur Multics
 pour le compte de la société AT&T, sur la plate-forme GE-635. Sa motivation première
 était de faire tourner un jeu de sa conception nommé Space Travel, une simulation du
 système solaire. Bien que le jeu n'ait jamais été commercialisé (il coûte d'ailleurs 75 $
 par utilisation pour louer l'ordinateur GE-635) et que la société AT&T en ait finalement
 stoppé le financement en 1969, il est à l'origine de la création d'Unix.
  <a href="https://fr.wikipedia.org/wiki/Space_Travel" target="_blank" >Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=\nc}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for}

\integer{cc=randint(2..\nc)}
\integer{alt=randint(1..2)}
\text{var=(\alt==1)?j:i}
\text{ex=(\alt==1)?j:3}
\text{ex1=(\alt==1)?2:i}
\text{zr=(\alt==1)?\cc:1000}
\text{zrr=(\alt==2)?\cc:1000}
text{zr=(\alt==1)?\kj==\cc:\kk==\cc}
\text{DD=pari(m=matrix(\nc,\nc,i,j,if(\var==\cc,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\if{\kj==\zr or \kk==\zrr}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme en fixant la valeur de \(i\) ou \(j\) comme indiqué dans l'exemple <code>mat[\ex1][\ex]=0</code> pour qu'il effectue
  <b>sans erreur</b> la représentation donnée à droite
  ou ci-dessous.}
