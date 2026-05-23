target=para2
\title{Parallélogramme ?}
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
\keywords{parallelogram}
\matrix{nom=A,B,C,D
E,F,G,H
M,N,O,P}
\text{don=randrow(\nom)}
\text{don=shuffle(\don)}
\text{A=item(1,\don)}
\text{B=item(2,\don)}
\text{C=item(3,\don)}
\text{D=item(4,\don)}


\integer{XA=random(-10..10)}
\integer{YA=random(-10..10)}
\integer{XB=random(-10..10)}
\integer{YB=random(-10..10)}
\integer{XC=random(-10..10)}
\integer{YC=random(-10..10)}

\if{(\XB-\XA)*(\YC-\YA)-(\YB-\YA)*(\XC-\XA)=0}
{\integer{XA=1}
\integer{YA=-1}
\integer{XB=3}
\integer{YB=5}
\integer{XC=-2}
\integer{YC=-2}}

\integer{Vx=\XB-\XA}
\integer{Vy=\YB-\YA}
\integer{XD=\XC+\Vx}
\integer{YD=\YC+\Vy}

\integer{ch=random(1..2)}
\if{\ch=1}
{\text{good=Oui}}
{\text{good=Non}
\integer{XD=\XD+(random(1,-1)*random(1..10))}
\integer{YD=\YD+(random(1,-1)*random(1..10))}
}

\statement{Dans le plan muni d'un repère,
on considère les points \(\A), \(\B), \(\C) et \(\D) de coordonnées
 respectives \((\XA,\YA)), \((\XB,\YB)), \((\XC,\YC)) et \((\XD,\YD)).
 Le quadrilatère \(\A \B \D \C) est-il un parallèlogramme ? }

\choice{réponse}{\good}{Oui,Non}
