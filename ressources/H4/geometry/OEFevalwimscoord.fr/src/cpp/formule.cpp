target=formule1,formule2,formule3,formule4,formule5
#define TITRE Formule
#include "author.inc"

\text{lettres=shuffle(A,B,C,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}

#if defined TARGET_formule1
 \keywords{coordinates,midpoint}
 \title{TITRE 1}
 \text{enonce=Quelles sont les coordonnées du milieu du segment \([\A\,\B])}
 \integer{good=1}
 \text{bad=1,2,4,5,6}
#endif
#if defined TARGET_formule2
 \keywords{coordinates,vectors}
 \title{TITRE 2}
 \text{enonce=Quelles sont les coordonnées du vecteur \(\overrightarrow{\A \B})}
 \integer{good=4}
 \text{bad=1,2,4,5,6}
#endif
#if defined TARGET_formule3
 \title{TITRE 3}
 \keywords{length}
 \text{enonce=Quelle est la longueur du segment \([\A\,\B])}
 \integer{good=7}
 \text{bad=8,9,10,11}
 \text{comp=orthonormé}
#endif
#if defined TARGET_formule4
 \title{TITRE 4}
 \keywords{coordinates, midpoint}
 \text{enonce=Quelles sont les coordonnées du milieu du segment \([\A\,\B])}
 \integer{good=1}
 \text{bad=1,2,3}
#endif
#if defined TARGET_formule5
 \title{TITRE 5}
 \keywords{coordinates, vectors}
 \text{enonce=Quelles sont les coordonnées du vecteur \(\overrightarrow{\A \B})}
 \integer{good=4}
 \text{bad=4,5,6}
#endif

\text{Bad=\((\frac{x_\A+x_\B}{2};\frac{y_\A+y_\B}{2})),\((\frac{x_\A-x_\B}{2};\frac{y_\A-y_\B}{2})),\((\frac{x_\A+y_\A}{2};\frac{x_\B+y_\B}{2})),\((x_\B - x_\A ; y_\B - y_\A)),\((x_\A - x_\B ; y_\A - y_\B)),\((x_\B + x_\A ; y_\B  + y_\A)),\(\sqrt{(x_\B-x_\A)^2+(y_\B-y_\A)^2}),\((x_\B-x_\A)+(y_\B-y_\A)),\(\sqrt{(x_\B+x_\A)^2+(y_\B+y_\A)^2}),\(\sqrt{(x_\B-x_\A)^2-(y_\B-y_\A)^2}),\(\sqrt{(x_\B+x_\A)^2-(y_\B+y_\A)^2})}
\text{Good=item(\good,\Bad)}
\text{Bad=wims(item \bad of \Bad)}

\statement{
Soient \(\A) et \(\B) deux points de coordonnées respectivement
\((x_\A;y_\A)) et \((x_\B;y_\B)) dans un repère \comp \((O,I,J)).
<div class="spacer">
\enonce ?
</div>}

\choice{}{\Good}{\Bad}{option=shuffle}
