\title{Pixel Art 10}

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

\text{keytest=for&if}
\text{instruction_code=instruction=[if k%2==0 ,or ,and ]}

\integer{alt=randint(1..4)}
\text{pp=(\alt==1 or \alt==2)?0:1}
\text{ppp=(\alt==2 or \alt==4)?1:0}
\integer{altt=randint(1..2)}
\text{zr=(\altt==2)?&&:||}
\text{DD=pari(m=matrix(\nc,\nc,i,j,if(j%2==\pp \zr i%2==\ppp,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\integer{s=(\kk)%2}
\integer{ss=(\kj)%2}
\if{(\altt==1 and (\s==\ppp or \ss==\pp)) or (\altt==2 and (\s==\ppp and \ss==\pp))}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme avec l'instruction <code>if k%2==0</code> couplée avec
 les opérateurs and et or afin d'écrire une instruction de la forme :
<code>if i%2==0 and j%2==0 :</code>.
 La représentation donnée à droite ou ci-dessous est à effectuer.}
