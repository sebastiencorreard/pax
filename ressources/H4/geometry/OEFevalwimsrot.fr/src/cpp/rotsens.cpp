target=rotsens1,rotsens2,rotsens3,rotsens4,rotsens5

#include "author.inc"
#define TITRE Sens d'une rotation
#if defined TARGET_rotsens1
 \title{TITRE 1}
 \text{ch=randint(1..3)}
 \text{image=item(\ch,\imagedir/pentaA.gif,\imagedir/hexaA.gif,\imagedir/octoA.gif)}
 \text{angle=item(\ch,72,60,45)}
 \text{ltpoints=A,B,C,D,E
F,G,H,I,J
A,B,C,D,E,F
G,H,I,J,K,L
A,C,E,G,I,K,M,Q
B,D,F,H,J,L,N,P}
 \integer{so=randint(2*\ch-1..2*\ch)}
 \text{so=row(\so,\ltpoints)}
 \text{so=\so,\so}
 \integer{ch2=randint(1..2)}
 \integer{angle=\ch2*\angle}
 \integer{m=items(\so)}
 \integer{M=ceil(\m/4)}
 \integer{m=floor(3*\m/4)}
 \integer{A=randint(\m..\M)}
 \integer{good=randint(1,2)}
 \integer{sens=item(\good,-1,1)}
 \text{B=item(\A+\sens*\ch2,\so)}
 \text{A=item(\A,\so)}
 \text{list=positif,négatif}
 \text{Good=item(\good,\list)}
 \text{enonce=Par une rotation de centre O et d'angle \angle°, l'image de \A est \B.<br>Quel est le sens de cette rotation}
 \text{reponse=Cette rotation est de sens}
#endif

#if defined TARGET_rotsens2
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
\dessin
text black,150,155,medium,O)}
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
 \text{list=positif,négatif}
 \text{Good=item(\good,\list)}
 \text{enonce=Par une rotation de centre O et d'angle \angle°, l'image de la figure \A est la figure \B.<br>Quel est le sens de cette rotation}
 \text{reponse=Cette rotation est de sens}
#endif

#if defined TARGET_rotsens3
 \title{TITRE 3}
 \text{ch=randint(1..3)}
 \text{image=item(\ch,\imagedir/pentaA.gif,\imagedir/hexaA.gif,\imagedir/octoA.gif)}
 \text{angle=item(\ch,72,60,45)}
 \text{ltpoints=A,B,C,D,E
F,G,H,I,J
A,B,C,D,E,F
G,H,I,J,K,L
A,C,E,G,I,K,M,Q
B,D,F,H,J,L,N,P}
 \integer{so=randint(2*\ch-1..2*\ch)}
 \text{so=row(\so,\ltpoints)}
 \text{so=\so,\so}
 \integer{ch2=randint(1..2)}
 \integer{angle=\ch2*\angle}
 \integer{m=items(\so)}
 \integer{M=ceil(\m/4)}
 \integer{m=floor(3*\m/4)}
 \integer{A=randint(\m..\M)}
 \integer{good=randint(1,2)}
 \integer{sens=item(\good,-1,1)}
 \text{B=item(\A+\sens*\ch2,\so)}
 \text{C=item(\A-\sens*\ch2,\so)}
 \text{A=item(\A,\so)}
 \text{list=\C,\B,\A}
 \text{sens=\sens<0?positif:négatif}
 \text{Good=\B}
 \text{enonce=Quelle est l'image de \A par la rotation de centre O, d'angle \angle° et de sens \sens}
 \text{reponse=L'image de \A est}
#endif

#if defined TARGET_rotsens4
 \title{TITRE 4}
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
 \text{C=item(\A-\sens*\ch2,\colorname)}
 \text{A=item(\A,\colorname)}
 \text{list=\B,\C,\A}
 \text{sens=\sens<0?positif:négatif}
 \text{Good=\B}
 \text{enonce=Quelle est l'image de la figure \A par la rotation de centre O, d'angle \angle° et de sens \sens}
 \text{reponse=L'image de la figure \A est la figure}
#endif

#if defined TARGET_rotsens5
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
 \text{list=positif,négatif}
 \text{Good=item(\good,\list)}
 \text{enonce=Par une rotation de centre O et d'angle \angle°, l'image de la figure \A est la figure \B.<br>Quel est le sens de cette rotation}
 \text{reponse=Cette rotation est de sens}
#endif



\statement{
   \enonce ?<p>
<b>Votre réponse :</b></p>
\reponse \embed{c1}
 <div class="wimscenter">
  <img src="\image" alt="">
 </div>
 }

\choice{}{\Good}{\list}
