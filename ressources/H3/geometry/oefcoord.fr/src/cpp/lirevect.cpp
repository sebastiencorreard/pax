target=lirevect
\title{Lire les coordonnées d'un vecteur}
\language{fr}
\range{-5..5}
#include "author.inc"
#include "css.inc"
\computeanswer{no}
\format{html}
\keywords{vectors}
\precision{10000}

\integer{XA=random(-4..4)}
\integer{YA=random(-4..4)}
\integer{XB=random(-4..4)}
\integer{YB=random(-4..4)}
\if{\XA=\XB and \YA=\YB}{
\integer{XA=2}
\integer{YA=3}
\integer{XB=1}
\integer{YB=-2}}

\text{dessin=wims(record 2 of src/graph.don)}

\integer{xpt1=150+(\XA*30)}
\integer{ypt1=150-(\YA*30)}
\integer{xpt2=150+(\XB*30)}
\integer{ypt2=150-(\YB*30)}
\text{dessin=wims(record 2 of src/graph.don)}
\text{dessin=\dessin
arrow \xpt1,\ypt1,\xpt2,\ypt2,10,red}

\integer{Vx=\XB-(\XA)}
\integer{Vy=\YB-(\YA)}


\statement{Quelles sont les coordonnées du vecteur du plan dessiné dans le repère ci-dessous ?
<div class="wimscenter">
\draw{300,300}{\dessin}
</div>
<br><span class="ans"><label for="reply1">Votre réponse</label></span> :
(\embed{r1,3},\embed{r2,3})}

\answer{Première coordonnée}{\Vx}{type=auto}
\answer{Deuxième coordonnée}{\Vy}{type=auto}
