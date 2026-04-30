\title{Pixel Art 10 +}

\text{prob=Pixel Art et Python}
\text{lii=Avcs2600_set.jpg}
\text{nomi=Console Atari}

\text{enonce=En 1977, Atari lance sa console Video Computer System, renommée par la
 suite Atari 2600. En 1979, la société Activision est créée par un groupe de
 programmeurs d'Atari mécontents. Il s'agit du premier développeur tiers de jeux vidéo.
 <a href="https://fr.wikipedia.org/wiki/Atari_2600" target="_blank" >Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=\nc}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for&if&or}
\text{instruction_code=instruction=[i+j==?? ,i-j==??,or ,and ]}

\integer{alt=randint(-4..4)}
\integer{altt=randint(-4..4)}

\text{DD=pari(m=matrix(\nc,\nc,i,j,if((i-j==\alt) || (i+j==\nc+\altt),0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\integer{s=-\kj+\kk}
\integer{ss=\kj+\kk}
\integer{sss=\nc+\altt}
\if{(\s==\alt) or (\ss==\sss)}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme en ecrivant des égalités entre les variables couplées avec
 les opérateurs and et or afin d'écrire une instruction de la forme :
<code>if i+j==0 and i-j==0 :</code>.
 La représentation donnée à droite ou ci-dessous est à effectuer.}
