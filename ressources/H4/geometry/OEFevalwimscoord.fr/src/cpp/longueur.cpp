target=longueur1,longueur2,longueur3,longueur4,longueur5
#define TITRE Longueur d'un segment
\keywords{length}
#include "author.inc"

\text{lettres=shuffle(A,B,C,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}

#if defined TARGET_longueur1
 \title{TITRE 1}
 \text{long=randrow(3,4
6,8)}
 \text{long=shuffle(\long)}
 \integer{s1=randitem(1,-1)}
 \integer{s2=randitem(1,-1)}
 \integer{x3=\s1*randint(1..6)}
 \integer{y3=\s2*randint(1..6)}
 \integer{x1=\x3-\s1*\long[1]}
 \integer{y1=\y3}
 \integer{x2=\x3}
 \integer{y2=\y3-\s2*\long[2]}
#endif
#if defined TARGET_longueur2
 \title{TITRE 2}
 \text{long=shuffle(2,3,4,5,6,7,8,9,10)}
 \integer{g=gcd(\long[1],\long[2])}
 \integer{l1=\long[1]/\g}
 \integer{l2=\long[2]/\g}
 \integer{s1=randitem(1,-1)}
 \integer{s2=randitem(1,-1)}
 \integer{x3=\s1*randint(1..6)}
 \integer{y3=\s2*randint(1..6)}
 \integer{x1=\x3-\s1*\l1}
 \integer{y1=\y3}
 \integer{x2=\x3}
 \integer{y2=\y3-\s2*\l2}
#endif
#if defined TARGET_longueur3
 \title{TITRE 3}
 \text{long=shuffle(2,3,4,5)}
 \integer{g=randitem(2,3)}
 \integer{l1=\long[1]*\g}
 \integer{l2=\long[2]*\g}
 \integer{s1=randitem(1,-1)}
 \integer{s2=randitem(1,-1)}
 \integer{x3=\s1*randint(1..6)}
 \integer{y3=\s2*randint(1..6)}
 \integer{x1=\x3-\s1*\l1}
 \integer{y1=\y3}
 \integer{x2=\x3}
 \integer{y2=\y3-\s2*\l2}
#endif
#if defined TARGET_longueur4
 \title{TITRE 4}
 \text{r=randitem(2,3,5)}
 \text{c=shuffle(2,3,4,5,6,7,8,9)}
 \text{x1=\c[1]*sqrt(\r)}
 \text{y1=\c[2]}
 \text{x2=\c[3]*sqrt(\r)}
 \text{y2=\c[4]}
 \text{d=randrow(\x1,\y1,\x2,\y2
\y1,\x1,\y2,\x2)}
 \text{x1=\d[1]}
 \text{y1=\d[2]}
 \text{x2=\d[3]}
 \text{y2=\d[4]}
#endif
#if defined TARGET_longueur5
 \title{TITRE 5}
 \text{r=randitem(2,3,5)}
 \text{c=wims(values v,-v for v=2 to 9)}
 \text{c=shuffle(\c)}
 \text{x1=\c[1]*sqrt(\r)}
 \text{y1=\c[2]*sqrt(\r)}
 \text{x2=\c[3]*sqrt(\r)}
 \text{y2=\c[4]*sqrt(\r)}
#endif
\text{l=sqrt(simplify(((\x2)-(\x1))^2+((\y2)-(\y1))^2))}
\real{lreal=\l}
\text{l1=. notin \lreal? \lreal: \l}

\statement{Soient \(\A\) et \(\B\) deux points du plan muni d'un repère orthonormé \((O,I,J)) ;
\(\A) a pour coordonnées \(( \x1 ; \y1 )) et \(\B) a pour coordonnées \(( \x2 ; \y2 )).
<p>
  Quelle est la mesure de la longueur du segment \([\A\,\B]) ?
</p>
<div class="spacer">
<b>Votre réponse</b> :
<label for="reply1">\(\A \B =)</label>\embed{r1,9} unités.
<div class="wims_instruction">Tapez sqrt(2) pour \(\sqrt{2}).</div>
</div>}

\answer{\A \B}{\l}{type=algexp}

% ajout par B. Mifsud
\solution{On sait que, dans le plan muni d'un repère orthonormé,
pour deux points \(A (x_A;y_A)\) et \(B(x_B;y_B)\) la longueur \(A B\) se calcule
avec la formule suivante :
<div class="wimscenter">
\(A B = sqrt((x_A-(x_B))^2+(y_A-(y_B))^2)\).
</div>
On obtient ici :
<div class="wimscenter">
  \(\A \B = sqrt((\x2-(\x1))^2+(\y2-(\y1))^2)=\l1).
</div>}
