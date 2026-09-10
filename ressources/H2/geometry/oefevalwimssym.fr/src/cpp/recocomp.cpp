target=recocomp1 recocomp2 recocomp3 recocomp4 recocomp5

#include "author.inc"
\title{Figure et centre de symétrie}

\integer{rep=randint(1..2)}
#if defined TARGET_recocomp1
 \integer{d2=randint(60..90)}
 \integer{d1=\rep=1?\d2:randint(30..45)}
 \text{image=draw(200,200
circle 100,100-\d1/2+1,\d1,black
circle 100,100+\d2/2-1,\d2,black)}
#endif

#if defined TARGET_recocomp2
 \integer{c=70}
 \if{\rep=1}{
  \integer{v=randint(1..2)}
  \if{\v=1}{
   \text{image=draw(200,200
square 100-\c/2,100-\c/2,\c,black
polygon black,100-\c/2,100-\c/2,100,100-\c/2-sqrt(3)/2*\c,100+\c/2,100-\c/2
polygon black,100-\c/2,100+\c/2,100,100+\c/2+sqrt(3)/2*\c,100+\c/2,100+\c/2)}
  }{
   \text{image=draw(200,200
square 100-\c/2,100-\c/2,\c,black
polygon black,100-\c/2,100-\c/2,100-\c/2-sqrt(3)/2*\c,100,100-\c/2,100+\c/2
polygon black,100+\c/2,100-\c/2,100+\c/2+sqrt(3)/2*\c,100,100+\c/2,100+\c/2)}
  }
 }{
  \text{triangle=randrow(polygon black,100-\c/2,100-\c/2,100,100-\c/2-sqrt(3)/2*\c,100+\c/2,100-\c/2
polygon black,100-\c/2,100+\c/2,100,100+\c/2+sqrt(3)/2*\c,100+\c/2,100+\c/2
polygon black,100-\c/2,100-\c/2,100-\c/2-sqrt(3)/2*\c,100,100-\c/2,100+\c/2
polygon black,100+\c/2,100-\c/2,100+\c/2+sqrt(3)/2*\c,100,100+\c/2,100+\c/2)}
  \text{image=draw(200,200
square 100-\c/2,100-\c/2,\c,black
\triangle)}
}
#endif

#if defined TARGET_recocomp3
 \if{\rep=2}{
  \text{image=draw(200,200
circle 100,100,160,black
polygon black,100-sqrt(3)/2*80,60,100+sqrt(3)/2*80,60,100,180)}
 }{
  \text{image=draw(200,200
arc 100,80,150,150,180,360,black
segment 25,80,175,80,black
segment 25,120,175,120,black
arc 100,120,150,150,0,180,black)}
 }
#endif

#if defined TARGET_recocomp4
 \integer{h=randint(50..80)}
 \if{\rep=1}{
  \text{image=draw(200,200
polygon black,20,100-\h,20,100,100,100
polygon black,180,100+\h,180,100,100,100)}
 }{
  \integer{sg=randitem(-1,1)}
  \text{image=draw(200,200
polygon black,20,100+\sg*\h,20,100,100,100
polygon black,180,100+\sg*\h,180,100,100,100)}
 }
#endif

#if defined TARGET_recocomp5
 \integer{h=\rep=2?200/8+1:200/9+1}
 \text{com=fsquare 1,1,\h,black
fsquare 2,2,\h,black
fsquare 2,3,\h,black
fsquare 3,4,\h,black
fsquare 4,4,\h,black
fsquare 5,3,\h,black
fsquare 5,2,\h,black
fsquare 6,1,\h,black
fsquare 2,5,\h,black
fsquare 5,5,\h,black}
 \if{\rep=2}{
  \text{image=draw(200,200
range 0,8,8,0
\com
fsquare 1,6,\h,black
fsquare 6,6,\h,black)}
 }{
  \text{image=draw(200,200
range -0.5,8.5,9,0
\com
fsquare 2,6,\h,black
fsquare 5,6,\h,black
fsquare 1,7,\h,black
fsquare 6,7,\h,black)}
 }
#endif

\text{choix=Oui,Non}
\text{rep=item(\rep,\choix)}

\statement{
 La figure ci-dessous possède-t-elle un centre de symétrie ?
<div class="wimscenter"><img src="\image" alt=""></div>}

\choice{}{\rep}{\choix}
