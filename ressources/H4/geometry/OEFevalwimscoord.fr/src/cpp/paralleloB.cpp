target=parallelo3,parallelo4,parallelo5
#define TITRE Parallélogramme
#include "author.inc"
\keywords{length, parallelogram}
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

#if defined TARGET_parallelo3
 \title{TITRE 3}
 \integer{ch=randint(1..2)}
 \text{cote=item(\ch,\A \B,\A \D)}
 \text{question=Quelle est la mesure de la longueur du côté [\cote]&nbsp;}
 \text{reponse=\cote}
 \text{l=item(\ch,(\xu)^2+(\yu)^2,(\xv)^2+(\yv)^2)}
#endif

#if defined TARGET_parallelo4
 \title{TITRE 4}
 \text{cote=\B \D}
 \text{question=Quelle est la mesure de la longueur de la diagonale [\cote]&nbsp;}
 \text{reponse=\cote}
 \text{l=(\xB-\xD)^2+(\yB-\yD)^2}
#endif

#if defined TARGET_parallelo5
 \title{TITRE 5}
 \text{cote=\A \C}
 \text{question=Quelle est la mesure de la longueur de la diagonale [\cote]&nbsp;}
 \text{reponse=\cote}
 \text{l=(\xu+\xv)^2+(\yu+\yv)^2}
#endif

\text{l=sqrt(simplify(\l))}

\statement{
   Le plan est muni d'un repère orthonormé \((O,I,J)) et
\(\A \B \C \D) est un parallélogramme tel que :
<div class="wimscenter"> \(\A (\xA ; \yA)) &nbsp; , &nbsp;
\(\B (\xB ; \yB))&nbsp;,&nbsp; \(\D (\xD ; \yD))</div>
<p>\question?</p>
<div class="spacer">
  <b>Votre réponse</b> :
<label for="reply1">\reponse =</label> \embed{r1,8} unités
</div>}

\answer{\reponse}{\l}{type=algexp}
