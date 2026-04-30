target=rotangle1,rotangle2,rotangle3,rotangle4,rotangle5

#include "author.inc"
#define TITRE Angle d'une rotation
#if defined TARGET_rotangle1
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

 \integer{A=randint(4..7)}
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
flood \x0+\don[5]+0.5,\y0+\don[6]+0.5,\color[2]
circle \x0,\y0,4,black
text black,\x0,\y0-0.1,medium,O}
 \text{image=draw(200,200
\dessin)}
 \text{sens=\sens<0?négatif:positif}
 \text{enonce=Par une rotation de centre O et de sens \sens, l'image de la figure \colorname[1] est la figure \colorname[2].<br>
  Quelle est la mesure de l'angle de cette rotation}
#endif

#if defined TARGET_rotangle2
 \title{TITRE 2}
 \text{ch=randitem(5,6,8,9)}
 \text{color=red,blue,yellow,green,purple,grey,white,sienna,pink}
 \text{colorname=rouge,bleue,jaune,verte,violette,grise,blanche,marron,rose}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{dessin=slib(polyfig1 \ch,300,(\color))}
 \text{image=draw(300,300
\dessin)}
 \real{angle=360/\ch}
 \text{colorname=item(1 to \ch,\colorname)}
 \text{colorname=\colorname,\colorname}
 \integer{ch2=item(\ch,,,,,2,2,,3,3)}
 \integer{ch2=randint(1..\ch2)}
 \integer{angle=\ch2*\angle}
 \integer{m=2*\ch}
 \integer{M=ceil(\m/4)}
 \integer{m=floor(3*\m/4)}
 \integer{A=randint(\m..\M)}
 \integer{good=randint(1,2)}
 \integer{sens=item(\good,-1,1)}
 \text{B=item(\A+\sens*\ch2,\colorname)}
 \text{A=item(\A,\colorname)}
 \text{sens=\sens<0?positif:négatif}
 \text{enonce=Par une rotation de centre O et de sens \sens, l'image de la figure \A est la figure \B.<br>
  Quelle est la mesure de l'angle de cette rotation}
#endif

#if defined TARGET_rotangle3
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
 \integer{ch2=randint(1..3)}
 \integer{sens=randitem(-1,1)}
 \integer{angle=\angle*\ch2}
 \integer{B=\A+\sens*\angle}
 \real{y0=2.5}
 \real{x0=4.5/sqrt(3)}
 \matrix{don=randrow(30,4/3
30,2/3
30,5/3
10,1.5/sqrt(3))}
 \text{dessin=\dessin
flood \x0+\don[2]*cos((\don[1]+\A)*pi/180),\y0+\don[2]*sin((\don[1]+\A)*pi/180),\color[1]
flood \x0+\don[2]*cos((\don[1]+\B)*pi/180),\y0+\don[2]*sin((\don[1]+\B)*pi/180),\color[2]
circle \x0,\y0,4,black
text black,\x0,\y0-0.1,medium,O}
 \text{image=draw(300,300
\dessin)}
 \text{sens=\sens>0?positif:négatif}
 \text{enonce=Sur la figure ci-contre, tous les triangles sont équilatéraux.<br>
  Par une rotation de centre O et de sens \sens, l'image de la figure \colorname[1] est la figure \colorname[2].<br>
  Quelle est la mesure de l'angle de cette rotation}
#endif

#if defined TARGET_rotangle4
 \title{TITRE 4}
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
 \integer{ch2=randint(4..5)}
 \integer{sens=randitem(-1,1)}
 \integer{angle=\angle*\ch2}
 \integer{B=\A+\sens*\angle}
 \real{y0=2.5}
 \real{x0=4.5/sqrt(3)}
 \matrix{don=randrow(30,4/3
30,2/3
30,5/3
10,1.5/sqrt(3))}
 \text{dessin=\dessin
flood \x0+\don[2]*cos((\don[1]+\A)*pi/180),\y0+\don[2]*sin((\don[1]+\A)*pi/180),\color[1]
flood \x0+\don[2]*cos((\don[1]+\B)*pi/180),\y0+\don[2]*sin((\don[1]+\B)*pi/180),\color[2]
circle \x0,\y0,4,black
text black,\x0,\y0-0.1,medium,O}
 \text{image=draw(300,300
\dessin)}
 \text{sens=\sens>0?positif:négatif}
 \text{enonce=Sur la figure ci-contre, tous les triangles sont équilatéraux.<br>
 Par une rotation de centre O et de sens \sens, l'image de la figure \colorname[1] est la figure \colorname[2].<br>
 Quelle est la mesure de l'angle de cette rotation}
#endif

#if defined TARGET_rotangle5
 \title{TITRE 5}
 \text{ch=randitem(5,6,8,9)}
 \text{color=red,blue,yellow,green,purple,grey,white,sienna,pink}
 \text{colorname=rouge,bleue,jaune,verte,violette,grise,blanche,marron,rose}
 \text{chco=wims(values v for v=1 to 9)}
 \text{chco=shuffle(\chco)}
 \text{color=wims(item \chco of \color)}
 \text{colorname=wims(item \chco of \colorname)}
 \text{dessin=slib(polyfig1 \ch,300,(\color))}
 \text{image=draw(300,300
\dessin)}
 \real{angle=360/\ch}
 \text{colorname=item(1 to \ch,\colorname)}
 \text{colorname=\colorname,\colorname}
 \integer{ch2=item(\ch,,,,,2,2,,3,3)}
 \integer{ch2=randint(1..\ch2)}
 \integer{angle=(\ch-\ch2)*\angle}
 \integer{m=2*\ch}
 \integer{M=ceil(\m/4)}
 \integer{m=floor(3*\m/4)}
 \integer{A=randint(\m..\M)}
 \integer{good=randint(1,2)}
 \integer{sens=item(\good,-1,1)}
 \text{B=item(\A-\sens*\ch2,\colorname)}
 \text{A=item(\A,\colorname)}
 \text{sens=\sens<0?positif:négatif}
 \text{enonce=Par une rotation de centre O et de sens \sens, l'image de la figure \A est la figure \B.<br>
  Quelle est la mesure de l'angle de cette rotation}
#endif



\statement{
   \enonce ?
<p><b>Votre réponse :</b></p>
  <label for="reply1">L'angle de cette rotation est de</label> \embed{r1,5}° .
<div class="wimscenter"><img src="\image" alt=""></div>}

\answer{}{\angle}{type=numeric}
