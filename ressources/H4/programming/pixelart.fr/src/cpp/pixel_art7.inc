\title{Pixel Art 07}

\text{prob=Pixel Art et Python}
\text{lii=BrownBox.jpg}
\text{nomi=Ancêtre de la console}

\text{prob=Pixel Art et Python}
\text{enonce=En 1966, Ralph Baer (alors ingénieur chez Sanders Associates) crée la
 brown box, boîtier se connectant aux téléviseurs ordinaires (une implémentation de son
 idée première de 1951) et pouvant à terme être vendu une vingtaine de dollars.
  <a href="https://fr.wikipedia.org/wiki/Histoire_du_jeu_vid%C3%A9o" target="_blank" >Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=\nc}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for}

\integer{cc=randint(2..\nc-1)}
\integer{ccc=randint(2..\nc-1)}
\text{DD=pari(m=matrix(\nc,\nc,i,j,if(i==\cc && j==\ccc,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\if{\kj==\ccc and \kk==\cc}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme en fixant la valeur de \(i\) et \(j\) pour qu'il
 effectue <b>sans erreur</b> la représentation donnée à droite ou ci-dessous.}
