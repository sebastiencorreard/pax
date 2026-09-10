target=cross

#include "header.inc"

\title{Cross}

\integer{coef=random(40,50,60,80,120,150,160,180)}
\text{sh=shuffle(3,4)}
\integer{AB=\sh[1]*\coef}
\integer{AC=\sh[2]*\coef}
\integer{BC=5*\coef}
\integer{deind=random(1,2)}
\text{nameAE=item(\deind,AE,AD)}
\integer{ABAC=item(\deind,\AB,\AC)}
\integer{ratio=random(2,3,4)}
\integer{AE=\ABAC*\ratio}
\integer{tot=\AB+\BC*(\ratio+1)+\AC*(\ratio-1)}

\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-8">
    Des élèves participent à un cross. Avant le départ, un plan leur a été remis
   (les dimensions ne sont pas respectées).
   <p>
    On peut lire les indications suivantes&nbsp;:
   </p>
   <div class="wimscenter">
     AB = \AB m ; AC = \AC m ; \nameAE = \AE m.
   </div>
   L'angle A est droit. Les droites (BC) et (DE) sont parallèles.
   <p>
    Quelle est la longueur du parcours ABCDE ?
   </p>
   <div class="wimscenter">\embed{r1,6} m</div>
  </div>
  <div class="cell small-12 medium-6 large-4">
     <img src="\imagedir/cross.png" alt="la carte">
  </div>
</div>
}

\reply{La longueur}{\tot}{type=default}
