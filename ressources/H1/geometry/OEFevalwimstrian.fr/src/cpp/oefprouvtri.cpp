target=oefprouvtri1 oefprouvtri2 oefprouvtri3 oefprouvtri4 oefprouvtri5
#define TITRE Prouver
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
#if defined TARGET_oefprouvtri1
# define NUM 1
#endif
#if defined TARGET_oefprouvtri2
# define NUM 2
#endif
#if defined TARGET_oefprouvtri3
# define NUM 3
#endif
#if defined TARGET_oefprouvtri4
# define NUM 4
#endif
#if defined TARGET_oefprouvtri5
# define NUM 5
#endif
\title{TITRE NUM}
\text{let=shuffle(A,B,C,E,F,G,H,R,S,T)}
\matrix{prop=triangle isocèle,deux côtés de même longueur
triangle équilatéral,trois côtés de même longueur
triangle rectangle,un angle droit
triangle isocèle et rectangle,deux côtés de même longueur et un angle droit}
\text{mot=deux,trois,côtés,de,même,longueur,et,un,angle,droit}

#if defined TARGET_oefprouvtri1
\text{typ=correspond}
\text{size=60x200x300}
\text{list1=column(1,\prop)}
\text{list2=column(2,\prop)}
\text{n=shuffle(4)}
\text{list1=\list1[\n[1]],\list1[\n[2]],\list1[\n[3]],\list1[\n[4]]}
\text{list2=\list2[\n[1]],\list2[\n[2]],\list2[\n[3]],\list2[\n[4]]}
#endif
#if defined TARGET_oefprouvtri2
\text{typ=clickfill}
\text{size=300x60}
\text{lista=column(1,\prop)}
\text{listb=column(2,\prop)}
\integer{n=randint(1..4)}
\text{list1=\listb[\n[1]]}
\text{list2=\listb[\n[2]],\listb[\n[3]],\listb[\n[4]]}
\text{enonc= Le triangle est un \lista[\n[1]] car il a }
#endif

#if defined TARGET_oefprouvtri3
\text{typ=clickfill}
\text{size=300x60}
\text{lista=column(1,\prop)}
\text{listb=column(2,\prop)}
\integer{n=randint(1..4)}
\text{list1=\lista[\n[1]]}
\text{list2=\lista[\n[2]],\lista[\n[3]],\lista[\n[4]]}
\text{enonc= Si un triangle a \listb[\n[1]] alors c'est un }
#endif
#if defined TARGET_oefprouvtri4
\text{typ=compose}
\text{size=300x60}
\matrix{prop=triangle isocèle,deux,côtés,de,même,longueur
triangle équilatéral,trois,côtés,de,même,longueur
triangle rectangle,un,angle,droit}
\integer{n=randint(1..3)}
\text{list=row(\n,\prop)}
\text{list1=item(2..9,\list)}
\text{list2=\mot}
\text{enonc= Le triangle est un \list[1] car il a }
#endif
#if defined TARGET_oefprouvtri5
\text{typ=atext}
\text{size=300x60}
\integer{n=randint(1..3)}
\text{list=row(\n,\prop)}
\text{list1=item(2,\list)}
\text{enonc= Le triangle est un \list[1] car il a }
#endif


\statement{
Comment prouver qu'un triangle est particulier ?
<p>\enonc</p>
<div class="wimscenter">\embed{r1,\size}</div>
}

\answer{}{\list1;\list2}{type=\typ}
