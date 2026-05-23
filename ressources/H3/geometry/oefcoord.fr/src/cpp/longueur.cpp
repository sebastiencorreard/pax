target=longueur
\title{Longueur d'un segment (calcul)}
\language{fr}
\range{-5..5}
#include "author.inc"
#include "css.inc"
\computeanswer{no}
\format{html}
\keywords{length}
\precision{10000}

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

\text{nom=dixième,centième,millième}
\integer{ch=random(1..3)}
\text{prec=item(\ch,\nom)}
\integer{long=((\XA-\XB)^2+(\YA-\YB)^2)^(1/2)*10^(\ch)}
\real{long=\long/(10^(\ch))}

\statement{Dans le plan muni d'un repère orthonormé,
on considère les points \(\A) et \(\B) de coordonnées respectives
 \((\XA,\YA)) et \((\XB,\YB)).
 Quelle est la longueur du segment \([\A\B]) au \prec près ?
<br><span class="ans">Votre réponse</span> :
  <label for="reply1">\(\A\B=)</label>\embed{r1,5} unité}

\answer{longueur}{\long}{type=algexp}
