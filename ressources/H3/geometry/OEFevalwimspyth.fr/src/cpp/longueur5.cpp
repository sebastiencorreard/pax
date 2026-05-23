target=longueur5
\title{Calculer une longueur 5}
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}

\integer{u=random(2..3)}
\integer{v=random(1..\u-1)}
\integer{sm=max(\u^2-\v^2,2*\u*\v)}
\integer{mn=min(\u^2-\v^2,2*\u*\v)}
\integer{sn=(\mn^2+\sm^2)^(1/2)}

\integer{xmax=(\sm+2)*20}
\integer{ymax=(\mn+2)*20}

\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L,M,O,P,R,S)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}
\text{D=item(4,\lettres)}

 \text{s=20,20,20+20*\sm,20,20,20+20*\mn}
 \text{ts=}
 \text{M=\xmax,\ymax,\xmax,\ymax,\xmax,\ymax}
 \text{f=(m-25)/(m-40)*(x)+(10-20*(m-25)/(m-40))}
 \for{k=1 to 6}{
  \text{tmp=simplify(evalue(\f,x=\s[\k],m=\M[\k]))}
  \text{ts=wims(append item \tmp to \ts)}
 }
 \text{dessin=triangle \s,black
text black,\ts[1],\ts[2],medium,\A
text black,\ts[3],\ts[4],medium,\B
text black,\ts[5],\ts[6],medium,\C}

\text{name=slib(lang/fname fr,boy)}
\text{inc=\B\C}
\text{enonce=\name a dessiné le triangle ci-contre sur une feuille de papier quadrillé.
 Quelle est la longueur (en carreaux) du segment [\B\C]}
 \integer{rep=\sn}
 \text{dessin=parallel 0,0,\xmax,0,0,20,\ymax/20+1,grey
parallel 0,0,0,\ymax,20,0,\xmax/20+1,grey
\dessin}

\text{dessin=\dessin!=?draw(\xmax,\ymax
\dessin)}

\statement{
\enonce
 <div class="wimscenter">
  <img src="\dessin" alt="">
</div>}

\answer{\inc}{\rep}{type=numexp}
