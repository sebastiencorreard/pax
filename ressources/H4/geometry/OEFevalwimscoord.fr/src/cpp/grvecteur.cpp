target=grvecteur1,grvecteur2,grvecteur3,grvecteur4,grvecteur5
#define TITRE Coordonnées d'un vecteur (graphique)
#include "author.inc"
\keywords{coordinates, vectors}
\text{lettres=shuffle(u,v,w)}
\text{A=\lettres[1]}
#if defined TARGET_grvecteur1
 \title{TITRE 1}
 \integer{x1=randitem(1,-1)*randint(1..4)}
 \integer{x2=\x1}
 \integer{y1=randitem(1,-1)*randint(2..4)}
 \integer{y2=\y1+randitem(2,4,6)*randitem(-1,1)}
#endif
#if defined TARGET_grvecteur2
 \title{TITRE 2}
 \integer{y1=randitem(1,-1)*randint(1..4)}
 \integer{y2=\y1}
 \integer{x1=randitem(1,-1)*randint(2..4)}
 \integer{x2=\x1+randitem(2,4,6)*randitem(-1,1)}
#endif
#if defined TARGET_grvecteur3
 \title{TITRE 3}
 \integer{y1=randitem(1,-1)*randitem(1,3,5)}
 \integer{y2=\y1+randitem(2,4,6)*randitem(-1,1)}
 \integer{x1=randitem(1,-1)*randitem(1,3,5)}
 \integer{x2=\x1+randitem(2,4,6)*randitem(-1,1)}
#endif
#if defined TARGET_grvecteur4
 \title{TITRE 4}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \integer{y1=randitem(1,-1)*randitem(1,3,5)}
  \integer{x1=randitem(1,-1)*randitem(1,2,3,4,5)}
  \integer{y2=\y1+randitem(2,4,6)*randitem(-1,1)}
  \integer{x2=-\x1}
 }{
  \integer{x1=randitem(1,-1)*randitem(1,3,5)}
  \integer{y1=randitem(1,-1)*randitem(1,2,3,4,5)}
  \integer{x2=\x1+randitem(2,4,6)*randitem(-1,1)}
  \integer{y2=-\y1}
 }
#endif
#if defined TARGET_grvecteur5
 \title{TITRE 5}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \integer{y1=randitem(1,-1)*randitem(1,3,5)}
  \integer{x1=randitem(1,-1)*randitem(1,2,3,4,5)}
  \integer{y2=\y1+randitem(2,4,6)*randitem(-1,1)}
  \integer{x2=\x1+randitem(1,-1)*randitem(1,3,5)}
 }{
  \integer{x1=randitem(1,-1)*randitem(1,3,5)}
  \integer{y1=randitem(1,-1)*randitem(1,2,3,4,5)}
  \integer{x2=\x1+randitem(2,4,6)*randitem(-1,1)}
  \integer{y2=\y1+randitem(1,-1)*randitem(1,3,5)}
 }
#endif

\text{color=randitem(red,green,blue,purple)}

\integer{size=300}
\integer{m1=max(abs(\x1),abs(\x2))+1}
\integer{m2=max(abs(\y1),abs(\y2))+1}
\integer{m=max(\m1,\m2)+1}
\text{dessin=range -\m1,\m1,-\m2,\m2
parallel -\m1,-\m2,\m1,-\m2,0,1,2*\m2+1,grey
parallel -\m1,-\m2,-\m1,\m2,1,0,2*\m1+1,grey
arrow -\m1,0,\m1,0,20,black
arrow 0,-\m2,0,\m2,20,black
text black,-0.4,0,medium,0
text black,\m1-0.5,0,medium,X
text black,-0.5,\m2,medium,Y
text black,-0.4,1.2,medium,1
text black,1,0,medium,1
linewidth 2
arrow \x1,\y1,\x2,\y2,15,\color}
\text{figure=draw(\size,\size
\dessin)}
\text{x=simplify(\x2-\x1)}
\text{y=simplify(\y2-\y1)}

\if{\confparm1=2}{
 \text{affcoord=[\left( reply1 ; reply2 \right)]}
}{
 \text{affcoord=[\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}]}
}

\statement{
<div class="grid-x grid-margin-x">
  <div class="cell medium-6 small-12  flex-dir-column">
    <div class="flex-child-auto">
        Le plan muni d'un repère \((O,I,J)).
        On a tracé un représentant du vecteur \(\overrightarrow{\A}\).
        <p>Quelles sont ses coordonnées ?</p>
    </div>

    <div class="flex-child-auto">
        <b>Votre réponse</b> :
          Les coordonnées du vecteur \(\overrightarrow{\A}\) sont
          <div class="wimscenter">
          \special{mathmlinput \affcoord,5,noanswer
reply1,,color:blue;text-align:center;
reply2,,color:blue;text-align:center;
}.
          </div>
    </div>
  </div>
  <div class="cell medium-6 small-12">
     <div class="unbreakable"><img src="\figure" alt=""></div>
  </div>
</div>
}

\answer{Abscisse}{\x}{type=numexp}
\answer{Ordonnée}{\y}{type=numexp}
