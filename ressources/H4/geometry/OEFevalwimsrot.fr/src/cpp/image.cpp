target=image1,image2,image3,image4,image5
#include "author.inc"
#define TITRE Image d'un point
\text{lettres=shuffle(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,R,S,T)}
\text{P=\lettres[1]}
\text{O=\lettres[2]}

#if defined TARGET_image1
 \title{TITRE 1}
 \integer{A0=randint(1..4)}
 \integer{A1=randint(1,-1)}
 \integer{angle=90}
 \integer{x0=randint(4..6)}
 \integer{y0=randint(4..6)}
 \integer{rmax1=item(\A0,9-\y0,\x0-1,\y0-1,9-\x0)}
 \integer{rmax2=item(\A0+\A1+1,9-\x0,9-\y0,\x0-1,\y0-1,9-\x0,9-\y0)}
 \integer{r=randint(2..min(\rmax1,\rmax2))}
 \text{dessin=range 0,10,0,10
parallel 0,0,0,10,1,0,10,grey
parallel 0,0,10,0,0,1,10,grey
circle \x0,\y0,4,black
text black,\x0-0.1,\y0-0.2,medium,\O
circle \x0+\r*cos(\A0*pi/2),\y0+\r*sin(\A0*pi/2),4,black
text black,\x0+\r*cos(\A0*pi/2)-0.1,\y0+\r*sin(\A0*pi/2)-0.2,medium,\P}
 \text{image=draw(200,200
\dessin)}
 \text{sens=\A1>0?positif:négatif}
 \integer{x=20*(\x0+\r*cos((\A0+\A1)*pi/2))}
 \integer{y=200-20*(\y0+\r*sin((\A0+\A1)*pi/2))}
 \integer{d=5}
 \text{enonce=Quelle est l'image de \P par la rotation de sens \sens, de centre \O et d'angle \angle°}
#endif

#if defined TARGET_image2
 \title{TITRE 2}
 \integer{angle=60}
 \integer{A0=randint(1..6)}
 \integer{sens=randitem(-1,1)}
 \integer{A1=randint(1..2)}
 \integer{angle=\angle*\A1}
 \integer{A1=\sens*\A1}
 \real{y0=randitem(0,0.5)}
 \real{x0=(randitem(3,4,5)+\y0)/sqrt(3)}
 \real{y0=randint(2..3)+\y0}
\text{calcmax=2*(5-\y0)-1,2*(5-\y0)-1,floor(\x0*sqrt(3)-0.5),2*\y0-1,2*\y0-1,floor((5-\x0)*sqrt(3)-0.5)}
 \real{rmax1=item(\A0,\calcmax)}
 \real{rmax2=item(\A0+\A1+6,\calcmax,\calcmax,\calcmax)}
 \real{r=randint(2..min(\rmax1,\rmax2))}
 \text{dessin=range 0,5,0,5
parallel 0,-10,10,10*sqrt(3)-10,0,1,15,grey
parallel 0,15,10,15-10*sqrt(3),0,-1,15,grey
parallel 0,0,5,0,0,0.5,10,grey
circle \x0,\y0,4,black
text black,\x0-0.05,\y0-0.05,medium,\O
circle \x0+\r/sqrt(3)*cos(\A0*pi/3),\y0+\r/sqrt(3)*sin(\A0*pi/3),4,black
text black,\x0+\r/sqrt(3)*cos(\A0*pi/3)-0.05,\y0+\r/sqrt(3)*sin(\A0*pi/3)-0.05,medium,\P}
 \text{image=draw(300,300
\dessin)}
 \text{sens=\A1>0?positif:négatif}
 \integer{x=60*(\x0+\r/sqrt(3)*cos((\A0+\A1)*pi/3))}
 \integer{y=300-60*(\y0+\r/sqrt(3)*sin((\A0+\A1)*pi/3))}
 \integer{d=10}
 \text{enonce=Sur la figure ci-contre, tous les triangles sont équilatéraux.<br>
  Quelle est l'image de \P par la rotation de sens \sens, de centre \O et d'angle \angle°}
#endif

#if defined TARGET_image3
 \title{TITRE 3}
 \integer{angle=60}
 \integer{A0=randint(1..6)}
 \integer{sens=randitem(-1,1)}
 \integer{A1=randint(4..5)}
 \integer{angle=\angle*\A1}
 \integer{A1=\sens*\A1}
 \real{y0=randitem(0,0.5)}
 \real{x0=(randitem(3,4,5)+\y0)/sqrt(3)}
 \real{y0=randint(2..3)+\y0}
\text{calcmax=2*(5-\y0)-1,2*(5-\y0)-1,floor(\x0*sqrt(3)-0.5),2*\y0-1,2*\y0-1,floor((5-\x0)*sqrt(3)-0.5)}
 \real{rmax1=item(\A0,\calcmax)}
 \real{rmax2=item(\A0+\A1+6,\calcmax,\calcmax,\calcmax)}
 \real{r=randint(2..min(\rmax1,\rmax2))}
 \text{dessin=range 0,5,0,5
parallel 0,-10,10,10*sqrt(3)-10,0,1,15,grey
parallel 0,15,10,15-10*sqrt(3),0,-1,15,grey
parallel 0,0,5,0,0,0.5,10,grey
circle \x0,\y0,4,black
text black,\x0-0.05,\y0-0.05,medium,\O
circle \x0+\r/sqrt(3)*cos(\A0*pi/3),\y0+\r/sqrt(3)*sin(\A0*pi/3),4,black
text black,\x0+\r/sqrt(3)*cos(\A0*pi/3)-0.05,\y0+\r/sqrt(3)*sin(\A0*pi/3)-0.05,medium,\P}
 \text{image=draw(300,300
\dessin)}
 \text{sens=\A1>0?positif:négatif}
 \integer{x=60*(\x0+\r/sqrt(3)*cos((\A0+\A1)*pi/3))}
 \integer{y=300-60*(\y0+\r/sqrt(3)*sin((\A0+\A1)*pi/3))}
 \integer{d=10}
 \text{enonce=Sur la figure ci-contre, tous les triangles sont équilatéraux.<br>
  Quelle est l'image de \P par la rotation de sens \sens, de centre \O et d'angle \angle°}
#endif

#if defined TARGET_image4
 \title{TITRE 4}
 \integer{ch=randint(1..5)}
 \text{color=item(\ch,red,blue,yellow,green,purple)}
 \text{colorname=item(\ch,rouge,bleu,jaune,vert,violet)}
 \text{n=randitem(5,6,8)}
 \text{ch2=item(\n,,,,,2,2,,3)}
 \text{ch2=randint(1..\ch2)}
 \integer{angle=360/\n*\ch2}
 \integer{sens=randitem(1,-1)}
 \real{A1=\sens*2*pi/\n*\ch2}
\text{dessin=slib(polyregulier \n,300,1,1,black,black)}
\text{coord=row(1,\dessin)}
\real{A0=item(1,\coord)}
\real{r=item(2,\coord)}
\text{image=draw(300,300
\dessin
fcircle 150+\r*cos(\A0),150+\r*sin(\A0),10,\color
fcircle 150,150,4,black
text black,148,154,medium,\O)}
 \text{sens=\sens<0?positif:négatif}
 \integer{x=150+\r*cos(\A0+\A1)}
 \integer{y=150+\r*sin(\A0+\A1)}
 \integer{d=15}
 \text{enonce=\O est le centre du cercle circonscrit du polygone tracé.<br>
  Quelle est l'image du point \colorname par la rotation de sens \sens, de centre \O et d'angle \angle°}
#endif

#if defined TARGET_image5
 \title{TITRE 5}
 \integer{A0=randint(1..4)}
 \integer{A1=randint(1,-1)}
 \integer{angle=90}
 \integer{x0=randint(4..6)}
 \integer{y0=randint(4..6)}
 \integer{rmax1=min(9-\y0,\x0-1)}
 \integer{rmax2=min(\y0-1,9-\x0)}
 \real{r=randint(2..min(\rmax1,\rmax2))*sqrt(2)}
 \integer{x=20*(\x0+\r*cos((\A0+\A1)*pi/2+pi/4))}
 \integer{y=200-20*(\y0+\r*sin((\A0+\A1)*pi/2+pi/4))}
 \text{dessin=range 0,10,0,10
parallel 0,0,0,10,1,0,10,grey
parallel 0,0,10,0,0,1,10,grey
circle \x0,\y0,4,black
text black,\x0-0.1,\y0-0.2,medium,\O
circle \x0+\r*cos(\A0*pi/2+pi/4),\y0+\r*sin(\A0*pi/2+pi/4),4,black
text black,\x0+\r*cos(\A0*pi/2+pi/4)-0.1,\y0+\r*sin(\A0*pi/2+pi/4)-0.2,medium,\P}
 \text{image=draw(200,200
\dessin)}
 \text{sens=\A1>0?positif:négatif}
 \integer{d=5}
 \text{enonce=Quelle est l'image de \P par la rotation de sens \sens, de centre \O et d'angle \angle°}
#endif


\statement{
\enonce ?
<div class="wims_instruction">
 Cliquer sur la figure pour placer l'image.
</div>

<div class="wimscenter">\embed{r1} </div>}

\answer{}{\image;circle,\x,\y,\d}{type=coord}
