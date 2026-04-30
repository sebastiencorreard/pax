target=cercle1,cercle2
#define TITRE Cercle
#include "author.inc"
\keywords{circle, coordinates}
\text{lettres=shuffle(A,B,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}

\text{v=wims(values v,-v for v=1 to 10)}
\text{v=shuffle(\v)}
\integer{xA=\v[1]}
\integer{yA=\v[2]}
\integer{xB=\v[3]}
\integer{yB=\v[4]}
\real{xC=(\xA+\xB)/2}
\real{yC=(\yA+\yB)/2}

#if defined TARGET_cercle1
 \title{TITRE 1}
 \text{question=Les coordonnées de \(\A) sont (\xA ; \yA) et celles de \(\B) sont (\xB ; \yB).
 <p>Quelles sont les coordonnées du centre du cercle&nbsp;}
 \text{reponse=les coordonnées du centre sont}
 \real{x=\xC}
 \real{y=\yC}
#endif
#if defined TARGET_cercle2
 \title{TITRE 2}
 \text{question=Les coordonnées de \(\A) sont (\xA ; \yA) et celles de \(\C) sont (\xC ; \yC).
 <p>Quelles sont les coordonnées du point \(\B)&nbsp;}
 \text{reponse=les coordonnées du point \(\B) sont}
 \real{x=\xB}
 \real{y=\yB}
#endif

\if{\confparm1=2}
{
 \text{affcoord=[\left( reply1 ; reply2 \right)]}
}{
 \text{affcoord=[\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}]}
}
%%%%%%%%%%%%% Pour solution MB%%%%%%%%%%%%%%

\text{imagesol=draw(200,200
xrange -100,100
yrange -100,100
circle 0,0,128,black
text blue,-75,0,medium , \A
text blue,70,0,medium , \B
crosshair 64,0,blue
text red,0,20,medium , \C
crosshair 0,0,red
crosshair -64,0,blue
segment -64,0,64,0,blue
segment -36,-8,-34,8,blue
segment -33,-8,-31,8,blue
segment 36,8,34,-8,blue
segment 33,8,31,-8,blue
)}
\text{img=<img src="\imagesol" alt="représentation graphique" style="float:right;margin-top:-0.5em">}
\text{introsol=Il est souvent très utile de faire une figure codée.}
%%%%% affichage () si besoin
\text{xBsol=\xB<0?(\xB):\xB}
\text{yBsol=\yB<0?(\yB):\yB}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
<p>Le plan est muni d'un repère orthonormé \((O,I,J)) et
\(\mathcal{C}) est un cercle de centre \(\C) et de diamètre \([ \A \B ]).
\question?</p>
<div class="spacer">
  <b>Votre réponse</b> :
\reponse
<div class="wimscenter">
\special{mathmlinput \affcoord,5,noanswer
reply1,,color:blue;text-align:center;
reply2,,color:blue;text-align:center;
}
</div>
</div>
}

\answer{Abscisse}{\x}{type=numexp}
\answer{Ordonnée}{\y}{type=numexp}

#if defined TARGET_cercle1
% ajout par B. Mifsud
\solution{\img
<p>
<b>On sait que </b>: dans le plan muni d'un repère, pour deux points \(A(x_A;y_A)\)
et \(B(x_B;y_B)) les coordonnées du milieu du segment \([A\,B]\) se calculent
avec la formule suivante : </p>
<div class="wimscenter">
(\(\frac{x_A+x_B}{2}) ; \(\frac{y_A+y_B}{2})).
</div>
<p>\(\C) est le centre du cercle de diamètre \([ \A\,\B ]), donc \(\C) est le
milieu du segment \([ \A\,\B ]).</p>
<p>Les coordonnées des points \(\A) et \(\B) sont \((\xA;\yA)) et \((\xB;\yB)).
On en déduit que les coordonnées du
centre \(\C) sont : </p>
<div class="wimscenter">
(\(\frac{\xA+\xBsol}{2}) ; \(\frac{\yA+\yBsol}{2}))=(\(\x) ; \(\y)).
</div> }
#endif
#if defined TARGET_cercle2
% ajout par B. Mifsud
\solution{\img
<p> <b>On sait que </b>:
dans le plan muni d'un repère, pour deux points \(A(x_A;y_A))
et \(B(x_B;y_B)) les coordonnées du milieu du segment \([ A\,B ]) se calculent
avec la formule suivante :</p>
<div class="wimscenter">
(\(\frac{x_A+x_B}{2}) ; \(\frac{y_A+y_B}{2})).
</div>
<p>\(\C) est le centre du cercle de diamètre \([ \A\,\B ]), donc \(\C) est le
milieu du segment \([ \A\,\B ]).</p>
<p>Les coordonnées \((x_\B;y_\B)) du point \(\B) vérifient donc : </p>
<div class="wimscenter">
(\(\frac{\xA+x_\B}{2}) ; \(\frac{\yA+y_\B}{2}))=(\(\xC) ; \(\yC)).
</div>
<p> Il faut résoudre :</p>
<div class="wimscenter">
\(\frac{\xA+x_\B}{2}=\xC) et \(\frac{\yA+y_\B}{2}=\yC).
</div>
<p>Ce qui donne :</p>
<div class="wimscenter">
\(x_\B=\x) et \(y_\B=\y).
</div>
}
#endif
