\title{Pixel Art 09}

\text{prob=Pixel Art et Python}
\text{lii=Pong.png}
\text{nomi=PONG !}

\text{enonce=Pong (stylisé PONG) est un des premiers jeux vidéo d'arcade et le premier
 jeu vidéo d'arcade de sport. Il a été imaginé par l'Américain Nolan Bushnell et
 développé par Allan Alcorn, et la société Atari le commercialise à partir de novembre
 1972. Bien que d'autres jeux vidéo aient été inventés précédemment, comme
 Computer Space, Pong est le premier à devenir populaire.
   <a href="https://fr.wikipedia.org/wiki/Pong" target="_blank" >Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=\nc}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for&if}
\text{instruction_code=instruction=[if k%2==0 :]}

\integer{alt=randint(1..2)}
\text{pp=(\alt==1 or \alt==2)?0:1}
\integer{altt=randint(1..2)}
\text{zr=(\altt==2)?i:j}
\text{DD=pari(m=matrix(\nc,\nc,i,j,if(\zr%2==\pp,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\integer{s=(\kk)%2}
\integer{ss=(\kj)%2}
\if{(\altt==1 and (\ss==\pp)) or (\altt==2 and (\s==\pp))}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}

\text{inst=Modifier cet algorithme avec l'instruction conditionnelle <code>if k%2==0 :</code>.
 La représentation donnée à droite ou ci-dessous est à réaliser.}
