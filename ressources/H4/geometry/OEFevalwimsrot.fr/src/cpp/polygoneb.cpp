target=polygone4,polygone5,polygone6
#include "author.inc"
#define TITRE Noms des polygones
#if defined TARGET_polygone4
 \title{TITRE 4}
 \text{don=0,20,20,80,90,60,50,0}
 \text{name=Quadrilatère}
#endif

#if defined TARGET_polygone5
 \title{TITRE 5}
 \text{don=0,50,20,70,50,70,60,20,20,0}
 \text{name=Pentagone}
#endif

#if defined TARGET_polygone6
 \title{TITRE 6}
 \text{don=0,50,20,70,50,70,80,50,60,20,20,0}
 \text{name=Hexagone}
#endif

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

\statement{
  Quel est le nom du polygone ci-dessous ?
<div class="wimscenter"><img src="\dessin" alt=""></div>}

\answer{Réponse}{\name}{type=nocase}
