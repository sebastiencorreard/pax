target=angle1,angle2,angle3,angle4,angle5
#include "author.inc"
#define TITRE Angle
#if defined TARGET_angle1
 \title{TITRE 1}
 \text{name=triangle équilatéral}
 \integer{n=3}
#endif
#if defined TARGET_angle2
 \title{TITRE 2}
 \text{name=carré}
 \integer{n=4}
#endif
#if defined TARGET_angle3
 \title{TITRE 3}
 \text{name=pentagone régulier}
 \integer{n=5}
#endif
#if defined TARGET_angle4
 \title{TITRE 4}
 \text{name=hexagone régulier}
 \integer{n=6}
#endif
#if defined TARGET_angle5
 \title{TITRE 5}
 \text{name=octogone régulier}
 \integer{n=8}
#endif

\text{dessin=slib(polyregulier \n,150,0,1,black,red)}
\text{dessin=draw(150,150
\dessin)}

\statement{
La figure ci-dessous est un \name. Quelle est la mesure, en degré, de ses angles ?
<div class="wimscenter"><img src="\dessin" alt=""></div>
<label for="reply1"><b>Votre réponse :</b></label>
\embed{r1,5} degrés.}

\answer{}{180*(\n-2)/\n}{type=numeric}
