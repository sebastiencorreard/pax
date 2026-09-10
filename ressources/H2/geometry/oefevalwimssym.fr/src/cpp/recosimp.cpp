target=recosimp1 recosimp2 recosimp3 recosimp4 recosimp5

#include "author.inc"
\title{Figure simple et centre de symétrie}

#if defined TARGET_recosimp1
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \text{image=draw(200,200
square 40,40,120,black)}
 }{
  \text{image=draw(200,200
rectangle 40,60,160,140,black)}
 }
 \integer{rep=1}
#endif
#if defined TARGET_recosimp2
  \text{image=draw(200,200
polygon black,30,40,150,40,180,160,60,160)}
 \integer{rep=1}
#endif

#if defined TARGET_recosimp3
  \text{image=draw(200,200
polygon black,60,40,140,40,180,160,20,160)}
 \integer{rep=2}
#endif
#if defined TARGET_recosimp4
 \integer{d=randint(75..120)}
 \text{image=draw(200,200
circle 100,100,\d,black)}
 \integer{rep=1}
#endif
#if defined TARGET_recosimp5
 \integer{d=randint(40..60)}
 \text{image=draw(200,200
polygon black,100,40,100-\d,160,100+\d,160)}
 \integer{rep=2}
#endif

\text{choix=Oui,Non}
\text{rep=item(\rep,\choix)}

\statement{
  La figure ci-dessous possède-t-elle un centre de symétrie ?
<div class="wimscenter"><img src="\image" alt=""></div>}

\choice{}{\rep}{\choix}
