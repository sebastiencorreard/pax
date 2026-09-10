target=isocele

#include "header.inc"

\title{Triangle isocèle}

\text{sommet=random(A,B,C)}
\integer{a=random(95..175)}
\integer{r=2*\a-180}

\statement{
  Dans un triangle ABC isocèle de sommet \sommet, soit I le point commun des
  bissectrices des angles B et C. <p>
  L'angle BIC vaut \a degrés, combien vaut l'angle A ?
\embed{r1,3} degrés.
</p>
}

\reply{L'angle A}{\r}

