target=dimension3,dimension4,dimension5
#define TITRE Dimensions d'une section
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

\text{lettres=shuffle(A,B,C,D,E,F,G,H,I,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)}
text{lettres=A,B,C,D,E,F,G,H,I,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}
\text{D=item(4,\lettres)}

#if defined TARGET_dimension3
 \title{TITRE 3}
%section obtenue en coupant un cone par un plan parallèle à la base.
 \text{list=wims(values v for v=5 to 13)}
 \text{list=shuffle(\list)}
 \integer{f1=max(\list[1],\list[4])}
 \integer{f2=\list[2]}
 \integer{l4=min(\list[1],\list[4])}
 \integer{R=\f1*\list[3]}
 \integer{h=\f2*\l4}
 \integer{H=\f1*\f2}
 \integer{r=\R*\h/\H}
 \text{nature=randitem(parallèle à sa base,perpendiculaire à son axe de révolution)}
 \text{enonce1=\(\mathcal{C}) est un cône de sommet \(\A) dont la base est un disque de rayon \(\R cm). \(\B) est le point de l'axe de révolution de \(\mathcal{C}) tel que \(\A\B = \h cm). On coupe le cône par un plan \nature et passant par le point \(\B). La section plane obtenue est un cercle. Sachant que la hauteur du cône est de \(\H cm), quel est le rayon du cercle obtenu}
 \integer{rep=\r}
 \text{reponse=Le rayon de la section plane mesure}
#endif

#if defined TARGET_dimension4
 \title{TITRE 4}
%section obtenue en coupant une pyramide à base carrée par un plan parallèle à la base.
 \text{list=wims(values v for v=5 to 13)}
 \text{list=shuffle(\list)}
 \integer{f1=max(\list[1],\list[4])}
 \integer{f2=\list[2]}
 \integer{l4=min(\list[1],\list[4])}
 \integer{R=\f1*\list[3]}
 \integer{h=\f2*\l4}
 \integer{H=\f1*\f2}
 \integer{r=\R*\h/\H}
 \text{enonce1=\(\mathcal{S}) est une pyramide de sommet \(\A) dont la base est un carré dont les côtés mesurent \(\R cm). \(\B) est un point de la hauteur de \(\mathcal{S}) tel que \(\A\B = \h cm). On coupe la pyramide par un plan parallèle à sa base et passant par le point \(\B). La section plane obtenue est un carré. Sachant que la hauteur de la pyramide est de \(\H cm), quelle est la longueur des côtés de la section plane obtenue}
 \integer{rep=\r}
 \text{reponse=Les côtés mesurent }
#endif

#if defined TARGET_dimension5
 \title{TITRE 5}
%section obtenue en coupant une sphère.
 \text{list=wims(values v for v=5 to 13)}
 \text{list=shuffle(\list)}
 \integer{u=random(2..6)}
 \integer{v=random(1..\u-1)}
 \integer{r=max(\u^2-\v^2,2*\u*\v)}
 \integer{h=min(\u^2-\v^2,2*\u*\v)}
 \integer{R=(\r^2+\h^2)^(1/2)}
 \text{enonce1=\(\mathcal{S}) est une sphère de rayon \(\R cm) et de centre \(\A). \(\B) est un point de la boule délimitée par la sphère \(\mathcal{S}) tel que \(\A\B = \h  cm). On coupe la sphère par un plan passant par le point \(\B) et perpendiculaire à la droite \((\A\B)). La section plane obtenue est un cercle. Quel est le rayon de ce cercle}
 \integer{rep=\r}
 \text{reponse=Le rayon du cercle mesure}
#endif


\statement{
\enonce1 ?
<br>
<strong>Votre réponse :</strong>
\reponse \embed{r1,12} cm.
}

\reply{réponse}{\rep}{type=numexp}
