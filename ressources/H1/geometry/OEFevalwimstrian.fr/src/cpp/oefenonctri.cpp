target=oefenonctri1 oefenonctri2 oefenonctri3 oefenonctri4 oefenonctri5
#define TITRE Énoncé
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
\text{let=shuffle(A,B,C,E,F,G,H,R,S,T)}
#if defined TARGET_oefenonctri1
# define NUM 1
#endif
#if defined TARGET_oefenonctri2
# define NUM 2
#endif
#if defined TARGET_oefenonctri3
# define NUM 3
#endif
#if defined TARGET_oefenonctri4
# define NUM 4
#endif
#if defined TARGET_oefenonctri5
# define NUM 5
#endif
\title{TITRE NUM}
#if defined TARGET_oefenonctri1
\text{enonc1=Nous avons un triangle \let[1]\let[2]\let[3] rectangle en \let[3] tels que}
\real{l1=randint(40..80)/10}
\real{l2=randint(\l1*10+10..120)/10}
\integer{rep=sqrt(\l1^2+\l2^2)*10}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
\text{l=shuffle(\l1,\l2)}
\text{enonc2=\let[1]\let[3] = \l[1] cm et \let[2]\let[3] = \l[2] cm}
\text{enonc3=\let[1]\let[2]}
#endif
#if defined TARGET_oefenonctri2
\text{enonc1=Nous avons un triangle \let[1]\let[2]\let[3] rectangle en \let[3] tels que}
\real{l1=randint(40..80)/10}
\real{l2=randint(\l1*10+10..120)/10}
\integer{rep=sqrt(\l2^2-\l1^2)*10}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}
\text{l=\l1,\l2}
\text{enonc2=\let[2]\let[3] = \l[1] cm et \let[2]\let[1] = \l[2] cm}
\text{enonc3=\let[1]\let[3]}
#endif
#if defined TARGET_oefenonctri3
\text{enonc1=Nous avons un triangle \let[1]\let[2]\let[3] équilatéral tel que}
\real{l1=randint(40..90)/10}
\text{enonc2=\let[1]\let[2] = \l1 cm}
\text{enonc3=\let[2]\let[3]}
\real{rep1=\l1}
\real{rep2=\l1}
#endif
#if defined TARGET_oefenonctri4
\text{enonc1=Nous avons un triangle \let[1]\let[2]\let[3] isocèle de sommet \let[3] tels que}
\real{l1=randint(40..80)/10}
\real{l2=randint(\l1*10+10..100)/10}
\text{l=\l1,\l2}
\real{rep1=\l[1]}
\real{rep2=\l[1]}
\text{enonc2=randomitem(\let[1]\let[3] = \l[1] cm et \let[1]\let[2] = \l[2] cm,
\let[1]\let[2] = \l[2] cm et \let[1]\let[3] = \l[1] cm)}
\text{enonc3=\let[2]\let[3]}
#endif
#if defined TARGET_oefenonctri5
\text{enonc1=Nous avons un triangle \let[1]\let[2]\let[3] formé
par deux triangles \let[1]\let[2]\let[4] et \let[1]\let[3]\let[4] rectangles en \let[4].}
\real{l1=randint(40..70)/10}
\real{l2=randint(\l1*10+10..100)/10}
\real{l3=randint(\l1*10+10..100)/10}
\integer{repa=sqrt(\l2^2-\l1^2)*10}
\integer{repb=sqrt(\l3^2-\l1^2)*10}
\integer{rep=\repa+\repb}
\real{rep1=(\rep-2)/10}
\real{rep2=(\rep+2)/10}
\text{enonc2= Nous avons les mesures suivantes
\let[1]\let[4] = \l1 cm &#44;
\let[1]\let[2] = \l2 cm et \let[1]\let[3] = \l3 cm}
\text{enonc3=\let[2]\let[3]}
#endif
\statement{
  <div>\enonc1 \enonc2.</div>
<p>
Faire la figure sur une feuille de brouillon
et donner la mesure de \enonc3.</p>
<div class="wimscenter"><label for="reply1">\enonc3</label> = \embed{r1,4} cm</div>
}

\answer{}{\rep1,\rep2}{type=range}
