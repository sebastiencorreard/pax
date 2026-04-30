target=dimension1,dimension2
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
\text{E=item(5,\lettres)}
\text{F=item(6,\lettres)}
\text{G=item(7,\lettres)}
\text{H=item(8,\lettres)}
\text{I=item(9,\lettres)}
\text{J=item(10,\lettres)}
\text{K=item(11,\lettres)}
\text{L=item(12,\lettres)}

#if defined TARGET_dimension1
 \title{TITRE 1}
%section obtenue en coupant un pavé par un plan parallèle à une face.
 \integer{nL=randint(7..20)}
 \integer{nH=randint(7..20)}
 \integer{P=randint(7..20)}
 \text{donnees=\(\D\A = \nH cm), <br> \(\D\C = \P cm), <br> \(\D\H = \nL cm)}
 \matrix{faces=\A\B\C\D,\nH,\P
\E\F\G\H,\nH,\P
\D\C\G\H,\P,\nL
\A\B\F\E,\P,\nL
\A\E\H\D,\nH,\nL
\B\F\G\C,\nH,\nL}
 \text{face=randrow(\faces)}
 \integer{r1=item(2,\face)}
 \integer{r2=item(3,\face)}
 \text{face=item(1,\face)}
 \integer{rep1=max(\r1,\r2)}
 \integer{rep2=min(\r1,\r2)}
 \text{enonce1=On coupe le parallélépipède rectangle ci-contre par un plan parallèle  à la face \(\face). La section plane obtenue est un rectangle.}
 \integer{l=\nL*10}
 \integer{h=\nH*10}
 \integer{p=\P*5}
 \text{name=pave}
 \text{drawcmd=\name,0.5,\l,\h,\p,,,(\A,\B,\C,\D,\E,\F,\G,\H)}
#endif

#if defined TARGET_dimension2
 \title{TITRE 2}
%section obtenue en coupant un pavé par un plan parallèle à une arête.
 \integer{init=randint(5..15)}
 \integer{P=randint(7..20)}
 \integer{u=random(2..6)}
 \integer{v=random(1..\u-1)}
 \integer{nL=max(\u^2-\v^2,2*\u*\v)}
 \integer{dec=min(\u^2-\v^2,2*\u*\v)}
 \integer{r1=(\dec^2+\nL^2)^(1/2)}
 \integer{dec2=\init+\dec}
 \integer{nH=\dec2+randint(5..15)}
 \text{donnees=\(\D\A = \nH cm), <br> \(\D\C = \P cm), <br> \(\D\H = \nL cm), <br>\(\A\I = \init cm),<br> \(\E\L = \dec2 cm)}
 \integer{rep1=max(\r1,\P)}
 \integer{rep2=min(\r1,\P)}
 \text{enonce1=\(\I) et \(\L) sont respectivements des points des arêtes \([\A\D]) et \([\E\H]).<br>On coupe le parallélépipède rectangle ci-contre par le plan parallèle  à l'arête \([\D\C]) et passant par les points \(\I) et \(\L). La section plane obtenue est un rectangle.}
 \integer{l=\nL*10}
 \integer{h=\nH*10}
 \integer{p=\P*5}
 \text{name=pave}
 \text{drawcmd=\name,0.5,\l,\h,\p,,,(\A,\B,\C,\D,\E,\F,\G,\H)}
#endif

\text{dessin=slib(local/solide \drawcmd)}
\text{tmp=wims(line 1 of \dessin)}
\text{dessin=wims(line 2 to -1 of \dessin)}
\integer{X=item(1,\tmp)}
\integer{Y=item(2,\tmp)}
\text{dessin=\dessin
\dessinadd}

\statement{
<div class="float_left spacer">
\draw{\X,\Y}{\dessin}
</div>

\enonce1<br>
Sachant que :<br>
\donnees,<br>
quelles sont les dimensions de cette section plane ?<br>
\complement

<p><strong>Votre réponse :</strong></p>
<ul><li>
  Longueur :  \embed{r1} cm.
  </li><li>
  Largeur : \embed{r2} cm.
 </li>
</ul>
}

\reply{Longueur}{\rep1}{type=numexp}
\reply{Largeur}{\rep2}{type=numexp}
