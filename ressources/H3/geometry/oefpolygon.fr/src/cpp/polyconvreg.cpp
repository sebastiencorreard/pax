target=polyconvreg
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{yes}
\precision{100}

\integer{k=random(1..6)}
\integer{n=random(3..15)}
\integer{R=random(1..6)}
\if{\k=1}{
  \text{question=Chaque angle de \(P\)}
  \real{rep=(\n-2)*180/\n}}
\if{\k=2}{
  \text{question=Chaque angle au centre de \(P\) }
  \real{rep=2*180/\n}}
\if{\k=3}{
  \text{question=La longueur de chaque côté de \(P\) }
  \real{rep=2*\R*sin(pi/\n)}}
\if{\k=4}{
  \text{question=L'apothème de \(P\) }
  \real{rep=\R*cos(pi/\n)}}
\if{\k=5}{
  \text{question=L'aire de \(P\) }
  \real{rep=\n*(\R^2)*cos(pi/\n)*sin(pi/\n)}}
\if{\k=6}{
  \text{question=Le périmètre de \(P\) }
  \real{rep=2*\n*\R*sin(pi/\n)}}

\statement{
<div class="wims_question">Dans le plan affine euclidien, on considère
un polygone convexe régulier \(P\) à \(\n\) côtés inscrit dans un cercle de
rayon \(\R \; cm\).
<label for="reply1">\question vaut</label> \embed{reply1,10}.</div>
<div class="wims_instruction">
Les angles sont mesurés en degré, les longueurs en cm et les aires en \(cm^2\).
Vous pouvez utiliser la calculatrice de WIMS en cliquant sur outils
dans la barre de liens. </div>}

\answer{\question vaut}{\rep}{type=numeric}
