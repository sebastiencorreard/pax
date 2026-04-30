target=rotation1,rotation2,rotation3,rotation4,rotation5
#include "author.inc"
#define TITRE Identifier une rotation
#if defined TARGET_rotation1
 \title{TITRE 1}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleue,jaune,verte,violette}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{don=0,0,0,30,20,30,20,-30,-30,-30}
 \integer{x0=randint(140..160)}
 \integer{y0=randint(140..160)}
 \integer{r=random(60..70)}
 \integer{nb=items(\don)/2}
 \real{A0=random(-pi..pi)}
 \real{A1=random(-pi..pi)}
 \real{A2=pi}
 \text{Image1=}
 \text{Image2=}
 \integer{rep=randitem(1,2,2,2)}
 \text{A3=pi*(\rep-1)}
 \for{k=1 to \nb}{
  \real{N=sqrt((\don[2*\k-1])^2+(\don[2*\k])^2)}
  \if{\N!=0}{
   \real{tmpA=arccos(\don[2*\k-1]/\N)}
   \real{tmpA=\don[2*\k]<0?-\tmpA}
   \real{tmpx1=\x0+\r*cos(\A1)+\N*cos(\tmpA+\A0+\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)+\N*sin(\tmpA+\A0+\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)+\N*cos(\tmpA+\A0+\A1+\A2+\A3)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)+\N*sin(\tmpA+\A0+\A1+\A2+\A3)}
  }{
   \real{tmpx1=\x0+\r*cos(\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)}
  }
  \text{Image1=wims(append item \tmpx1,\tmpy1 to \Image1)}
  \text{Image2=wims(append item \tmpx2,\tmpy2 to \Image2)}
 }
 \text{image=draw(300,300
poly \color[1],\Image1
poly \color[2],\Image2)}
 \text{enonce=Existe-il une rotation telle que l'image de la figure \colorname[1] soit la figure \colorname[2]}
#endif

#if defined TARGET_rotation2
 \title{TITRE 2}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleue,jaune,verte,violette}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{don=0,0,0,30,20,30,20,-30,-30,-30}
 \integer{x0=randint(140..160)}
 \integer{y0=randint(140..160)}
 \integer{r=randint(40..60)}
 \integer{nb=items(\don)/2}
 \real{A0=0}
 \real{A1=random(-pi..pi)}
 \real{A2=pi}
 \text{Image1=}
 \text{Image2=}
 \integer{rep=randitem(1,2,2,2)}
 \text{SG=item(\rep,1,-1)}
 \for{k=1 to \nb}{
  \real{N=sqrt((\don[2*\k-1])^2+(\don[2*\k])^2)}
  \if{\N!=0}{
   \real{tmpA=arccos(\don[2*\k-1]/\N)}
   \real{tmpA=\don[2*\k]<0?-\tmpA}
   \real{tmpx1=\x0+\r*cos(\A1)+\N*cos(\tmpA+\A0+\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)+\N*sin(\tmpA+\A0+\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)+\N*cos(\SG*\tmpA+\A0+\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)+\N*sin(\SG*\tmpA+\A0+\A1+\A2)}
  }{
   \real{tmpx1=\x0+\r*cos(\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)}
  }
  \text{Image1=wims(append item \tmpx1,\tmpy1 to \Image1)}
  \text{Image2=wims(append item \tmpx2,\tmpy2 to \Image2)}
 }
 \text{image=draw(300,300
poly \color[1],\Image1
poly \color[2],\Image2)}
 \text{enonce=Existe-il une rotation telle que l'image de la figure \colorname[1] soit la figure \colorname[2]}
#endif

#if defined TARGET_rotation3
 \title{TITRE 3}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleu,jaune,vert,violet}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \integer{x0=150}
 \integer{y0=150}
 \integer{r1=randint(40..70)}
 \integer{r2=randint(110..140)}
 \real{A1=random(-pi..pi)}
 \real{A2=random(1,-1)*random(pi/3..2*pi/3)}
 \integer{rep=randint(1..2)}
 \text{r=\rep=2?shuffle(\r1,\r2):randrow(\r1,\r1
\r2,\r2)}
 \text{image=draw(300,300
fcircle \x0,\y0,5,black
text black,\x0,\y0,medium,0
circle \x0,\y0,2*\r1,black
circle \x0,\y0,2*\r2,black
fcircle \x0+\r[1]*cos(\A1),\x0+\r[1]*sin(\A1),10,\color[1]
fcircle \x0+\r[2]*cos(\A1+\A2),\x0+\r[2]*sin(\A1+\A2),10,\color[2])}
 \text{enonce=Existe-il une rotation de centre O telle que l'image du point \colorname[1] soit le point \colorname[2]}
#endif

#if defined TARGET_rotation4
 \title{TITRE 4}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleue,jaune,verte,violette}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{don=0,0,0,30,20,30,20,-30,-30,-30}
 \integer{x0=randint(140..160)}
 \integer{y0=randint(140..160)}
 \integer{r=random(60..70)}
 \integer{nb=items(\don)/2}
 \real{A0=random(-pi..pi)}
 \real{A1=random(-pi..pi)}
 \real{A2=pi}
 \text{Image1=}
 \text{Image2=}
 \integer{rep=randitem(1,2,2,2)}
 \real{N2=1+(\rep-1)*randint(4..7)/10}
 \for{k=1 to \nb}{
  \real{N=sqrt((\don[2*\k-1])^2+(\don[2*\k])^2)}
  \if{\N!=0}{
   \real{tmpA=arccos(\don[2*\k-1]/\N)}
   \real{tmpA=\don[2*\k]<0?-\tmpA}
   \real{tmpx1=\x0+\r*cos(\A1)+\N*cos(\tmpA+\A0+\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)+\N*sin(\tmpA+\A0+\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)+\N2*\N*cos(\tmpA+\A0+\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)+\N2*\N*sin(\tmpA+\A0+\A1+\A2)}
  }{
   \real{tmpx1=\x0+\r*cos(\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)}
  }
  \text{Image1=wims(append item \tmpx1,\tmpy1 to \Image1)}
  \text{Image2=wims(append item \tmpx2,\tmpy2 to \Image2)}
 }
 \text{image=draw(300,300
poly \color[1],\Image1
poly \color[2],\Image2)}
 \text{enonce=Existe-il une rotation telle que l'image de la figure \colorname[1] soit la figure \colorname[2]}
#endif


#if defined TARGET_rotation5
 \title{TITRE 5}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleu,jaune,vert,violet}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \integer{x0=150}
 \integer{y0=150}
 \integer{r1=randint(40..70)}
 \integer{r2=randint(110..140)}
 \real{A1=random(-pi..pi)}
 \real{A2=random(1,-1)*random(pi/3..2*pi/3)}
 \integer{rep=1}
 \text{r=shuffle(\r1,\r2)}
 \text{image=draw(300,300
circle \x0,\y0,2*\r1,black
circle \x0,\y0,2*\r2,black
fcircle \x0+\r[1]*cos(\A1),\x0+\r[1]*sin(\A1),10,\color[1]
fcircle \x0+\r[2]*cos(\A1+\A2),\x0+\r[2]*sin(\A1+\A2),10,\color[2])}
 \text{enonce=Existe-il une rotation telle que l'image du point \colorname[1] soit le point \colorname[2]}
#endif

\text{list=Oui,Non}
\text{good=item(\rep,\list)}

\statement{\enonce ?
<div class="wimscenter"> <img src="\image" alt=""></div>}

\choice{}{\good}{Oui,Non}
