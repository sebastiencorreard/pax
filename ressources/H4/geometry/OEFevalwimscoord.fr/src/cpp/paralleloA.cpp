target=parallelo1,parallelo2
#define TITRE Parallélogramme
#include "author.inc"
\keywords{coordinates, parallelogram}
\text{lettres=shuffle(A,B,C,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}
\text{D=\lettres[4]}

\text{v=wims(values v,-v for v=1 to 10)}
\text{v=shuffle(\v)}
\integer{xA=\v[1]}
\integer{yA=\v[2]}
\integer{xu=\v[3]}
\integer{yu=\v[4]}
\integer{xv=\v[5]}
\integer{yv=\v[6]}
\integer{det=\xu*\yv-\xv*\yu}
\if{\det=0}{
 \integer{xu=3}
 \integer{yu=1}
 \integer{xv=4}
 \integer{yv=-2}
}
\integer{xB=\xA+\xu}
\integer{yB=\yA+\yu}
\integer{xD=\xA+\xv}
\integer{yD=\yA+\yv}

#if defined TARGET_parallelo1
 \title{TITRE 1}
 \text{question=Quelles sont les coordonnées de \C}
 \text{reponse=Les coordonnées du point \C sont}
 \integer{x=\xB+\xv}
 \integer{y=\yB+\yv}
#endif

#if defined TARGET_parallelo2
 \title{TITRE 2}
 \text{question=Quelles sont les coordonnées du centre de ce parallélogramme}
 \text{reponse=les coordonnées du centre sont}
 \real{x=(\xB+\xD)/2}
 \real{y=(\yB+\yD)/2}
#endif

\if{\confparm1=2}
{
 \text{affcoord=[\left( reply1 ; reply2 \right)]}
 \text{affsolution=\left( \x ; \y \right)}
}{
 \text{affcoord=[\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}]}
 \text{affsolution=\begin{pmatrix} \x \\ \y \end{pmatrix}}
}
%%%%%%%%%% sol %%%%%%%%%%%%
\text{xDsol=\xD<0? (\xD):\xD}
\text{yDsol=\yD<0? (\yD):\yD}
\integer{xBD=\xB+\xD}
\integer{yBD=\yB+\yD}
%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
   Le plan est muni d'un repère \((O,I,J)) et
\(\A \B \C \D) est un parallélogramme tel que :
<div class="wimscenter"> \(\A (\xA ; \yA)\), \(\B (\xB ; \yB)\),  \(\D (\xD ; \yD)\)</div>
<p>\question ?</p>
<div class="spacer">
  <b>Votre réponse</b> :
\reponse <div class="wimscenter">\special{mathmlinput \affcoord,5,noanswer
reply1,,color:blue;text-align:center;
reply2,,color:blue;text-align:center;
}
.</div>
</div>}

\answer{Abscisse}{\x}{type=numexp}
\answer{Ordonnée}{\y}{type=numexp}
%%% MB %%%%%%ù
\solution{<p>Dans la suite, les coordonnées d'un point \(A) se noteront \((x_A;y_A)).</p>
#if defined TARGET_parallelo1
<p>\(\A \B \C \D) est un parallélogramme donc le milieu de \([\A\,\C]\) est
confondu avec le milieu de\([\B\,\D]\). Par conséquent les deux milieux ont les mêmes
coordonnées ce qui se traduit par la relation suivante : </p>
\(\left\lbrace
 \begin{array}{lcl}
\frac{x_\A+x_\C}{2} & = & \frac{x_\B+x_\D}{2} \\ \frac{y_D+y_F}{2} & = & \frac{y_C+y_A}{2}
 \end{array}
\right.
\)
\( \Leftrightarrow  \left\lbrace
 \begin{array}{lcl}
\frac{\xA+x_\C}{2} & = & \frac{\xB+\xDsol}{2} \\ \frac{\yA+y_\C}{2} & = & \frac{\yB+\yDsol}{2}
 \end{array}
\right.
\)

\( \Leftrightarrow  \left\lbrace
 \begin{array}{lcl}
\frac{\xA+x_\C}{2} & = & \frac{\xBD}{2} \\ \frac{\yA+y_\C}{2} & = & \frac{\yBD}{2}
 \end{array}
\right.
\)
\( \Leftrightarrow  \left\lbrace
 \begin{array}{lcl}
\xA+x_\C & = & \xBD \\ \yA+y_\C & = & \yBD
 \end{array}
\right.
\)
\( \Leftrightarrow  \left\lbrace
 \begin{array}{lcl}
x_\C & = & \x \\ y_\C & = & \y
 \end{array}
\right.
\)
<p>Le point \C a pour coordonnées \(\affsolution).</p>
#endif
#if defined TARGET_parallelo2
<p>Puisque \(\A \B \C \D) est un parallélogramme, le centre est le milieu de \([\B\,\D]\).</p>
<p> Calculons les coordonnées du milieu de ce segment :</p>
<ul><li>Son abscisse : \(x=\frac{x_\B+x_\D}{2}=\frac{\xB+\xDsol}{2}=\x\).</li>
<li>Son ordonnée : \(y=\frac{y_\B+y_\D}{2}=\frac{\yB+\yDsol}{2}=\y\).<//li></ul>
#endif
}
