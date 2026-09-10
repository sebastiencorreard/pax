target=tirage1 tirage2 remise1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
/*Prendre s<4 pour tirage*/
\css{<style>
.bgreen{color:green; font-weight:bold;font-style:italic}
</style>}
\text{remise=randitem(\avecsans)}

#if defined TARGET_tirage1
\integer{s=\confparm1= ? randint(2..3):min(3,\confparm1+1)}
\text{prof=3}
#elif defined TARGET_tirage2
\integer{s=\confparm1= ? randint(2..3):min(3,\confparm1+1)}
\integer{prof=3}
#elif defined TARGET_remise1
\integer{s=\confparm1= ? randint(2..3):min(3,\confparm1+1)}
\text{prof=3}
\text{rep=position(\remise,\avecsans)}
#endif

\integer{N=randint(15..26)}
\text{prob=wims(makelist 1/\s for x=1 to \s-1)}
\text{liste=slib(stat/multinomial 1,\N,[\prob])}

\text{ps= pari([\liste]/\N)}
\text{p1=pari([\liste]/(\N-1))}
\text{pa=pari([\liste]/\N)}
\text{ligne=}
\matrix{liste=\liste}
/*r=1*/
\text{r=1}
\for{j=1 to \s}{
#if defined TARGET_tirage1
	\text{p1=\p1,simplify(max((\liste[\r;\j]-1)/\N))}
	\text{p1=\p1,simplify(max(0,(\liste[\r;\j]-1)/(\N-1)))}
#endif
	\for{ k= 1 to \s}{
		\text{ps= (\k-\j) %\s = 0 ?\ps,simplify((\liste[\r;\k]-1)/(\N-\r)):
		\ps,simplify((\liste[\r;\k])/(\N-\r))}
		\text{pa=\pa, simplify((\liste[1;\k])/\N)}
		\text{ligne=(\k-\j )%\s = 0? \ligne, \liste[\r;\k]-1:\ligne, \liste[\r;\k]}
	}
	\text{ligne=wims(nonempty items \ligne)}
	\matrix{liste=\liste
\ligne}
}

\text{p=\remise issametext \avecsans[1] ? \pa:\ps}
\integer{n=randint(10..12)}
\text{colors=blue,red,orange,black,purple,grey,white}
\text{choix=item(1..\s,shuffle(items(\colors)))}
\text{couleurs=\couleurs[\choix]}
\integer{H=(\s^(\prof)-1)/(\s-1)-1}
\text{colors=wims(makelist \colors[\choix] for x=1 to \H)}
\text{nom=*}
\text{S=slib(graph/randtree \H,\s,\prof,[\nom], middle perfect point)}
\text{u=wims(declosing \S[1])}
\text{position=\S[3]}
\text{milieu=\S[4]}
\matrix{position= wims(declosing \position)}
\matrix{milieu= wims(declosing \milieu)}
\text{G=\S[2]}
\text{G= wims(declosing \G)}
\text{cnt=rows(\G)}
\integer{cnt_m=rows(\milieu)}
\for{i=2 to \cnt}{
	\text{u=\u
	fill \position[\i;], \colors[\i-1]
	}
}
Deuxième question
\text{U=randint(1..\s)}
\text{couleur=\couleur[\choix]}
\text{couleur=\couleur[\U]}
\rational{rep2= 0}
\for{i=1 to \s}{
	\rational{rep2= \rep2 + \p[\i]*\p[\s*\i+\U]}
	}
Dessin
\matrix{G = \G }
\text{rangex=row(1,\u)}
\text{rangex =wims(replace internal xrange by in \rangex)}
\text{rangey=row(2,\u)}
\text{rangey =wims(replace internal yrange by in \rangey)}
\text{Sizex=600}
\text{Sizey=250}
\text{pos_m=}
\text{border=10}


#if defined TARGET_tirage1
Reponses
\text{rep=wims(makelist r x for x = 1 to \cnt_m)}
\text{rep = wims(nospace \rep)}
 \for{i=2 to \cnt_m}{
 	\real{sx=\milieu[\i;1]}
 	\real{sy=\milieu[\i;2]}
	\text{POS=slib(draw/convpixel \sx,\sy,\Sizex,\Sizey,\rangex,\rangey,10,pixels)
 }
 	\matrix{pos_m=\pos_m
	r \i , \POS[1] x \POS[2]}
}
\steps{\rep}
#elif defined TARGET_tirage2  || defined TARGET_remise1
\for{i=2 to \cnt_m}{
	\text{c=\p[\i-1]}
 	\real{sx=\milieu[\i;1]}
 	\real{sy=\milieu[\i;2]}
	\text{u=\u
	text black,\sx-0.4,\sy+0.1,medium,\c
	}
}
#endif

\text{dessin=draw(\Sizex,\Sizey
\u)}

\statement{
   Une urne contient \N boules :
\for{T=1 to \s}{\if{\T < \s and \T >1}{,}
\if{\T=\s}{et} \liste[1;\T] \couleurs[\T]}. On effectue
#if defined TARGET_tirage1 || defined TARGET_tirage2
\deux tirages \remise remise.
#endif
#if defined TARGET_remise1
\deux tirages.
#endif
#if defined TARGET_tirage1
<ul><li>On représente cette situation par un arbre. Le remplir :
<div class="wimscenter">\special{imagefill \dessin,\Sizex x \Sizey,40x20
\pos_m
}
</div>
</li>
<li>La probabilité de l'événement
<span class="bgreen">tirer une boule \couleur
   au deuxième tirage</span> est
<div class="wimscenter"> \embed{r1}.</div>
</li></ul>
#elif defined TARGET_tirage2
   On représente cette situation par un arbre :
<div class="wimscenter"><img src="\dessin" alt=""></div>
   La probabilité de l'événement
<span class="bgreen">tirer une boule \couleur au \deuxieme tirage</span>
   est
<div class="wimscenter"> \embed{r1}.</div>
#elif defined TARGET_remise1
  On représente cette situation par un arbre :
<div class="wimscenter"><img src="\dessin" alt=""></div>
   Il s'agit d'un tirage \embed{r1,1} ou \embed{r1,2} remise.
#endif
}
#if defined TARGET_tirage1 || defined TARGET_tirage2
\answer{Probabilité de l'événement}{\rep2}
# if defined TARGET_tirage1
\answer{}{\p[1];\p1}{type=clickfill}
\answer{}{\p[2]}{type=clickfill}
\answer{}{\p[3]}{type=clickfill}
\answer{}{\p[4]}{type=clickfill}
\answer{}{\p[5]}{type=clickfill}
\answer{}{\p[6]}{type=clickfill}
\answer{}{\p[7]}{type=clickfill}
\answer{}{\p[8]}{type=clickfill}
\answer{}{\p[9]}{type=clickfill}
\answer{}{\p[10]}{type=clickfill}
\answer{}{\p[11]}{type=clickfill}
\answer{}{\p[12]}{type=clickfill}
# endif
#elif defined TARGET_remise1
\answer{Tirage}{\rep;\avecsans}{type=click}
#endif
