target=milieu
\title{Milieu d'un segment (calcul)}
\language{fr}
\range{-5..5}
#include "author.inc"
#include "css.inc"
\computeanswer{no}
\format{html}
\precision{10000}
\keywords{midpoint}

\text{choix=A,B,C,D,E,F,G,H}
\text{choix=shuffle(\choix)}
\text{A=item(1,\choix)}
\text{B=item(2,\choix)}

\integer{XA=random(-10..10)}
\integer{YA=random(-10..10)}
\integer{XB=random(-10..10)}
\integer{YB=random(-10..10)}

\ifval{(\XA-\XB)^2+(\YA-\YB)^2=0}{
\integer{XA=2}
\integer{YA=5}
\integer{XB=-3}
\integer{YB=1}}

\real{XC=(\XA+\XB)/2}
\real{YC=(\YA+\YB)/2}

\statement{Dans le plan muni d'un repère orthonormé,
on considère les points \(\A) et \(\B) de coordonnées
respectives \((\XA,\YA)) et \((\XB,\YB)).
<label for="reply1">Les coordonnées du milieu du segment \([\A\B])</label> sont :
 (\embed{r1,3},\embed{r2,3})}

\answer{Première coordonnée}{\XC}{type=auto}
\answer{Deuxième coordonnée}{\YC}{type=auto}
