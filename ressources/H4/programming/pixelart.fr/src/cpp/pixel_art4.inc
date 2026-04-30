\title{Pixel Art 04}

\text{prob=Pixel Art et Python}
\text{lii=Tennis_for_Two_Machine_at_CAX_2010.jpg}
\text{nomi=Jeux de Tennis}

\text{enonce=Tennis for Two est un jeu vidéo de tennis conçu en 1958 par William Higinbotham
 et développé par Robert Dvorak, souvent considéré comme le premier jeu vidéo de l'histoire.
 <a href="https://fr.wikipedia.org/wiki/Tennis_for_Two" target="_blank">Source Wikipedia</a>}

\integer{nc=randint(10..20)}
\text{nl=1}
\text{nll=\nc}
\text{encop=[[1] * nombre_colonne for _ in range(nombre_ligne)]}

\text{keytest=for&if}
\text{instruction_code=instruction=[if k%2==0 :]}

\integer{alt=randint(1..2)}
\text{var=(\alt==1)?j:(j+1)}
\text{zr=(\alt==1)?0:1}
\text{DD=pari(m=matrix(1,\nc,i,j,if(\var%2==0,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\integer{s=(\kj+\zr)%2}
\if{\s==0}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,0.5],{color:'black'}); to \mjsx)}
}}

\text{inst=Modifier cet algorithme avec l'instruction conditionnelle <code>if k%2==0 :</code>
 pour qu'il effectue <b>sans erreur</b> la représentation donnée à droite ou ci-dessous.}
