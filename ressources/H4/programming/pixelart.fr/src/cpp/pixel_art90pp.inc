\title{Pixel Art 10 ++}

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
\text{instruction_code=instruction=[if, k%3==??,i<=j+?? ,j<=i+??,and,or ]}

\integer{alt=randint(0..3)}
\integer{pp=randint(0..1)}
\integer{ppp=randint(0..2)}
\text{cond1=randitem(j%2==\pp,j%3==\ppp,true)}
\text{cond2=randitem(i<=j+\alt,j<=i+\alt)}

\text{DD=pari(m=matrix(\nc,\nc,i,j,if((\cond1) && (\cond2),0,1));)}
\text{DDV=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DDV )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\integer{s=\DDV[\kk;\kj]}
\if{(\s==0)}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme en ecrivant des inégalités entre les variables couplées éventuellement avec
 les opérateurs and et modulo qui donne le reste de la division euclidienne afin d'écrire une instruction de la forme :
<code>if i%2==0 and j<=i+2 :</code>.
 La représentation donnée à droite ou ci-dessous est à effectuer.}
