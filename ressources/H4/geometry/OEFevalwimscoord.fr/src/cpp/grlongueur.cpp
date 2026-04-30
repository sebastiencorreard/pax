target=grlongueur1,grlongueur2,grlongueur3,grlongueur4,grlongueur5
#define TITRE Longueur d'un segment (graphique)
#include "author.inc"
\keywords{length}
\text{lettres=shuffle(A,B,C,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
#if defined TARGET_grlongueur1
 \title{TITRE 1}
 \integer{x1=randitem(1,-1)*randint(1..4)}
 \integer{x2=\x1}
 \integer{y1=randitem(1,-1)*randint(2..4)}
 \integer{y2=\y1+randitem(2,4,6)*randitem(-1,1)}
#endif
#if defined TARGET_grlongueur2
 \title{TITRE 2}
 \integer{y1=randitem(1,-1)*randint(1..4)}
 \integer{y2=\y1}
 \integer{x1=randitem(1,-1)*randint(2..4)}
 \integer{x2=\x1+randitem(2,4,6)*randitem(-1,1)}
#endif
#if defined TARGET_grlongueur3
 \title{TITRE 3}
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
#if defined TARGET_grlongueur4
 \title{TITRE 4}
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
#if defined TARGET_grlongueur5
 \title{TITRE 5}
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

\integer{size=300}
\integer{m1=max(abs(\x1),abs(\x2))}
\integer{m2=max(abs(\y1),abs(\y2))}
\integer{m=max(\m1,\m2)+1}
\text{dessin=range -\m,\m,-\m,\m
parallel -\m,-\m,\m,-\m,0,1,2*\m+1,grey
parallel -\m,-\m,-\m,\m,1,0,2*\m+1,grey
arrow -\m,0,\m,0,20,black
arrow 0,-\m,0,\m,20,black
text black,-0.4,0,medium,0
text black,\m-0.5,0,medium,X
text black,-0.5,\m,medium,Y
text black,-0.4,1.2,medium,1
text black,1,0,medium,1
circle \x1,\y1,5,red
circle \x2,\y2,5,red
text red,\x1,\y1-0.1,medium,\A
text red,\x2,\y2-0.1,medium,\B}
\text{figure=draw(\size,\size
\dessin)}
\text{l=sqrt(simplify((\x2-\x1)^2+(\y2-\y1)^2))}

\statement{
<div class="grid-x grid-margin-x">
  <div class="cell medium-6 small-12  flex-dir-column">
    <div class="flex-child-auto">
      Soient \(\A) et \(\B) deux points du plan muni d'un repère orthonormé \((O,I,J)).
<p>Quelle est la mesure de la longueur du segment \([\A\,\B]) ?</p>
    </div>
    <div class="flex-child-auto">
        <b>Votre réponse</b> :
          <label for="reply1">\(\A \B =)</label>\embed{r1,9} unités.
         <div class="wims_instruction">Tapez <span class="tt">sqrt(2)</span> pour \(\sqrt{2}).</div>
    </div>
  </div>
  <div class="cell medium-6 small-12">
     <div class="unbreakable"><img src="\figure" alt=""></div>
  </div>
</div>
}

\answer{\A \B}{\l}{type=algexp}

#if defined TARGET_grlongueur3 || defined TARGET_grlongueur4 || defined TARGET_grlongueur5
% ajout par B. Mifsud
\solution{<p>Par définition, dans le plan muni d'un repère orthonormé, pour deux points
\(A) \((x_A;y_A)) et \(B) \((x_B;y_B)),
la longueur \(AB) se calcule
avec la formule suivante :
<div class="wimscenter">
\(AB = sqrt(((x_A)-(x_B))^2+((y_A)-(y_B))^2)).
</div>
On obtient ici :
<div class="wimscenter">
  \(\A \B = sqrt(((\x2)-(\x1))^2+((\y2)-(\y1))^2)= \l ).
</div>}
#endif
