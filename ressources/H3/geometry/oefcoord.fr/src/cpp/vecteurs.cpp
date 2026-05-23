target=vecteurs
\title{Coordonnées d'un vecteur}
\language{fr}
\range{-5..5}
#include "author.inc"
#include "css.inc"
\keywords{vectors}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{XA=random(-10..10)}
\integer{YA=random(-10..10)}
\integer{XB=random(-10..10)}
\integer{YB=random(-10..10)}

\integer{ch=random(1,2)}
\if{\ch=1}{
\text{vect=\overrightarrow{A B}}
\integer{Vx=\XB-\XA}
\integer{Vy=\YB-\YA}
}{
\text{vect=\overrightarrow{B A}}
\integer{Vx=\XA-\XB}
\integer{Vy=\YA-\YB}
}

\statement{Dans le plan muni d'un repère, on considère les points \(A) et \(B)
de coordonnées respectives \((\XA,\YA)) et \((\XB,\YB)).<br>
 <label for="reply1">Les coordonnées du vecteur \(\vect) sont</label> (\embed{r1,3},\embed{r2,3}).}

\answer{Première coordonnée}{\Vx}{type=auto}
\answer{Deuxième coordonnée}{\Vy}{type=auto}
