target=thmpte1 thmpte2 thmpte3 thmpte4 thmpte5
#define TITRE Théorèmes et propriétés
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{no}
\text{lstthm=théorème de la droite des milieux, théorème de Thalès,réciproque du théorème de Thalès, théorème de Pythagore, théorème de l'angle droit, théorème de l'angle inscrit, théorème de l'angle au centre}

#if defined TARGET_thmpte1
\title{TITRE 1}
\integer{k=randint(1..3)}
\if{\k=1}
{
\text{lstthm=Théorème de Pythagore,
   Réciproque du théorème de Pythagore,
   Théorème de Thalès,
   Réciproque du théorème de Thalès,
   Théorème de la droite des milieux,
   Théorème de l'angle droit,
   Théorème de l'angle inscrit,
   Théorème de l'angle au centre,
}
\text{lstenonce=Soit un triangle \(AB C\) rectangle en \(A\). Alors \(B C^2=A B^2+A C^2),
   Soit un triangle \(A B C). Si \(B C^2=A B^2+A C^2) alors le triangle est rectangle en \(A).,
   Soit trois points non alignés \(A,B,C) et un point \(M \in (A B)) et un point \(N \in (A C)). Si \((M N) \parallel (B C)) alors \(\frac{A M}{A B}=\frac{A N}{A C}=\frac{M N}{B C}).,
   Soit trois points non alignés \(A,B,C) et deux points \(M) et \(N)&#44; tels que \(A,M,B) et \(A,N,C) soient alignés et dans le même ordre. Si \(\frac{A M}{A B}=\frac{A N}{A C})&#44; alors les droites \((M N)) et \((B C))  sont parallèles.,
   Soit un triangle non aplati \(A B C)&#44; \(I) le milieu de \([A B]) et \(J) le milieu de \([A C]). Alors la droite \((M N)) est parallèle à \((B C)) et \(M N=\frac{B C}{2}).,
   Soit un triangle \(A B C) non aplati. Pour tout point \(M) du cercle \(\mathcal{C}) de diamètre \([A B]) distinct de \(A) et de \(B)&#44; le triangle \(A B M) est rectangle en \(M).,
   Soit trois points non alignés \(A,B,C) et \(\mathcal{C}) le cercle circonscrit à ces points. Pour tout point \(M \in \mathcal{C}) distinct de \(A) et de \(B)&#44; \(\widehat{A M B}=\widehat{A C B}).,
   Soit trois points non alignés \(A,B,C)&#44; \(\mathcal{C}) le cercle circonscrit à ces points&#44; et \(O) le centre de ce cercle. \(\widehat{A O B}=2\widehat{A C B}).,
}
\text{lstind=shuffle(8)}
\text{ListThm=}
\text{ListEnonce=}
\text{lstind=5,6,7,8}
\for{i=1 to 4}
 {
\text{ListThm=wims(append item \lstthm[\lstind[\i]] to \ListThm)}
\text{ListEnonce=wims(append item \lstenonce[\lstind[\i]] to \ListEnonce)}
 }
\text{size=150x200x500}
\text{tintro=Mettez en correspondance les noms des théorèmes et leurs énoncés.}

}
\if{\k=2}
{
\text{size=100x150x150}
\text{tintro=Mettez en correspondance les droites remarquables du triangle et les noms des points d'intersection de ces droites.}
\text{ListThm=Médianes,Médiatrices,Hauteurs,Bissectrices}
\text{ListEnonce=Centre de gravité,Centre du cercle circonscrit au triangle, Orthocentre, Centre du cercle inscrit dans le triangle}
}
\if{\k=3}
{
\text{size=100x100x250}
\text{tintro=Mettez en correspondance les droites remarquables du triangle et leurs définitions.}
\text{ListThm=Médiane,Médiatrice,Hauteur,Bissectrice}
\text{ListEnonce=Droite qui passe par un sommet et le milieu du côté opposé,
   Droite perpendiculaire à un côté&#44; passant par le milieu de ce côté,
   Droite qui passe par un sommet et est perpendiculaire au côté opposé,
   Droite qui passe par un sommet et qui partage l'angle au sommet en deux angles égaux
}
}
\statement{
\tintro
<div class="wimscenter">
\embed{reply1,\size}</div>
}
\answer{correspondance}{\ListThm;\ListEnonce}{type=correspond}
#endif

#if defined TARGET_thmpte2
\title{TITRE 2}
\text{lstfill=A B C,G B C,A C'B',G I J,B C'G,C B'G,\(\overrightarrow{I J}),\(\overrightarrow{B C}),\(\overrightarrow{C'B'}),\(\overrightarrow{C'G}),\(\overrightarrow{G J}),\(\overrightarrow{B'G}),\(\overrightarrow{G I}),\(\overrightarrow{J C}),\(\overrightarrow{I B})}
\text{dessin=
 xrange -5,12
 yrange -5,12
 poly blue,0,8,-4,-2,10,-2
 poly red,-2,3,5,3,6,-1/3,-1,-1/3
 segment -4,-2,5,3,red
 segment 10,-2,-2,3,red
 text black,0,8.6,medium,A
 text black,10,-2.5,medium,C
 text black,-4,-2.5,medium,B
 text black,-3,4,medium,C'
 text black,5.4,4,medium,B'
 text black,-1.5,0.5,medium,I
 text black,6,0.5,medium,J
 text black,2,2.5,medium,G
}
\integer{goodtr1=0}
\integer{goodtr2=0}
\integer{egal1=0}

\text{size=80x40x1}
\rational{rap=1/2}
\text{tABC=A B C}
\text{tGBC=G B C}
\text{vCpBp=\(\overrightarrow{C'B'})}
\text{vBC=\(\overrightarrow{B C})}
\text{vIJ=\(\overrightarrow{I J})}
\text{lCpG=C'G}
\text{lGJ=G J}
\text{lGI=G I}
\text{lBpG=B'G}
\text{lstquad=parallélogramme,carré,losange,rectangle,trapèze}
\statement{<div class="float_right">\draw{300,300}{\dessin}</div>
   Soit un triangle \(A B C), \(B') le milieu de \([A C]), \(C') le milieu de \([A B]).
   On note \(G) le point commun des droites \((B B')) et \((C C')).
   On note \(I) le milieu de \([B G]) et \(J) celui de \([C G]).<p>
   Il faut démontrer que les médianes d'un triangle se coupent aux deux tiers de leur longueur en partant d'un sommet.
</p><p>
   Pour cela, vous devez compléter le raisonnement suivant:
</p>
<br class="clearall">
<ul><li>
   On sait par le \embed{reply1} dans le triangle \embed{reply2,\size} que:
<div class="wimscenter"> \embed{reply3,\size}=\embed{reply4,3}\embed{reply5,\size}.</div>
</li><li>
   On sait par le \embed{reply6} dans le triangle \embed{reply7,\size} que:
<div class="wimscenter"> \embed{reply8,\size}=\embed{reply9,3}\embed{reply10,\size}.</div>
</li><li>On en déduit l'égalité : \embed{reply11,\size}=\embed{reply12,\size}.
</li><li>
   Donc le quadrilatère \(C'B'J I) est un \embed{reply13}.
</li><li>
   Il vient \(C'G)=\embed{reply14,\size} et \(B'G)=\embed{reply15,\size}.
</li><li>
   Ainsi, étant données les définitions de \(I) et \(J), on a :
<div class="wimscenter">
\(J C =J G)=\embed{reply16,\size} et \(I B=I G)=\embed{reply17,\size}.
</div>
</li></ul>
}
\if{\ttABC issametext \tABC}
 {
  \if{((\vvCpBp issametext \vCpBp and \vvBC issametext \vBC and \rrap=1/2) or (\vvCpBp issametext \vBC and \vvBC issametext \vCpBp and \rrap=2))}
   { \integer{goodtr1=1}}
 }
\if{\ttABC issametext \tGBC}
 {
  \if{((\vvCpBp issametext \vIJ and \vvBC issametext \vBC and \rrap=1/2) or (\vvCpBp issametext \vBC and \vvBC issametext \vIJ and \rrap=2))}
   { \integer{goodtr1=1}}
 }
\if{\ttGBC issametext \tABC}
 {
  \if{((\vvIJ issametext \vCpBp and \vvBC2 issametext \vBC and \rrap2=1/2) or (\vvIJ issametext \vBC and \vvBC2 issametext \vCpBp and \rrap2=2))}
   { \integer{goodtr2=1}}
 }
\if{\ttGBC issametext \tGBC}
 {
  \if{((\vvIJ issametext \vIJ and \vvBC2 issametext \vBC and \rrap2=1/2) or (\vvIJ issametext \vBC and \vvBC2 issametext \vIJ and \rrap2=2))}
   { \integer{goodtr2=1}}
 }
\if{(\v2IJ issametext \vIJ and \v2CpBp issametext \vCpBp) or (\v2IJ issametext \vCpBp and \v2CpBp issametext \vIJ)}
  {\integer{egal1=1}}
\answer{thm1}{1;\lstthm}{type=menu}{option=shuffle}
\answer{triangle 1}{\ttABC;\lstfill}{type=clickfill}
\answer{vecteur 1}{\vvCpBp;\lstfill}{type=clickfill}
\answer{rapport 1}{\rrap}{type=numeric}
\answer{vecteur 2}{\vvBC;\lstfill}{type=clickfill}
\answer{thm2}{1;\lstthm}{type=menu}{option=shuffle}
\answer{triangle 2}{\ttGBC;\lstfill}{type=clickfill}
\answer{vecteur 3}{\vvIJ;\lstfill}{type=clickfill}
\answer{rapport 2}{\rrap2}{type=numeric}
\answer{vecteur 4}{\vvBC2;\lstfill}{type=clickfill}
\answer{vecteur 5}{\v2IJ;\lstfill}{type=clickfill}
\answer{vecteur 6}{\v2CpBp;\lstfill}{type=clickfill}
\answer{quadrilatère}{1;\lstquad}{type=menu}
\answer{longueur 1}{\lGJ;\lstfill}{type=clickfill}
\answer{longueur 2}{\lGI;\lstfill}{type=clickfill}
\answer{longueur 3}{\lCpG;\lstfill}{type=clickfill}
\answer{longueur 4}{\lBpG;\lstfill}{type=clickfill}
\condition{}{\goodtr1=1 and \goodtr2=1 and \egal1=1}
#endif

#if defined TARGET_thmpte3
\title{TITRE 3}
\text{dessin=
 xrange -5,12
 yrange -5,12
 poly blue,0,8,-4,-2,10,-2
 segment 0,8,3,-2,red
 segment -1,11/2,5/2,11/2,red
 text black,0,8.6,medium,A
 text black,10,-2.5,medium,C
 text black,-4,-2.5,medium,B
 text black,3,-2.5,medium,A'
 text black,-1.5,6,medium,E
 text black,3,6,medium,F
 text black,1,6,medium,K
}
\text{size=80x30x1}
\text{lstfill=\((A B)),\((A C)),\(B A'),\(A K),\(A A'),\(F K),\(A'C),\(B A'),\(A'C),\(E K)}
\text{dAB=\((A B))}
\text{dAC=\((A C))}
\text{lBAp=\(B A')}
\text{lAK=\(A K)}
\text{lAAp=\(A A')}
\text{lFK=\(F K)}
\text{lApC=A'C}
\text{lBAp=\(B A')}
\text{lApC=\(A'C)}
\text{lEK=\(E K)}
\integer{goodrep1=0}
\integer{goodrep2=0}
\integer{goodrep3=0}
\integer{goodrep4=0}
\statement{
   Soit un triangle \(A B C), \(A') le milieu de \([B C]), la médiane \((A A'))
   et un segment \([E F]) parallèle à\((B C)), qui coupe \((A A')) en \(K).
   <p>
   Il faut démontrer que \(K) est le milieu de \([E F]).</p>
<p>Pour cela, vous devez compléter le raisonnement suivant:</p>
<br class="float_right">
<ul><li>Etape 1 :
   Le \embed{reply1} relatif aux sécantes \((A A')) et \embed{reply2,\size}
   et aux parallèles \((E F)) et \((B C)) implique que:
<table class="wimscenter"><tr>
<td>\(A K) </td><td rowspan="3"> = </td><td>\embed{reply3,\size}</td></tr>
<tr><td><hr></td><td><hr></td></tr>
<tr><td>\embed{reply4,\size}</td><td>\embed{reply5,\size}</td></tr></table>
</li><li> Etape 2 :
   Le \embed{reply6} relatif aux sécantes \((A A')) et \embed{reply7,\size}
   et aux parallèles \((E F)) et \((B C)) implique que:
<table class="wimscenter"><tr>
<td>\(A K) </td><td rowspan="3"> = </td><td>\embed{reply8,\size}</td></tr>
<tr><td><hr></td><td><hr></td></tr>
<tr><td>\embed{reply9,\size}</td><td>\embed{reply10,\size}</td></tr></table>
</li><li>Etape 3 :
   On en déduit l'égalité:
<table class="wimscenter"><tr>
<td>\(E K) </td><td rowspan="3"> = </td><td>\embed{reply11,\size}</td></tr>
<tr><td><hr></td><td><hr></td></tr>
<tr><td>\embed{reply12,\size}</td><td>\embed{reply13,\size}</td></tr></table>
</li><li>Etape 4 :
   Comme \embed{reply14,\size}=\embed{reply15,\size},on a \(E K = K F).
</li></ul>
}
\if{\ddAB issametext \dAB}
 {
 \if {\llBAp issametext \lBAp and ((\llAAp issametext \lAAp and \llEK issametext \lEK) or (\llAAp issametext \lEK and \llEK issametext \lAAp))}
   {\text{goodrep1=1}}
 }
\if{\ddAB issametext \dAC}
 {
 \if {\llBAp issametext \lApC and ((\llAAp issametext \lAAp and \llEK issametext \lFK) or (\llAAp issametext \lFK and \llEK issametext \lAAp))}
   {\text{goodrep1=1}}
 }
\if{\ddAC issametext \dAC}
 {
 \if {\llApC issametext \lApC and ((\ll2AAp issametext \lAAp and \llFK issametext \lFK) or (\ll2AAp issametext \lFK and \llFK issametext \lAAp))}
   {\text{goodrep2=1}}
 }
\if{\ddAC issametext \dAB}
 {
 \if {\llApC issametext \lBAp and ((\ll2AAp issametext \lAAp and \llFK issametext \lEK) or (\ll2AAp issametext \lEK and \llFK issametext \lAAp))}
   {\text{goodrep2=1}}
 }
\if{\ll2ApC issametext \lApC and ((\ll2BAp issametext \lBAp and \ll2FK issametext \lFK) or (\ll2BAp issametext \lFK and \ll2FK issametext \lBAp))}
   {\text{goodrep3=1}}
\if{(\ll3BAp issametext \lBAp and \ll3ApC issametext \lApC) or (\ll3BAp issametext \lApC and \ll3ApC issametext \lBAp)}
   {\text{goodrep4=1}}

\answer{}{2;\lstthm}{type=menu}
\answer{}{\ddAB;\lstfill}{type=clickfill}
\answer{}{\llEK;\lstfill}{type=clickfill}
\answer{}{\llAAp;\lstfill}{type=clickfill}
\answer{}{\llBAp;\lstfill}{type=clickfill}
\answer{}{2;\lstthm}{type=menu}
\answer{}{\ddAC;\lstfill}{type=clickfill}
\answer{}{\llFK;\lstfill}{type=clickfill}
\answer{}{\ll2AAp;\lstfill}{type=clickfill}
\answer{}{\llApC;\lstfill}{type=clickfill}
\answer{}{\ll2BAp;\lstfill}{type=clickfill}
\answer{}{\ll2FK;\lstfill}{type=clickfill}
\answer{}{\ll2ApC;\lstfill}{type=clickfill}
\answer{}{\ll3BAp;\lstfill}{type=clickfill}
\answer{}{\ll3ApC;\lstfill}{type=clickfill}
\condition{\goodrep4=1 and \goodrep3=1 and \goodrep2=1 and \goodrep1=1}

#endif

#if defined TARGET_thmpte4
\title{TITRE 4}
\text{dessin=
 xrange -3,7
 yrange -2,2
 linewidth 2
 circle 1,0,80,black
 circle 3,0,80,black
 circle 5,0,80,black
 segment 2.98,0.59,3,0,black
 poly black,3,0,2.1,0.43,3.66,0.75
 segment 0,0,4.8,0.98,red
 segment 3,0,2.88,0.59
 polyline black,0,0,5,0,4.8,0.98
 text black,-0.5,0,medium,A
 text black,1,-0.2,medium,O1
 text black,3,-0.2,medium,O2
 text black,5,-0.2,medium,O3
 text black,5,1.3,medium,D
 text black,3,1,medium,H
 text black,2,0.9,medium,B
 text black,3.66,1.2,medium,C
 linewidth 5
 points black,1,0,3,0,5,0

}
\text{lstorth=Le triangle \(B O_2C) est isocèle en \(O_2)&#44; la médiane issue de \(O_2) est donc hauteur.,
\((O_2H)) est parallèle à \((O_3D)) et le rayon au point de tangence est perpendiculaire à la tangente.,
   La réciproque du théorème de Pythagore prouve que le triangle \(A O_2H) est rectangle
   car \(A H^2+O_2H^2 = A O_2^2).}
\integer{a=randint(1..5)}
\integer{ao2=3*\a}
\integer{ao3=5*\a}
\rational{o2h=3/5*\a}
\rational{bh=4/5*\a}
\rational{bc=2*\bh}
\statement{<div class="float_right">\draw{400,160}{\dessin}</div>
   On a trois cercles de rayon \a.
   La droite \((A D)) est tangente au cercle de centre \(O_3).
   Les points \(B) et \(C) sont les points où cette droite
   rencontre le cercle de centre \(O_2).
\(H) est le milieu de \([B C]).<p>
   On souhaite calculer la longueur \(B C).
</p>
<br class="clearall">
<ol>
<li> Calculez les longueurs: \(A O_2)=\embed{reply1,3},\(A O_3)=\embed{reply2,3}</li>
<li> Démontrez que \((O_2H)) est perpendiculaire à \((A D))
   en choississant l'un des arguments ci-dessous :
  <ul>
  <li> \embed{reply3,1} </li>
  <li> \embed{reply3,2} </li>
  <li> \embed{reply3,3} </li>
  </ul>
</li>
<li> Pour calculer la longueur \(O_2H), j'utilise le \embed{reply4}
<div class="wimscenter">longueur \(O_2H)=\embed{reply5,3}</div></li>
<li> Pour calculer la longueur \(B H), j'utilise le \embed{reply6}
<div class="wimscenter">longueur \(B H)=\embed{reply7,3}
   longueur \(B C)=\embed{reply8,3}</div>
</li></ol>

}
\answer{\(A O_2\)}{\ao2}{type=numeric}{weight=0.5}
\answer{\(A O_3\)}{\ao3}{type=numeric}{weight=0.5}
\answer{\(O_2H\) perpendiculaire à \(A D\)}{1;\lstorth}{type=radio}{weight=2}
\answer{Thm}{2;\lstthm}{type=menu}{weight=2}
\answer{\(O2H\)}{\o2h}{type=numeric}{weight=1}
\answer{Thm2}{4;\lstthm}{type=menu}{weight=2}
\answer{\(B H\)}{\bh}{type=numeric}{weight=1.5}
\answer{\(B C\)}{\bc}{type=numeric}{weight=0.5}
#endif

#include "thmpte5.inc"
