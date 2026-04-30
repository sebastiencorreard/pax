target=polygone1,polygone2,polygone3
#include "author.inc"
#define TITRE Noms des polygones
#if defined TARGET_polygone1
 \title{TITRE 1}
 \integer{number=2}
 \text{name=quadrilatère}
#endif

#if defined TARGET_polygone2
 \title{TITRE 2}
 \integer{number=3}
 \text{name=pentagone}
#endif

#if defined TARGET_polygone3
 \title{TITRE 3}
 \integer{number=4}
 \text{name=hexagone}
#endif

\matrix{point=0,20,40,80,90,40
0,20,20,80,90,60,50,0
0,50,20,70,50,70,60,20,20,0
0,50,20,70,50,70,80,50,60,20,20,0}

\text{image=}
\for{k=1 to 4}{
 \text{don=row(\k,\point)}
 \integer{nb=items(\don)/2}
 \text{val=}
 \text{dessin=}
 \for{j=1 to \nb}{
  \integer{x=randint(\don[2*\j-1]..\don[2*\j-1]+9)}
  \integer{y=randint(\don[2*\j]..\don[2*\j]+9)}
  \text{tmp=circle \x,\y,5,red}
  \text{dessin=wims(append line \tmp to \dessin)}
  \text{val=wims(append item \x,\y to \val)}
 }
 \text{dessin=draw(100,100
range 0,100,0,100
\dessin
poly black,\val)}
\text{dessin=<img src="\dessin" alt="">}
\text{image=wims(append item \dessin to \image)}
}
\text{good=item(\number,\image)}
\text{image=shuffle(\image)}
\integer{number=position(\good,\image)}

\statement{
  Parmi les polygones suivants, lequel est un \name ?
<div class="wims_instruction">
 Cliquer sur l'image correspondante.
</div>
<div class="wimscenter">\embed{r1}</div>}

\answer{Réponse}{\number;\image}{type=click}
