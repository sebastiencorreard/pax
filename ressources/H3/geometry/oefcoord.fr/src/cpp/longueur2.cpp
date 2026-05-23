target=longueur2
\title{Longueur d'un segment (graphique)}
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

\integer{XA=random(-4..4)}
\integer{YA=random(-4..4)}
\integer{XB=random(-4..4)}
\integer{YB=random(-4..4)}

\ifval{(\XA-\XB)^2+(\YA-\YB)^2=0}{
\integer{XA=2}
\integer{YA=4}
\integer{XB=-3}
\integer{YB=1}}

\text{nom=dixième,centième,millième}
\integer{ch=random(1..3)}
\text{prec=item(\ch,\nom)}
\integer{long=((\XA-\XB)^2+(\YA-\YB)^2)^(1/2)*10^(\ch)}
\real{long=\long/(10^(\ch))}

\text{dessin=wims(record 2 of src/graph.don)}
\integer{xptA=150+(\XA*30)}
\integer{yptA=150-(\YA*30)}
\integer{xptB=150+(\XB*30)}
\integer{yptB=150-(\YB*30)}
\if{\XA>\XB}{
\integer{difA=0}
\integer{difB=-10}
}{
\integer{difB=0}
\integer{difA=-10}
}
\text{dessin=\dessin
segment \xptA,\yptA,\xptB,\yptB,red
text black,\xptA+\difA,\yptA,medium,\A
text black,\xptB+\difB,\yptB,medium,\B}

\statement{Dans le plan muni d'un repère orthonormé,
on considère les points \(\A) et \(\B)  représentés ci-dessous :
<div class="wimscenter">
\draw{300,300}{\dessin}
</div>
Quelle est la longueur du segment \([\A\B]) au \prec près ?
<br><span class="ans">Votre réponse</span> :
  <label for="reply1">\(\A\B=)</label>\embed{r1,5} unité}

\answer{longueur}{\long}{type=algexp}
