target=anglecentre1,anglecentre2,anglecentre3,anglecentre4,anglecentre5

#include "author.inc"
#define TITRE Angle au centre
#if defined TARGET_anglecentre1
 \title{TITRE 1}
 \text{name=triangle équilatéral}
 \integer{n=3}
#endif

#if defined TARGET_anglecentre2
 \title{TITRE 2}
 \text{name=carré}
 \integer{n=4}
#endif
#if defined TARGET_anglecentre3
 \title{TITRE 3}
 \text{name=pentagone régulier}
 \integer{n=5}
#endif
#if defined TARGET_anglecentre4
 \title{TITRE 4}
 \text{name=hexagone régulier}
 \integer{n=6}
#endif
#if defined TARGET_anglecentre5
 \title{TITRE 5}
 \text{name=octogone régulier}
 \integer{n=8}
#endif

\text{dessin=slib(polyregulier \n,150,1,1,black,red,1)}
\text{dessin=draw(150,150
\dessin)}

\statement{
  La figure ci-dessous est un \name inscrit dans le cercle tracé. Quelle est la mesure,
  en degré, de l'angle au centre marqué ?
<div class="wimscenter"><img src="\dessin" alt=""></div>
<label for="reply1"><b>Votre réponse :</b></label>:
\embed{r1,5} degrés.}

\answer{}{360/\n}{type=numeric}
