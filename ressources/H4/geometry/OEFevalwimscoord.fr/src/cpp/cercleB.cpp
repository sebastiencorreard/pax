target=cercle3,cercle4
#define TITRE Cercle
#include "author.inc"
\keywords{circle, coordinates,length}
\text{lettres=shuffle(A,B,C,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}

\text{v=wims(values v,-v for v=1 to 10)}
\text{v=shuffle(\v)}
\integer{xA=\v[1]}
\integer{yA=\v[2]}
\integer{xB=\v[3]}
\integer{yB=\v[4]}
\text{xC=simplify((\xA+\xB)/2)}
\text{yC=simplify((\yA+\yB)/2)}

#if defined TARGET_cercle3
 \title{TITRE 3}
 \text{l=sqrt(simplify((\xC-\xA)^2+(\yC-\yA)^2))}
 \text{question=Les coordonnées de \(\A\) sont (\xA ; \yA) et celles de \(\C\) sont (\xC ; \yC).
 <p>Quelle est la mesure du rayon de ce cercle&nbsp;}
 \text{reponse=Le rayon mesure }
#endif

#if defined TARGET_cercle4
 \title{TITRE 4}
 \text{l=sqrt(simplify((\xB-\xA)^2+(\yB-\yA)^2))}
 \text{question=Les coordonnées de \(\A\) sont (\xA ; \yA) et celles de \(\B\) sont (\xB ; \yB).
 <p>Quelle est la mesure du diamètre de ce cercle&nbsp;}
 \text{reponse=Le diamètre mesure }
#endif

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
\text{xCsol=\xC<0?(\xC):\xC}
\text{yCsol=\yC<0?(\yC):\yC}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
Le plan est muni d'un repère orthonormé \((O,I,J)).
\(\mathcal{C}) est un cercle de centre \(\C\) et de diamètre \([\A\,\B]).
\question ?
</p><div class="spacer">
  <b>Votre réponse</b> :
<label for="reply1">\reponse</label> \embed{r1,9} unités.
</div>
<div class="wims_instruction">
Vous devez taper sqrt(2) pour \(\sqrt{2}).
</div>
}

\answer{\reponse}{\l}{type=algexp}

% ajout par B. Mifsud
\solution{\img

<p>\introsol</p>
<p><b>Rappel : </b>
#if defined TARGET_cercle3
\(\A(\xA ; \yA)) et \(\C(\xC ; \yC)).
#endif
#if defined TARGET_cercle4
\(\A(\xA ; \yA)) et \(\B(\xB ; \yB)).
#endif
</p>
<p>Puisque \(\mathcal{C}) est un cercle de centre \(\C\) et de diamètre \([\A\,\B]),
il faut calculer la longueur
#if defined TARGET_cercle3
  \(\A \C).
#endif
#if defined TARGET_cercle4
  \(\A \B).
#endif
</p>
<p>
Or on sait que, dans le plan muni d'un repère othonormé, pour deux points \(A(x_A;y_A))
et \(B(x_B;y_B)) la longueur \(A B) se calcule avec la formule suivante :
\( \sqrt{(x_B-x_A)^2+(y_B-y_A)^2}\).</p>
<p>
<p>Ce qui donne ici : </p>
<div class="wimscenter">
#if defined TARGET_cercle3
\( \sqrt{(x_\A-x_\C)^2+(y_\A-y_\C)^2}=\sqrt{(\xA-\xCsol)^2+(\yA-\yCsol)^2}=\)\(\l\)
#endif
#if defined TARGET_cercle4
\( \sqrt{(x_\A-x_\B)^2+(y_\A-y_\B)^2}=\sqrt{(\xA-\xBsol)^2+(\yA-\yBsol)^2}=\)\(\l\)
#endif
</div>}
