\title{Pixel Art 08 +}

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

\text{keytest=for&if}
\text{instruction_code=instruction=[if 7&lt;=k&lt;=14 :]}

\integer{cc=randint(2..\nc-1)}
\integer{alt=randint(1..2)}
\text{var=(\alt==1)?j:i}
\text{varb=(\alt==2)?j:i}

\text{zr=(\alt==1)?\cc:1000}
\text{zrr=(\alt==2)?\cc:1000}

\integer{intmin=randint(2..\nc-4)}
\integer{intmax=randint(\intmin..\nc-1)}

\text{DD=pari(m=matrix(\nc,\nc,i,j,if(\var==\cc && \intmin<=\varb && \varb<=\intmax,0,1));)}
\text{DD=pari(print(m);)}
text{DD=wims(replace internal ; by &#93;,&#91; in \DD )} <= Bon affichage matrice
\text{DD=wims(replace internal ; by , in \DD )}
text{DD=[\DD]}<= Bon affichage matrice

\text{mjsx=}
\for{kj=1 to \nc}{
\for{kk=1 to \nc}{
\if{(\kj==\zr and \intmin<=\kk and \kk<=\intmax) or (\kk==\zrr and \intmin<=\kj and \kj<=\intmax)}{
\text{mjsx=wims(append line board.create('point', [\kj-0.5,\kk-0.5],{color:'black'}); to \mjsx)}
}}}
\text{inst=Modifier cet algorithme en ecrivant des inégalités couplées avec
 les opérateurs and et or afin d'écrire une instruction de la forme :
<code>if 1<=i<=5 and 4<=j<=8 :</code>.
 La représentation donnée à droite ou ci-dessous est à effectuer.}
