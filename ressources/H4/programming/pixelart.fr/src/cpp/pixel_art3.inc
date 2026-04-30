\title{Pixel Art 03}

\text{prob=Pixel Art et Python}
\text{lii=Dame.jpg }
\text{nomi=Jeux de Dames}

\text{enonce=Les premiers jeux sur ordinateur reliés à un écran font leur apparition en
 1952 via des recherches académiques : un jeu de dames par Christopher Strachey sur
 Ferranti Mark I et OXO.  <a href=" https://fr.wikipedia.org/wiki/Programme_de_dames_de_Christopher_Strachey" target="_blank">Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=1}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\integer{ncmin=randint(1..8)}
\integer{ncmax=randint(10..\nc)}

\text{keytest=for&if}
\text{instruction_code=instruction=[if 7&lt;=k&lt;=14 :]}

\text{DD=pari(m=matrix(1,\nc,i,j,if(\ncmin<=j && j<=\ncmax,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\if{\ncmin<=\kj and \kj<=\ncmax}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,0.5],{color:'black'}); to \mjsx)}
}}

\text{inst=Modifier cet algorithme avec l'instruction conditionnelle <code>if 7&lt;=k&lt;=14 :</code>
 pour qu'il effectue <b>sans erreur</b> la représentation donnée à droite ou ci-dessous. La variable \(k\) est à modifier judicieusement.}
