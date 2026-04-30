target=rotcentre1,rotcentre2,rotcentre3,rotcentre4,rotcentre5

#include "author.inc"
#define TITRE Centre d'une rotation
#if defined TARGET_rotcentre1
 \title{TITRE 1}
 \text{color=red,blue,yellow,green,purple,grey,sienna,pink}
\text{colorname=rouge,bleue,jaune,verte,violette,grise,marron,rose}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \integer{angle=90}
 \text{dessin=range 0,10,0,10
parallel 0,0,0,10,1,0,10,grey
parallel 0,0,10,0,0,1,10,grey}

 \integer{A=randint(3..6)}
 \integer{ch2=randint(1..3)}
 \integer{good=randint(1,2)}
 \integer{sens=item(\good,-1,1)}
 \integer{B=\A+\sens*\ch2}
 \integer{angle=\angle*\ch2}
 \integer{x0=randint(4..6)}
 \integer{y0=randint(4..6)}
 \text{fignumber=1,2,3,4,1,2,3,4,1,2,3,4}
 \matrix{gdon=0,0,1,0,0,1
-1,0,-2,0,-1,1
-1,-1,-2,-1,-1,-2
0,-1,0,-2,1,-1}
 \integer{f1=item(\A,\fignumber)}
 \text{don=row(\f1,\gdon)}
 \text{dessin=\dessin
flood \x0+\don[1]+0.5,\y0+\don[2]+0.5,\color[1]
flood \x0+\don[3]+0.5,\y0+\don[4]+0.5,\color[1]
flood \x0+\don[5]+0.5,\y0+\don[6]+0.5,\color[1]}
 \integer{f2=item(\B,\fignumber)}
 \text{don=row(\f2,\gdon)}
 \text{dessin=\dessin
flood \x0+\don[1]+0.5,\y0+\don[2]+0.5,\color[2]
flood \x0+\don[3]+0.5,\y0+\don[4]+0.5,\color[2]
flood \x0+\don[5]+0.5,\y0+\don[6]+0.5,\color[2]}
 \text{image=draw(200,200
\dessin)}
 \text{sens=\sens>0?positif:négatif}
 \integer{x=20*\x0}
 \integer{y=200-20*\y0}
 \integer{d=10}
 \text{enonce=Par une rotation de sens \sens et d'angle \angle°, l'image de la figure \colorname[1] est la figure \colorname[2].<br>
  Quel est le centre de cette rotation}
#endif

#if defined TARGET_rotcentre2
 \title{TITRE 2}
 \text{color=red,blue,yellow,green,purple,grey,sienna,pink}
\text{colorname=rouge,bleue,jaune,verte,violette,grise,marron,rose}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \integer{angle=60}
 \text{dessin=range 0,5,0,5
parallel 0,-10,10,10*sqrt(3)-10,0,1,15,grey
parallel 0,15,10,15-10*sqrt(3),0,-1,15,grey
parallel 0,0,5,0,0,0.5,10,grey}

 \integer{A=randint(0..5)*\angle}
 \integer{ch2=randint(2..3)}
 \integer{sens=randitem(-1,1)}
 \integer{angle=\angle*\ch2}
 \integer{B=\A+\sens*\angle}
 \real{y0=randitem(0,0.5)}
 \real{x0=(randitem(3,4,5)+\y0)/sqrt(3)}
 \real{y0=randint(2..3)+\y0}
 \matrix{don=randrow(30,4/3
30,2/3)}
 \text{dessin=\dessin
flood \x0+\don[2]*cos((\don[1]+\A)*pi/180),\y0+\don[2]*sin((\don[1]+\A)*pi/180),\color[1]
flood \x0+\don[2]*cos((\don[1]+\B)*pi/180),\y0+\don[2]*sin((\don[1]+\B)*pi/180),\color[2]}
 \text{image=draw(300,300
\dessin)}
 \text{sens=\sens>0?positif:négatif}
 \integer{x=60*\x0}
 \integer{y=300-60*\y0}
 \integer{d=10}
 \text{enonce=Sur la figure ci-contre, tous les triangles sont équilatéraux.<br>
  Par une rotation de sens \sens et d'angle \angle°, l'image de la figure \colorname[1] est la figure \colorname[2].<br>
  Quel est le centre de cette rotation}
#endif

#if defined TARGET_rotcentre3
 \title{TITRE 3}
 \text{color=red,blue,yellow,green,purple,grey,sienna,pink}
\text{colorname=rouge,bleue,jaune,verte,violette,grise,marron,rose}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \integer{angle=60}
 \text{dessin=range 0,5,0,5
parallel 0,-10,10,10*sqrt(3)-10,0,1,15,grey
parallel 0,15,10,15-10*sqrt(3),0,-1,15,grey
parallel 0,0,5,0,0,0.5,10,grey}

 \integer{A=randint(0..5)*\angle}
 \integer{ch2=1}
 \integer{sens=randitem(-1,1)}
 \integer{angle=\angle*\ch2}
 \integer{B=\A+\sens*\angle}
 \real{y0=randitem(0,0.5)}
 \real{x0=(randitem(3,4,5)+\y0)/sqrt(3)}
 \real{y0=randint(2..3)+\y0}
 \matrix{don=30,2/3}
 \text{dessin=\dessin
flood \x0+\don[2]*cos((\don[1]+\A)*pi/180),\y0+\don[2]*sin((\don[1]+\A)*pi/180),\color[1]
flood \x0+\don[2]*cos((\don[1]+\B)*pi/180),\y0+\don[2]*sin((\don[1]+\B)*pi/180),\color[2]}
 \text{image=draw(300,300
\dessin)}
 \text{sens=\sens>0?positif:négatif}
 \integer{x=60*\x0}
 \integer{y=300-60*\y0}
 \integer{d=10}
 \text{enonce=Sur la figure ci-contre, tous les triangles sont équilatéraux.<br>
 Par une rotation de sens \sens et d'angle \angle°, l'image de la figure \colorname[1] est la figure \colorname[2].<br>
  Quel est le centre de cette rotation}
#endif

#if defined TARGET_rotcentre4
 \title{TITRE 4}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleue,jaune,verte,violette}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{don=0,0,0,30,20,30,20,-30,-30,-30}
 \integer{x0=randint(90..110)}
 \integer{y0=randint(90..110)}
 \integer{r=0}
 \integer{nb=items(\don)/2}
 \real{A0=random(-pi..pi)}
 \real{A1=random(-pi..pi)}
 \real{A2=random(pi/4..3*pi/4)*randitem(1,-1)}
 \text{Image1=}
 \text{Image2=}
 \for{k=1 to \nb}{
  \real{N=sqrt((\don[2*\k-1])^2+(\don[2*\k])^2)}
  \if{\N!=0}{
   \real{tmpA=arccos(\don[2*\k-1]/\N)}
   \real{tmpA=\don[2*\k]<0?-\tmpA}
   \real{tmpx1=\x0+\r*cos(\A1)+\N*cos(\tmpA+\A0+\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)+\N*sin(\tmpA+\A0+\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)+\N*cos(\tmpA+\A0+\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)+\N*sin(\tmpA+\A0+\A1+\A2)}
  }{
   \real{tmpx1=\x0+\r*cos(\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)}
  }
  \text{Image1=wims(append item \tmpx1,\tmpy1 to \Image1)}
  \text{Image2=wims(append item \tmpx2,\tmpy2 to \Image2)}
 }
 \text{image=draw(200,200
poly \color[1],\Image1
poly \color[2],\Image2)}
 \text{enonce=Cliquer sur le centre de la rotation permettant de passer de la figure \colorname[1] à la figure \colorname[2]}
 \integer{x=\x0}
 \integer{y=\y0}
 \integer{d=10}
#endif

#if defined TARGET_rotcentre5
 \title{TITRE 5}
 \text{color=red,blue,yellow,green,purple}
\text{colorname=rouge,bleue,jaune,verte,violette}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{don=0,0,0,30,20,30,20,-30,-30,-30}
 \integer{x0=randint(90..110)}
 \integer{y0=randint(90..110)}
 \integer{r=randint(20..30)}
 \integer{nb=items(\don)/2}
 \real{A0=random(-pi..pi)}
 \real{A1=random(-pi..pi)}
 \real{A2=random(pi/4..3*pi/4)*randitem(1,-1)}
 \text{Image1=}
 \text{Image2=}
 \for{k=1 to \nb}{
  \real{N=sqrt((\don[2*\k-1])^2+(\don[2*\k])^2)}
  \if{\N!=0}{
   \real{tmpA=arccos(\don[2*\k-1]/\N)}
   \real{tmpA=\don[2*\k]<0?-\tmpA}
   \real{tmpx1=\x0+\r*cos(\A1)+\N*cos(\tmpA+\A0+\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)+\N*sin(\tmpA+\A0+\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)+\N*cos(\tmpA+\A0+\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)+\N*sin(\tmpA+\A0+\A1+\A2)}
  }{
   \real{tmpx1=\x0+\r*cos(\A1)}
   \real{tmpy1=\y0+\r*sin(\A1)}
   \real{tmpx2=\x0+\r*cos(\A1+\A2)}
   \real{tmpy2=\y0+\r*sin(\A1+\A2)}
  }
  \text{Image1=wims(append item \tmpx1,\tmpy1 to \Image1)}
  \text{Image2=wims(append item \tmpx2,\tmpy2 to \Image2)}
 }
 \text{image=draw(200,200
poly \color[1],\Image1
poly \color[2],\Image2)}
 \text{enonce=Cliquer sur le centre de la rotation permettant de passer de la figure \colorname[1] à la figure \colorname[2]}
 \integer{x=\x0}
 \integer{y=\y0}
 \integer{d=20}
#endif


\statement{
  \enonce ?
  <div class="wims_instruction">
  Cliquer sur la figure pour placer le centre.
  </div>
<div class="wimscenter">
 \embed{r1}
</div>}

\answer{}{\image;circle,\x,\y,\d}{type=coord}
