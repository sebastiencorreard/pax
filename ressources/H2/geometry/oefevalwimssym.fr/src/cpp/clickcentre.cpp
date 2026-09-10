target=clickcentre1 clickcentre2 clickcentre3 clickcentre4 clickcentre5

#include "author.inc"
#define TITRE Centre de symétrie d'une figure

\text{name_enonce=Cliquez avec la souris à l'emplacement du centre
  de symétrie de la figure suivante&nbsp;}
\title{TITRE}
\integer{tx=randint(10..40)}
\integer{ty=randint(10..40)}

#if defined TARGET_clickcentre1
 \text{dessin=square \tx,\ty,300,black
square \tx+50,\ty+50,200,black
fsquare \tx,\ty,50,red
fsquare \tx+250,\ty,50,red
fsquare \tx,\ty+250,50,red
fsquare \tx+250,\ty+250,50,red}
 \integer{x=\tx+150}
 \integer{y=\ty+150}
 \integer{d=20}
#endif
#if defined TARGET_clickcentre2
 \text{dessin=linewidth 2
segment \tx+125,\ty+100,\tx+125,\ty+300,black
polygon black,\tx+75,\ty+120,\tx+125,\ty+170,\tx+125,\ty+230,\tx+75,\ty+280
polygon black,\tx+175,\ty+120,\tx+125,\ty+170,\tx+125,\ty+230,\tx+175,\ty+280}
 \integer{x=\tx+125}
 \integer{y=\ty+200}
 \integer{d=20}
#endif
#if defined TARGET_clickcentre3
 \integer{c1=randint(50..100)}
 \text{dessin=linewidth 2
polygon black,\tx+1.5*\c1,\ty,\tx+2*\c1,\ty+\c1,\tx+3*\c1,\ty+1.5*\c1,\tx+2*\c1,\ty+2*\c1,\tx+1.5*\c1,\ty+3*\c1,\tx+\c1,\ty+2*\c1,\tx,\ty+1.5*\c1,\tx+\c1,\ty+\c1}
 \integer{x=\tx+1.5*\c1}
 \integer{y=\ty+1.5*\c1}
 \integer{d=20}
#endif
#if defined TARGET_clickcentre4
 \integer{u=randint(75..150)}
 \integer{w=2*randint(100..150)}
 \integer{v=randint(10..150)}
 \text{dessin=linewidth 2
polygon black,\tx,\ty,\tx+\u,\ty,\tx+\v,\ty+\w,\tx+\u+\v,\ty+\w}
 \integer{x=\tx+(\u+\v)/2}
 \integer{y=\ty+\w/2}
 \integer{d=20}
#endif
#if defined TARGET_clickcentre5
 \integer{u=2*randint(50..75)}
 \text{a=0,180;
180,0}
 \text{b=shuffle(1,2)}
 \text{s=10,-10}
 \text{color=randitem(green,red,yellow,pink,brown,grey)}
 \text{dessin=linewidth 2
segment \tx,\ty+150,\tx+2*\u,\ty+150,black
arc \tx+\u/2,\ty+150,\u,\u,\a[\b[1];1],\a[\b[1];2],black
arc \tx+3*\u/2,\ty+150,\u,\u,\a[\b[2];1],\a[\b[2];2],black
fill \tx+\u/2,\ty+150+\s[\b[1]],\color
fill \tx+3*\u/2,\ty+150+\s[\b[2]],\color
}
 \integer{x=\tx+\u}
 \integer{y=\ty+150}
 \integer{d=20}
#endif

\text{image=draw(400,400
\dessin)}

\statement{
  \name_enonce
<div class="wimscenter">\embed{r1,400x400}</div>}

\answer{}{\image;circle,\x,\y,\d}{type=coord}
